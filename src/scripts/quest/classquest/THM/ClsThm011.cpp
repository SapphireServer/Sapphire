// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: ClsThm011_00344
// Quest Name: Way of the Thaumaturge
// Quest ID: 65880
// Start NPC: 1002279 (Yayake)
// End NPC: 1001709 (Cocobygo)

using namespace Sapphire;

class ClsThm011 : public Sapphire::ScriptAPI::QuestScript
{
  private:
    // Basic quest information 
    // Quest vars / flags used
    // UI8AL

    /// Countable Num: 1 Seq: 255 Event: 1 Listener: 1001709
    // Steps in this quest ( 0 is before accepting, 
    // 1 is first, 255 means ready for turning it in
    enum Sequence : uint8_t
    {
      Seq0 = 0,
      SeqFinish = 255,
    };

    // Entities found in the script data of the quest
    static constexpr auto Actor0 = 1002279; // Yayake ( Pos: -196.886993 18.459999 59.952599  Teri: 130 )
    static constexpr auto Actor1 = 1001709; // Cocobygo ( Pos: -240.473999 18.700001 85.611702  Teri: 130 )
    static constexpr auto Classjob = 7;
    static constexpr auto GearsetUnlock = 1905;
    static constexpr auto LocActor1 = 1001708; // Cocobuki ( Pos: -250.347000 18.000000 80.903603  Teri: 130 )
    static constexpr auto LocActor2 = 1001709; // Cocobygo ( Pos: -240.473999 18.700001 85.611702  Teri: 130 )
    static constexpr auto LocActor3 = 1001710; // Cocobani ( Pos: -240.251007 18.799999 86.916702  Teri: 130 )
    static constexpr auto LocActor4 = 1001711; // Cocobezi ( Pos: -241.621002 18.799999 83.356400  Teri: 130 )
    static constexpr auto LocActor5 = 1001712; // Cocoboha ( Pos: -241.473999 19.577299 84.641701  Teri: 130 )
    static constexpr auto LocPosActor3 = 3996617; // 
    static constexpr auto LocPosActor4 = 3996618; // 
    static constexpr auto LocPosActor5 = 3996619; // 
    static constexpr auto LogmessageMonsterNotePageUnlock = 1014;
    static constexpr auto UnlockImageClassThm = 43;

  public:
    ClsThm011() : Sapphire::ScriptAPI::QuestScript( 65880 ){}; 
    ~ClsThm011() = default; 

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
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &ClsThm011::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, NONE, bindSceneReturn( &ClsThm011::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    // Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, FADE_OUT | CONDITION_CUTSCENE | DISABLE_SKIP | HIDE_UI, bindSceneReturn( &ClsThm011::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
      player.setLevelForClass( 1, Sapphire::Common::ClassJob::Thaumaturge );
      player.addGearSet();
    }

  }

};

EXPOSE_SCRIPT( ClsThm011 );