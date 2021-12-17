// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>
#include "Manager/TerritoryMgr.h"

// Quest Script: ClsArc006_00076
// Quest Name: The One that Got Away
// Quest ID: 65612
// Start NPC: 1000200
// End NPC: 1000200

using namespace Sapphire;

class ClsArc006 : public Sapphire::ScriptAPI::QuestScript
{
  private:
    // Basic quest information 
    // Quest vars / flags used
    // BitFlag8
    // UI8AL

    /// Countable Num: 1 Seq: 1 Event: 1 Listener: 1000795
    /// Countable Num: 1 Seq: 2 Event: 1 Listener: 1000796
    /// Countable Num: 1 Seq: 255 Event: 1 Listener: 1000797
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
    static constexpr auto Actor0 = 1000200;
    static constexpr auto Actor1 = 1000795;
    static constexpr auto Actor2 = 1000796;
    static constexpr auto Actor3 = 1000797;
    static constexpr auto Actor4 = 1000798;
    static constexpr auto Actor5 = 1000799;
    static constexpr auto Actor6 = 1000800;
    static constexpr auto Actor7 = 1003066;
    static constexpr auto Actor8 = 1003067;
    static constexpr auto Actor9 = 1003068;
    static constexpr auto Eobject0 = 2001841;
    static constexpr auto Eobject1 = 2000709;
    static constexpr auto EventAction = 27;
    static constexpr auto EventActionSearch = 1;
    static constexpr auto EventMotZephyr = 366;
    static constexpr auto LocAction0 = 995;
    static constexpr auto LocActor0 = 1000199;
    static constexpr auto LocActor1 = 1000204;
    static constexpr auto LocVfx = 241;
    static constexpr auto LocWs = 113;
    static constexpr auto Questbattle0 = 2;
    static constexpr auto Questbattle1 = 3;
    static constexpr auto Seq0Actor0Lq = 98;
    static constexpr auto Territorytype0 = 231;
    static constexpr auto Territorytype1 = 236;

  public:
    ClsArc006() : Sapphire::ScriptAPI::QuestScript( 65612 ){}; 
    ~ClsArc006() = default; 

  //////////////////////////////////////////////////////////////////////
  // Event Handlers
  void onTalk( World::Quest& quest, Entity::Player& player, uint64_t actorId ) override
  {
    switch( actorId )
    {
      case Actor0:
      {
        if (!player.hasQuest(getId()))
          Scene00000(quest, player);
        else if (quest.getSeq() == SeqFinish)
          Scene00013(quest, player);

        break;
      }
      case Actor1:
      {
        if (quest.getSeq() == Seq1)
          Scene00002(quest, player);

        break;
      }
      case Actor2:
      {
        break;
      }
      case Actor3:
      {
        break;
      }
      case Actor4:
      {
        break;
      }
      case Actor5:
      {
        break;
      }
      case Actor6:
      {
        break;
      }
      case Actor7:
      {
        if (quest.getSeq() == SeqFinish)
          Scene00014(quest, player);

        break;
      }
      case Actor8:
      {
        if (quest.getSeq() == SeqFinish)
          Scene00015(quest, player);

        break;
      }
      case Actor9:
      {
        if (quest.getSeq() == SeqFinish)
          Scene00016(quest, player);

        break;
      }
      case Eobject1:
      {
        eventMgr().eventActionStart(player, getId(), 0x1B,
          [&](Entity::Player& player, uint32_t eventId, uint64_t additional)
          {
            Scene00011(quest, player);
          },
          nullptr, 0);

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
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &ClsArc006::Scene00000Return ) );
  }

  void Scene00000Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 ) // accept quest
    {
      Scene00001(quest, player);
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00001( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 1, SET_EOBJ_BASE | HIDE_HOTBAR | INVIS_EOBJ, bindSceneReturn( &ClsArc006::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq(Seq1);
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, HIDE_HOTBAR, bindSceneReturn( &ClsArc006::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if (result.getResult(0) == 1) {
      quest.setSeq(Seq2);
      auto& pTeriMgr = Common::Service< Sapphire::World::Manager::TerritoryMgr >::ref();

      eventMgr().eventFinish(player, result.eventId, 0);
      pTeriMgr.createAndJoinQuestBattle(player, Questbattle0);
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, HIDE_HOTBAR, bindSceneReturn( &ClsArc006::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, HIDE_HOTBAR, bindSceneReturn( &ClsArc006::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, HIDE_HOTBAR, bindSceneReturn( &ClsArc006::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00006( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 6, HIDE_HOTBAR, bindSceneReturn( &ClsArc006::Scene00006Return ) );
  }

  void Scene00006Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00007( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 7, HIDE_HOTBAR, bindSceneReturn( &ClsArc006::Scene00007Return ) );
  }

  void Scene00007Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00008( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 8, HIDE_HOTBAR, bindSceneReturn( &ClsArc006::Scene00008Return ) );
  }

  void Scene00008Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00009( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 9, HIDE_HOTBAR, bindSceneReturn( &ClsArc006::Scene00009Return ) );
  }

  void Scene00009Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00010( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 10, HIDE_HOTBAR, bindSceneReturn( &ClsArc006::Scene00010Return ) );
  }

  void Scene00010Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00011( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 11, HIDE_HOTBAR, bindSceneReturn( &ClsArc006::Scene00011Return ) );
  }

  void Scene00011Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if (result.getResult(0) == 1) {
      quest.setSeq(SeqFinish);
      auto& pTeriMgr = Common::Service< Sapphire::World::Manager::TerritoryMgr >::ref();

      eventMgr().eventFinish(player, result.eventId, 0);
      pTeriMgr.createAndJoinQuestBattle(player, Questbattle1);
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00012( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 12, HIDE_HOTBAR, bindSceneReturn( &ClsArc006::Scene00012Return ) );
  }

  void Scene00012Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00013( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 13, SET_EOBJ_BASE | HIDE_HOTBAR | INVIS_EOBJ, bindSceneReturn( &ClsArc006::Scene00013Return ) );
  }

  void Scene00013Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      if( player.giveQuestRewards( getId(), result.getResult(1)) )
        player.finishQuest( getId() );
    }

  }

  //////////////////////////////////////////////////////////////////////

  void Scene00014( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 14, HIDE_HOTBAR, bindSceneReturn( &ClsArc006::Scene00014Return ) );
  }

  void Scene00014Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00015( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 15, HIDE_HOTBAR, bindSceneReturn( &ClsArc006::Scene00015Return ) );
  }

  void Scene00015Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00016( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 16, HIDE_HOTBAR, bindSceneReturn( &ClsArc006::Scene00016Return ) );
  }

  void Scene00016Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

};

EXPOSE_SCRIPT( ClsArc006 );