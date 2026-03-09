// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: ClsBsm011_00291
// Quest Name: Way of the Blacksmith
// Quest ID: 65827
// Start NPC: 1000995 (Randwulf )
// End NPC: 1000997 (Brithael)

using namespace Sapphire;

class ClsBsm011 : public Sapphire::ScriptAPI::QuestScript
{
  private:
    // Basic quest information 
    // Quest vars / flags used
    // UI8AL

    /// Countable Num: 1 Seq: 255 Event: 1 Listener: 1000997
    // Steps in this quest ( 0 is before accepting, 
    // 1 is first, 255 means ready for turning it in
    enum Sequence : uint8_t
    {
      Seq0 = 0,
      SeqFinish = 255,
    };

    // Entities found in the script data of the quest
    static constexpr auto Actor0 = 1000995; // Randwulf  ( Pos: -52.006199 42.799500 192.248001  Teri: 128 )
    static constexpr auto Actor1 = 1000997; // Brithael ( Pos: -31.265800 44.480000 185.533997  Teri: 128 )
    static constexpr auto Classjob = 9;
    static constexpr auto GearsetUnlock = 1905;
    static constexpr auto LogmessageCraftNotePageUnlock = 1195;
    static constexpr auto UnlockImageClassBsm = 46;
    static constexpr auto UnlockImageGearSet = 29;
    static constexpr auto UnlockImageRecipeBook = 16;

  public:
    ClsBsm011() : Sapphire::ScriptAPI::QuestScript( 65827 ){}; 
    ~ClsBsm011() = default; 

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
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &ClsBsm011::Scene00000Return ) );
  }

  void Scene00000Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 ) // accept quest
    {
      quest.setSeq( SeqFinish );
    }


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00001( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 1, HIDE_HOTBAR, bindSceneReturn( &ClsBsm011::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
      player.setLevelForClass( 1, Sapphire::Common::ClassJob::Blacksmith );
      player.addGearSet();
    }

  }

};

EXPOSE_SCRIPT( ClsBsm011 );