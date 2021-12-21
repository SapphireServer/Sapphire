#ifndef _PLAYERSPAWN_H
#define _PLAYERSPAWN_H

#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <Network/GamePacket.h>
#include <Util/Util.h>
#include <Common.h>
#include "Actor/Player.h"
#include "Actor/BNpc.h"
#include "Forwards.h"
#include "Inventory/Item.h"
#include "StatusEffect/StatusEffect.h"

namespace Sapphire::Network::Packets::WorldPackets::Server
{

  /**
  * @brief The packet sent to spawn a player.
  */
  class NpcSpawnPacket : public ZoneChannelPacket< FFXIVIpcPlayerSpawn >
  {
  public:
    NpcSpawnPacket( Entity::BNpc& bnpc, Entity::Player& target ) :
      ZoneChannelPacket< FFXIVIpcPlayerSpawn >( bnpc.getId(), target.getId() )
    {
      initialize( bnpc, target );
    };

  private:
    void initialize( Entity::BNpc& bnpc, Entity::Player& target )
    {
      // todo: figure out unkown offsets
      m_data.ClassJob = static_cast< uint8_t >( bnpc.getClass() );
      //m_data.ActiveType = static_cast< uint8_t >( bnpc.getStatus() );

      m_data.LayoutId = bnpc.getLayoutId();
      m_data.Hp = bnpc.getHp();
      m_data.Mp = bnpc.getMp();
      m_data.HpMax = bnpc.getMaxHp();
      m_data.Lv = bnpc.getLevel();
      m_data.ModeArgs = bnpc.getPose();
      m_data.ContentId = bnpc.getDirectorId();

      memcpy( m_data.Customize, bnpc.getLookArray(), sizeof( m_data.Customize ) );
      memcpy( m_data.Equipment, bnpc.getModelArray(), sizeof( m_data.Equipment ) );

      m_data.Pos[ 0 ] = bnpc.getPos().x;
      m_data.Pos[ 1 ] = bnpc.getPos().y;
      m_data.Pos[ 2 ] = bnpc.getPos().z;
      m_data.Dir = Common::Util::floatToUInt16Rot( bnpc.getRot() );
      m_data.BindId = bnpc.getBoundInstanceId();

      m_data.Rank = bnpc.getRank();
      m_data.MainWeapon = bnpc.getWeaponMain();
      m_data.SubWeapon = bnpc.getWeaponSub();
      m_data.ActiveType = bnpc.getAggressionMode() != 1 ? 2 : 1;

      m_data.ClassJob = 0;

      m_data.ContentId = bnpc.getDirectorId();
      m_data.MainTarget = bnpc.getTargetId();
      // no idea ... m_data.spawnerId = Common::INVALID_GAME_OBJECT_ID64;
      m_data.ParentId = Common::INVALID_GAME_OBJECT_ID;
      m_data.TriggerId = 0;
      m_data.ChannelingTarget = Common::INVALID_GAME_OBJECT_ID;
      m_data.OwnerId = Common::INVALID_GAME_OBJECT_ID;

      //m_data.u23 = 0x04;
      //m_data.u24 = 256;
      m_data.Mode = static_cast< uint8_t >( bnpc.getStatus() );
      m_data.ObjKind = bnpc.getObjKind();
      m_data.ObjType = 5;
      // ref to bnpcbase.battalion, 0 is friendly npc rest are ???
      m_data.Battalion = bnpc.getEnemyType();

      m_data.ModelCharaId = bnpc.getModelChara();

      m_data.NpcId = bnpc.getBNpcBaseId();
      m_data.NameId = bnpc.getBNpcNameId();

      assert( target.getId() != bnpc.getId() );

      m_data.Index = target.getSpawnIdForActorId( bnpc.getId() );

      if( !target.isActorSpawnIdValid( m_data.Index ) )
        return;
      // 0x20 == spawn hidden to be displayed by the spawneffect control
      //m_data.displayFlags = bnpc.getDisplayFlags();

      //m_data.currentMount = bnpc.getCurrentMount();
      //m_data.persistentEmote = bnpc.getPersistentEmote();

      m_data.MainTarget = static_cast< uint64_t >( bnpc.getTargetId() );

      uint64_t currentTimeMs = Common::Util::getTimeMs();

      for( auto const& effect : bnpc.getStatusEffectMap() )
      {
        m_data.Status[ effect.first ].Id = effect.second->getId();
        m_data.Status[ effect.first ].Time = static_cast< float >( effect.second->getDuration() -
                                                                       ( currentTimeMs -
                                                                         effect.second->getStartTimeMs() ) ) / 1000;
        m_data.Status[ effect.first ].Source = effect.second->getSrcActorId();
        m_data.Status[ effect.first ].SystemParam = effect.second->getParam();
      }

    };
  };

}

#endif /*_PlayerSpawn_H*/
