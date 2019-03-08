#ifndef _INVENTORY_SLOT_UPDATE_PACKET_H
#define _INVENTORY_SLOT_UPDATE_PACKET_H

#include <Network/GamePacket.h>
#include "Actor/Player.h"
#include "Inventory/Item.h"
#include "Forwards.h"

namespace Sapphire::Network::Packets::Server
{

  /**
  * @brief The update inventory-slot packet.
  */
  class UpdateInventorySlotPacket : public ZoneChannelPacket< FFXIVIpcUpdateInventorySlot >
  {
  public:
    UpdateInventorySlotPacket( uint32_t playerId, uint8_t slot, uint16_t storageId, const Item& item ) :
      ZoneChannelPacket< FFXIVIpcUpdateInventorySlot >( playerId, playerId )
    {
      initialize( slot, storageId, item );
    };

  private:
    void initialize( uint8_t slot, uint16_t storageId, const Item& item )
    {
      m_data.sequence = 0;
      m_data.containerId = storageId;
      m_data.slot = slot;
      m_data.quantity = item.getStackSize();
      m_data.catalogId = item.getId();
      m_data.reservedFlag = item.getReservedFlag(); // no idea
      m_data.signatureId = 0;
      m_data.hqFlag = item.isHq() ? 1 : 0;
      m_data.condition = 60000; // 200%
      m_data.spiritBond = item.getSpiritbond();
      m_data.color = 0;
      m_data.glamourCatalogId = 0;
      m_data.materia1 = 0;
      m_data.materia2 = 0;
      m_data.materia3 = 0;
      m_data.materia4 = 0;
      m_data.materia5 = 0;
      //m_data.buffer1;
      //uint8_t buffer2;
      //uint8_t buffer3;
      //uint8_t buffer4;
      //uint8_t buffer5;
    };
  };

}

#endif /*_MODELEQUIPPACKET_H*/
