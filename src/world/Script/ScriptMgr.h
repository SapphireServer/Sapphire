#ifndef _ScriptMgr_H_
#define _ScriptMgr_H_

#include <memory>
#include <mutex>
#include <set>

#include <Common.h>
#include <ForwardsCommon.h>
#include "Notifications/Forwards.h"
#include "Territory/InstanceContent.h"

namespace Sapphire::Scripting
{
  class ScriptMgr
  {
  private:
    /*!
     * @brief A shared ptr to NativeScriptMgr, used for accessing and managing the native script system.
     */
    std::shared_ptr< NativeScriptMgr > m_nativeScriptMgr;

    std::function< std::string( Entity::Player& ) > m_onFirstEnterWorld;

    /*!
     * @brief Used to ignore the first change notification that Watchdog emits.
     * Because reasons, it likes to emit an initial notification with all the files that match the filter, we don't want that so we ignore it.
     */
    bool m_firstScriptChangeNotificiation;
    bool m_watchingDirectories{ false };

    void stopWatchingDirectories();

  public:
    ScriptMgr();

    explicit ScriptMgr( std::shared_ptr< NativeScriptMgr > nativeScriptMgr );

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

    void onBNpcKill( const World::Notifications::NpcKillCredited& event );

    void onPlayerDeath( const World::Notifications::PlayerDied& event );

    void onNpcTriggerOwnerDeaggro( const World::Notifications::NpcTriggerOwnerDeaggro& event );

    void onPlayerEventObjectHit( const World::Notifications::PlayerEventObjectHit& event );

    bool onBeforeBootstrap( World::Action::Action& action );

    bool onStart( World::Action::Action& action );

    void onActionInterrupted( const World::Notifications::ActionInterrupted& event );

    bool onExecute( World::Action::Action& action );

    void onActionEffectsBuilt( const World::Notifications::ActionEffectsBuilt& event );

    void onStatusEffectApplied( const World::Notifications::StatusEffectApplied& event );

    bool onStatusTick( Entity::CharaPtr pActor, Sapphire::StatusEffect::StatusEffect& effect );

    void onStatusEffectRemoving( const World::Notifications::StatusEffectRemoving& event );

    void onStatusEffectTargetHit( const World::Notifications::StatusEffectTargetHit& event );

    bool onZoneInit( const Territory& zone );

    bool onEventHandlerReturn( Entity::Player& player, uint32_t eventId, uint16_t subEvent, uint16_t param1,
                               uint16_t param2, uint16_t param3 );

    bool onEventHandlerTradeReturn( Entity::Player& player, uint32_t eventId, uint16_t subEvent, uint16_t param,
                                    uint32_t catalogId );

    bool onInstanceInit( InstanceContent& instance );

    void onInstanceReset( const World::Notifications::InstanceReset& event );

    bool onInstanceUpdate( InstanceContent& instance, uint64_t tickCount );

    void onInstanceStateChange( const World::Notifications::InstanceStateChanged& event );

    bool
    onInstanceEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                              uint16_t param2 );

    void onInstancePlayerRemoved( const World::Notifications::InstancePlayerRemoved& event );

    void onInstanceDirectorSequenceUpdated( const World::Notifications::InstanceDirectorSequenceUpdated& event );

    void onInstanceDirectorFlagsUpdated( const World::Notifications::InstanceDirectorFlagsUpdated& event );

    void onInstanceDirectorVarUpdated( const World::Notifications::InstanceDirectorVarUpdated& event );

    void onInstanceCustomVarUpdated( const World::Notifications::InstanceCustomVarUpdated& event );

    void onInstanceActorDeath( const World::Notifications::InstanceActorDied& event );

    bool onPlayerSetup( QuestBattle& instance, Entity::Player& player );

    bool onInstanceInit( QuestBattle& instance );

    bool onInstanceUpdate( QuestBattle& instance, uint64_t tickCount );

    bool onDutyCommence( QuestBattle& instance, Entity::Player& player );

    bool onInstanceEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                                   uint16_t param2 );

    void onQuestBattleCompleted( const World::Notifications::QuestBattleCompleted& event );

    bool loadDir( const std::string& dirname, std::set< std::string >& files, const std::string& ext );

    NativeScriptMgr& getNativeScriptHandler();
  };
}
#endif
