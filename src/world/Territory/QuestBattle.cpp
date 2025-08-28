
#include <Common.h>
#include <Logging/Logger.h>
#include <Util/Util.h>
#include <Util/UtilMath.h>
#include <Exd/ExdData.h>
#include <Network/CommonActorControl.h>
#include <Service.h>

#include <utility>

#include "Event/Director.h"
#include "Event/EventDefs.h"
#include "Script/ScriptMgr.h"

#include "Actor/Player.h"
#include "Actor/EventObject.h"
#include "Actor/BNpc.h"

#include "Network/PacketWrappers/ActorControlPacket.h"
#include "Network/PacketWrappers/ActorControlSelfPacket.h"

#include "WorldServer.h"
#include "Manager/PlayerMgr.h"
#include "Manager/EventMgr.h"
#include "Event/EventHandler.h"

#include "QuestBattle.h"

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets::Server;
using namespace Sapphire::Network::ActorControl;
using namespace Sapphire::World::Manager;


Sapphire::QuestBattle::QuestBattle( std::shared_ptr< Excel::ExcelStruct< Excel::QuestBattle > > pBattleDetails,
                                    uint16_t territoryType, uint32_t guId,
                                    const std::string& internalName, const std::string& contentName,
                                    uint32_t questBattleId ) :
  Territory( static_cast< uint16_t >( territoryType ), guId, internalName, contentName ),
  Director( Event::Director::QuestBattle, questBattleId ),
  m_pBattleDetails( std::move( pBattleDetails ) ),
  m_questBattleId( questBattleId ),
  m_state( Created ),
  m_instanceCommenceTime( 0 )
{

}

bool Sapphire::QuestBattle::init()
{
  if( !Territory::init() )
    return false;

  //loadBNpcs();

  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();
  scriptMgr.onInstanceInit( *this );

  return true;
}

uint32_t Sapphire::QuestBattle::getQuestBattleId() const
{
  return m_questBattleId;
}


std::shared_ptr< Excel::ExcelStruct< Excel::QuestBattle > > Sapphire::QuestBattle::getQuestBattleDetails() const
{
  return m_pBattleDetails;
}

void Sapphire::QuestBattle::onPlayerZoneIn( Entity::Player& player )
{
  Logger::debug( "QuestBattle::onPlayerZoneIn: Territory#{0}|{1}, Entity#{2}",
                 getGuId(), getTerritoryTypeId(), player.getId() );

  m_pPlayer = player.getAsPlayer();

  // mark player as "bound by duty"
  //player.setCondition( PlayerCondition::BoundByDuty );

  sendDirectorInit( player );

}

void Sapphire::QuestBattle::onLeaveTerritory( Entity::Player& player )
{
  Logger::debug( "QuestBattle::onLeaveTerritory: Territory#{0}|{1}, Entity#{2}",
                 getGuId(), getTerritoryTypeId(), player.getId() );

  clearDirector( player );
}

void Sapphire::QuestBattle::onEnterSceneFinish( Entity::Player& player )
{
  auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();
  eventMgr.eventStart( player, player.getId(), getDirectorId(), Event::EventHandler::GameProgress, 1, 0 );
  eventMgr.playScene( player, getDirectorId(),  60000, 0, { 0x40000 /*unmapped*/ } );
  setSequence( 2 );
}

void Sapphire::QuestBattle::onUpdate( uint64_t tickCount )
{
  if( !m_pPlayer )
    return;

  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();

  switch( m_state )
  {
    case Created:
    {


      if( !m_pPlayer->isLoadingComplete() ||
          !m_pPlayer->isDirectorInitialized() ||
          !m_pPlayer->isOnEnterEventDone() ||
          m_pPlayer->hasCondition( PlayerCondition::WatchingCutscene ) )
        return;

      if( m_instanceCommenceTime == 0 )
      {
        m_instanceCommenceTime = Util::getTimeMs() + instanceStartDelay;
        return;
      }
      else if( Util::getTimeMs() < m_instanceCommenceTime )
        return;

      onEnterSceneFinish( *m_pPlayer );

      scriptMgr.onDutyCommence( *this, *m_pPlayer );

      m_state = DutyInProgress;
      m_instanceExpireTime = Util::getTimeSeconds() + ( m_pBattleDetails->data().LimitTime * 60u );
      break;
    }

    case DutyReset:
      break;

    case DutyInProgress:
      updateBNpcs( tickCount );
      break;

    case DutyFinished:
      break;

    case DutyFailed:
    {
      if( getSequence() != 0xFE )
      {
        setSequence( 0xFE );
        m_instanceFailTime = tickCount;
      }

      if( ( static_cast< int64_t >( tickCount ) - static_cast< int64_t >( m_instanceFailTime ) ) > 6000 )
      {
        playerMgr().onExitInstance( *m_pPlayer );
        m_pPlayer.reset();
      }
      break;
    }
  }

  scriptMgr.onInstanceUpdate( *this, tickCount );

  m_lastUpdate = tickCount;
}

void Sapphire::QuestBattle::onFinishLoading( Entity::Player& player )
{

}

void Sapphire::QuestBattle::onInitDirector( Entity::Player& player )
{
  auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();
  eventMgr.sendEventNotice( player, getDirectorId(), 0, 2, Util::getTimeSeconds(), 0x0708 );
  sendDirectorVars( player );
  player.setDirectorInitialized( true );
}

void Sapphire::QuestBattle::onDirectorSync( Entity::Player& player )
{
  auto& server = Common::Service< World::WorldServer >::ref();
  server.queueForPlayer( player.getCharacterId(), makeActorControlSelf( player.getId(), DirectorUpdate, 0x00110001, 0x80000000, 1 ) );
}

void Sapphire::QuestBattle::setVar( uint8_t index, uint8_t value )
{
  setDirectorVar( index, value );
  sendDirectorVars( *m_pPlayer );
}

void Sapphire::QuestBattle::setSequence( uint8_t value )
{
  setDirectorSequence( value );
  sendDirectorVars( *m_pPlayer );
}

void Sapphire::QuestBattle::setFlags( uint8_t value )
{
  setDirectorFlags( value );
  sendDirectorVars( *m_pPlayer );
}

void Sapphire::QuestBattle::startQte()
{
  auto& server = Common::Service< World::WorldServer >::ref();
  server.queueForPlayer( m_pPlayer->getCharacterId(), makeActorControlSelf( m_pPlayer->getId(), DirectorUpdate, getDirectorId(), 0x8000000A ) );
}

void Sapphire::QuestBattle::startEventCutscene()
{
  auto& server = Common::Service< World::WorldServer >::ref();
  server.queueForPlayer( m_pPlayer->getCharacterId(), makeActorControlSelf( m_pPlayer->getId(), DirectorUpdate, getDirectorId(), 0x80000008 ) );
}

void Sapphire::QuestBattle::endEventCutscene()
{
  auto& server = Common::Service< World::WorldServer >::ref();
  server.queueForPlayer( m_pPlayer->getCharacterId(), makeActorControlSelf( m_pPlayer->getId(), DirectorUpdate, getDirectorId(), 0x80000009 ) );
}

void Sapphire::QuestBattle::onAddEObj( Entity::EventObjectPtr object )
{
  if( object->getName() != "none" )
    m_eventObjectMap[ object->getName() ] = object;

  auto& exdData = Common::Service< Data::ExdData >::ref();
  auto objData = exdData.getRow< Excel::EObj >( object->getObjectId() );
  if( objData )
    m_eventIdToObjectMap[ objData->data().EventHandler ] = object;
  else
    Logger::error( "InstanceContent::onAddEObj Territory " +
                   m_internalName + ": No EObj data found for EObj with ID: " +
                   std::to_string( object->getObjectId() ) );
}

void Sapphire::QuestBattle::onEventHandlerOrder( Entity::Player& player, uint32_t arg0, uint32_t arg1, uint32_t arg2,
                                                 uint32_t arg3, uint32_t arg4 )
{

}

Sapphire::Event::Director::DirectorState Sapphire::QuestBattle::getState() const
{
  return m_state;
}

void Sapphire::QuestBattle::onBeforePlayerZoneIn( Sapphire::Entity::Player& player )
{
  player.setRot( PI );
  player.setPos( { 0.f, 0.f, 0.f } );

  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();
  scriptMgr.onPlayerSetup( *this, player );

  player.resetObjSpawnIndex();

  player.setDirectorId( getDirectorId() );
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
    PlayerMgr::sendDebug( player, "No onTalk handler found for interactable eobj with EObjID#{0}, eventId#{1}",
                          it->second->getObjectId(), eventId );
}

void
Sapphire::QuestBattle::onEnterTerritory( Entity::Player& player, uint32_t eventId, uint16_t param1, uint16_t param2 )
{
  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();
  scriptMgr.onInstanceEnterTerritory( *this, player, eventId, param1, param2 );
}

void Sapphire::QuestBattle::clearDirector( Entity::Player& player )
{
  sendDirectorClear( player );

  player.setDirectorInitialized( false );
  // remove "bound by duty" state
  //player.removeCondition( PlayerCondition::BoundByDuty );
}

void Sapphire::QuestBattle::success()
{
  auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();
  //m_state = DutyFinished;
  eventMgr.eventStart( *m_pPlayer, m_pPlayer->getId(), getDirectorId(), Event::EventHandler::GameProgress, 1, 0 );
  eventMgr.playScene( *m_pPlayer, getDirectorId(), 60001, 0x40000,
    [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      eventMgr.eventFinish( player, getDirectorId(), 1 );
      eventMgr.eventStart( player, player.getId(), getDirectorId(), Event::EventHandler::GameProgress, 1, 0 );
      eventMgr.playScene( player, getDirectorId(), 6, HIDE_HOTBAR | NO_DEFAULT_CAMERA,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {
                          eventMgr.eventFinish( player, getDirectorId(), 1 );

                          auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();
                          scriptMgr.onDutyComplete( *this, *m_pPlayer );

                          playerMgr().onExitInstance( player );
                        } );

    } );
}

void Sapphire::QuestBattle::fail()
{
  m_state = DutyFailed;
}

uint32_t Sapphire::QuestBattle::getQuestId() const
{
  return m_pBattleDetails->data().Quest;
}

uint32_t Sapphire::QuestBattle::getCountEnemyBNpc()
{
  uint32_t count = 0;
  for( const auto& bnpcIt : m_bNpcMap )
  {
    if( bnpcIt.second->getEnemyType() == 4 && bnpcIt.second->isAlive() )
      count++;
  }
  return count;
}

Sapphire::Entity::PlayerPtr Sapphire::QuestBattle::getPlayerPtr()
{
  return m_pPlayer;
}