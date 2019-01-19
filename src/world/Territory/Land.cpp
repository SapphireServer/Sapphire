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

#include "Manager/ItemMgr.h"

#include "Forwards.h"
#include "Land.h"
#include "Framework.h"
#include "House.h"

using namespace Sapphire::Common;

Sapphire::Land::Land( uint16_t territoryTypeId, uint8_t wardNum, uint8_t landId, uint32_t landSetId,
                      Sapphire::Data::HousingLandSetPtr info, FrameworkPtr pFw ) :
  m_currentPrice( 0 ),
  m_minPrice( 0 ),
  m_nextDrop( Util::getTimeSeconds() + 21600 ),
  m_ownerId( 0 ),
  m_landSetId( landSetId ),
  m_landInfo( info ),
  m_type( Common::LandType::none ),
  m_fcIcon( 0 ),
  m_fcIconColor( 0 ),
  m_fcId( 0 ),
  m_iconAddIcon( 0 ),
  m_pFw( pFw )
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

void Sapphire::Land::init( Common::LandType type, Common::HouseSize size, Common::HouseStatus state, uint32_t currentPrice,
                           uint64_t ownerId, uint64_t houseId )
{
  m_type = type;
  m_size = size;
  m_state = state;
  m_currentPrice = currentPrice;
  m_ownerId = ownerId;

  auto pExdData = m_pFw->get< Data::ExdDataGenerated >();
  auto info = pExdData->get< Sapphire::Data::HousingMapMarkerInfo >( m_landIdent.territoryTypeId, m_landIdent.landId );
  if( info )
  {
    m_mapMarkerPosition.x = info->x;
    m_mapMarkerPosition.y = info->y;
    m_mapMarkerPosition.z = info->z;
  }
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
void Sapphire::Land::setSize( Common::HouseSize size )
{
  m_size = size;
}

void Sapphire::Land::setStatus( Common::HouseStatus state )
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

Sapphire::Common::HouseSize Sapphire::Land::getSize() const
{
  return m_size;
}

Sapphire::Common::HouseStatus Sapphire::Land::getStatus() const
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

void Sapphire::Land::setHouse( Sapphire::HousePtr house )
{
  m_pHouse = house;
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
  return m_nextDrop - Util::getTimeSeconds();
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
    houseId = getHouse()->getId();

  // todo: change to prepared statement
  auto pDb = m_pFw->get< Db::DbWorkerPool< Db::ZoneDbConnection > >();
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
  if( getStatus() == HouseStatus::ForSale )
  {
    if( m_nextDrop < currTime && m_minPrice < m_currentPrice )
    {
      m_nextDrop = currTime + 21600;
      m_currentPrice = static_cast< uint32_t >( ( m_currentPrice / 100 ) * 99.58f );
      updateLandDb();
    }
  }
}

Sapphire::Land::InvMaxItemsPair Sapphire::Land::getInventoryItemMax() const
{
  return std::make_pair( m_maxPlacedExternalItems, m_maxPlacedInternalItems );
}