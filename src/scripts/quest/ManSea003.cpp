// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: ManSea003_00109
// Quest Name: Close to Home
// Quest ID: 65645
// Start NPC: 1002697 (Baderon)
// End NPC: 1000972 (Baderon)

using namespace Sapphire;

class ManSea003 : public Sapphire::ScriptAPI::QuestScript
{
  private:
    // Basic quest information 
    // Quest vars / flags used
    // BitFlag8
    // UI8AL
    // UI8BH
    // UI8BL
    // UI8CH

    /// Countable Num: 1 Seq: 1 Event: 1 Listener: 8
    /// Countable Num: 1 Seq: 1 Event: 1 Listener: 1001217
    /// Countable Num: 1 Seq: 1 Event: 1 Listener: 1000895
    /// Countable Num: 0 Seq: 255 Event: 1 Listener: 1000972
    // Steps in this quest ( 0 is before accepting, 
    // 1 is first, 255 means ready for turning it in
    enum Sequence : uint8_t
    {
      Seq0 = 0,
      Seq1 = 1,
      SeqFinish = 255,
    };

    // Quest rewards
    static constexpr auto RewardExpFactor = 100;
    static constexpr auto RewardGil = 107;

    // Entities found in the script data of the quest
    static constexpr auto Actor0 = 1002697; // Baderon ( Pos: 20.297800 40.199902 -6.102380  Teri: 181 )
    static constexpr auto Actor1 = 1001217; // Swozblaet ( Pos: -140.856003 18.173401 17.013700  Teri: 129 )
    static constexpr auto Actor2 = 1000895; // Murie ( Pos: -335.743988 12.893800 1.388490  Teri: 129 )
    static constexpr auto Actor3 = 1000972; // Baderon ( Pos: 20.297800 40.199902 -6.102400  Teri: 128 )
    static constexpr auto Aetheryte0 = 8;
    static constexpr auto BindActor0 = 6229226; // 
    static constexpr auto Item0 = 2000105;
    static constexpr auto LocActor1 = 1001023; // Sundhimal ( Pos: -78.629799 18.000299 -22.629200  Teri: 129 )
    static constexpr auto LocFace0 = 604;
    static constexpr auto LocFace1 = 605;
    static constexpr auto LocPosCam1 = 4106696;
    static constexpr auto LocPosCam2 = 4106698;
    static constexpr auto Reward0 = 1;
    static constexpr auto Screenimage0 = 14;
    static constexpr auto UnlockDesion = 14;

  public:
    ManSea003() : Sapphire::ScriptAPI::QuestScript( 65645 ){}; 
    ~ManSea003() = default; 

  //////////////////////////////////////////////////////////////////////
  // Event Handlers
  void onTalk( World::Quest& quest, Entity::Player& player, uint64_t actorId ) override
    {
      switch( actorId )
      {
        case Actor0:
        {
          Scene00000( quest, player );
          break;
        }
        case Actor1:
        {
          Scene00004( quest, player );
          break;
        }
        case Actor2:
        {
          Scene00006( quest, player );
          break;
        }
        case Actor3:
        {
          Scene00007( quest, player );
          break;
        }
        case Aetheryte0:
        {
          eventMgr().eventActionStart( player, getId(), 0x13, [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
              player.registerAetheryte( Aetheryte0 );
              player.setRewardFlag( Common::UnlockEntry::Return );
              Scene00002( quest, player ); }, nullptr, getId() );
          break;
        }
      }
  }

  private:
    void checkQuestCompletion( World::Quest& quest, Entity::Player& player )
    {
      auto var_Attune = quest.getUI8AL();
      auto var_Class = quest.getUI8BH();
      auto var_Trade = quest.getUI8BL();

      if( var_Attune == 1 && var_Class == 1 && var_Trade == 1 )
      {
        quest.setSeq( SeqFinish );
      }
    }
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &ManSea003::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &ManSea003::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( Seq1 );
    quest.setUI8CH( 1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, NO_DEFAULT_CAMERA | HIDE_HOTBAR, bindSceneReturn( &ManSea003::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    Scene00003( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &ManSea003::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8BL( 1 );
    eventMgr().sendEventNotice( player, getId(), 0, 0, 0, 0 );
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, HIDE_HOTBAR, bindSceneReturn( &ManSea003::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 ) // Turn in quest item
    {
      quest.setUI8CH( 0 );
      Scene00005( quest, player );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &ManSea003::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8BH( 1 );
    eventMgr().sendEventNotice( player, getId(), 1, 0, 0, 0 );
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00006( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 6, HIDE_HOTBAR, bindSceneReturn( &ManSea003::Scene00006Return ) );
  }

  void Scene00006Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8AL( 1 );
    eventMgr().sendEventNotice( player, getId(), 2, 0, 0, 0 );
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00007( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 7, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &ManSea003::Scene00007Return ) );
  }

  void Scene00007Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
    }

  }

};

EXPOSE_SCRIPT( ManSea003 );