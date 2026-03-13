// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include "Actor/BNpc.h"
#include "Manager/EventMgr.h"
#include <Actor/Player.h>
#include <ScriptObject.h>
#include <Service.h>

#include "Territory/Territory.h"

// Quest Script: ClsThm050_00347
// Quest Name: The Threat of Intimacy
// Quest ID: 65883
// Start NPC: 1001708 (Cocobuki)
// End NPC: 1001709 (Cocobygo)

using namespace Sapphire;

class ClsThm050 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // BitFlag8 - removes the wait destination
  // UI8AL - is everything completed?
  // UI8BH - #dried fish
  // UI8BL - #vulture meat

  /// Countable Num: 1 Seq: 1 Event: 1 Listener: 1001709
  /// Countable Num: 1 Seq: 2 Event: 1 Listener: 2001468
  /// Countable Num: 1 Seq: 3 Event: 8 Listener: 2001468
  /// Countable Num: 1 Seq: 4 Event: 1 Listener: 2001469
  /// Countable Num: 1 Seq: 255 Event: 9 Listener: 12
  // Steps in this quest ( 0 is before accepting,
  // 1 is first, 255 means ready for turning it in
  enum Sequence : uint8_t
  {
    Seq0 = 0,
    Seq1 = 1,//speak with cocobygo
    Seq2 = 2,//place dried fish
    Seq3 = 3,//wait for chance to slay vulture
    Seq4 = 4,//hand slice of vulture meat
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto ActorCocobuki = 1001708;// Cocobuki ( Pos: -250.347000 18.000000 80.903603  Teri: 130 )
  static constexpr auto ActorCocobygo = 1001709;// Cocobygo ( Pos: -240.473999 18.700001 85.611702  Teri: 130 )
  static constexpr auto ActorFafafono = 1002027;// Fafafono ( Pos: -255.229004 33.233601 407.295013  Teri: 140 )
  static constexpr auto ActorCocobusi = 1001713;// Cocobusi
  static constexpr auto CutClsthm05010 = 50;
  static constexpr auto enemyCirclingVulture = 4002289;  //
  static constexpr auto fishDestinationEObject = 2001468;// Destination ( Pos: -87.371597 50.629902 315.605011  Teri: 140 )
  static constexpr auto waitDestinationEObject = 2001469;// Destination ( Pos: -74.943199 53.255798 336.807007  Teri: 140 )
  static constexpr auto EventActionSearch = 1;
  static constexpr auto EventActionWaitingShor = 11;
  static constexpr auto Item0 = 2000414;
  static constexpr auto Item1 = 2000415;
  static constexpr auto Item0Icon = 25919;
  static constexpr auto Item1Icon = 25151;

public:
  ClsThm050() : Sapphire::ScriptAPI::QuestScript( 65883 ){};
  ~ClsThm050() = default;

  //////////////////////////////////////////////////////////////////////
  // Event Handlers
  void onTalk( World::Quest& quest, Entity::Player& player, uint64_t actorId ) override
  {
    switch( actorId )
    {
      case ActorCocobuki:
      {
        if( quest.getSeq() == Seq0 )
        {
          Scene00000( quest, player );
        }
        break;
      }
      case ActorCocobygo:
      {
        if( quest.getSeq() == Seq1 )
        {
          Scene00001( quest, player );
        }
        else if( quest.getSeq() == SeqFinish )
        {
          Scene00010( quest, player );
        }

        break;
      }
      case fishDestinationEObject:
      {
        Scene00002( quest, player );
        break;
      }
      case waitDestinationEObject:
      {
        if( quest.getSeq() == Seq3 )
        {
          eventMgr().eventActionStart(
                  player, getId(), EventActionWaitingShor,
                  [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                    quest.setSeq( Seq3 );
                    Scene00005( quest, player );
                  },
                  nullptr, 0 );
        }
        break;
      }
      case ActorFafafono:
      {
        if( quest.getSeq() == Seq4 )
        {
          Scene00008( quest, player );
        }
        break;
      }
      case ActorCocobusi:
      {
        break;
      }
    }
  }

  void onEventItem( World::Quest& quest, Entity::Player& player, uint64_t actorId ) override
  {
    if( actorId == fishDestinationEObject )
    {
      eventMgr().sendEventNotice( player, getId(), 1 );
      quest.setUI8BH( 0 );
      quest.setSeq( Seq3 );
    }
  }

  void onBNpcKill( World::Quest& quest, Entity::BNpc& bnpc, Entity::Player& player ) override
  {

    switch( bnpc.getLayoutId() )
    {
      case enemyCirclingVulture:
      {
        quest.setSeq( Seq4 );
        quest.setUI8BL( 1 );
        eventMgr().sendNotice( player, getId(), 2, { Item1Icon } );//wait for chance to slay with item icon
        break;
      }
    }
  }

  void onPlayerDeath( World::Quest& quest, Sapphire::Entity::Player& player ) override
  {
    if( quest.getSeq() == Seq3 )
    {
      auto instance = teriMgr().getTerritoryByGuId( player.getTerritoryId() );

      auto enemy = instance->getActiveBNpcByLayoutIdAndTriggerOwner( enemyCirclingVulture, player.getId() );

      if( enemy != nullptr ) instance->removeActor( enemy );

      quest.setBitFlag8( 1, false );
    }
  }

private:
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &ClsThm050::Scene00000Return ) );
  }

  void Scene00000Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )// accept quest
    {
      quest.setSeq( Seq1 );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00001( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 1, HIDE_HOTBAR, bindSceneReturn( &ClsThm050::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 0 );
    quest.setSeq( Seq2 );
    quest.setUI8BH( 1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, HIDE_HOTBAR, bindSceneReturn( &ClsThm050::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
    {
      eventMgr().eventItemActionStart(
              player, getId(), Item0,
              quest.getSeq(), fishDestinationEObject );
    }
  }

  //////////////////////////////////////////////////////////////////////

  // does nothing
  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, NONE, bindSceneReturn( &ClsThm050::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  // does nothing
  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, HIDE_HOTBAR, bindSceneReturn( &ClsThm050::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, HIDE_HOTBAR, bindSceneReturn( &ClsThm050::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setBitFlag8( 1, true );//removes the location
    auto instance = teriMgr().getTerritoryByGuId( player.getTerritoryId() );
    auto enemy = instance->createBNpcFromLayoutId( enemyCirclingVulture, 90, Common::BNpcType::Enemy, player.getId() );
    enemy->hateListAdd( player.getAsPlayer(), 1 );
  }

  //////////////////////////////////////////////////////////////////////
  //does nothing
  void Scene00006( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 6, NONE, bindSceneReturn( &ClsThm050::Scene00006Return ) );
  }

  void Scene00006Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////
  //does nothing
  void Scene00007( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 7, NONE, bindSceneReturn( &ClsThm050::Scene00007Return ) );
  }

  void Scene00007Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00008( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 8, HIDE_HOTBAR, bindSceneReturn( &ClsThm050::Scene00008Return ) );
  }

  void Scene00008Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
    {
      Scene00009( quest, player );
    }
    else
    {
      Scene00006( quest, player );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00009( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 9, FADE_OUT | HIDE_UI | SET_INVIS_BASE, bindSceneReturn( &ClsThm050::Scene00009Return ) );
  }

  void Scene00009Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( SeqFinish );
    quest.setUI8BL( 0 );
    quest.setUI8AL( 1 );
    eventMgr().sendEventNotice( player, getId(), 3 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00010( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 10, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI | SET_INVIS_BASE, bindSceneReturn( &ClsThm050::Scene00010Return ) );
  }

  void Scene00010Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    Scene00011( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00011( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 11, HIDE_HOTBAR, bindSceneReturn( &ClsThm050::Scene00011Return ) );
  }

  void Scene00011Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
    }
  }
};

EXPOSE_SCRIPT( ClsThm050 );