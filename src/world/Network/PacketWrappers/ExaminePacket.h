#ifndef _CORE_NETWORK_PACKETS_EXAMINEPACKET_H
#define _CORE_NETWORK_PACKETS_EXAMINEPACKET_H

#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <Network/GamePacket.h>
#include <Util/Util.h>
#include "Actor/Player.h"
#include "Forwards.h"
#include "Inventory/Item.h"
#include "StatusEffect/StatusEffect.h"


namespace Sapphire::Network::Packets::Server
{

  /**
  * @brief The Examine response packet.
  */
  class ExaminePacket : public ZoneChannelPacket< FFXIVIpcExamine >
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

        // gc id 0 is no gc, but we only store ranks for 3
        // gc id 3 is immortal flames, but they're at index 2 not 3, so we need to correct for that if we have a gc set
        if( m_data.grandCompany > 0 )
          m_data.grandCompanyRank = pTarget->getGcRankArray()[ m_data.grandCompany - 1 ];

        m_data.mainWeaponModel = pTarget->getModelMainWeapon();
        m_data.secWeaponModel = pTarget->getModelSubWeapon();

        memcpy( m_data.look, pTarget->getLookArray(), sizeof( m_data.look ) );

        m_data.models[ Common::GearModelSlot::ModelHead ] = pTarget->getModelForSlot( Common::GearModelSlot::ModelHead );
        m_data.models[ Common::GearModelSlot::ModelBody ] = pTarget->getModelForSlot( Common::GearModelSlot::ModelBody );
        m_data.models[ Common::GearModelSlot::ModelHands ] = pTarget->getModelForSlot( Common::GearModelSlot::ModelHands );
        m_data.models[ Common::GearModelSlot::ModelLegs ] = pTarget->getModelForSlot( Common::GearModelSlot::ModelLegs );
        m_data.models[ Common::GearModelSlot::ModelFeet ] = pTarget->getModelForSlot( Common::GearModelSlot::ModelFeet );
        m_data.models[ Common::GearModelSlot::ModelNeck ] = pTarget->getModelForSlot( Common::GearModelSlot::ModelNeck );
        m_data.models[ Common::GearModelSlot::ModelEar ] = pTarget->getModelForSlot( Common::GearModelSlot::ModelEar );
        m_data.models[ Common::GearModelSlot::ModelRing1 ] = pTarget->getModelForSlot( Common::GearModelSlot::ModelRing1 );
        m_data.models[ Common::GearModelSlot::ModelRing2 ] = pTarget->getModelForSlot( Common::GearModelSlot::ModelRing2 );
        m_data.models[ Common::GearModelSlot::ModelWrist ] = pTarget->getModelForSlot( Common::GearModelSlot::ModelWrist );

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

#endif /*_CORE_NETWORK_PACKETS_EXAMINEPACKET_H*/
