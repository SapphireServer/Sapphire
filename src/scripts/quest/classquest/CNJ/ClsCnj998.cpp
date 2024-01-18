// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include "Manager/EventMgr.h"
#include <Actor/Player.h>
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: ClsCnj998_00133
// Quest Name: Way of the Conjurer
// Quest ID: 65669
// Start NPC: 1000323 (Madelle)
// End NPC: 1000692 (E-Sumi-Yan)

using namespace Sapphire;

class ClsCnj998 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // UI8AL

  /// Countable Num: 1 Seq: 255 Event: 1 Listener: 1000692
  // Steps in this quest ( 0 is before accepting,
  // 1 is first, 255 means ready for turning it in
  enum Sequence : uint8_t
  {
    Seq0 = 0,
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1000323;// Madelle ( Pos: -234.028000 -4.000220 -11.062800  Teri: 133 )
  static constexpr auto Actor1 = 1000692;// E-sumi-yan ( Pos: -258.808014 -5.773500 -27.237400  Teri: 133 )
  static constexpr auto Classjob = 6;
  static constexpr auto GearsetUnlock = 1905;
  static constexpr auto LogmessageMonsterNotePageUnlock = 1009;
  static constexpr auto UnlockImageClassCnj = 25;

public:
  ClsCnj998() : Sapphire::ScriptAPI::QuestScript( 65669 ){};
  ~ClsCnj998() = default;

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
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &ClsCnj998::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, FADE_OUT | HIDE_UI, bindSceneReturn( &ClsCnj998::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId() );
      player.setLevelForClass( 1, Sapphire::Common::ClassJob::Conjurer );
      player.addGearSet();
    }
  }
};

EXPOSE_SCRIPT( ClsCnj998 );