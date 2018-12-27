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
                              const std::string& contentName );

    virtual ~HousingInteriorTerritory();

    bool init() override;

    void onPlayerZoneIn( Entity::Player& player ) override;
    void onUpdate( uint32_t currTime ) override;

    uint32_t getLastActivityTime() const;

    const Common::LandIdent getLandIdent() const;

    void updateHousingObjects();
    void spawnHousingObject( uint8_t containerIdx, uint16_t slot, uint16_t containerType,
                             Inventory::HousingItemPtr item );
    void updateHousingObjectPosition( uint16_t slot, Common::FFXIVARR_POSITION3_U16 pos, uint16_t rot );

  private:
    Common::LandIdent m_landIdent;
    uint32_t m_lastActivityTime;

    std::array< Sapphire::Common::HousingObject, 400 > m_housingObjects;
  };
}