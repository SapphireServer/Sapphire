#ifndef _ACTORSPAWN_H
#define _ACTORSPAWN_H

#include <Server_Common/Network/GamePacketNew.h>
#include <Server_Common/Util/UtilMath.h>
#include "Actor/Player.h"
#include "Forwards.h"

namespace Core {
namespace Network {
namespace Packets {
namespace Server {

/**
* @brief The packet sent to spawn an actor.
*/
class ActorSpawnPacket :
   public GamePacketNew< FFXIVIpcActorSpawn, ServerZoneIpcType >
{
public:
   ActorSpawnPacket( Entity::PlayerPtr pPlayer, Entity::PlayerPtr pTarget ) :
      GamePacketNew< FFXIVIpcActorSpawn, ServerZoneIpcType >( pPlayer->getId(), pTarget->getId() )
   {
      initialize( pPlayer, pTarget );
   };

private:
   void initialize( Entity::PlayerPtr pPlayer, Entity::PlayerPtr pTarget )
   {
      // TODO: temporary gm rank
      m_data.gmRank = 0xff;
      m_data.classJob = static_cast< uint8_t >( pPlayer->getClass() );
      m_data.status = static_cast< uint8_t >( pPlayer->getStatus() );
      m_data.hPCurr = pPlayer->getHp();
      m_data.mPCurr = pPlayer->getMp();
      m_data.tPCurr = pPlayer->getTp();
      m_data.hPMax = pPlayer->getMaxHp();
      m_data.mPMax = pPlayer->getMaxMp();
      m_data.tPMax = 3000;
      m_data.level = pPlayer->getLevel();
      memcpy( m_data.look, pPlayer->getLookArray(), 26 );
      m_data.mainWeaponModel = pPlayer->getModelMainWeapon();
      m_data.secWeaponModel = pPlayer->getModelSubWeapon();
      m_data.models[0] = pPlayer->getModelForSlot( Inventory::EquipSlot::Head );
      m_data.models[1] = pPlayer->getModelForSlot( Inventory::EquipSlot::Body );
      m_data.models[2] = pPlayer->getModelForSlot( Inventory::EquipSlot::Hands );
      m_data.models[3] = pPlayer->getModelForSlot( Inventory::EquipSlot::Legs );
      m_data.models[4] = pPlayer->getModelForSlot( Inventory::EquipSlot::Feet );
      strcpy( m_data.name, pPlayer->getName().c_str() );
      m_data.pos.x = pPlayer->getPos().x;
      m_data.pos.y = pPlayer->getPos().y;
      m_data.pos.z = pPlayer->getPos().z;
      m_data.voice = pPlayer->getVoiceId();
      
      m_data.rotation = Math::Util::floatToUInt16Rot( pPlayer->getRotation() );

      m_data.statusIcon = pPlayer->getOnlineStatus();

      if( pTarget == pPlayer )
      {
         m_data.spawnIndex = 0x00;
      }
      else
      {
         m_data.spawnIndex = pTarget->getSpawnIdForActorId( pPlayer->getId() );
      }
      // 0x20 == spawn hidden to be displayed by the spawneffect control
      m_data.displayFlags = pPlayer->getStance();

      if( pPlayer->getZoningType() != Common::ZoneingType::None )
      {
         m_data.displayFlags |= 0x20;
      }

      m_data.targetId = pPlayer->getTargetId();
      m_data.type = 1;
      m_data.unknown_33 = 4;
      //m_data.unknown_38 = 0x70;
      //m_data.unknown_60 = 3;
      //m_data.unknown_61 = 7;


   };
};

}
}
}
}

#endif /*_ACTORSPAWN_H*/