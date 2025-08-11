#pragma once
#include "ForwardsZone.h"

namespace Sapphire::World::Manager
{

  class InventoryMgr
  {
  public:
    InventoryMgr() = default;

    /*!
     * @brief Sends an item container to a player
     *
     * This does no checks on the container itself. You can send another players inventory to a different
     * player if you so wish - not that you should
     *
     * Automagically manages inventory packet sequencing.
     *
     * @param player The player to send the container to
     * @param container The container to send to the player
     */
    void sendInventoryContainer( Sapphire::Entity::Player& player, Sapphire::ItemContainerPtr container );

    /*!
     * @brief Creates an item, saves it to the global item table and returns a ptr to the created item
     * @param player The player that will 'own' the item
     * @param catalogId The ID for the item, see item.exd
     * @param quantity how much item to make
     * @return An ItemPtr to the newly created item
     */
    Sapphire::ItemPtr createItem( Entity::Player& player, uint32_t catalogId, uint32_t quantity = 1 );

    /*!
     * @brief Commits a housing containers contents to the db
     * @param ident The identity of the owner of the container
     * @param container The container to save to the db
     */
    void saveHousingContainer( Common::LandIdent ident, Sapphire::ItemContainerPtr container );

    /*!
     * @brief Unlinks an item from the housing container in the db
     * @param ident The identity of the estate that owns the item
     * @param containerId The container the item is in
     * @param slotId The slot the item is in
     */
    void removeItemFromHousingContainer( Common::LandIdent ident, uint16_t containerId, uint16_t slotId );

    /*!
     * @brief Update an item in the db
     * @param item The item to commit to the db
     */
    void updateItem( Sapphire::ItemPtr item );

    /*!
     * @brief Updates the position/rotation of a housing object
     * @param item The item to update
     */
    void updateHousingItemPosition( Sapphire::Inventory::HousingItemPtr item );

    /*!
     * @brief Removes the position/rotation from a housing object
     * @param item The item to remove the position from.
     */
    void removeHousingItemPosition( Sapphire::Inventory::HousingItem& item );

    /*!
     * @brief Saves an item to the global item table
     * @param player The player which owns the item
     * @param item The item to save
     */
    void saveItem( Entity::Player& player, ItemPtr item );

  private:
    /*!
     * @brief Saves an individual item to the db.
     *
     * This will create a new row in the event the slot doesn't exist in the db, otherwise this
     * will overwrite the itemid in the existing row.
     *
     * @param ident
     * @param containerId
     * @param slotId
     * @param itemId
     */
    void saveHousingContainerItem( uint64_t ident,
                                   uint16_t containerId, uint16_t slotId,
                                   uint64_t itemId );
  };

}
