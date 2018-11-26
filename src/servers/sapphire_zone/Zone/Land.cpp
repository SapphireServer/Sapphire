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

extern Core::Framework g_fw;

using namespace Core::Common;

Core::Land::Land( uint16_t territoryTypeId, uint8_t wardNum, uint8_t landId, uint32_t landSetId,
                  Core::Data::HousingLandSetPtr info ) :
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

  load();
}

Core::Land::~Land()
{

}

void Core::Land::load()
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
  }
  init();
}

uint32_t Core::Land::convertItemIdToHousingItemId( uint32_t itemId )
{
  auto pExdData = g_fw.get< Data::ExdDataGenerated >();
  auto info = pExdData->get< Core::Data::Item >( itemId );
  return info->additionalData;
}

uint32_t Core::Land::getCurrentPrice() const
{
  return m_currentPrice;
}

uint32_t Core::Land::getMaxPrice() const
{
  return m_maxPrice;
}

//Primary State
void Core::Land::setSize( uint8_t size )
{
  m_size = size;
}

void Core::Land::setState( uint8_t state )
{
  m_state = state;
}

void Core::Land::setSharing( uint8_t state )
{
  m_iconAddIcon = state;
}

void Core::Land::setLandType( Common::LandType type )
{
  m_type = type;
}

uint8_t Core::Land::getSize() const
{
  return m_size;
}

uint8_t Core::Land::getState() const
{
  return m_state;
}

uint8_t Core::Land::getSharing() const
{
  return m_iconAddIcon;
}

uint32_t Core::Land::getLandSetId() const
{
  return m_landSetId;
}

uint8_t Core::Land::getWardNum() const
{
  return m_wardNum;
}

uint8_t Core::Land::getLandId() const
{
  return m_landId;
}

uint16_t Core::Land::getTerritoryTypeId() const
{
  return m_territoryTypeId;
}

Core::HousePtr Core::Land::getHouse() const
{
  return m_pHouse;
}

Core::Common::LandType Core::Land::getLandType() const
{
  return m_type;
}

//Free Comapny
void Core::Land::setFreeCompany( uint32_t id, uint32_t icon, uint32_t color )
{
  m_fcId = id;
  m_fcIcon = icon;
  m_fcIconColor = color; //RGBA
}

uint32_t Core::Land::getFcId()
{
  return m_fcIcon;
}

uint32_t Core::Land::getFcIcon()
{
  return m_fcIcon;
}

uint32_t Core::Land::getFcColor()
{
  return m_fcIconColor;
}

//Player
void Core::Land::setPlayerOwner( uint32_t id )
{
  m_ownerPlayerId = id;
}

uint32_t Core::Land::getPlayerOwner()
{
  return m_ownerPlayerId;
}

uint32_t Core::Land::getMaxItems()
{
  return m_maxItems;
}

uint32_t Core::Land::getDevaluationTime()
{
  return m_nextDrop - static_cast< uint32_t >( Util::getTimeSeconds() );
}

void Core::Land::setCurrentPrice( uint32_t currentPrice )
{
  m_currentPrice = currentPrice;
}

void Core::Land::setLandTag( uint8_t slot, uint8_t tag )
{
  m_tag[ slot ] = tag;
}

uint8_t Core::Land::getLandTag( uint8_t slot )
{
  return m_tag[ slot ];
}

void Core::Land::init()
{

  switch( m_size )
  {
    case HouseSize::small:
      m_maxItems = 20;
      break;
    case HouseSize::medium:
      m_maxItems = 30;
      break;
    case HouseSize::big:
      m_maxItems = 40;
      break;
    default:
      break;
  }
}

void Core::Land::updateLandDb()
{
  uint32_t houseId = 0;

  if( getHouse() )
    houseId = getHouse()->getHouseId();

  auto pDb = g_fw.get< Db::DbWorkerPool< Db::ZoneDbConnection > >();
  pDb->directExecute( "UPDATE land SET status = " + std::to_string( m_state )
  + ", LandPrice = " + std::to_string( getCurrentPrice() )
  + ", UpdateTime = " + std::to_string( getDevaluationTime() )
  + ", OwnerId = " + std::to_string( getPlayerOwner() )
  + ", HouseId = " + std::to_string( houseId )
  + ", Type = " + std::to_string( static_cast< uint32_t >( m_type ) ) //TODO: add house id
  + " WHERE LandSetId = " + std::to_string( m_landSetId )
  + " AND LandId = " + std::to_string( m_landId ) + ";" );
}

void Core::Land::update( uint32_t currTime )
{
  if( getState() == HouseState::forSale )
  {
    if( m_nextDrop < currTime && m_minPrice < m_currentPrice )
    {
      m_nextDrop = currTime + 21600;
      m_currentPrice = ( m_currentPrice / 100 ) * 99.58;
      updateLandDb();
    }
  }
}

uint32_t Core::Land::getNextHouseId()
{
  auto pDb = g_fw.get< Db::DbWorkerPool< Db::ZoneDbConnection > >();
  auto pQR = pDb->query( "SELECT MAX( HouseId ) FROM house" );

  if( !pQR->next() )
    return 0;

  return pQR->getUInt( 1 ) + 1;
}

bool Core::Land::setPreset( uint32_t itemId )
{
  auto housingItemId = convertItemIdToHousingItemId( itemId );

  auto exdData = g_fw.get< Core::Data::ExdDataGenerated >();
  if( !exdData )
    return false;

  auto housingPreset = exdData->get< Core::Data::HousingPreset >( housingItemId );
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

  return true;
}
