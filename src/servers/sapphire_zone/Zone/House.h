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
    House( uint32_t houseId, uint32_t landSetId, uint8_t landId, uint8_t wardNum, uint16_t territoryTypeId );
    virtual ~House();

    using HousePart = std::tuple< uint32_t, uint8_t >;
    using HousePartsArray = std::array< HousePart, 8 >;

    //gerneral
    uint32_t getLandSetId() const;
    uint8_t getLandId() const;
    uint8_t getWardNum() const;
    uint16_t getTerritoryTypeId() const;
    uint32_t getHouseId() const;

    //functions
    void setHousePart( Common::HousePartSlot slot, uint32_t id );
    void setHousePartColor( Common::HousePartSlot slot, uint32_t id );
    uint32_t getHousePart( Common::HousePartSlot slot ) const;
    uint8_t getHousePartColor( Common::HousePartSlot slot ) const;

    HousePartsArray const& getHouseParts() const;

  private:
    uint32_t m_landSetId;
    uint8_t m_landId;
    uint8_t m_wardNum;
    uint16_t m_territoryTypeId;
    uint32_t m_houseId;

    HousePartsArray m_houseParts;

    char m_commentMsg[ 193 ];
  };

}

#endif // SAPPHIRE_HOUSE_H
