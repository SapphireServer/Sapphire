#ifndef NATIVE_SCRIPT_API
#define NATIVE_SCRIPT_API

#include <string>
#include <Actor/Actor.h>
#include <Actor/Player.h>
#include <StatusEffect/StatusEffect.h>

#define EXPORT_SCRIPTOBJECT( type, base ) \
extern "C" __declspec( dllexport ) base* get##base() \
{ return static_cast< base* >( new type ); }

#define EXPORT_STATUSEFFECTSCRIPT( type ) EXPORT_SCRIPTOBJECT( type, StatusEffectScript )
#define EXPORT_ABILITYSCRIPT( type ) EXPORT_SCRIPTOBJECT( type, AbilityScript )
#define EXPORT_QUESTSCRIPT( type ) EXPORT_SCRIPTOBJECT( type, QuestScript )
#define EXPORT_BATTLENPCSCRIPT( type ) EXPORT_SCRIPTOBJECT( type, BattleNpcScript )
#define EXPORT_ZONESCRIPT( type ) EXPORT_SCRIPTOBJECT( type, ZoneScript )

class ScriptObject
{
protected:
   const std::string m_scriptName;

public:
   ScriptObject( std::string name ) :
      m_scriptName( name )
   { }

   const std::string getName()
   {
      return m_scriptName;
   }
};


class StatusEffectScript : public ScriptObject
{
protected:
    const uint32_t m_effectId;

public:
   StatusEffectScript( std::string name, uint32_t effectId ) :
      ScriptObject( name ),
      m_effectId( effectId )
   { }

   const uint32_t getEffectId( )
   {
      return m_effectId;
   }

   virtual void onTick( Core::Entity::ActorPtr actor ) { }
   virtual void onApply( Core::Entity::ActorPtr actor ) { }
   virtual void onRemove( Core::Entity::ActorPtr actor ) { }
   virtual void onExpire(Core::Entity::ActorPtr actor) { }
   virtual void onPlayerCollision( Core::Entity::ActorPtr actor, Core::Entity::ActorPtr actorHit ) { }
   virtual void onPlayerFinishCast( Core::Entity::ActorPtr actor ) { }
   virtual void onPlayerDamaged( Core::Entity::ActorPtr actor ) { }
   virtual void onPlayerDeath( Core::Entity::ActorPtr actor ) { }
};


class ActionScript : public ScriptObject
{
protected:
    const uint32_t m_actionId;

public:
    ActionScript( std::string name, uint32_t abilityId ) :
      ScriptObject( name ),
      m_actionId( abilityId )
   { }

   const uint32_t getActionId()
   {
      return m_actionId;
   }

   virtual void onStart( Core::Entity::Actor sourceActor, Core::Entity::ActorPtr targetActor ) { }
   virtual void onCastFinish( Core::Entity::Player player, Core::Entity::ActorPtr targetActor ) { }
   virtual void onInterrupt( Core::Entity::Actor sourceActor/*, Core::Entity::Actor targetActor*/ ) { }
};


class QuestScript : public ScriptObject
{
protected:
   const uint32_t m_questId;

public:
   QuestScript( std::string name, uint32_t questId ) :
      ScriptObject( name ),
      m_questId( questId )
   { }

   const uint32_t getQuestId()
   {
      return m_questId;
   }

   virtual void onTalk(uint32_t eventId, Core::Entity::Player player, uint64_t actorId) { }
   virtual void onNpcKill( uint32_t npcId, Core::Entity::Player player ) { }
   virtual void onEmote( uint64_t actorId, uint32_t eventId, uint32_t emoteId, Core::Entity::Player player ) { }
};


class BattleNpcScript : public ScriptObject
{
protected:
    const uint32_t m_npcId;

public:
   BattleNpcScript( std::string name, uint32_t npcId ) :
      ScriptObject( name ),
      m_npcId( npcId )
   { }

   const uint32_t getNpcId()
   {
      return m_npcId;
   }
};

class ZoneScript : public ScriptObject
{
protected:
   const uint32_t m_zoneId;

public:
   ZoneScript( std::string name, uint32_t zoneId ) :
      ScriptObject( name ),
      m_zoneId( zoneId )
   { }

   const uint32_t getZoneId()
   {
      return m_zoneId;
   }

   virtual void onZoneInit() { }
   virtual void onEnterZone( Core::Entity::Player pPlayer, uint32_t eventId, uint16_t param1, uint16_t param2 ) { }
};

#endif