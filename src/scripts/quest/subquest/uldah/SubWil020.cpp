// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: SubWil020_00393
// Quest Name: Vox Populi
// Quest ID: 65929
// Start NPC: 1001685
// End NPC: 1001945

using namespace Sapphire;

class SubWil020 : public Sapphire::ScriptAPI::QuestScript
{
  private:
    // Basic quest information 
    // Quest vars / flags used
    // BitFlag8
    // UI8AH
    // UI8AL
    // UI8BH

    /// Countable Num: 8 Seq: 1 Event: 1 Listener: 1001940
    /// Countable Num: 1 Seq: 1 Event: 1 Listener: 1001937
    /// Countable Num: 0 Seq: 255 Event: 1 Listener: 1001939
    // Steps in this quest ( 0 is before accepting, 
    // 1 is first, 255 means ready for turning it in
    enum Sequence : uint8_t
    {
      Seq0 = 0,
      Seq1 = 1,
      SeqFinish = 255,
    };

    // Entities found in the script data of the quest
    static constexpr auto Actor0 = 1001685;
    static constexpr auto Actor1 = 1001940;
    static constexpr auto Actor2 = 1001937;
    static constexpr auto Actor3 = 1001939;
    static constexpr auto Actor4 = 1001942;
    static constexpr auto Actor5 = 1001949;
    static constexpr auto Actor6 = 1003902;
    static constexpr auto Actor7 = 1001914;
    static constexpr auto Actor8 = 1003899;
    static constexpr auto Actor9 = 1001945;

  public:
    SubWil020() : Sapphire::ScriptAPI::QuestScript( 65929 ){}; 
    ~SubWil020() = default; 

  //////////////////////////////////////////////////////////////////////
  // Event Handlers
  void onTalk( World::Quest& quest, Entity::Player& player, uint64_t actorId ) override
  {
    //Some of these feel wrong
    switch( actorId )
    {
      case Actor0:
      {
        Scene00000(quest, player);
        break;
      }
      case Actor1:
      {
        if (!quest.getBitFlag8(1))
          Scene00001(quest, player);
        else
          Scene00002(quest, player);
        break;
      }
      case Actor2:
      {
        if (!quest.getBitFlag8(2))
          Scene00003(quest, player);
        else
          Scene00004(quest, player);
        break;
      }
      case Actor3:
      {
        if (!quest.getBitFlag8(3))
          Scene00005(quest, player);
        else
          Scene00006(quest, player);
        break;
      }
      case Actor4:
      {
        if (!quest.getBitFlag8(4))
          Scene00007(quest, player);
        else
          Scene00008(quest, player);
        break;
      }
      case Actor5:
      {
        if (!quest.getBitFlag8(5))
          Scene00009(quest, player);
        else
          Scene00010(quest, player);
        break;
      }
      case Actor6:
      {
        if (!quest.getBitFlag8(6))
          Scene00011(quest, player);
        else
          Scene00012(quest, player);
        break;
      }
      case Actor7:
      {
        if (!quest.getBitFlag8(7))
          Scene00013(quest, player);
        else
          Scene00014(quest, player);
        break;
      }
      case Actor8:
      {
        if (!quest.getBitFlag8(0))
          Scene00015(quest, player);
        else
          Scene00016(quest, player);
        break;
      }
      case Actor9:
      {
        Scene00017(quest, player);
        break;
      }
    }
  }


  private:

    void checkQuestProgression(World::Quest& quest, Entity::Player& player)
    {
      if (quest.getUI8AL() == 6 && quest.getUI8BH() == 2)
      {
        quest.setSeq(SeqFinish);
      }
    }
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, NONE, bindSceneReturn( &SubWil020::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, NONE, bindSceneReturn( &SubWil020::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    auto hustCount = quest.getUI8AL();
    hustCount += 1;
    quest.setUI8AL(hustCount);
    player.sendEventNotice(getId(), 0, 2, hustCount, 6);
    quest.setBitFlag8(1, true);
    checkQuestProgression(quest, player);
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, NONE, bindSceneReturn( &SubWil020::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    auto hustCount = quest.getUI8AL();
    hustCount += 1;
    quest.setUI8AL(hustCount);
    player.sendEventNotice(getId(), 0, 2, hustCount, 6);
    quest.setBitFlag8(2, true);
    checkQuestProgression(quest, player);
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, NONE, bindSceneReturn( &SubWil020::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    auto hustCount = quest.getUI8AL();
    hustCount += 1;
    quest.setUI8AL(hustCount);
    player.sendEventNotice(getId(), 0, 2, hustCount, 6);
    quest.setBitFlag8(3, true);
    checkQuestProgression(quest, player);
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, NONE, bindSceneReturn( &SubWil020::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    auto hustCount = quest.getUI8AL();
    hustCount += 1;
    quest.setUI8AL(hustCount);
    player.sendEventNotice(getId(), 0, 2, hustCount, 6);
    quest.setBitFlag8(4, true);
    checkQuestProgression(quest, player);
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, NONE, bindSceneReturn( &SubWil020::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    auto hustCount = quest.getUI8AL();
    hustCount += 1;
    quest.setUI8AL(hustCount);
    player.sendEventNotice(getId(), 0, 2, hustCount, 6);
    quest.setBitFlag8(5, true);
    checkQuestProgression(quest, player);
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00006( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 6, NONE, bindSceneReturn( &SubWil020::Scene00006Return ) );
  }

  void Scene00006Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    auto hustCount = quest.getUI8AL();
    hustCount += 1;
    quest.setUI8AL(hustCount);
    player.sendEventNotice(getId(), 0, 2, hustCount, 6);
    quest.setBitFlag8(6, true);
    checkQuestProgression(quest, player);
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00007( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 7, NONE, bindSceneReturn( &SubWil020::Scene00007Return ) );
  }

  void Scene00007Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    auto hustCount = quest.getUI8AL();
    hustCount += 1;
    quest.setUI8AL(hustCount);
    player.sendEventNotice(getId(), 0, 2, hustCount, 6);
    quest.setBitFlag8(7, true);
    checkQuestProgression(quest, player);
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00008( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 8, NONE, bindSceneReturn( &SubWil020::Scene00008Return ) );
  }

  void Scene00008Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    auto hustCount = quest.getUI8AL();
    hustCount += 1;
    quest.setUI8AL(hustCount);
    player.sendEventNotice(getId(), 0, 2, hustCount, 6);
    quest.setBitFlag8(8, true);
    checkQuestProgression(quest, player);
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00009( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 9, NONE, bindSceneReturn( &SubWil020::Scene00009Return ) );
  }

  void Scene00009Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00010( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 10, NONE, bindSceneReturn( &SubWil020::Scene00010Return ) );
  }

  void Scene00010Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00011( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 11, NONE, bindSceneReturn( &SubWil020::Scene00011Return ) );
  }

  void Scene00011Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00012( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 12, NONE, bindSceneReturn( &SubWil020::Scene00012Return ) );
  }

  void Scene00012Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00013( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 13, NONE, bindSceneReturn( &SubWil020::Scene00013Return ) );
  }

  void Scene00013Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00014( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 14, NONE, bindSceneReturn( &SubWil020::Scene00014Return ) );
  }

  void Scene00014Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00015( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 15, NONE, bindSceneReturn( &SubWil020::Scene00015Return ) );
  }

  void Scene00015Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00016( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 16, NONE, bindSceneReturn( &SubWil020::Scene00016Return ) );
  }

  void Scene00016Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00017( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 17, NONE, bindSceneReturn( &SubWil020::Scene00017Return ) );
  }

  void Scene00017Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
    }

  }

  //////////////////////////////////////////////////////////////////////

  void Scene00018( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 18, NONE, bindSceneReturn( &SubWil020::Scene00018Return ) );
  }

  void Scene00018Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00019( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 19, NONE, bindSceneReturn( &SubWil020::Scene00019Return ) );
  }

  void Scene00019Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00020( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 20, NONE, bindSceneReturn( &SubWil020::Scene00020Return ) );
  }

  void Scene00020Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00021( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 21, NONE, bindSceneReturn( &SubWil020::Scene00021Return ) );
  }

  void Scene00021Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00022( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 22, NONE, bindSceneReturn( &SubWil020::Scene00022Return ) );
  }

  void Scene00022Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00023( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 23, NONE, bindSceneReturn( &SubWil020::Scene00023Return ) );
  }

  void Scene00023Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00024( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 24, NONE, bindSceneReturn( &SubWil020::Scene00024Return ) );
  }

  void Scene00024Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00025( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 25, NONE, bindSceneReturn( &SubWil020::Scene00025Return ) );
  }

  void Scene00025Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

};

EXPOSE_SCRIPT( SubWil020 );