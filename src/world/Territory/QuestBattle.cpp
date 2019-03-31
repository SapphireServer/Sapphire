
#include <Common.h>
#include <Logging/Logger.h>
#include <Util/Util.h>
#include <Util/UtilMath.h>
#include <Exd/ExdDataGenerated.h>
#include <Network/CommonActorControl.h>

#include "Event/Director.h"
#include "Event/EventDefs.h"
#include "Script/ScriptMgr.h"

#include "Actor/Player.h"
#include "Actor/EventObject.h"

#include "Network/PacketWrappers/ActorControlPacket142.h"
#include "Network/PacketWrappers/ActorControlPacket143.h"


#include "Event/EventHandler.h"

#include "QuestBattle.h"
#include "Framework.h"

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;
using namespace Sapphire::Network::ActorControl;

Sapphire::QuestBattle::QuestBattle( std::shared_ptr< Sapphire::Data::QuestBattle > pBattleDetails,
                                    uint16_t territoryType,
                                    uint32_t guId,
                                    const std::string& internalName,
                                    const std::string& contentName,
                                    uint32_t questBattleId,
                                    FrameworkPtr pFw ) :
  Zone( static_cast< uint16_t >( territoryType ), guId, internalName, contentName, pFw ),
  Director( Event::Director::QuestBattle, questBattleId ),
  m_pBattleDetails( pBattleDetails ),
  m_questBattleId( questBattleId ),
  m_state( Created ),
  m_instanceCommenceTime( 0 )
 // m_currentBgm( pInstanceConfiguration->bGM )
{

}

bool Sapphire::QuestBattle::init()
{
  auto pScriptMgr = m_pFw->get< Scripting::ScriptMgr >();
  pScriptMgr->onInstanceInit( getAsQuestBattle() );

  return true;
}


Sapphire::QuestBattle::~QuestBattle()
{

}

uint32_t Sapphire::QuestBattle::getQuestBattleId() const
{
  return m_questBattleId;
}

Sapphire::Data::ExdDataGenerated::QuestBattlePtr Sapphire::QuestBattle::getQuestBattleDetails() const
{
  return m_pBattleDetails;
}

void Sapphire::QuestBattle::onPlayerZoneIn( Entity::Player& player )
{
  Logger::debug( "QuestBattle::onPlayerZoneIn: Zone#{0}|{1}, Entity#{2}",
                 getGuId(), getTerritoryTypeId(), player.getId() );

  // mark player as "bound by duty"
  player.setStateFlag( PlayerStateFlag::BoundByDuty );

  // if the instance was not started yet, director init is sent on enter event.
  // else it will be sent on finish loading.
  if( m_state == Created )
    sendDirectorInit( player );

}

void Sapphire::QuestBattle::onLeaveTerritory( Entity::Player& player )
{
  Logger::debug( "QuestBattle::onLeaveTerritory: Zone#{0}|{1}, Entity#{2}",
                 getGuId(), getTerritoryTypeId(), player.getId() );

  clearDirector( player );
}

void Sapphire::QuestBattle::onUpdate( uint32_t currTime )
{
  switch( m_state )
  {
    case Created:
    {
      if( m_boundPlayerId == 0 )
        return;

      auto it = m_playerMap.find( m_boundPlayerId );
      if( it == m_playerMap.end() )
        return;

      auto player = it->second;
      if( !player->isLoadingComplete() ||
          !player->isDirectorInitialized() ||
          !player->isOnEnterEventDone() ||
          player->hasStateFlag( PlayerStateFlag::WatchingCutscene ) )
        return;

      if( m_instanceCommenceTime == 0 )
      {
        m_instanceCommenceTime = Util::getTimeMs() + instanceStartDelay;
        return;
      }
      else if( Util::getTimeMs() < m_instanceCommenceTime )
        return;

      // TODO: we do not have a list of players for questbattles... just one
      for( const auto& playerIt : m_playerMap )
      {
        auto pPlayer = playerIt.second;
        pPlayer->sendDebug( " ALL DONE LOADING " );
      }

      m_state = DutyInProgress;
      m_instanceExpireTime = Util::getTimeSeconds() + ( m_pBattleDetails->timeLimit * 60u );
      break;
    }


    case DutyReset:
      break;

    case DutyInProgress:
    {
      break;
    }


    case DutyFinished:
      break;
  }

  auto pScriptMgr = m_pFw->get< Scripting::ScriptMgr >();
  pScriptMgr->onInstanceUpdate( getAsQuestBattle(), currTime );
}

void Sapphire::QuestBattle::onFinishLoading( Entity::Player& player )
{

}

void Sapphire::QuestBattle::onInitDirector( Entity::Player& player )
{
  player.sendQuestMessage( getDirectorId(), 0, 2, Util::getTimeSeconds(), 0x0708 );
  sendDirectorVars( player );
  player.setDirectorInitialized( true );
}

void Sapphire::QuestBattle::onDirectorSync( Entity::Player& player )
{
  player.queuePacket( makeActorControl143( player.getId(), DirectorUpdate, 0x00110001, 0x80000000, 1 ) );
}

void Sapphire::QuestBattle::setVar( uint8_t index, uint8_t value )
{
  if( index > 19 )
    return;

  switch( index )
  {
    case 0:
      setDirectorUI8AL( value );
      break;
    case 1:
      setDirectorUI8AH( value );
      break;
    case 2:
      setDirectorUI8BL( value );
      break;
    case 3:
      setDirectorUI8BH( value );
      break;
    case 4:
      setDirectorUI8CL( value );
      break;
    case 5:
      setDirectorUI8CH( value );
      break;
    case 6:
      setDirectorUI8DL( value );
      break;
    case 7:
      setDirectorUI8DH( value );
      break;
    case 8:
      setDirectorUI8EL( value );
      break;
    case 9:
      setDirectorUI8EH( value );
      break;
    case 10:
      setDirectorUI8FL( value );
      break;
    case 11:
      setDirectorUI8FH( value );
      break;
    case 12:
      setDirectorUI8GL( value );
      break;
    case 13:
      setDirectorUI8GH( value );
      break;
    case 14:
      setDirectorUI8HL( value );
      break;
    case 15:
      setDirectorUI8HH( value );
      break;
    case 16:
      setDirectorUI8IL( value );
      break;
    case 17:
      setDirectorUI8IH( value );
      break;
    case 18:
      setDirectorUI8JL( value );
      break;
    case 19:
      setDirectorUI8JH( value );
      break;

  }

  // todo: genericise this?
  for( const auto& playerIt : m_playerMap )
  {
    sendDirectorVars( *playerIt.second );
  }
}

void Sapphire::QuestBattle::setSequence( uint8_t value )
{
  setDirectorSequence( value );

  for( const auto& playerIt : m_playerMap )
  {
    sendDirectorVars( *playerIt.second );
  }
}

void Sapphire::QuestBattle::setBranch( uint8_t value )
{
  setDirectorBranch( value );

  for( const auto& playerIt : m_playerMap )
  {
    sendDirectorVars( *playerIt.second );
  }
}

void Sapphire::QuestBattle::startQte()
{
  for( const auto& playerIt : m_playerMap )
  {
    auto player = playerIt.second;
    player->queuePacket( makeActorControl143( player->getId(), DirectorUpdate, getDirectorId(), 0x8000000A ) );
  }
}

void Sapphire::QuestBattle::startEventCutscene()
{
  // TODO: lock player movement
  for( const auto& playerIt : m_playerMap )
  {
    auto player = playerIt.second;
    player->queuePacket( makeActorControl143( player->getId(), DirectorUpdate, getDirectorId(), 0x80000008 ) );
  }
}

void Sapphire::QuestBattle::endEventCutscene()
{
  for( const auto& playerIt : m_playerMap )
  {
    auto player = playerIt.second;
    player->queuePacket( makeActorControl143( player->getId(), DirectorUpdate, getDirectorId(), 0x80000009 ) );
  }
}

void Sapphire::QuestBattle::onRegisterEObj( Entity::EventObjectPtr object )
{
  if( object->getName() != "none" )
    m_eventObjectMap[ object->getName() ] = object;

  auto pExdData = m_pFw->get< Data::ExdDataGenerated >();
  auto objData = pExdData->get< Sapphire::Data::EObj >( object->getObjectId() );
  if( objData )
    // todo: data should be renamed to eventId
    m_eventIdToObjectMap[ objData->data ] = object;
  else
    Logger::error( "InstanceContent::onRegisterEObj Zone " +
                   m_internalName + ": No EObj data found for EObj with ID: " +
                   std::to_string( object->getObjectId() ) );
}

Sapphire::Event::Director::DirectorState Sapphire::QuestBattle::getState() const
{
  return m_state;
}

void Sapphire::QuestBattle::onBeforePlayerZoneIn( Sapphire::Entity::Player& player )
{
  // remove any players from the instance who aren't bound on zone in
  if( !isPlayerBound( player.getId() ) )
    player.exitInstance();

  // TODO: let script set start position??
  player.setRot( PI );
  player.setPos( { 0.f, 0.f, 0.f } );


  player.resetObjSpawnIndex();
}

Sapphire::Entity::EventObjectPtr Sapphire::QuestBattle::getEObjByName( const std::string& name )
{
  auto it = m_eventObjectMap.find( name );
  if( it == m_eventObjectMap.end() )
    return nullptr;

  return it->second;
}

void Sapphire::QuestBattle::onTalk( Sapphire::Entity::Player& player, uint32_t eventId, uint64_t actorId )
{
  // todo: handle exit (and maybe shortcut?) behaviour here

  auto it = m_eventIdToObjectMap.find( eventId );
  if( it == m_eventIdToObjectMap.end() )
    return;

  if( auto onTalkHandler = it->second->getOnTalkHandler() )
    onTalkHandler( player, it->second, getAsQuestBattle(), actorId );
  else
    player.sendDebug( "No onTalk handler found for interactable eobj with EObjID#{0}, eventId#{1}  ",
                      it->second->getObjectId(), eventId );
}

void
Sapphire::QuestBattle::onEnterTerritory( Entity::Player& player, uint32_t eventId, uint16_t param1, uint16_t param2 )
{
  auto pScriptMgr = m_pFw->get< Scripting::ScriptMgr >();
  pScriptMgr->onInstanceEnterTerritory( getAsQuestBattle(), player, eventId, param1, param2 );

  // TODO: this may or may not be correct for questbattles
  player.playScene( getDirectorId(), 1, NO_DEFAULT_CAMERA | CONDITION_CUTSCENE | SILENT_ENTER_TERRI_ENV |
                                        HIDE_HOTBAR | SILENT_ENTER_TERRI_BGM | SILENT_ENTER_TERRI_SE |
                                        DISABLE_STEALTH | 0x00100000 | LOCK_HUD | LOCK_HOTBAR |
                                        // todo: wtf is 0x00100000
                                        DISABLE_CANCEL_EMOTE, 0 );

}

void Sapphire::QuestBattle::setCurrentBGM( uint16_t bgmIndex )
{
  m_currentBgm = bgmIndex;

  for( const auto& playerIt : m_playerMap )
  {
    auto player = playerIt.second;
    // note: retail do send a BGM_MUTE(1) first before any BGM transition, but YOLO in this case.
    // also do note that this code can't control the bgm granularly. (i.e. per player for WoD submap.) oops.
    // player->queuePacket( ActorControlPacket143( player->getId(), DirectorUpdate, getDirectorId(), 0x80000001, 1 ) );
    player->queuePacket(
      makeActorControl143( player->getId(), DirectorUpdate, getDirectorId(), 0x80000001, bgmIndex ) );
  }
}

void Sapphire::QuestBattle::setPlayerBGM( Sapphire::Entity::Player& player, uint16_t bgmId )
{
  player.queuePacket( makeActorControl143( player.getId(), DirectorUpdate, getDirectorId(), 0x80000001, bgmId ) );
}

uint16_t Sapphire::QuestBattle::getCurrentBGM() const
{
  return m_currentBgm;
}

bool Sapphire::QuestBattle::bindPlayer( uint32_t playerId )
{
  // if player already bound, return false
  if( m_boundPlayerId != 0 )
    return false;

  m_boundPlayerId = playerId;
  return true;
}

bool Sapphire::QuestBattle::isPlayerBound( uint32_t playerId ) const
{
  return m_boundPlayerId == playerId;
}

void Sapphire::QuestBattle::unbindPlayer( uint32_t playerId )
{
  if( m_boundPlayerId != playerId )
    return;

  auto it = m_playerMap.find( playerId );
  if( it != m_playerMap.end() )
    it->second->exitInstance();
}

void Sapphire::QuestBattle::clearDirector( Entity::Player& player )
{
  sendDirectorClear( player );

  player.setDirectorInitialized( false );
  // remove "bound by duty" state
  player.unsetStateFlag( PlayerStateFlag::BoundByDuty );
}
