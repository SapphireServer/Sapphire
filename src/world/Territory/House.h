#ifndef SAPPHIRE_HOUSE_H
#define SAPPHIRE_HOUSE_H

#include "Forwards.h"
#include <Common.h>
#include <set>
#include <unordered_map>

namespace Sapphire
{

  class House
  {
  public:
    House( uint32_t houseId, uint32_t landSetId, Common::LandIdent ident, FrameworkPtr pFw );
    virtual ~House();

    using HousePart = std::pair< uint32_t, uint8_t >;
    using HousePartsArray = std::array< HousePart, 8 >;

    //gerneral
    uint32_t getLandSetId() const;
    Common::LandIdent getLandIdent() const;
    uint32_t getHouseId() const;

    const std::string& getHouseName() const;
    void setHouseName( const std::string& name );

    const std::string& getHouseGreeting() const;
    void setHouseGreeting( const std::string& greeting );

    //functions
    void setHousePart( Common::HousePartSlot slot, uint32_t id );
    void setHousePartColor( Common::HousePartSlot slot, uint32_t id );
    void setHouseInteriorPart( Common::HousingInteriorSlot slot, uint32_t id );
    uint32_t getHousePart( Common::HousePartSlot slot ) const;
    uint8_t getHousePartColor( Common::HousePartSlot slot ) const;
    uint32_t getHouseInteriorPart( Common::HousingInteriorSlot slot ) const;

    HousePartsArray const& getHouseParts() const;

    void updateHouseDb();

  private:
    uint32_t m_landSetId;
    Common::LandIdent m_landIdent;
    uint32_t m_houseId;

    uint64_t m_buildTime;

    HousePartsArray m_houseParts;
    uint32_t m_houseInteriorParts[10];

    std::string m_estateMessage;
    std::string m_houseName;
    FrameworkPtr m_pFw;
  };

}

#endif // SAPPHIRE_HOUSE_H
