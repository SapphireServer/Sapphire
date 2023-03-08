
#include <Common.h>
#include <Logging/Logger.h>
#include <Util/Util.h>
#include <Util/UtilMath.h>
#include <Exd/ExdData.h>
#include <Network/CommonActorControl.h>
#include <Service.h>
#include <datReader/DatCategories/bg/pcb.h>
#include <datReader/DatCategories/bg/lgb.h>
#include <datReader/DatCategories/bg/sgb.h>
#include "Event/Director.h"
#include "Event/EventDefs.h"
#include "Script/ScriptMgr.h"
#include "WorldServer.h"
#include "Manager/PlayerMgr.h"
#include "Manager/TerritoryMgr.h"
#include "Manager/EventMgr.h"

#include "Actor/Player.h"
#include "Actor/EventObject.h"

#include "Network/PacketWrappers/ActorControlPacket.h"
#include "Network/PacketWrappers/ActorControlSelfPacket.h"

#include "Event/EventHandler.h"

#include "InstanceContent.h"
#include "InstanceObjectCache.h"

#include <Encounter/InstanceContent/IfritNormal.h>


using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets::Server;
using namespace Sapphire::Network::ActorControl;
using namespace Sapphire::World::Manager;

Sapphire::InstanceContent::InstanceContent( std::shared_ptr< Excel::ExcelStruct< Excel::InstanceContent > > pInstanceConfiguration,
                                            std::shared_ptr< Excel::ExcelStruct< Excel::ContentFinderCondition > > pContentFinderCondition,
                                            uint16_t territoryType,
                                            uint32_t guId,
                                            const std::string& internalName,
                                            const std::string& contentName,
                                            uint32_t instanceContentId ) :
  Territory( static_cast< uint16_t >( territoryType ), guId, internalName, contentName ),
  Director( Event::Director::InstanceContent, instanceContentId ),
  m_instanceConfiguration( pInstanceConfiguration ),
  m_contentFinderCondition( pContentFinderCondition ),
  m_instanceContentId( instanceContentId ),
  m_state( Created ),
  m_pEntranceEObj( nullptr ),
  m_instanceCommenceTime( 0 ),
  m_voteState( false ),
  m_currentBgm( pInstanceConfiguration->data().Music ),
  m_instanceExpireTime( Util::getTimeSeconds() + 300 ),
  m_instanceTerminateTime( 0 ),
  m_instanceResetTime( 0 ),
  m_instanceTerminate( false )
{

}

bool Sapphire::InstanceContent::init()
{
  if( !Territory::init() )
    return false;

  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();
  scriptMgr.onInstanceInit( *this );

  // todo: every fight is now ifrit
  m_pEncounter = std::make_shared< IfritEncounterFight >( std::dynamic_pointer_cast< InstanceContent, Territory >( shared_from_this() ) );

  m_pEncounter->init();

  return true;
}


Sapphire::InstanceContent::~InstanceContent()
{

}

uint32_t Sapphire::InstanceContent::getInstanceContentId() const
{
  return m_instanceContentId;
}

std::shared_ptr< Excel::ExcelStruct< Excel::InstanceContent > > Sapphire::InstanceContent::getInstanceConfiguration() const
{
  return m_instanceConfiguration;
}

void Sapphire::InstanceContent::onPlayerZoneIn( Entity::Player& player )
{
  Logger::debug( "InstanceContent::onPlayerZoneIn: Territory#{0}|{1}, Entity#{2}",
                 getGuId(), getTerritoryTypeId(), player.getId() );

  if( isTerminationReady() ) // wtf
  {
    Logger::warn( "Entity#{0} Appear for a terminated instance!", player.getId() );
    player.exitInstance();
    return;
  }

  // mark player as "bound by duty"
  player.setCondition( PlayerCondition::BoundByDuty );

  sendDirectorInit( player );
}

void Sapphire::InstanceContent::onLeaveTerritory( Entity::Player& player )
{
  Logger::debug( "InstanceContent::onLeaveTerritory: Territory#{0}|{1}, Entity#{2}",
                 getGuId(), getTerritoryTypeId(), player.getId() );

  unbindPlayer( player.getId() );

  clearDirector( player );

  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();
  scriptMgr.onInstanceLeaveTerritory( *this, player );
}

void Sapphire::InstanceContent::onUpdate( uint64_t tickCount )
{
  switch( m_state )
  {
    case Created:
    {
      if( !getInstancePlayerCount() )
        return;

      if( m_spawnedPlayers.size() != m_boundPlayerIds.size() )
      {
        return;
      }

      for( auto playerId : m_boundPlayerIds )
      {
        auto it = m_playerMap.find( playerId );
        if( it == m_playerMap.end() )
          return;

        auto pPlayer = it->second;
        if( !pPlayer->isLoadingComplete() ||
            !pPlayer->isDirectorInitialized() ||
                pPlayer->hasCondition( PlayerCondition::WatchingCutscene ) )
          return;
      }

      if( m_instanceCommenceTime == 0 )
      {
        m_instanceCommenceTime = tickCount + instanceStartDelay;
        return;
      }
      else if( tickCount < m_instanceCommenceTime )
        return;

      m_instanceExpireTime = Util::getTimeSeconds() + m_instanceConfiguration->data().Time * 60u;
      sendDutyCommence();

      if( m_pEntranceEObj )
        m_pEntranceEObj->setPermissionInvisibility( 1 );
      m_state = DutyInProgress;

      break;
    }


    case DutyReset:
    {
      // todo: revive players if trial/enclosed raid arena, add reset timer
      if( m_instanceResetTime == 0 )
      {
        //sendDutyReset();
        m_instanceResetTime = tickCount + 3000;
        m_pEncounter->reset();
        for( const auto& playerIt : m_playerMap )
        {
          movePlayerToEntrance( *playerIt.second );
        }
        if( m_pEntranceEObj )
          m_pEntranceEObj->setPermissionInvisibility( 0 );
        return;
      }
      else if( tickCount < m_instanceResetTime )
        return;

      auto& server = Common::Service< World::WorldServer >::ref();
      for( const auto& playerIt : m_playerMap )
      {
        auto player = playerIt.second;
        auto zoneInPacket = makeActorControlSelf( player->getId(), Appear, 0x3, 0, 0, 0 );
        auto setStatusPacket = makeActorControl( player->getId(), SetStatus, static_cast< uint8_t >( Common::ActorStatus::Idle ) );

        server.queueForPlayer( player->getCharacterId(), zoneInPacket );
        server.queueForPlayers( player->getInRangePlayerIds( true ), setStatusPacket );
      }

      m_pEntranceEObj->setPermissionInvisibility( 1 );
      sendForward();
      
      m_state = DutyInProgress;
      break;
    }

    case DutyInProgress:
    {
      // remove 15min timelock to kick & abandon
      if( ( m_instanceCommenceTime + 900000 < tickCount ) && !getVoteState() )
        setVoteState( true );

      if( getExpireValue() == 0 )
        terminate( TerminateReason::TimeExpired );

      if( !getInstancePlayerCount() )
        m_instanceTerminate = true;

      updateBNpcs( tickCount );

      if( m_pEncounter->getEncounterFightStatus() == EncounterFightStatus::FAIL )
        m_state = DutyReset;
      break;
    }


    case DutyFinished:
    {
      if( !getInstancePlayerCount() )
        m_instanceTerminate = true;

      break;
    }

    case Terminate:
    {
      // exit players
      if( ( m_instanceTerminateTime + 3000 ) >= tickCount )
      {
        for( auto playerId : m_boundPlayerIds )
        {
          auto it = m_playerMap.find( playerId );
          if( it == m_playerMap.end() )
            return;

          auto player = it->second;
          player->exitInstance();
          return;
        }
      }
      if( !getInstancePlayerCount() )
        m_instanceTerminate = true;
      return;
    }
  }

  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();
  scriptMgr.onInstanceUpdate( *this, tickCount );

  m_pEncounter->update( tickCount );

  m_lastUpdate = tickCount;
}

void Sapphire::InstanceContent::onEventHandlerOrder( Entity::Player& player, uint32_t arg0, uint32_t arg1,
                                                     uint32_t arg2, uint32_t arg3, uint32_t arg4 )
{
  if( arg0 == getDirectorId() )
  {
    switch( arg1 )
    {
      case EventHandlerOrderId::SheetDataReady:
      {
        break;
      }
      case EventHandlerOrderId::AbortContent:
      {
        switch( arg2 )
        {
          case 0: // Leave content
          {
            player.exitInstance();
            break;
          }
          case 1: // Force leave ( afk timer )
          {
            break;
          }
        }
        break;
      }
      case EventHandlerOrderId::LuaOnStartCutscene:
      {
        Logger::debug( "[{0}] InstanceContent::onEventHandlerOrder: LuaOnStartCutscene {1:X}.",
                       player.getId(), arg1 );

        break;
      }
      case EventHandlerOrderId::VoteRequest:
      {
        Logger::debug( "[{0}] InstanceContent::onEventHandlerOrder: VoteRequest {1}.",
                       player.getId(), arg1 );
        break;
      }
      case EventHandlerOrderId::VoteReplay:
      {
        Logger::debug( "[{0}] InstanceContent::onEventHandlerOrder: VoteReplay {1} Accept {2}.",
                       player.getId(), arg1, arg2 );
        break;
      }
      default:
      {
        Logger::error( "[{0}] InstanceContent::onEventHandlerOrder: Unknown order {1:X}.",
                       player.getId(), arg0 );
        break;
      }
    }
  }
}

void Sapphire::InstanceContent::onInitDirector( Entity::Player& player )
{
  sendDirectorVars( player );
  player.setDirectorInitialized( true );
}

void Sapphire::InstanceContent::onDirectorSync( Entity::Player& player )
{
  auto& server = Common::Service< World::WorldServer >::ref();
  server.queueForPlayer( player.getCharacterId(), makeActorControlSelf( player.getId(), DirectorUpdate, 0x00110001, 0x80000000, 1 ) );
}

void Sapphire::InstanceContent::setVar( uint8_t index, uint8_t value )
{
  setDirectorVar( index, value );

  for( const auto& playerIt : m_playerMap )
  {
    sendDirectorVars( *playerIt.second );
  }
}

void Sapphire::InstanceContent::setSequence( uint8_t value )
{
  setDirectorSequence( value );

  for( const auto& playerIt : m_playerMap )
  {
    sendDirectorVars( *playerIt.second );
  }
}

void Sapphire::InstanceContent::setFlags( uint8_t value )
{
  setDirectorFlags( value );

  for( const auto& playerIt : m_playerMap )
  {
    sendDirectorVars( *playerIt.second );
  }
}

void Sapphire::InstanceContent::startQte()
{
  auto& server = Common::Service< World::WorldServer >::ref();
  for( const auto& playerIt : m_playerMap )
  {
    auto player = playerIt.second;
    server.queueForPlayer( player->getCharacterId(), makeActorControlSelf( player->getId(), DirectorUpdate, getDirectorId(), 0x8000000A ) );
  }
}

void Sapphire::InstanceContent::startEventCutscene()
{
  auto& server = Common::Service< World::WorldServer >::ref();
  // TODO: lock player movement
  for( const auto& playerIt : m_playerMap )
  {
    auto player = playerIt.second;
    server.queueForPlayer( player->getCharacterId(), makeActorControlSelf( player->getId(), DirectorUpdate, getDirectorId(), 0x80000008 ) );
  }
}

void Sapphire::InstanceContent::endEventCutscene()
{
  auto& server = Common::Service< World::WorldServer >::ref();
  for( const auto& playerIt : m_playerMap )
  {
    auto player = playerIt.second;
    server.queueForPlayer( player->getCharacterId(), makeActorControlSelf( player->getId(), DirectorUpdate, getDirectorId(), 0x80000009 ) );
  }
}

void Sapphire::InstanceContent::onAddEObj( Entity::EventObjectPtr object )
{
  if( object->getName() != "none" )
    m_eventObjectMap[ object->getName() ] = object;
  if( object->getObjectId() == 2000182 ) // start
    m_pEntranceEObj = object;

  auto& exdData = Common::Service< Data::ExdData >::ref();
  auto objData = exdData.getRow< Excel::EObj >( object->getObjectId() );
  if( objData )
  {
    m_eventIdToObjectMap[ objData->data().EventHandler ] = object;
  }
  else
    Logger::error( "InstanceContent::onAddEObj Territory " +
                   m_internalName + ": No EObj data found for EObj with ID: " +
                   std::to_string( object->getObjectId() ) );
}

void Sapphire::InstanceContent::sendSharedGroup( uint32_t sharedGroupId, uint32_t timeIndex )
{
  auto& server = Common::Service< World::WorldServer >::ref();
  for( const auto& playerIt : m_playerMap )
  {
    auto player = playerIt.second;
    server.queueForPlayer( player->getCharacterId(), makeActorControlSelf( player->getId(), DirectorUpdate, getDirectorId(),
                                                                              DirectorEventId::SetSharedGroupId, sharedGroupId, timeIndex ) );
  }
}

void Sapphire::InstanceContent::sendInvalidateTodoList()
{
  auto& server = Common::Service< World::WorldServer >::ref();
  for( const auto& playerIt : m_playerMap )
  {
    auto player = playerIt.second;
    server.queueForPlayer( player->getCharacterId(), makeActorControlSelf( player->getId(), DirectorUpdate, getDirectorId(),
                                                                              DirectorEventId::InvalidateTodoList ) );
  }
}

void Sapphire::InstanceContent::sendDutyComplete()
{
  auto& server = Common::Service< World::WorldServer >::ref();
  for( const auto& playerIt : m_playerMap )
  {
    auto player = playerIt.second;
    server.queueForPlayer( player->getCharacterId(), makeActorControlSelf( player->getId(), DirectorUpdate, getDirectorId(),
                                                                              DirectorEventId::DutyComplete, m_instanceConfiguration->data().ClearMusic, 0 ) );
  }
}

void Sapphire::InstanceContent::sendDutyCommence()
{
  auto& server = Common::Service< World::WorldServer >::ref();
  for( const auto& playerIt : m_playerMap )
  {
    auto player = playerIt.second;
    server.queueForPlayer( player->getCharacterId(), makeActorControlSelf( player->getId(), DirectorUpdate, getDirectorId(),
                                                                              DirectorEventId::DutyCommence, getExpireValue() ) );
  }
}

void Sapphire::InstanceContent::sendForward()
{
  auto& server = Common::Service< World::WorldServer >::ref();
  for( const auto& playerIt : m_playerMap )
  {
    auto player = playerIt.second;
    server.queueForPlayer( player->getCharacterId(), makeActorControlSelf( player->getId(), DirectorUpdate, getDirectorId(),
                                                                              DirectorEventId::Forward, getExpireValue() ) );
  }
}

void Sapphire::InstanceContent::sendDutyReset()
{
  auto& server = Common::Service< World::WorldServer >::ref();
  for( const auto& playerIt : m_playerMap )
  {
    auto player = playerIt.second;
    server.queueForPlayer( player->getCharacterId(), makeActorControlSelf( player->getId(), DirectorUpdate, getDirectorId(),
                                                                           DirectorEventId::LoadingScreen, 3000 ) );
  }
}

void Sapphire::InstanceContent::sendVoteState()
{
  auto& server = Common::Service< World::WorldServer >::ref();
  for( const auto& playerIt : m_playerMap )
  {
    auto player = playerIt.second;
    server.queueForPlayer( player->getCharacterId(), makeActorControlSelf( player->getId(), DirectorUpdate, getDirectorId(),
                                                                              DirectorEventId::VoteState, m_voteState ) );
  }
}

void Sapphire::InstanceContent::sendStringendoMode( uint16_t mode )
{
  auto& server = Common::Service< World::WorldServer >::ref();
  for( const auto& playerIt : m_playerMap )
  {
    auto player = playerIt.second;
    server.queueForPlayer( player->getCharacterId(), makeActorControlSelf( player->getId(), DirectorUpdate, getDirectorId(),
                                                                              DirectorEventId::SetStringendoMode, mode ) );
  }
}

bool Sapphire::InstanceContent::hasPlayerPreviouslySpawned( Entity::Player& player ) const
{
  auto it = m_spawnedPlayers.find( player.getId() );
  return it != m_spawnedPlayers.end();
}

Sapphire::InstanceContent::InstanceContentState Sapphire::InstanceContent::getState() const
{
  return m_state;
}

void Sapphire::InstanceContent::movePlayerToEntrance( Sapphire::Entity::Player& player )
{
  auto& exdData = Common::Service< Data::ExdData >::ref();
  auto& instanceObjectCache = Common::Service< InstanceObjectCache >::ref();
  auto contentInfo = exdData.getRow< Excel::InstanceContent >( m_instanceContentId );

  auto rect = instanceObjectCache.getEventRange( contentInfo->data().EntranceRect );

  if( m_pEntranceEObj != nullptr )
  {
    if( rect )
      player.setRot( Util::eulerToDirection( { rect->header.transform.rotation.x, rect->header.transform.rotation.y, rect->header.transform.rotation.z } ) );
    else
      player.setRot( PI );
    player.setPos( m_pEntranceEObj->getPos() );
  }
  else if( rect )
  {
    player.setRot( Util::eulerToDirection( { rect->header.transform.rotation.x, rect->header.transform.rotation.y, rect->header.transform.rotation.z } ) );
    player.setPos( { rect->header.transform.translation.x, rect->header.transform.translation.y, rect->header.transform.translation.z } );
  }
  else
  {
    player.setRot( PI );
    player.setPos( { 0.f, 0.f, 0.f } );
  }
}

void Sapphire::InstanceContent::onBeforePlayerZoneIn( Sapphire::Entity::Player& player )
{
  // remove any players from the instance who aren't bound on zone in
  if( !isPlayerBound( player.getId() ) )
    player.exitInstance();

  // if a player has already spawned once inside this instance, don't move them if they happen to zone in again
  if( !hasPlayerPreviouslySpawned( player ) )
  {
    movePlayerToEntrance( player );
  }

  player.resetObjSpawnIndex();
}

Sapphire::Entity::EventObjectPtr Sapphire::InstanceContent::getEObjByName( const std::string& name )
{
  auto it = m_eventObjectMap.find( name );
  if( it == m_eventObjectMap.end() )
    return nullptr;

  return it->second;
}

void Sapphire::InstanceContent::onTalk( Sapphire::Entity::Player& player, uint32_t eventId, uint64_t actorId )
{
  // todo: handle exit (and maybe shortcut?) behaviour here

  /*auto it = m_eventIdToObjectMap.find( eventId );
  if( it == m_eventIdToObjectMap.end() )
    return;

  if( auto onTalk = it->second->getOnTalkHandler() )
    onTalk( player, it->second, getAsInstanceContent(), actorId );
  else
    PlayerMgr::sendDebug( player, "No onTalk handler found for interactable eobj with EObjID#{0}, eventId#{1}",
                          it->second->getObjectId(), eventId );*/
                        
  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();
  scriptMgr.onTalk( player, actorId, eventId );
}

void
Sapphire::InstanceContent::onEnterTerritory( Entity::Player& player, uint32_t eventId, uint16_t param1, uint16_t param2 )
{
  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();
  auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();
  scriptMgr.onInstanceEnterTerritory( *this, player, eventId, param1, param2 );

  if( !hasPlayerPreviouslySpawned( player ) )
  {
    m_spawnedPlayers.insert( player.getId() );
    eventMgr.playScene( player, getDirectorId(), DirectorSceneId::SetupEventArgsOnStart, NO_DEFAULT_CAMERA | CONDITION_CUTSCENE |
                        HIDE_HOTBAR | SILENT_ENTER_TERRI_BGM | SILENT_ENTER_TERRI_SE | SILENT_ENTER_TERRI_ENV |
                        DISABLE_STEALTH | 0x00100000 | LOCK_HUD | LOCK_HOTBAR | DISABLE_CANCEL_EMOTE,
                       { 0/*bgm*/, 0/*StringendoMode*/, 0/*Unknown*/, 0/*Option param*/, 0/*Unknown*/,
                        getOptionFlags()/*Option bitFlag*/ } );
  }
  else
  {
    eventMgr.playScene( player, getDirectorId(), DirectorSceneId::SetupEventArgsInProgress, NO_DEFAULT_CAMERA | HIDE_HOTBAR,
                        { getCurrentBGM()/*bgm*/, 0/*StringendoMode*/, 0/*Unknown*/, 0/*Option param*/,
                        0/*Unknown*/, getOptionFlags(),/*Option bitFlag*/ getExpireValue() /*Time remaining*/ } );
  }
}

void Sapphire::InstanceContent::setCurrentBGM( uint16_t bgmIndex )
{
  auto& server = Common::Service< World::WorldServer >::ref();
  m_currentBgm = bgmIndex;

  for( const auto& playerIt : m_playerMap )
  {
    auto player = playerIt.second;
    server.queueForPlayer( player->getCharacterId(),
      makeActorControlSelf( player->getId(), DirectorUpdate, getDirectorId(),
                            DirectorEventId::BattleGroundMusic, bgmIndex ) );
  }
}

void Sapphire::InstanceContent::setPlayerBGM( Sapphire::Entity::Player& player, uint16_t bgmId )
{
  auto& server = Common::Service< World::WorldServer >::ref();
  server.queueForPlayer( player.getCharacterId(), makeActorControlSelf( player.getId(), DirectorUpdate, getDirectorId(),
                                                                           DirectorEventId::BattleGroundMusic, bgmId ) );
}

uint16_t Sapphire::InstanceContent::getCurrentBGM() const
{
  return m_currentBgm;
}

void Sapphire::InstanceContent::setVoteState( bool state )
{
  m_voteState = state;
  sendVoteState();
}

bool Sapphire::InstanceContent::getVoteState() const
{
  return m_voteState;
}

bool Sapphire::InstanceContent::bindPlayer( uint32_t playerId )
{
  // if player already bound, return false
  if( m_boundPlayerIds.count( playerId ) )
    return false;

  // TODO: do not allow binding of players if instance already has all it can take
  // if( m_boundPlayerIds.size() >= party restrictions )
  //    return false;

  m_boundPlayerIds.insert( playerId );
  return true;
}

bool Sapphire::InstanceContent::isPlayerBound( uint32_t playerId ) const
{
  return m_boundPlayerIds.count( playerId ) > 0;
}

void Sapphire::InstanceContent::unbindPlayer( uint32_t playerId )
{
  m_boundPlayerIds.erase( playerId );

  auto it = m_playerMap.find( playerId );
  if( it != m_playerMap.end() )
    it->second->exitInstance();
}

void Sapphire::InstanceContent::clearDirector( Entity::Player& player )
{
  sendDirectorClear( player );

  player.setDirectorInitialized( false );
  // remove "bound by duty" state
  player.removeCondition( PlayerCondition::BoundByDuty );
}

uint32_t Sapphire::InstanceContent::getExpireValue()
{
  auto timeNow = Util::getTimeSeconds();
  auto remain = m_instanceExpireTime - timeNow;
  if( remain > static_cast< uint32_t >( m_instanceConfiguration->data().Time * 60 ) )
    return 0;
  return remain;
}

uint32_t Sapphire::InstanceContent::getOptionFlags()
{
  uint32_t bitFlag = 0;

  auto& exdData = Common::Service< Data::ExdData >::ref();
  auto contentInfo = exdData.getRow< Excel::ContentMemberType >( m_contentFinderCondition->data().ContentMemberType );

  if( contentInfo->data().PartyMemberCount == 1 )
    bitFlag |= 1;

  if( getVoteState() )
    bitFlag |= 4;

  bitFlag |= 0x80;

  return bitFlag;
}

void Sapphire::InstanceContent::terminate( uint8_t reason )
{
  if( reason == TerminateReason::TimeExpired || reason == TerminateReason::TimeLimitReached )
    sendDutyFailed( true );
  else
    sendDutyFailed( false );

  m_instanceTerminateTime = Util::getTimeMs();
  m_state = InstanceContentState::Terminate;
}

bool Sapphire::InstanceContent::isTerminationReady() const
{
  return m_instanceTerminate && m_boundPlayerIds.empty();
}

void Sapphire::InstanceContent::sendDutyFailed( bool force )
{
  auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();

  for( const auto& playerIt : m_playerMap )
  {
    auto player = playerIt.second;
    eventMgr.eventStart( *player, player->getId(), getDirectorId(), Event::EventHandler::EventType::GameProgress, 0, 0 );
    eventMgr.playScene( *player, getDirectorId(), DirectorSceneId::DutyFailed,
                        NO_DEFAULT_CAMERA | CONDITION_CUTSCENE |
                        HIDE_HOTBAR | SILENT_ENTER_TERRI_BGM | SILENT_ENTER_TERRI_SE | SILENT_ENTER_TERRI_ENV |
                        DISABLE_STEALTH | 0x00100000 | LOCK_HUD | LOCK_HOTBAR | DISABLE_CANCEL_EMOTE,
                        { 1 }, nullptr );
  }
}

void Sapphire::InstanceContent::setExpireValue( uint32_t value )
{
  m_instanceExpireTime = Util::getTimeSeconds() + value;
}

size_t Sapphire::InstanceContent::getInstancePlayerCount() const
{
  return m_boundPlayerIds.size();
}
