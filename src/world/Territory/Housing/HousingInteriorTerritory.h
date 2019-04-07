#include "ForwardsZone.h"
#include "Territory/Zone.h"
#include "Common.h"
#include <array>

namespace Sapphire::World::Territory::Housing
{
  class HousingInteriorTerritory : public Zone
  {
  public:
    HousingInteriorTerritory( Common::LandIdent ident, uint16_t territoryTypeId,
                              uint32_t guId,
                              const std::string& internalName,
                              const std::string& contentName,
                              FrameworkPtr pFw );

    virtual ~HousingInteriorTerritory();

    bool init() override;

    void onPlayerZoneIn( Entity::Player& player ) override;
    void onUpdate( uint64_t tickCount ) override;

    const Common::LandIdent getLandIdent() const;

    void updateHousingObjects();
    void spawnHousingObject( uint8_t containerIdx, uint16_t slot, uint16_t containerType,
                             Inventory::HousingItemPtr item );
    void updateHousingObjectPosition(
      Entity::Player& sourcePlayer, uint16_t slot, Sapphire::Common::FFXIVARR_POSITION3 pos, uint16_t rot );
    void removeHousingObject( uint16_t slot );

  private:
    Common::LandIdent m_landIdent;

    std::array< Sapphire::Common::HousingObject, 400 > m_housingObjects;
  };
}