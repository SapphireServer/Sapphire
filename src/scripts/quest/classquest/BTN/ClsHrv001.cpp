// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include "Manager/EventMgr.h"
#include <Actor/Player.h>
#include <Actor/BNpc.h>
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: ClsHrv001_00003
// Quest Name: Way of the Botanist
// Quest ID: 65539
// Start NPC: 1000294
// End NPC: 1000815

using namespace Sapphire;

class ClsHrv001 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // UI8AL

  /// Countable Num: 1 Seq: 255 Event: 1 Listener: 1000815
  // Steps in this quest ( 0 is before accepting,
  // 1 is first, 255 means ready for turning it in
  enum Sequence : uint8_t
  {
    Seq0 = 0,
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1000294;//Leonceault
  static constexpr auto Actor1 = 1000815;//Fufucha
  static constexpr auto Classjob = 17;
  static constexpr auto GearsetUnlock = 1905;
  static constexpr auto LogmessageGatheringNotePageUnlock = 1094;
  static constexpr auto UnlockImageClassHrv = 26;
  static constexpr auto UnlockImageGatherBook = 17;
  static constexpr auto UnlockImageGearSet = 29;

public:
  ClsHrv001() : Sapphire::ScriptAPI::QuestScript( 65539 ){};
  ~ClsHrv001() = default;

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


private:
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, NONE, bindSceneReturn( &ClsHrv001::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, NONE, bindSceneReturn( &ClsHrv001::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      //TODO:Unlock gathering log? Maybe?
      player.finishQuest( getId() );
      player.setLevelForClass( 1, Sapphire::Common::ClassJob::Botanist );
      player.setMaxGearSets( player.getMaxGearSets() + 1 );
    }
  }
};

EXPOSE_SCRIPT( ClsHrv001 );