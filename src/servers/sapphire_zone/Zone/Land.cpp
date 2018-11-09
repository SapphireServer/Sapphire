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

extern Core::Framework g_fw;

using namespace Core::Common;

Core::Land::Land( uint16_t zoneId, uint8_t wardNum, uint8_t landId, uint32_t landSetId,
                  Core::Data::HousingLandSetPtr info ) :
  m_zoneId( zoneId ),
  m_wardNum( wardNum ),
  m_landId( landId ),
  m_currentPrice( 0 ),
  m_minPrice( 0 ),
  m_nextDrop( 0 ),
  m_landSetId( landSetId ),
  m_landInfo( info )
{
  memset( &m_land, 0x00, sizeof( LandStruct ) );
  load();
}

Core::Land::~Land()
{

}

void Core::Land::load()
{
  m_land.houseState = HouseState::forSale;

  auto pDb = g_fw.get< Db::DbWorkerPool< Db::ZoneDbConnection > >();
  auto res = pDb->query( "SELECT * FROM land WHERE landsetid = " + std::to_string( m_landSetId ) + " "
                                            "AND landid = " + std::to_string( m_landId ) );
  if( !res->next() )
  {
    pDb->directExecute( "INSERT INTO land ( landsetid, landid, size, status, landprice ) "
                        "VALUES ( " + std::to_string( m_landSetId ) + "," + std::to_string( m_landId ) + ","
                        + std::to_string( m_landInfo->sizes[ m_landId ] ) + ","
                        + " 1, " + std::to_string( m_landInfo->prices[ m_landId ] ) + " );" );

    m_currentPrice = m_landInfo->prices[ m_landId ];
    m_minPrice = m_landInfo->minPrices[ m_landId ];
    m_land.houseSize = m_landInfo->sizes[ m_landId ];
  }
  else
  {
    m_land.houseSize = res->getUInt( "size" );
    m_land.houseState = res->getUInt( "status" );
    m_currentPrice = res->getUInt( "LandPrice" );;
  }
  init();
//  setPreset( 262145 );
/*  auto pDb = g_fw.get< Db::DbWorkerPool< Db::ZoneDbConnection > >();
  auto res = pDb->query( "SELECT * FROM land WHERE Id = " + std::to_string( m_landKey ) );
  if( !res->next() )
  {
    setHouseSize( HouseSizeType::smallHouse );//ToDo: get house site from ExD (Landset first 60 rows)
    m_currentPrice = m_initPrice;
    m_land.color[ 7 ] = 0xFF;
    m_ownerPlayerId = 0;
    m_nextDrop = 0;
    setState( HouseStateType::forSell );
    auto stmt = pDb->getPreparedStatement( Db::ZoneDbStatements::LAND_INS );
    stmt->setUInt( 1, m_landKey );
    pDb->directExecute( stmt );
    Init();
  }
  else
  {
    Init();
    if( getState() == HouseStateType::privateHouse || getState() == HouseStateType::sold )
    {
      m_ownerPlayerId = res->getUInt( "ownerPlayerId" );
    }
    else if( getState() == HouseStateType::forSell )
    {
      m_currentPrice = res->getUInt( "currentPrice" );
      m_nextDrop = res->getUInt( "nextDrop" );
      m_ownerPlayerId = 0;
    }
  }
  ItemsOutdoorContainer = make_ItemContainer( InventoryType::HousingOutdoorItems,
                                              m_maxItems,
                                              "housingoutdooritems", true );*/
}

uint16_t Core::Land::convertItemIdToHousingItemId( uint16_t itemId )
{
  auto pExdData = g_fw.get< Data::ExdDataGenerated >();
  auto info = pExdData->get< Core::Data::Item >( itemId );
  return info->additionalData;
}

uint32_t Core::Land::getCurrentPrice() const
{
  return m_currentPrice;
}

void Core::Land::setPreset( uint32_t id )
{
  auto pExdData = g_fw.get< Data::ExdDataGenerated >();
  auto info = pExdData->get< Core::Data::HousingPreset >( convertItemIdToHousingItemId( id ) );
  setHousePart( Common::HousePartSlot::ExteriorRoof, info->exteriorRoof );
  setHousePart( Common::HousePartSlot::ExteriorWall, info->exteriorWall );
  setHousePart( Common::HousePartSlot::ExteriorWindow, info->exteriorWindow );
  setHousePart( Common::HousePartSlot::BasementWall, info->basementWall );
  setHousePart( Common::HousePartSlot::OtherFloorFlooring, info->otherFloorFlooring );
  setHousePart( Common::HousePartSlot::OtherFloorWall, info->otherFloorWall );
}

//Primary State
void Core::Land::setHouseSize( uint8_t size )
{
  m_land.houseSize = size;
}

void Core::Land::setState( uint8_t state )
{
  m_land.houseState = state;
}

void Core::Land::setOwnership( uint8_t state )
{
  m_land.iconColor = state;
}

void Core::Land::setSharing( uint8_t state )
{
  m_land.iconAddIcon = state;
}

uint8_t Core::Land::getHouseSize()
{
  return m_land.houseSize;
}

uint8_t Core::Land::getState()
{
  return m_land.houseState;
}

uint8_t Core::Land::getOwnership()
{
  return m_land.iconColor;
}

uint8_t Core::Land::getSharing()
{
  return m_land.iconAddIcon;
}

//Free Comapny
void Core::Land::setFreeCompany( uint32_t id, uint32_t icon, uint32_t color )
{
  m_land.fcId = id;
  m_land.fcIcon = icon;
  m_land.fcIconColor = color; //RGBA
}

uint32_t Core::Land::getFcId()
{
  return m_land.fcIcon;
}

uint32_t Core::Land::getFcIcon()
{
  return m_land.fcIcon;
}

uint32_t Core::Land::getFcColor()
{
  return m_land.fcIconColor;
}

//House Data
void Core::Land::setHousePart( Common::HousePartSlot slot, uint16_t id )
{
  m_land.housePart[ slot ] = convertItemIdToHousingItemId( id );
}

uint16_t Core::Land::getHousePart( Common::HousePartSlot slot )
{
  return m_land.housePart[ slot ];
}

//Color
void Core::Land::setColor( uint8_t slot, uint8_t color )
{
  m_land.color[ slot ] = color;
}

uint8_t Core::Land::getColor( uint8_t slot )
{
  return m_land.color[ slot ];
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

const LandStruct& Core::Land::getLand()
{
  return m_land;
}

uint32_t Core::Land::getMaxItems()
{
  return m_maxItems;
}

uint32_t Core::Land::getDevaluationTime()
{
  return m_nextDrop - Util::getTimeSeconds();
}

void Core::Land::init()
{

  switch( getHouseSize() )
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

void Core::Land::UpdateDatabase()
{
  /*auto pDb = g_fw.get< Db::DbWorkerPool< Db::ZoneDbConnection > >();
  std::string exec = "UPDATE land SET landset='" +
                     std::string( reinterpret_cast< const char* >( &m_land ) ) + "', nextDrop=" +
                     std::to_string( m_nextDrop ) + ", currentPrice=" +
                     std::to_string( m_currentPrice ) +
                     " WHERE Id =" + std::to_string( m_landKey );
  pDb->execute( exec );*/
}

void Core::Land::Update( uint32_t currTime )
{
  if( getState() == HouseState::forSale )
  {
    if( m_nextDrop < currTime && m_minPrice < m_currentPrice )
    {
      m_nextDrop = currTime + 21600;
      m_currentPrice = ( m_currentPrice / 100 ) * 99.58;
    }
    UpdateDatabase();
  }
}