#ifndef _ScriptMgr_H_
#define _ScriptMgr_H_

#include <memory>
#include <mutex>
#include <set>

#include <Common.h>
#include "Forwards.h"

namespace Sapphire::Scripting
{

  class ScriptMgr
  {
  private:
    /*!
     * @brief A shared ptr to NativeScriptMgr, used for accessing and managing the native script system.
     */
    std::shared_ptr< NativeScriptMgr > m_nativeScriptMgr;

    std::function< std::string( Entity::Player & ) > m_onFirstEnterWorld;

    /*!
     * @brief Used to ignore the first change notification that Watchdog emits.
     * Because reasons, it likes to emit an initial notification with all the files that match the filter, we don't want that so we ignore it.
     */
    bool m_firstScriptChangeNotificiation;

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

    bool onYield( Entity::Player& player, uint32_t eventId, uint16_t sceneId, uint8_t resumeId, const std::string& resultString, uint64_t resultInt );

    bool onSay( Entity::Player& player, uint64_t actorId, uint32_t eventId, uint32_t sayId );

    bool onEnterTerritory( Entity::Player& player, uint32_t eventId, uint16_t param1, uint16_t param2 );

    bool onWithinRange( Entity::Player& player, uint32_t eventId, uint32_t param1, float x, float y, float z );

    bool onOutsideRange( Entity::Player& player, uint32_t eventId, uint32_t param1, float x, float y, float z );

    bool onEmote( Entity::Player& player, uint64_t actorId, uint32_t eventId, uint8_t emoteId );

    bool onEventItem( Entity::Player& player, uint32_t eventItemId, uint32_t eventId, uint64_t targetId );

    bool onBNpcKill( Entity::Player& player, Entity::BNpc& bnpc );

    bool onPlayerDeath( Entity::Player& player );

    void onTriggerOwnerDeaggro( Entity::Player& player, Entity::BNpc& bnpc );

    bool onEObjHit( Entity::Player& player, uint64_t actorId, uint32_t actionId );

    bool onStart( World::Action::Action& action );

    bool onInterrupt( World::Action::Action& action );

    bool onExecute( World::Action::Action& action );

    bool onStatusReceive( Entity::CharaPtr pActor, uint32_t effectId );

    bool onStatusTick( Entity::CharaPtr pActor, Sapphire::StatusEffect::StatusEffect& effect );

    bool onStatusTimeOut( Entity::CharaPtr pActor, uint32_t effectId );

    bool onPlayerHit( Sapphire::StatusEffect::StatusEffect& effect, Entity::CharaPtr& attackSource, Entity::CharaPtr& attackTarget, uint32_t& amount, uint32_t actionId );

    bool onZoneInit( const Territory& zone );

    bool onEventHandlerReturn( Entity::Player& player, uint32_t eventId, uint16_t subEvent, uint16_t param1,
                               uint16_t param2, uint16_t param3 );

    bool onEventHandlerTradeReturn( Entity::Player& player, uint32_t eventId, uint16_t subEvent, uint16_t param,
                                    uint32_t catalogId );

    bool onInstanceInit( InstanceContent& instance );

    bool onInstanceUpdate( InstanceContent& instance, uint64_t tickCount );

    bool
    onInstanceEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                              uint16_t param2 );

    bool onInstanceLeaveTerritory( InstanceContent& instance, Entity::Player& player );

    bool onPlayerSetup( QuestBattle& instance, Entity::Player& player );

    bool onInstanceInit( QuestBattle& instance );

    bool onInstanceUpdate( QuestBattle& instance, uint64_t tickCount );

    bool onDutyCommence( QuestBattle& instance, Entity::Player& player );

    bool onInstanceEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                                   uint16_t param2 );

    bool onDutyComplete( QuestBattle& instance, Entity::Player& player );

    bool loadDir( const std::string& dirname, std::set< std::string >& files, const std::string& ext );

    NativeScriptMgr& getNativeScriptHandler();
  };
}
#endif
