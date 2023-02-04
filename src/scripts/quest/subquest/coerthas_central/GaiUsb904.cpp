// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include "Manager/EventMgr.h"
#include <Actor/Player.h>
#include <Actor/BNpc.h>
#include <ScriptObject.h>
#include <Service.h>

#include "Actor/BNpc.h"
#include "Manager/TerritoryMgr.h"
#include "Territory/Territory.h"

// Quest Script: GaiUsb904_00927
// Quest Name: Factual Folklore
// Quest ID: 66463
// Start NPC: 1006448
// End NPC: 1007567

using namespace Sapphire;

class GaiUsb904 : public Sapphire::ScriptAPI::QuestScript
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

  /// Countable Num: 0 Seq: 1 Event: 1 Listener: 2002158
  /// Countable Num: 0 Seq: 2 Event: 9 Listener: 2196
  /// Countable Num: 0 Seq: 3 Event: 8 Listener: 2196
  /// Countable Num: 0 Seq: 4 Event: 1 Listener: 1006448
  /// Countable Num: 0 Seq: 255 Event: 1 Listener: 1006449
  // Steps in this quest ( 0 is before accepting,
  // 1 is first, 255 means ready for turning it in
  enum Sequence : uint8_t
  {
    Seq0 = 0,
    Seq1 = 1,
    Seq2 = 2,
    Seq3 = 3,
    Seq4 = 4,
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1006448;//Haustefort
  static constexpr auto Actor1 = 1006449;//Ombeline
  static constexpr auto Actor2 = 1006450;//Theophilain
  static constexpr auto Actor3 = 1006451;//Ignemortel
  static constexpr auto Actor4 = 1007567;//Cenota
  static constexpr auto Enemy0 = 4293214;
  static constexpr auto Enemy1 = 2196;
  static constexpr auto Eobject0 = 2002158;//Destination
  static constexpr auto EventActionSearch = 1;
  static constexpr auto Item0 = 2000961;
  static constexpr auto Item1 = 2000724;
  static constexpr auto Item2 = 2000725;
  static constexpr auto Item3 = 2000984;

public:
  GaiUsb904() : Sapphire::ScriptAPI::QuestScript( 66463 ){};
  ~GaiUsb904() = default;

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
          Scene00004( quest, player );
        else if( quest.getSeq() == Seq4 )
          Scene00012( quest, player );
        break;
      }
      case Actor1:
      {
        if( quest.getSeq() == Seq3 )
          Scene00006( quest, player );
        break;
      }
      case Actor2:
      {
        if( quest.getSeq() == Seq3 )
          Scene00008( quest, player );
        break;
      }
      case Actor3:
      {
        if( quest.getSeq() == Seq3 )
          Scene00010( quest, player );
        break;
      }
      case Actor4:
      {
        if( quest.getSeq() == SeqFinish )
          Scene00013( quest, player );
        break;
      }
      case Eobject0:
      {
        if( quest.getSeq() == Seq1 )
          eventMgr().eventActionStart(
                  player, getId(), EventActionSearch,
                  [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                    Scene00003( quest, player );
                  },
                  nullptr, 0 );
        break;
      }
    }
  }

  void onBNpcKill( World::Quest& quest, Entity::BNpc& bnpc, Entity::Player& player ) override
  {
    if( bnpc.getLayoutId() == Enemy0 )
    {
      eventMgr().sendEventNotice( player, getId(), 0, 0 );
      quest.setSeq( Seq2 );
      quest.setUI8BH( 1 );
    }
    else if( bnpc.getBNpcNameId() == Enemy1 )
    {
    }
  }

private:
  void checkQuestCompletion( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().sendEventNotice( player, getId(), 2, 2, quest.getUI8AH(), 3 );
    if(  quest.getUI8AH() >= 3 )
    {
      quest.setUI8AH( 0 );
      quest.setUI8AL( 0 );
      quest.setUI8BH( 0 );
      quest.setUI8BL( 0 );
      quest.setSeq( Seq4 );
    }
  }
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &GaiUsb904::Scene00000Return ) );
  }

  void Scene00000Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )// accept quest
    {
      Scene00001( quest, player );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00001( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 1, HIDE_HOTBAR, bindSceneReturn( &GaiUsb904::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( Seq1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, HIDE_HOTBAR, bindSceneReturn( &GaiUsb904::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, HIDE_HOTBAR, bindSceneReturn( &GaiUsb904::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    auto instance = teriMgr().getTerritoryByGuId( player.getTerritoryId() );

    auto enemySpawned = instance->getActiveBNpcByLayoutIdAndTriggerOwner( Enemy0, player.getId() );

    if( !enemySpawned )
    {
      auto enemy = instance->createBNpcFromLayoutId( Enemy0, 413 /*TODO: Find the right value*/, Common::BNpcType::Enemy, player.getId() );
      enemy->hateListAdd( player.getAsPlayer(), 1 );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, HIDE_HOTBAR, bindSceneReturn( &GaiUsb904::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      Scene00005( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, HIDE_HOTBAR, bindSceneReturn( &GaiUsb904::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 1, 0 );
    quest.setUI8BH( 0 );
    quest.setUI8CH( 3 );
    quest.setSeq( Seq3 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00006( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 6, HIDE_HOTBAR, bindSceneReturn( &GaiUsb904::Scene00006Return ) );
  }

  void Scene00006Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      Scene00007( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00007( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 7, HIDE_HOTBAR, bindSceneReturn( &GaiUsb904::Scene00007Return ) );
  }

  void Scene00007Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8AL( 1 );                   //Hide Quest Icon
    quest.setUI8AH( quest.getUI8AH() + 1 );//Increment Journal
    quest.setUI8CH( quest.getUI8CH() - 1 );//Decrement KeyItem
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00008( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 8, HIDE_HOTBAR, bindSceneReturn( &GaiUsb904::Scene00008Return ) );
  }

  void Scene00008Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      Scene00009( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00009( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 9, HIDE_HOTBAR, bindSceneReturn( &GaiUsb904::Scene00009Return ) );
  }

  void Scene00009Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8BH( 1 );                   //Hide Quest Icon
    quest.setUI8AH( quest.getUI8AH() + 1 );//Increment Journal
    quest.setUI8CH( quest.getUI8CH() - 1 );//Decrement KeyItem
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00010( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 10, HIDE_HOTBAR, bindSceneReturn( &GaiUsb904::Scene00010Return ) );
  }

  void Scene00010Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      Scene00011( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00011( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 11, HIDE_HOTBAR, bindSceneReturn( &GaiUsb904::Scene00011Return ) );
  }

  void Scene00011Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8BL( 1 );                   //Hide Quest Icon
    quest.setUI8AH( quest.getUI8AH() + 1 );//Increment Journal
    quest.setUI8CH( quest.getUI8CH() - 1 );//Decrement KeyItem
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00012( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 12, HIDE_HOTBAR, bindSceneReturn( &GaiUsb904::Scene00012Return ) );
  }

  void Scene00012Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8BH( 1 );
    eventMgr().sendEventNotice( player, getId(), 3, 0 );
    quest.setSeq( SeqFinish );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00013( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 13, HIDE_HOTBAR, bindSceneReturn( &GaiUsb904::Scene00013Return ) );
  }

  void Scene00013Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      Scene00014( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00014( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 14, HIDE_HOTBAR, bindSceneReturn( &GaiUsb904::Scene00014Return ) );
  }

  void Scene00014Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
    }
  }
};

EXPOSE_SCRIPT( GaiUsb904 );