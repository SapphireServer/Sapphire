#ifndef SAPPHIRE_HOUSE_H
#define SAPPHIRE_HOUSE_H

#include "Forwards.h"
#include <Common.h>
#include <set>
#include <unordered_map>

namespace Core
{

  class House
  {

  public:
    House( uint32_t houseId, uint32_t landSetId, uint8_t landId, uint8_t wardNum, uint16_t zoneId );
    virtual ~House();

    //gerneral
    uint32_t getLandSetId();
    uint8_t getLandId();
    uint8_t getWardNum();
    uint16_t getZoneId();
    uint32_t getHouseId();

    //functions
    void setHousePart( Common::HousePartSlot slot, uint32_t id );
    void setHousePartColor( Common::HousePartSlot slot, uint32_t id );
    uint32_t getHousePart( Common::HousePartSlot slot );
    uint8_t getHousePartColor( Common::HousePartSlot slot );

  private:
    uint32_t m_landSetId;
    uint8_t m_landId;
    uint8_t m_wardNum;
    uint16_t m_zoneId;
    uint32_t m_houseId;

    uint32_t m_houseParts[8];
    uint8_t m_housePartsColor[8];

    char m_HouseMsg[193];
  };

}

#endif // SAPPHIRE_HOUSE_H
