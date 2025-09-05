#include <Logging/Logger.h>
#include <Exd/ExdData.h>

#include <watchdog/Watchdog.h>
#include <Service.h>

#include "Territory/Territory.h"
#include "Territory/InstanceContent.h"
#include "Territory/QuestBattle.h"
#include "Actor/Player.h"
#include "Actor/EventObject.h"
#include "Actor/BNpc.h"
#include "WorldServer.h"
#include "Event/EventHandler.h"
#include "Action/Action.h"

#include "Manager/EventMgr.h"
#include "Manager/PlayerMgr.h"
#include "Manager/TerritoryMgr.h"

#include "StatusEffect/StatusEffect.h"

#include "Network/PacketWrappers/ServerNoticePacket.h"

#include "Script/ScriptMgr.h"

#include "NativeScriptMgr.h"
#include "WorldServer.h"

#include "Quest/Quest.h"

using namespace Sapphire::World::Manager;
// enable the ambiguity fix for every platform to avoid #define nonsense
#define WIN_AMBIGUITY_FIX

namespace fs = std::filesystem;

Sapphire::Scripting::ScriptMgr::ScriptMgr() :
  m_firstScriptChangeNotificiation( false )
{
  m_nativeScriptMgr = createNativeScriptMgr();
}

Sapphire::Scripting::ScriptMgr::~ScriptMgr()
{
  Watchdog::unwatchAll();
}

void Sapphire::Scripting::ScriptMgr::update()
{
  m_nativeScriptMgr->processLoadQueue();
}

bool Sapphire::Scripting::ScriptMgr::init()
{
  std::set< std::string > files;
  auto& server = Common::Service< World::WorldServer >::ref();

  auto status = loadDir( server.getConfig().scripts.path, files, m_nativeScriptMgr->getModuleExtension() );

  if( !status )
  {
    Logger::error( "ScriptMgr: failed to load modules, the server will not function correctly without scripts loaded." );
    return false;
  }

  uint32_t scriptsFound = 0;
  uint32_t scriptsLoaded = 0;

  for( auto itr = files.begin(); itr != files.end(); ++itr )
  {
    auto& path = *itr;

    scriptsFound++;

    if( m_nativeScriptMgr->loadScript( path ) )
      scriptsLoaded++;
  }

  Logger::info( "ScriptMgr: Loaded {0}/{1} modules", scriptsLoaded, scriptsFound );

  watchDirectories();

  return true;
}

void Sapphire::Scripting::ScriptMgr::watchDirectories()
{
  auto& server = Common::Service< World::WorldServer >::ref();
  auto shouldWatch = server.getConfig().scripts.hotSwap;
  if( !shouldWatch )
    return;

  Watchdog::watchMany( server.getConfig().scripts.path + "*" +
                       m_nativeScriptMgr->getModuleExtension(),
                       [ this ]( const std::vector< ci::fs::path >& paths )
                       {
                         if( !m_firstScriptChangeNotificiation )
                         {
                           // for whatever reason, the first time this runs, it detects every file as changed
                           // so we're always going to ignore the first notification
                           m_firstScriptChangeNotificiation = true;
                           return;
                         }

                         for( const auto& path : paths )
                         {
                           if( m_nativeScriptMgr->isModuleLoaded( path.stem().string() ) )
                           {
                             Logger::debug( "Reloading changed script: {0}", path.stem().string() );

                             m_nativeScriptMgr->queueScriptReload( path.stem().string() );
                           }
                           else
                           {
                             Logger::debug( "Loading new script: {0}", path.stem().string() );

                             m_nativeScriptMgr->loadScript( path.string() );
                           }
                         }
                       } );
}

bool Sapphire::Scripting::ScriptMgr::loadDir( const std::string& dirname, std::set< std::string >& files, const std::string& ext )
{
  Logger::info( "ScriptMgr: loading scripts from: {0}", dirname );

  if( !fs::exists( dirname ) )
  {
    Logger::error( "ScriptMgr: scripts directory doesn't exist" );
    return false;
  }

  fs::path targetDir( dirname );

  fs::directory_iterator iter( targetDir );

  for( const auto& i : iter )
  {
    if( fs::is_regular_file( i ) && fs::path( i ).extension() == ext )
    {
      files.insert( fs::path( i ).string() );
    }
  }

  if( !files.empty() )
    return true;
  else
  {
    Logger::error( "ScriptMgr: couldn't find any script modules" );
    return false;
  }
}

void Sapphire::Scripting::ScriptMgr::onPlayerFirstEnterWorld( Entity::Player& player )
{
//   try
//   {
//      std::string test = m_onFirstEnterWorld( player );
//   }
//   catch( const std::exception &e )
//   {
//      std::string what = e.what();
//   }
}

bool Sapphire::Scripting::ScriptMgr::onTalk( Entity::Player& player, uint64_t actorId, uint32_t eventId )
{
  auto eventType = static_cast< uint16_t >( eventId >> 16 );
  auto& exdData = Common::Service< Data::ExdData >::ref();
  if( eventType == Event::EventHandler::EventHandlerType::Quest )
  {
    auto script = m_nativeScriptMgr->getScript< Sapphire::ScriptAPI::QuestScript >( eventId );
    if( !script )
    {
      auto questInfo = exdData.getRow< Excel::Quest >( eventId );
      if( questInfo )
      {
        World::Manager::PlayerMgr::sendUrgent( player, "Quest not implemented: {0} ({1})", questInfo->getString( questInfo->data().Text.Name ), eventId );
        return false;
      }
    }

    auto& pEventMgr = Common::Service< World::Manager::EventMgr >::ref();
    auto actor = pEventMgr.mapEventActorToRealActor( static_cast< uint32_t >( actorId ) );

    auto questId = static_cast< uint16_t >( eventId );
    if( player.hasQuest( eventId ) )
    {
      World::Quest preQ;
      auto questIdx = player.getQuestIndex( questId );
      auto& quest = player.getQuestByIndex( questIdx );
      preQ = quest;
      script->onTalk( quest, player, actor );
      if( quest != preQ )
        player.updateQuest( quest );
    }
    else
    {
      auto newQuest = World::Quest( questId, 0, 0 );
      script->onTalk( newQuest, player, actor );
    }
    return true;
  }

  // all other types....

  // check if the actor is an eobj and call its script if we have one
  auto& teriMgr = Common::Service< World::Manager::TerritoryMgr >::ref();
  auto zone = teriMgr.getTerritoryByGuId( player.getTerritoryId() );
  if( auto eobj = zone ? zone->getEObj( static_cast< uint32_t >( actorId ) ) : nullptr )
  {
    auto script = m_nativeScriptMgr->getScript< Sapphire::ScriptAPI::EventObjectScript >( eobj->getObjectId() );
    if( script )
    {
      script->onTalk( eventId, player, *eobj );
      return true;
    }

    if( auto instance = zone->getAsInstanceContent() )
    {
      auto instanceScript = m_nativeScriptMgr->getScript< Sapphire::ScriptAPI::InstanceContentScript >( instance->getDirectorId() );
      if( instanceScript )
      {
        instanceScript->onTalk( *instance, player, *eobj, eventId );
        return true;
      }
    }
  }

  // check for a direct eventid match first, otherwise default to base type
  auto script = m_nativeScriptMgr->getScript< Sapphire::ScriptAPI::EventScript >( eventId );
  if( script )
  {
    script->onTalk( eventId, player, actorId );
    return true;
  }
  else
  {
    script = m_nativeScriptMgr->getScript< Sapphire::ScriptAPI::EventScript >( eventId & 0xFFFF0000 );
    if( !script )
      return false;

    script->onTalk( eventId, player, actorId );
    return true;
  }

  // check for instance script
  if( auto instance = zone->getAsInstanceContent() )
  {
    auto instanceScript = m_nativeScriptMgr->getScript< Sapphire::ScriptAPI::InstanceContentScript >( instance->getDirectorId() );
    if( instanceScript )
    {
      instanceScript->onTalk( *instance, player, eventId, actorId );
      return true;
    }
  }

  return false;
}

bool Sapphire::Scripting::ScriptMgr::onYield( Entity::Player& player, uint32_t eventId, uint16_t sceneId, uint8_t resumeId,
                                              const std::string& resultString, uint64_t resultInt )
{
  auto eventType = static_cast< uint16_t >( eventId >> 16 );
  auto& exdData = Common::Service< Data::ExdData >::ref();
  if( eventType == Event::EventHandler::EventHandlerType::Quest )
  {
    Logger::error( "Yield unimplemented for EventHandlerType::Quest!" );
    return false;
  }

  // check for a direct eventid match first, otherwise default to base type
  auto script = m_nativeScriptMgr->getScript< Sapphire::ScriptAPI::EventScript >( eventId );
  if( script )
  {
    script->onYield( eventId, sceneId, resumeId, player, resultString, resultInt );
    return true;
  }
  else
  {
    script = m_nativeScriptMgr->getScript< Sapphire::ScriptAPI::EventScript >( eventId & 0xFFFF0000 );
    if( !script )
      return false;

    script->onYield( eventId, sceneId, resumeId, player, resultString, resultInt );
    return true;
  }
}

bool Sapphire::Scripting::ScriptMgr::onEnterTerritory( Entity::Player& player, uint32_t eventId, uint16_t param1, uint16_t param2 )
{
  const auto eventType = static_cast< uint16_t >( eventId >> 16 );

  if( eventType == Event::EventHandler::EventHandlerType::Quest )
  {
    auto script = m_nativeScriptMgr->getScript< Sapphire::ScriptAPI::QuestScript >( eventId );
    if( !script )
      return false;
    if( player.hasQuest( eventId ) )
    {
      auto idx = player.getQuestIndex( eventId );
      auto& quest = player.getQuestByIndex( idx );
      script->onEnterTerritory( quest, player, param1, param2 );
    }
  }
  else
  {
    auto script = m_nativeScriptMgr->getScript< Sapphire::ScriptAPI::EventScript >( eventId );
    if( !script )
      return false;
    script->onEnterTerritory( player, eventId, param1, param2 );
  }

  return true;
}

bool Sapphire::Scripting::ScriptMgr::onWithinRange( Entity::Player& player, uint32_t eventId, uint32_t param1, float x, float y, float z )
{
  const auto eventType = static_cast< uint16_t >( eventId >> 16 );
  auto& pEventMgr = Common::Service< World::Manager::EventMgr >::ref();

  if( eventType == Event::EventHandler::EventHandlerType::Quest )
  {
    auto script = m_nativeScriptMgr->getScript< Sapphire::ScriptAPI::QuestScript >( eventId );
    if( !script )
      return false;
    if( player.hasQuest( eventId ) )
    {
      auto idx = player.getQuestIndex( eventId );
      auto& quest = player.getQuestByIndex( idx );
      World::Quest preQ = quest;
      script->onWithinRange( quest, player, eventId, param1, x, y, z );
      if( quest != preQ )
        player.updateQuest( quest );
    }
  }
  else if( auto script = m_nativeScriptMgr->getScript< Sapphire::ScriptAPI::ZoneScript >( player.getTerritoryTypeId() ) )
  {
    script->onWithinRange( player, eventId, param1, x, y, z );
  }
  else
  {
    auto script1 = m_nativeScriptMgr->getScript< Sapphire::ScriptAPI::EventScript >( eventId );
    if( !script1 )
      return false;
    script1->onWithinRange( player, eventId, param1, x, y, z );
  }

  return true;
}

bool Sapphire::Scripting::ScriptMgr::onOutsideRange( Entity::Player& player, uint32_t eventId, uint32_t param1, float x, float y, float z )
{
  const auto eventType = static_cast< uint16_t >( eventId >> 16 );
  auto& pEventMgr = Common::Service< World::Manager::EventMgr >::ref();

  if( eventType == Event::EventHandler::EventHandlerType::Quest )
  {
    auto script = m_nativeScriptMgr->getScript< Sapphire::ScriptAPI::QuestScript >( eventId );
    if( !script )
      return false;
    if( player.hasQuest( eventId ) )
    {
      auto idx = player.getQuestIndex( eventId );
      auto& quest = player.getQuestByIndex( idx );
      World::Quest preQ = quest;
      script->onOutsideRange( quest, player, eventId, param1, x, y, z );
      if( quest != preQ )
        player.updateQuest( quest );
    }
  }
  else
  {
    auto script = m_nativeScriptMgr->getScript< Sapphire::ScriptAPI::EventScript >( eventId );
    if( !script )
      return false;
    script->onOutsideRange( player, eventId, param1, x, y, z );
  }

  return true;
}

bool Sapphire::Scripting::ScriptMgr::onEmote( Entity::Player& player, uint64_t actorId, uint32_t eventId, uint8_t emoteId )
{
  const auto eventType = static_cast< uint16_t >( eventId >> 16 );

  auto& pEventMgr = Common::Service< World::Manager::EventMgr >::ref();
  auto actor = pEventMgr.mapEventActorToRealActor( static_cast< uint32_t >( actorId ) );
  if( eventType == Event::EventHandler::EventHandlerType::Quest )
  {
    auto script = m_nativeScriptMgr->getScript< Sapphire::ScriptAPI::QuestScript >( eventId );
    if( !script )
      return false;
    if( player.hasQuest( eventId ) )
    {
      auto idx = player.getQuestIndex( eventId );
      auto& quest = player.getQuestByIndex( idx );
      World::Quest preQ = quest;
      script->onEmote( quest, actor, emoteId, player );
      if( quest != preQ )
        player.updateQuest( quest );
    }
  }
  else
  {
    auto script = m_nativeScriptMgr->getScript< Sapphire::ScriptAPI::EventScript >( eventId );
    if( !script )
      return false;
    script->onEmote( actor, eventId, emoteId, player );
  }

  return true;
}

bool Sapphire::Scripting::ScriptMgr::onEventHandlerReturn( Entity::Player& player, uint32_t eventId, uint16_t subEvent, uint16_t param1, uint16_t param2,
                                                           uint16_t param3 )
{

  return false;
}

bool Sapphire::Scripting::ScriptMgr::onEventHandlerTradeReturn( Entity::Player& player, uint32_t eventId, uint16_t subEvent, uint16_t param, uint32_t catalogId )
{
  auto script = m_nativeScriptMgr->getScript< Sapphire::ScriptAPI::EventScript >( eventId );
  if( script )
  {
    script->onEventHandlerTradeReturn( player, eventId, subEvent, param, catalogId );
    return true;
  }

  return false;
}

bool Sapphire::Scripting::ScriptMgr::onEventItem( Entity::Player& player, uint32_t eventItemId, uint32_t eventId, uint64_t targetId )
{
  auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();
  std::string eventName = "onEventItem";
  std::string objName = eventMgr.getEventName( eventId );
  PlayerMgr::sendDebug( player, "Calling: {0}.{1} - {2}", objName, eventName, eventId );

  auto& pEventMgr = Common::Service< World::Manager::EventMgr >::ref();
  auto actor = pEventMgr.mapEventActorToRealActor( static_cast< uint32_t >( targetId ) );

  auto eventType = static_cast< uint16_t >( eventId >> 16 );
  auto& exdData = Common::Service< Data::ExdData >::ref();
  if( eventType == Event::EventHandler::EventHandlerType::Quest )
  {
    auto script = m_nativeScriptMgr->getScript< Sapphire::ScriptAPI::QuestScript >( eventId );
    if( script )
    {
      auto questId = static_cast< uint16_t >( eventId );
      if( player.hasQuest( eventId ) )
      {
        World::Quest preQ;
        auto questIdx = player.getQuestIndex( questId );
        auto& quest = player.getQuestByIndex( questIdx );
        preQ = quest;
        script->onEventItem( quest, player, actor );
        if( quest != preQ )
          player.updateQuest( quest );
        return true;
      }
    }
  }

  return false;
}

bool Sapphire::Scripting::ScriptMgr::onEventGroundItem( Entity::Player& player, uint32_t eventItemId, uint32_t eventId, Common::FFXIVARR_POSITION3 pos )
{
  auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();
  std::string eventName = "onEventGroundItem";
  std::string objName = eventMgr.getEventName( eventId );
  PlayerMgr::sendDebug( player, "Calling: {0}.{1} - {2}", objName, eventName, eventId );

  auto& pEventMgr = Common::Service< World::Manager::EventMgr >::ref();

  auto eventType = static_cast< uint16_t >( eventId >> 16 );
  auto& exdData = Common::Service< Data::ExdData >::ref();
  if( eventType == Event::EventHandler::EventHandlerType::Quest )
  {
    auto script = m_nativeScriptMgr->getScript< Sapphire::ScriptAPI::QuestScript >( eventId );
    if( script )
    {
      auto questId = static_cast< uint16_t >( eventId );
      if( player.hasQuest( eventId ) )
      {
        World::Quest preQ;
        auto questIdx = player.getQuestIndex( questId );
        auto& quest = player.getQuestByIndex( questIdx );
        preQ = quest;
        script->onEventGroundItem( quest, player, pos );
        if( quest != preQ )
          player.updateQuest( quest );
        return true;
      }
    }
  }

  return false;
}

void Sapphire::Scripting::ScriptMgr::onTriggerOwnerDeaggro( Entity::Player& player, Entity::BNpc& bnpc )
{
  auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();

  // loop through all active quests and try to call available onBNpcKill callbacks
  for( size_t i = 0; i < 30; i++ )
  {
    auto quest = player.getQuestByIndex( static_cast< uint16_t >( i ) );
    if( quest.getId() == 0 )
      continue;

    uint32_t questId = quest.getId() | Event::EventHandler::EventHandlerType::Quest << 16;

    auto script = m_nativeScriptMgr->getScript< Sapphire::ScriptAPI::QuestScript >( questId );
    if( script )
    {
      std::string objName = eventMgr.getEventName( questId );

      PlayerMgr::sendDebug( player, "Calling: {0}.onTriggerOwnerDeaggro layoutId#{1}", objName, bnpc.getLayoutId() );

      World::Quest preQ = quest;
      script->onTriggerOwnerDeaggro( quest, bnpc, player );
      if( quest != preQ )
        player.updateQuest( quest );
    }
  }
}

bool Sapphire::Scripting::ScriptMgr::onBNpcKill( Entity::Player& player, Entity::BNpc& bnpc )
{
  auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();

  // loop through all active quests and try to call available onBNpcKill callbacks
  for( size_t i = 0; i < 30; i++ )
  {
    auto quest = player.getQuestByIndex( static_cast< uint16_t >( i ) );
    if( quest.getId() == 0 )
      continue;

    uint32_t questId = quest.getId() | Event::EventHandler::EventHandlerType::Quest << 16;

    auto script = m_nativeScriptMgr->getScript< Sapphire::ScriptAPI::QuestScript >( questId );
    if( script )
    {
      std::string objName = eventMgr.getEventName( questId );

      PlayerMgr::sendDebug( player, "Calling: {0}.onBnpcKill nameId#{1}", objName, bnpc.getBNpcNameId() );


      World::Quest preQ = quest;
      script->onBNpcKill( quest, bnpc, player );
      if( quest != preQ )
        player.updateQuest( quest );
    }
  }

  return true;
}

bool Sapphire::Scripting::ScriptMgr::onPlayerDeath( Entity::Player& player )
{
  auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();

  // loop through all active quests and try to call available onPlayerDeath callbacks
  for( size_t i = 0; i < 30; i++ )
  {
    auto quest = player.getQuestByIndex( static_cast< uint16_t >( i ) );
    if( quest.getId() == 0 )
      continue;

    uint32_t questId = quest.getId() | Event::EventHandler::EventHandlerType::Quest << 16;

    auto script = m_nativeScriptMgr->getScript< Sapphire::ScriptAPI::QuestScript >( questId );
    if( script )
    {
      std::string objName = eventMgr.getEventName( questId );

      PlayerMgr::sendDebug( player, "Calling: {0}.onPlayerDeath name: {1}", objName, player.getName() );

      World::Quest preQ = quest;
      script->onPlayerDeath( quest, player );
      if( quest != preQ )
        player.updateQuest( quest );
    }
  }

  return true;
}

bool Sapphire::Scripting::ScriptMgr::onEObjHit( Sapphire::Entity::Player& player, uint64_t actorId, uint32_t actionId )
{
  auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();
  bool didCallScript = false;

  auto& pEventMgr = Common::Service< World::Manager::EventMgr >::ref();
  auto actor = pEventMgr.mapEventActorToRealActor( static_cast< uint32_t >( actorId ) );

  for( size_t i = 0; i < 30; i++ )
  {
    auto quest = player.getQuestByIndex( static_cast< uint16_t >( i ));
    if( quest.getId() == 0 )
      continue;

    uint32_t questId = quest.getId() | Event::EventHandler::EventHandlerType::Quest << 16;

    auto script = m_nativeScriptMgr->getScript< Sapphire::ScriptAPI::QuestScript >( questId );
    if( script )
    {
      didCallScript = true;
      std::string objName = eventMgr.getEventName( questId );

      PlayerMgr::sendDebug( player, "Calling: {0}.onEObjHit actorId#{1}, questId#{2}", objName, actor, quest.getId() );

      World::Quest preQ = quest;
      script->onEObjHit( quest, player, actor, actionId );
      if( quest != preQ )
        player.updateQuest( quest );
    }
  }

  return didCallScript;
}

bool Sapphire::Scripting::ScriptMgr::onExecute( World::Action::Action& action )
{
  auto script = m_nativeScriptMgr->getScript< Sapphire::ScriptAPI::ActionScript >( action.getId() );

  if( script )
  {
    script->onExecute( action );
    return true;
  }
  return false;
}

bool Sapphire::Scripting::ScriptMgr::onAfterBuildEffect( World::Action::Action& action )
{
  auto script = m_nativeScriptMgr->getScript< Sapphire::ScriptAPI::ActionScript >( action.getId() );

  if( script )
  {
    script->onAfterBuildEffect( action );
    return true;
  }
  return false;
}

bool Sapphire::Scripting::ScriptMgr::onInterrupt( World::Action::Action& action )
{
  auto script = m_nativeScriptMgr->getScript< Sapphire::ScriptAPI::ActionScript >( action.getId() );

  if( script )
  {
    script->onInterrupt( action );
    return true;
  }
  return false;
}

bool Sapphire::Scripting::ScriptMgr::onBeforeBootstrap( World::Action::Action& action )
{
  auto script = m_nativeScriptMgr->getScript< Sapphire::ScriptAPI::ActionScript >( action.getId() );

  if( script )
  {
    script->onBeforeBootstrap( action );
    return true;
  }

  return false;
}

bool Sapphire::Scripting::ScriptMgr::onStart( World::Action::Action& action )
{
  auto script = m_nativeScriptMgr->getScript< Sapphire::ScriptAPI::ActionScript >( action.getId() );

  if( script )
  {
    script->onStart( action );
    return true;
  }

  return false;
}

bool Sapphire::Scripting::ScriptMgr::onStatusReceive( Entity::CharaPtr pActor, uint32_t effectId )
{
  auto script = m_nativeScriptMgr->getScript< Sapphire::ScriptAPI::StatusEffectScript >( effectId );

  if( script )
  {
    if( pActor->isPlayer() )
      PlayerMgr::sendDebug( *pActor->getAsPlayer(), "Calling status receive for statusid#{0}", effectId );

    script->onApply( *pActor );
    return true;
  }

  return false;
}

bool Sapphire::Scripting::ScriptMgr::onStatusTick( Entity::CharaPtr pActor, Sapphire::StatusEffect::StatusEffect& effect )
{
  auto script = m_nativeScriptMgr->getScript< Sapphire::ScriptAPI::StatusEffectScript >( effect.getId() );
  if( script )
  {
    script->onTick( *pActor, effect );
    return true;
  }

  return false;
}

bool Sapphire::Scripting::ScriptMgr::onStatusTimeOut( Entity::CharaPtr pChara, uint32_t effectId )
{
  auto script = m_nativeScriptMgr->getScript< Sapphire::ScriptAPI::StatusEffectScript >( effectId );
  if( script )
  {
    if( pChara->isPlayer() )
      PlayerMgr::sendDebug( *pChara->getAsPlayer(), "Calling status timeout for statusid#{0}", effectId );

    script->onExpire( *pChara );
    return true;
  }

  return false;
}

bool Sapphire::Scripting::ScriptMgr::onPlayerHit( Entity::CharaPtr& pHitChara, Sapphire::StatusEffect::StatusEffect& effect )
{
  auto script = m_nativeScriptMgr->getScript< Sapphire::ScriptAPI::StatusEffectScript >( effect.getId() );
  if( script )
  {
    script->onPlayerHit( *pHitChara, effect );
    return true;
  }

  return false;
}

bool Sapphire::Scripting::ScriptMgr::onZoneInit( const Territory& zone )
{
  auto script = m_nativeScriptMgr->getScript< Sapphire::ScriptAPI::ZoneScript >( zone.getTerritoryTypeId() );
  if( script )
  {
    script->onZoneInit();
    return true;
  }

  return false;
}

bool Sapphire::Scripting::ScriptMgr::onInstanceInit( InstanceContent& instance )
{
  auto instId = instance.getDirectorId();
  auto script = m_nativeScriptMgr->getScript< Sapphire::ScriptAPI::InstanceContentScript >( instance.getDirectorId() );

  if( script )
  {
    script->onInit( instance );

    return true;
  }

  return false;
}

bool Sapphire::Scripting::ScriptMgr::onInstanceReset( InstanceContent& instance )
{
  auto instId = instance.getDirectorId();
  auto script = m_nativeScriptMgr->getScript< Sapphire::ScriptAPI::InstanceContentScript >( instance.getDirectorId() );

  if( script )
  {
    script->onReset( instance );

    return true;
  }

  return false;
}

bool Sapphire::Scripting::ScriptMgr::onInstanceUpdate( InstanceContent& instance, uint64_t tickCount )
{
  auto script = m_nativeScriptMgr->getScript< Sapphire::ScriptAPI::InstanceContentScript >( instance.getDirectorId() );

  if( script )
  {
    script->onUpdate( instance, tickCount );

    return true;
  }

  return false;
}


bool Sapphire::Scripting::ScriptMgr::onInstanceStateChange( Sapphire::InstanceContent& instance,
                                                            Sapphire::InstanceContentState oldState,
                                                            Sapphire::InstanceContentState newState )
{
  auto script = m_nativeScriptMgr->getScript< Sapphire::ScriptAPI::InstanceContentScript >( instance.getDirectorId() );

  if( script )
  {
    script->onStateChange( instance, oldState, newState );

    return true;
  }

  return false;
}




bool Sapphire::Scripting::ScriptMgr::onInstanceEnterTerritory( InstanceContent& instance, Entity::Player& player,
                                                               uint32_t eventId, uint16_t param1, uint16_t param2 )
{
  auto script = m_nativeScriptMgr->getScript< Sapphire::ScriptAPI::InstanceContentScript >( instance.getDirectorId() );
  if( script )
  {
    script->onEnterTerritory( instance, player, eventId, param1, param2 );
    return true;
  }

  return false;
}

bool Sapphire::Scripting::ScriptMgr::onInstanceLeaveTerritory( InstanceContent& instance, Entity::Player& player )
{
  auto script = m_nativeScriptMgr->getScript< Sapphire::ScriptAPI::InstanceContentScript >( instance.getDirectorId() );
  if( script )
  {
    script->onLeaveTerritory( instance, player );
    return true;
  }

  return false;
}

bool Sapphire::Scripting::ScriptMgr::onPlayerSetup( QuestBattle& instance, Entity::Player& player )
{
  auto script = m_nativeScriptMgr->getScript< Sapphire::ScriptAPI::QuestBattleScript >( instance.getDirectorId() );
  if( script )
  {
    script->onPlayerSetup( instance, player );
    return true;
  }

  return false;
}

bool Sapphire::Scripting::ScriptMgr::onInstanceInit( QuestBattle& instance )
{
  auto script = m_nativeScriptMgr->getScript< Sapphire::ScriptAPI::QuestBattleScript >( instance.getDirectorId() );
  if( script )
  {
    script->onInit( instance );
    return true;
  }

  return false;
}

bool Sapphire::Scripting::ScriptMgr::onInstanceUpdate( QuestBattle& instance, uint64_t tickCount )
{
  auto script = m_nativeScriptMgr->getScript< Sapphire::ScriptAPI::QuestBattleScript >( instance.getDirectorId() );

  if( script )
  {
    script->onUpdate( instance, tickCount );
    return true;
  }

  return false;
}

bool Sapphire::Scripting::ScriptMgr::onDutyCommence( QuestBattle& instance, Entity::Player& player )
{
  auto script = m_nativeScriptMgr->getScript< Sapphire::ScriptAPI::QuestBattleScript >( instance.getDirectorId() );

  if( script )
  {
    script->onDutyCommence( instance, player );
    return true;
  }

  return false;
}

bool Sapphire::Scripting::ScriptMgr::onInstanceEnterTerritory( QuestBattle& instance, Entity::Player& player,
                                                               uint32_t eventId, uint16_t param1, uint16_t param2 )
{
  auto script = m_nativeScriptMgr->getScript< Sapphire::ScriptAPI::QuestBattleScript >( instance.getDirectorId() );
  if( script )
  {
    script->onEnterTerritory( instance, player, eventId, param1, param2 );
    return true;
  }

  return false;
}

Sapphire::Scripting::NativeScriptMgr& Sapphire::Scripting::ScriptMgr::getNativeScriptHandler()
{
  return *m_nativeScriptMgr;
}

bool
Sapphire::Scripting::ScriptMgr::onDutyComplete( QuestBattle& instance, Sapphire::Entity::Player& player )
{
  auto script = m_nativeScriptMgr->getScript< Sapphire::ScriptAPI::QuestBattleScript >( instance.getDirectorId() );
  if( script )
  {
    World::Quest preQ;
    auto questIdx = player.getQuestIndex( instance.getQuestId() );
    auto& quest = player.getQuestByIndex( questIdx );
    preQ = quest;
    script->onDutyComplete( instance, player );
    if( quest != preQ )
      player.updateQuest( quest );

    return true;
  }

  return false;
}

bool Sapphire::Scripting::ScriptMgr::onSay( Sapphire::Entity::Player& player, uint64_t actorId, uint32_t eventId, uint32_t sayId )
{
  auto eventType = static_cast< uint16_t >( eventId >> 16 );
  auto& exdData = Common::Service< Data::ExdData >::ref();
  if( eventType == Event::EventHandler::EventHandlerType::Quest )
  {
    auto script = m_nativeScriptMgr->getScript< Sapphire::ScriptAPI::QuestScript >( eventId );
    if( !script )
    {
      auto questInfo = exdData.getRow< Excel::Quest >( eventId );
      if( questInfo )
      {
        World::Manager::PlayerMgr::sendUrgent( player, "Quest not implemented: {0} ({1})", questInfo->getString( questInfo->data().Text.Name ), eventId );
        return false;
      }
    }

    auto& pEventMgr = Common::Service< World::Manager::EventMgr >::ref();
    auto actor = pEventMgr.mapEventActorToRealActor( static_cast< uint32_t >( actorId ) );

    auto questId = static_cast< uint16_t >( eventId );
    if( player.hasQuest( eventId ) )
    {
      World::Quest preQ;
      auto questIdx = player.getQuestIndex( questId );
      auto& quest = player.getQuestByIndex( questIdx );
      preQ = quest;
      script->onSay( quest, player, actor, sayId );
      if( quest != preQ )
        player.updateQuest( quest );
    }
    else
    {
      auto newQuest = World::Quest( questId, 0, 0 );
      script->onSay( newQuest, player, actor, sayId );
    }
    return true;
  }
  return false;
}

