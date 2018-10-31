#ifndef SAPPHIRE_HOUSINGZONE_H
#define SAPPHIRE_HOUSINGZONE_H

#include "Zone.h"
#include "Forwards.h"

namespace Core
{
  class HousingZone : public Zone
  {
  public:
    HousingZone( uint8_t wardNum,
                 uint16_t territoryId,
                 uint32_t guId,
                 const std::string& internalName,
                 const std::string& contentName );

    virtual ~HousingZone();

    bool init() override;

    void onPlayerZoneIn( Entity::Player& player ) override;
    void onUpdate( uint32_t currTime ) override;

    void sendMap( Entity::Player& player );
    bool isPlayerSubInstance( Entity::Player& player );

    /* returns current ward number for this zone */
    uint8_t getWardNum() const;
    Core::LandsetPtr getLandset( uint8_t id );

    const uint32_t m_wardMaxNum = 18;
  private:
    using LandsetPtrMap = std::unordered_map< uint8_t, Core::LandsetPtr >;
    LandsetPtrMap m_landsetPtrMap;
    uint8_t m_wardNum;
    uint32_t m_zoneId;
  };

}
#endif //SAPPHIRE_HOUSINGZONE_H