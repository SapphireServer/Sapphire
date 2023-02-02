#pragma once

#include <Network/GamePacket.h>
#include "Actor/Player.h"
#include "Inventory/Item.h"
#include "Forwards.h"

namespace Sapphire::Network::Packets::WorldPackets::Server
{

  /**
  * @brief The update inventory-slot packet.
  */
  class UpdateInventorySlotPacket : public ZoneChannelPacket< FFXIVIpcNormalItem >
  {
  public:
    UpdateInventorySlotPacket( uint32_t playerId, uint16_t slot, uint16_t storageId, const Item& item, uint32_t contextId ) :
      ZoneChannelPacket< FFXIVIpcNormalItem >( playerId, playerId )
    {
      initialize( slot, storageId, item, contextId );
    };

    UpdateInventorySlotPacket( uint32_t playerId, uint16_t slot, uint16_t storageId, uint32_t contextId ) :
      ZoneChannelPacket< FFXIVIpcNormalItem >( playerId, playerId )
    {
      initialize( slot, storageId, contextId );
    };

  private:
    void initialize( uint16_t slot, uint16_t storageId, const Item& item, uint32_t contextId )
    {
      m_data.contextId = contextId;
      m_data.item.storageId = storageId;
      m_data.item.catalogId = item.getId();
      m_data.item.stack = item.getStackSize();
      m_data.item.containerIndex = slot;
      m_data.item.flags = static_cast< uint8_t >( item.isHq() ? 1 : 0 );
      m_data.item.refine = item.getSpiritbond();
      m_data.item.stain = static_cast< uint8_t >( item.getStain() );
      m_data.item.signatureId = 0;
    };

    void initialize( uint16_t slot, uint16_t storageId, uint32_t contextId )
    {
      m_data.contextId = contextId;
      m_data.item.storageId = storageId;
      m_data.item.containerIndex = slot;
      m_data.item.stack = 0;
      m_data.item.catalogId = 0;
    };
  };

}