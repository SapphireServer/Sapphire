#ifndef _CORE_NETWORK_PACKETS_EXAMINEPACKET_H
#define _CORE_NETWORK_PACKETS_EXAMINEPACKET_H

#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <Network/GamePacketNew.h>
#include <Util/Util.h>
#include "Actor/Player.h"
#include "Forwards.h"
#include "Inventory/Item.h"
#include "StatusEffect/StatusEffect.h"


namespace Core {
namespace Network {
namespace Packets {
namespace Server {

/**
* @brief The Examine response packet.
*/
class ExaminePacket :
  public ZoneChannelPacket< FFXIVIpcExamine >
{
public:
  ExaminePacket( Entity::Player& player, Entity::PlayerPtr pTarget ) :
    ZoneChannelPacket< FFXIVIpcExamine >( pTarget->getId(), player.getId() )
  {
    initialize( player, pTarget );
  };

private:
  void initialize( Entity::Player& player, Entity::PlayerPtr pTarget )
  {
    assert( pTarget );
    {
      // todo: this packet needs mapping out
      strcpy( m_data.name, pTarget->getName().c_str() );
      m_data.classJob = static_cast< uint8_t >( pTarget->getClass() );
      m_data.level = pTarget->getLevel();

      m_data.unkFlag1 = 4;
      m_data.unkFlag2 = 1;

      m_data.titleId = pTarget->getTitle();
      m_data.grandCompany = pTarget->getGc();
      m_data.grandCompanyRank = pTarget->getGcRankArray()[m_data.grandCompany];

      m_data.mainWeaponModel = pTarget->getModelMainWeapon();
      m_data.secWeaponModel = pTarget->getModelSubWeapon();

      memcpy( m_data.look, pTarget->getLookArray(), sizeof( m_data.look ) );
      for( auto i = 2; i < Common::GearSetSlot::SoulCrystal; ++i )
        m_data.models[ i - 2 ] = pTarget->getModelForSlot( static_cast< Common::GearSetSlot >( i ) );

      // todo: main/sub/other stuff too

      for( auto i = 0; i < Common::GearSetSlot::SoulCrystal + 1; ++i )
      {
        auto pItem = pTarget->getItemAt( Common::InventoryType::GearSet0, i );
        if( pItem )
        {
          auto& entry = m_data.entries[i];
          entry.catalogId = pItem->getId();
          entry.quality = pItem->isHq();
          //entry.appearanceCatalogId = pItem->getGlamourId()
          // todo: glamour/materia etc.
        }
      }
    }
  };
};

}
}
}
}

#endif /*_CORE_NETWORK_PACKETS_EXAMINEPACKET_H*/
