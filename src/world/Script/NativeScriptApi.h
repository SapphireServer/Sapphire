#ifndef NATIVE_SCRIPT_API
#define NATIVE_SCRIPT_API

#include <string>
#include "ForwardsZone.h"
#include "Event/EventHandler.h"
#include "Manager/EventMgr.h"
#include "Manager/LinkshellMgr.h"
#include "Manager/PlayerMgr.h"
#include "Manager/TerritoryMgr.h"
#include "Manager/WarpMgr.h"
#include "Exd/ExdData.h"
#include "Territory/InstanceObjectCache.h"
#include "Service.h"

#ifdef _MSC_VER
#define EXPORT __declspec( dllexport )
#else
#define EXPORT __attribute__((visibility("default")))
#endif

namespace Sapphire
{
  class Framework;
}

namespace Sapphire::ScriptAPI
{
  /*!
  * @brief The base class that any script should inherit from and set the type param accordingly
  */
  class ScriptObject
  {
  protected:
    uint32_t m_id;
    std::size_t m_type;

  public:
    /*!
    * @param id an ID which uniquely identifies this script in relation to it's type
    * @param type The RTTI hash code of the implementing type to uniquely identify it
    */
    ScriptObject( uint32_t id, std::size_t type );

    /*!
    * @brief Gets the ID set for this script
    *
    * @return The allocated ID of the script set during object construction
    */
    virtual uint32_t getId() const;

    /*!
    * @brief Gets the unique identifier (hash_code) of the script
    *
    * @return The hash_code of the script
    */
    virtual std::size_t getType() const;
  };


  /*!
  * @brief The base class for any scripts that implement behaviour related to status effects.
  */
  class StatusEffectScript : public ScriptObject
  {
  public:
    explicit StatusEffectScript( uint32_t effectId );

    /*!
    * @brief Called on each tick that a status effect is active on an actor
    *
    * @param actor the actor the status effect is ticking on
    */
    virtual void onTick( Sapphire::Entity::Chara& actor );

    /*!
    * @brief Called when the status effect is applied to an actor
    *
    * @param actor the actor on which the status effect was applied to
    */
    virtual void onApply( Sapphire::Entity::Chara& actor );

    /*!
    * @brief Called when the actor (usually a player) removes the status effect by right clicking it
    *
    * @param actor The actor on which the effect was removed from
    */
    virtual void onRemove( Sapphire::Entity::Chara& actor );

    /*!
    * @brief Called when the status effect expires
    *
    * @param actor The actor on which the efect expired on
    */
    virtual void onExpire( Sapphire::Entity::Chara& actor );

    /*!
    * @brief Called when the player with the status effect collides with another player, eg. hot potato
    *
    * @param actor The actor which has status effect
    * @param actorHit The actor who collided with the status effect owner
    */
    virtual void onPlayerCollision( Sapphire::Entity::Chara& actor, Sapphire::Entity::Chara& actorHit );

    /*!
    * @brief Called when the owner finishes a cast
    *
    * @param actor The actor who finished a cast
    */
    virtual void onPlayerFinishCast( Sapphire::Entity::Chara& actor );

    /*!
    * @brief Called when the status effect owner was damaged
    *
    * @param actor The actor that was damaged
    */
    virtual void onPlayerDamaged( Sapphire::Entity::Chara& actor );

    /*!
    * @brief Called when the status effect owner dies
    *
    * @param actor The actor that died
    */
    virtual void onPlayerDeath( Sapphire::Entity::Chara& actor );
  };


  /*!
  * @brief The base class for any scripts that implement behaviour related to actions
  */
  class ActionScript :  public ScriptObject
  {
  public:
    explicit ActionScript( uint32_t actionId );

    virtual void onStart( Sapphire::World::Action::Action& action );

    virtual void onExecute( Sapphire::World::Action::Action& action );

    virtual void onInterrupt( Sapphire::World::Action::Action& action );

    World::Manager::WarpMgr& warpMgr()
    {
      return Common::Service< World::Manager::WarpMgr >::ref();
    }
  };

  /*!
  * @brief The base class for any scripts that implement behaviour related to the event system.
  * This includes but is not limited to: NPCs, shops, some world objects
  */
  class EventScript : public ScriptObject
  {
  protected:
    template< typename Ret, class Obj >
    inline std::function< void( Sapphire::Entity::Player& ) > bindScene( Ret ( Obj::*f )( Sapphire::Entity::Player& ) )
    {
      return std::bind( f, static_cast< Obj* >( this ), std::placeholders::_1 );
    }
    template< typename Ret, class Obj >
    inline std::function< void( Entity::Player& player, const Event::SceneResult& result ) >
    bindSceneReturn( Ret ( Obj::*f )( Entity::Player& player, const Event::SceneResult& result ) )
    {
      return std::bind( f, static_cast< Obj* >( this ), std::placeholders::_1, std::placeholders::_2 );
    }

  public:
    explicit EventScript( uint32_t eventId );

    virtual void onTalk( uint32_t eventId, Sapphire::Entity::Player& player, uint64_t actorId );

    virtual void onBNpcKill( uint32_t nameId, Sapphire::Entity::Player& player );

    virtual void onEmote( uint64_t actorId, uint32_t eventId, uint32_t emoteId, Sapphire::Entity::Player& player );

    virtual void onEnterTerritory( Sapphire::Entity::Player& player, uint32_t eventId, uint16_t param1, uint16_t param2 );

    virtual void onWithinRange( Sapphire::Entity::Player& player, uint32_t eventId, uint32_t param1, float x, float y, float z );

    virtual void onOutsideRange( Sapphire::Entity::Player& player, uint32_t eventId, uint32_t param1, float x, float y, float z );

    //virtual void onEventItem( World::Quest& quest, Entity::Player& player, uint64_t actorId );

    virtual void onEventHandlerTradeReturn( Sapphire::Entity::Player& player, uint32_t eventId, uint16_t subEvent, uint16_t param,
                                            uint32_t catalogId );

    virtual void onEObjHit( Sapphire::Entity::Player& player, uint64_t actorId, uint32_t actionId );

    virtual void onYield( uint32_t eventId, uint16_t sceneId, uint8_t yieldId, Entity::Player& player, const std::string& resultString, uint64_t returnInt );

    Data::ExdData& exdData()
    {
      return Common::Service< Data::ExdData >::ref();
    }

    World::Manager::EventMgr& eventMgr()
    {
      return Common::Service< World::Manager::EventMgr >::ref();
    }

    World::Manager::LinkshellMgr& linkshellMgr()
    {
      return Common::Service< World::Manager::LinkshellMgr >::ref();
    }

    World::Manager::PlayerMgr& playerMgr()
    {
      return Common::Service< World::Manager::PlayerMgr >::ref();
    }

    World::Manager::WarpMgr& warpMgr()
    {
      return Common::Service< World::Manager::WarpMgr >::ref();
    }

    Sapphire::InstanceObjectCache& instanceObjectCache()
    {
      return Common::Service< Sapphire::InstanceObjectCache >::ref();
    }

    World::Manager::TerritoryMgr& teriMgr()
    {
      return Common::Service< World::Manager::TerritoryMgr >::ref();
    }
  };

  class QuestScript : public ScriptObject
  {
  protected:
    template< typename Ret, class Obj >
    inline std::function< void( Sapphire::Entity::Player& ) > bindScene( Ret ( Obj::*f )( Sapphire::Entity::Player& ) )
    {
      return std::bind( f, static_cast< Obj* >( this ), std::placeholders::_1 );
    }

    template< typename Ret, class Obj >
    inline std::function< void( World::Quest&, Sapphire::Entity::Player& ) > bindQuestScene( Ret ( Obj::*f )( World::Quest&, Sapphire::Entity::Player& ) )
    {
      return std::bind( f, static_cast< Obj* >( this ), std::placeholders::_1, std::placeholders::_2 );
    }

    template< typename Ret, class Obj >
    inline std::function< void( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result ) >
      bindSceneReturn( Ret ( Obj::*f )( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result ) )
    {
      return std::bind( f, static_cast< Obj* >( this ), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3 );
    }

  public:
    explicit QuestScript( uint32_t eventId );

    virtual void onTalk( World::Quest& quest, Sapphire::Entity::Player& player, uint64_t actorId );

    virtual void onSay( World::Quest& quest, Sapphire::Entity::Player& player, uint64_t actorId, uint32_t sayId );

    virtual void onEventItem( World::Quest& quest, Sapphire::Entity::Player& player, uint64_t actorId );

    virtual void onBNpcKill( World::Quest& quest, Entity::BNpc& bnpc, Entity::Player& player );

    virtual void onTriggerOwnerDeaggro( World::Quest& quest, Sapphire::Entity::BNpc& bnpc, Sapphire::Entity::Player& player );

    virtual void onEmote( World::Quest& quest, uint64_t actorId, uint32_t emoteId, Sapphire::Entity::Player& player );

    virtual void onEnterTerritory( World::Quest& quest, Sapphire::Entity::Player& player, uint16_t param1, uint16_t param2 );

    virtual void onWithinRange( World::Quest& quest, Sapphire::Entity::Player& player, uint32_t eventId, uint32_t param1, float x, float y, float z );

    virtual void onOutsideRange( World::Quest& quest, Sapphire::Entity::Player& player, uint32_t eventId, uint32_t param1, float x, float y, float z );

    virtual void onPlayerDeath( World::Quest& quest, Sapphire::Entity::Player& player );

    virtual void onEventHandlerTradeReturn( Sapphire::Entity::Player& player, uint32_t eventId, uint16_t subEvent, uint16_t param, uint32_t catalogId );

    virtual void onEObjHit( World::Quest& quest, Sapphire::Entity::Player& player, uint64_t actorId, uint32_t actionId );

    virtual Event::EventHandler::QuestAvailability getQuestAvailability( Sapphire::Entity::Player& player, uint32_t eventId );

    World::Manager::EventMgr& eventMgr()
    {
      return Common::Service< World::Manager::EventMgr >::ref();
    }

    World::Manager::PlayerMgr& playerMgr()
    {
      return Common::Service< World::Manager::PlayerMgr >::ref();
    }

    World::Manager::TerritoryMgr& teriMgr()
    {
      return Common::Service< World::Manager::TerritoryMgr >::ref();
    }

    World::Manager::WarpMgr& warpMgr()
    {
      return Common::Service< World::Manager::WarpMgr >::ref();
    }
  };

  /*!
   * @brief The base class for scripts that implement behaviour related to Event Objects (EObjs)
   */
  class EventObjectScript : public ScriptObject
  {
  public:
    explicit EventObjectScript( uint32_t eobjId );

    virtual void onTalk( uint32_t eventId, Sapphire::Entity::Player& player, Entity::EventObject& eobj );

    World::Manager::EventMgr& eventMgr()
    {
      return Common::Service< World::Manager::EventMgr >::ref();
    }

    World::Manager::PlayerMgr& playerMgr()
    {
      return Common::Service< World::Manager::PlayerMgr >::ref();
    }

    World::Manager::WarpMgr& warpMgr()
    {
      return Common::Service< World::Manager::WarpMgr >::ref();
    }
  };

  /*!
  * @brief The base class for any scripts that implement behaviour related to BattleNPCs
  */
  class BattleNpcScript : public ScriptObject
  {
  public:
    explicit BattleNpcScript( uint32_t npcId );
  };

  /*!
  * @brief The base class for any scripts that implement behaviour related to zones
  */
  class ZoneScript : public ScriptObject
  {
  public:
    explicit ZoneScript( uint32_t zoneId );

    virtual void onZoneInit();
  };

  /*!
  * @brief The base class for any scripts that implement behaviour related to instance content zones
  */
  class InstanceContentScript : public ScriptObject
  {
  public:
    explicit InstanceContentScript( uint32_t instanceContentId );

    virtual void onInit( Sapphire::InstanceContent& instance );

    virtual void onTalk( Sapphire::InstanceContent& instance, Sapphire::Entity::Player& player, Sapphire::Entity::EventObject& eobj, uint32_t eventId );

    virtual void onTalk( Sapphire::InstanceContent& instance, Sapphire::Entity::Player& player, uint32_t eventId, uint64_t actorId );

    virtual void onUpdate( Sapphire::InstanceContent& instance, uint64_t tickCount );

    virtual void onEnterTerritory( Sapphire::InstanceContent& instance, Sapphire::Entity::Player& player, uint32_t eventId,
                                   uint16_t param1, uint16_t param2 );

    virtual void onLeaveTerritory( InstanceContent& instance, Entity::Player& player );

    World::Manager::EventMgr& eventMgr()
    {
      return Common::Service< World::Manager::EventMgr >::ref();
    }

    World::Manager::PlayerMgr& playerMgr()
    {
      return Common::Service< World::Manager::PlayerMgr >::ref();
    }
  };

  /*!
  * @brief The base class for any scripts that implement behaviour related to instance content zones
  */
  class QuestBattleScript : public ScriptObject
  {
  public:
    explicit QuestBattleScript( uint32_t questBattleId );

    virtual void onDutyComplete( Sapphire::QuestBattle& instance, Entity::Player& player );

    virtual void onDutyCommence( QuestBattle& instance, Entity::Player& player );

    virtual void onPlayerSetup( Sapphire::QuestBattle& instance, Entity::Player& player );

    virtual void onInit( Sapphire::QuestBattle& instance );

    virtual void onUpdate( Sapphire::QuestBattle& instance, uint64_t tickCount );

    virtual void onEnterTerritory( Sapphire::QuestBattle& instance, Sapphire::Entity::Player& player, uint32_t eventId,
                                   uint16_t param1, uint16_t param2 );

    World::Manager::EventMgr& eventMgr()
    {
      return Common::Service< World::Manager::EventMgr >::ref();
    }

    World::Manager::PlayerMgr& playerMgr()
    {
      return Common::Service< World::Manager::PlayerMgr >::ref();
    }
  };

}

#endif
