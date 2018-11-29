#ifndef SAPPHIRE_HOUSINGZONE_H
#define SAPPHIRE_HOUSINGZONE_H

#include "Zone.h"
#include "Forwards.h"

namespace Sapphire
{
  enum class LandPurchaseResult
  {
    SUCCESS,
    ERR_NOT_ENOUGH_GIL,
    ERR_NOT_AVAILABLE,
    ERR_NO_MORE_LANDS_FOR_CHAR,
    ERR_INTERNAL,
  };

  enum class LandPurchaseMode
  {
    FC = 1,
    PRIVATE = 2,
    RELOCATE = 4,
  };

  class HousingZone : public Zone
  {
  public:
    HousingZone( uint8_t landSetId,
                 uint16_t territoryTypeId,
                 uint32_t guId,
                 const std::string& internalName,
                 const std::string& contentName );

    virtual ~HousingZone();

    bool init() override;

    void onPlayerZoneIn( Entity::Player& player ) override;
    void onUpdate( uint32_t currTime ) override;

    void sendLandSet( Entity::Player& player );
    void sendLandUpdate( uint8_t landId );
    bool isPlayerSubInstance( Entity::Player& player );

    /* returns current ward number for this zone */
    uint8_t getWardNum() const;

    uint32_t getLandSetId() const;
    Sapphire::LandPtr getLand( uint8_t id );

  private:
    using LandPtrMap = std::unordered_map< uint8_t, Sapphire::LandPtr >;
    const uint32_t m_landSetMax = 18;
    LandPtrMap m_landPtrMap;
    uint8_t m_wardNum;
    uint32_t m_landSetId;
    uint32_t m_zoneId;
  };

}
#endif //SAPPHIRE_HOUSINGZONE_H
