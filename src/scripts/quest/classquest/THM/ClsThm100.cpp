// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include "Actor/BNpc.h"
#include "Manager/EventMgr.h"
#include <Actor/Player.h>
#include <ScriptObject.h>
#include <Service.h>

#include "Territory/Territory.h"

// Quest Script: ClsThm100_00348
// Quest Name: The Threat of Paucity
// Quest ID: 65884
// Start NPC: 1001708 (Cocobuki)
// End NPC: 1001708 (Cocobuki)

using namespace Sapphire;

class ClsThm100 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // BitFlag8
  // UI8AH
  // UI8AL
  // UI8BH
  // UI8BL

  /// Countable Num: 1 Seq: 1 Event: 1 Listener: 1001710
  /// Countable Num: 1 Seq: 2 Event: 5 Listener: 160
  /// Countable Num: 1 Seq: 3 Event: 1 Listener: 1001710
  /// Countable Num: 5 Seq: 4 Event: 1 Listener: 2001511
  /// Countable Num: 1 Seq: 5 Event: 9 Listener: 166
  /// Countable Num: 1 Seq: 6 Event: 9 Listener: 1238
  /// Countable Num: 0 Seq: 255 Event: 1 Listener: 2001759
  // Steps in this quest ( 0 is before accepting,
  // 1 is first, 255 means ready for turning it in
  enum Sequence : uint8_t
  {
    Seq0 = 0,
    Seq1 = 1,
    Seq2 = 2,
    Seq3 = 3,
    Seq4 = 4,
    Seq5 = 5,
    Seq6 = 6,
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto actorCocobuki = 1001708;// Cocobuki ( Pos: -250.347000 18.000000 80.903603  Teri: 130 )
  static constexpr auto actorCocobani = 1001710;// Cocobani ( Pos: -240.251007 18.799999 86.916702  Teri: 130 )
  static constexpr auto Actor20 = 1001713;      // Cocobusi
  static constexpr auto enemyEft = 289;         // Eft teri ( Pos: 75 0 1  Teri: 141 )
  static constexpr auto Enemy1 = 4074126;       //
  static constexpr auto Enemy2 = 4184413;       //
  static constexpr auto Eobject0 = 2001511;     // Armored War Transport ( Pos: -366 -35 290  Teri: 145 )
  static constexpr auto Eobject1 = 2001759;     // ?????
  static constexpr auto Eobject2 = 2001498;     // Armored War Transport ( Pos: -366.277008 -34.983299 293.579987  Teri: 145 )
  static constexpr auto EventActionSearch = 1;
  static constexpr auto Item0 = 2000417;
  static constexpr auto Item1 = 2000416;
  static constexpr auto ItemIcon = 22601;
  static constexpr auto Item2Icon = 21003;
  static constexpr auto UnlockImageClassCange = 22;
  static constexpr auto UnlockImageGearSet = 29;

public:
  ClsThm100() : Sapphire::ScriptAPI::QuestScript( 65884 ){};
  ~ClsThm100() = default;

  //////////////////////////////////////////////////////////////////////
  // Event Handlers
  void onTalk( World::Quest& quest, Entity::Player& player, uint64_t actorId ) override
  {
    switch( actorId )
    {
      case actorCocobuki:
      {
        if( quest.getSeq() == Seq0 )
        {
          Scene00000( quest, player );
        }
        break;
      }
      case actorCocobani:
      {
        if( quest.getSeq() == Seq1 )
        {
          Scene00001( quest, player );
        }
        if( quest.getSeq() == Seq3 )
        {
          Scene00002( quest, player );
        }
        if( quest.getSeq() == Seq6 )
        {
          Scene00011( quest, player );
        }
        break;
      }
      case Eobject0:
      {
        eventMgr().eventActionStart(
                player, getId(), EventActionSearch,
                [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                  Scene00004( quest, player );
                },
                nullptr, 0 );
        break;
      }
      case Eobject2:
      {
        eventMgr().eventActionStart(
                player, getId(), EventActionSearch,
                [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                  Scene00006( quest, player );
                },
                nullptr, 0 );
        break;
      }
      case Actor20:
      {
        break;
      }
    }
  }

  void onEventItem( World::Quest& quest, Entity::Player& player, uint64_t actorId ) override
  {
  }

  void onBNpcKill( World::Quest& quest, Entity::BNpc& bnpc, Entity::Player& player ) override
  {
    // UI8AH
    // UI8AL
    // UI8BH
    // UI8BL
    //
    //    quest.setUI8AH( 0 );//completes obtain blood something..
    //    playerMgr().sendDebug( player, "UI8AH: {}", quest.getUI8AH() );
    //
    //    quest.setUI8AL( 0 );//not sure
    //    playerMgr().sendDebug( player, "UI8AL: {}", quest.getUI8AL() );
    //
    //    quest.setUI8BH( 0 );//gives 2 ether when set to 1
    //    playerMgr().sendDebug( player, "UI8BH: {}", quest.getUI8BH() );
    //
    //    quest.setUI8BL( 0 );//not sure
    //    playerMgr().sendDebug( player, "UI8BL: {}", quest.getUI8BL() );
    //
    //    quest.setSeq( Seq4 );
    //    quest.setBitFlag8( 1, false );

    switch( bnpc.getBNpcNameId() )
    {
      case enemyEft:
      {
        if( quest.getSeq() == Seq2 )
        {
          if( quest.getUI8AL() < 8 )
          {
            quest.setUI8AL( quest.getUI8AL() + 1 );
            eventMgr().sendNotice( player, getId(), 1, { quest.getUI8AL(), 8 } );
          }
          if( quest.getUI8AL() >= 8 )
          {
            quest.setSeq( Seq3 );
            quest.setUI8AL( 0 );
          }
        }
        break;
      }
    }

    switch( bnpc.getLayoutId() )
    {
      case Enemy1:
      case Enemy2:
        playerMgr().sendDebug( player, "UI8AH: {}", quest.getUI8AH() );
        playerMgr().sendDebug( player, "UI8AL: {}", quest.getUI8AL() );
        playerMgr().sendDebug( player, "UI8BH: {}", quest.getUI8BH() );
        playerMgr().sendDebug( player, "UI8BL: {}", quest.getUI8BL() );
        quest.setUI8BL( quest.getUI8BL() + 1 );
        if( quest.getUI8BL() >= 2 )
        {
          quest.setBitFlag8( 1, false );
          eventMgr().sendNotice( player, getId(), 3, { ItemIcon } );
          quest.setUI8AH( 1 );
          quest.setUI8BH( 2 );
          quest.setSeq( Seq5 );
          quest.setUI8AH( 0 );
          quest.setUI8BH( 0 );
        }
        break;
    }
  }

  void onPlayerDeath( World::Quest& quest, Sapphire::Entity::Player& player ) override
  {
    if( quest.getSeq() == Seq4 )
    {
      auto instance = teriMgr().getTerritoryByGuId( player.getTerritoryId() );

      auto enemy = instance->getActiveBNpcByLayoutIdAndTriggerOwner( Enemy1, player.getId() );

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
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &ClsThm100::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, HIDE_HOTBAR, bindSceneReturn( &ClsThm100::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendNotice( player, getId(), 0 );
    quest.setSeq( Seq2 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, HIDE_HOTBAR, bindSceneReturn( &ClsThm100::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendNotice( player, getId(), 2 );
    quest.setSeq( Seq4 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, HIDE_HOTBAR, bindSceneReturn( &ClsThm100::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, HIDE_HOTBAR, bindSceneReturn( &ClsThm100::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setBitFlag8( 1, true );//removes the location
    //sense hostile presence
    auto instance = teriMgr().getTerritoryByGuId( player.getTerritoryId() );
    auto enemy0 = instance->createBNpcFromLayoutId( Enemy1, 120, Common::BNpcType::Enemy, player.getId() );
    auto enemy1 = instance->createBNpcFromLayoutId( Enemy2, 120, Common::BNpcType::Enemy, player.getId() );
    enemy0->setTriggerOwnerId( player.getId() );
    enemy1->setTriggerOwnerId( player.getId() );
    enemy0->hateListAddDelayed( player.getAsPlayer(), 1 );
    enemy1->hateListAddDelayed( player.getAsPlayer(), 1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, NONE, bindSceneReturn( &ClsThm100::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00006( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 6, HIDE_HOTBAR, bindSceneReturn( &ClsThm100::Scene00006Return ) );
  }

  void Scene00006Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8BH( 1 );
    quest.setSeq( Seq6 );
    eventMgr().sendNotice( player, getId(), 4, { Item2Icon } );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00007( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 7, HIDE_HOTBAR, bindSceneReturn( &ClsThm100::Scene00007Return ) );
  }

  void Scene00007Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00008( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 8, HIDE_HOTBAR, bindSceneReturn( &ClsThm100::Scene00008Return ) );
  }

  void Scene00008Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00009( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 9, HIDE_HOTBAR, bindSceneReturn( &ClsThm100::Scene00009Return ) );
  }

  void Scene00009Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00010( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 10, HIDE_HOTBAR, bindSceneReturn( &ClsThm100::Scene00010Return ) );
  }

  void Scene00010Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00011( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 11, HIDE_HOTBAR, bindSceneReturn( &ClsThm100::Scene00011Return ) );
  }

  void Scene00011Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
    {
      Scene00012( quest, player );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00012( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 12, FADE_OUT | HIDE_UI | INVIS_ALL | SET_INVIS_BASE, bindSceneReturn( &ClsThm100::Scene00012Return ) );
  }

  void Scene00012Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    //remove key items?
    Scene00016( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00013( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 13, HIDE_HOTBAR, bindSceneReturn( &ClsThm100::Scene00013Return ) );
  }

  void Scene00013Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00014( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 14, HIDE_HOTBAR, bindSceneReturn( &ClsThm100::Scene00014Return ) );
  }

  void Scene00014Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00015( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 15, HIDE_HOTBAR, bindSceneReturn( &ClsThm100::Scene00015Return ) );
  }

  void Scene00015Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00016( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 16, HIDE_HOTBAR, bindSceneReturn( &ClsThm100::Scene00016Return ) );
  }


  void Scene00016Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
    }
  }
};

EXPOSE_SCRIPT( ClsThm100 );