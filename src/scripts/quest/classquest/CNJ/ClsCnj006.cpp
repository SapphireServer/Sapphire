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

// Quest Script: ClsCnj006_00441
// Quest Name: In Nature's Embrace
// Quest ID: 65977
// Start NPC: 1000692
// End NPC: 1000692

using namespace Sapphire;

class ClsCnj006 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // BitFlag8
  // UI8AL

  /// Countable Num: 1 Seq: 1 Event: 1 Listener: 2000899
  /// Countable Num: 1 Seq: 2 Event: 5 Listener: 294
  /// Countable Num: 1 Seq: 3 Event: 1 Listener: 1002965
  /// Countable Num: 1 Seq: 4 Event: 1 Listener: 1002965
  /// Countable Num: 1 Seq: 5 Event: 1 Listener: 2000901
  /// Countable Num: 1 Seq: 6 Event: 5 Listener: 294
  /// Countable Num: 1 Seq: 7 Event: 1 Listener: 1002966
  /// Countable Num: 1 Seq: 255 Event: 1 Listener: 1002966
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
    Seq7 = 7,
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1000692;//E-Sumi-Yan
  static constexpr auto Actor1 = 1002965;//Sylphie (Seq1/Seq2)
  static constexpr auto Actor2 = 1002966;//Sylphie (Seq3/Seq4)
  static constexpr auto Actor3 = 1002967;//Sylphie (Seq5/Seq6)
  static constexpr auto Actor4 = 1002968;//Sylphie (Seq7)
  static constexpr auto Enemy0 = 3876178;
  static constexpr auto Enemy1 = 3876179;
  static constexpr auto Enemy2 = 3876180;
  static constexpr auto Eobject0 = 2000899;//Corrupted Soil (Seq1)
  static constexpr auto Eobject1 = 2000901;//Corrupted Soil (Seq3)
  static constexpr auto Eobject2 = 2000906;//Corrupted Soil (Seq5)
  static constexpr auto Eobject3 = 2001839;
  static constexpr auto EventActionSearch = 1;
  static constexpr auto LocAction0 = 995;
  static constexpr auto LocActor0 = 1003003;
  static constexpr auto LocActor1 = 1000693;
  static constexpr auto LocPosActor0 = 1170797;
  static constexpr auto LocVfx = 241;
  static constexpr auto LocWs = 135;
  static constexpr auto NqPoint001 = 19;
  static constexpr auto NqPoint002 = 20;
  static constexpr auto Questbattle0 = 17;
  static constexpr auto Seq0Actor0Lq = 90;
  static constexpr auto Territorytype0 = 235;

public:
  ClsCnj006() : Sapphire::ScriptAPI::QuestScript( 65977 ){};
  ~ClsCnj006() = default;

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
          Scene00029( quest, player );
        break;
      }
      case Actor1:
      {
        if( quest.getSeq() == Seq1 )
          Scene00008( quest, player );
        else if( quest.getSeq() == Seq2 )
          Scene00009( quest, player );
        break;
      }
      case Actor2:
      {
        if( quest.getSeq() == Seq3 )
          Scene00016( quest, player );
        else if( quest.getSeq() == Seq4 )
          Scene00017( quest, player );
        break;
      }
      case Actor3:
      {
        if( quest.getSeq() == Seq5 )
          Scene00024( quest, player );
        else if( quest.getSeq() == Seq6 )
          Scene00025( quest, player );
        break;
      }
      case Actor4:
      {
        if( quest.getSeq() == Seq7 )
        {
          //TODO: Selecting "Procede" causes the game to fade out, so if we don't send the player to an instance it soft-locks them.
          //Scene00026( quest, player );
          playerMgr().sendUrgent( player, "QuestBattle content is currently broken. The fight has been skipped for you." );
          eventMgr().sendEventNotice( player, getId(), 6, 0 );
          quest.setSeq( SeqFinish );
        }
        break;
      }
      case Eobject0:
      {
        if( quest.getSeq() == Seq1 )
          Scene00003( quest, player );
        break;
      }
      case Eobject1:
      {
        if( quest.getSeq() == Seq3 )
          Scene00011( quest, player );
        break;
      }
      case Eobject2:
      {
        if( quest.getSeq() == Seq5 )
          Scene00019( quest, player );
        break;
      }
    }
  }

  void onBNpcKill( World::Quest& quest, uint16_t nameId, uint32_t entityId, Sapphire::Entity::Player& player ) override
  {
    switch( entityId )
    {
      case Enemy0:
      {
        if( quest.getSeq() == Seq1 )
        {
          eventMgr().sendEventNotice( player, getId(), 0, 0 );
          quest.setSeq( Seq2 );
          quest.setBitFlag8( 1, false );
        }
        break;
      }
      case Enemy1:
      {
        if( quest.getSeq() == Seq3 )
        {
          eventMgr().sendEventNotice( player, getId(), 2, 0 );
          quest.setSeq( Seq4 );
          quest.setBitFlag8( 1, false );
        }
        break;
      }
      case Enemy2:
      {
        if( quest.getSeq() == Seq5 )
        {
          eventMgr().sendEventNotice( player, getId(), 4, 0 );
          quest.setSeq( Seq6 );
          quest.setBitFlag8( 1, false );
        }
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
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &ClsCnj006::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, FADE_OUT | HIDE_UI | CONDITION_CUTSCENE, bindSceneReturn( &ClsCnj006::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( Seq1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, NONE, bindSceneReturn( &ClsCnj006::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, NONE, bindSceneReturn( &ClsCnj006::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    auto& teriMgr = Common::Service< Sapphire::World::Manager::TerritoryMgr >::ref();
    auto instance = teriMgr.getTerritoryByGuId( player.getTerritoryId() );
    auto enemy = instance->createBNpcFromInstanceId( Enemy0, 413 /*TODO: Find the right value*/, Common::BNpcType::Enemy );
    enemy->hateListAdd( player.getAsPlayer(), 1 );
    quest.setBitFlag8( 1, true );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, NONE, bindSceneReturn( &ClsCnj006::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, NONE, bindSceneReturn( &ClsCnj006::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00006( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 6, NONE, bindSceneReturn( &ClsCnj006::Scene00006Return ) );
  }

  void Scene00006Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00007( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 7, NONE, bindSceneReturn( &ClsCnj006::Scene00007Return ) );
  }

  void Scene00007Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00008( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 8, NONE, bindSceneReturn( &ClsCnj006::Scene00008Return ) );
  }

  void Scene00008Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00009( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 9, NONE, bindSceneReturn( &ClsCnj006::Scene00009Return ) );
  }

  void Scene00009Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 1, 0 );
    quest.setSeq( Seq3 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00010( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 10, NONE, bindSceneReturn( &ClsCnj006::Scene00010Return ) );
  }

  void Scene00010Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00011( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 11, NONE, bindSceneReturn( &ClsCnj006::Scene00011Return ) );
  }

  void Scene00011Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    auto& teriMgr = Common::Service< Sapphire::World::Manager::TerritoryMgr >::ref();
    auto instance = teriMgr.getTerritoryByGuId( player.getTerritoryId() );
    auto enemy = instance->createBNpcFromInstanceId( Enemy1, 413 /*TODO: Find the right value*/, Common::BNpcType::Enemy );
    enemy->hateListAdd( player.getAsPlayer(), 1 );
    quest.setBitFlag8( 1, true );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00012( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 12, NONE, bindSceneReturn( &ClsCnj006::Scene00012Return ) );
  }

  void Scene00012Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00013( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 13, NONE, bindSceneReturn( &ClsCnj006::Scene00013Return ) );
  }

  void Scene00013Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00014( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 14, NONE, bindSceneReturn( &ClsCnj006::Scene00014Return ) );
  }

  void Scene00014Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00015( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 15, NONE, bindSceneReturn( &ClsCnj006::Scene00015Return ) );
  }

  void Scene00015Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00016( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 16, NONE, bindSceneReturn( &ClsCnj006::Scene00016Return ) );
  }

  void Scene00016Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00017( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 17, NONE, bindSceneReturn( &ClsCnj006::Scene00017Return ) );
  }

  void Scene00017Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 3, 0 );
    quest.setSeq( Seq5 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00018( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 18, NONE, bindSceneReturn( &ClsCnj006::Scene00018Return ) );
  }

  void Scene00018Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00019( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 19, NONE, bindSceneReturn( &ClsCnj006::Scene00019Return ) );
  }

  void Scene00019Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    auto& teriMgr = Common::Service< Sapphire::World::Manager::TerritoryMgr >::ref();
    auto instance = teriMgr.getTerritoryByGuId( player.getTerritoryId() );
    auto enemy = instance->createBNpcFromInstanceId( Enemy2, 413 /*TODO: Find the right value*/, Common::BNpcType::Enemy );
    enemy->hateListAdd( player.getAsPlayer(), 1 );

    quest.setBitFlag8( 1, true );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00020( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 20, NONE, bindSceneReturn( &ClsCnj006::Scene00020Return ) );
  }

  void Scene00020Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00021( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 21, NONE, bindSceneReturn( &ClsCnj006::Scene00021Return ) );
  }

  void Scene00021Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00022( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 22, NONE, bindSceneReturn( &ClsCnj006::Scene00022Return ) );
  }

  void Scene00022Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00023( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 23, NONE, bindSceneReturn( &ClsCnj006::Scene00023Return ) );
  }

  void Scene00023Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00024( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 24, NONE, bindSceneReturn( &ClsCnj006::Scene00024Return ) );
  }

  void Scene00024Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00025( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 25, NONE, bindSceneReturn( &ClsCnj006::Scene00025Return ) );
  }

  void Scene00025Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 5, 0 );
    quest.setSeq( Seq7 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00026( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 26, NONE, bindSceneReturn( &ClsCnj006::Scene00026Return ) );
  }

  void Scene00026Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
    {
      //TODO: QuestBattle content

      auto& teriMgr = Common::Service< Sapphire::World::Manager::TerritoryMgr >::ref();

      eventMgr().eventFinish( player, result.eventId, 0 );
      teriMgr.createAndJoinQuestBattle( player, Questbattle0 );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00027( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 27, NONE, bindSceneReturn( &ClsCnj006::Scene00027Return ) );
  }

  void Scene00027Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00028( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 28, NONE, bindSceneReturn( &ClsCnj006::Scene00028Return ) );
  }

  void Scene00028Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00029( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 29, FADE_OUT | HIDE_UI | CONDITION_CUTSCENE, bindSceneReturn( &ClsCnj006::Scene00029Return ) );
  }

  void Scene00029Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
    }
  }
};

EXPOSE_SCRIPT( ClsCnj006 );