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
    House( uint32_t houseId, uint32_t landSetId, Common::LandIdent ident, const std::string& estateName,
           const std::string& estateComment, FrameworkPtr pFw );
    virtual ~House();

    using HousePart = std::pair< uint32_t, uint16_t >;
    using HouseModelsArray = std::array< HousePart, 8 >;

    //gerneral
    uint32_t getLandSetId() const;
    Common::LandIdent getLandIdent() const;
    uint32_t getId() const;

    const std::string& getHouseName() const;
    void setHouseName( const std::string& name );

    const std::string& getHouseGreeting() const;
    void setHouseGreeting( const std::string& greeting );

    //functions
    void setExteriorModel( Common::HouseExteriorSlot slot, uint32_t modelId, uint16_t stain );
    HousePart getExteriorModel( Common::HouseExteriorSlot slot );

    void setInteriorModel( Common::HouseInteriorSlot slot, uint32_t modelId );
    uint32_t getInteriorModel( Common::HouseInteriorSlot slot );

    HouseModelsArray const& getHouseModels() const;

    void updateHouseDb();

    void setHasAetheryte( bool hasAetheryte );
    bool getHasAetheryte() const;

  private:
    uint32_t m_landSetId;
    Common::LandIdent m_landIdent;
    uint32_t m_houseId;

    uint64_t m_buildTime;
    bool m_hasAetheryte;

    HouseModelsArray m_exteriorModelCache;
    uint32_t m_interiorModelCache[10];

    std::string m_estateComment;
    std::string m_estateName;
    FrameworkPtr m_pFw;
  };

}

#endif // SAPPHIRE_HOUSE_H
