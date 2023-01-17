// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include "Manager/EventMgr.h"
#include <Actor/Player.h>
#include <ScriptObject.h>
#include <Service.h>

#include "Actor/BNpc.h"
#include "Manager/TerritoryMgr.h"
#include "Territory/Territory.h"

// Quest Script: JobWhm350_01080
// Quest Name: Only You Can Prevent Forest Ire
// Quest ID: 66616
// Start NPC: 1006751
// End NPC: 1006751

using namespace Sapphire;

class JobWhm350 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // BitFlag8
  // UI8AL

  /// Countable Num: 0 Seq: 1 Event: 10 Listener: 5000000
  /// Countable Num: 0 Seq: 255 Event: 1 Listener: 2002392
  // Steps in this quest ( 0 is before accepting,
  // 1 is first, 255 means ready for turning it in
  enum Sequence : uint8_t
  {
    Seq0 = 0,
    Seq1 = 1,
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1006751;//Raya-O-Senna
  static constexpr auto Enemy0 = 4306588;
  static constexpr auto Enemy1 = 4306589;
  static constexpr auto Enemy2 = 4306590;
  static constexpr auto Eobject0 = 2002392;//Destination (Seq1)
  static constexpr auto Eobject1 = 2002393;
  static constexpr auto Eventrange0 = 4306570;
  static constexpr auto EventActionQuietUnderLong = 44;
  static constexpr auto EventActionSearch = 1;
  static constexpr auto LocAction0Wsget = 995;
  static constexpr auto LocLogMes = 3652;
  static constexpr auto LocVfx1 = 241;
  static constexpr auto LocVfx2 = 413;
  static constexpr auto LocWs = 137;
  static constexpr auto Logmessage0 = 3653;

public:
  JobWhm350() : Sapphire::ScriptAPI::QuestScript( 66616 ){};
  ~JobWhm350() = default;

  //////////////////////////////////////////////////////////////////////
  // Event Handlers
  void onTalk( World::Quest& quest, Entity::Player& player, uint64_t actorId ) override
  {
    switch( actorId )
    {
      case Actor0:
      {
        if( quest.getSeq() == Seq0 )
          Scene00000( quest, player );
        else if( quest.getSeq() == SeqFinish )
          Scene00007( quest, player );
        break;
      }
      case Eobject0:
      {
        if( quest.getUI8AL() >= 3 )
        {
          eventMgr().eventActionStart(
                  player, getId(), EventActionQuietUnderLong,
                  [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                    Scene00004( quest, player );
                  },
                  nullptr, 0 );
        }
        else
        {
          //"The enemy is still about!"?? Seem to not be claiming BNpcs properly?
          Scene00003( quest, player );
        }
      }
    }
  }

  void onBNpcKill( World::Quest& quest, Entity::BNpc& bnpc, Entity::Player& player ) override
  {
    switch( bnpc.getLayoutId() )
    {
      case Enemy0:
      case Enemy1:
      case Enemy2:
      {
        if( bnpc.getTriggerOwnerId() == player.getId() )
          quest.setUI8AL( quest.getUI8AL() + 1 );
        break;
      }
    }
  }

  void onWithinRange( World::Quest& quest, Entity::Player& player, uint32_t eventId, uint32_t param1, float x, float y, float z ) override
  {
    switch( param1 )
    {
      case Eventrange0:
      {
        if( quest.getUI8AL() < 3 )
          Scene00002( quest, player );
      }
    }
  }

  void onPlayerDeath( World::Quest& quest, Sapphire::Entity::Player& player ) override
  {
    auto instance = teriMgr().getTerritoryByGuId( player.getTerritoryId() );

    auto enem0 = instance->getActiveBNpcByLayoutIdAndTriggerOwner( Enemy0, player.getId() );
    auto enem1 = instance->getActiveBNpcByLayoutIdAndTriggerOwner( Enemy1, player.getId() );
    auto enem2 = instance->getActiveBNpcByLayoutIdAndTriggerOwner( Enemy2, player.getId() );

    if( enem0 != nullptr ) instance->removeActor( enem0 );
    if( enem1 != nullptr ) instance->removeActor( enem1 );
    if( enem2 != nullptr ) instance->removeActor( enem2 );

    quest.setUI8AL( 0 );
  }

private:
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, NONE, bindSceneReturn( &JobWhm350::Scene00000Return ) );
  }

  void Scene00000Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )// accept quest
    {
      Scene00001( quest, player );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00001( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 1, NONE, bindSceneReturn( &JobWhm350::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( Seq1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, NONE, bindSceneReturn( &JobWhm350::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    auto instance = teriMgr().getTerritoryByGuId( player.getTerritoryId() );

    bool enemy0Spawned = instance->getActiveBNpcByLayoutIdAndTriggerOwner( Enemy0, player.getId() ) != nullptr;
    bool enemy1Spawned = instance->getActiveBNpcByLayoutIdAndTriggerOwner( Enemy1, player.getId() ) != nullptr;
    bool enemy2Spawned = instance->getActiveBNpcByLayoutIdAndTriggerOwner( Enemy2, player.getId() ) != nullptr;

    if( enemy0Spawned || enemy1Spawned || enemy2Spawned || quest.getUI8AL() >= 3) return;

    if( !enemy0Spawned )
    {
      auto enemy0 = instance->createBNpcFromLayoutId( Enemy0, 1220 /*Find the right value*/, Common::BNpcType::Enemy, player.getId() );
      enemy0->hateListAddDelayed( player.getAsPlayer(), 1 );
    }
    if( !enemy1Spawned )
    {
      auto enemy1 = instance->createBNpcFromLayoutId( Enemy1, 1220 /*Find the right value*/, Common::BNpcType::Enemy, player.getId() );
      enemy1->hateListAddDelayed( player.getAsPlayer(), 1 );
    }
    if( !enemy2Spawned )
    {
      auto enemy2 = instance->createBNpcFromLayoutId( Enemy2, 1220 /*Find the right value*/, Common::BNpcType::Enemy, player.getId() );
      enemy2->hateListAddDelayed( player.getAsPlayer(), 1 );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, HIDE_HOTBAR, bindSceneReturn( &JobWhm350::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, HIDE_HOTBAR, bindSceneReturn( &JobWhm350::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 0, 0 );
    playerMgr().sendLogMessage( player, Logmessage0 );
    quest.setSeq( SeqFinish );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, NONE, bindSceneReturn( &JobWhm350::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00006( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 6, NONE, bindSceneReturn( &JobWhm350::Scene00006Return ) );
  }

  void Scene00006Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00007( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 7, NONE, bindSceneReturn( &JobWhm350::Scene00007Return ) );
  }

  void Scene00007Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      Scene00008( quest, player );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00008( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 8, FADE_OUT | HIDE_UI | CONDITION_CUTSCENE, bindSceneReturn( &JobWhm350::Scene00008Return ) );
  }

  void Scene00008Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    //TODO: Unlock Regen
    player.finishQuest( getId() );
  }
};

EXPOSE_SCRIPT( JobWhm350 );