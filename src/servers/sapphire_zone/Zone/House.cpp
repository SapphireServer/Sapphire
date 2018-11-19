#include <set>
#include <string.h>

#include <Logging/Logger.h>
#include <Exd/ExdDataGenerated.h>

#include "House.h"

#include <unordered_map>
#include "Framework.h"

extern Core::Framework g_fw;

Core::House::House( uint32_t houseId, uint32_t landSetId, uint8_t landId, uint8_t wardNum, uint16_t zoneId ) :
  m_houseId( houseId ),
  m_landSetId( landSetId ),
  m_landId( landId ),
  m_wardNum( wardNum ),
  m_zoneId( zoneId )
{
  memset( &m_houseParts, 0x00, 8 );
  memset( &m_HouseMsg, 0x00, 193 );
}

Core::House::~House()
{

}

uint32_t Core::House::getLandSetId()
{
  return m_landSetId;
}

uint8_t Core::House::getLandId()
{
  return m_landId;
}

uint8_t Core::House::getWardNum()
{
  return m_wardNum;
}

uint32_t Core::House::getHouseId()
{
  return m_houseId;
}

uint8_t Core::House::getHousePartColor( Common::HousePartSlot slot )
{
  return m_housePartsColor[ slot ];
}

void Core::House::setHousePart( Common::HousePartSlot slot, uint32_t id )
{
  m_houseParts[ slot ] = id;
}

void Core::House::setHousePartColor( Common::HousePartSlot slot, uint32_t id )
{
  m_housePartsColor[ slot ] = id;
}

uint32_t Core::House::getHousePart( Common::HousePartSlot slot )
{
  return m_houseParts[ slot ];
}
