#ifndef SAPPHIRE_HOUSINGZONE_H
#define SAPPHIRE_HOUSINGZONE_H

#include "Zone.h"
#include "Forwards.h"

namespace Core {
class HousingZone :
  public Zone
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

  /* returns current ward number for this zone */
  uint8_t getWardNum() const;

  const uint32_t m_wardMaxNum = 18;
private:
  uint8_t m_wardNum;
};

}
#endif //SAPPHIRE_HOUSINGZONE_H
