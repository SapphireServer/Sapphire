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
#include "Landset.h"
#include "Framework.h"

extern Core::Framework g_fw;

using namespace Core::Common;

Core::Landset::Landset( uint16_t zoneId, uint8_t wardNum, uint8_t landsetId ) :
  m_zoneId( zoneId ),
  m_wardNum( wardNum ),
  m_landsetId( landsetId ),
  m_currentPrice( 0 ),
  m_nextDrop( 0 )
{
  m_landsetKey = ( m_zoneId << 16 ) | ( m_wardNum << 8 ) | m_landsetId;
  memset( &m_landset, 0x00, sizeof( LandsetStruct ) );
  load();
}

Core::Landset::~Landset()
{

}

void Core::Landset::load()
{
  auto pDb = g_fw.get< Db::DbWorkerPool< Db::ZoneDbConnection > >();
  auto res = pDb->query( "SELECT * FROM landset WHERE Id = " + std::to_string( m_landsetKey ) );
  if( !res->next() )
  {
    setHouseSize( HouseSizeType::smallHouse );//ToDo: get house site from ExD (Landset first 60 rows)
    m_currentPrice = m_initPrice;
    m_landset.color[ 7 ] = 0xFF;
    m_ownerPlayerId = 0;
    m_nextDrop = 0;
    setState( HouseStateType::forSell );
    auto stmt = pDb->getPreparedStatement( Db::ZoneDbStatements::LAND_INS );
    stmt->setUInt( 1, m_landsetKey );
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
                                              "housingoutdooritems", true );
}

uint32_t Core::Landset::convertItemIdToHousingItemId( uint32_t itemId )
{
  auto pExdData = g_fw.get< Data::ExdDataGenerated >();
  auto info = pExdData->get< Core::Data::Item >( itemId );
  return info->additionalData;
}

void Core::Landset::setPreset( uint32_t id )
{
  auto pExdData = g_fw.get< Data::ExdDataGenerated >();
  auto info = pExdData->get< Core::Data::HousingPreset >( convertItemIdToHousingItemId( id ) );
  setRoof( info->exteriorRoof );
  setWall( info->exteriorWall );
  setWindow( info->exteriorWindow );
  setBasementWall( info->basementWall );
  setFloorFlooring( info->otherFloorFlooring );
  setFloorWall( info->otherFloorWall );
}

//Primary State
void Core::Landset::setHouseSize( uint8_t size )
{
  m_landset.houseSize = size;
}

void Core::Landset::setState( uint8_t state )
{
  m_landset.houseState = state;
}

void Core::Landset::setOwnership( uint8_t state )
{
  m_landset.iconColor = state;
}

void Core::Landset::setSharing( uint8_t state )
{
  m_landset.iconAddIcon = state;
}

uint8_t Core::Landset::getHouseSize()
{
  return m_landset.houseSize;
}

uint8_t Core::Landset::getState()
{
  return m_landset.houseState;
}

uint8_t Core::Landset::getOwnership()
{
  return m_landset.iconColor;
}

uint8_t Core::Landset::getSharing()
{
  return m_landset.iconAddIcon;
}

//Free Comapny
void Core::Landset::setFreeCompany( uint32_t id, uint32_t icon, uint32_t color )
{
  m_landset.fcId = id;
  m_landset.fcIcon = icon;
  m_landset.fcIconColor = color; //RGBA
}

uint32_t Core::Landset::getFcId()
{
  return m_landset.fcIcon;
}

uint32_t Core::Landset::getFcIcon()
{
  return m_landset.fcIcon;
}

uint32_t Core::Landset::getFcColor()
{
  return m_landset.fcIconColor;
}

//House Data
void Core::Landset::setRoof( uint16_t id )
{
  m_landset.exteriorRoof = convertItemIdToHousingItemId( id );
}

void Core::Landset::setFacade( uint16_t id )
{
  m_landset.exteriorWall = convertItemIdToHousingItemId( id );
}

void Core::Landset::setWindow( uint16_t id )
{
  m_landset.exteriorWindow = convertItemIdToHousingItemId( id );
}

void Core::Landset::setDoor( uint16_t id )
{
  m_landset.exteriorDoor = convertItemIdToHousingItemId( id );
}

void Core::Landset::setFloorWall( uint16_t id )
{
  m_landset.otherFloorWall = convertItemIdToHousingItemId( id );
}

void Core::Landset::setFloorFlooring( uint16_t id )
{
  m_landset.otherFloorFlooring = convertItemIdToHousingItemId( id );
}

void Core::Landset::setWall( uint16_t id )
{
  m_landset.exteriorWall = convertItemIdToHousingItemId( id );
}

void Core::Landset::setSign( uint16_t id )
{
  m_landset.gardenSign = convertItemIdToHousingItemId( id );
}

void Core::Landset::setBasementWall( uint16_t id )
{
  m_landset.basementWall = convertItemIdToHousingItemId( id );
}

uint16_t Core::Landset::getRoof()
{
  return m_landset.exteriorRoof;
}

uint16_t Core::Landset::getFacade()
{
  return m_landset.exteriorWall;
}

uint16_t Core::Landset::getWindow()
{
  return m_landset.exteriorWindow;
}

uint16_t Core::Landset::getDoor()
{
  return m_landset.exteriorDoor;
}

uint16_t Core::Landset::getSign()
{
  return m_landset.gardenSign;
}

uint16_t Core::Landset::getWall()
{
  return m_landset.basementWall;
}

uint16_t Core::Landset::getFloorWall()
{
  return m_landset.otherFloorFlooring;
}

uint16_t Core::Landset::getFloorFlooring()
{
  return m_landset.otherFloorFlooring;
}

uint16_t Core::Landset::getBasememtWall()
{
  return m_landset.basementWall;
}

//Color
void Core::Landset::setColor( uint8_t slot, uint8_t color )
{
  m_landset.color[ slot ] = color;
}

uint8_t Core::Landset::getColor( uint8_t slot )
{
  return m_landset.color[ slot ];
}

//Player
void Core::Landset::setPlayerOwner( uint32_t id )
{
  m_ownerPlayerId = id;
}

uint32_t Core::Landset::getPlayerOwner()
{
  return m_ownerPlayerId;
}

uint32_t Core::Landset::getLandsetKey()
{
  return m_landsetKey;
}

LandsetStruct Core::Landset::getLandset()
{
  return m_landset;
}

uint32_t Core::Landset::getMaxItems()
{
  return m_maxItems;
}

void Core::Landset::Init()
{


  switch( getHouseSize() )
  {
    case HouseSizeType::smallHouse:
      m_initPrice = 3750000;
      m_maxItems = 20;
      break;
    case HouseSizeType::mediumHouse:
      m_initPrice = 20000000;
      m_maxItems = 30;
      break;
    case HouseSizeType::bigHouse:
      m_initPrice = 50000000;
      m_maxItems = 40;
      break;
    default:
      break;
  }
}

void Core::Landset::UpdateDatabase()
{
  auto pDb = g_fw.get< Db::DbWorkerPool< Db::ZoneDbConnection > >();
  std::string exec = "UPDATE land SET landset='" +
                     std::string( reinterpret_cast< const char* >( &m_landset ) ) + "', nextDrop=" +
                     std::to_string( m_nextDrop ) + ", currentPrice=" +
                     std::to_string( m_currentPrice ) +
                     " WHERE Id =" + std::to_string( m_landsetKey );
  pDb->execute( exec );
}

void Core::Landset::Update( uint32_t currTime )
{
  if( m_currentPrice == 0 && getState() == HouseStateType::forSell )
  {
    m_currentPrice = m_initPrice;
    m_nextDrop = 0;
    UpdateDatabase();
  }
  if( m_nextDrop < currTime  && getState() == HouseStateType::forSell )
  {
    m_currentPrice = ( m_currentPrice / 100 ) * 90;
    m_nextDrop = currTime + 86400;
    UpdateDatabase();
  }
  onUpdate();
}

void Core::Landset::onUpdate()
{

}