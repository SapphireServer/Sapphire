// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: SubSea001_00111
// Quest Name: Making a Name
// Quest ID: 65647
// Start NPC: 1002698
// End NPC: 1003604

using namespace Sapphire;

class SubSea001 : public Sapphire::ScriptAPI::QuestScript
{
  private:
    // Basic quest information 
    // Quest vars / flags used
    // BitFlag8
    // UI8AL
    // UI8BH

    /// Countable Num: 1 Seq: 1 Event: 1 Listener: 1000969
    /// Countable Num: 0 Seq: 2 Event: 1 Listener: 2001563
    /// Countable Num: 0 Seq: 255 Event: 1 Listener: 2001564
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
    static constexpr auto Actor0 = 1002698;
    static constexpr auto Actor1 = 1000969;
    static constexpr auto Actor2 = 1003604;
    static constexpr auto Eobject0 = 2001563;
    static constexpr auto Eobject1 = 2001564;
    static constexpr auto Eobject2 = 2001565;
    static constexpr auto Eobject3 = 2001566;
    static constexpr auto Eobject4 = 2001567;
    static constexpr auto Eobject5 = 2001568;
    static constexpr auto EventActionProcess = 14;
    static constexpr auto Item0 = 2000447;
    static constexpr auto Poprange0 = 4161445;
    static constexpr auto Quest0 = 65644;
    static constexpr auto Quest1 = 65645;
    static constexpr auto Territorytype0 = 129;

  public:
    SubSea001() : Sapphire::ScriptAPI::QuestScript( 65647 ){}; 
    ~SubSea001() = default; 

  //////////////////////////////////////////////////////////////////////
  // Event Handlers
  void onTalk( World::Quest& quest, Entity::Player& player, uint64_t actorId ) override
  {
    switch( actorId )
    {
      case Actor0:
      {
        Scene00000(quest, player);
        break;
      }
      case Actor1:
      {
        Scene00002(quest, player);
        break;
      }
      case Actor2:
      {
        Scene00016(quest, player);
        break;
      }
      case Eobject0:
      {
        eventMgr().eventActionStart(player, getId(), 0x0E,
          [&](Entity::Player& player, uint32_t eventId, uint64_t additional)
          {
            Scene00003(quest, player);
          },
          nullptr, 0);

        break;
      }
      case Eobject1:
      {
        eventMgr().eventActionStart(player, getId(), 0x0E,
          [&](Entity::Player& player, uint32_t eventId, uint64_t additional)
          {
            Scene00005(quest, player);
          },
          nullptr, 0);

        break;
      }
      case Eobject2:
      {
        eventMgr().eventActionStart(player, getId(), 0x0E,
          [&](Entity::Player& player, uint32_t eventId, uint64_t additional)
          {
            Scene00007(quest, player);
          },
          nullptr, 0);

        break;
      }
      case Eobject3:
      {
        eventMgr().eventActionStart(player, getId(), 0x0E,
          [&](Entity::Player& player, uint32_t eventId, uint64_t additional)
          {
            Scene00009(quest, player);
          },
          nullptr, 0);

        break;
      }
      case Eobject4:
      {
        eventMgr().eventActionStart(player, getId(), 0x0E,
          [&](Entity::Player& player, uint32_t eventId, uint64_t additional)
          {
            Scene00011(quest, player);
          },
          nullptr, 0);

        break;
      }
      case Eobject5:
      {
        eventMgr().eventActionStart(player, getId(), 0x0E,
          [&](Entity::Player& player, uint32_t eventId, uint64_t additional)
          {
            Scene00013(quest, player);
          },
          nullptr, 0);

        break;
      }
    }
  }


  private:


    void checkQuestCompletion(World::Quest& quest, Entity::Player& player)
    {
      auto currentCC = quest.getUI8BH();

      player.sendEventNotice(getId(), 1, 3, currentCC + 1, 6);

      if (currentCC + 1 >= 6)
      {
        quest.setSeq(SeqFinish);
        quest.setUI8BH(currentCC + 1);
        quest.setUI8AL(currentCC + 1);
      }
      else
      {
        quest.setUI8BH(currentCC + 1);
        quest.setUI8AL(currentCC + 1);
      }
    }
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &SubSea001::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, HIDE_HOTBAR, bindSceneReturn( &SubSea001::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, HIDE_HOTBAR, bindSceneReturn( &SubSea001::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if (player.hasQuest(Quest0) || player.hasQuest(Quest1))
    {
      if (result.getResult(0) == 1)
      {
        quest.setSeq(Seq2);
        player.changePosition(10, 21, 13, -2);
        player.forceZoneing(Territorytype0); //Teleport to real Limsa
      }
    }
    else
    {
      return;
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, HIDE_HOTBAR, bindSceneReturn( &SubSea001::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    Scene00004(quest, player);
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, HIDE_HOTBAR, bindSceneReturn( &SubSea001::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    checkQuestCompletion(quest, player);
    quest.setBitFlag8(1, true);
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, HIDE_HOTBAR, bindSceneReturn( &SubSea001::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    Scene00006(quest, player);
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00006( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 6, HIDE_HOTBAR, bindSceneReturn( &SubSea001::Scene00006Return ) );
  }

  void Scene00006Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    checkQuestCompletion(quest, player);
    quest.setBitFlag8(2, true);
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00007( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 7, HIDE_HOTBAR, bindSceneReturn( &SubSea001::Scene00007Return ) );
  }

  void Scene00007Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    Scene00008(quest, player);
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00008( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 8, HIDE_HOTBAR, bindSceneReturn( &SubSea001::Scene00008Return ) );
  }

  void Scene00008Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    checkQuestCompletion(quest, player);
    quest.setBitFlag8(3, true);
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00009( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 9, HIDE_HOTBAR, bindSceneReturn( &SubSea001::Scene00009Return ) );
  }

  void Scene00009Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    Scene00010(quest, player);
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00010( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 10, HIDE_HOTBAR, bindSceneReturn( &SubSea001::Scene00010Return ) );
  }

  void Scene00010Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    checkQuestCompletion(quest, player);
    quest.setBitFlag8(4, true);
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00011( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 11, HIDE_HOTBAR, bindSceneReturn( &SubSea001::Scene00011Return ) );
  }

  void Scene00011Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    Scene00012(quest, player);
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00012( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 12, HIDE_HOTBAR, bindSceneReturn( &SubSea001::Scene00012Return ) );
  }

  void Scene00012Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    checkQuestCompletion(quest, player);
    quest.setBitFlag8(5, true);
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00013( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 13, HIDE_HOTBAR, bindSceneReturn( &SubSea001::Scene00013Return ) );
  }

  void Scene00013Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    Scene00014(quest, player);
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00014( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 14, HIDE_HOTBAR, bindSceneReturn( &SubSea001::Scene00014Return ) );
  }

  void Scene00014Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    checkQuestCompletion(quest, player);
    quest.setBitFlag8(6, true);
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00015( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 15, HIDE_HOTBAR, bindSceneReturn( &SubSea001::Scene00015Return ) );
  }

  void Scene00015Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    //What do I replace this with?
    //player.playScene(player, getId(), 15, 0, 0, 0);
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00016( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 16, HIDE_HOTBAR, bindSceneReturn( &SubSea001::Scene00016Return ) );
  }

  void Scene00016Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    Scene00017(quest, player);
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00017( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 17, HIDE_HOTBAR, bindSceneReturn( &SubSea001::Scene00017Return ) );
  }

  void Scene00017Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      if( player.giveQuestRewards( getId(), 0 ) )
        player.finishQuest( getId() );
    }

  }

};

EXPOSE_SCRIPT( SubSea001 );