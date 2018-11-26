#include <set>
#include <string.h>

#include <Logging/Logger.h>
#include <Exd/ExdDataGenerated.h>
#include <Database/DatabaseDef.h>

#include "House.h"

#include <unordered_map>
#include "Framework.h"

extern Core::Framework g_fw;

Core::House::House( uint32_t houseId, uint32_t landSetId, uint8_t landId, uint8_t wardNum, uint16_t territoryTypeId ) :
  m_houseId( houseId ),
  m_landSetId( landSetId ),
  m_landId( landId ),
  m_wardNum( wardNum ),
  m_territoryTypeId( territoryTypeId )
{
  memset( &m_houseParts, 0x00, sizeof( m_houseParts ) );
  memset( &m_commentMsg, 0x00, sizeof( m_commentMsg ) );

  auto pDB = g_fw.get< Db::DbWorkerPool< Db::ZoneDbConnection > >();
  auto res = pDB->query("SELECT * FROM house WHERE HouseId = " + std::to_string( houseId ) );

  if( !res->next() )
  {
    pDB->directExecute("INSERT INTO house ( LandSetId, HouseId ) VALUES ( " + std::to_string( m_landSetId ) + ", " + std::to_string( m_houseId ) + " )" );
  }
  else
  {
    // todo
  }
}

Core::House::~House()
{

}

uint32_t Core::House::getLandSetId() const
{
  return m_landSetId;
}

uint8_t Core::House::getLandId() const
{
  return m_landId;
}

uint8_t Core::House::getWardNum() const
{
  return m_wardNum;
}

uint16_t Core::House::getTerritoryTypeId() const
{
  return m_territoryTypeId;
}

uint32_t Core::House::getHouseId() const
{
  return m_houseId;
}

uint8_t Core::House::getHousePartColor( Common::HousePartSlot slot ) const
{
  return std::get< 1 >( m_houseParts[ slot ] );
}

void Core::House::setHousePart( Common::HousePartSlot slot, uint32_t id )
{
  std::get< 0 >( m_houseParts[ slot ] ) = id;
}

void Core::House::setHousePartColor( Common::HousePartSlot slot, uint32_t id )
{
  std::get< 1 >( m_houseParts[ slot ] ) = id;
}

uint32_t Core::House::getHousePart( Common::HousePartSlot slot ) const
{
  return std::get< 0 >( m_houseParts[ slot ] );
}

Core::House::HousePartsArray const& Core::House::getHouseParts() const
{
  return m_houseParts;
}