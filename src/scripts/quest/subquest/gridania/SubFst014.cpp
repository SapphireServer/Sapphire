// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: SubFst014_00041
// Quest Name: Covered in Roses
// Quest ID: 65577
// Start NPC: 1000300
// End NPC: 1000300

using namespace Sapphire;

class SubFst014 : public Sapphire::ScriptAPI::QuestScript
{
  private:
    // Basic quest information 
    // Quest vars / flags used
    // BitFlag8
    // UI8AL
    // UI8BH

    /// Countable Num: 6 Seq: 1 Event: 1 Listener: 2000026
    /// Countable Num: 1 Seq: 255 Event: 1 Listener: 2000027
    // Steps in this quest ( 0 is before accepting, 
    // 1 is first, 255 means ready for turning it in
    enum Sequence : uint8_t
    {
      Seq0 = 0,
      Seq1 = 1,
      SeqFinish = 255,
    };

    // Entities found in the script data of the quest
    static constexpr auto Actor0 = 1000300;
    static constexpr auto Eobject0 = 2000026;
    static constexpr auto Eobject1 = 2000027;
    static constexpr auto Eobject2 = 2000028;
    static constexpr auto Eobject3 = 2000029;
    static constexpr auto Eobject4 = 2000030;
    static constexpr auto Eobject5 = 2000031;
    static constexpr auto EventActionSearch = 1;
    static constexpr auto Item0 = 2000084;

  public:
    SubFst014() : Sapphire::ScriptAPI::QuestScript( 65577 ){}; 
    ~SubFst014() = default; 

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
          Scene00007(quest, player);
        break;
      }

      case Eobject0:
      {
        eventMgr().eventActionStart(player, getId(), 0x01,
          [&](Entity::Player& player, uint32_t eventId, uint64_t additional)
          {
            Scene00001(quest, player);
          },
          nullptr, 0);
        break;
      }
      case Eobject1:
      {
        eventMgr().eventActionStart(player, getId(), 0x01,
          [&](Entity::Player& player, uint32_t eventId, uint64_t additional)
          {
            Scene00002(quest, player);
          },
          nullptr, 0);
        break;
      }
      case Eobject2:
      {
        eventMgr().eventActionStart(player, getId(), 0x01,
          [&](Entity::Player& player, uint32_t eventId, uint64_t additional)
          {
            Scene00003(quest, player);
          },
          nullptr, 0);
        break;
      }
      case Eobject3:
      {
        eventMgr().eventActionStart(player, getId(), 0x01,
          [&](Entity::Player& player, uint32_t eventId, uint64_t additional)
          {
            Scene00004(quest, player);
          },
          nullptr, 0);
        break;
      }
      case Eobject4:
      {
        eventMgr().eventActionStart(player, getId(), 0x01,
          [&](Entity::Player& player, uint32_t eventId, uint64_t additional)
          {
            Scene00005(quest, player);
          },
          nullptr, 0);
        break;
      }
      case Eobject5:
      {
        eventMgr().eventActionStart(player, getId(), 0x01,
          [&](Entity::Player& player, uint32_t eventId, uint64_t additional)
          {
            Scene00006(quest, player);
          },
          nullptr, 0);
        break;
      }
    }
  }


  private:

    void checkQuestCompletion(World::Quest& quest, Entity::Player& player)
    {
      auto currentCC = quest.getUI8AL();

      player.sendEventNotice(getId(), 0, 2, currentCC + 1, 6);
      quest.setUI8AL(currentCC + 1);
      quest.setUI8BH(currentCC + 1);

      if (currentCC + 1 >= 6)
      {
        quest.setSeq(SeqFinish);
      }
    }
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &SubFst014::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, HIDE_HOTBAR, bindSceneReturn( &SubFst014::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    Scene00100(quest, player);
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, HIDE_HOTBAR, bindSceneReturn( &SubFst014::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    Scene00098(quest, player);
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, HIDE_HOTBAR, bindSceneReturn( &SubFst014::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    Scene00096(quest, player);
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, HIDE_HOTBAR, bindSceneReturn( &SubFst014::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    Scene00094(quest, player);
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, HIDE_HOTBAR, bindSceneReturn( &SubFst014::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    Scene00092(quest, player);
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00006( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 6, HIDE_HOTBAR, bindSceneReturn( &SubFst014::Scene00006Return ) );
  }

  void Scene00006Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    Scene00090(quest, player);
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00007( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 7, HIDE_HOTBAR, bindSceneReturn( &SubFst014::Scene00007Return ) );
  }

  void Scene00007Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if (result.getResult(0) == 1)
      Scene00088(quest, player);
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00087( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 87, HIDE_HOTBAR, bindSceneReturn( &SubFst014::Scene00087Return ) );
  }

  void Scene00087Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    //Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00088( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 88, HIDE_HOTBAR, bindSceneReturn( &SubFst014::Scene00088Return ) );
  }

  void Scene00088Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      if( player.giveQuestRewards( getId(), 0 ) )
        player.finishQuest( getId() );
    }

  }

  //////////////////////////////////////////////////////////////////////

  void Scene00089( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 89, HIDE_HOTBAR, bindSceneReturn( &SubFst014::Scene00089Return ) );
  }

  void Scene00089Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    //Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00090( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 90, HIDE_HOTBAR, bindSceneReturn( &SubFst014::Scene00090Return ) );
  }

  void Scene00090Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    checkQuestCompletion(quest, player);
    quest.setBitFlag8(6, true);
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00091( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 91, HIDE_HOTBAR, bindSceneReturn( &SubFst014::Scene00091Return ) );
  }

  void Scene00091Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    //Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00092( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 92, HIDE_HOTBAR, bindSceneReturn( &SubFst014::Scene00092Return ) );
  }

  void Scene00092Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    checkQuestCompletion(quest, player);
    quest.setBitFlag8(5, true);
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00093( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 93, HIDE_HOTBAR, bindSceneReturn( &SubFst014::Scene00093Return ) );
  }

  void Scene00093Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    //Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00094( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 94, HIDE_HOTBAR, bindSceneReturn( &SubFst014::Scene00094Return ) );
  }

  void Scene00094Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    checkQuestCompletion(quest, player);
    quest.setBitFlag8(4, true);
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00095( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 95, HIDE_HOTBAR, bindSceneReturn( &SubFst014::Scene00095Return ) );
  }

  void Scene00095Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    //Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00096( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 96, HIDE_HOTBAR, bindSceneReturn( &SubFst014::Scene00096Return ) );
  }

  void Scene00096Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    checkQuestCompletion(quest, player);
    quest.setBitFlag8(3, true);
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00097( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 97, HIDE_HOTBAR, bindSceneReturn( &SubFst014::Scene00097Return ) );
  }

  void Scene00097Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    //Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00098( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 98, HIDE_HOTBAR, bindSceneReturn( &SubFst014::Scene00098Return ) );
  }

  void Scene00098Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    checkQuestCompletion(quest, player);
    quest.setBitFlag8(2, true);
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00099( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 99, HIDE_HOTBAR, bindSceneReturn( &SubFst014::Scene00099Return ) );
  }

  void Scene00099Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    //Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00100( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 100, HIDE_HOTBAR, bindSceneReturn( &SubFst014::Scene00100Return ) );
  }

  void Scene00100Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    checkQuestCompletion(quest, player);
    quest.setBitFlag8(1, true);
  }

};

EXPOSE_SCRIPT( SubFst014 );