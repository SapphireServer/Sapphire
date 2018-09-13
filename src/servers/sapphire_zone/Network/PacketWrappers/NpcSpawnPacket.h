#ifndef _PLAYERSPAWN_H
#define _PLAYERSPAWN_H

#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <Network/GamePacketNew.h>
#include <Util/Util.h>
#include "Actor/Player.h"
#include "Actor/BNpc.h"
#include "Forwards.h"
#include "Inventory/Item.h"
#include "StatusEffect/StatusEffect.h"

namespace Core {
namespace Network {
namespace Packets {
namespace Server {

/**
* @brief The packet sent to spawn a player.
*/
class NpcSpawnPacket : public ZoneChannelPacket< FFXIVIpcNpcSpawn >
{
public:
  NpcSpawnPacket( Entity::BNpc& bnpc, Entity::Player& target ) :
    ZoneChannelPacket< FFXIVIpcNpcSpawn >( bnpc.getId(), target.getId() )
  {
    initialize( bnpc, target );
  };

private:
  void initialize( Entity::BNpc& bnpc, Entity::Player& target )
  {
    // todo: figure out unkown offsets
    m_data.classJob = static_cast< uint8_t >( bnpc.getClass() );
    //m_data.status = static_cast< uint8_t >( pPlayer->getStatus() );

    m_data.hPCurr = bnpc.getHp();
    m_data.mPCurr = bnpc.getMp();
    m_data.tPCurr = bnpc.getTp();
    m_data.hPMax = bnpc.getMaxHp();
    m_data.mPMax = bnpc.getMaxMp();
    m_data.subtype = 5;

    //m_data.tPMax = 3000;
    m_data.level = bnpc.getLevel();
    m_data.pose = bnpc.getPose();

    memcpy( m_data.look, bnpc.getLookArray(), sizeof( m_data.look ) );

    auto models = bnpc.getModelArray();
    memcpy( m_data.models, bnpc.getModelArray(), sizeof( m_data.models ) );

    memcpy( m_data.look, bnpc.getLookArray(), sizeof( m_data.look ) );

    m_data.pos.x = bnpc.getPos().x;
    m_data.pos.y = bnpc.getPos().y;
    m_data.pos.z = bnpc.getPos().z;
    m_data.rotation = Math::Util::floatToUInt16Rot( bnpc.getRot() );

    m_data.enemyType = bnpc.getEnemyType();
    m_data.mainWeaponModel = bnpc.getWeaponMain();
    m_data.secWeaponModel = bnpc.getWeaponSub();
    m_data.aggressionMode = bnpc.getAggressionMode();

    m_data.classJob = 0;
    //m_data.voice = bnpc.getVoiceId();
    //m_data.currentMount = bnpc.getCurrentMount();

    //m_data.onlineStatus = static_cast< uint8_t >( bnpc.getOnlineStatus() );

    //m_data.u23 = 0x04;
    //m_data.u24 = 256;
    m_data.state = static_cast< uint8_t >( bnpc.getStatus() );
    m_data.modelType = bnpc.getObjKind();
    m_data.modelChara = bnpc.getModelChara();

    m_data.bNPCBase = bnpc.getBNpcBaseId();
    m_data.bNPCName = bnpc.getBNpcNameId();

    m_data.state = 1;
    if( target.getId() == bnpc.getId() )
    {
      m_data.spawnIndex = 0x00;
    }
    else
    {
      m_data.spawnIndex = target.getSpawnIdForActorId( bnpc.getId() );

      if( !target.isActorSpawnIdValid( m_data.spawnIndex ) )
        return;
    }
    // 0x20 == spawn hidden to be displayed by the spawneffect control
    //m_data.displayFlags = bnpc.getDisplayFlags();

    /*if( bnpc.getZoningType() != Common::ZoneingType::None )
    {
      m_data.displayFlags |= static_cast< uint16_t >( Common::DisplayFlags::Invisible );
    }*/

    //m_data.currentMount = bnpc.getCurrentMount();
    //m_data.persistentEmote = bnpc.getPersistentEmote();

    m_data.targetId = static_cast< uint64_t >( bnpc.getTargetId() );
    //m_data.type = 1;
    //m_data.unknown_33 = 4;
    //m_data.unknown_38 = 0x70;
    //m_data.unknown_60 = 3;
    //m_data.unknown_61 = 7;


    uint64_t currentTimeMs = Core::Util::getTimeMs();

    for( auto const& effect : bnpc.getStatusEffectMap() )
    {
      m_data.effect[ effect.first ].effect_id = effect.second->getId();
      m_data.effect[ effect.first ].duration = static_cast< float >( effect.second->getDuration() -
                                                                     ( currentTimeMs -
                                                                       effect.second->getStartTimeMs() ) ) / 1000;
      m_data.effect[ effect.first ].sourceActorId = effect.second->getSrcActorId();
      m_data.effect[ effect.first ].unknown1 = effect.second->getParam();
    }

  };
};

}
}
}
}

#endif /*_PlayerSpawn_H*/
