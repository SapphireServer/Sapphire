#include <Actor/Player.h>
#include <ScriptObject.h>
#include "Manager/EventMgr.h"
#include "Event/EventHandler.h"
#include <Service.h>

// Quest Script: ManFst001_00039
// Quest Name: Coming to Gridania
// Quest ID: 65575
// Start NPC: 1001148
// End NPC: 1001140

using namespace Sapphire;

class ManFst001 : public Sapphire::ScriptAPI::QuestScript
{
private:
  static constexpr auto SEQ_0 = 0;
  static constexpr auto SEQ_FINISH = 255;

  static constexpr auto RewardExpFactor = 50;
  static constexpr auto RewardGil = 103;

  static constexpr auto ACTOR0 = 1001148;
  static constexpr auto ACTOR1 = 1001140;
  static constexpr auto CUT_EVENT = 29;
  static constexpr auto EOBJECT0 = 2001659;
  static constexpr auto EOBJECT1 = 2001660;
  static constexpr auto EOBJECT7 = 2616477;
  static constexpr auto EVENT_ACTION_SEARCH = 1;
  static constexpr auto HOWTO_QUEST_ACCEPT = 12;
  static constexpr auto HOWTO_QUEST_ANNOUNCE = 2;
  static constexpr auto HOWTO_REWARD = 11;
  static constexpr auto HOWTO_TODO = 3;
  static constexpr auto OPENING_EVENT_HANDLER = 1245186;
  static constexpr auto SEQ_2_ACTOR1 = 2;

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &ManFst001::Scene00000Return ) );
  }

  void Scene00000Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 ) // accept quest
    {
      player.setOpeningSequence( 2 );
      Scene00001( quest, player );
    }
  }

  void Scene00001( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 1, DISABLE_SKIP | HIDE_HOTBAR | SET_BASE, bindSceneReturn( &ManFst001::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    Scene00002( quest, player );
  }

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, 0, bindSceneReturn( &ManFst001::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( SEQ_FINISH );

    eventMgr().eventStart( player, result.actorId, OPENING_EVENT_HANDLER, Event::EventHandler::Nest, 0, 0 );
    eventMgr().playQuestScene( player, OPENING_EVENT_HANDLER, 0x1E, HIDE_HOTBAR | NO_DEFAULT_CAMERA );
  }

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, FADE_OUT | HIDE_HOTBAR | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &ManFst001::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    Scene00005( quest, player );
  }

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, INVIS_OTHER_PC, bindSceneReturn( &ManFst001::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
    }
  }

public:
  ManFst001() : Sapphire::ScriptAPI::QuestScript( 65575 )
  {
  }

  void onTalk( World::Quest& quest, Entity::Player& player, uint64_t actorId ) override
  {
    if( actorId == ACTOR0 )
      Scene00000( quest, player );
    else if( actorId == ACTOR1 )
      Scene00004( quest, player );
  }
};

EXPOSE_SCRIPT( ManFst001 );