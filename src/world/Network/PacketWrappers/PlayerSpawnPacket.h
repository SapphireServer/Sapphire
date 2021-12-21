#ifndef _PLAYERSPAWN_H
#define _PLAYERSPAWN_H

#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <Network/GamePacket.h>
#include <Util/Util.h>
#include "Actor/Player.h"
#include "Forwards.h"
#include "Inventory/Item.h"
#include "StatusEffect/StatusEffect.h"

namespace Sapphire::Network::Packets::WorldPackets::Server
{

  /**
  * @brief The packet sent to spawn a player.
  */
  class PlayerSpawnPacket : public ZoneChannelPacket< FFXIVIpcPlayerSpawn >
  {
  public:
    PlayerSpawnPacket( Entity::Player& player, Entity::Player& target ) :
      ZoneChannelPacket< FFXIVIpcPlayerSpawn >( player.getId(), target.getId() )
    {
      initialize( player, target );
    };

  private:
    void initialize( Entity::Player& player, Entity::Player& target )
    {
      // todo: figure out unkown offsets
      m_data.ClassJob = static_cast< uint8_t >( player.getClass() );
      //m_data.status = static_cast< uint8_t >( pPlayer->getStatus() );

// TODO: world id from server
      m_data.WorldId = 67;
      //m_data.homeWorldId = 67;

      m_data.Hp = player.getHp();
      m_data.Mp = player.getMp();
      m_data.HpMax = player.getMaxHp();
      m_data.MpMax = player.getMaxMp();

      m_data.Lv = player.getLevel();
      m_data.GMRank = player.getGmRank();
      m_data.ModeArgs = player.getPersistentEmote();
      m_data.PoseEmote = player.getPose();

      if( player.isDirectorInitialized() )
      {
        m_data.ContentId = player.getDirectorId();
      }

      memcpy( m_data.Customize, player.getLookArray(), sizeof( m_data.Customize ) );

      auto item = player.getItemAt( Common::GearSet0, Common::GearSetSlot::MainHand );
      if( item )
        m_data.MainWeapon = player.getModelMainWeapon();
      m_data.SubWeapon = player.getModelSubWeapon();

      m_data.Equipment[ Common::GearModelSlot::ModelHead ] = player.getModelForSlot( Common::GearModelSlot::ModelHead );
      m_data.Equipment[ Common::GearModelSlot::ModelBody ] = player.getModelForSlot( Common::GearModelSlot::ModelBody );
      m_data.Equipment[ Common::GearModelSlot::ModelHands ] = player.getModelForSlot( Common::GearModelSlot::ModelHands );
      m_data.Equipment[ Common::GearModelSlot::ModelLegs ] = player.getModelForSlot( Common::GearModelSlot::ModelLegs );
      m_data.Equipment[ Common::GearModelSlot::ModelFeet ] = player.getModelForSlot( Common::GearModelSlot::ModelFeet );
      m_data.Equipment[ Common::GearModelSlot::ModelNeck ] = player.getModelForSlot( Common::GearModelSlot::ModelNeck );
      m_data.Equipment[ Common::GearModelSlot::ModelEar ] = player.getModelForSlot( Common::GearModelSlot::ModelEar );
      m_data.Equipment[ Common::GearModelSlot::ModelRing1 ] = player.getModelForSlot( Common::GearModelSlot::ModelRing1 );
      m_data.Equipment[ Common::GearModelSlot::ModelRing2 ] = player.getModelForSlot( Common::GearModelSlot::ModelRing2 );
      m_data.Equipment[ Common::GearModelSlot::ModelWrist ] = player.getModelForSlot( Common::GearModelSlot::ModelWrist );

      strcpy( reinterpret_cast< char* >( m_data.Name ), player.getName().c_str() );

      m_data.Pos[ 0 ] = player.getPos().x;
      m_data.Pos[ 1 ] = player.getPos().y;
      m_data.Pos[ 2 ] = player.getPos().z;
      m_data.Dir = Common::Util::floatToUInt16Rot( player.getRot() );


      m_data.Title = player.getTitle();
      m_data.Voice = player.getVoiceId();

      m_data.Companion = player.getCurrentCompanion();
      m_data.Mount.Id = player.getCurrentMount();

      m_data.OnlineStatus = static_cast< uint8_t >( player.getOnlineStatus() );

      //m_data.u23 = 0x04;
      //m_data.u24 = 256;
      m_data.Mode = static_cast< uint8_t >( player.getStatus() );
      m_data.ObjKind = player.getObjKind();
      m_data.ObjType = 4;
      if( target.getId() == player.getId() )
      {
        m_data.Index = 0;
      }
      else
      {
        m_data.Index = target.getSpawnIdForActorId( player.getId() );

        if( !target.isActorSpawnIdValid( m_data.Index ) )
          return;
      }
      // 0x20 == spawn hidden to be displayed by the spawneffect control
      m_data.ActiveType = player.getStance();

      if( player.getZoningType() != Common::ZoneingType::None || player.getGmInvis() )
      {
        m_data.ActiveType |= static_cast< uint16_t >( Common::DisplayFlags::Invisible );
      }

      if( player.getEquipDisplayFlags() & Sapphire::Common::EquipDisplayFlags::HideHead )
      {
        m_data.ActiveType |= static_cast< uint16_t >( Common::DisplayFlags::HideHead );
      }

      if( player.getEquipDisplayFlags() & Sapphire::Common::EquipDisplayFlags::HideWeapon )
      {
        m_data.ActiveType |= static_cast< uint16_t >( Common::DisplayFlags::HideWeapon );
      }

      if( player.getEquipDisplayFlags() & Sapphire::Common::EquipDisplayFlags::Visor )
      {
        m_data.ActiveType |= static_cast< uint16_t >( Common::DisplayFlags::Visor );
      }

      if( !( player.getEquipDisplayFlags() & Sapphire::Common::EquipDisplayFlags::HideLegacyMark ) )
      {
        m_data.Customize[ 0xC ] = m_data.Customize[ 0xC ] | 1 << 7;
      }

     // m_data.currentMount = player.getCurrentMount();

      m_data.MainTarget = player.getTargetId();
      //m_data.type = 1;
      //m_data.unknown_33 = 4;
      //m_data.unknown_38 = 0x70;
      //m_data.unknown_60 = 3;
      //m_data.unknown_61 = 7;

      uint64_t currentTimeMs = Common::Util::getTimeMs();

      for( auto const& effect : player.getStatusEffectMap() )
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
