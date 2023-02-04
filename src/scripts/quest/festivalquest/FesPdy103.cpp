// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include "Manager/EventMgr.h"
#include <Actor/Player.h>
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: FesPdy103_00501
// Quest Name: A Father's Folly
// Quest ID: 66037
// Start NPC: 1011780
// End NPC: 1011780

using namespace Sapphire;

class FesPdy103 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // BitFlag8
  // UI8AL

  /// Countable Num: 1 Seq: 1 Event: 1 Listener: 2005193
  /// Countable Num: 1 Seq: 255 Event: 1 Listener: 1011780
  // Steps in this quest ( 0 is before accepting,
  // 1 is first, 255 means ready for turning it in
  enum Sequence : uint8_t
  {
    Seq0 = 0,
    Seq1 = 1,
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1011780;//Nanapasi
  static constexpr auto Eobject0 = 2005193;//Destination
  static constexpr auto EventActionWaiting2Middle = 12;
  static constexpr auto LcutActor01 = 1011878;
  static constexpr auto LcutActor02 = 1011785;
  static constexpr auto LcutLevelHide01 = 4996401;
  static constexpr auto LcutLevelHide02 = 4996400;
  static constexpr auto LocBgm01 = 87;
  static constexpr auto LocBgm02 = 98;
  static constexpr auto LocEmote1 = 3754;
  static constexpr auto LocFace1 = 605;
  static constexpr auto LocLevelEnpcId01 = 5668092;
  static constexpr auto LocPosActor1 = 5668682;
  static constexpr auto LocPosActor2 = 5762414;
  static constexpr auto LocQuestCheck01 = 65572;
  static constexpr auto AchievementCompleteQuest = 1062;//Welcome to the Dollhouse

public:
  FesPdy103() : Sapphire::ScriptAPI::QuestScript( 66037 ){};
  ~FesPdy103() = default;

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
        else if( quest.getSeq() == Seq1 )
          Scene00004( quest, player );
        else if( quest.getSeq() == SeqFinish )
          Scene00005( quest, player );
        break;
      }
      case Eobject0:
      {
        eventMgr().eventActionStart(
                player, getId(), EventActionWaiting2Middle,
                [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                  Scene00003( quest, player );
                },
                nullptr, 0 );
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
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &FesPdy103::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, HIDE_HOTBAR, bindSceneReturn( &FesPdy103::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( Seq1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, HIDE_HOTBAR, bindSceneReturn( &FesPdy103::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &FesPdy103::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 0, 0 );
    quest.setSeq( SeqFinish );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, HIDE_HOTBAR, bindSceneReturn( &FesPdy103::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, HIDE_HOTBAR, bindSceneReturn( &FesPdy103::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      //TODO:Achievement
      player.finishQuest( getId() );
    }
  }
};

EXPOSE_SCRIPT( FesPdy103 );