// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: ClsGla011_00285
// Quest Name: Way of the Gladiator
// Quest ID: 65821
// Start NPC: 1002277 (Lulutsu)
// End NPC: 1001739 (Mylla)

using namespace Sapphire;

class ClsGla011 : public Sapphire::ScriptAPI::QuestScript
{
  private:
    // Basic quest information 
    // Quest vars / flags used
    // UI8AL

    /// Countable Num: 1 Seq: 255 Event: 1 Listener: 1001739
    // Steps in this quest ( 0 is before accepting, 
    // 1 is first, 255 means ready for turning it in
    enum Sequence : uint8_t
    {
      Seq0 = 0,
      SeqFinish = 255,
    };

    // Entities found in the script data of the quest
    static constexpr auto Actor0 = 1002277; // Lulutsu ( Pos: -97.520401 6.973330 23.605700  Teri: 131 )
    static constexpr auto Actor1 = 1001739; // Mylla ( Pos: -94.529701 6.499970 39.810699  Teri: 131 )
    static constexpr auto Classjob = 1;
    static constexpr auto GearsetUnlock = 1905;
    static constexpr auto LogmessageMonsterNotePageUnlock = 1010;
    static constexpr auto UnlockImageClassGla = 36;

  public:
    ClsGla011() : Sapphire::ScriptAPI::QuestScript( 65821 ){}; 
    ~ClsGla011() = default; 

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
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &ClsGla011::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, FADE_OUT | HIDE_UI, bindSceneReturn( &ClsGla011::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 ) // Say yes in cutscene
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
      player.setLevelForClass( 1, Sapphire::Common::ClassJob::Gladiator );
      player.addGearSet();
    }

  }

};

EXPOSE_SCRIPT( ClsGla011 );