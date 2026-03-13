// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: ManSea005_00543
// Quest Name: Lurkers in the Grotto
// Quest ID: 66079
// Start NPC: 1002626 (Staelwyrn)
// End NPC: 1002626 (Staelwyrn)

using namespace Sapphire;

class ManSea005 : public Sapphire::ScriptAPI::QuestScript
{
  private:
    // Basic quest information 
    // Quest vars / flags used
    // UI8AL
    // UI8BH

    /// Countable Num: 0 Seq: 1 Event: 1 Listener: 2001582
    /// Countable Num: 0 Seq: 2 Event: 15 Listener: 5020000
    /// Countable Num: 0 Seq: 255 Event: 1 Listener: 1002626
    // Steps in this quest ( 0 is before accepting, 
    // 1 is first, 255 means ready for turning it in
    enum Sequence : uint8_t
    {
      Seq0 = 0,
      Seq1 = 1,
      Seq2 = 2,
      SeqFinish = 255,
    };

    // Entities found in the script data of the quest
    static constexpr auto Actor0 = 1002626; // Staelwyrn ( Pos: 207.263000 112.839996 -222.431000  Teri: 134 )
    static constexpr auto CutScene02 = 134;
    static constexpr auto CutScene03 = 56;
    static constexpr auto CutScene04 = 135;
    static constexpr Common::QuestEobject Eobject0 = { 2001582, 134, { -58.631599, 27.154499, -141.768005 }, 1.000000 }; // Stone Monument
    static constexpr auto EventActionProcessMiddle = 16;
    static constexpr auto Item0 = 2000522;
    static constexpr auto Questbattle0 = 35;
    static constexpr auto Seq0Actor0Lq = 90; // Spriggan Collector
    static constexpr auto Territorytype0 = 252;
    static constexpr auto Territorytype1 = 134;

  public:
    ManSea005() : Sapphire::ScriptAPI::QuestScript( 66079 ){}; 
    ~ManSea005() = default; 

  //////////////////////////////////////////////////////////////////////
  // Event Handlers
  void onTalk( World::Quest& quest, Entity::Player& player, uint64_t actorId ) override
  {
    if( actorId == Actor0 )
    {
      switch( quest.getSeq() )
      {
        case Seq0:
        {
          Scene00000( quest, player );
          break;
        }
        case Seq1:
        {
          Scene00003( quest, player );
          break;
        }
        case Seq2:
        {
          Scene00004( quest, player );
          break;
        }
        case SeqFinish:
        {
          Scene00005( quest, player );
          break;
        }
      }
    }
  }


  private:
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
    {
      //playerMgr().sendDebug( player, "ManSea005:66079 calling Scene00000: Normal(Talk, QuestOffer, TargetCanMove), id=STAELWYRN" );
      eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &ManSea005::Scene00000Return ) );
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
    //playerMgr().sendDebug( player, "ManSea005:66079 calling Scene00001: Normal(Talk, FadeIn, QuestAccept, TargetCanMove), id=STAELWYRN" );
    eventMgr().playQuestScene( player, getId(), 1, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &ManSea005::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( Seq1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    //playerMgr().sendDebug( player, "ManSea005:66079 calling Scene00003: Normal(QuestBattle, YesNo, SystemTalk), id=unknown" );
    eventMgr().playQuestScene( player, getId(), 3, HIDE_HOTBAR, bindSceneReturn( &ManSea005::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
    {
      eventMgr().eventFinish( player, result.eventId, 1 );
      teriMgr().createAndJoinQuestBattle( player, m_id, 35 );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    //playerMgr().sendDebug( player, "ManSea005:66079 calling Scene00004: Normal(CutScene, AutoFadeIn), id=unknown" );
    eventMgr().playQuestScene( player, getId(), 4, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &ManSea005::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( SeqFinish );
    quest.setUI8BH( 1 );
    //playerMgr().sendDebug( player, "Finished with AutoFadeIn scene, reloading zone..." );
    eventMgr().eventFinish( player, result.eventId, 1 );
    warpMgr().requestWarp( player, Common::WarpType::WARP_TYPE_NORMAL, player.getPos(), player.getRot() );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    //playerMgr().sendDebug( player, "ManSea005:66079 calling Scene00005: NpcTrade(Basic), id=unknown" );
    eventMgr().playQuestScene( player, getId(), 5, NONE, bindSceneReturn( &ManSea005::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    Scene00006( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00006( World::Quest& quest, Entity::Player& player )
  {
    //playerMgr().sendDebug( player, "ManSea005:66079 calling Scene00006: Normal(Talk, FadeIn, QuestReward, QuestComplete, TargetCanMove), id=STAELWYRN" );
    eventMgr().playQuestScene( player, getId(), 6, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &ManSea005::Scene00006Return ) );
  }

  void Scene00006Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
    }

  }

};

EXPOSE_SCRIPT( ManSea005 );