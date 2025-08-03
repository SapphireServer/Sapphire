// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include "Manager/PlayerMgr.h"
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: GaiUsa209_00732
// Quest Name: Stash Saboteur
// Quest ID: 66268
// Start NPC: 1000598 (Auphiliot)
// End NPC: 1000598 (Auphiliot)

using namespace Sapphire;

class GaiUsa209 : public Sapphire::ScriptAPI::QuestScript
{
  private:
    // Basic quest information 
    // Quest vars / flags used
    // BitFlag8
    // UI8AH
    // UI8AL
    // UI8BH
    // UI8BL
    // UI8CH

    /// Countable Num: 0 Seq: 1 Event: 1 Listener: 2001942
    /// Countable Num: 0 Seq: 255 Event: 8 Listener: 2001942
    // Steps in this quest ( 0 is before accepting, 
    // 1 is first, 255 means ready for turning it in
    enum Sequence : uint8_t
    {
      Seq0 = 0,
      Seq1 = 1,
      SeqFinish = 255,
    };

    // Entities found in the script data of the quest
    static constexpr auto Actor0 = 1000598; // Auphiliot ( Pos: -170.809998 9.964130 -84.129402  Teri: 153 )
    static constexpr Common::QuestEobject Eobject0 = { 2001942, 153, { -287.321014, 24.902500, -194.147995 }, 1.000000 }; // Storage Case
    static constexpr Common::QuestEobject Eobject1 = { 2001943, 153, { -294.333008, 24.268900, -207.630997 }, 1.000000 }; // Storage Case
    static constexpr Common::QuestEobject Eobject2 = { 2001944, 153, { -294.175995, 25.021999, -194.072006 }, 1.000000 }; // Storage Case
    static constexpr auto Item0 = 2000586;

  public:
    GaiUsa209() : Sapphire::ScriptAPI::QuestScript( 66268 ){}; 
    ~GaiUsa209() = default; 

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
        if( quest.getSeq() == SeqFinish )
          Scene00008( quest, player );
        break;
      }
    }
  }

  void onEventGroundItem( World::Quest& quest, Entity::Player& player, Common::FFXIVARR_POSITION3 pos ) override
  {
    uint8_t hitTargets = 0;
    if( !quest.getBitFlag8( 1 ) && eventMgr().checkHitEobject( player, pos, Eobject0 ) )
    {
      Scene00003( quest, player );
    }

    if( !quest.getBitFlag8( 2 ) && eventMgr().checkHitEobject( player, pos, Eobject1 ) )
    {
      Scene00005( quest, player );
    }

    if( !quest.getBitFlag8( 3 ) && eventMgr().checkHitEobject( player, pos, Eobject2 ) )
    {
      Scene00007( quest, player );
    }
  }

  private:

  void checkProgress( World::Quest& quest, Entity::Player& player )
  {
    uint8_t hitTargets = 0;
    if( quest.getBitFlag8( 1 ) )
      hitTargets++;
    if( quest.getBitFlag8( 2 ) )
      hitTargets++;
    if( quest.getBitFlag8( 3 ) )
      hitTargets++;

    eventMgr().sendEventNotice( player, getId(), 0, 2, hitTargets, 3 );
    quest.setUI8CH( 3 - hitTargets );
    quest.setUI8AH( hitTargets );

    if( hitTargets == 3 )
    {
      quest.setUI8AH( 0 );
      quest.setUI8AL( 0 );
      quest.setUI8BH( 0 );
      quest.setUI8BL( 0 );
      quest.setUI8CH( 0 );
      quest.setBitFlag8( 1, false );
      quest.setBitFlag8( 2, false );
      quest.setBitFlag8( 3, false );
      quest.setSeq( SeqFinish );
    }
  }

  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &GaiUsa209::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, NONE, bindSceneReturn( &GaiUsa209::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( Seq1 );
    quest.setUI8CH( 3 );

    quest.setUI8AL( 0 );
    quest.setUI8BH( 0 );
    quest.setUI8BL( 0 );
    quest.setBitFlag8( 1, false );
    quest.setBitFlag8( 2, false );
    quest.setBitFlag8( 3, false );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, NONE, bindSceneReturn( &GaiUsa209::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, HIDE_HOTBAR, bindSceneReturn( &GaiUsa209::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8AL( 1 );
    quest.setBitFlag8( 1, true );
    checkProgress( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, HIDE_HOTBAR, bindSceneReturn( &GaiUsa209::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, HIDE_HOTBAR, bindSceneReturn( &GaiUsa209::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8BH( 1 );
    quest.setBitFlag8( 2, true );
    checkProgress( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00006( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 6, NONE, bindSceneReturn( &GaiUsa209::Scene00006Return ) );
  }

  void Scene00006Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00007( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 7, NONE, bindSceneReturn( &GaiUsa209::Scene00007Return ) );
  }

  void Scene00007Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8BL( 1 );
    quest.setBitFlag8( 3, true );
    checkProgress( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00008( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 8, NONE, bindSceneReturn( &GaiUsa209::Scene00008Return ) );
  }

  void Scene00008Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
    }

  }

};

EXPOSE_SCRIPT( GaiUsa209 );