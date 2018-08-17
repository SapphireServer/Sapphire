#ifndef NATIVE_SCRIPT_API
#define NATIVE_SCRIPT_API

#include <string>
#include <typeinfo>
#include <typeindex>
#include <sapphire_zone/Event/EventHandler.h>
#include "Forwards.h"

#ifdef _MSC_VER
#define EXPORT __declspec( dllexport )
#else
#define EXPORT __attribute__((visibility("default")))
#endif

using namespace Core;

// constant script ids for certain events
#define EVENTSCRIPT_AETHERYTE_ID 0x50000
#define EVENTSCRIPT_AETHERNET_ID 0x50001

class ScriptObject
{
protected:
   uint32_t m_id;
   std::size_t m_type;

public:
   ScriptObject( uint32_t id, std::size_t type ) :
      m_id( id ),
      m_type( type )
   { }

   virtual uint32_t getId() const
   {
      return m_id;
   }

   virtual std::size_t getType() const
   {
      return m_type;
   }
};


class StatusEffectScript : public ScriptObject
{
public:
   explicit StatusEffectScript( uint32_t effectId ) :
      ScriptObject( effectId, typeid( StatusEffectScript ).hash_code() )
   { }

   virtual void onTick( Entity::Chara& actor ) { }
   virtual void onApply( Entity::Chara& actor ) { }
   virtual void onRemove( Entity::Chara& actor ) { }
   virtual void onExpire( Entity::Chara& actor ) { }
   virtual void onPlayerCollision( Entity::Chara& actor, Entity::Chara& actorHit ) { }
   virtual void onPlayerFinishCast( Entity::Chara& actor ) { }
   virtual void onPlayerDamaged( Entity::Chara& actor ) { }
   virtual void onPlayerDeath( Entity::Chara& actor ) { }
};


class ActionScript : public ScriptObject
{
public:
   explicit ActionScript( uint32_t abilityId ) :
      ScriptObject( abilityId, typeid( ActionScript ).hash_code() )
   { }

   virtual void onStart( Entity::Chara& sourceActor, Entity::Chara& targetActor ) { }
   virtual void onCastFinish( Entity::Player& player, Entity::Chara& targetActor ) { }
   virtual void onInterrupt( Entity::Chara& sourceActor/*, Core::Entity::Chara targetActor*/ ) { }
};


class EventScript : public ScriptObject
{
protected:
   template< typename Ret, class Obj >
   inline Event::EventHandler::SceneChainCallback bindScene( Ret ( Obj::*f )( Entity::Player& ) )
   {
      return std::bind( f, static_cast< Obj* >( this ), std::placeholders::_1 );
   }

public:
   explicit EventScript( uint32_t questId ) :
      ScriptObject( questId, typeid( EventScript ).hash_code() )
   { }

   virtual void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) { }
   virtual void onNpcKill( uint32_t npcId, Entity::Player& player ) { }
   virtual void onEmote( uint64_t actorId, uint32_t eventId, uint32_t emoteId, Entity::Player& player ) { }
   virtual void onEnterTerritory( Entity::Player& player, uint32_t eventId, uint16_t param1, uint16_t param2 ) { }
   virtual void onWithinRange( Entity::Player& player, uint32_t eventId, uint32_t param1, float x, float y, float z ) { }
   virtual void onOutsideRange( Entity::Player& player, uint32_t eventId, uint32_t param1, float x, float y, float z ) { }
   virtual void onEventItem( Entity::Player& player, uint32_t eventItemId, uint32_t eventId, uint32_t castTime, uint64_t targetId ) { }
   virtual void onEventHandlerTradeReturn( Entity::Player& player, uint32_t eventId, uint16_t subEvent, uint16_t param, uint32_t catalogId ) { }
};


class BattleNpcScript : public ScriptObject
{
public:
   explicit BattleNpcScript( uint32_t npcId ) :
      ScriptObject( npcId, typeid( BattleNpcScript ).hash_code() )
   { }
};

class ZoneScript : public ScriptObject
{
public:
   explicit ZoneScript( uint32_t zoneId ) :
      ScriptObject( zoneId, typeid( ZoneScript ).hash_code() )
   { }

   virtual void onZoneInit() { }
};

class InstanceContentScript : public ScriptObject
{
public:
   explicit InstanceContentScript( uint32_t instanceContentId ) :
      ScriptObject( uint32_t{ 0x8003 } << 16 | instanceContentId, typeid( InstanceContentScript ).hash_code() )
   { }

   virtual void onInit( InstanceContentPtr instance ) { }
   virtual void onUpdate( InstanceContentPtr instance, uint32_t currTime ) { }
   virtual void onEnterTerritory( InstanceContentPtr instance, Entity::Player& player, uint32_t eventId, uint16_t param1, uint16_t param2 ) { }
};

#endif
