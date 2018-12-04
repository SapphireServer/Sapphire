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

#include "Forwards.h"
#include "Land.h"
#include "Framework.h"
#include "House.h"

extern Sapphire::Framework g_fw;

using namespace Sapphire::Common;

Sapphire::Land::Land( uint16_t territoryTypeId, uint8_t wardNum, uint8_t landId, uint32_t landSetId,
                  Sapphire::Data::HousingLandSetPtr info ) :
  m_territoryTypeId( territoryTypeId ),
  m_wardNum( wardNum ),
  m_landId( landId ),
  m_currentPrice( 0 ),
  m_minPrice( 0 ),
  m_nextDrop( static_cast< uint32_t >( Util::getTimeSeconds() ) + 21600 ),
  m_ownerPlayerId( 0 ),
  m_landSetId( landSetId ),
  m_landInfo( info ),
  m_type( Common::LandType::none ),
  m_fcIcon( 0 ),
  m_fcIconColor( 0 ),
  m_fcId( 0 ),
  m_iconAddIcon( 0 )
{
  memset( &m_tag, 0x00, 3 );

  init();
}

Sapphire::Land::~Land()
{

}

void Sapphire::Land::init()
{
  auto pDb = g_fw.get< Db::DbWorkerPool< Db::ZoneDbConnection > >();
  auto res = pDb->query( "SELECT * FROM land WHERE LandSetId = " + std::to_string( m_landSetId ) + " "
                                            "AND LandId = " + std::to_string( m_landId ) );
  if( !res->next() )
  {
    pDb->directExecute( "INSERT INTO land ( landsetid, landid, type, size, status, landprice, UpdateTime, OwnerId, HouseId ) "
                        "VALUES ( " + std::to_string( m_landSetId ) + "," + std::to_string( m_landId ) + ","
                        + std::to_string( static_cast< uint8_t >( m_type ) ) + ","
                        + std::to_string( m_landInfo->plotSize[ m_landId ] ) + ","
                        + " 1, " + std::to_string( m_landInfo->initialPrice[ m_landId ] ) + ", 0, 0, 0 );" );

    m_currentPrice = m_landInfo->initialPrice[ m_landId ];
    m_minPrice = m_landInfo->minPrice[ m_landId ];
    m_size = m_landInfo->plotSize[ m_landId ];
    m_state = HouseState::forSale;
  }
  else
  {
    m_type = static_cast< Common::LandType >( res->getUInt( "Type" ) );
    m_size = res->getUInt( "Size" );
    m_state = res->getUInt( "Status" );
    m_currentPrice = res->getUInt( "LandPrice" );
    m_ownerPlayerId = res->getUInt( "OwnerId" );
    m_minPrice = m_landInfo->minPrice[ m_landId ];
    m_maxPrice = m_landInfo->initialPrice[ m_landId ];

    auto houseId = res->getUInt( "HouseId" );

    // fetch the house if we have one for this land
    if( houseId > 0 )
      m_pHouse = make_House( houseId, m_landSetId, m_landId, m_wardNum, m_territoryTypeId );

  }

  auto pExdData = g_fw.get< Data::ExdDataGenerated >();
  auto info = pExdData->get< Sapphire::Data::HousingMapMarkerInfo >( getTerritoryTypeId(), getLandId() );
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
  auto setupContainer = [ this ]( InventoryType type, uint8_t maxSize )
  {
    m_landInventoryMap[ type ] = make_ItemContainer( type, maxSize, "houseiteminventory", true, true );
  };

  setupContainer( InventoryType::HousingExternalAppearance, 8 );
  setupContainer( InventoryType::HousingInternalAppearance, 8 );
  setupContainer( InventoryType::HousingOutdoorItemStoreroom, m_maxPlacedExternalItems );
  setupContainer( InventoryType::HousingIndoorItemStoreroom, m_maxPlacedInternalItems );
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

uint8_t Sapphire::Land::getWardNum() const
{
  return m_wardNum;
}

uint8_t Sapphire::Land::getLandId() const
{
  return m_landId;
}

uint16_t Sapphire::Land::getTerritoryTypeId() const
{
  return m_territoryTypeId;
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
void Sapphire::Land::setPlayerOwner( uint32_t id )
{
  m_ownerPlayerId = id;
}

uint32_t Sapphire::Land::getPlayerOwner()
{
  return m_ownerPlayerId;
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
  + ", OwnerId = " + std::to_string( getPlayerOwner() )
  + ", HouseId = " + std::to_string( houseId )
  + ", Type = " + std::to_string( static_cast< uint32_t >( m_type ) ) //TODO: add house id
  + " WHERE LandSetId = " + std::to_string( m_landSetId )
  + " AND LandId = " + std::to_string( m_landId ) + ";" );

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
    m_pHouse = make_House( newId, getLandSetId(), getLandId(), getWardNum(), getTerritoryTypeId() );
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
