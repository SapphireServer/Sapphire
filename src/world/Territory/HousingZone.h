#pragma once

#include "Territory.h"
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

  class HousingZone : public Territory
  {
  public:
    HousingZone( uint8_t landSetId,
                 uint16_t territoryTypeId,
                 const std::string& internalName,
                 const std::string& contentName );

    virtual ~HousingZone() = default;

    bool init() override;

    void onPlayerZoneIn( Entity::Player& player ) override;
    void onUpdate( uint64_t tickCount ) override;

    void sendLandSet( Entity::Player& player );
    void sendLandUpdate( uint16_t landId );
    bool isPlayerSubInstance( Entity::Player& player );

    bool onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId );

    /* returns current ward number for this zone */
    uint8_t getWardNum() const;

    uint32_t getLandSetId() const;
    Sapphire::LandPtr getLand( uint16_t id );

    Entity::EventObjectPtr registerEstateEntranceEObj( uint16_t landId );
    void removeEstateEntranceEObj( uint16_t landId );

    void updateYardObjects( Common::LandIdent ident );
    void spawnYardObject( uint16_t landId, uint16_t slotId, Sapphire::Inventory::HousingItem& item );
    void updateYardObjectPos( Entity::Player& sourcePlayer, uint16_t slot, uint16_t landId,
                                  Inventory::HousingItem& item );
    void despawnYardObject( uint16_t landId, uint16_t slot );

  private:
    using LandPtrMap = std::unordered_map< uint16_t, Sapphire::LandPtr >;

    /*! @brief global storage for all yard items in the ward */
    using YardObjectArray = std::array< Common::Furniture, 1200 >;

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

    const uint32_t m_landSetMax = 12;
    LandPtrMap m_landPtrMap;
    uint8_t m_wardNum;
    uint32_t m_landSetId;

    YardObjectArray m_yardObjects{};
    YardObjectArrayBoundsArray m_yardObjectArrayBounds;
  };

}
