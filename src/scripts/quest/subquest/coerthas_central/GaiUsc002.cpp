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

// Quest Script: GaiUsc002_00939
// Quest Name: By the Lights of Ishgard
// Quest ID: 66475
// Start NPC: 1006467
// End NPC: 1006467

using namespace Sapphire;

class GaiUsc002 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // BitFlag8
  // UI8AL
  // UI8BH

  /// Countable Num: 0 Seq: 1 Event: 10 Listener: 5000000
  /// Countable Num: 0 Seq: 2 Event: 1 Listener: 2002170
  /// Countable Num: 0 Seq: 255 Event: 5 Listener: 46
  // Steps in this quest ( 0 is before accepting,
  // 1 is first, 255 means ready for turning it in
  enum Sequence : uint8_t
  {
    Seq0 = 0,
    Seq1 = 1,
    Seq2 = 2,
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1006467;//Alphinaud
  static constexpr auto Actor1 = 1007631;
  static constexpr auto Enemy0 = 4297103;
  static constexpr auto Enemy1 = 4297104;
  static constexpr auto Enemy2 = 4297106;
  static constexpr auto Eobject0 = 2002170;//Snowy Mound
  static constexpr auto Eobject1 = 2002322;
  static constexpr auto Eobject2 = 2002590;//Inquisitor Corpse
  static constexpr auto Eventrange0 = 4297079;
  static constexpr auto EventActionSearch = 1;
  static constexpr auto Item0 = 2000733;

public:
  GaiUsc002() : Sapphire::ScriptAPI::QuestScript( 66475 ){};
  ~GaiUsc002() = default;

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
          Scene00010( quest, player );
        break;
      }
      case Actor1:
      {
        break;
      }
      case Eobject0:
      {
        if( quest.getSeq() == Seq1 )
          if( quest.getUI8AL() < 3 )
            Scene00003( quest, player );
          else
            eventMgr().eventActionStart(
                    player, getId(), EventActionSearch,
                    [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                      Scene00004( quest, player );
                    },
                    nullptr, 0 );
        break;
      }
      case Eobject2:
      {
        eventMgr().eventActionStart(
                player, getId(), EventActionSearch,
                [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                  Scene00005( quest, player );
                },
                nullptr, 0 );
        break;
      }
    }
  }

  void onWithinRange( World::Quest& quest, Entity::Player& player, uint32_t eventId, uint32_t param1, float x, float y, float z ) override
  {
    if( param1 == Eventrange0 )
    {
      auto instance = teriMgr().getTerritoryByGuId( player.getTerritoryId() );

      auto enemy0Spawned = instance->getActiveBNpcByLayoutIdAndTriggerOwner( Enemy0, player.getId() );
      auto enemy1Spawned = instance->getActiveBNpcByLayoutIdAndTriggerOwner( Enemy1, player.getId() );
      auto enemy2Spawned = instance->getActiveBNpcByLayoutIdAndTriggerOwner( Enemy2, player.getId() );

      if( !enemy0Spawned && !enemy1Spawned && !enemy2Spawned && quest.getUI8AL() < 3 )
      {
        auto enemy0 = instance->createBNpcFromLayoutId( Enemy0, 413 /*TODO: Find the right value*/, Common::BNpcType::Enemy, player.getId() );
        auto enemy1 = instance->createBNpcFromLayoutId( Enemy1, 413 /*TODO: Find the right value*/, Common::BNpcType::Enemy, player.getId() );
        auto enemy2 = instance->createBNpcFromLayoutId( Enemy2, 413 /*TODO: Find the right value*/, Common::BNpcType::Enemy, player.getId() );
        enemy0->hateListAddDelayed( player.getAsPlayer(), 1 );
        enemy1->hateListAddDelayed( player.getAsPlayer(), 1 );
        enemy2->hateListAddDelayed( player.getAsPlayer(), 1 );
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
        quest.setUI8AL( quest.getUI8AL() + 1 );
        break;
      }
    }
  }

private:
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &GaiUsc002::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, HIDE_HOTBAR, bindSceneReturn( &GaiUsc002::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( Seq1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, HIDE_HOTBAR, bindSceneReturn( &GaiUsc002::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, HIDE_HOTBAR, bindSceneReturn( &GaiUsc002::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, HIDE_HOTBAR, bindSceneReturn( &GaiUsc002::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8AL( 0 );
    quest.setSeq( Seq2 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, HIDE_HOTBAR, bindSceneReturn( &GaiUsc002::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8BH( 1 );
    quest.setSeq( SeqFinish );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00006( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 6, HIDE_HOTBAR, bindSceneReturn( &GaiUsc002::Scene00006Return ) );
  }

  void Scene00006Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00007( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 7, HIDE_HOTBAR, bindSceneReturn( &GaiUsc002::Scene00007Return ) );
  }

  void Scene00007Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00008( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 8, HIDE_HOTBAR, bindSceneReturn( &GaiUsc002::Scene00008Return ) );
  }

  void Scene00008Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00009( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 9, HIDE_HOTBAR, bindSceneReturn( &GaiUsc002::Scene00009Return ) );
  }

  void Scene00009Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00010( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 10, HIDE_HOTBAR, bindSceneReturn( &GaiUsc002::Scene00010Return ) );
  }

  void Scene00010Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      Scene00011( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00011( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 11, HIDE_HOTBAR, bindSceneReturn( &GaiUsc002::Scene00011Return ) );
  }

  void Scene00011Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId() );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00012( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 12, HIDE_HOTBAR, bindSceneReturn( &GaiUsc002::Scene00012Return ) );
  }

  void Scene00012Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }
};

EXPOSE_SCRIPT( GaiUsc002 );