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

// Quest Script: ClsCnj004_00093
// Quest Name: Sylphie's Trials
// Quest ID: 65629
// Start NPC: 1000692
// End NPC: 1000692

using namespace Sapphire;

class ClsCnj004 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // BitFlag8
  // UI8AL
  // UI8BH

  /// Countable Num: 1 Seq: 1 Event: 1 Listener: 2000891
  /// Countable Num: 1 Seq: 2 Event: 5 Listener: 294
  /// Countable Num: 1 Seq: 3 Event: 1 Listener: 1002961
  /// Countable Num: 1 Seq: 4 Event: 1 Listener: 1002961
  /// Countable Num: 1 Seq: 5 Event: 1 Listener: 2000893
  /// Countable Num: 1 Seq: 6 Event: 5 Listener: 299
  /// Countable Num: 1 Seq: 255 Event: 1 Listener: 1002962
  // Steps in this quest ( 0 is before accepting,
  // 1 is first, 255 means ready for turning it in
  enum Sequence : uint8_t
  {
    Seq0 = 0,
    Seq1 = 1,
    Seq2 = 2,
    Seq3 = 3,
    Seq4 = 4,
    Seq5 = 5,
    Seq6 = 6,
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1000692;//E-Sumi-Yan
  static constexpr auto Actor1 = 1002961;//Sylphie (Seq1/Seq2)
  static constexpr auto Actor2 = 1002962;//Sylphie (Seq3/Seq4)
  static constexpr auto Actor3 = 1002963;//Sylphie (Seq5/Seq6)
  static constexpr auto Enemy0 = 3878392;
  static constexpr auto Enemy1 = 3796339;
  static constexpr auto Enemy2 = 3876177;
  static constexpr auto Eobject0 = 2000891;//Corrupted Soil
  static constexpr auto Eobject1 = 2000893;//Corrupted Air
  static constexpr auto Eobject2 = 2000895;//Corrupted Water
  static constexpr auto EventActionSearch = 1;
  static constexpr auto LocActor0 = 1003003;
  static constexpr auto LocActor1 = 1000693;
  static constexpr auto LocPosActor0 = 1170797;
  static constexpr auto Seq0Actor0 = 0;
  static constexpr auto Seq1Actor1 = 2;
  static constexpr auto Seq1Eobject0 = 1;
  static constexpr auto Seq1Eobject0Eventactionno = 99;
  static constexpr auto Seq1Eobject0Eventactionok = 100;
  static constexpr auto Seq2Actor1 = 3;
  static constexpr auto Seq3Actor2 = 5;
  static constexpr auto Seq3Eobject1 = 4;
  static constexpr auto Seq3Eobject1Eventactionno = 97;
  static constexpr auto Seq3Eobject1Eventactionok = 98;
  static constexpr auto Seq4Actor2 = 6;
  static constexpr auto Seq5Actor3 = 8;
  static constexpr auto Seq5Eobject2 = 7;
  static constexpr auto Seq5Eobject2Eventactionno = 95;
  static constexpr auto Seq5Eobject2Eventactionok = 96;
  static constexpr auto Seq6Actor3 = 9;
  static constexpr auto Seq7Actor0 = 10;

public:
  ClsCnj004() : Sapphire::ScriptAPI::QuestScript( 65629 ){};
  ~ClsCnj004() = default;

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
        if( quest.getSeq() == Seq1 )
          Scene00002( quest, player );
        else if( quest.getSeq() == Seq2 )
          Scene00003( quest, player );
        break;
      }
      case Actor2:
      {
        if( quest.getSeq() == Seq3 )
          Scene00005( quest, player );
        else if( quest.getSeq() == Seq4 )
          Scene00006( quest, player );
        break;
      }
      case Actor3:
      {
        if( quest.getSeq() == Seq5 )
          Scene00008( quest, player );
        else if( quest.getSeq() == Seq6 )
          Scene00009( quest, player );
        break;
      }
      case Eobject0:
      {
        if( quest.getSeq() == Seq1 )
          Scene00096( quest, player );
        break;
      }
      case Eobject1:
      {
        if( quest.getSeq() == Seq3 )
          Scene00098( quest, player );
        break;
      }
      case Eobject2:
      {
        if( quest.getSeq() == Seq5 )
          Scene00100( quest, player );
        break;
      }
    }
  }

  void onBNpcKill( World::Quest& quest, uint16_t nameId, uint32_t entityId, Sapphire::Entity::Player& player ) override
  {
    if( quest.getSeq() == Seq1 && entityId == Enemy0 )
    {
      eventMgr().sendEventNotice( player, getId(), 0, 0 );
      quest.setSeq( Seq2 );
    }
    else if( quest.getSeq() == Seq3 && entityId == Enemy1 )
    {
      eventMgr().sendEventNotice( player, getId(), 2, 0 );
      quest.setSeq( Seq4 );
    }
    else if( quest.getSeq() == Seq5 && entityId == Enemy2 )
    {
      eventMgr().sendEventNotice( player, getId(), 4, 0 );
      quest.setSeq( Seq6 );
    }
  }

private:
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, NONE, bindSceneReturn( &ClsCnj004::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, NONE, bindSceneReturn( &ClsCnj004::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( Seq1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, HIDE_HOTBAR, bindSceneReturn( &ClsCnj004::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, HIDE_HOTBAR, bindSceneReturn( &ClsCnj004::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 1, 0 );
    quest.setSeq( Seq3 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, NONE, bindSceneReturn( &ClsCnj004::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, HIDE_HOTBAR, bindSceneReturn( &ClsCnj004::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00006( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 6, HIDE_HOTBAR, bindSceneReturn( &ClsCnj004::Scene00006Return ) );
  }

  void Scene00006Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 3, 0 );
    quest.setSeq( Seq5 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00007( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 7, NONE, bindSceneReturn( &ClsCnj004::Scene00007Return ) );
  }

  void Scene00007Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00008( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 8, HIDE_HOTBAR, bindSceneReturn( &ClsCnj004::Scene00008Return ) );
  }

  void Scene00008Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00009( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 9, HIDE_HOTBAR, bindSceneReturn( &ClsCnj004::Scene00009Return ) );
  }

  void Scene00009Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 5, 0 );
    quest.setSeq( SeqFinish );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00010( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 10, FADE_OUT | HIDE_UI | CONDITION_CUTSCENE, bindSceneReturn( &ClsCnj004::Scene00010Return ) );
  }

  void Scene00010Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00095( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 95, NONE, bindSceneReturn( &ClsCnj004::Scene00095Return ) );
  }

  void Scene00095Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00096( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 96, NONE, bindSceneReturn( &ClsCnj004::Scene00096Return ) );
  }

  void Scene00096Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    auto& teriMgr = Common::Service< Sapphire::World::Manager::TerritoryMgr >::ref();
    auto instance = teriMgr.getTerritoryByGuId( player.getTerritoryId() );
    auto enemy = instance->createBNpcFromInstanceId( Enemy0, 413 /*TODO: Find the right value*/, Common::BNpcType::Enemy );
    enemy->hateListAdd( player.getAsPlayer(), 1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00097( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 97, NONE, bindSceneReturn( &ClsCnj004::Scene00097Return ) );
  }

  void Scene00097Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00098( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 98, NONE, bindSceneReturn( &ClsCnj004::Scene00098Return ) );
  }

  void Scene00098Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    auto& teriMgr = Common::Service< Sapphire::World::Manager::TerritoryMgr >::ref();
    auto instance = teriMgr.getTerritoryByGuId( player.getTerritoryId() );
    auto enemy = instance->createBNpcFromInstanceId( Enemy1, 413 /*TODO: Find the right value*/, Common::BNpcType::Enemy );
    enemy->hateListAdd( player.getAsPlayer(), 1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00099( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 99, NONE, bindSceneReturn( &ClsCnj004::Scene00099Return ) );
  }

  void Scene00099Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00100( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 100, NONE, bindSceneReturn( &ClsCnj004::Scene00100Return ) );
  }

  void Scene00100Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    auto& teriMgr = Common::Service< Sapphire::World::Manager::TerritoryMgr >::ref();
    auto instance = teriMgr.getTerritoryByGuId( player.getTerritoryId() );
    auto enemy = instance->createBNpcFromInstanceId( Enemy2, 413 /*TODO: Find the right value*/, Common::BNpcType::Enemy );
    enemy->hateListAdd( player.getAsPlayer(), 1 );
  }
};

EXPOSE_SCRIPT( ClsCnj004 );