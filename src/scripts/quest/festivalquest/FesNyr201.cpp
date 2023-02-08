// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include "Manager/EventMgr.h"
#include "Manager/PlayerMgr.h"
#include <Actor/Player.h>
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: FesNyr201_02217
// Quest Name: Monkey about Town
// Quest ID: 67753
// Start NPC: 1016387 (saru bugyo)
// End NPC: 1016387 (saru bugyo)

using namespace Sapphire;

class FesNyr201 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // BitFlag8
  // UI8AH
  // UI8AL

  /// Countable Num: 1 Seq: 1 Event: 1 Listener: 5010000
  /// Countable Num: 1 Seq: 255 Event: 1 Listener: 5010000
  // Steps in this quest ( 0 is before accepting,
  // 1 is first, 255 means ready for turning it in
  enum Sequence : uint8_t
  {
    Seq0 = 0,
    Seq1 = 1,
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1016387;// Saru Bugyo ( Pos: -50.018700 6.485050 -91.088997  Teri: 133 )
  static constexpr auto Actor1 = 5010000;//
  static constexpr auto Actor2 = 1016388;// Mochi Daikan ( Pos: -46.919800 5.762080 -100.890999  Teri: 133 )
  static constexpr auto Fate0 = 936;
  static constexpr auto Fate1 = 937;
  static constexpr auto Fate2 = 938;
  static constexpr auto Fate3 = 939;
  static constexpr auto Fate4 = 940;
  static constexpr auto Fate5 = 941;
  static constexpr auto LevelEnpcId0 = 6148089;//
  static constexpr auto LevelEnpcId1 = 6148090;//
  static constexpr auto LocActor0 = 1016397;   // Mochi Daikan
  static constexpr auto LocActor1 = 1016398;   // Monkey Handler
  static constexpr auto LocActor2 = 1016399;   // Jiromaru
  static constexpr auto LocActor3 = 1016400;   //
  static constexpr auto LocActor4 = 1016401;   //
  static constexpr auto LocActor5 = 1016402;   //
  static constexpr auto LocActor6 = 1016403;   // Gridanian Citizen
  static constexpr auto LocActor7 = 1016509;   //
  static constexpr auto LocMotion0 = 796;
  static constexpr auto LocMotion1 = 801;

public:
  FesNyr201() : Sapphire::ScriptAPI::QuestScript( 67753 ){};
  ~FesNyr201() = default;

  //////////////////////////////////////////////////////////////////////
  // Event Handlers98
  void onTalk( World::Quest& quest, Entity::Player& player, uint64_t actorId ) override
  {
    switch( actorId )
    {
      case Actor0:
      {
        if( quest.getSeq() == Seq0 )
          Scene00000( quest, player );
        else if( quest.getSeq() == Seq1 )
          Scene00002( quest, player );
        else if( quest.getSeq() == SeqFinish )
          Scene00004( quest, player );
        break;
      }
      case Actor1:
      {
        break;
      }
      case Actor2:
      {
        if( quest.getSeq() == SeqFinish )
          Scene00005( quest, player );
        else
          Scene00003( quest, player );
        break;
      }
    }
  }

  //TODO: This func doesn't exist, leaving behind for future implementation
  void onFateComplete( World::Quest& quest, Entity::Player& player, uint32_t fateId )
  {
    if( fateId == Fate0 || fateId == Fate1 || fateId == Fate2 || fateId == Fate3 || fateId == Fate4 || fateId == Fate5 )//Pounding Rice, Pounding Hearts FATE
      quest.setSeq( SeqFinish );
  }

private:
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, NONE, bindSceneReturn( &FesNyr201::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, FADE_OUT | HIDE_UI, bindSceneReturn( &FesNyr201::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( Seq1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, NONE, bindSceneReturn( &FesNyr201::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, NONE, bindSceneReturn( &FesNyr201::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, FADE_OUT | HIDE_UI, bindSceneReturn( &FesNyr201::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )// complete quest
    {
      player.finishQuest( getId() );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, NONE, bindSceneReturn( &FesNyr201::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }
};

EXPOSE_SCRIPT( FesNyr201 );