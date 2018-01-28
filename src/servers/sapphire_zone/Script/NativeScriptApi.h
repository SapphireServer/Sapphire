#ifndef NATIVE_SCRIPT_API
#define NATIVE_SCRIPT_API

#include "ScriptManager.h"

#include <string>
#include <typeinfo>
#include <typeindex>
#include <utility>

#include <Actor/Actor.h>
#include <Actor/Player.h>
#include <StatusEffect/StatusEffect.h>
#include <common/Logging/Logger.h>
#include <ServerZone.h>
#include <common/Exd/ExdData.h>

#ifdef _MSC_VER
#define EXPORT __declspec( dllexport )
#else
#define EXPORT __attribute__((visibility("default")))
#endif

using namespace Core;

// constant script ids for certain events
#define EVENTSCRIPT_AETHERYTE_ID 0x50000
#define EVENTSCRIPT_AETHERNET_ID 0x50001

class SapphireObjects
{
public:
   SapphireObjects() = default;

   Core::Logger* m_logger;
   Core::ServerZone* m_zone;
   Core::Scripting::ScriptManager* m_scriptMgr;
   Core::Data::ExdData* m_exd;
};

class ScriptObject
{
protected:
   uint32_t m_id;
   std::size_t m_type;
   SapphireObjects* m_objects;

public:
   ScriptObject( uint32_t id, const type_info& type ) :
      m_id( id ),
      m_type( type.hash_code() )
   { }

   virtual uint32_t getId() const
   {
      return m_id;
   }

   virtual void setId( const uint32_t id )
   {
      m_id = id;
   }

   virtual std::size_t getType() const
   {
      return m_type;
   }

   virtual void setObjects( SapphireObjects* ptr )
   {
      m_objects = ptr;
   }
};


class StatusEffectScript : public ScriptObject
{
public:
   explicit StatusEffectScript( uint32_t effectId ) :
      ScriptObject( effectId, typeid( StatusEffectScript ) )
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
   explicit ActionScript( uint32_t abilityId ) :
      ScriptObject( abilityId, typeid( ActionScript ) )
   { }

   virtual void onStart( Entity::Actor& sourceActor, Entity::Actor& targetActor ) { }
   virtual void onCastFinish( Entity::Player& player, Entity::Actor& targetActor ) { }
   virtual void onInterrupt( Entity::Actor& sourceActor/*, Core::Entity::Actor targetActor*/ ) { }
};


class EventScript : public ScriptObject
{
public:
   explicit EventScript( uint32_t questId ) :
      ScriptObject( questId, typeid( EventScript ) )
   { }

   virtual void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) { }
   virtual void onNpcKill( uint32_t npcId, Entity::Player& player ) { }
   virtual void onEmote( uint64_t actorId, uint32_t eventId, uint32_t emoteId, Entity::Player& player ) { }
   virtual void onEnterZone( Entity::Player& player, uint32_t eventId, uint16_t param1, uint16_t param2 ) { }
   virtual void onWithinRange( Entity::Player& player, uint32_t eventId, uint32_t param1, float x, float y, float z ) { }
   virtual void onOutsideRange( Entity::Player& player, uint32_t eventId, uint32_t param1, float x, float y, float z ) { }
   virtual void onEventItem( Entity::Player& player, uint32_t eventItemId, uint32_t eventId, uint32_t castTime, uint64_t targetId ) { }
   virtual void onEventHandlerTradeReturn( Entity::Player& player, uint32_t eventId, uint16_t subEvent, uint16_t param, uint32_t catalogId ) { }
};


class BattleNpcScript : public ScriptObject
{
public:
   explicit BattleNpcScript( uint32_t npcId ) :
      ScriptObject( npcId, typeid( BattleNpcScript ) )
   { }
};

class ZoneScript : public ScriptObject
{
public:
   explicit ZoneScript( uint32_t zoneId ) :
      ScriptObject( zoneId, typeid( ZoneScript ) )
   { }

   virtual void onZoneInit() { }
};

class GmCommandScript : public ScriptObject
{
public:
   explicit GmCommandScript( uint32_t cmdId ) :
      ScriptObject( cmdId, typeid( GmCommandScript ) )
   { }

   virtual void gm1Handler( uint32_t param1, uint32_t param2, uint32_t param3 ) { }
   virtual void gm2Handler( const std::string& param1 ) { }
};

class DebugCommandScript : public ScriptObject
{
protected:
   std::string m_cmd;
   std::string m_helpText;
   uint8_t m_gmLevel;

public:
   explicit DebugCommandScript( const std::string& cmd, const std::string& helpText, uint8_t gmLevel) :
      ScriptObject( 0, typeid( DebugCommandScript ) ),
      m_cmd( cmd ),
      m_helpText( helpText ),
      m_gmLevel( gmLevel )
   { }

   virtual const std::string& getCmd()
   {
      return m_cmd;
   }

   virtual const uint8_t getGmLevel()
   {
      return m_gmLevel;
   }

   virtual const std::string getHelpText()
   {
      return m_helpText;
   }

   virtual void run( Entity::Player& player, const std::string& args, const std::string& subCommand, const std::string& params ) { }
};

#endif