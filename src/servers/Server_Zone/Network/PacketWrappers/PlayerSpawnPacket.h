#ifndef _PLAYERSPAWN_H
#define _PLAYERSPAWN_H

#include <Server_Common/Network/PacketDef/Zone/ServerZoneDef.h>
#include <Server_Common/Network/GamePacketNew.h>
#include <Server_Common/Util/UtilMath.h>
#include "Actor/Player.h"
#include "Forwards.h"
#include "Inventory/Inventory.h"
#include "Inventory/Item.h"
#include "StatusEffect/StatusEffect.h"

namespace Core {
namespace Network {
namespace Packets {
namespace Server {

   /**
   * @brief The packet sent to spawn a player.
   */
   class PlayerSpawnPacket :
      public GamePacketNew< FFXIVIpcPlayerSpawn, ServerZoneIpcType >
   {
   public:
      PlayerSpawnPacket( Entity::Player& player, Entity::Player& target ) :
         GamePacketNew< FFXIVIpcPlayerSpawn, ServerZoneIpcType >( player.getId(), target.getId() )
      {
         initialize( player, target );
      };

   private:
      void initialize( Entity::Player& player, Entity::Player& target )
      {
         // todo: figure out unkown offsets
         // TODO: temporary gm rank
         //m_data.gmRank = 0xff;

         m_data.classJob = static_cast< uint8_t >( player.getClass() );
         //m_data.status = static_cast< uint8_t >( pPlayer->getStatus() );

         m_data.hPCurr = player.getHp();
         m_data.mPCurr = player.getMp();
         m_data.tPCurr = player.getTp();
         m_data.hPMax = player.getMaxHp();
         m_data.mPMax = player.getMaxMp();
         
         //m_data.tPMax = 3000;
         m_data.level = player.getLevel();
         m_data.gmRank = player.getGmRank();
         m_data.pose = 0;

         memcpy( m_data.look, player.getLookArray(), 26 );

         auto item = player.getInventory()->getItemAt( Inventory::GearSet0, Inventory::EquipSlot::MainHand );
         if( item )
            m_data.mainWeaponModel = item->getModelId1();
         m_data.secWeaponModel = player.getModelSubWeapon();

         m_data.models[0] = player.getModelForSlot( Inventory::EquipSlot::Head );
         m_data.models[1] = player.getModelForSlot( Inventory::EquipSlot::Body );
         m_data.models[2] = player.getModelForSlot( Inventory::EquipSlot::Hands );
         m_data.models[3] = player.getModelForSlot( Inventory::EquipSlot::Legs );
         m_data.models[4] = player.getModelForSlot( Inventory::EquipSlot::Feet );
         strcpy( m_data.name, player.getName().c_str() );

         m_data.pos.x = player.getPos().x;
         m_data.pos.y = player.getPos().y;
         m_data.pos.z = player.getPos().z;
         m_data.rotation = Math::Util::floatToUInt16Rot( player.getRotation() );
         

         m_data.title = player.getTitle();
         m_data.voice = player.getVoiceId();
         m_data.currentMount = player.getCurrentMount();

         m_data.onlineStatus = static_cast< uint8_t >( player.getOnlineStatus() );

         //m_data.u23 = 0x04;
         //m_data.u24 = 256;
         m_data.state = static_cast< uint8_t >( player.getStatus() );
         m_data.type = 1;
         if( target.getId() == player.getId() )
         {
            m_data.spawnIndex = 0x00;
         }
         else
         {
            m_data.spawnIndex = target.getSpawnIdForActorId( player.getId() );
         }
         // 0x20 == spawn hidden to be displayed by the spawneffect control
         m_data.displayFlags = player.getStance();

         if( player.getZoningType() != Common::ZoneingType::None )
         {
            m_data.displayFlags |= Entity::Actor::DisplayFlags::Invisible;
         }

         if( player.getEquipDisplayFlags() & Core::Common::EquipDisplayFlags::HideHead )
         {
            m_data.displayFlags |= Entity::Actor::DisplayFlags::HideHead;
         }

         if( player.getEquipDisplayFlags() & Core::Common::EquipDisplayFlags::HideWeapon )
         {
            m_data.displayFlags |= Entity::Actor::DisplayFlags::HideWeapon;
         }

         if( player.getEquipDisplayFlags() & Core::Common::EquipDisplayFlags::Visor )
         {
            m_data.displayFlags |= Entity::Actor::DisplayFlags::Visor;
         }

         m_data.currentMount = player.getCurrentMount();

         m_data.targetId = player.getTargetId();
         //m_data.type = 1;
         //m_data.unknown_33 = 4;
         //m_data.unknown_38 = 0x70;
         //m_data.unknown_60 = 3;
         //m_data.unknown_61 = 7;

         uint64_t currentTimeMs = Util::getTimeMs();

         for( auto const& effect : player.getStatusEffectMap() )
         {
            m_data.effect[effect.first].effect_id = effect.second->getId();
            m_data.effect[effect.first].duration = static_cast< float >( effect.second->getDuration() -
                                                                       ( currentTimeMs - effect.second->getStartTimeMs() ) ) / 1000;
            m_data.effect[effect.first].sourceActorId = effect.second->getSrcActorId();
            m_data.effect[effect.first].unknown1 = effect.second->getParam();
         }

      };
   };

}
}
}
}

#endif /*_PlayerSpawn_H*/
