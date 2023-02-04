// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include "Manager/EventMgr.h"
#include <Actor/Player.h>
#include <Actor/BNpc.h>
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: ManFst303_00683
// Quest Name: Wood's Will Be Done
// Quest ID: 66219
// Start NPC: 1002394
// End NPC: 1005012

using namespace Sapphire;

class ManFst303 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // UI8AL

  /// Countable Num: 0 Seq: 255 Event: 1 Listener: 1005012
  // Steps in this quest ( 0 is before accepting,
  // 1 is first, 255 means ready for turning it in
  enum Sequence : uint8_t
  {
    Seq0 = 0,
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1002394;//Serpent Personnel Officer
  static constexpr auto Actor1 = 1005012;//Scion of the Seventh Dawn
  static constexpr auto LocAction1 = 1002;
  static constexpr auto LocActor0 = 1003783;
  static constexpr auto LocSe1 = 42;
  static constexpr auto LocTalkshape1 = 6;
  static constexpr auto LogmessageMonsternotePageUnlock = 1017;
  static constexpr auto Ncut0 = 220;
  static constexpr auto Ncut1 = 391;
  static constexpr auto OrderOfTwinAdder = 2;
  static constexpr auto Poprange0 = 4148347;
  static constexpr auto Reward0 = 22;
  static constexpr auto Screenimage0 = 32;
  static constexpr auto Screenimage1 = 69;

public:
  ManFst303() : Sapphire::ScriptAPI::QuestScript( 66219 ){};
  ~ManFst303() = default;

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
        if( quest.getSeq() == SeqFinish )
          Scene00003( quest, player );
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
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &ManFst303::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &ManFst303::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    player.setGc( OrderOfTwinAdder );
    player.setGcRankAt( OrderOfTwinAdder, 1 );
    Scene00002( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, HIDE_HOTBAR, bindSceneReturn( &ManFst303::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( SeqFinish );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, HIDE_HOTBAR, bindSceneReturn( &ManFst303::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      Scene00004( quest, player );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &ManFst303::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    player.finishQuest( getId() );
    warpMgr().requestWarp( player, Common::WarpType::WARP_TYPE_NORMAL, { 29.3651f, 1.f, -0.0461532f }, 1.52733f );//Manual Pos
  }
};

EXPOSE_SCRIPT( ManFst303 );