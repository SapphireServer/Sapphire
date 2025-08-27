// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: ClsAcn011_00452
// Quest Name: Way of the Arcanist
// Quest ID: 65988
// Start NPC: 1000895 (Murie)
// End NPC: 1000909 (Thubyrgeim)

using namespace Sapphire;

class ClsAcn011 : public Sapphire::ScriptAPI::QuestScript
{
  private:
    // Basic quest information 
    // Quest vars / flags used
    // UI8AL

    /// Countable Num: 0 Seq: 255 Event: 1 Listener: 1000909
    // Steps in this quest ( 0 is before accepting, 
    // 1 is first, 255 means ready for turning it in
    enum Sequence : uint8_t
    {
      Seq0 = 0,
      SeqFinish = 255,
    };

    // Entities found in the script data of the quest
    static constexpr auto Actor0 = 1000895; // Murie ( Pos: -335.743988 12.893800 1.388490  Teri: 129 )
    static constexpr auto Actor1 = 1000909; // Thubyrgeim ( Pos: -326.360992 12.893700 10.001000  Teri: 129 )
    static constexpr auto Classjob = 26;
    static constexpr auto GearsetUnlock = 1905;
    static constexpr auto LogmessageMonsterNotePageUnlock = 1016;
    static constexpr auto UnlockImageClassAcn = 45;

  public:
    ClsAcn011() : Sapphire::ScriptAPI::QuestScript( 65988 ){}; 
    ~ClsAcn011() = default; 

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
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &ClsAcn011::Scene00000Return ) );
  }

  void Scene00000Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 ) // accept quest
    {
      Scene00001( quest, player );
    }


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00001( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 1, HIDE_HOTBAR, bindSceneReturn( &ClsAcn011::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
      quest.setSeq( SeqFinish );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, FADE_OUT | HIDE_UI, bindSceneReturn( &ClsAcn011::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 ) // Said yes in cutscene
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
      player.setLevelForClass( 1, Sapphire::Common::ClassJob::Arcanist );
      player.addGearSet();
    }

  }

};

EXPOSE_SCRIPT( ClsAcn011 );