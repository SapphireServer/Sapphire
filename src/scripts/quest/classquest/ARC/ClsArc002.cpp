// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: ClsArc002_00067
// Quest Name: School of Hard Nocks
// Quest ID: 65603
// Start NPC: 1000200
// End NPC: 1000200

using namespace Sapphire;

class ClsArc002 : public Sapphire::ScriptAPI::QuestScript
{
  private:
    // Basic quest information 
    // Quest vars / flags used
    // BitFlag8
    // UI8AL
    // UI8BH

    /// Countable Num: 1 Seq: 1 Event: 1 Listener: 1000199
    /// Countable Num: 6 Seq: 2 Event: 1 Listener: 2000936
    /// Countable Num: 1 Seq: 3 Event: 18 Listener: 2000936
    /// Countable Num: 8 Seq: 4 Event: 1 Listener: 2000937
    /// Countable Num: 8 Seq: 4 Event: 18 Listener: 2000937
    /// Countable Num: 1 Seq: 5 Event: 1 Listener: 2000938
    /// Countable Num: 1 Seq: 255 Event: 18 Listener: 2000938
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
      SeqFinish = 255,
    };

    // Entities found in the script data of the quest
    static constexpr auto Action0 = 97;
    static constexpr auto Actor0 = 1000200;
    static constexpr auto Actor1 = 1000199;
    static constexpr auto Actor2 = 1000204;
    static constexpr auto Enemy0 = 39;
    static constexpr auto Enemy1 = 12;
    static constexpr auto Eobject0 = 2000936;
    static constexpr auto Eobject1 = 2000937;
    static constexpr auto Eobject2 = 2000938;
    static constexpr auto Eobject3 = 2000939;
    static constexpr auto Eobject4 = 2000940;
    static constexpr auto Eobject5 = 2001171;
    static constexpr auto Eobject6 = 2001173;
    static constexpr auto Eobject7 = 2001174;
    static constexpr auto UnlockCheckClassStart = 6;
    static constexpr auto UnlockImageClassCange = 22;
    static constexpr auto UnlockImageGearSet = 29;

  public:
    ClsArc002() : Sapphire::ScriptAPI::QuestScript( 65603 ){}; 
    ~ClsArc002() = default; 

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
          Scene00030(quest, player);

        break;
      }
      case Actor1:
      {
        if (quest.getSeq() == Seq1)
          Scene00001(quest, player);
        else if (quest.getSeq() == Seq3)
          Scene00026(quest, player);
        else if (quest.getSeq() == Seq5)
          Scene00029(quest, player);

        break;
      }
      case Actor2:
      {
        break;
      }
    }
  }

  void onBNpcKill(World::Quest& quest, uint16_t nameId, uint32_t entityId, Sapphire::Entity::Player& player) override
  {
    if (entityId != Enemy0 && entityId != Enemy1)
      return;

    auto currentKC39 = quest.getUI8AL() + 1;
    auto currentKC12 = quest.getUI8BH() + 1;

    switch( entityId )
    {
      case Enemy0: {
        if (currentKC39 >= 8)
        {
          quest.setUI8AL(currentKC39);
          checkQuestCompletion(quest, player, 2);
          eventMgr().sendEventNotice(player, getId(), 3, 2, currentKC39, 8);
        }
        else if (currentKC39 < 8)
        {
          quest.setUI8AL(currentKC39);
          eventMgr().sendEventNotice(player, getId(), 3, 2, currentKC39, 8);
        }

        break;
      }
      case Enemy1: {
        if (currentKC12 >= 8)
        {
          quest.setUI8BH(currentKC12);
          checkQuestCompletion(quest, player, 2);
          eventMgr().sendEventNotice(player, getId(), 4, 2, currentKC12, 8);
        }
        else if (currentKC12 < 8)
        {
          quest.setUI8BH(currentKC12);
          eventMgr().sendEventNotice(player, getId(), 4, 2, currentKC12, 8);
        }

        break;
      }
    }
  }

  void onEObjHit(World::Quest& quest, Sapphire::Entity::Player& player, uint64_t actorId, uint32_t actionId) override
  {
    switch( actorId )
    {
      case Eobject0: {
        eventMgr().eventStart(player, actorId, getId(), Event::EventHandler::Nest, 0, 0);
        Scene00002(quest, player);
        break;
      }
      case Eobject1: {
        eventMgr().eventStart(player, actorId, getId(), Event::EventHandler::Nest, 0, 0);
        Scene00003(quest, player);
        break;
      }
      case Eobject2: {
        eventMgr().eventStart(player, actorId, getId(), Event::EventHandler::Nest, 0, 0);
        Scene00004(quest, player);
        break;
      }
      case Eobject3: {
        eventMgr().eventStart(player, actorId, getId(), Event::EventHandler::Nest, 0, 0);
        Scene00005(quest, player);
        break;
      }
      case Eobject4: {
        eventMgr().eventStart(player, actorId, getId(), Event::EventHandler::Nest, 0, 0);
        Scene00006(quest, player);
        break;
      }
      case Eobject5: {
        eventMgr().eventStart(player, actorId, getId(), Event::EventHandler::Nest, 0, 0);
        Scene00007(quest, player);
        break;
      }
      case Eobject6: {
        eventMgr().eventStart(player, actorId, getId(), Event::EventHandler::Nest, 0, 0);
        Scene00008(quest, player);
        break;
      }
      case Eobject7: {
        eventMgr().eventStart(player, actorId, getId(), Event::EventHandler::Nest, 0, 0);
        Scene00009(quest, player);
        break;
      }
    }
  }
  private:


    void checkQuestCompletion(World::Quest& quest, Entity::Player& player, uint32_t varIdx)
    {
      if (varIdx == 1)
      {
        auto currentCC = quest.getUI8AL();

        eventMgr().sendEventNotice(player, getId(), 1, 2, currentCC + 1, 6);

        if (currentCC + 1 >= 6)
        {
          quest.setSeq( Seq3);
          quest.setUI8AL(0);
          quest.setUI8BH(0);
        }
        else
        {
          quest.setUI8AL(currentCC + 1);
        }
      }
      else if (varIdx == 2)
      {
        auto QUEST_ONKILL_39 = quest.getUI8AL();
        auto QUEST_ONKILL_12 = quest.getUI8BH();

        if (QUEST_ONKILL_39 == 8 && QUEST_ONKILL_12 == 8)
        {
          quest.setUI8AL(0);
          quest.setUI8BH(0);
          quest.setSeq(Seq5);
        }
      }
    }
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &ClsArc002::Scene00000Return ) );
  }

  void Scene00000Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 ) // accept quest
    {
      quest.setSeq(Seq1);
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00001( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 1, HIDE_HOTBAR, bindSceneReturn( &ClsArc002::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq(Seq2);
    eventMgr().sendEventNotice(player, getId(), 0, 2, 0, 0);
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, HIDE_HOTBAR, bindSceneReturn( &ClsArc002::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    checkQuestCompletion(quest, player, 1);
    quest.setBitFlag8(1, true);
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, HIDE_HOTBAR, bindSceneReturn( &ClsArc002::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    checkQuestCompletion(quest, player, 1);
    quest.setBitFlag8(2, true);
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, HIDE_HOTBAR, bindSceneReturn( &ClsArc002::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    checkQuestCompletion(quest, player, 1);
    quest.setBitFlag8(3, true);
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, HIDE_HOTBAR, bindSceneReturn( &ClsArc002::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    checkQuestCompletion(quest, player, 1);
    quest.setBitFlag8(4, true);
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00006( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 6, HIDE_HOTBAR, bindSceneReturn( &ClsArc002::Scene00006Return ) );
  }

  void Scene00006Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    checkQuestCompletion(quest, player, 1);
    quest.setBitFlag8(5, true);
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00007( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 7, HIDE_HOTBAR, bindSceneReturn( &ClsArc002::Scene00007Return ) );
  }

  void Scene00007Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    checkQuestCompletion(quest, player, 1);
    quest.setBitFlag8(6, true);
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00008( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 8, HIDE_HOTBAR, bindSceneReturn( &ClsArc002::Scene00008Return ) );
  }

  void Scene00008Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    checkQuestCompletion(quest, player, 1);
    quest.setBitFlag8(7, true);
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00009( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 9, HIDE_HOTBAR, bindSceneReturn( &ClsArc002::Scene00009Return ) );
  }

  void Scene00009Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    checkQuestCompletion(quest, player, 1);
    quest.setBitFlag8(8, true);
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00010( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 10, HIDE_HOTBAR, bindSceneReturn( &ClsArc002::Scene00010Return ) );
  }

  void Scene00010Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    //Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00011( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 11, HIDE_HOTBAR, bindSceneReturn( &ClsArc002::Scene00011Return ) );
  }

  void Scene00011Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    //Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00012( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 12, HIDE_HOTBAR, bindSceneReturn( &ClsArc002::Scene00012Return ) );
  }

  void Scene00012Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    //Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00013( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 13, HIDE_HOTBAR, bindSceneReturn( &ClsArc002::Scene00013Return ) );
  }

  void Scene00013Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    //Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00014( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 14, HIDE_HOTBAR, bindSceneReturn( &ClsArc002::Scene00014Return ) );
  }

  void Scene00014Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    //Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00015( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 15, HIDE_HOTBAR, bindSceneReturn( &ClsArc002::Scene00015Return ) );
  }

  void Scene00015Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    //Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00016( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 16, HIDE_HOTBAR, bindSceneReturn( &ClsArc002::Scene00016Return ) );
  }

  void Scene00016Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    //Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00017( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 17, HIDE_HOTBAR, bindSceneReturn( &ClsArc002::Scene00017Return ) );
  }

  void Scene00017Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    //Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00018( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 18, HIDE_HOTBAR, bindSceneReturn( &ClsArc002::Scene00018Return ) );
  }

  void Scene00018Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    //Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00019( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 19, HIDE_HOTBAR, bindSceneReturn( &ClsArc002::Scene00019Return ) );
  }

  void Scene00019Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    //Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00020( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 20, HIDE_HOTBAR, bindSceneReturn( &ClsArc002::Scene00020Return ) );
  }

  void Scene00020Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    //Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00021( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 21, HIDE_HOTBAR, bindSceneReturn( &ClsArc002::Scene00021Return ) );
  }

  void Scene00021Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    //Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00022( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 22, HIDE_HOTBAR, bindSceneReturn( &ClsArc002::Scene00022Return ) );
  }

  void Scene00022Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    //Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00023( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 23, HIDE_HOTBAR, bindSceneReturn( &ClsArc002::Scene00023Return ) );
  }

  void Scene00023Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    //Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00024( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 24, HIDE_HOTBAR, bindSceneReturn( &ClsArc002::Scene00024Return ) );
  }

  void Scene00024Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    //Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00025( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 25, HIDE_HOTBAR, bindSceneReturn( &ClsArc002::Scene00025Return ) );
  }

  void Scene00025Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    //Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00026( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 26, HIDE_HOTBAR, bindSceneReturn( &ClsArc002::Scene00026Return ) );
  }

  void Scene00026Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    //Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00027( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 27, HIDE_HOTBAR, bindSceneReturn( &ClsArc002::Scene00027Return ) );
  }

  void Scene00027Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    //Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00028( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 28, HIDE_HOTBAR, bindSceneReturn( &ClsArc002::Scene00028Return ) );
  }

  void Scene00028Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    //Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00029( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 29, HIDE_HOTBAR, bindSceneReturn( &ClsArc002::Scene00029Return ) );
  }

  void Scene00029Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice(player, getId(), 5, 2, 0, 0);
    quest.setSeq(SeqFinish);
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00030( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 30, SET_EOBJ_BASE | HIDE_HOTBAR | INVIS_EOBJ, bindSceneReturn( &ClsArc002::Scene00030Return ) );
  }

  void Scene00030Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if (result.getResult(0) == 1) {
      //if (player.giveQuestRewards(getId(), result.getResult(1)))
        player.finishQuest( getId(), result.getResult( 1 ) );
    }
  }

};

EXPOSE_SCRIPT( ClsArc002 );