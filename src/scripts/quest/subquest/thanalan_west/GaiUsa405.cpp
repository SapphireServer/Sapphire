// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include "Manager/EventMgr.h"
#include <Actor/Player.h>
#include <Actor/BNpc.h>
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: GaiUsa405_00747
// Quest Name: Shadow of Darkness
// Quest ID: 66283
// Start NPC: 1006688
// End NPC: 1006196

using namespace Sapphire;

class GaiUsa405 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // UI8AL

  /// Countable Num: 0 Seq: 1 Event: 1 Listener: 1004576
  /// Countable Num: 0 Seq: 255 Event: 1 Listener: 1006196
  // Steps in this quest ( 0 is before accepting,
  // 1 is first, 255 means ready for turning it in
  enum Sequence : uint8_t
  {
    Seq0 = 0,
    Seq1 = 1,
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1006688;//Minfilia
  static constexpr auto Actor1 = 1004576;//Swift <Flame Commander>
  static constexpr auto Actor2 = 1006196;//Hihibaru
  static constexpr auto CutScene01 = 96;
  static constexpr auto Seq0Actor0Lq = 90;

public:
  GaiUsa405() : Sapphire::ScriptAPI::QuestScript( 66283 ){};
  ~GaiUsa405() = default;

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
        break;
      }
      case Actor1:
      {
        if( quest.getSeq() == Seq1 )
          Scene00001( quest, player );
        break;
      }
      case Actor2:
      {
        if( quest.getSeq() == SeqFinish )
          Scene00002( quest, player );
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
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &GaiUsa405::Scene00000Return ) );
  }

  void Scene00000Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )// accept quest
    {
      Scene00090( quest, player );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00001( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 1, HIDE_HOTBAR, bindSceneReturn( &GaiUsa405::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 0, 0 );
    quest.setSeq( SeqFinish );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, HIDE_HOTBAR, bindSceneReturn( &GaiUsa405::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId() );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00090( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 90, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &GaiUsa405::Scene00090Return ) );
  }

  void Scene00090Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( Seq1 );
  }
};

EXPOSE_SCRIPT( GaiUsa405 );