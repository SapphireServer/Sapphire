#ifndef _PLAYERSPAWN_H
#define _PLAYERSPAWN_H

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
    m_data.pose = player.getPose();

    memcpy( m_data.look, player.getLookArray(), sizeof( m_data.look ) );

    auto item = player.getItemAt( Common::GearSet0, Common::GearSetSlot::MainHand );
    if( item )
      m_data.mainWeaponModel = item->getModelId1();
    m_data.secWeaponModel = player.getModelSubWeapon();

    m_data.models[ Common::GearModelSlot::ModelHead ] = player.getModelForSlot( Common::GearModelSlot::ModelHead );
    m_data.models[ Common::GearModelSlot::ModelBody ] = player.getModelForSlot( Common::GearModelSlot::ModelBody );
    m_data.models[ Common::GearModelSlot::ModelHands ] = player.getModelForSlot( Common::GearModelSlot::ModelHands );
    m_data.models[ Common::GearModelSlot::ModelLegs ] = player.getModelForSlot( Common::GearModelSlot::ModelLegs );
    m_data.models[ Common::GearModelSlot::ModelFeet ] = player.getModelForSlot( Common::GearModelSlot::ModelFeet );
    m_data.models[ Common::GearModelSlot::ModelNeck ] = player.getModelForSlot( Common::GearModelSlot::ModelNeck );
    m_data.models[ Common::GearModelSlot::ModelEar ] = player.getModelForSlot( Common::GearModelSlot::ModelEar );
    m_data.models[ Common::GearModelSlot::ModelRing1 ] = player.getModelForSlot( Common::GearModelSlot::ModelRing1 );
    m_data.models[ Common::GearModelSlot::ModelRing2 ] = player.getModelForSlot( Common::GearModelSlot::ModelRing2 );
    m_data.models[ Common::GearModelSlot::ModelWrist ] = player.getModelForSlot( Common::GearModelSlot::ModelWrist );

    strcpy( m_data.name, player.getName().c_str() );

    m_data.pos.x = player.getPos().x;
    m_data.pos.y = player.getPos().y;
    m_data.pos.z = player.getPos().z;
    m_data.rotation = Math::Util::floatToUInt16Rot( player.getRot() );


    m_data.title = player.getTitle();
    m_data.voice = player.getVoiceId();
    m_data.currentMount = player.getCurrentMount();

    m_data.onlineStatus = static_cast< uint8_t >( player.getOnlineStatus() );

    //m_data.u23 = 0x04;
    //m_data.u24 = 256;
    m_data.state = static_cast< uint8_t >( player.getStatus() );
    m_data.modelType = player.getObjKind();
    if( target.getId() == player.getId() )
    {
      m_data.spawnIndex = 0x00;
    }
    else
    {
      m_data.spawnIndex = target.getSpawnIdForActorId( player.getId() );

      if( !target.isActorSpawnIdValid( m_data.spawnIndex ) )
        return;
    }
    // 0x20 == spawn hidden to be displayed by the spawneffect control
    m_data.displayFlags = player.getStance();

    if( player.getZoningType() != Common::ZoneingType::None || player.getGmInvis() == true )
    {
      m_data.displayFlags |= static_cast< uint16_t >( Common::DisplayFlags::Invisible );
    }

    if( player.getEquipDisplayFlags() & Core::Common::EquipDisplayFlags::HideHead )
    {
      m_data.displayFlags |= static_cast< uint16_t >( Common::DisplayFlags::HideHead );
    }

    if( player.getEquipDisplayFlags() & Core::Common::EquipDisplayFlags::HideWeapon )
    {
      m_data.displayFlags |= static_cast< uint16_t >( Common::DisplayFlags::HideWeapon );
    }

    if( player.getEquipDisplayFlags() & Core::Common::EquipDisplayFlags::Visor )
    {
      m_data.displayFlags |= static_cast< uint16_t >( Common::DisplayFlags::Visor );
    }

    if( !( player.getEquipDisplayFlags() & Core::Common::EquipDisplayFlags::HideLegacyMark ) )
    {
      m_data.look[ 0xC ] = m_data.look[ 0xC ] | 1 << 7;
    }

    m_data.currentMount = player.getCurrentMount();
    m_data.persistentEmote = player.getPersistentEmote();

    m_data.targetId = player.getTargetId();
    //m_data.type = 1;
    //m_data.unknown_33 = 4;
    //m_data.unknown_38 = 0x70;
    //m_data.unknown_60 = 3;
    //m_data.unknown_61 = 7;

    uint64_t currentTimeMs = Core::Util::getTimeMs();

    for( auto const& effect : player.getStatusEffectMap() )
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
