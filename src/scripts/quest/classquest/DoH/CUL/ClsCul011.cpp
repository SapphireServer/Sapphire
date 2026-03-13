// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: ClsCul011_00271
// Quest Name: Way of the Culinarian
// Quest ID: 65807
// Start NPC: 1000946 (Charlys)
// End NPC: 1000947 (Lyngsath)

using namespace Sapphire;

class ClsCul011 : public Sapphire::ScriptAPI::QuestScript
{
  private:
    // Basic quest information 
    // Quest vars / flags used
    // UI8AL

    /// Countable Num: 1 Seq: 255 Event: 1 Listener: 1000947
    // Steps in this quest ( 0 is before accepting, 
    // 1 is first, 255 means ready for turning it in
    enum Sequence : uint8_t
    {
      Seq0 = 0,
      SeqFinish = 255,
    };

    // Entities found in the script data of the quest
    static constexpr auto Actor0 = 1000946; // Charlys ( Pos: -61.122799 42.347099 -164.035004  Teri: 128 )
    static constexpr auto Actor1 = 1000947; // Lyngsath ( Pos: -54.642601 43.991699 -151.201996  Teri: 128 )
    static constexpr auto Classjob = 15;
    static constexpr auto GearsetUnlock = 1905;
    static constexpr auto LogmessageCraftNotePageUnlock = 1194;
    static constexpr auto UnlockImageClassCul = 51;
    static constexpr auto UnlockImageGearSet = 29;
    static constexpr auto UnlockImageRecipeBook = 16;

  public:
    ClsCul011() : Sapphire::ScriptAPI::QuestScript( 65807 ){}; 
    ~ClsCul011() = default; 

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
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &ClsCul011::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, HIDE_HOTBAR, bindSceneReturn( &ClsCul011::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
      player.setLevelForClass( 1, Sapphire::Common::ClassJob::Culinarian );
      player.addGearSet();
    }

  }

};

EXPOSE_SCRIPT( ClsCul011 );