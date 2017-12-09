#ifndef NATIVE_SCRIPT_API
#define NATIVE_SCRIPT_API

#include <string>
#include <Server_Zone/Actor/Actor.h>
#include <Server_Zone/Actor/Player.h>
#include <Server_Zone/StatusEffect/StatusEffect.h>

#define EXPORT_SCRIPTOBJECT( type, base ) \
extern "C" __declspec( dllexport ) __cdecl base* get##base() \
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

    std::string getName() const
    {
       return m_scriptName;
    }

    virtual void onScriptUnload( ) { }
};


class StatusEffectScript : ScriptObject
{
protected:
    const uint32_t m_effectId;
    const uint32_t m_baseDuration;
public:
    StatusEffectScript( std::string name, uint32_t effectId, uint32_t duration ) :
       ScriptObject( name ),
       m_effectId( effectId ),
       m_baseDuration( duration )
    { }

    uint32_t getEffectId( ) const
    {
       return m_effectId;
    }

    uint32_t getBaseDuration( ) const
    {
       return m_baseDuration;
    }

    virtual Core::StatusEffect::StatusEffect applyEffect( Core::Entity::Actor sourceActor, Core::Entity::Actor targetActor ) { }
    virtual void onTick(Core::Entity::ActorPtr actor) { }
    virtual void onApply(Core::Entity::ActorPtr actor) { }
    virtual void onRemove( Core::Entity::Actor actor ) { }
    virtual void onExpire(Core::Entity::ActorPtr actor) { }
    virtual void onPlayerCollision( Core::Entity::Actor actor, Core::Entity::Actor actorHit ) { }
    virtual void onPlayerFinishCast( Core::Entity::Actor actor ) { }
    virtual void onPlayerDamaged( Core::Entity::Actor actor ) { }
    virtual bool onPlayerDeath( Core::Entity::Actor actor ) { }
};


class AbilityScript : ScriptObject
{
protected:
    uint32_t m_abilityId;

public:
    AbilityScript( std::string name, uint32_t abilityId ) :
       ScriptObject( name ),
       m_abilityId( abilityId )
    { }

    uint32_t GetAbilityId( )
    {
       return m_abilityId;
    }

    virtual void onStart( Core::Entity::Actor sourceActor, Core::Entity::Actor targetActor ) { }
    virtual bool onCastFinish(Core::Entity::Player player, Core::Entity::ActorPtr targetActor) { }
    virtual void onInterrupt( Core::Entity::Actor sourceActor/*, Core::Entity::Actor targetActor*/ ) { }
};


class QuestScript : ScriptObject
{
protected:
    uint32_t QuestId;
public:
    QuestScript( std::string name, uint32_t questId ) :
       ScriptObject( name ),
       QuestId( questId )
    { }

    virtual void onTalk(uint32_t eventId, Core::Entity::Player player, uint64_t actorId) { }
    virtual void onNpcKill( uint32_t npcId, Core::Entity::Player player ) { }
    virtual void onEmote( uint64_t actorId, uint32_t eventId, uint32_t emoteId, Core::Entity::Player player ) { }
};


class BattleNpcScript : ScriptObject
{
public:
    BattleNpcScript( std::string name ) :
       ScriptObject( name )
    { }
};

class ZoneScript : ScriptObject
{
public:
    ZoneScript( std::string name ) :
       ScriptObject( name )
    { }

    virtual void onZoneInit() { }
    virtual void onEnterZone( Core::Entity::Player pPlayer, uint32_t eventId, uint16_t param1, uint16_t param2 ) { }
};

#endif