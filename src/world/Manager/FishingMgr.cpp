#include <Common.h>
#include <Logging/Logger.h>
#include <Service.h>
#include <Util/Util.h>

#include "FishingMgr.h"
#include "EventMgr.h"
#include "PlayerMgr.h"

#include "Actor/Player.h"
#include "Event/EventDefs.h"

using namespace Sapphire::World::Manager;

bool FishingMgr::isFishing( uint64_t characterId ) const
{
  return m_sessions.find( characterId ) != m_sessions.end();
}

void FishingMgr::startFishing( Entity::Player& player )
{
  const auto characterId = player.getCharacterId();
  if( isFishing( characterId ) )
  {
    Logger::debug( "[FishingMgr] Player {} attempted to start fishing while already active.", characterId );
    return;
  }

  auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();

  if( player.getEvent( PrototypeEventId ) )
  {
    Logger::debug( "[FishingMgr] Player {} had stale fishing event {}, cleaning up before restart.",
                   characterId, PrototypeEventId );
    eventMgr.eventFinish( player, PrototypeEventId, 1 );
  }

  Session session;
  session.state = FishingState::CastingOut; // todo: depends on whether player uses Cast or other fishing action
  session.startedAtMs = Common::Util::getTimeMs();
  session.stateChangedAtMs = session.startedAtMs;
  m_sessions[ characterId ] = session;

  player.setStatus( Common::ActorStatus::Gathering );
  player.setCondition( Common::PlayerCondition::Gathering );

  eventMgr.eventStart( player, player.getId(), PrototypeEventId, Event::EventHandler::Fishing, EventStartFlags,
                       EventStartArg,
                       [this]( Entity::Player& cbPlayer, uint64_t )
                       {
                         cleanupSession( cbPlayer, true );
                       } );

  // eventStart unconditionally sets InNpcEvent which greys out the hotbar;
  // fishing must allow the player to act (quit, hook, etc.) so remove it.
  player.removeCondition( Common::PlayerCondition::InNpcEvent );

  Logger::debug( "[FishingMgr] Player {} start -> event {} scene {}", characterId, PrototypeEventId,
                 static_cast< uint32_t >( FishingState::CastingOut ) );

  eventMgr.playScene( player, PrototypeEventId, static_cast< uint32_t >( FishingState::CastingOut ), SceneFlags, { 3u, 275u, 278u, 0u },
                      [this]( Entity::Player& cbPlayer, const Event::SceneResult& result )
                      {
                        onCastSceneReturn( cbPlayer, result );
                      } );
}

void FishingMgr::quitFishing( Entity::Player& player )
{
  const auto characterId = player.getCharacterId();
  auto sessionIt = m_sessions.find( characterId );
  if( sessionIt == m_sessions.end() )
  {
    Logger::debug( "[FishingMgr] Player {} attempted to quit fishing while inactive.", characterId );
    if( player.hasCondition( Common::PlayerCondition::Fishing ) )
      player.removeCondition( Common::PlayerCondition::Fishing );
    if( player.hasCondition( Common::PlayerCondition::Gathering ) )
      player.removeCondition( Common::PlayerCondition::Gathering );
    player.setStatus( Common::ActorStatus::Idle );
    return;
  }

  sessionIt->second.state = FishingState::Quitting;

  auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();

  if( !player.getEvent( PrototypeEventId ) )
  {
    Logger::debug( "[FishingMgr] Player {} quit with no active event instance; cleaning session only.",
                   characterId );
    cleanupSession( player, true );
    return;
  }

  Logger::debug( "[FishingMgr] Player {} quit -> event {} scene {}", characterId, PrototypeEventId,
                 static_cast< uint32_t >( FishingState::Quitting ) );

  eventMgr.playScene( player, PrototypeEventId, static_cast< uint32_t >( FishingState::Quitting ), SceneFlags, { 1u, 273u, 0u, 0u },
                      [this]( Entity::Player& cbPlayer, const Event::SceneResult& result )
                      {
                        onQuitSceneReturn( cbPlayer, result );
                      } );
}

void FishingMgr::onCastSceneReturn( Entity::Player& player, const Event::SceneResult& result )
{
  if( result.eventId != PrototypeEventId )
    return;

  const auto characterId = player.getCharacterId();
  auto sessionIt = m_sessions.find( characterId );
  if( sessionIt == m_sessions.end() )
    return;

  Logger::debug( "[FishingMgr] Player {} cast scene returned, advancing to PullingPoleIn.", characterId );

  // Client confirmed the cast – now trigger PullingPoleIn (scene 2) so the rod
  // settles.  The client will return this scene to request the next transition.
  sessionIt->second.state = FishingState::PullingPoleIn;
  sessionIt->second.stateChangedAtMs = Common::Util::getTimeMs();

  player.setCondition( Common::PlayerCondition::Fishing );

  auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();
  eventMgr.playScene( player, PrototypeEventId, static_cast< uint32_t >( FishingState::PullingPoleIn ), SceneFlags,
                      { 2u, 283u, 271u, 0u },
                      [this]( Entity::Player& cbPlayer, const Event::SceneResult& cbResult )
                      {
                        onRestSceneReturn( cbPlayer, cbResult );
                      } );
}

void FishingMgr::onRestSceneReturn( Entity::Player& player, const Event::SceneResult& result )
{
  if( result.eventId != PrototypeEventId )
    return;

  const auto characterId = player.getCharacterId();
  auto sessionIt = m_sessions.find( characterId );
  if( sessionIt == m_sessions.end() )
    return;

  Logger::debug( "[FishingMgr] Player {} rest scene returned, advancing to pole ready.", characterId );

  player.setCondition( Common::PlayerCondition::Fishing );
  player.setStatus( Common::ActorStatus::Gathering );

  sessionIt->second.state = FishingState::PoleReady;
  sessionIt->second.stateChangedAtMs = Common::Util::getTimeMs();

  auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();
  eventMgr.playScene( player, PrototypeEventId, static_cast< uint32_t >( FishingState::PoleReady ), SceneFlags,
                      { 3u, 271u, 0u, 0u },
                      [this]( Entity::Player& cbPlayer, const Event::SceneResult& cbResult )
                      {
                        onPoleReadySceneReturn( cbPlayer, cbResult );
                      } );
}

void FishingMgr::onPoleReadySceneReturn( Entity::Player& player, const Event::SceneResult& result )
{
  if( result.eventId != PrototypeEventId )
    return;

  Logger::debug( "[FishingMgr] Player {} pole ready scene returned, keeping event alive.",
                 player.getCharacterId() );

  // PoleReady is the idle fishing state; keep the event alive.
  auto pEvent = player.getEvent( PrototypeEventId );
  if( pEvent )
    pEvent->setPlayedScene( true );
}

void FishingMgr::onQuitSceneReturn( Entity::Player& player, const Event::SceneResult& result )
{
  if( result.eventId != PrototypeEventId )
    return;

  auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();

  if( player.getEvent( PrototypeEventId ) )
  {
    Logger::debug( "[FishingMgr] Player {} quit scene returned; finishing event {}.",
                   player.getCharacterId(), PrototypeEventId );
    eventMgr.eventFinish( player, PrototypeEventId, 1 );
  }

  cleanupSession( player, true );
}

void FishingMgr::cleanupSession( Entity::Player& player, bool setIdle )
{
  m_sessions.erase( player.getCharacterId() );

  if( player.hasCondition( Common::PlayerCondition::Fishing ) )
    player.removeCondition( Common::PlayerCondition::Fishing );

  if( player.hasCondition( Common::PlayerCondition::Gathering ) )
    player.removeCondition( Common::PlayerCondition::Gathering );

  if( setIdle )
    player.setStatus( Common::ActorStatus::Idle );
}

void FishingMgr::onFishingActionRequest( Entity::Player& player, uint32_t actionId, uint16_t requestId,
                                         uint64_t targetId )
{
  Logger::debug( "[FishingMgr] Fishing action request: player={} actionId={} requestId={} targetId={}",
                 player.getCharacterId(), actionId, requestId, targetId );
}

void FishingMgr::onStartActionResultEvent( Entity::Player& player, uint32_t arg0, uint32_t arg1,
                                           uint32_t arg2, uint32_t arg3 )
{
  Logger::debug( "[FishingMgr] StartActionResultEvent: player={} a0={} a1={} a2={} a3={}",
                 player.getCharacterId(), arg0, arg1, arg2, arg3 );
}
