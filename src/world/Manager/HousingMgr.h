#ifndef SAPPHIRE_HOUSINGMGR_H
#define SAPPHIRE_HOUSINGMGR_H

#include "Forwards.h"
#include "Territory/HousingZone.h"
#include <set>
#include <unordered_map>
#include <array>

namespace Sapphire::Data
{
  using HousingZonePtr = std::shared_ptr< HousingZone >;
}

namespace Sapphire::World::Manager
{
  class HousingMgr
  {

  public:

    /*!
     * @brief Structure that is generated and filled on world launch. Used to store housing data during init
     * so we don't need to query them individually.
     */
    struct LandCacheEntry
    {
      // land table
      uint64_t m_landSetId;
      uint16_t m_landId;

      Common::LandType m_type;
      Common::HouseSize m_size;
      Common::HouseStatus m_status;

      uint64_t m_currentPrice;

      uint64_t m_updateTime;
      uint64_t m_ownerId;
      uint64_t m_houseId;

      // house table

      std::string m_estateWelcome;
      std::string m_estateComment;
      std::string m_estateName;

      bool m_hasAetheryte;

      uint64_t m_buildTime;
      uint64_t m_endorsements;

      uint16_t m_maxPlacedExternalItems;
      uint16_t m_maxPlacedInternalItems;
    };

    /*!
     * @brief Maps land id to a list of cached entries
     */
    using LandSetLandCacheMap = std::unordered_map< uint64_t, std::vector< LandCacheEntry > >;

    /*!
     * @brief Maps container IDs to their relevant ItemContainerPtr
     */
    using ContainerIdToContainerMap = std::unordered_map< uint16_t, ItemContainerPtr >;
    /*!
     * @brief Maps land idents to a container containing ItemContainerPtrs
     */
    using LandIdentToInventoryContainerMap = std::unordered_map< uint64_t, ContainerIdToContainerMap >;

    HousingMgr();
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

    void buildPresetEstate( Entity::Player& player, uint8_t plotNum, uint32_t presetCatalogId );

    void requestEstateRename( Entity::Player& player, const Common::LandIdent ident );

    void requestEstateEditGreeting( Entity::Player& player, const Common::LandIdent ident );
    void updateEstateGreeting( Entity::Player& player, const Common::LandIdent ident, const std::string& greeting );

    void requestEstateEditGuestAccess( Entity::Player& player, const Common::LandIdent ident );

    void sendEstateGreeting( Entity::Player& player, const Common::LandIdent ident );

    /*!
     * @brief Updates the cached models on a house from the relevant apperance inventories.
     * Does not send the subsequent update to clients.
     *
     * @param house The house to update the models for
     */
    void updateHouseModels( HousePtr house );

    /*!
     * @brief Sends the house inventory for the specified type to a player.
     *
     * This enforces permissions on the inventory too so random players can't request an estates items
     */
    void sendEstateInventory( Entity::Player& player, uint16_t inventoryType, uint8_t plotNum );

    /*!
     * @brief Sends all the available internal inventories in one go. Used to initially populate the menu.
     * @param player The player to send the containers to
     * @param storeroom True if we should send the storeroom, false we send the placed items
     */
    void sendInternalEstateInventoryBatch( Entity::Player& player, bool storeroom = false );

    /*!
     * @brief Get the land & house data that was cached on world startup.
     * @return
     */
    const LandSetLandCacheMap& getLandCacheMap();

    /*!
     * @brief Get all loaded inventories for housing estates
     * @return
     */
    LandIdentToInventoryContainerMap& getEstateInventories();

    /*!
     * @brief Get an estate inventory for a specific estate
     * @param ident LandIdent for the specified estate
     * @return A map containing container ids to ItemContainerPtr
     */
    ContainerIdToContainerMap& getEstateInventory( uint64_t ident );

    /*!
     * @brief Get an estate inventory for a specific estate
     * @param ident LandIdent for the specified estate
     * @return A map containing container ids to ItemContainerPtr
     */
    ContainerIdToContainerMap& getEstateInventory( Common::LandIdent ident );

    /**
     * @brief Sets up inventories and spawns the base items for the house appearance
     * @param land The house to update
     */
    bool initHouseModels( Entity::Player& player, LandPtr land, uint32_t presetCatalogId );

    void reqPlaceHousingItem( Entity::Player& player, uint16_t landId, uint16_t containerId, uint8_t slotId,
                              Common::FFXIVARR_POSITION3 pos, float rotation );

    void reqPlaceItemInStore( Entity::Player& player, uint16_t landId, uint16_t containerId, uint8_t slotId );

    /*!
     * @brief Returns the equivalent YardObject for a HousingItem
     * @param item The item to convert into a YardObject
     * @return The resultant YardObject
     */
    Common::HousingObject getYardObjectForItem( Inventory::HousingItemPtr item ) const;


    void reqMoveHousingItem( Entity::Player& player, Common::LandIdent ident, uint8_t slot,
                             Common::FFXIVARR_POSITION3 pos, float rot );


    void reqRemoveHousingItem( Sapphire::Entity::Player& player, uint16_t plot,
                               uint16_t containerId, uint8_t slot, bool sendToStoreroom );

    void reqEstateExteriorRemodel( Entity::Player& player, uint16_t plot );

    void reqEstateInteriorRemodel( Entity::Player& player );

    bool hasPermission( Entity::Player& player, Land& land, uint32_t permission );

    void editExterior( Sapphire::Entity::Player& player, uint16_t plot, std::vector< uint16_t > containerList, std::vector< uint8_t> slotList );

  private:

    Inventory::HousingItemPtr getHousingItemFromPlayer( Entity::Player& player, Common::InventoryType type, uint8_t slot );

    ItemContainerPtr getFreeEstateInventorySlot( Common::LandIdent ident,
                                                 Inventory::InventoryContainerPair& pair,
                                                 Inventory::InventoryTypeList bagList );

    /*!
     *
     * @param player
     * @param terri
     * @param containerId
     * @param slotId
     * @param sendToStoreroom
     * @return
     */
    bool removeInternalItem( Entity::Player& player, Territory::Housing::HousingInteriorTerritory& terri,
                             uint16_t containerId, uint16_t slotId, bool sendToStoreroom );

    /*!
     *
     * @param player
     * @param terri
     * @param slotId
     * @param sendToStoreroom
     * @return
     */
    bool removeExternalItem( Entity::Player& player, HousingZone& terri, Land& land,
                             Common::InventoryType containerType, uint8_t slotId,
                             bool sendToStoreroom );

    /*!
     * @brief Processes the movement of an item placed in a HousingZone
     *
     * This function assumes that the player has permission to move the item.
     *
     * @param player The player who placed the item
     * @param ident The ident of the land that the item belongs to
     * @param containerIdx The index of the container
     * @param slot The slot of the item
     * @param pos The new position
     * @param rot The new rotation
     * @return true if moved successfully
     */
    bool moveExternalItem( Entity::Player& player, Common::LandIdent ident, uint8_t slot,
                           Sapphire::HousingZone& terri, Common::FFXIVARR_POSITION3 pos, float rot );

    /*!
     * @brief Processes the movement of an item placed inside a HousingInteriorTerritory
     *
     * This function assumes that the player has permission to move the item.
     *
     * @param player The player who placed the item
     * @param ident The ident of the land that the item belongs to
     * @param slot The index of the container
     * @param slotIdx The slot of the item
     * @param pos The new position
     * @param rot The new rotation
     * @return true if moved successfully
     */
    bool moveInternalItem( Entity::Player& player, Common::LandIdent ident,
                           Territory::Housing::HousingInteriorTerritory& terri, uint8_t slot,
                           Common::FFXIVARR_POSITION3 pos, float rot );

    /*!
     * @brief Processes the spawning and linking of a newly placed housing item for external items
     * @param player The player who is placing the item
     * @param item The item that we're placing
     * @param ident The land that is going to own the item
     * @return true if the item was placed successfully, false if there's no free container slots to place it
     */
    bool placeExternalItem( Entity::Player& player, Inventory::HousingItemPtr item, Common::LandIdent ident );

    /*!
     * @brief Processing the spawning and linking of a newly placed item for interior items
     * @param player The player who is placing the item
     * @param item The item that we're placing
     * @return true if the item was placed successfully, false if there's no free spots to place it
     */
    bool placeInteriorItem( Entity::Player& player, Inventory::HousingItemPtr item );

    /*!
     * @brief Creates a house and saves the minimum amount required to persist a house through restarts.
     *
     * Any other changes will be covered by the usual saving logic and can be safely ignored here.
     *
     * @param house The house to create in the house table
     */
    void createHouse( HousePtr house ) const;

    /*!
     * @brief Gets the next available house id
     * @return The next available house id
     */
    uint64_t getNextHouseId();

    /*!
     * @brief Loads all the land entries from the database and caches them to speed up housing territory init
     */
    void initLandCache();

    /*!
     * @brief Loads all the inventories for every estate on the world and sets up their containers
     * @return True if it was successful
     */
    bool loadEstateInventories();

    /*!
     * @brief Gets the additionalData field from item.exd for an item
     * @param catalogId The item id to lookup in item.exd
     * @return The additionalData field from item.exd
     */
    uint32_t getItemAdditionalData( uint32_t catalogId );

    /*!
     * @brief Checks whether an estate inventory contains items that are placed and have a world position
     *
     * Eg, any item inside the 'placed' items container _should_ have a world position and can be spawned.
     *
     * @param type The inventory type that contains items
     * @return true if contains items that would have a world position
     */
    bool isPlacedItemsInventory( Common::InventoryType type );

    LandSetLandCacheMap m_landCache;
    LandIdentToInventoryContainerMap m_estateInventories;

    Inventory::InventoryTypeList m_internalPlacedItemContainers;
    Inventory::InventoryTypeList m_internalStoreroomContainers;

    std::array< std::pair< Common::InventoryType, Common::InventoryType >, 8 > m_containerMap;

  };

}

#endif // SAPPHIRE_HOUSINGMGR_H
