#include <set>

#include <Common.h>
#include <Logging/Logger.h>
#include <Util/Util.h>
#include <Util/UtilMath.h>
#include <Exd/ExdDataGenerated.h>
#include <Database/DatabaseDef.h>

#include <MySqlBase.h>
#include <Connection.h>

#include <Network/GamePacketNew.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>

#include "Actor/Player.h"
#include "Inventory/ItemContainer.h"
#include "Inventory/Item.h"
#include "Inventory/ItemUtil.h"

#include "Forwards.h"
#include "Land.h"
#include "Framework.h"
#include "House.h"

extern Sapphire::Framework g_fw;

using namespace Sapphire::Common;

Sapphire::Land::Land( uint16_t territoryTypeId, uint8_t wardNum, uint8_t landId, uint32_t landSetId,
                  Sapphire::Data::HousingLandSetPtr info ) :
  m_currentPrice( 0 ),
  m_minPrice( 0 ),
  m_nextDrop( static_cast< uint32_t >( Util::getTimeSeconds() ) + 21600 ),
  m_ownerId( 0 ),
  m_landSetId( landSetId ),
  m_landInfo( info ),
  m_type( Common::LandType::none ),
  m_fcIcon( 0 ),
  m_fcIconColor( 0 ),
  m_fcId( 0 ),
  m_iconAddIcon( 0 )
{
  memset( &m_tag, 0x00, 3 );

  m_landIdent.landId = landId;
  m_landIdent.territoryTypeId = territoryTypeId;
  m_landIdent.wardNum = wardNum;
  m_landIdent.worldId = 67; // todo: fix this

  m_minPrice = m_landInfo->minPrice[ m_landIdent.landId ];
  m_maxPrice = m_landInfo->initialPrice[ m_landIdent.landId ];
}

Sapphire::Land::~Land() = default;

void Sapphire::Land::init( Common::LandType type, uint8_t size, uint8_t state, uint32_t currentPrice, uint64_t ownerId, uint64_t houseId )
{
  m_type = type;
  m_size = size;
  m_state = state;
  m_currentPrice = currentPrice;
  m_ownerId = ownerId;

  // fetch the house if we have one for this land
  if( houseId > 0 )
    m_pHouse = make_House( houseId, m_landSetId, getLandIdent() );

  auto pExdData = g_fw.get< Data::ExdDataGenerated >();
  auto info = pExdData->get< Sapphire::Data::HousingMapMarkerInfo >( m_landIdent.territoryTypeId, m_landIdent.landId );
  if( info )
  {
    m_mapMarkerPosition.x = info->x;
    m_mapMarkerPosition.y = info->y;
    m_mapMarkerPosition.z = info->z;
  }

  switch( m_size )
  {
    case HouseSize::Cottage:
      m_maxPlacedExternalItems = 20;
      m_maxPlacedInternalItems = 200;
      break;
    case HouseSize::House:
      m_maxPlacedExternalItems = 30;
      m_maxPlacedInternalItems = 300;
      break;
    case HouseSize::Mansion:
      m_maxPlacedExternalItems = 40;
      m_maxPlacedInternalItems = 400;
      break;
    default:
      break;
  }

  // init item containers
  auto setupContainer = [ this ]( InventoryType type, uint16_t maxSize )
  {
    m_landInventoryMap[ type ] = make_ItemContainer( type, maxSize, "houseiteminventory", true, true );
  };

  setupContainer( InventoryType::HousingOutdoorAppearance, 8 );
  setupContainer( InventoryType::HousingOutdoorPlacedItems, m_maxPlacedExternalItems );
  setupContainer( InventoryType::HousingOutdoorStoreroom, m_maxPlacedExternalItems );

  setupContainer( InventoryType::HousingInteriorAppearance, 9 );

  // nb: so we're going to store these internally in one container because SE is fucked in the head
  // but when an inventory is requested, we will split them into groups of 50
  setupContainer( InventoryType::HousingInteriorPlacedItems1, m_maxPlacedInternalItems );
  setupContainer( InventoryType::HousingInteriorStoreroom1, m_maxPlacedInternalItems );

  loadItemContainerContents();
}

void Sapphire::Land::loadItemContainerContents()
{
  if( !m_pHouse )
    return;

  auto ident = *reinterpret_cast< uint64_t* >( &m_landIdent );
  g_fw.get< Sapphire::Logger >()->debug( "Loading housing inventory for ident: " + std::to_string( ident ) );

  auto pDB = g_fw.get< Db::DbWorkerPool< Db::ZoneDbConnection > >();

  auto stmt = pDB->getPreparedStatement( Db::LAND_INV_SEL_HOUSE );
  stmt->setUInt64( 1, ident );

  auto res = pDB->query( stmt );

  std::unordered_map< uint16_t, std::vector< std::pair< uint16_t, uint32_t > > > items;

  while( res->next() )
  {
    auto containerId = res->getUInt( "ContainerId" );
    auto itemId = res->getUInt64( "ItemId" );
    auto slotId = res->getUInt( "SlotId" );

    items[ containerId ].push_back( std::make_pair( slotId, itemId ) );
  }

  res.reset();

  for( auto it = items.begin(); it != items.end(); it++ )
  {
    auto container = m_landInventoryMap[ it->first ];

    // todo: delet this
    for( auto fuck = it->second.begin(); fuck != it->second.end(); fuck++ )
    {
      auto item = Sapphire::Items::Util::loadItem( fuck->second );
      if( item )
        container->setItem( fuck->first, item );
    }
  }
}

uint32_t Sapphire::Land::convertItemIdToHousingItemId( uint32_t itemId )
{
  auto pExdData = g_fw.get< Data::ExdDataGenerated >();
  auto info = pExdData->get< Sapphire::Data::Item >( itemId );
  return info->additionalData;
}

uint32_t Sapphire::Land::getCurrentPrice() const
{
  return m_currentPrice;
}

uint32_t Sapphire::Land::getMaxPrice() const
{
  return m_maxPrice;
}

//Primary State
void Sapphire::Land::setSize( uint8_t size )
{
  m_size = size;
}

void Sapphire::Land::setState( uint8_t state )
{
  m_state = state;
}

void Sapphire::Land::setSharing( uint8_t state )
{
  m_iconAddIcon = state;
}

void Sapphire::Land::setLandType( Common::LandType type )
{
  m_type = type;
}

uint8_t Sapphire::Land::getSize() const
{
  return m_size;
}

uint8_t Sapphire::Land::getState() const
{
  return m_state;
}

uint8_t Sapphire::Land::getSharing() const
{
  return m_iconAddIcon;
}

uint32_t Sapphire::Land::getLandSetId() const
{
  return m_landSetId;
}

Sapphire::Common::LandIdent Sapphire::Land::getLandIdent() const
{
  return m_landIdent;
}

Sapphire::HousePtr Sapphire::Land::getHouse() const
{
  return m_pHouse;
}

FFXIVARR_POSITION3 Sapphire::Land::getMapMarkerPosition()
{
  return m_mapMarkerPosition;
}

Sapphire::Common::LandType Sapphire::Land::getLandType() const
{
  return m_type;
}

//Free Comapny
void Sapphire::Land::setFreeCompany( uint32_t id, uint32_t icon, uint32_t color )
{
  m_fcId = id;
  m_fcIcon = icon;
  m_fcIconColor = color; //RGBA
}

uint32_t Sapphire::Land::getFcId()
{
  return m_fcIcon;
}

uint32_t Sapphire::Land::getFcIcon()
{
  return m_fcIcon;
}

uint32_t Sapphire::Land::getFcColor()
{
  return m_fcIconColor;
}

//Player
void Sapphire::Land::setOwnerId( uint64_t id )
{
  m_ownerId = id;
}

uint64_t Sapphire::Land::getOwnerId()
{
  return m_ownerId;
}

uint32_t Sapphire::Land::getDevaluationTime()
{
  return m_nextDrop - static_cast< uint32_t >( Util::getTimeSeconds() );
}

void Sapphire::Land::setCurrentPrice( uint32_t currentPrice )
{
  m_currentPrice = currentPrice;
}

void Sapphire::Land::setLandTag( uint8_t slot, uint8_t tag )
{
  m_tag[ slot ] = tag;
}

uint8_t Sapphire::Land::getLandTag( uint8_t slot )
{
  return m_tag[ slot ];
}

void Sapphire::Land::updateLandDb()
{
  uint32_t houseId = 0;

  if( getHouse() )
    houseId = getHouse()->getHouseId();

  // todo: change to prepared statement
  auto pDb = g_fw.get< Db::DbWorkerPool< Db::ZoneDbConnection > >();
  pDb->directExecute( "UPDATE land SET status = " + std::to_string( m_state )
  + ", LandPrice = " + std::to_string( getCurrentPrice() )
  + ", UpdateTime = " + std::to_string( getDevaluationTime() )
  + ", OwnerId = " + std::to_string( getOwnerId() )
  + ", HouseId = " + std::to_string( houseId )
  + ", Type = " + std::to_string( static_cast< uint32_t >( m_type ) ) //TODO: add house id
  + " WHERE LandSetId = " + std::to_string( m_landSetId )
  + " AND LandId = " + std::to_string( m_landIdent.landId ) + ";" );

  if( auto house = getHouse() )
    house->updateHouseDb();
}

void Sapphire::Land::update( uint32_t currTime )
{
  if( getState() == HouseState::forSale )
  {
    if( m_nextDrop < currTime && m_minPrice < m_currentPrice )
    {
      m_nextDrop = currTime + 21600;
      m_currentPrice = static_cast< uint32_t >( ( m_currentPrice / 100 ) * 99.58f );
      updateLandDb();
    }
  }
}

uint32_t Sapphire::Land::getNextHouseId()
{
  auto pDb = g_fw.get< Db::DbWorkerPool< Db::ZoneDbConnection > >();
  auto pQR = pDb->query( "SELECT MAX( HouseId ) FROM house" );

  if( !pQR->next() )
    return 0;

  return pQR->getUInt( 1 ) + 1;
}

bool Sapphire::Land::setPreset( uint32_t itemId )
{
  auto housingItemId = convertItemIdToHousingItemId( itemId );

  auto exdData = g_fw.get< Sapphire::Data::ExdDataGenerated >();
  if( !exdData )
    return false;

  auto housingPreset = exdData->get< Sapphire::Data::HousingPreset >( housingItemId );
  if( !housingPreset )
    return false;

  if( !getHouse() )
  {
    // todo: i guess we'd create a house here?
    auto newId = getNextHouseId();
    m_pHouse = make_House( newId, getLandSetId(), getLandIdent() );
  }


  getHouse()->setHousePart( Common::HousePartSlot::ExteriorRoof, convertItemIdToHousingItemId( housingPreset->exteriorRoof ) );
  getHouse()->setHousePart( Common::HousePartSlot::ExteriorWall, convertItemIdToHousingItemId( housingPreset->exteriorWall ) );
  getHouse()->setHousePart( Common::HousePartSlot::ExteriorWindow, convertItemIdToHousingItemId( housingPreset->exteriorWindow ) );
  getHouse()->setHousePart( Common::HousePartSlot::ExteriorDoor, convertItemIdToHousingItemId( housingPreset->exteriorDoor ) );

  getHouse()->setHouseInteriorPart( Common::HousingInteriorSlot::InteriorWall, convertItemIdToHousingItemId( housingPreset->interiorWall ) );
  getHouse()->setHouseInteriorPart( Common::HousingInteriorSlot::InteriorFloor, convertItemIdToHousingItemId( housingPreset->interiorFlooring ) );
  getHouse()->setHouseInteriorPart( Common::HousingInteriorSlot::InteriorLight, convertItemIdToHousingItemId( housingPreset->interiorLighting ) );
  getHouse()->setHouseInteriorPart( Common::HousingInteriorSlot::InteriorWall_Attic, convertItemIdToHousingItemId( housingPreset->otherFloorWall ) );
  getHouse()->setHouseInteriorPart( Common::HousingInteriorSlot::InteriorFloor_Attic, convertItemIdToHousingItemId( housingPreset->otherFloorFlooring ) );
  getHouse()->setHouseInteriorPart( Common::HousingInteriorSlot::InteriorLight_Attic, convertItemIdToHousingItemId( housingPreset->otherFloorLighting ) );
  getHouse()->setHouseInteriorPart( Common::HousingInteriorSlot::InteriorWall_Basement, convertItemIdToHousingItemId( housingPreset->basementWall ) );
  getHouse()->setHouseInteriorPart( Common::HousingInteriorSlot::InteriorFloor_Basement, convertItemIdToHousingItemId( housingPreset->basementFlooring ) );
  getHouse()->setHouseInteriorPart( Common::HousingInteriorSlot::InteriorLight_Basement, convertItemIdToHousingItemId( housingPreset->basementLighting ) );
  getHouse()->setHouseInteriorPart( Common::HousingInteriorSlot::InteriorLight_Mansion, convertItemIdToHousingItemId( housingPreset->mansionLighting ) );


  return true;
}

Sapphire::ItemContainerPtr Sapphire::Land::getItemContainer( uint16_t inventoryType ) const
{
  auto container = m_landInventoryMap.find( inventoryType );
  if( container == m_landInventoryMap.end() )
    return nullptr;

  return container->second;
}