// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: ManSea001_00107
// Quest Name: Coming to Limsa Lominsa
// Quest ID: 65643
// Start NPC: 1001028 (Ryssfloh)
// End NPC: 1002697 (Baderon)

using namespace Sapphire;

class ManSea001 : public Sapphire::ScriptAPI::QuestScript
{
  private:
    // Basic quest information 
    // Quest vars / flags used
    // BitFlag8
    // UI8AL

    /// Countable Num: 1 Seq: 1 Event: 1 Listener: 1002732
    /// Countable Num: 0 Seq: 255 Event: 1 Listener: 2001679
    // Steps in this quest ( 0 is before accepting, 
    // 1 is first, 255 means ready for turning it in
    enum Sequence : uint8_t
    {
      Seq0 = 0,
      Seq1 = 1,
      SeqFinish = 255,
    };

    // Entities found in the script data of the quest
    static constexpr auto Actor0 = 1001028; // Ryssfloh ( Pos: -39.841301 20.000000 -4.951920  Teri: 181 )
    static constexpr auto Actor1 = 1002732; // Grehfarr ( Pos: 11.192500 20.999300 13.347300  Teri: 181 )
    static constexpr auto Actor2 = 1002697; // Baderon ( Pos: 20.297800 40.199902 -6.102380  Teri: 181 )
    static constexpr auto CutEvent = 202;
    static constexpr auto Eobject0 = 2001679; //{ 2001679, 181, { -57.398499, 18.000000, 0.063036 }, 1.000000 }; // 
    static constexpr auto Eobject1 = 2001680; //{ 2001680, 181, { -35.055000, 20.000000, -0.014301 }, 1.000000 }; // 
    static constexpr auto EventActionSearch = 1;
    static constexpr auto LocActor0 = 1002732; // Grehfarr ( Pos: 11.192500 20.999300 13.347300  Teri: 181 )
    static constexpr auto LocPosActor0 = 4107186; // 
    static constexpr auto OpeningEventHandler = 1245185;
    static constexpr auto Poprange0 = 4127803;
    static constexpr auto Territorytype0 = 181;

    void checkQuestCompletion( World::Quest& quest, Entity::Player& player )
    {
      if( quest.getUI8AL() == 1 )
      {
        quest.setUI8AL( 0 );
        quest.setBitFlag8( 1, false );
        quest.setSeq( SeqFinish );
      }
    }

  public:
    ManSea001() : Sapphire::ScriptAPI::QuestScript( 65643 ){}; 
    ~ManSea001() = default; 

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
        if( quest.getSeq() == Seq1 )
        {
          if( quest.getUI8AL() != 1 )
            Scene00005( quest, player );
        }
        else if( quest.getSeq() == SeqFinish )
          Scene00013( quest, player );
        break;
      }
      case Actor2:
      {
        if( quest.getSeq() == SeqFinish )
          Scene00011( quest, player );
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
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &ManSea001::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &ManSea001::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    Scene00002( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, HIDE_HOTBAR, bindSceneReturn( &ManSea001::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    player.setOpeningSequence( 2 );
    checkQuestCompletion( quest, player );
    quest.setSeq( Seq1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, HIDE_HOTBAR, bindSceneReturn( &ManSea001::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if ( result.getResult( 0 ) == 1 ) // say yes to lift attendant
    {
      quest.setUI8AL( 1 );
      quest.setBitFlag8( 1, true );
      checkQuestCompletion( quest, player );
      eventMgr().eventFinish( player, result.eventId, 1 );
      warpMgr().requestMoveTerritory( player, Common::WarpType::WARP_TYPE_NORMAL, teriMgr().getTerritoryByTypeId( 181 )->getGuId(), { 9.0f, 40.0f, 14.0f }, 0.0f );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00007( World::Quest& quest, Entity::Player& player )
  {
    //playerMgr().sendDebug( player, "ManSea001:65643 calling Scene00007: Normal(None), id=unknown" );
    eventMgr().playQuestScene( player, getId(), 7, NONE, bindSceneReturn( &ManSea001::Scene00007Return ) );
  }

  void Scene00007Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00009( World::Quest& quest, Entity::Player& player )
  {
    //playerMgr().sendDebug( player, "ManSea001:65643 calling Scene00009: Normal(None), id=unknown" );
    eventMgr().playQuestScene( player, getId(), 9, NONE, bindSceneReturn( &ManSea001::Scene00009Return ) );
  }

  void Scene00009Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00011( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 11, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &ManSea001::Scene00011Return ) );
  }

  void Scene00011Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    Scene00012( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00012( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 12, HIDE_HOTBAR, bindSceneReturn( &ManSea001::Scene00012Return ) );
  }

  void Scene00012Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
    }

  }

  //////////////////////////////////////////////////////////////////////

  void Scene00013( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 13, HIDE_HOTBAR, bindSceneReturn( &ManSea001::Scene00013Return ) );
  }

  void Scene00013Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if ( result.getResult( 0 ) == 1 )
    {
      eventMgr().eventFinish( player, result.eventId, 1 );
      warpMgr().requestMoveTerritory( player, Common::WarpType::WARP_TYPE_NORMAL, teriMgr().getTerritoryByTypeId( 181 )->getGuId(), { 9.0f, 40.0f, 14.0f }, 0.0f );
    }
  }

};

EXPOSE_SCRIPT( ManSea001 );