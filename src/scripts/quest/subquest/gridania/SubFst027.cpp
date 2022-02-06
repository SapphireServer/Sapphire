// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include "Manager/EventMgr.h"
#include <Actor/Player.h>
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: SubFst027_00176
// Quest Name: On to Bentbranch
// Quest ID: 65712
// Start NPC: 1000100
// End NPC: 1000470

using namespace Sapphire;

class SubFst027 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // UI8AL

  /// Countable Num: 1 Seq: 255 Event: 1 Listener: 1000470
  // Steps in this quest ( 0 is before accepting,
  // 1 is first, 255 means ready for turning it in
  enum Sequence : uint8_t
  {
    Seq0 = 0,
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1000100;//Mother Miounne
  static constexpr auto Actor1 = 1000470;//Keitha
  static constexpr auto LocFace1 = 605;
  static constexpr auto LocFace2 = 604;
  static constexpr auto Seq0Actor0 = 0;
  static constexpr auto Seq1Actor1 = 1;

public:
  SubFst027() : Sapphire::ScriptAPI::QuestScript( 65712 ){};
  ~SubFst027() = default;

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
          Scene00001( quest, player );
        break;
      }
    }
  }

  void onEventItem( World::Quest& quest, Entity::Player& player, uint64_t actorId ) override
  {
  }


private:
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &SubFst027::Scene00000Return ) );
  }

  void Scene00000Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )// accept quest
    {
      quest.setSeq( SeqFinish );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00001( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 1, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &SubFst027::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
    }
  }
};

EXPOSE_SCRIPT( SubFst027 );