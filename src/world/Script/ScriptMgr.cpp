#include <algorithm>
#include <cctype>

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

#include "LuaScriptRuntime.h"
#include "NativeScriptMgr.h"
#include "WorldServer.h"

#include "Quest/Quest.h"

using namespace Sapphire::World::Manager;
// enable the ambiguity fix for every platform to avoid #define nonsense
#define WIN_AMBIGUITY_FIX

namespace fs = std::filesystem;

namespace
{
  std::string normalizeScriptBackend( std::string backend )
  {
    std::transform( backend.begin(), backend.end(), backend.begin(),
                    []( unsigned char ch )
                    {
                      return static_cast< char >( std::tolower( ch ) );
                    } );

    if( backend.empty() )
      return "native";

    return backend;
  }

  std::vector< std::string > collectRuntimeDirectories( const std::string& rootDir )
  {
    std::vector< std::string > directories;
    if( !fs::exists( rootDir ) )
      return directories;

    directories.push_back( rootDir );

    for( const auto& entry : fs::recursive_directory_iterator( rootDir ) )
    {
      if( entry.is_directory() )
        directories.push_back( entry.path().string() );
    }

    return directories;
  }

  std::string buildWatchPattern( const std::string& dirname, const std::string& extension )
  {
    return ( fs::path( dirname ) / ( "*" + extension ) ).string();
  }

  std::string describeScriptType( const std::size_t type )
  {
    if( type == typeid( Sapphire::ScriptAPI::EventScript ).hash_code() )
      return "event";
    if( type == typeid( Sapphire::ScriptAPI::QuestScript ).hash_code() )
      return "quest";
    if( type == typeid( Sapphire::ScriptAPI::ActionScript ).hash_code() )
      return "action";
    if( type == typeid( Sapphire::ScriptAPI::StatusEffectScript ).hash_code() )
      return "status";
    if( type == typeid( Sapphire::ScriptAPI::EventObjectScript ).hash_code() )
      return "event_object";
    if( type == typeid( Sapphire::ScriptAPI::ZoneScript ).hash_code() )
      return "zone";
    if( type == typeid( Sapphire::ScriptAPI::InstanceContentScript ).hash_code() )
      return "instance";
    if( type == typeid( Sapphire::ScriptAPI::QuestBattleScript ).hash_code() )
      return "quest_battle";

    return "type#" + std::to_string( type );
  }
}

Sapphire::Scripting::ScriptMgr::ScriptMgr()
{
  auto& server = Common::Service< World::WorldServer >::ref();
  const auto& scriptConfig = server.getConfig().scripts;
  const auto backend = normalizeScriptBackend( scriptConfig.backend );

  m_nativeScriptHandler = createNativeScriptMgr( scriptConfig.cachePath );
  m_nativeScriptMgr = m_nativeScriptHandler;

  if( backend == "native" )
  {
    Logger::info( "ScriptMgr: using native runtime with modules at {0}", scriptConfig.path );
  }
  else if( backend == "lua" )
  {
    m_luaScriptRuntime = createLuaScriptRuntime( scriptConfig.luaPath, scriptConfig.luaHotReload );
    m_preferLuaScripts = true;
    Logger::warn(
      "ScriptMgr: Scripts.Backend=lua is configured. Script lookups now check Lua first. "
      "Only declarative Lua event talk plus quest talk/item/ground-item/emote/object-hit/territory/range/kill handlers are supported in this slice, so other hooks still fall back to native modules at {0} while staging content under {1}.",
      scriptConfig.path, scriptConfig.luaPath );
  }
  else if( backend == "hybrid" )
  {
    m_luaScriptRuntime = createLuaScriptRuntime( scriptConfig.luaPath, scriptConfig.luaHotReload );
    Logger::warn(
      "ScriptMgr: Scripts.Backend=hybrid is configured. Native scripts remain authoritative while Lua modules are loaded and validated from {0}. "
      "This slice only supports declarative Lua event talk plus quest talk/item/ground-item/emote/object-hit/territory/range/kill handlers.",
      scriptConfig.luaPath );
  }
  else
  {
    Logger::warn( "ScriptMgr: unknown Scripts.Backend value '{0}', defaulting to native modules at {1}.",
                  scriptConfig.backend, scriptConfig.path );
  }
}

Sapphire::Scripting::ScriptMgr::~ScriptMgr()
{
  // Ensure watchers are cleared; scripts are ideally unloaded via shutdown() called by WorldServer
  Watchdog::unwatchAll();
}

void Sapphire::Scripting::ScriptMgr::shutdown()
{
  // Stop watching for changes and unload scripts
  Watchdog::unwatchAll();
  if( m_nativeScriptMgr )
  {
    m_nativeScriptMgr->unloadAll();
  }

  if( m_luaScriptRuntime )
  {
    m_luaScriptRuntime->unloadAll();
  }
}

void Sapphire::Scripting::ScriptMgr::update()
{
  m_nativeScriptMgr->processLoadQueue();

  if( m_luaScriptRuntime )
  {
    m_luaScriptRuntime->processLoadQueue();
  }
}

bool Sapphire::Scripting::ScriptMgr::init()
{
  auto& server = Common::Service< World::WorldServer >::ref();
  const auto& scriptConfig = server.getConfig().scripts;
  const auto backend = normalizeScriptBackend( scriptConfig.backend );

  if( !loadRuntimeScripts( *m_nativeScriptMgr, scriptConfig.path, "native", true, false ) )
  {
    Logger::error(
      "ScriptMgr: failed to load modules, the server will not function correctly without scripts loaded." );
    return false;
  }

  if( m_luaScriptRuntime &&
      !loadRuntimeScripts( *m_luaScriptRuntime, scriptConfig.luaPath, "lua", false, true ) )
  {
    Logger::error( "ScriptMgr: failed to stage Lua modules from {0}.", scriptConfig.luaPath );
    return false;
  }

  if( m_luaScriptRuntime && backend != "native" )
    reportLuaShadowedNativeScripts();

  watchDirectories();

  return true;
}

void Sapphire::Scripting::ScriptMgr::watchDirectories()
{
  auto& server = Common::Service< World::WorldServer >::ref();
  const auto& scriptConfig = server.getConfig().scripts;

  watchRuntimeDirectory( m_nativeScriptMgr, scriptConfig.path, scriptConfig.hotSwap, "native" );

  if( m_luaScriptRuntime )
  {
    watchRuntimeDirectory( m_luaScriptRuntime, scriptConfig.luaPath, scriptConfig.luaHotReload, "lua" );
  }
}

bool Sapphire::Scripting::ScriptMgr::loadDir( const std::string& dirname, std::set< std::string >& files,
                                              const std::string& ext )
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

bool Sapphire::Scripting::ScriptMgr::loadRuntimeScripts( IScriptRuntime& runtime, const std::string& dirname,
                                                         const std::string& runtimeName, bool requireScripts,
                                                         bool failOnPartialLoad )
{
  std::set< std::string > files;

  Logger::info( "ScriptMgr: loading {0} scripts from: {1}", runtimeName, dirname );

  if( !fs::exists( dirname ) )
  {
    if( requireScripts )
    {
      Logger::error( "ScriptMgr: {0} scripts directory doesn't exist", runtimeName );
      return false;
    }

    Logger::info( "ScriptMgr: skipping {0} scripts because the directory does not exist yet.", runtimeName );
    return true;
  }

  fs::path targetDir( dirname );
  fs::recursive_directory_iterator iter( targetDir );

  for( const auto& i : iter )
  {
    if( fs::is_regular_file( i ) && fs::path( i ).extension() == runtime.getModuleExtension() )
      files.insert( fs::path( i ).string() );
  }

  if( files.empty() )
  {
    if( requireScripts )
    {
      Logger::error( "ScriptMgr: couldn't find any {0} script modules", runtimeName );
      return false;
    }

    Logger::info( "ScriptMgr: no {0} script modules found in {1}", runtimeName, dirname );
    return true;
  }

  uint32_t scriptsFound = 0;
  uint32_t scriptsLoaded = 0;
  std::vector< std::string > failedScripts;

  for( const auto& path : files )
  {
    scriptsFound++;

    if( runtime.loadScript( path ) )
      scriptsLoaded++;
    else
      failedScripts.push_back( path );
  }

  if( failedScripts.empty() )
  {
    Logger::info( "ScriptMgr: Loaded {0}/{1} {2} modules", scriptsLoaded, scriptsFound, runtimeName );
    return true;
  }

  Logger::error( "ScriptMgr: Loaded {0}/{1} {2} modules. {3} failed to load.", scriptsLoaded, scriptsFound,
                 runtimeName, failedScripts.size() );

  for( const auto& path : failedScripts )
    Logger::error( "ScriptMgr: {0} module failed to load: {1}", runtimeName, path );

  if( failOnPartialLoad )
    return false;

  return true;
}

void Sapphire::Scripting::ScriptMgr::reportLuaShadowedNativeScripts()
{
  if( !m_luaScriptRuntime || !m_nativeScriptMgr )
    return;

  const auto luaRuntime = std::dynamic_pointer_cast< LuaScriptRuntime >( m_luaScriptRuntime );
  if( !luaRuntime )
    return;

  const auto descriptors = luaRuntime->getLoadedScriptDescriptors();
  std::vector< LuaScriptRuntime::LoadedScriptDescriptor > overlaps;
  overlaps.reserve( descriptors.size() );

  for( const auto& descriptor : descriptors )
  {
    if( m_nativeScriptMgr->getScriptObject( descriptor.type, descriptor.id ) )
      overlaps.push_back( descriptor );
  }

  if( overlaps.empty() )
    return;

  const char* precedenceOwner = m_preferLuaScripts ? "Lua" : "Native";
  const char* precedenceVerb = m_preferLuaScripts ? "shadow" : "overlap";
  Logger::warn(
    "ScriptMgr: detected {0} Lua script(s) that {1} an existing native script. {2} remains authoritative for these ids.",
    overlaps.size(), precedenceVerb, precedenceOwner );

  constexpr std::size_t MaxLoggedOverlaps = 10;
  const auto overlapsToLog = std::min( overlaps.size(), MaxLoggedOverlaps );

  for( std::size_t i = 0; i < overlapsToLog; ++i )
  {
    const auto& overlap = overlaps[i];
    Logger::warn(
      "ScriptMgr: Lua {0} script id {1} from module {2} overlaps a native script with the same id. {3} remains authoritative.",
      describeScriptType( overlap.type ), overlap.id, overlap.moduleName, precedenceOwner );
  }

  if( overlaps.size() > MaxLoggedOverlaps )
  {
    Logger::warn( "ScriptMgr: ... plus {0} additional Lua/native script overlap(s).",
                  overlaps.size() - MaxLoggedOverlaps );
  }
}

void Sapphire::Scripting::ScriptMgr::watchRuntimeDirectory( const std::shared_ptr< IScriptRuntime >& runtime,
                                                            const std::string& dirname, bool hotReload,
                                                            const std::string& runtimeName )
{
  if( !hotReload || !runtime )
    return;

  if( !fs::exists( dirname ) )
  {
    Logger::info( "ScriptMgr: skipping {0} script watch because the directory does not exist: {1}", runtimeName,
                  dirname );
    return;
  }

  for( const auto& watchDir : collectRuntimeDirectories( dirname ) )
  {
    auto ignoreInitialNotification = std::make_shared< bool >( true );
    Watchdog::watchMany( buildWatchPattern( watchDir, runtime->getModuleExtension() ),
                         [ runtime, ignoreInitialNotification, runtimeName ]( const std::vector< ci::fs::path >& paths )
                         {
                           if( *ignoreInitialNotification )
                           {
                             // Watchdog emits an initial burst for all matching files. Ignore that for each watcher.
                             *ignoreInitialNotification = false;
                             return;
                           }

                           for( const auto& path : paths )
                           {
                             const auto moduleName = runtime->getModuleNameForPath( path.string() );

                             if( runtime->isModuleLoaded( moduleName ) )
                             {
                               Logger::debug( "Reloading changed {0} script: {1}", runtimeName, moduleName );
                               runtime->queueScriptReload( moduleName );
                             }
                             else
                             {
                               Logger::debug( "Loading new {0} script: {1}", runtimeName, moduleName );
                               runtime->loadScript( path.string() );
                             }
                           }
                         } );
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
    auto script = getScript< Sapphire::ScriptAPI::QuestScript >( eventId );
    if( !script )
    {
      auto questInfo = exdData.getRow< Excel::Quest >( eventId );
      if( questInfo )
      {
        World::Manager::PlayerMgr::sendUrgent( player, "Quest not implemented: {0} ({1})",
                                               questInfo->getString( questInfo->data().Text.Name ), eventId );
        return false;
      }
    }

    auto& pEventMgr = Common::Service< World::Manager::EventMgr >::ref();
    auto actor = pEventMgr.getActorBaseId( static_cast< uint32_t >( actorId ) );

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
    auto script = getScript< Sapphire::ScriptAPI::EventObjectScript >( eobj->getBaseId() );
    if( script )
    {
      script->onTalk( eventId, player, *eobj );
      return true;
    }

    if( auto instance = zone->getAsInstanceContent() )
    {
      auto instanceScript = getScript< Sapphire::ScriptAPI::InstanceContentScript >(
        instance->getDirectorId() );
      if( instanceScript )
      {
        instanceScript->onTalk( *instance, player, *eobj, eventId );
        return true;
      }
    }
  }

  // check for a direct eventid match first, otherwise default to base type
  auto script = getScript< Sapphire::ScriptAPI::EventScript >( eventId );
  if( script )
  {
    script->onTalk( eventId, player, actorId );
    return true;
  }
  script = getScript< Sapphire::ScriptAPI::EventScript >( eventId & 0xFFFF0000 );
  if( script )
  {
    script->onTalk( eventId, player, actorId );
    return true;
  }
  // fallthrough to instance content check
  // todo: this zone check might fumbling it. need testing
  if( auto instance = zone ? zone->getAsInstanceContent() : nullptr )
  {
    auto instanceScript = getScript< Sapphire::ScriptAPI::InstanceContentScript >( instance->getDirectorId() );
    if( instanceScript )
    {
      instanceScript->onTalk( *instance, player, eventId, actorId );
      return true;
    }
  }

  return false;
}

bool Sapphire::Scripting::ScriptMgr::onYield( Entity::Player& player, uint32_t eventId, uint16_t sceneId,
                                              uint8_t resumeId,
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
  auto script = getScript< Sapphire::ScriptAPI::EventScript >( eventId );
  if( script )
  {
    script->onYield( eventId, sceneId, resumeId, player, resultString, resultInt );
    return true;
  }
  else
  {
    script = getScript< Sapphire::ScriptAPI::EventScript >( eventId & 0xFFFF0000 );
    if( !script )
      return false;

    script->onYield( eventId, sceneId, resumeId, player, resultString, resultInt );
    return true;
  }
}

bool Sapphire::Scripting::ScriptMgr::onEnterTerritory( Entity::Player& player, uint32_t eventId, uint16_t param1,
                                                       uint16_t param2 )
{
  const auto eventType = static_cast< uint16_t >( eventId >> 16 );

  if( eventType == Event::EventHandler::EventHandlerType::Quest )
  {
    auto script = getScript< Sapphire::ScriptAPI::QuestScript >( eventId );
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
    auto script = getScript< Sapphire::ScriptAPI::EventScript >( eventId );
    if( !script )
      return false;
    script->onEnterTerritory( player, eventId, param1, param2 );
  }

  return true;
}

bool Sapphire::Scripting::ScriptMgr::onWithinRange( Entity::Player& player, uint32_t eventId, uint32_t param1, float x,
                                                    float y, float z )
{
  const auto eventType = static_cast< uint16_t >( eventId >> 16 );
  auto& pEventMgr = Common::Service< World::Manager::EventMgr >::ref();

  if( eventType == Event::EventHandler::EventHandlerType::Quest )
  {
    auto script = getScript< Sapphire::ScriptAPI::QuestScript >( eventId );
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
  else if( auto script = getScript< Sapphire::ScriptAPI::EventScript >( eventId ) )
  {
    script->onWithinRange( player, eventId, param1, x, y, z );
  }
  else if( auto script = getScript<
    Sapphire::ScriptAPI::ZoneScript >( player.getTerritoryTypeId() ) )
  {
    script->onWithinRange( player, eventId, param1, x, y, z );
  }
  else
  {
    return false;
  }

  return true;
}

bool Sapphire::Scripting::ScriptMgr::onOutsideRange( Entity::Player& player, uint32_t eventId, uint32_t param1, float x,
                                                     float y, float z )
{
  const auto eventType = static_cast< uint16_t >( eventId >> 16 );
  auto& pEventMgr = Common::Service< World::Manager::EventMgr >::ref();

  if( eventType == Event::EventHandler::EventHandlerType::Quest )
  {
    auto script = getScript< Sapphire::ScriptAPI::QuestScript >( eventId );
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
    auto script = getScript< Sapphire::ScriptAPI::EventScript >( eventId );
    if( !script )
      return false;
    script->onOutsideRange( player, eventId, param1, x, y, z );
  }

  return true;
}

bool Sapphire::Scripting::ScriptMgr::onEmote( Entity::Player& player, uint64_t actorId, uint32_t eventId,
                                              uint8_t emoteId )
{
  const auto eventType = static_cast< uint16_t >( eventId >> 16 );

  auto& pEventMgr = Common::Service< World::Manager::EventMgr >::ref();
  auto actor = pEventMgr.getActorBaseId( static_cast< uint32_t >( actorId ) );
  if( eventType == Event::EventHandler::EventHandlerType::Quest )
  {
    auto script = getScript< Sapphire::ScriptAPI::QuestScript >( eventId );
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
    auto script = getScript< Sapphire::ScriptAPI::EventScript >( eventId );
    if( !script )
      return false;
    script->onEmote( actor, eventId, emoteId, player );
  }

  return true;
}

bool Sapphire::Scripting::ScriptMgr::onEventHandlerReturn( Entity::Player& player, uint32_t eventId, uint16_t subEvent,
                                                           uint16_t param1, uint16_t param2,
                                                           uint16_t param3 )
{
  return false;
}

bool Sapphire::Scripting::ScriptMgr::onEventHandlerTradeReturn( Entity::Player& player, uint32_t eventId,
                                                                uint16_t subEvent, uint16_t param, uint32_t catalogId )
{
  auto script = getScript< Sapphire::ScriptAPI::EventScript >( eventId );
  if( script )
  {
    script->onEventHandlerTradeReturn( player, eventId, subEvent, param, catalogId );
    return true;
  }

  return false;
}

bool Sapphire::Scripting::ScriptMgr::onEventItem( Entity::Player& player, uint32_t eventItemId, uint32_t eventId,
                                                  uint64_t targetId )
{
  auto& eventMgr = Common::Service< World::Manager::EventMgr >::ref();
  std::string eventName = "onEventItem";
  std::string objName = eventMgr.getEventName( eventId );
  PlayerMgr::sendDebug( player, "Calling: {0}.{1} - {2}", objName, eventName, eventId );

  auto& pEventMgr = Common::Service< World::Manager::EventMgr >::ref();
  auto actor = pEventMgr.getActorBaseId( static_cast< uint32_t >( targetId ) );

  auto eventType = static_cast< uint16_t >( eventId >> 16 );
  auto& exdData = Common::Service< Data::ExdData >::ref();
  if( eventType == Event::EventHandler::EventHandlerType::Quest )
  {
    auto script = getScript< Sapphire::ScriptAPI::QuestScript >( eventId );
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

bool Sapphire::Scripting::ScriptMgr::onEventGroundItem( Entity::Player& player, uint32_t eventItemId, uint32_t eventId,
                                                        Common::Vector3 pos )
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
    auto script = getScript< Sapphire::ScriptAPI::QuestScript >( eventId );
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

    auto script = getScript< Sapphire::ScriptAPI::QuestScript >( questId );
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

    auto script = getScript< Sapphire::ScriptAPI::QuestScript >( questId );
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

    auto script = getScript< Sapphire::ScriptAPI::QuestScript >( questId );
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
  auto actor = pEventMgr.getActorBaseId( static_cast< uint32_t >( actorId ) );

  for( size_t i = 0; i < 30; i++ )
  {
    auto quest = player.getQuestByIndex( static_cast< uint16_t >( i ) );
    if( quest.getId() == 0 )
      continue;

    uint32_t questId = quest.getId() | Event::EventHandler::EventHandlerType::Quest << 16;

    auto script = getScript< Sapphire::ScriptAPI::QuestScript >( questId );
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
  auto script = getScript< Sapphire::ScriptAPI::ActionScript >( action.getId() );

  if( script )
  {
    script->onExecute( action );
    return true;
  }
  return false;
}

bool Sapphire::Scripting::ScriptMgr::onAfterBuildEffect( World::Action::Action& action )
{
  auto script = getScript< Sapphire::ScriptAPI::ActionScript >( action.getId() );

  if( script )
  {
    script->onAfterBuildEffect( action );
    return true;
  }
  return false;
}

bool Sapphire::Scripting::ScriptMgr::onInterrupt( World::Action::Action& action )
{
  auto script = getScript< Sapphire::ScriptAPI::ActionScript >( action.getId() );

  if( script )
  {
    script->onInterrupt( action );
    return true;
  }
  return false;
}

bool Sapphire::Scripting::ScriptMgr::onBeforeBootstrap( World::Action::Action& action )
{
  if( !m_nativeScriptMgr )
  {
    // Defensive: scripts system not initialized yet
    return false;
  }

  auto script = getScript< Sapphire::ScriptAPI::ActionScript >( action.getId() );

  if( script )
  {
    script->onBeforeBootstrap( action );
    return true;
  }

  return false;
}

bool Sapphire::Scripting::ScriptMgr::onStart( World::Action::Action& action )
{
  auto script = getScript< Sapphire::ScriptAPI::ActionScript >( action.getId() );

  if( script )
  {
    script->onStart( action );
    return true;
  }

  return false;
}

bool Sapphire::Scripting::ScriptMgr::onStatusReceive( Entity::CharaPtr pActor, uint32_t effectId )
{
  auto script = getScript< Sapphire::ScriptAPI::StatusEffectScript >( effectId );

  if( script )
  {
    if( pActor->isPlayer() )
      PlayerMgr::sendDebug( *pActor->getAsPlayer(), "Calling status receive for statusid#{0}", effectId );

    script->onApply( *pActor );
    return true;
  }

  return false;
}

bool Sapphire::Scripting::ScriptMgr::onStatusTick( Entity::CharaPtr pActor,
                                                   Sapphire::StatusEffect::StatusEffect& effect )
{
  auto script = getScript< Sapphire::ScriptAPI::StatusEffectScript >( effect.getId() );
  if( script )
  {
    script->onTick( *pActor, effect );
    return true;
  }

  return false;
}

bool Sapphire::Scripting::ScriptMgr::onStatusTimeOut( Entity::CharaPtr pChara, uint32_t effectId )
{
  auto script = getScript< Sapphire::ScriptAPI::StatusEffectScript >( effectId );
  if( script )
  {
    if( pChara->isPlayer() )
      PlayerMgr::sendDebug( *pChara->getAsPlayer(), "Calling status timeout for statusid#{0}", effectId );

    script->onExpire( *pChara );
    return true;
  }

  return false;
}

bool Sapphire::Scripting::ScriptMgr::onPlayerHit( Entity::CharaPtr& pHitChara,
                                                  Sapphire::StatusEffect::StatusEffect& effect )
{
  auto script = getScript< Sapphire::ScriptAPI::StatusEffectScript >( effect.getId() );
  if( script )
  {
    script->onPlayerHit( *pHitChara, effect );
    return true;
  }

  return false;
}

bool Sapphire::Scripting::ScriptMgr::onZoneInit( const Territory& zone )
{
  auto script = getScript< Sapphire::ScriptAPI::ZoneScript >( zone.getTerritoryTypeId() );
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
  auto script = getScript< Sapphire::ScriptAPI::InstanceContentScript >( instance.getDirectorId() );

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
  auto script = getScript< Sapphire::ScriptAPI::InstanceContentScript >( instance.getDirectorId() );

  if( script )
  {
    script->onReset( instance );

    return true;
  }

  return false;
}

bool Sapphire::Scripting::ScriptMgr::onInstanceUpdate( InstanceContent& instance, uint64_t tickCount )
{
  auto script = getScript< Sapphire::ScriptAPI::InstanceContentScript >( instance.getDirectorId() );

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
  auto script = getScript< Sapphire::ScriptAPI::InstanceContentScript >( instance.getDirectorId() );

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
  auto script = getScript< Sapphire::ScriptAPI::InstanceContentScript >( instance.getDirectorId() );
  if( script )
  {
    script->onEnterTerritory( instance, player, eventId, param1, param2 );
    return true;
  }

  return false;
}

bool Sapphire::Scripting::ScriptMgr::onInstanceLeaveTerritory( InstanceContent& instance, Entity::Player& player )
{
  auto script = getScript< Sapphire::ScriptAPI::InstanceContentScript >( instance.getDirectorId() );
  if( script )
  {
    script->onLeaveTerritory( instance, player );
    return true;
  }

  return false;
}

bool Sapphire::Scripting::ScriptMgr::onInstanceDirectorSeqChange( InstanceContent& instance, uint8_t seq )
{
  auto script = getScript< Sapphire::ScriptAPI::InstanceContentScript >( instance.getDirectorId() );
  if( script )
  {
    script->onDirectorSeqChange( instance, seq );
    return true;
  }

  return false;
}

bool Sapphire::Scripting::ScriptMgr::onInstanceDirectorFlagChange( InstanceContent& instance, uint8_t flag )
{
  auto script = getScript< Sapphire::ScriptAPI::InstanceContentScript >( instance.getDirectorId() );
  if( script )
  {
    script->onDirectorFlagChange( instance, flag );
    return true;
  }

  return false;
}

bool Sapphire::Scripting::ScriptMgr::onInstanceDirectorVarChange( InstanceContent& instance, uint8_t var, uint8_t val )
{
  auto script = getScript< Sapphire::ScriptAPI::InstanceContentScript >( instance.getDirectorId() );
  if( script )
  {
    script->onDirectorVarChange( instance, var, val );
    return true;
  }

  return false;
}

bool Sapphire::Scripting::ScriptMgr::onInstanceCustomVarChange( InstanceContent& instance, uint32_t var, uint64_t val )
{
  auto script = getScript< Sapphire::ScriptAPI::InstanceContentScript >( instance.getDirectorId() );
  if( script )
  {
    script->onCustomVarChange( instance, var, val );
    return true;
  }

  return false;
}

bool Sapphire::Scripting::ScriptMgr::onInstanceActorDeath( InstanceContent& instance, Entity::Chara& chara )
{
  auto script = getScript< Sapphire::ScriptAPI::InstanceContentScript >( instance.getDirectorId() );
  if( script )
  {
    script->onActorDeath( instance, chara );
    return true;
  }

  return false;
}

bool Sapphire::Scripting::ScriptMgr::onPlayerSetup( QuestBattle& instance, Entity::Player& player )
{
  auto script = getScript< Sapphire::ScriptAPI::QuestBattleScript >( instance.getDirectorId() );
  if( script )
  {
    script->onPlayerSetup( instance, player );
    return true;
  }

  return false;
}

bool Sapphire::Scripting::ScriptMgr::onInstanceInit( QuestBattle& instance )
{
  auto script = getScript< Sapphire::ScriptAPI::QuestBattleScript >( instance.getDirectorId() );
  if( script )
  {
    script->onInit( instance );
    return true;
  }

  return false;
}

bool Sapphire::Scripting::ScriptMgr::onInstanceUpdate( QuestBattle& instance, uint64_t tickCount )
{
  auto script = getScript< Sapphire::ScriptAPI::QuestBattleScript >( instance.getDirectorId() );

  if( script )
  {
    script->onUpdate( instance, tickCount );
    return true;
  }

  return false;
}

bool Sapphire::Scripting::ScriptMgr::onDutyCommence( QuestBattle& instance, Entity::Player& player )
{
  auto script = getScript< Sapphire::ScriptAPI::QuestBattleScript >( instance.getDirectorId() );

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
  auto script = getScript< Sapphire::ScriptAPI::QuestBattleScript >( instance.getDirectorId() );
  if( script )
  {
    script->onEnterTerritory( instance, player, eventId, param1, param2 );
    return true;
  }

  return false;
}

Sapphire::Scripting::NativeScriptMgr& Sapphire::Scripting::ScriptMgr::getNativeScriptHandler()
{
  return *m_nativeScriptHandler;
}

Sapphire::Event::EventHandler::QuestAvailability
Sapphire::Scripting::ScriptMgr::getQuestAvailability( Entity::Player& player, uint32_t questId )
{
  if( auto script = getScript< Sapphire::ScriptAPI::QuestScript >( questId ) )
    return script->getQuestAvailability( player, questId );

  return Event::EventHandler::QuestAvailability::Invisible;
}

Sapphire::Scripting::IScriptRuntime& Sapphire::Scripting::ScriptMgr::getScriptRuntime()
{
  return *m_nativeScriptMgr;
}

bool
Sapphire::Scripting::ScriptMgr::onDutyComplete( QuestBattle& instance, Sapphire::Entity::Player& player )
{
  auto script = getScript< Sapphire::ScriptAPI::QuestBattleScript >( instance.getDirectorId() );
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

bool Sapphire::Scripting::ScriptMgr::onSay( Sapphire::Entity::Player& player, uint64_t actorId, uint32_t eventId,
                                            uint32_t sayId )
{
  auto eventType = static_cast< uint16_t >( eventId >> 16 );
  auto& exdData = Common::Service< Data::ExdData >::ref();
  if( eventType == Event::EventHandler::EventHandlerType::Quest )
  {
    auto script = getScript< Sapphire::ScriptAPI::QuestScript >( eventId );
    if( !script )
    {
      auto questInfo = exdData.getRow< Excel::Quest >( eventId );
      if( questInfo )
      {
        World::Manager::PlayerMgr::sendUrgent( player, "Quest not implemented: {0} ({1})",
                                               questInfo->getString( questInfo->data().Text.Name ), eventId );
        return false;
      }
    }

    auto& pEventMgr = Common::Service< World::Manager::EventMgr >::ref();
    auto actor = pEventMgr.getActorBaseId( static_cast< uint32_t >( actorId ) );

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
