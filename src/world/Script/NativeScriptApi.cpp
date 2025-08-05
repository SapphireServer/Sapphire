#include <string>
#include <typeinfo>
#include <typeindex>
#include <Event/EventHandler.h>
#include "NativeScriptApi.h"
#include <cassert>

#ifdef _MSC_VER
#define EXPORT __declspec( dllexport )
#else
#define EXPORT __attribute__((visibility("default")))
#endif

using namespace Sapphire;

namespace Sapphire::ScriptAPI
{
  ScriptObject::ScriptObject( uint32_t id, std::size_t type ) :
    m_id( id ),
    m_type( type )
  {
  }

  uint32_t ScriptObject::getId() const
  {
    return m_id;
  }

  std::size_t ScriptObject::getType() const
  {
    return m_type;
  }

  ///////////////////////////////////////////////////////////////////

  StatusEffectScript::StatusEffectScript( uint32_t effectId ) :
    ScriptObject( effectId, typeid( StatusEffectScript ).hash_code() )
  {
  }

  void StatusEffectScript::onTick( Sapphire::Entity::Chara& actor, Sapphire::StatusEffect::StatusEffect& effect )
  {
  }

  void StatusEffectScript::onApply( Entity::Chara& actor )
  {
  }

  void StatusEffectScript::onRemove( Entity::Chara& actor )
  {
  }

  void StatusEffectScript::onExpire( Entity::Chara& actor )
  {
  }

  void StatusEffectScript::onPlayerCollision( Entity::Chara& actor, Entity::Chara& actorHit )
  {
  }

  void StatusEffectScript::onPlayerFinishCast( Entity::Chara& actor )
  {
  }

  void StatusEffectScript::onPlayerHit( Entity::Chara& hitActor, Sapphire::StatusEffect::StatusEffect& effect )
  {
  }

  void StatusEffectScript::onPlayerDeath( Entity::Chara& actor )
  {
  }

  ///////////////////////////////////////////////////////////////////

  ActionScript::ActionScript( uint32_t actionId ) :
    ScriptObject( actionId, typeid( ActionScript ).hash_code() )
  {
  }

  void ActionScript::onBeforeBootstrap( Sapphire::World::Action::Action& action )
  {
  }

  void ActionScript::onStart( Sapphire::World::Action::Action& action )
  {
  }

  void ActionScript::onExecute( Sapphire::World::Action::Action& action )
  {
  }

  void ActionScript::onInterrupt( Sapphire::World::Action::Action& action )
  {
  }

  void ActionScript::onAfterBuildEffect( Sapphire::World::Action::Action& action )
  {
  }

  ///////////////////////////////////////////////////////////////////

  EventScript::EventScript( uint32_t eventId ) : ScriptObject( eventId, typeid( EventScript ).hash_code() )
  {
  }

  void EventScript::onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId )
  {
  }

  void EventScript::onBNpcKill( uint32_t nameId, Entity::Player& player )
  {
  }

  void EventScript::onEmote( uint64_t actorId, uint32_t eventId, uint32_t emoteId, Entity::Player& player )
  {
  }

  void EventScript::onEnterTerritory( Entity::Player& player, uint32_t eventId, uint16_t param1, uint16_t param2 )
  {
  }

  void EventScript::onWithinRange( Entity::Player& player, uint32_t eventId, uint32_t param1, float x, float y, float z )
  {
  }

  void EventScript::onOutsideRange( Entity::Player& player, uint32_t eventId, uint32_t param1, float x, float y, float z )
  {
  }

  //void EventScript::onEventItem( Entity::Player& player, Entity::Player& player, uint64_t actorId )
  //{
  //}

  void EventScript::onEventHandlerTradeReturn( Entity::Player& player, uint32_t eventId, uint16_t subEvent, uint16_t param,
                                              uint32_t catalogId )
  {
  }

  void EventScript::onEObjHit( Sapphire::Entity::Player& player, uint64_t actorId, uint32_t actionId )
  {
  }

  void EventScript::onYield( uint32_t eventId, uint16_t sceneId, uint8_t yieldId, Entity::Player& player, const std::string& resultString, uint64_t resultInt )
  {
    eventMgr().resumeScene( player, eventId, sceneId, yieldId, { 0 } );
  }

  ///////////////////////////////////////////////////////////////////

  QuestScript::QuestScript( uint32_t eventId ) : ScriptObject( eventId, typeid( QuestScript ).hash_code() )
  {
  }

  void QuestScript::onTalk( World::Quest& quest, Entity::Player& player, uint64_t actorId )
  {
  }

  void QuestScript::onSay( World::Quest& quest, Entity::Player& player, uint64_t actorId, uint32_t sayId )
  {
  }

  void QuestScript::onEventItem( World::Quest& quest, Entity::Player& player, uint64_t actorId )
  {
  }

  void QuestScript::onBNpcKill( World::Quest& quest, Entity::BNpc& bnpc, Entity::Player& player )
  {
  }

  void QuestScript::onTriggerOwnerDeaggro( World::Quest& quest, Entity::BNpc& bnpc, Entity::Player& player )
  {
  }

  void QuestScript::onEmote( World::Quest& quest, uint64_t actorId, uint32_t emoteId, Entity::Player& player )
  {
  }

  void QuestScript::onEnterTerritory( World::Quest& quest, Entity::Player& player, uint16_t param1, uint16_t param2 )
  {
  }

  void QuestScript::onWithinRange( World::Quest& quest, Entity::Player& player, uint32_t eventId, uint32_t param1, float x, float y, float z )
  {
  }

  void QuestScript::onOutsideRange( World::Quest& quest, Entity::Player& player, uint32_t eventId, uint32_t param1, float x, float y, float z )
  {
  }

  void QuestScript::onEventHandlerTradeReturn( Entity::Player& player, uint32_t eventId, uint16_t subEvent, uint16_t param, uint32_t catalogId )
  {
  }

  void QuestScript::onEObjHit( World::Quest& quest, Sapphire::Entity::Player& player, uint64_t actorId, uint32_t actionId )
  {
  }

  void QuestScript::onPlayerDeath( World::Quest& quest, Sapphire::Entity::Player& player )
  {
  }

  Event::EventHandler::QuestAvailability QuestScript::getQuestAvailability( Sapphire::Entity::Player& player, uint32_t eventId )
  {
    return Event::EventHandler::QuestAvailability::Available;
  }

  ///////////////////////////////////////////////////////////////////

  EventObjectScript::EventObjectScript( uint32_t eobjId ) : ScriptObject( eobjId, typeid( EventObjectScript ).hash_code() )
  {
  }

  void EventObjectScript::onTalk( uint32_t eventId, Sapphire::Entity::Player& player, Entity::EventObject& eobj )
  {
  }

  ///////////////////////////////////////////////////////////////////

  BattleNpcScript::BattleNpcScript( uint32_t npcId ) :
    ScriptObject( npcId, typeid( BattleNpcScript ).hash_code() )
  {
  }

  ///////////////////////////////////////////////////////////////////

  ZoneScript::ZoneScript( uint32_t zoneId ) :
    ScriptObject( zoneId, typeid( ZoneScript ).hash_code() )
  {
  }

  void ZoneScript::onZoneInit()
  {
  }

  ///////////////////////////////////////////////////////////////////

  InstanceContentScript::InstanceContentScript( uint32_t instanceContentId ) :
    ScriptObject( uint32_t{ 0x8003 } << 16 | instanceContentId, typeid( InstanceContentScript ).hash_code() )
  {
  }

  void InstanceContentScript::onInit( InstanceContent& instance )
  {
  }

  void InstanceContentScript::onReset( InstanceContent& instance )
  {
  }

  void InstanceContentScript::onTalk( Sapphire::InstanceContent& instance, Sapphire::Entity::Player& player, Sapphire::Entity::EventObject& eobj, 
                                      uint32_t eventId )
  {
  }

  void InstanceContentScript::onTalk( Sapphire::InstanceContent& instance, Sapphire::Entity::Player& player, uint32_t eventId, 
                                      uint64_t actorId )
  {
  }

  void InstanceContentScript::onUpdate( InstanceContent& instance, uint64_t tickCount )
  {
  }

  void InstanceContentScript::onStateChange( InstanceContent& instance,
                                             InstanceContentState oldState,
                                             InstanceContentState newState )
  {
  }

  void InstanceContentScript::onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId,
                                                uint16_t param1, uint16_t param2 )
  {
  }

  void InstanceContentScript::onLeaveTerritory( InstanceContent& instance, Entity::Player& player )
  {
  }

  ///////////////////////////////////////////////////////////////////

  QuestBattleScript::QuestBattleScript( uint32_t questBattleId ) :
    ScriptObject( uint32_t{ 0x8006 } << 16 | questBattleId, typeid( QuestBattleScript ).hash_code() )
  {
  }

  void QuestBattleScript::onDutyComplete( Sapphire::QuestBattle& instance, Entity::Player& player )
  {

  }

  void QuestBattleScript::onPlayerSetup( Sapphire::QuestBattle& instance, Entity::Player& player )
  {
  }

  void QuestBattleScript::onInit( QuestBattle& instance )
  {
  }

  void QuestBattleScript::onUpdate( QuestBattle& instance, uint64_t tickCount )
  {
  }

  void QuestBattleScript::onDutyCommence( QuestBattle& instance, Entity::Player& player )
  {
  }

  void QuestBattleScript::onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId,
                                            uint16_t param1, uint16_t param2 )
  {
  }
}

