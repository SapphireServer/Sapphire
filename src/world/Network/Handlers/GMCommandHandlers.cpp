#include <Common.h>
#include <Network/CommonNetwork.h>
#include <Network/GamePacket.h>
#include <Logging/Logger.h>
#include <Network/PacketContainer.h>
#include <Network/CommonActorControl.h>
#include <Network/PacketDef/Zone/ClientZoneDef.h>
#include <Exd/ExdData.h>
#include <Service.h>

#include "Network/GameConnection.h"

#include "Session.h"

#include "Manager/TerritoryMgr.h"
#include "Manager/PlayerMgr.h"
#include "Manager/WarpMgr.h"
#include "Territory/Territory.h"
#include "Territory/InstanceContent.h"

#include "Network/PacketWrappers/PlayerSetupPacket.h"
#include "Network/PacketWrappers/ActorControlPacket.h"
#include "Network/PacketWrappers/ActorControlSelfPacket.h"

#include "WorldServer.h"

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets::Server;
using namespace Sapphire::Network::Packets::WorldPackets::Client;
using namespace Sapphire::Network::Packets::WorldPackets;
using namespace Sapphire::Network::ActorControl;
using namespace Sapphire::World::Manager;

enum GmCommand
{
  Pos = 0x0000,
  Lv = 0x0001,
  Race = 0x0002,
  Tribe = 0x0003,
  Sex = 0x0004,
  Time = 0x0005,
  Weather = 0x0006,
  Call = 0x0007,
  Inspect = 0x0008,
  Speed = 0x0009,
  Invis = 0x000D,

  Raise = 0x0010,
  Kill = 0x000E,
  Icon = 0x0012,

  Hp = 0x0064,
  Mp = 0x0065,
  Tp = 0x0066,
  Gp = 0x0067,
  Exp = 0x0068,
  Inv = 0x006A,

  Orchestrion = 0x0074,

  Item = 0x00C8,
  Gil = 0x00C9,
  Collect = 0x00CA,

  QuestAccept = 0x012C,
  QuestCancel = 0x012D,
  QuestComplete = 0x012E,
  QuestIncomplete = 0x012F,
  QuestSequence = 0x0130,
  QuestInspect = 0x0131,
  GC = 0x0154,
  GCRank = 0x0155,
  Aetheryte = 0x015E,
  Wireframe = 0x0226,
  Teri = 0x0258,
  Kick = 0x025C,
  TeriInfo = 0x025D,
  Jump = 0x025E,
  JumpNpc = 0x025F,
};

void Sapphire::Network::GameConnection::gmCommandHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{
  if( player.getGmRank() <= 0 )
    return;

  auto& server = Common::Service< World::WorldServer >::ref();
  auto& teriMgr = Common::Service< World::Manager::TerritoryMgr >::ref();
  auto& exdData = Common::Service< Data::ExdData >::ref();

  const auto packet = ZoneChannelPacket< FFXIVIpcGmCommand >( inPacket );
  const auto commandId = packet.data().Id;
  const auto param1 = packet.data().Arg0;
  const auto param2 = packet.data().Arg1;
  const auto param3 = packet.data().Arg2;
  const auto param4 = packet.data().Arg3;
  const auto target = packet.data().Target;

  Logger::info( "{0} used GM1 commandId: {1}, params: {2}, {3}, {4}, {5}, target: {6}",
                player.getName(), commandId, param1, param2, param3, param4, target );

  Sapphire::Entity::GameObjectPtr targetActor;

  if( player.getId() == target )
  {
    targetActor = player.getAsPlayer();
  }
  else
  {
    auto inRange = player.getInRangeActors();
    for( auto& actor : inRange )
    {
      if( actor->getId() == target )
        targetActor = actor;
    }
  }

  if( !targetActor )
    return;

  auto targetPlayer = targetActor->getAsPlayer();

  auto pTargetZone = teriMgr.getTerritoryByGuId( targetActor->getTerritoryId() );

  switch( commandId )
  {
    case GmCommand::Lv:
    {
      targetPlayer->setLevel( static_cast< uint8_t >( param1 ) );
      PlayerMgr::sendServerNotice( player, "Level for {0} was set to {1}", targetPlayer->getName(), param1 );
      break;
    }
    case GmCommand::Race:
    {
      targetPlayer->setLookAt( CharaLook::Race, static_cast< uint8_t >( param1 ) );
      PlayerMgr::sendServerNotice( player, "Race for {0} was set to {1}", targetPlayer->getName(), param1 );
      targetPlayer->spawn( targetPlayer );
      auto inRange = targetPlayer->getInRangeActors();
      for( auto actor : inRange )
      {
        if( actor->isPlayer() )
        {
          targetPlayer->despawn( actor->getAsPlayer() );
          targetPlayer->spawn( actor->getAsPlayer() );
        }
      }
      break;
    }
    case GmCommand::Tribe:
    {
      targetPlayer->setLookAt( CharaLook::Tribe, static_cast< uint8_t >( param1 ) );
      PlayerMgr::sendServerNotice( player, "Tribe for {0} was set to ", targetPlayer->getName(), param1 );
      targetPlayer->spawn( targetPlayer );
      auto inRange = targetPlayer->getInRangeActors();
      for( auto actor : inRange )
      {
        if( actor->isPlayer() )
        {
          targetPlayer->despawn( actor->getAsPlayer() );
          targetPlayer->spawn( actor->getAsPlayer() );
        }
      }
      break;
    }
    case GmCommand::Sex:
    {
      targetPlayer->setLookAt( CharaLook::Gender, static_cast< uint8_t >( param1 ) );
      PlayerMgr::sendServerNotice( player, "Sex for {0} was set to ", targetPlayer->getName(), param1 );
      targetPlayer->spawn( targetPlayer );
      auto inRange = targetActor->getInRangeActors();
      for( auto actor : inRange )
      {
        if( actor->isPlayer() )
        {
          targetPlayer->despawn( actor->getAsPlayer() );
          targetPlayer->spawn( actor->getAsPlayer() );
        }
      }
      break;
    }
    case GmCommand::Time:
    {
      player.setEorzeaTimeOffset( param2 );
      PlayerMgr::sendServerNotice( player, "Eorzea time offset: {0}", param2 );
      break;
    }
    case GmCommand::Weather:
    {
      pTargetZone->setWeatherOverride( static_cast< Common::Weather >( param1 ) );
      PlayerMgr::sendServerNotice( player, "Weather in Territory \"{0}\" of {1} set in range.",
                                   pTargetZone->getName(), targetPlayer->getName() );
      break;
    }
    case GmCommand::Call:
    {
      if( targetPlayer->getTerritoryTypeId() != player.getTerritoryTypeId() )
        targetPlayer->performZoning( player.getTerritoryTypeId(), player.getTerritoryId(), { player.getPos().x, player.getPos().y, player.getPos().z }, player.getRot() );
      else
        targetPlayer->changePosition( player.getPos().x, player.getPos().y, player.getPos().z, player.getRot() );
      PlayerMgr::sendServerNotice( player, "Calling {0}", targetPlayer->getName() );
      break;
    }
    case GmCommand::Inspect:
    {
      PlayerMgr::sendServerNotice( player, "Name: {0}"
                               "\nGil: {1}"
                               "\nTerritory: {2}"
                               "({3})"
                               "\nClass: {4}"
                               "\nLevel: {5}"
                               "\nExp: {6}"
                               "\nSearchMessage: {7}"
                               "\nPlayTime: {8}",
                               targetPlayer->getName(),
                               targetPlayer->getCurrency( CurrencyType::Gil ),
                               pTargetZone->getName(),
                               targetPlayer->getTerritoryTypeId(),
                               static_cast< uint8_t >( targetPlayer->getClass() ),
                               targetPlayer->getLevel(),
                               targetPlayer->getExp(),
                               targetPlayer->getSearchMessage(),
                               targetPlayer->getPlayTime() );
      break;
    }
    case GmCommand::Speed:
    {
      server.queueForPlayer( targetPlayer->getCharacterId(), makeActorControlSelf( player.getId(), Flee, param1 ) );
      PlayerMgr::sendServerNotice( player, "Speed for {0} was set to {1}", targetPlayer->getName(), param1 );
      break;
    }
    case GmCommand::Invis:
    {
      player.setGmInvis( !player.getGmInvis() );
      PlayerMgr::sendServerNotice( player, "Invisibility flag for {0} was toggled to {1}", player.getName(), !player.getGmInvis());

      for( auto actor : player.getInRangeActors() )
      {
        if( actor->isPlayer() )
        {
          targetPlayer->despawn( actor->getAsPlayer() );
          targetPlayer->spawn( actor->getAsPlayer() );
        }
      }
      break;
    }
    case GmCommand::Kill:
    {
      targetActor->getAsChara()->takeDamage( 9999999 );
      PlayerMgr::sendServerNotice( player, "Killed {0}", targetActor->getId());
      break;
    }
    case GmCommand::Icon:
    {
      targetPlayer->setOnlineStatusMask( param1 );

      auto statusPacket = makeZonePacket< FFXIVIpcSetOnlineStatus >( player.getId() );
      statusPacket->data().onlineStatusFlags = param1;
      queueOutPacket( statusPacket );

      auto searchInfoPacket = makeZonePacket< Server::FFXIVIpcSetProfileResult >( player.getId() );
      searchInfoPacket->data().OnlineStatus = param1;
      searchInfoPacket->data().Region = targetPlayer->getSearchSelectRegion();
      strcpy( searchInfoPacket->data().SearchComment, targetPlayer->getSearchMessage() );
      server.queueForPlayer( targetPlayer->getCharacterId(), searchInfoPacket );

      targetPlayer->sendToInRangeSet( makeActorControl( player.getId(), SetStatusIcon,
                                                        static_cast< uint8_t >( player.getOnlineStatus() ) ),
                                      true );
      PlayerMgr::sendServerNotice( player, "Icon for {0} was set to {1}", targetPlayer->getName(), param1 );
      break;
    }
    case GmCommand::Hp:
    {
      auto chara = targetActor->getAsChara();
      if( chara )
      {
        chara->setHp( param1 );
        PlayerMgr::sendServerNotice( player, "Hp for {0} was set to {1}", chara->getName(), param1 );
      }

      break;
    }
    case GmCommand::Mp:
    {
      targetPlayer->setMp( param1 );
      PlayerMgr::sendServerNotice( player, "Mp for {0} was set to {1}", targetPlayer->getName(), param1 );
      break;
    }
    case GmCommand::Tp:
    {
      targetPlayer->setTp( param1 );
      PlayerMgr::sendServerNotice( player, "Tp for {0} was set to {1}", targetPlayer->getName(), param1 );
      break;
    }
    case GmCommand::Gp:
    {
      targetPlayer->setHp( param1 );
      PlayerMgr::sendServerNotice( player, "Gp for {0} was set to {1}", targetPlayer->getName(), param1 );
      break;
    }
    case GmCommand::Exp:
    {
      targetPlayer->gainExp( param1 );
      PlayerMgr::sendServerNotice( player, "{0} Exp was added to {1}", param1, targetPlayer->getName());
      break;
    }
    case GmCommand::Inv:
    {
      if( targetActor->getAsChara()->getInvincibilityType() == Common::InvincibilityType::InvincibilityRefill )
        targetActor->getAsChara()->setInvincibilityType( Common::InvincibilityType::InvincibilityNone );
      else
        targetActor->getAsChara()->setInvincibilityType( Common::InvincibilityType::InvincibilityRefill );

      PlayerMgr::sendServerNotice( player, "Invincibility for {0} was switched.", targetPlayer->getName());
      break;
    }
    case GmCommand::Orchestrion:
    {
      if( param1 == 1 )
      {
        if( param2 == 0 )
        {
          for( uint8_t i = 0; i < 255; i++ )
            targetActor->getAsPlayer()->learnSong( i, 0 );

          PlayerMgr::sendServerNotice( player, "All Songs for {0} were turned on.", targetPlayer->getName());
        }
        else
        {
          targetActor->getAsPlayer()->learnSong( static_cast< uint8_t >( param2 ), 0 );
          PlayerMgr::sendServerNotice( player, "Song {0} for {1} was turned on.", param2, targetPlayer->getName());
        }
      }

      break;
    }
    case GmCommand::Item:
    {
      auto quantity = param2;

      if( quantity < 1 || quantity > 999 )
      {
        quantity = 1;
      }

      if( ( param1 == 0xcccccccc ) )
      {
        PlayerMgr::sendUrgent( player, "Syntaxerror." );
        return;
      }

      if( !targetPlayer->addItem( param1, quantity ) )
        PlayerMgr::sendUrgent( player, "Item #{0} could not be added to inventory.", param1 );
      break;
    }
    case GmCommand::Gil:
    {
      targetPlayer->addCurrency( CurrencyType::Gil, param1 );
      PlayerMgr::sendServerNotice( player, "Added {0} Gil for {1}", param1, targetPlayer->getName() );
      break;
    }
    case GmCommand::Collect:
    {
      uint32_t gil = targetPlayer->getCurrency( CurrencyType::Gil );

      if( gil < param1 )
      {
        PlayerMgr::sendUrgent( player, "Player does not have enough Gil({0})", gil );
      }
      else
      {
        targetPlayer->removeCurrency( CurrencyType::Gil, param1 );
        PlayerMgr::sendServerNotice( player, "Removed {0} Gil from {1} ({2} before)", param1, targetPlayer->getName(), gil );
      }
      break;
    }
    case GmCommand::QuestAccept:
    {
      auto quest = World::Quest( static_cast< uint16_t >( param1 ), 1, 0 );
      targetPlayer->updateQuest( quest );
      break;
    }
    case GmCommand::QuestCancel:
    {
      targetPlayer->removeQuest( static_cast< uint16_t >( param1 ) );
      break;
    }
    case GmCommand::QuestComplete:
    {
      targetPlayer->finishQuest( static_cast< uint16_t >( param1 ) );
      break;
    }
    case GmCommand::QuestIncomplete:
    {
      targetPlayer->unfinishQuest( static_cast< uint16_t >( param1 ) );
      break;
    }
    case GmCommand::QuestSequence:
    {
      auto idx = targetPlayer->getQuestIndex( static_cast< uint16_t >( param1 ) );
      auto quest = targetPlayer->getQuestByIndex( idx );
      quest.setSeq( static_cast< uint8_t >( param2 ) );
      targetPlayer->updateQuest( quest );
      break;
    }
    case GmCommand::GC:
    {
      if( param1 > 3 )
      {
        PlayerMgr::sendUrgent( player, "Invalid Grand Company ID: {0}", param1 );
        return;
      }

      targetPlayer->setGc( static_cast< uint8_t >( param1 ) );

      // if we're changing them to a GC, check if they have a rank and if not, set it to the lowest rank
      if( param1 > 0 )
      {
        auto gcRankIdx = static_cast< uint8_t >( param1 ) - 1;
        if( targetPlayer->getGcRankArray()[ gcRankIdx ] == 0 )
        {
          player.setGcRankAt( static_cast< uint8_t >( gcRankIdx ), 1 );
        }
      }

      PlayerMgr::sendServerNotice( player, "GC for {0} was set to {1}", targetPlayer->getName(), targetPlayer->getGc());
      break;
    }
    case GmCommand::GCRank:
    {
      auto gcId = targetPlayer->getGc() - 1;

      if( gcId > 2 )
      {
        PlayerMgr::sendUrgent( player, "{0} has an invalid Grand Company ID: {0}", targetPlayer->getName(), gcId );
        return;
      }

      targetPlayer->setGcRankAt( static_cast< uint8_t >( gcId ), static_cast< uint8_t >( param1 ) );
      PlayerMgr::sendServerNotice( player, "GC Rank for {0} for GC {1} was set to {2}", targetPlayer->getName(), targetPlayer->getGc(),
                               targetPlayer->getGcRankArray()[ targetPlayer->getGc() - 1 ] );
      break;
    }
    case GmCommand::Aetheryte:
    {
      if( param1 == 0 )
      {
        if( param2 == 0 )
        {
          for( uint8_t i = 0; i < 255; i++ )
            targetActor->getAsPlayer()->registerAetheryte( i );

          PlayerMgr::sendServerNotice( player, "All Aetherytes for {0} were turned on.", targetPlayer->getName() );
        }
        else
        {
          targetActor->getAsPlayer()->registerAetheryte( static_cast< uint8_t >( param2 ) );
          PlayerMgr::sendServerNotice( player, "Aetheryte {0} for {1} was turned on.", param2, targetPlayer->getName() );
        }
      }

      break;
    }
    case GmCommand::Wireframe:
    {
      server.queueForPlayer( player.getCharacterId(),
        std::make_shared< ActorControlSelfPacket >( player.getId(), ActorControlType::ToggleWireframeRendering ) );
      PlayerMgr::sendServerNotice( player, "Wireframe Rendering for {0} was toggled", player.getName());
      break;
    }
    case GmCommand::Teri:
    {
      auto& teriMgr = Common::Service< TerritoryMgr >::ref();
      auto& warpMgr = Common::Service< WarpMgr >::ref();
      if( auto instance = teriMgr.getTerritoryByGuId( param1 ) )
      {
        PlayerMgr::sendDebug( player, "Found instance: {0}, id#{1}", instance->getName(), param1 );

        // if the zone is an instanceContent instance, make sure the player is actually bound to it
        auto pInstance = instance->getAsInstanceContent();

        // pInstance will be nullptr if you're accessing a normal zone via its allocated instance id rather than its zoneid
        if( pInstance && !pInstance->isPlayerBound( player.getId() ) )
        {
          PlayerMgr::sendUrgent( player, "Not able to join instance#{0}", param1 );
          PlayerMgr::sendUrgent( player, "Player not bound! ( run !instance bind <instanceId> first ) {0}", param1 );
          break;
        }
        warpMgr.requestMoveTerritory( player, WarpType::WARP_TYPE_INSTANCE_CONTENT, param1, { 0.f, 0.f, 0.f }, 0.f );
      }
      else if( !teriMgr.isValidTerritory( param1 ) )
      {
        PlayerMgr::sendUrgent( player, "Invalid zone {0}", param1 );
      }
      else
      {
        auto pZone = teriMgr.getZoneByTerritoryTypeId( param1 );
        if( !pZone )
        {
          PlayerMgr::sendUrgent( player, "No zone instance found for {0}", param1 );
          break;
        }

        if( !teriMgr.isDefaultTerritory( param1 ) )
        {
          PlayerMgr::sendUrgent( player, "{0} is an instanced area - instance ID required to zone in.", pZone->getName() );
          break;
        }

        bool doTeleport = false;
        uint16_t teleport;
        auto idList = exdData.getIdList< Excel::Aetheryte >();

        for( auto i : idList )
        {
          auto data = exdData.getRow< Excel::Aetheryte >( i );

          if( !data )
            continue;

          if( data->data().TerritoryType == param1 && data->data().Telepo )
          {
            doTeleport = true;
            teleport = static_cast< uint16_t >( i );
            break;
          }

        }
        if( doTeleport )
        {
          player.teleport( teleport );
        }
        else
        {
          targetPlayer->setPos( targetPlayer->getPos() );
          targetPlayer->performZoning( static_cast< uint16_t >( param1 ), targetPlayer->getTerritoryId(), targetPlayer->getPos(), 0 );
        }

        PlayerMgr::sendServerNotice( player, "{0} was warped to zone {1}", targetPlayer->getName(), param1, pZone->getName() );
      }
      break;
    }
    case GmCommand::Kick:
    {
      // todo: this doesn't kill their session straight away, should do this properly but its good for when you get stuck for now
      targetPlayer->setMarkedForRemoval();

      PlayerMgr::sendServerNotice( player, "Kicked {0}", targetPlayer->getName() );

      break;
    }
    case GmCommand::TeriInfo:
    {
      PlayerMgr::sendServerNotice( player, "ZoneId: {0}"
                               "\nName: {1}"
                               "\nInternalName: {2}"
                               "\nGuId: {3}"
                               "\nPopCount: {4}"
                               "\nCurrentWeather: {5}"
                               "\nNextWeather: {6}",
                               player.getTerritoryTypeId(),
                               pTargetZone->getName(),
                               pTargetZone->getInternalName(),
                               pTargetZone->getGuId(),
                               pTargetZone->getPopCount(),
                               static_cast< uint8_t >( pTargetZone->getCurrentWeather() ),
                               static_cast< uint8_t >( pTargetZone->getNextWeather() ) );
      break;
    }
    case GmCommand::Jump:
    {

      auto inRange = player.getInRangeActors();

      player.changePosition( targetActor->getPos().x, targetActor->getPos().y, targetActor->getPos().z,
                             targetActor->getRot() );

      PlayerMgr::sendServerNotice( player, "Jumping to {0} in range.", targetPlayer->getName());
      break;
    }

    default:
      PlayerMgr::sendUrgent( player, "GM1 Command not implemented: {0}", commandId );
      break;
  }

}

void Sapphire::Network::GameConnection::gmCommandNameHandler( const Packets::FFXIVARR_PACKET_RAW& inPacket, Entity::Player& player )
{
  if( player.getGmRank() <= 0 )
    return;

  auto& server = Common::Service< World::WorldServer >::ref();
  auto& teriMgr = Common::Service< World::Manager::TerritoryMgr >::ref();

  const auto packet = ZoneChannelPacket< Client::FFXIVIpcGmCommandName >( inPacket );

  const auto commandId = packet.data().Id;
  const auto param1 = packet.data().Arg0;
  const auto param2 = packet.data().Arg1;
  const auto param3 = packet.data().Arg2;
  const auto param4 = packet.data().Arg3;
  const auto target = std::string( packet.data().Name );

  Logger::debug( "{0} used GM2 commandId: {1}, params: {2}, {3}, {4}, {5}, target: {6}",
                 player.getName(), commandId, param1, param2, param3, param4, target );

  auto targetSession = server.getSession( target );
  Sapphire::Entity::CharaPtr targetActor;

  if( targetSession != nullptr )
  {
    targetActor = targetSession->getPlayer();
  }
  else
  {
    if( target == "self" )
    {
      targetActor = player.getAsPlayer();
    }
    else
    {
      PlayerMgr::sendUrgent( player, "Player {0} not found on this server.", target );
      return;
    }
  }

  if( !targetActor )
    return;

  auto pTargetActorTerri = teriMgr.getTerritoryByGuId( targetActor->getTerritoryId() );
  auto pPlayerTerri = teriMgr.getTerritoryByGuId( player.getTerritoryId() );

  auto targetPlayer = targetActor->getAsPlayer();

  switch( commandId )
  {
    case GmCommand::Raise:
    {
      targetPlayer->resetHp();
      targetPlayer->resetMp();
      targetPlayer->setStatus( Common::ActorStatus::Idle );
      targetPlayer->sendZoneInPackets( 0x01, true );


      targetPlayer->sendToInRangeSet( makeActorControlSelf( player.getId(), Appear, 0x01, 0x01, 0, 113 ), true );
      targetPlayer->sendToInRangeSet( makeActorControl( player.getId(), SetStatus,
                                                        static_cast< uint8_t >( Common::ActorStatus::Idle ) ),
                                      true );
      PlayerMgr::sendServerNotice( player, "Raised {0}", targetPlayer->getName());
      break;
    }
    default:
      PlayerMgr::sendUrgent( player, "GM2 Command not implemented: {0}", commandId );
      break;
  }

}
