#ifndef _ScriptMgr_H_
#define _ScriptMgr_H_

#include <memory>
#include <mutex>
#include <set>

#include <Common.h>
#include "IScriptRuntime.h"
#include "Forwards.h"
#include "Territory/InstanceContent.h"

namespace Sapphire::Scripting
{
  class ScriptMgr
  {
  private:
    /*!
     * @brief Active script runtime used by ScriptMgr dispatch.
     *
     * This is intentionally abstract so we can introduce Lua or hybrid backends without
     * rewriting the event dispatch surface all at once.
     */
    std::shared_ptr< IScriptRuntime > m_nativeScriptMgr;

    /*!
     * @brief Back-compat handle for native-only admin/debug flows.
     *
     * Existing callers outside ScriptMgr still reach for NativeScriptMgr directly.
     * Keep this until those surfaces are moved onto runtime-agnostic APIs.
     */
    std::shared_ptr< NativeScriptMgr > m_nativeScriptHandler;

    /*!
     * @brief Placeholder Lua runtime used to stage the migration surface.
     *
     * Keep the runtime alive so staged Lua content can be validated, looked up according to
     * the active backend preference, and checked for Lua/native collisions during startup.
     */
    std::shared_ptr< IScriptRuntime > m_luaScriptRuntime;
    bool m_preferLuaScripts{ false };

    std::function< std::string( Entity::Player& ) > m_onFirstEnterWorld;

    /*!
     * @brief Used to ignore the first change notification that Watchdog emits.
     * Because reasons, it likes to emit an initial notification with all the files that match the filter, we don't want that so we ignore it.
     */
    bool loadRuntimeScripts( IScriptRuntime& runtime, const std::string& dirname, const std::string& runtimeName,
                             bool requireScripts, bool failOnPartialLoad );

    void watchRuntimeDirectory( const std::shared_ptr< IScriptRuntime >& runtime, const std::string& dirname,
                                bool hotReload, const std::string& runtimeName );

    void reportLuaShadowedNativeScripts();

    template< typename T >
    T* getScript( uint32_t scriptId )
    {
      if( m_preferLuaScripts && m_luaScriptRuntime )
      {
        if( auto script = m_luaScriptRuntime->getScript< T >( scriptId ) )
          return script;
      }

      if( m_nativeScriptMgr )
      {
        if( auto script = m_nativeScriptMgr->getScript< T >( scriptId ) )
          return script;
      }

      if( !m_preferLuaScripts && m_luaScriptRuntime )
        return m_luaScriptRuntime->getScript< T >( scriptId );

      return nullptr;
    }

  public:
    ScriptMgr();

    ~ScriptMgr();

    /*!
     * @brief Loads all the script modules and readies the ScriptMgr
     *
     * This gets all the modules inside the specified scripts folder and then attempts to load each one.
     * After that, it starts the directory watcher so the server can reload modules at runtime when changes occur.
     *
     * @return true if init success
     */
    bool init();

    // Gracefully stop watching and unload all scripts so that a new init() can reload them cleanly.
    void shutdown();

    /*!
     * @brief Called on each tick or at a regular interval. Allows for the NativeScriptMgr to process module loading and reloading.
     */
    void update();

    /*!
     * @brief Registers a directory watcher which allows for script modules to be reloaded when changes to the modules occur
     */
    void watchDirectories();

    void onPlayerFirstEnterWorld( Entity::Player& player );

    bool onTalk( Entity::Player& player, uint64_t actorId, uint32_t eventId );

    bool onYield( Entity::Player& player, uint32_t eventId, uint16_t sceneId, uint8_t resumeId,
                  const std::string& resultString, uint64_t resultInt );

    bool onSay( Entity::Player& player, uint64_t actorId, uint32_t eventId, uint32_t sayId );

    bool onEnterTerritory( Entity::Player& player, uint32_t eventId, uint16_t param1, uint16_t param2 );

    bool onWithinRange( Entity::Player& player, uint32_t eventId, uint32_t param1, float x, float y, float z );

    bool onOutsideRange( Entity::Player& player, uint32_t eventId, uint32_t param1, float x, float y, float z );

    bool onEmote( Entity::Player& player, uint64_t actorId, uint32_t eventId, uint8_t emoteId );

    bool onEventItem( Entity::Player& player, uint32_t eventItemId, uint32_t eventId, uint64_t targetId );

    bool onEventGroundItem( Entity::Player& player, uint32_t eventItemId, uint32_t eventId,
                            Common::Vector3 pos );

    bool onBNpcKill( Entity::Player& player, Entity::BNpc& bnpc );

    bool onPlayerDeath( Entity::Player& player );

    void onTriggerOwnerDeaggro( Entity::Player& player, Entity::BNpc& bnpc );

    bool onEObjHit( Entity::Player& player, uint64_t actorId, uint32_t actionId );

    bool onBeforeBootstrap( World::Action::Action& action );

    bool onStart( World::Action::Action& action );

    bool onInterrupt( World::Action::Action& action );

    bool onExecute( World::Action::Action& action );

    bool onAfterBuildEffect( World::Action::Action& action );

    bool onStatusReceive( Entity::CharaPtr pActor, uint32_t effectId );

    bool onStatusTick( Entity::CharaPtr pActor, Sapphire::StatusEffect::StatusEffect& effect );

    bool onStatusTimeOut( Entity::CharaPtr pActor, uint32_t effectId );

    bool onPlayerHit( Entity::CharaPtr& pHitChara, Sapphire::StatusEffect::StatusEffect& effect );

    bool onZoneInit( const Territory& zone );

    bool onEventHandlerReturn( Entity::Player& player, uint32_t eventId, uint16_t subEvent, uint16_t param1,
                               uint16_t param2, uint16_t param3 );

    bool onEventHandlerTradeReturn( Entity::Player& player, uint32_t eventId, uint16_t subEvent, uint16_t param,
                                    uint32_t catalogId );

    bool onInstanceInit( InstanceContent& instance );

    bool onInstanceReset( InstanceContent& instance );

    bool onInstanceUpdate( InstanceContent& instance, uint64_t tickCount );

    bool onInstanceStateChange( InstanceContent& instance,
                                InstanceContentState oldState,
                                InstanceContentState newState );

    bool
    onInstanceEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                              uint16_t param2 );

    bool onInstanceLeaveTerritory( InstanceContent& instance, Entity::Player& player );

    bool onInstanceDirectorSeqChange( InstanceContent& instance, uint8_t seq );

    bool onInstanceDirectorFlagChange( InstanceContent& instance, uint8_t flag );

    bool onInstanceDirectorVarChange( InstanceContent& instance, uint8_t var, uint8_t val );

    bool onInstanceCustomVarChange( InstanceContent& instance, uint32_t var, uint64_t val );

    bool onInstanceActorDeath( InstanceContent& instance, Entity::Chara& chara );

    bool onPlayerSetup( QuestBattle& instance, Entity::Player& player );

    bool onInstanceInit( QuestBattle& instance );

    bool onInstanceUpdate( QuestBattle& instance, uint64_t tickCount );

    bool onDutyCommence( QuestBattle& instance, Entity::Player& player );

    bool onInstanceEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                                   uint16_t param2 );

    bool onDutyComplete( QuestBattle& instance, Entity::Player& player );

    bool loadDir( const std::string& dirname, std::set< std::string >& files, const std::string& ext );

    Event::EventHandler::QuestAvailability getQuestAvailability( Entity::Player& player, uint32_t questId );

    IScriptRuntime& getScriptRuntime();
    NativeScriptMgr& getNativeScriptHandler();
  };
}
#endif
