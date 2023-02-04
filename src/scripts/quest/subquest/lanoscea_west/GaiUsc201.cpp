// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include "Manager/EventMgr.h"
#include <Actor/Player.h>
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: GaiUsc201_00960
// Quest Name: It's Probably Not Pirates
// Quest ID: 66496
// Start NPC: 1006497
// End NPC: 1006497

using namespace Sapphire;

class GaiUsc201 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // BitFlag8
  // UI8AL

  /// Countable Num: 0 Seq: 1 Event: 1 Listener: 1006498
  /// Countable Num: 0 Seq: 255 Event: 1 Listener: 1006499
  // Steps in this quest ( 0 is before accepting,
  // 1 is first, 255 means ready for turning it in
  enum Sequence : uint8_t
  {
    Seq0 = 0,
    Seq1 = 1,
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1006497;//Ceana
  static constexpr auto Actor1 = 1006498;//Alza Gamilza
  static constexpr auto Actor2 = 1006499;//Firkmann
  static constexpr auto Actor3 = 1006500;//Q'ahnebb

public:
  GaiUsc201() : Sapphire::ScriptAPI::QuestScript( 66496 ){};
  ~GaiUsc201() = default;

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
          Scene00005( quest, player );
        break;
      }
      case Actor1:
      {
        if( quest.getSeq() == Seq1 )
          Scene00002( quest, player );
        break;
      }
      case Actor2:
      {
        if( quest.getSeq() == Seq1 )
          Scene00003( quest, player );
        break;
      }
      case Actor3:
      {
        if( quest.getSeq() == Seq1 )
          Scene00004( quest, player );
        break;
      }
    }
  }


private:
  void checkQuestCompletion( World::Quest& quest, Entity::Player& player, uint8_t bitFlagIdx )
  {
    quest.setBitFlag8( bitFlagIdx, true );
    quest.setUI8AL( quest.getUI8AL() + 1 );
    eventMgr().sendEventNotice( player, getId(), 0, 2, quest.getUI8AL(), 3 );
    if( quest.getUI8AL() >= 3 )
    {
      quest.setBitFlag8( 1, false );
      quest.setBitFlag8( 2, false );
      quest.setBitFlag8( 3, false );
      quest.setUI8AL( 0 );
      quest.setSeq( SeqFinish );
    }
  }
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &GaiUsc201::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, HIDE_HOTBAR, bindSceneReturn( &GaiUsc201::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( Seq1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, HIDE_HOTBAR, bindSceneReturn( &GaiUsc201::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    checkQuestCompletion( quest, player, 1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, HIDE_HOTBAR, bindSceneReturn( &GaiUsc201::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    checkQuestCompletion( quest, player, 2 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, HIDE_HOTBAR, bindSceneReturn( &GaiUsc201::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    checkQuestCompletion( quest, player, 3 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, HIDE_HOTBAR, bindSceneReturn( &GaiUsc201::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult(1) );
    }
  }
};

EXPOSE_SCRIPT( GaiUsc201 );