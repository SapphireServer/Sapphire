
#include <Common.h>
#include <Logging/Logger.h>
#include <Util/Util.h>
#include <Util/UtilMath.h>
#include <Exd/ExdDataGenerated.h>
#include <Network/CommonActorControl.h>
#include <Service.h>

#include "Event/Director.h"
#include "Event/EventDefs.h"
#include "Script/ScriptMgr.h"

#include "Actor/Player.h"
#include "Actor/EventObject.h"

#include "Network/PacketWrappers/ActorControlPacket.h"
#include "Network/PacketWrappers/ActorControlSelfPacket.h"


#include "Event/EventHandler.h"

#include "InstanceContent.h"

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;
using namespace Sapphire::Network::ActorControl;

Sapphire::InstanceContent::InstanceContent( std::shared_ptr< Sapphire::Data::InstanceContent > pInstanceConfiguration,
                                            uint16_t territoryType,
                                            uint32_t guId,
                                            const std::string& internalName,
                                            const std::string& contentName,
                                            uint32_t instanceContentId, uint16_t contentFinderConditionId ) :
  Territory( static_cast< uint16_t >( territoryType ), guId, internalName, contentName ),
  Director( Event::Director::InstanceContent, instanceContentId, contentFinderConditionId ),
  m_instanceConfiguration( pInstanceConfiguration ),
  m_instanceContentId( instanceContentId ),
  m_state( Created ),
  m_pEntranceEObj( nullptr ),
  m_instanceCommenceTime( 0 ),
  m_currentBgm( pInstanceConfiguration->bGM )
{

}

bool Sapphire::InstanceContent::init()
{
  if( !Territory::init() )
    return false;

  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();
  scriptMgr.onInstanceInit( getAsInstanceContent() );

  return true;
}


Sapphire::InstanceContent::~InstanceContent()
{

}

uint32_t Sapphire::InstanceContent::getInstanceContentId() const
{
  return m_instanceContentId;
}

Sapphire::Data::ExdDataGenerated::InstanceContentPtr Sapphire::InstanceContent::getInstanceConfiguration() const
{
  return m_instanceConfiguration;
}

void Sapphire::InstanceContent::onPlayerZoneIn( Entity::Player& player )
{
  Logger::debug( "InstanceContent::onPlayerZoneIn: Territory#{0}|{1}, Entity#{2}",
                 getGuId(), getTerritoryTypeId(), player.getId() );

  // mark player as "bound by duty"
  player.setStateFlag( PlayerStateFlag::BoundByDuty );

  sendDirectorInit( player );
}

void Sapphire::InstanceContent::onLeaveTerritory( Entity::Player& player )
{
  Logger::debug( "InstanceContent::onLeaveTerritory: Territory#{0}|{1}, Entity#{2}",
                 getGuId(), getTerritoryTypeId(), player.getId() );

  clearDirector( player );
}

void Sapphire::InstanceContent::onUpdate( uint64_t tickCount )
{
  switch( m_state )
  {
    case Created:
    {
      if( m_boundPlayerIds.empty() )
        return;

      for( auto playerId : m_boundPlayerIds )
      {
        auto it = m_playerMap.find( playerId );
        if( it == m_playerMap.end() )
          return;

        auto player = it->second;
        if( !player->isLoadingComplete() ||
            !player->isDirectorInitialized() ||
            !player->isOnEnterEventDone() ||
            player->hasStateFlag( PlayerStateFlag::WatchingCutscene ) )
          return;
      }

      if( m_instanceCommenceTime == 0 )
      {
        m_instanceCommenceTime = tickCount + instanceStartDelay;
        return;
      }
      else if( tickCount < m_instanceCommenceTime )
        return;

      for( const auto& playerIt : m_playerMap )
      {
        auto pPlayer = playerIt.second;
        pPlayer->queuePacket( makeActorControlSelf( pPlayer->getId(), DirectorUpdate,
                                                    getDirectorId(), 0x40000001,
                                                    m_instanceConfiguration->timeLimitmin * 60u ) );
      }

      if( m_pEntranceEObj )
        m_pEntranceEObj->setState( 7 );
      m_state = DutyInProgress;
      m_instanceExpireTime = Util::getTimeSeconds() + ( m_instanceConfiguration->timeLimitmin * 60u );
      break;
    }


    case DutyReset:
      break;

    case DutyInProgress:
    {
      updateBNpcs( tickCount );
      break;
    }


    case DutyFinished:
      break;
  }

  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();
  scriptMgr.onInstanceUpdate( getAsInstanceContent(), tickCount );

  m_lastUpdate = tickCount;
}

void Sapphire::InstanceContent::onFinishLoading( Entity::Player& player )
{
}

void Sapphire::InstanceContent::onInitDirector( Entity::Player& player )
{
  sendDirectorVars( player );
  player.setDirectorInitialized( true );
}

void Sapphire::InstanceContent::onDirectorSync( Entity::Player& player )
{
  player.queuePacket( makeActorControlSelf( player.getId(), DirectorUpdate, 0x00110001, 0x80000000, 1 ) );
}


void Sapphire::InstanceContent::setVar( uint8_t index, uint8_t value )
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

void Sapphire::InstanceContent::setSequence( uint8_t value )
{
  setDirectorSequence( value );

  for( const auto& playerIt : m_playerMap )
  {
    sendDirectorVars( *playerIt.second );
  }
}

void Sapphire::InstanceContent::setBranch( uint8_t value )
{
  setDirectorBranch( value );

  for( const auto& playerIt : m_playerMap )
  {
    sendDirectorVars( *playerIt.second );
  }
}

void Sapphire::InstanceContent::startQte()
{
  for( const auto& playerIt : m_playerMap )
  {
    auto player = playerIt.second;
    player->queuePacket( makeActorControlSelf( player->getId(), DirectorUpdate, getDirectorId(), 0x8000000A ) );
  }
}

void Sapphire::InstanceContent::startEventCutscene()
{
  // TODO: lock player movement
  for( const auto& playerIt : m_playerMap )
  {
    auto player = playerIt.second;
    player->queuePacket( makeActorControlSelf( player->getId(), DirectorUpdate, getDirectorId(), 0x80000008 ) );
  }
}

void Sapphire::InstanceContent::endEventCutscene()
{
  for( const auto& playerIt : m_playerMap )
  {
    auto player = playerIt.second;
    player->queuePacket( makeActorControlSelf( player->getId(), DirectorUpdate, getDirectorId(), 0x80000009 ) );
  }
}

void Sapphire::InstanceContent::onRegisterEObj( Entity::EventObjectPtr object )
{
  if( object->getName() != "none" )
    m_eventObjectMap[ object->getName() ] = object;
  if( object->getObjectId() == 2000182 ) // start
    m_pEntranceEObj = object;
  if( m_pEntranceEObj == nullptr && object->getName() == "Entrance" )
    m_pEntranceEObj = object;

  auto& exdData = Common::Service< Data::ExdDataGenerated >::ref();
  auto objData = exdData.get< Sapphire::Data::EObj >( object->getObjectId() );
  if( objData )
    // todo: data should be renamed to eventId
    m_eventIdToObjectMap[ objData->data ] = object;
  else
    Logger::error( "InstanceContent::onRegisterEObj Territory " +
                   m_internalName + ": No EObj data found for EObj with ID: " +
                   std::to_string( object->getObjectId() ) );
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

void Sapphire::InstanceContent::onBeforePlayerZoneIn( Sapphire::Entity::Player& player )
{
  // remove any players from the instance who aren't bound on zone in
  if( !isPlayerBound( player.getId() ) )
    player.exitInstance();

  // if a player has already spawned once inside this instance, don't move them if they happen to zone in again
  if( !hasPlayerPreviouslySpawned( player ) )
  {
    if( m_pEntranceEObj != nullptr )
    {
      player.setRot( PI );
      player.setPos( m_pEntranceEObj->getPos() );
    }
    else
    {
      player.setRot( PI );
      player.setPos( { 0.f, 0.f, 0.f } );
    }
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

  auto it = m_eventIdToObjectMap.find( eventId );
  if( it == m_eventIdToObjectMap.end() )
    return;

  if( auto onTalk = it->second->getOnTalkHandler() )
    onTalk( player, it->second, getAsInstanceContent(), eventId, actorId );
  else
    player.sendDebug( "No onTalk handler found for interactable eobj with EObjID#{0}, eventId#{1}  ",
                      it->second->getObjectId(), eventId );
}

void
Sapphire::InstanceContent::onEnterTerritory( Entity::Player& player, uint32_t eventId, uint16_t param1, uint16_t param2 )
{
  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();
  scriptMgr.onInstanceEnterTerritory( getAsInstanceContent(), player, eventId, param1, param2 );

  if( !hasPlayerPreviouslySpawned( player ) )
  {
    m_spawnedPlayers.insert( player.getId() );
    player.directorPlayScene( getDirectorId(), 1, NO_DEFAULT_CAMERA | CONDITION_CUTSCENE | SILENT_ENTER_TERRI_ENV |
                                                  HIDE_HOTBAR | SILENT_ENTER_TERRI_BGM | SILENT_ENTER_TERRI_SE |
                                                  DISABLE_STEALTH | 0x00100000 | LOCK_HUD | LOCK_HOTBAR |
                                                  // todo: wtf is 0x00100000
                                                  DISABLE_CANCEL_EMOTE, 0, 0x9, 0 );
  }
  else
    player.directorPlayScene( getDirectorId(), 2, NO_DEFAULT_CAMERA | HIDE_HOTBAR, 0, 0x9, getCurrentBGM() );
}

void Sapphire::InstanceContent::setCurrentBGM( uint16_t bgmIndex )
{
  m_currentBgm = bgmIndex;

  for( const auto& playerIt : m_playerMap )
  {
    auto player = playerIt.second;
    // note: retail do send a BGM_MUTE(1) first before any BGM transition, but YOLO in this case.
    // also do note that this code can't control the bgm granularly. (i.e. per player for WoD submap.) oops.
    // player->queuePacket( ActorControlSelfPacket( player->getId(), DirectorUpdate, getDirectorId(), 0x80000001, 1 ) );
    player->queuePacket(
      makeActorControlSelf( player->getId(), DirectorUpdate, getDirectorId(), 0x80000001, bgmIndex ) );
  }
}

void Sapphire::InstanceContent::setPlayerBGM( Sapphire::Entity::Player& player, uint16_t bgmId )
{
  player.queuePacket( makeActorControlSelf( player.getId(), DirectorUpdate, getDirectorId(), 0x80000001, bgmId ) );
}

uint16_t Sapphire::InstanceContent::getCurrentBGM() const
{
  return m_currentBgm;
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
  player.unsetStateFlag( PlayerStateFlag::BoundByDuty );}
