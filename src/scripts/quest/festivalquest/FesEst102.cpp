// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: FesEst102_00557
// Quest Name: Poaching the Poachers
// Quest ID: 66093
// Start NPC: 1011800
// End NPC: 1011801

using namespace Sapphire;

class FesEst102 : public Sapphire::ScriptAPI::QuestScript
{
  private:
    // Basic quest information 
    // Quest vars / flags used
    // BitFlag8
    // UI8AL
    // UI8BH

    /// Countable Num: 1 Seq: 1 Event: 1 Listener: 1011801
    /// Countable Num: 1 Seq: 2 Event: 1 Listener: 1011800
    /// Countable Num: 1 Seq: 3 Event: 1 Listener: 1011810
    /// Countable Num: 1 Seq: 4 Event: 1 Listener: 1011801
    /// Countable Num: 1 Seq: 5 Event: 1 Listener: 1011833
    /// Countable Num: 1 Seq: 6 Event: 1 Listener: 1011810
    /// Countable Num: 1 Seq: 255 Event: 1 Listener: 1011801
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
    static constexpr auto Actor0 = 1011800;
    static constexpr auto Actor1 = 1011801;
    static constexpr auto Actor2 = 1011810;
    static constexpr auto Actor3 = 1011833;
    static constexpr auto Actor4 = 1011834;
    static constexpr auto Actor5 = 1011836;
    static constexpr auto Actor6 = 1011827;
    static constexpr auto Actor7 = 1011828;
    static constexpr auto Actor8 = 1011829;
    static constexpr auto Actor9 = 1011837;
    static constexpr auto Item0 = 2001564;
    static constexpr auto LevelEnpcId0 = 5713999;
    static constexpr auto LevelEnpcId1 = 5714006;
    static constexpr auto LevelEnpcId2 = 5714066;
    static constexpr auto LevelEnpcId3 = 5714067;
    static constexpr auto LevelEnpcId4 = 5714070;
    static constexpr auto LocActor0 = 1011841;
    static constexpr auto LocMotion0 = 85;
    static constexpr auto LocVfx0 = 300;
    static constexpr auto Status0 = 565;
    static constexpr auto Transformation0 = 18;

  public:
    FesEst102() : Sapphire::ScriptAPI::QuestScript( 66093 ){}; 
    ~FesEst102() = default; 

  //////////////////////////////////////////////////////////////////////
  // Event Handlers
  void onTalk( World::Quest& quest, Entity::Player& player, uint64_t actorId ) override
  {
    switch( actorId )
    {
      case Actor0:
      {
        break;
      }
      case Actor1:
      {
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
        break;
      }
      case Actor8:
      {
        break;
      }
      case Actor9:
      {
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
    eventMgr().playQuestScene( player, getId(), 0, NONE, bindSceneReturn( &FesEst102::Scene00000Return ) );
  }

  void Scene00000Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 ) // accept quest
    {
 
    }


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00001( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 1, NONE, bindSceneReturn( &FesEst102::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, NONE, bindSceneReturn( &FesEst102::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, NONE, bindSceneReturn( &FesEst102::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, NONE, bindSceneReturn( &FesEst102::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, NONE, bindSceneReturn( &FesEst102::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00006( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 6, NONE, bindSceneReturn( &FesEst102::Scene00006Return ) );
  }

  void Scene00006Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00007( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 7, NONE, bindSceneReturn( &FesEst102::Scene00007Return ) );
  }

  void Scene00007Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00008( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 8, NONE, bindSceneReturn( &FesEst102::Scene00008Return ) );
  }

  void Scene00008Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00009( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 9, NONE, bindSceneReturn( &FesEst102::Scene00009Return ) );
  }

  void Scene00009Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00010( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 10, NONE, bindSceneReturn( &FesEst102::Scene00010Return ) );
  }

  void Scene00010Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00011( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 11, NONE, bindSceneReturn( &FesEst102::Scene00011Return ) );
  }

  void Scene00011Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00012( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 12, NONE, bindSceneReturn( &FesEst102::Scene00012Return ) );
  }

  void Scene00012Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00013( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 13, NONE, bindSceneReturn( &FesEst102::Scene00013Return ) );
  }

  void Scene00013Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00014( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 14, NONE, bindSceneReturn( &FesEst102::Scene00014Return ) );
  }

  void Scene00014Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00015( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 15, NONE, bindSceneReturn( &FesEst102::Scene00015Return ) );
  }

  void Scene00015Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00016( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 16, NONE, bindSceneReturn( &FesEst102::Scene00016Return ) );
  }

  void Scene00016Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00017( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 17, NONE, bindSceneReturn( &FesEst102::Scene00017Return ) );
  }

  void Scene00017Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00018( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 18, NONE, bindSceneReturn( &FesEst102::Scene00018Return ) );
  }

  void Scene00018Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00019( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 19, NONE, bindSceneReturn( &FesEst102::Scene00019Return ) );
  }

  void Scene00019Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00020( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 20, NONE, bindSceneReturn( &FesEst102::Scene00020Return ) );
  }

  void Scene00020Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00021( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 21, NONE, bindSceneReturn( &FesEst102::Scene00021Return ) );
  }

  void Scene00021Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00022( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 22, NONE, bindSceneReturn( &FesEst102::Scene00022Return ) );
  }

  void Scene00022Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00023( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 23, NONE, bindSceneReturn( &FesEst102::Scene00023Return ) );
  }

  void Scene00023Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00024( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 24, NONE, bindSceneReturn( &FesEst102::Scene00024Return ) );
  }

  void Scene00024Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00025( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 25, FADE_OUT | HIDE_UI, bindSceneReturn( &FesEst102::Scene00025Return ) );
  }

  void Scene00025Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
        player.finishQuest( getId() );
    }

  }

  //////////////////////////////////////////////////////////////////////

  void Scene00026( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 26, NONE, bindSceneReturn( &FesEst102::Scene00026Return ) );
  }

  void Scene00026Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

};

EXPOSE_SCRIPT( FesEst102 );