#ifndef SAPPHIRE_HOUSINGZONE_H
#define SAPPHIRE_HOUSINGZONE_H

#include "Zone.h"
#include "Forwards.h"

#include <array>

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
                 const std::string& contentName,
                 FrameworkPtr pFw );

    virtual ~HousingZone() = default;

    bool init() override;

    void onPlayerZoneIn( Entity::Player& player ) override;
    void onUpdate( uint64_t tickCount ) override;

    void sendLandSet( Entity::Player& player );
    void sendLandUpdate( uint8_t landId );
    bool isPlayerSubInstance( Entity::Player& player );

    bool onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId );

    /* returns current ward number for this zone */
    uint8_t getWardNum() const;

    uint32_t getLandSetId() const;
    Sapphire::LandPtr getLand( uint8_t id );

    Entity::EventObjectPtr registerEstateEntranceEObj( uint8_t landId );

    void updateYardObjects( Common::LandIdent ident );
    void spawnYardObject( uint8_t landId, uint16_t slotId, Sapphire::Inventory::HousingItem& item );
    void updateYardObjectPos( Entity::Player& sourcePlayer, uint16_t slot, uint16_t landId,
                                  Inventory::HousingItem& item );
    void despawnYardObject( uint16_t landId, uint16_t slot );

  private:
    using LandPtrMap = std::unordered_map< uint8_t, Sapphire::LandPtr >;
    using YardObjectArray = std::array< Common::HousingObject, 800 >;
    using YardObjectSubdivisionArray = std::array< YardObjectArray, 2 >;

    /*!
     * @brief Maps the start and end index of the yard object array for a specific plot
     *
     * pair.first = start index
     * pair.second = end index
     */
    using YardObjectArrayBoundsPair = std::pair< uint16_t, uint16_t >;

    /*!
     * @brief Maps each plot to a YardObjectArrayBoundsPair to the start/end index of the yard object array.
     */
    using YardObjectArrayBoundsArray = std::array< YardObjectArrayBoundsPair, 60 >;

    const uint32_t m_landSetMax = 18;
    LandPtrMap m_landPtrMap;
    uint8_t m_wardNum;
    uint32_t m_landSetId;
    uint32_t m_territoryTypeId;

    YardObjectSubdivisionArray m_yardObjects;
    YardObjectArrayBoundsArray m_yardObjectArrayBounds;
    FrameworkPtr m_pFw;
  };

}
#endif //SAPPHIRE_HOUSINGZONE_H
