#include <string>
#include <typeinfo>
#include <typeindex>
#include <Event/EventHandler.h>
#include "NativeScriptApi.h"

#ifdef _MSC_VER
#define EXPORT __declspec( dllexport )
#else
#define EXPORT __attribute__((visibility("default")))
#endif

using namespace Core;

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

void StatusEffectScript::onTick( Entity::Chara& actor )
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

void StatusEffectScript::onPlayerDamaged( Entity::Chara& actor )
{
}

void StatusEffectScript::onPlayerDeath( Entity::Chara& actor )
{
}

///////////////////////////////////////////////////////////////////

ActionScript::ActionScript( uint32_t abilityId ) :
  ScriptObject( abilityId, typeid( ActionScript ).hash_code() )
{
}

void ActionScript::onStart( Entity::Chara& sourceActor, Entity::Chara& targetActor )
{
}

void ActionScript::onCastFinish( Entity::Player& player, Entity::Chara& targetActor )
{
}

void ActionScript::onInterrupt( Entity::Chara& sourceActor/*, Core::Entity::Chara targetActor*/ )
{
}

///////////////////////////////////////////////////////////////////

EventScript::EventScript( uint32_t questId ) :
  ScriptObject( questId, typeid( EventScript ).hash_code() )
{
}

void EventScript::onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId )
{
}

void EventScript::onNpcKill( uint32_t npcId, Entity::Player& player )
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

void
  EventScript::onEventItem( Entity::Player& player, uint32_t eventItemId, uint32_t eventId, uint32_t castTime, uint64_t targetId )
{
}

void EventScript::onEventHandlerTradeReturn( Entity::Player& player, uint32_t eventId, uint16_t subEvent, uint16_t param,
                                             uint32_t catalogId )
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

void InstanceContentScript::onInit( InstanceContentPtr instance )
{
}

void InstanceContentScript::onUpdate( InstanceContentPtr instance, uint32_t currTime )
{
}

void InstanceContentScript::onEnterTerritory( InstanceContentPtr instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                                              uint16_t param2 )
{
}

