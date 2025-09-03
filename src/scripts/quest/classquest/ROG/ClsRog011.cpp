// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: ClsRog011_00102
// Quest Name: My First Daggers
// Quest ID: 65638
// Start NPC: 1009944 (Lonwoerd)
// End NPC: 1009943 (Jacke)

using namespace Sapphire;

class ClsRog011 : public Sapphire::ScriptAPI::QuestScript
{
  private:
    // Basic quest information 
    // Quest vars / flags used
    // UI8AH

    /// Countable Num: 1 Seq: 255 Event: 1 Listener: 1009943
    // Steps in this quest ( 0 is before accepting, 
    // 1 is first, 255 means ready for turning it in
    enum Sequence : uint8_t
    {
      Seq0 = 0,
      SeqFinish = 255,
    };

    // Entities found in the script data of the quest
    static constexpr auto Actor0 = 1009944; // Lonwoerd ( Pos: -152.656006 2.856240 243.188004  Teri: 129 )
    static constexpr auto Actor1 = 1009943; // Jacke ( Pos: -153.367004 -129.440002 265.907990  Teri: 129 )
    static constexpr auto Classjob = 29;
    static constexpr auto GearsetUnlock = 1905;
    static constexpr auto LcutBgm0 = 97;
    static constexpr auto LcutBgm1 = 87;
    static constexpr auto LcutPos0 = 5120981;
    static constexpr auto LcutPos1 = 5120983;
    static constexpr auto LcutPos2 = 5121028;
    static constexpr auto LcutPos3 = 5404447;
    static constexpr auto LogmessageMonsterNotePageUnlock = 1020;
    static constexpr auto Poprange0 = 5341051;
    static constexpr auto Territorytype0 = 129;
    static constexpr auto UnlockImageClassRog = 258;

  public:
    ClsRog011() : Sapphire::ScriptAPI::QuestScript( 65638 ){}; 
    ~ClsRog011() = default; 

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
        else if( quest.getSeq() == SeqFinish )
          Scene00003( quest, player );
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
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &ClsRog011::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, HIDE_HOTBAR, bindSceneReturn( &ClsRog011::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( SeqFinish );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, FADE_OUT | CONDITION_CUTSCENE | DISABLE_SKIP | HIDE_UI, bindSceneReturn( &ClsRog011::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
      player.setLevelForClass( 1, Sapphire::Common::ClassJob::Rogue );
      player.addGearSet();
    }

  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, NONE, bindSceneReturn( &ClsRog011::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      warpMgr().requestMoveTerritory( player, Common::WarpType::WARP_TYPE_NORMAL, teriMgr().getTerritoryByTypeId( Territorytype0 )->getGuId(), { -151.8f, -129.4f, 258.5f }, 0.0f );
  }

};

EXPOSE_SCRIPT( ClsRog011 );