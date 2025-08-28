// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>
#include <Actor/BNpc.h>
#include "Manager/TerritoryMgr.h"

// Quest Script: ClsPgl050_00554
// Quest Name: Harder than Rock
// Quest ID: 66090
// Start NPC: 1003817 (Hamon)
// End NPC: 1003817 (Hamon)

using namespace Sapphire;

class ClsPgl050 : public Sapphire::ScriptAPI::QuestScript
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
    // UI8CL
    // UI8DH

    /// Countable Num: 5 Seq: 1 Event: 1 Listener: 2001280
    /// Countable Num: 1 Seq: 2 Event: 1 Listener: 2001281
    /// Countable Num: 5 Seq: 3 Event: 1 Listener: 2001282
    /// Countable Num: 5 Seq: 255 Event: 1 Listener: 2001283
    // Steps in this quest ( 0 is before accepting, 
    // 1 is first, 255 means ready for turning it in
    enum Sequence : uint8_t
    {
      Seq0 = 0,
      Seq1 = 1,
      Seq2 = 2,
      Seq3 = 3,
      SeqFinish = 255,
    };

    // Entities found in the script data of the quest
    static constexpr auto Action0 = 53;
    static constexpr auto Actor0 = 1003817; // Hamon ( Pos: -74.541298 1.999990 -42.379501  Teri: 130 )
    static constexpr auto CutClspgl05010 = 163;
    static constexpr auto Enemy0 = 4068746; // 
    static constexpr auto Enemy1 = 4068756; // 
    static constexpr auto Enemy2 = 4068761; // 
    static constexpr auto Enemy3 = 4068766; // 
    static constexpr auto Eobject0 = 2001280; // Faded Gil Coins ( Pos: -162.442993 17.486099 60.224800  Teri: 130 )
    static constexpr auto Eobject1 = 2001281; // Faded Gil Coins ( Pos: -254.727005 18.000000 67.353203  Teri: 130 )
    static constexpr auto Eobject2 = 2001282; // Faded Gil Coins ( Pos: -21.744101 10.018200 -78.477203  Teri: 130 )
    static constexpr auto Eobject3 = 2001283; // Faded Gil Coins ( Pos: 37.064098 7.249540 -98.893799  Teri: 130 )
    static constexpr auto Eobject4 = 2001285; // Faded Gil Coins ( Pos: -80.338799 0.700921 -59.525501  Teri: 130 )
    static constexpr auto Eobject5 = 2001541; // Trial Stone ( Pos: 224.740005 52.070400 79.478104  Teri: 140 )
    static constexpr auto Eobject6 = 2001542; // Trial Stone ( Pos: 245.742004 52.498501 58.100399  Teri: 140 )
    static constexpr auto Eobject7 = 2001543; // Trial Stone ( Pos: 224.026993 52.244701 41.381901  Teri: 140 )
    static constexpr auto Eobject8 = 2001544; // Trial Stone ( Pos: 259.056000 53.448101 25.430000  Teri: 140 )
    static constexpr auto EventActionSearch = 1;
    static constexpr auto Item0 = 2000423;

  public:
    ClsPgl050() : Sapphire::ScriptAPI::QuestScript( 66090 ){}; 
    ~ClsPgl050() = default; 

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
        else if( quest.getSeq() == Seq2 )
          Scene00011( quest, player );
        else if( quest.getSeq() == SeqFinish )
          Scene00021( quest, player );
        break;
      }
      case Eobject0:
      {
        eventMgr().eventActionStart(
                player, getId(), EventActionSearch,
                [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                  Scene00002( quest, player );
                },
                nullptr, getId() );
        break;
      }
      case Eobject1:
      {
        eventMgr().eventActionStart(
                player, getId(), EventActionSearch,
                [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                  Scene00004( quest, player );
                },
                nullptr, getId() );
        break;
      }
      case Eobject2:
      {
        eventMgr().eventActionStart(
                player, getId(), EventActionSearch,
                [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                  Scene00006( quest, player );
                },
                nullptr, getId() );
        break;
      }
      case Eobject3:
      {
        eventMgr().eventActionStart(
                player, getId(), EventActionSearch,
                [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                  Scene00008( quest, player );
                },
                nullptr, getId() );
        break;
      }
      case Eobject4:
      {
        eventMgr().eventActionStart(
                player, getId(), EventActionSearch,
                [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                  Scene00010( quest, player );
                },
                nullptr, getId() );
        break;
      }
      case Eobject5:
      {
        Scene00013( quest, player );
        break;
      }
      case Eobject6:
      {
        Scene00015( quest, player );
        break;
      }
      case Eobject7:
      {
        Scene00017( quest, player );
        break;
      }
      case Eobject8:
      {
        Scene00019( quest, player );
        break;
      }
    }
  }

  void onPlayerDeath( World::Quest& quest, Sapphire::Entity::Player& player ) override
  {
    if( quest.getSeq() != Seq3 )
      return;

    auto instance = teriMgr().getTerritoryByGuId( player.getTerritoryId() );

    if( !quest.getUI8AL() )
    {
      auto enemy = instance->getActiveBNpcByLayoutIdAndTriggerOwner( Enemy0, player.getId() );

      if( enemy != nullptr ) instance->removeActor( enemy );

      quest.setBitFlag8( 1, false );
    }
    if( !quest.getUI8BH() )
    {
      auto enemy = instance->getActiveBNpcByLayoutIdAndTriggerOwner( Enemy1, player.getId() );

      if( enemy != nullptr ) instance->removeActor( enemy );

      quest.setBitFlag8( 2, false );
    }
    if( !quest.getUI8BL() )
    {
      auto enemy = instance->getActiveBNpcByLayoutIdAndTriggerOwner( Enemy2, player.getId() );

      if( enemy != nullptr ) instance->removeActor( enemy );

      quest.setBitFlag8( 3, false );
    }
    if( !quest.getUI8CH() )
    {
      auto enemy = instance->getActiveBNpcByLayoutIdAndTriggerOwner( Enemy3, player.getId() );

      if( enemy != nullptr ) instance->removeActor( enemy );

      quest.setBitFlag8( 4, false );
    }
  }

  void onBNpcKill( World::Quest& quest, Entity::BNpc& bnpc, Entity::Player& player ) override
  {
    switch( bnpc.getLayoutId() )
    {
      case Enemy0:
      {
        quest.setUI8AL( 1 );
        checkCompletition( quest, player );
        break;
      }
      case Enemy1:
      {
        quest.setUI8BH( 1 );
        checkCompletition( quest, player );
        break;
      }
      case Enemy2:
      {
        quest.setUI8BL( 1 );
        checkCompletition( quest, player );
        break;
      }
      case Enemy3:
      {
        quest.setUI8CH( 1 );
        checkCompletition( quest, player );
        break;
      }
    }
  }

  void onEObjHit( World::Quest& quest, Sapphire::Entity::Player& player, uint64_t actorId, uint32_t actionId ) override
  {
    if( actionId != Action0 )
      return;

    eventMgr().eventStart( player, actorId, getId(), Event::EventHandler::Nest, 0, 0 );

    switch( actorId )
    {
      case Eobject5:
      {
        Scene00014( quest, player );
        break;
      }
      case Eobject6:
      {
        Scene00016( quest, player );
        break;
      }
      case Eobject7:
      {
        Scene00018( quest, player );
        break;
      }
      case Eobject8:
      {
        Scene00020( quest, player );
        break;
      }
    }
  }
  private:
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void checkCompletition(World::Quest& quest, Entity::Player& player)
  {
    if( quest.getSeq() == Seq1 )
    {
      quest.setUI8AH( quest.getUI8AH() + 1 );
      quest.setUI8DH( quest.getUI8DH() + 1 );
      eventMgr().sendNotice( player, getId(), 0, { player.getQuestItemIcon( Item0 ) } );

      if( quest.getUI8AH() >= 5 )
      {
        quest.setUI8AH( 0 );
        quest.setUI8AL( 0 );
        quest.setUI8BL( 0 );
        quest.setUI8BH( 5 );
        quest.setUI8CL( 0 );
        quest.setUI8DH( 0 );
        quest.setSeq( Seq2 );
      }
    }
    else if( quest.getSeq() == Seq3 )
    {
      quest.setUI8AH( quest.getUI8AH() + 1 );
      eventMgr().sendEventNotice( player, getId(), 2, 2, quest.getUI8AH(), 4 );

      if( quest.getUI8AH() >= 4 )
      {
        quest.setSeq( SeqFinish );
      }
    }
  }

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, NONE, bindSceneReturn( &ClsPgl050::Scene00000Return ) );
  }

  void Scene00000Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 ) // accept quest
    {
       quest.setSeq( Seq1 );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00001( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 1, NONE, bindSceneReturn( &ClsPgl050::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, AUTO_LOC_CAMERA, bindSceneReturn( &ClsPgl050::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8AL( 1 );
    checkCompletition( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, NONE, bindSceneReturn( &ClsPgl050::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, AUTO_LOC_CAMERA, bindSceneReturn( &ClsPgl050::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8BH( 1 );
    checkCompletition( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, NONE, bindSceneReturn( &ClsPgl050::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00006( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 6, AUTO_LOC_CAMERA, bindSceneReturn( &ClsPgl050::Scene00006Return ) );
  }

  void Scene00006Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8BL( 1 );
    checkCompletition( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00007( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 7, NONE, bindSceneReturn( &ClsPgl050::Scene00007Return ) );
  }

  void Scene00007Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00008( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 8, AUTO_LOC_CAMERA, bindSceneReturn( &ClsPgl050::Scene00008Return ) );
  }

  void Scene00008Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8CH( 1 );
    checkCompletition( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00009( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 9, NONE, bindSceneReturn( &ClsPgl050::Scene00009Return ) );
  }

  void Scene00009Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00010( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 10, AUTO_LOC_CAMERA, bindSceneReturn( &ClsPgl050::Scene00010Return ) );
  }

  void Scene00010Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8CL( 1 );
    checkCompletition( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00011( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 11, NONE, bindSceneReturn( &ClsPgl050::Scene00011Return ) );
  }

  void Scene00011Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult(0) == 1 )
    {
      Scene00012( quest, player );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00012( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 12, NONE, bindSceneReturn( &ClsPgl050::Scene00012Return ) );
  }

  void Scene00012Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 1, 0 );
    quest.setUI8BH( 0 );
    quest.setSeq( Seq3 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00013( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 13, NONE, bindSceneReturn( &ClsPgl050::Scene00013Return ) );
  }

  void Scene00013Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00014( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 14, NONE, bindSceneReturn( &ClsPgl050::Scene00014Return ) );
  }

  void Scene00014Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setBitFlag8( 1, true );

    auto instance = teriMgr().getTerritoryByGuId( player.getTerritoryId() );

    auto enemy = instance->createBNpcFromLayoutId( Enemy0, 1220 /*Find the right value*/, Common::BNpcType::Enemy, player.getId() );
    enemy->hateListAddDelayed( player.getAsPlayer(), 1 );

  }

  //////////////////////////////////////////////////////////////////////

  void Scene00015( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 15, NONE, bindSceneReturn( &ClsPgl050::Scene00015Return ) );
  }

  void Scene00015Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00016( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 16, NONE, bindSceneReturn( &ClsPgl050::Scene00016Return ) );
  }

  void Scene00016Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setBitFlag8( 2, true );

    auto instance = teriMgr().getTerritoryByGuId( player.getTerritoryId() );

    auto enemy = instance->createBNpcFromLayoutId( Enemy1, 1220 /*Find the right value*/, Common::BNpcType::Enemy, player.getId() );
    enemy->hateListAddDelayed( player.getAsPlayer(), 1 );

  }

  //////////////////////////////////////////////////////////////////////

  void Scene00017( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 17, NONE, bindSceneReturn( &ClsPgl050::Scene00017Return ) );
  }

  void Scene00017Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00018( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 18, NONE, bindSceneReturn( &ClsPgl050::Scene00018Return ) );
  }

  void Scene00018Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setBitFlag8( 3, true );

    auto instance = teriMgr().getTerritoryByGuId( player.getTerritoryId() );

    auto enemy = instance->createBNpcFromLayoutId( Enemy2, 1220 /*Find the right value*/, Common::BNpcType::Enemy, player.getId() );
    enemy->hateListAddDelayed( player.getAsPlayer(), 1 );

  }

  //////////////////////////////////////////////////////////////////////

  void Scene00019( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 19, NONE, bindSceneReturn( &ClsPgl050::Scene00019Return ) );
  }

  void Scene00019Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00020( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 20, NONE, bindSceneReturn( &ClsPgl050::Scene00020Return ) );
  }

  void Scene00020Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setBitFlag8( 4, true );

    auto instance = teriMgr().getTerritoryByGuId( player.getTerritoryId() );

    auto enemy = instance->createBNpcFromLayoutId( Enemy3, 1220 /*Find the right value*/, Common::BNpcType::Enemy, player.getId() );
    enemy->hateListAddDelayed( player.getAsPlayer(), 1 );

  }

  //////////////////////////////////////////////////////////////////////

  void Scene00021( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 21, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &ClsPgl050::Scene00021Return ) );
  }

  void Scene00021Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    Scene00022( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00022( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 22, NONE, bindSceneReturn( &ClsPgl050::Scene00022Return ) );
  }

  void Scene00022Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
    {
        player.finishQuest( getId(), result.getResult( 1 ) );
    }
  }

};

EXPOSE_SCRIPT( ClsPgl050 );