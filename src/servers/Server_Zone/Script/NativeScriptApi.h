#ifndef NATIVE_SCRIPT_API
#define NATIVE_SCRIPT_API

#include <string>
#include <Actor/Actor.h>
#include <Actor/Player.h>
#include <StatusEffect/StatusEffect.h>

#ifdef _MSC_VER
#define EXPORT __declspec( dllexport )
#else
#define EXPORT __attribute__((visibility("default")))
#endif

#define EXPORT_SCRIPTOBJECT( type ) \
extern "C" EXPORT ScriptObject* getScript() \
{ return static_cast< ScriptObject* >( new type ); }

using namespace Core;

enum ScriptType
{
    StatusEffect,
    Action,
    Quest,
    BattleNpc,
    Zone
};

class ScriptObject
{
protected:
   std::string m_scriptName;
   uint32_t m_id;
   ScriptType m_type;

public:
   ScriptObject( std::string name, uint32_t id, ScriptType type ) :
      m_scriptName( name ),
      m_id( id ),
      m_type( type )
   { }

   virtual const std::string& getName() const
   {
      return m_scriptName;
   }

   virtual uint32_t getId() const
   {
      return m_id;
   }

   virtual ScriptType getType() const
   {
      return m_type;
   }
};


class StatusEffectScript : public ScriptObject
{
public:
   StatusEffectScript( std::string name, uint32_t effectId ) :
      ScriptObject( name, effectId, ScriptType::StatusEffect )
   { }

   virtual void onTick( Entity::Actor& actor ) { }
   virtual void onApply( Entity::Actor& actor ) { }
   virtual void onRemove( Entity::Actor& actor ) { }
   virtual void onExpire( Entity::Actor& actor ) { }
   virtual void onPlayerCollision( Entity::Actor& actor, Entity::Actor& actorHit ) { }
   virtual void onPlayerFinishCast( Entity::Actor& actor ) { }
   virtual void onPlayerDamaged( Entity::Actor& actor ) { }
   virtual void onPlayerDeath( Entity::Actor& actor ) { }
};


class ActionScript : public ScriptObject
{
public:
    ActionScript( std::string name, uint32_t abilityId ) :
      ScriptObject( name, abilityId, ScriptType::Action )
   { }

   virtual void onStart( Entity::Actor& sourceActor, Entity::Actor& targetActor ) { }
   virtual void onCastFinish( Entity::Player& player, Entity::Actor& targetActor ) { }
   virtual void onInterrupt( Entity::Actor& sourceActor/*, Core::Entity::Actor targetActor*/ ) { }
};


class QuestScript : public ScriptObject
{
public:
   QuestScript( std::string name, uint32_t questId ) :
      ScriptObject( name, questId, ScriptType::Quest )
   { }

   virtual void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) { }
   virtual void onNpcKill( uint32_t npcId, Entity::Player& player ) { }
   virtual void onEmote( uint64_t actorId, uint32_t eventId, uint32_t emoteId, Entity::Player& player ) { }
};


class BattleNpcScript : public ScriptObject
{
public:
   BattleNpcScript( std::string name, uint32_t npcId ) :
      ScriptObject( name, npcId, ScriptType::BattleNpc )
   { }
};

class ZoneScript : public ScriptObject
{
public:
   ZoneScript( std::string name, uint32_t zoneId ) :
      ScriptObject( name, zoneId, ScriptType::Zone )
   { }

   virtual void onZoneInit() { }
   virtual void onEnterZone( Entity::Player& pPlayer, uint32_t eventId, uint16_t param1, uint16_t param2 ) { }
};

#endif