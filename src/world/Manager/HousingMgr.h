#ifndef SAPPHIRE_HOUSINGMGR_H
#define SAPPHIRE_HOUSINGMGR_H

#include "Forwards.h"
#include "BaseManager.h"
#include "Territory/HousingZone.h"
#include <set>
#include <unordered_map>

namespace Sapphire::Data
{
  using HousingZonePtr = std::shared_ptr< HousingZone >;
}

namespace Sapphire::World::Manager
{
  class HousingMgr : public BaseManager
  {

  public:
    HousingMgr( FrameworkPtr pFw );
    virtual ~HousingMgr();

    bool init();

    uint32_t toLandSetId( uint16_t territoryTypeId, uint8_t wardId ) const;
    Sapphire::Data::HousingZonePtr getHousingZoneByLandSetId( uint32_t id );
    Sapphire::LandPtr getLandByOwnerId( uint32_t id );

    void sendLandSignOwned( Entity::Player& player, const Common::LandIdent ident );
    void sendLandSignFree( Entity::Player& player, const Common::LandIdent ident );
    LandPurchaseResult purchaseLand( Entity::Player& player, uint8_t plot, uint8_t state );

    /*!
     * @brief Converts param1 of a client trigger into a Common::LandIndent
     */
    Common::LandIdent clientTriggerParamsToLandIdent( uint32_t param11, uint32_t param12, bool use16bits = true ) const;

    void sendWardLandInfo( Entity::Player& player, uint8_t wardId, uint16_t territoryTypeId );

    bool relinquishLand( Entity::Player& player, uint8_t plot );

    void buildPresetEstate( Entity::Player& player, uint8_t plotNum, uint32_t presetItem );

    void requestEstateRename( Entity::Player& player, const Common::LandIdent ident );

    void requestEstateEditGreeting( Entity::Player& player, const Common::LandIdent ident );
    void updateEstateGreeting( Entity::Player& player, const Common::LandIdent ident, const std::string& greeting );

    void requestEstateEditGuestAccess( Entity::Player& player, const Common::LandIdent ident );

    void sendEstateGreeting( Entity::Player& player, const Common::LandIdent ident );

    /*!
     * @brief Sends the house inventory for the specified type to a player.
     *
     * This enforces permissions on the inventory too so random players can't request a houses items
     */
    void sendHousingInventory( Entity::Player& player, uint16_t inventoryType, uint8_t plotNum );

  };

}

#endif // SAPPHIRE_HOUSINGMGR_H
