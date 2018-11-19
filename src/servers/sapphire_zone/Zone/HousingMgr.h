#ifndef SAPPHIRE_HOUSINGMGR_H
#define SAPPHIRE_HOUSINGMGR_H

#include "Forwards.h"
#include "HousingZone.h"
#include <set>
#include <unordered_map>

namespace Core
{
  namespace Data
  {
    using HousingZonePtr = std::shared_ptr< HousingZone >;
  }

  class HousingMgr
  {

  public:
    HousingMgr();
    virtual ~HousingMgr();

    bool init();

    uint32_t toLandSetId( uint16_t territoryTypeId, uint8_t wardId ) const;
    uint16_t getNextLandId();
    void insertHousingZone( Core::Data::HousingZonePtr hZone );
    Core::Data::HousingZonePtr getHousingZone( uint16_t id );
    Core::Data::HousingZonePtr getHousingZoneByLandSetId( uint32_t id );
    Core::LandPtr getLandByOwnerId( uint32_t id );

    void sendLandSignOwned( Entity::Player& player, uint8_t wardId, uint8_t plotId, uint16_t territoryTypeId );
    void sendLandSignFree( Entity::Player& player, uint8_t wardId, uint8_t plotId, uint16_t territoryTypeId );
    LandPurchaseResult purchaseLand( Entity::Player& player, uint8_t plot, uint8_t state );

    bool relinquishLand( Entity::Player& player, uint8_t plot );

  private:
    using HousingZonePtrMap = std::unordered_map< uint16_t, Core::Data::HousingZonePtr >;
    uint16_t m_lastLandId;
    HousingZonePtrMap m_housingZonePtrMap;
  };

}

#endif // SAPPHIRE_HOUSINGMGR_H
