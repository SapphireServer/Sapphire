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

// Quest Script: GaiUsc601_01001
// Quest Name: Drowning Out the Voices
// Quest ID: 66537
// Start NPC: 1006535
// End NPC: 1006535

using namespace Sapphire;

class GaiUsc601 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // BitFlag8
  // UI8AH
  // UI8AL
  // UI8BH
  // UI8BL
  // UI8CH
  // UI8CL
  // UI8DH

  /// Countable Num: 0 Seq: 1 Event: 1 Listener: 2002231
  /// Countable Num: 0 Seq: 255 Event: 8 Listener: 2002231
  // Steps in this quest ( 0 is before accepting,
  // 1 is first, 255 means ready for turning it in
  enum Sequence : uint8_t
  {
    Seq0 = 0,
    Seq1 = 1,
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1006535;//Cid
  static constexpr auto Enemy0 = 4300120;
  static constexpr auto Enemy1 = 4300124;
  static constexpr auto Enemy2 = 4300125;
  static constexpr auto Enemy3 = 4300128;
  static constexpr auto Eobject0 = 2002231;
  static constexpr auto Eobject1 = 2002233;
  static constexpr auto Eobject2 = 2002230;
  static constexpr auto Eobject3 = 2002232;
  static constexpr auto Eobject4 = 2002234;
  static constexpr auto Item0 = 2000766;

public:
  GaiUsc601() : Sapphire::ScriptAPI::QuestScript( 66537 ){};
  ~GaiUsc601() = default;

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
          Scene00012( quest, player );
        break;
      }
      case Eobject0:
      {
        if( quest.getSeq() == Seq1 )
          Scene00002( quest, player );
        break;
      }
      case Eobject1:
      {
        if( quest.getSeq() == Seq1 )
          Scene00004( quest, player );
        break;
      }
      case Eobject2:
      {
        if( quest.getSeq() == Seq1 )
          Scene00006( quest, player );
        break;
      }
      case Eobject3:
      {
        if( quest.getSeq() == Seq1 )
          Scene00008( quest, player );
        break;
      }
      case Eobject4:
      {
        if( quest.getSeq() == Seq1 )
          Scene00010( quest, player );
        break;
      }
    }
  }

  void onEventItem( World::Quest& quest, Entity::Player& player, uint64_t actorId ) override
  {
    switch( actorId )
    {
      case Eobject0:
      {
        if( quest.getSeq() == Seq1 )
          Scene00003( quest, player );
        break;
      }
      case Eobject1:
      {
        if( quest.getSeq() == Seq1 )
          Scene00005( quest, player );
        break;
      }
      case Eobject2:
      {
        if( quest.getSeq() == Seq1 )
          Scene00007( quest, player );
        break;
      }
      case Eobject3:
      {
        if( quest.getSeq() == Seq1 )
          Scene00009( quest, player );
        break;
      }
      case Eobject4:
      {
        if( quest.getSeq() == Seq1 )
          Scene00011( quest, player );
        break;
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
        quest.setUI8CH( quest.getUI8CH() + 1 );
        if( quest.getUI8CH() >= 3 )
        {
          quest.setUI8AH( quest.getUI8AH() + 1 );
          quest.setBitFlag8( 3, true );
          checkQuestCompletion( quest, player );
        }
        break;
      }
      case Enemy3:
      {
        quest.setUI8CL( 1 );
        quest.setBitFlag8( 4, true );
        quest.setUI8AH( quest.getUI8AH() + 1 );
        checkQuestCompletion( quest, player );
        break;
      }
    }
  }

private:
  void checkQuestCompletion( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().sendEventNotice( player, getId(), 0, 2, quest.getUI8AH(), 5 );
    if( quest.getUI8AH() >= 5 )
    {
      quest.setUI8AH( 0 );
      quest.setUI8AL( 0 );
      quest.setUI8BH( 1 );//KeyItem
      quest.setUI8BL( 0 );
      quest.setUI8CH( 0 );
      quest.setUI8CL( 0 );
      quest.setUI8DH( 0 );
      quest.setSeq( SeqFinish );
    }
  }
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &GaiUsc601::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, HIDE_HOTBAR, bindSceneReturn( &GaiUsc601::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( Seq1 );
    quest.setUI8DH( 1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, HIDE_HOTBAR, bindSceneReturn( &GaiUsc601::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    //Opens KeyItem Inventory
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, HIDE_HOTBAR, bindSceneReturn( &GaiUsc601::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8AL( 1 );                   //Hide Eobj
    quest.setBitFlag8( 1, true );          //Hide Eobj
    quest.setUI8AH( quest.getUI8AH() + 1 );//Increment Journal
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, HIDE_HOTBAR, bindSceneReturn( &GaiUsc601::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    //Opens KeyItem Inventory
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, HIDE_HOTBAR, bindSceneReturn( &GaiUsc601::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8BH( 1 );                   //Hide Eobj
    quest.setBitFlag8( 2, true );          //Hide Eobj
    quest.setUI8AH( quest.getUI8AH() + 1 );//Increment Journal
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00006( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 6, HIDE_HOTBAR, bindSceneReturn( &GaiUsc601::Scene00006Return ) );
  }

  void Scene00006Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    //Opens KeyItem Inventory
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00007( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 7, HIDE_HOTBAR, bindSceneReturn( &GaiUsc601::Scene00007Return ) );
  }

  void Scene00007Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    //Enemy0,1,2
    auto instance = teriMgr().getTerritoryByGuId( player.getTerritoryId() );

    auto enemy0spawned = instance->getActiveBNpcByLayoutIdAndTriggerOwner( Enemy0, player.getId() );
    auto enemy1spawned = instance->getActiveBNpcByLayoutIdAndTriggerOwner( Enemy1, player.getId() );
    auto enemy2spawned = instance->getActiveBNpcByLayoutIdAndTriggerOwner( Enemy2, player.getId() );

    if( !enemy0spawned && !enemy1spawned && !enemy2spawned && quest.getUI8CH() < 3 )
    {
      auto enemy0 = instance->createBNpcFromLayoutId( Enemy0, 1220 /*Find the right value*/, Common::BNpcType::Enemy, player.getId() );
      auto enemy1 = instance->createBNpcFromLayoutId( Enemy1, 1220 /*Find the right value*/, Common::BNpcType::Enemy, player.getId() );
      auto enemy2 = instance->createBNpcFromLayoutId( Enemy2, 1220 /*Find the right value*/, Common::BNpcType::Enemy, player.getId() );

      enemy0->hateListAddDelayed( player.getAsPlayer(), 1 );
      enemy1->hateListAddDelayed( player.getAsPlayer(), 1 );
      enemy2->hateListAddDelayed( player.getAsPlayer(), 1 );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00008( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 8, HIDE_HOTBAR, bindSceneReturn( &GaiUsc601::Scene00008Return ) );
  }

  void Scene00008Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    //Opens KeyItem Inventory
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00009( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 9, HIDE_HOTBAR, bindSceneReturn( &GaiUsc601::Scene00009Return ) );
  }

  void Scene00009Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    auto instance = teriMgr().getTerritoryByGuId( player.getTerritoryId() );

    auto enemy3spawned = instance->getActiveBNpcByLayoutIdAndTriggerOwner( Enemy3, player.getId() );

    if( !enemy3spawned && quest.getUI8CL() < 1 )
    {
      auto enemy3 = instance->createBNpcFromLayoutId( Enemy3, 1220 /*Find the right value*/, Common::BNpcType::Enemy, player.getId() );
      enemy3->hateListAddDelayed( player.getAsPlayer(), 1 );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00010( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 10, HIDE_HOTBAR, bindSceneReturn( &GaiUsc601::Scene00010Return ) );
  }

  void Scene00010Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    //Opens KeyItem Inventory
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00011( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 11, HIDE_HOTBAR, bindSceneReturn( &GaiUsc601::Scene00011Return ) );
  }

  void Scene00011Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8BL( 1 );                   //Hide Eobj
    quest.setBitFlag8( 5, true );          //Hide Eobj
    quest.setUI8AH( quest.getUI8AH() + 1 );//Increment Journal
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00012( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 12, HIDE_HOTBAR, bindSceneReturn( &GaiUsc601::Scene00012Return ) );
  }

  void Scene00012Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      Scene00013( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00013( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 13, HIDE_HOTBAR, bindSceneReturn( &GaiUsc601::Scene00013Return ) );
  }

  void Scene00013Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
    }
  }
};

EXPOSE_SCRIPT( GaiUsc601 );