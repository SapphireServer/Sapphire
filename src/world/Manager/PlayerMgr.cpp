#include "PlayerMgr.h"

#include <Service.h>

#include <Exd/ExdData.h>

#include <Territory/ZonePosition.h>
#include <Territory/Territory.h>

#include <Manager/TerritoryMgr.h>
#include <Manager/HousingMgr.h>

#include "Script/ScriptMgr.h"
#include "WorldServer.h"
#include <Common.h>

#include <Network/PacketContainer.h>
#include <Network/GameConnection.h>
#include <Network/CommonActorControl.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <Network/PacketWrappers/ActorControlPacket.h>
#include <Network/PacketWrappers/ActorControlSelfPacket.h>
#include "Network/PacketWrappers/ActorControlTargetPacket.h"
#include <Network/PacketWrappers/ModelEquipPacket.h>
#include <Network/PacketWrappers/PlayerStateFlagsPacket.h>
#include <Network/PacketWrappers/UpdateHpMpTpPacket.h>
#include "Network/PacketWrappers/PlayerSetupPacket.h"
#include "Network/PacketWrappers/ServerNoticePacket.h"
#include "Network/PacketWrappers/ChatPacket.h"
#include "Network/PacketWrappers/HudParamPacket.h"

#include <Actor/Player.h>

using namespace Sapphire::World::Manager;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets::Server;
using namespace Sapphire::Network::ActorControl;
using namespace Sapphire::Common;

void PlayerMgr::movePlayerToLandDestination( Sapphire::Entity::Player& player, uint32_t landId, uint16_t param )
{
  // check if we have one in the db first
  auto& terriMgr = Common::Service< TerritoryMgr >::ref();

  Sapphire::TerritoryPtr destinationZone;

  auto terriPos = terriMgr.getTerritoryPosition( landId );
  if( terriPos )
  {
    // check if its a housing zone, zoning is different here
    if( terriMgr.isHousingTerritory( terriPos->getTargetZoneId() ) )
    {
      auto& housingMgr = Common::Service< HousingMgr >::ref();
      auto landSetId = housingMgr.toLandSetId( terriPos->getTargetZoneId(), param );

      auto housingZone = housingMgr.getHousingZoneByLandSetId( landSetId );

      if( !housingZone )
        return;

      destinationZone = housingZone;
    }
    else if( terriMgr.isInstanceContentTerritory( terriPos->getTargetZoneId() ) )
    {
      // todo: instance dungeon handling
      // will need to use setInstance so old pos gets set
      return;
    }
    else
    {
      // normal zones
      destinationZone = terriMgr.getZoneByTerritoryTypeId( terriPos->getTargetZoneId() );
    }
  }
  else
  {
    // todo: lookup land.exd and see if it's in there if its not in our db
    return;
  }

  if( !destinationZone )
  {
    PlayerMgr::sendDebug( player,  "Unable to find applicable territory for Warp#{0}. "
                                   "Check that it exists inside zonepositions table.",
                          landId );
    return;
  }

  player.setPos( terriPos->getTargetPosition() );
  player.setRot( terriPos->getTargetRotation() );

  terriMgr.movePlayer( destinationZone, player );
}

void PlayerMgr::onOnlineStatusChanged( Sapphire::Entity::Player& player, bool updateProfile )
{
  auto& server = Common::Service< World::WorldServer >::ref();

  auto statusPacket = makeZonePacket< FFXIVIpcSetOnlineStatus >( player.getId() );
  statusPacket->data().onlineStatusFlags = player.getFullOnlineStatusMask();
  server.queueForPlayer( player.getCharacterId(), statusPacket );

  if( updateProfile )
  {
    auto searchInfoPacket = makeZonePacket< FFXIVIpcSetProfileResult >( player.getId());
    searchInfoPacket->data().OnlineStatus = player.getFullOnlineStatusMask();
    searchInfoPacket->data().Region = player.getSearchSelectRegion();
    strcpy( searchInfoPacket->data().SearchComment, player.getSearchMessage());
    server.queueForPlayer( player.getCharacterId(), searchInfoPacket );
  }

  player.sendToInRangeSet( makeActorControl( player.getId(), SetStatusIcon, static_cast< uint8_t >( player.getOnlineStatus() ) ), true );
}

void PlayerMgr::onEquipDisplayFlagsChanged( Sapphire::Entity::Player& player )
{
  auto& server = Common::Service< World::WorldServer >::ref();
  PlayerMgr::sendDebug( player, "EquipDisplayFlag CHANGE: {0}", player.getEquipDisplayFlags() );
  auto paramPacket = makeZonePacket< FFXIVIpcConfig >( player.getId() );
  paramPacket->data().flag = player.getEquipDisplayFlags();
  player.sendToInRangeSet( paramPacket, true );
}

void PlayerMgr::onSendStateFlags( Sapphire::Entity::Player& player, bool updateInRange )
{
  auto& server = Common::Service< World::WorldServer >::ref();
  server.queueForPlayer( player.getCharacterId(), std::make_shared< PlayerStateFlagsPacket >( player ) );

  if( updateInRange )
    player.sendToInRangeSet( makeActorControl( player.getId(), SetStatusIcon,
                                        static_cast< uint8_t >( player.getOnlineStatus() ) ), true );
}

void PlayerMgr::onSendStats( Sapphire::Entity::Player& player )
{
  std::array< uint32_t, 50 > statParams;

  auto& exd = Common::Service< Data::ExdData >::ref();

  // todo: this is no doubt slow as shit...
  auto idList = exd.getIdList< Component::Excel::BaseParam >();

  for( const auto id : idList )
  {
    auto row = exd.getRow< Component::Excel::BaseParam >( id );
    if( !row )
    {
      continue;
    }

    if( row->data().PacketIndex < 0 )
    {
      continue;
    }

    statParams[ row->data().PacketIndex ] = player.getStatValue( static_cast< Common::BaseParam >( id ) );
  }

  auto& server = Common::Service< World::WorldServer >::ref();

  auto statPacket = makeZonePacket< FFXIVIpcBaseParam >( player.getId() );
  memcpy( statPacket->data().Param, statParams.data(), sizeof( uint32_t ) * statParams.size() );

  server.queueForPlayer( player.getCharacterId(), statPacket );
}

void PlayerMgr::onPlayerStatusUpdate( Sapphire::Entity::Player& player )
{
  auto& server = Common::Service< World::WorldServer >::ref();

  auto playerStatusUpdate = makeZonePacket< FFXIVIpcPlayerStatusUpdate >( player.getId() );
  playerStatusUpdate->data().ClassJob = static_cast< uint8_t >( player.getClass() );
  playerStatusUpdate->data().Lv = player.getLevel();
  playerStatusUpdate->data().LvSync = 0; //player.getLevelSync();
  playerStatusUpdate->data().Exp = player.getExp();

  server.queueForPlayer( player.getCharacterId(), playerStatusUpdate );
}

void PlayerMgr::onPlayerHpMpTpChanged( Sapphire::Entity::Player& player )
{
  player.sendToInRangeSet( std::make_shared< UpdateHpMpTpPacket >( player ), true );
}

void PlayerMgr::onPlayerItemLevelUpdate( Sapphire::Entity::Player& player )
{
  auto& server = Common::Service< World::WorldServer >::ref();
  server.queueForPlayer( player.getCharacterId(), makeActorControl( player.getId(), SetItemLevel, player.getItemLevel(), 0 ) );
}

void PlayerMgr::onLevelUp( Sapphire::Entity::Player& player )
{
  player.calculateStats();
  player.sendStats();
  Service< World::Manager::PlayerMgr >::ref().onPlayerHpMpTpChanged( player );

  player.sendToInRangeSet( makeHudParam( player ), true );

  player.sendToInRangeSet( makeActorControl( player.getId(), LevelUpEffect, static_cast< uint8_t >( player.getClass() ),
                           player.getLevel(), player.getLevel() - 1 ), true );
}

void PlayerMgr::onGainExp( Sapphire::Entity::Player& player, uint32_t exp )
{
  auto& server = Common::Service< World::WorldServer >::ref();

  if( exp != 0 )
    server.queueForPlayer( player.getCharacterId(), makeActorControlSelf( player.getId(), GainExpMsg, static_cast< uint8_t >( player.getClass() ), exp ) );

  server.queueForPlayer( player.getCharacterId(), makeActorControlSelf( player.getId(), UpdateUiExp, static_cast< uint8_t >( player.getClass() ), exp ) );
}

void PlayerMgr::onUnlockOrchestrion( Sapphire::Entity::Player& player, uint8_t songId, uint32_t itemId )
{
  auto& server = Common::Service< World::WorldServer >::ref();
  server.queueForPlayer( player.getCharacterId(), makeActorControlSelf( player.getId(), ToggleOrchestrionUnlock, songId, 1, itemId ) );
}

void PlayerMgr::onChangeGear( Sapphire::Entity::Player& player )
{
  player.sendToInRangeSet( std::make_shared< ModelEquipPacket >( player ), true );
}

void PlayerMgr::onGcUpdate( Sapphire::Entity::Player& player )
{
  auto& server = Common::Service< World::WorldServer >::ref();
  auto gcAffPacket = makeZonePacket< FFXIVGCAffiliation >( player.getId() );
  gcAffPacket->data().gcId = player.getGc();
  gcAffPacket->data().gcRank[ 0 ] = player.getGcRankArray()[ 0 ];
  gcAffPacket->data().gcRank[ 1 ] = player.getGcRankArray()[ 1 ];
  gcAffPacket->data().gcRank[ 2 ] = player.getGcRankArray()[ 2 ];
  server.queueForPlayer( player.getCharacterId(), gcAffPacket );
}

void PlayerMgr::onMountUpdate( Sapphire::Entity::Player& player, uint32_t mountId )
{
  if( mountId != 0 )
  {
    player.sendToInRangeSet( makeActorControl( player.getId(), ActorControlType::SetStatus,
                      static_cast< uint8_t >( Common::ActorStatus::Mounted ) ), true );
    player.sendToInRangeSet( makeActorControlSelf( player.getId(), 0x39e, 12 ), true ); //?

    auto mountPacket = makeZonePacket< FFXIVIpcMount >( player.getId() );
    mountPacket->data().id = mountId;
    player.sendToInRangeSet( mountPacket, true );
  }
  else
  {
    player.sendToInRangeSet( makeActorControl( player.getId(), ActorControlType::SetStatus,
                      static_cast< uint8_t >( Common::ActorStatus::Idle ) ), true );
    player.sendToInRangeSet( makeActorControlSelf( player.getId(), ActorControlType::Dismount, 1 ), true );
  }
}

void PlayerMgr::onMobKill( Sapphire::Entity::Player& player, uint16_t nameId )
{
  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();
  scriptMgr.onBNpcKill( player, nameId );

  if( player.isActionLearned( Common::UnlockEntry::HuntingLog ) )
  {
    player.updateHuntingLog( nameId );
  }
}

void PlayerMgr::onHateListChanged( Sapphire::Entity::Player& player )
{
  auto& server = Common::Service< World::WorldServer >::ref();

  auto hateListPacket = makeZonePacket< FFXIVIpcHateList >( player.getId() );
  auto hateRankPacket = makeZonePacket< FFXIVIpcHaterList >( player.getId() );

  auto actorIdToHateSlotMap = player.getActorIdToHateSlotMap();

  hateListPacket->data().Count = static_cast< uint8_t >( actorIdToHateSlotMap.size() );
  
  hateRankPacket->data().Count = static_cast< uint8_t >( actorIdToHateSlotMap.size() );
  auto it = actorIdToHateSlotMap.begin();
  for( int32_t i = 0; it != actorIdToHateSlotMap.end(); ++it, i++ )
  {
    // TODO: get actual hate values for these
    hateListPacket->data().List[ i ].Id = it->first;
    hateListPacket->data().List[ i ].Value = 100;

    hateRankPacket->data().List[ i ].Id = it->first;
    hateRankPacket->data().List[ i ].Rate = 1;
  }

  server.queueForPlayer( player.getCharacterId(), { hateListPacket, hateRankPacket } );
}

void PlayerMgr::onChangeClass( Sapphire::Entity::Player &player )
{
  player.sendToInRangeSet( makeActorControl( player.getId(), ClassJobChange, 0x04 ), true );
  player.sendStatusUpdate();
}

void PlayerMgr::onLogin( Sapphire::Entity::Player &player )
{
  auto& server = Common::Service< World::WorldServer >::ref();

  auto motd = server.getConfig().motd;

  std::istringstream ss( motd );
  std::string msg;
  while( std::getline( ss, msg, ';' ) )
  {
    PlayerMgr::sendServerNotice( player, msg );
  }
}




////////// Helper ///////////



void PlayerMgr::sendServerNotice( Sapphire::Entity::Player& player, const std::string& message ) //Purple Text
{
  auto& server = Common::Service< World::WorldServer >::ref();
  server.queueForPlayer( player.getCharacterId(), std::make_shared< ServerNoticePacket >( player.getId(), message ) );

}

void PlayerMgr::sendUrgent( Sapphire::Entity::Player& player, const std::string& message ) //Red Text
{
  auto& server = Common::Service< World::WorldServer >::ref();
  server.queueForPlayer( player.getCharacterId(), std::make_shared< ChatPacket >( player, ChatType::ServerUrgent, message ) );
}

void PlayerMgr::sendDebug( Sapphire::Entity::Player& player, const std::string& message ) //Grey Text
{
  auto& server = Common::Service< World::WorldServer >::ref();
  server.queueForPlayer( player.getCharacterId(), std::make_shared< ChatPacket >( player, ChatType::SystemMessage, message ) );
}

void PlayerMgr::sendLogMessage( Sapphire::Entity::Player& player, uint32_t messageId, uint32_t param2, uint32_t param3,
                                uint32_t param4, uint32_t param5, uint32_t param6 )
{
  auto& server = Common::Service< World::WorldServer >::ref();
  server.queueForPlayer( player.getCharacterId(), makeActorControlTarget( player.getId(), ActorControlType::LogMsg, messageId,
                                                                                 param2, param3, param4, param5, param6 ) );
}
