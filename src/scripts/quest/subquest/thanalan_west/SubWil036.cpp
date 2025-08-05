// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>
#include <Actor/BNpc.h>

#include "Manager/TerritoryMgr.h"
#include "Territory/Territory.h"

// Quest Script: SubWil036_00228
// Quest Name: Getting Your Bearings
// Quest ID: 65764
// Start NPC: 1002030 (Danyell)
// End NPC: 1002044 (Galfridus)

using namespace Sapphire;

class SubWil036 : public Sapphire::ScriptAPI::QuestScript
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

    /// Countable Num: 3 Seq: 1 Event: 10 Listener: 5000000
    /// Countable Num: 1 Seq: 255 Event: 1 Listener: 2001276
    // Steps in this quest ( 0 is before accepting, 
    // 1 is first, 255 means ready for turning it in
    enum Sequence : uint8_t
    {
      Seq0 = 0,
      Seq1 = 1,
      SeqFinish = 255,
    };

    // Entities found in the script data of the quest
    static constexpr auto Actor0 = 1002030; // Danyell ( Pos: -296.290985 16.936100 334.173004  Teri: 140 )
    static constexpr auto Actor1 = 1002044; // Galfridus ( Pos: -253.479996 33.229099 409.988007  Teri: 140 )
    static constexpr auto Enemy0 = 3923955; // 
    static constexpr auto Enemy1 = 3949791; // 
    static constexpr auto Enemy2 = 3949797; // 
    static constexpr auto Eobject0 = 2001276; // Magnetite ( Pos: -162.860001 49.869099 312.337006  Teri: 140 )
    static constexpr auto Eobject1 = 2001356; // Magnetite ( Pos: -118.516998 56.229401 411.123993  Teri: 140 )
    static constexpr auto Eobject2 = 2001357; // Magnetite ( Pos: -99.895302 59.123901 389.091003  Teri: 140 )
    static constexpr auto Eventrange0 = 4084925;
    static constexpr auto Eventrange1 = 4084894;
    static constexpr auto Eventrange2 = 4084766;
    static constexpr auto EventActionSearch = 1;
    static constexpr auto Item0 = 2000153;

  public:
    SubWil036() : Sapphire::ScriptAPI::QuestScript( 65764 ){}; 
    ~SubWil036() = default; 

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
          Scene00011( quest, player );
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
      case Eobject1:
      {
        eventMgr().eventActionStart(
                player, getId(), EventActionSearch,
                [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                  Scene00007( quest, player );
                },
                nullptr, 0 );
        break;
      }
      case Eobject2:
      {
        eventMgr().eventActionStart(
                player, getId(), EventActionSearch,
                [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                  Scene00010( quest, player );
                },
                nullptr, 0 );
        break;
      }
    }
  }

  void onWithinRange( World::Quest& quest, Entity::Player& player, uint32_t eventId, uint32_t param1, float x, float y, float z )
  {
    switch( param1 )
    {
      case( Eventrange0 ):
      {
        if( quest.getUI8AL() == 0 )
          Scene00002( quest, player );
        break;
      }
      case( Eventrange1 ):
      {
        if( quest.getUI8BH() == 0 )
          Scene00005( quest, player );
        break;
      }
      case( Eventrange2 ):
      {
        if( quest.getUI8BL() == 0 )
          Scene00008( quest, player );
        break;
      }
    }
  }

  void onBNpcKill( World::Quest& quest, Entity::BNpc& bnpc, Entity::Player& player ) override
  {
    switch( bnpc.getLayoutId() )
    {
      case Enemy0:
      {
        quest.setUI8AL( 1 );
        break;
      }
      case Enemy1:
      {
        quest.setUI8BH( 1 );
        break;
      }
      case Enemy2:
      {
        quest.setUI8BL( 1 );
        break;
      }
    }
  }

  private:
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void checkCompletition( World::Quest& quest, Entity::Player& player )
  {
    quest.setUI8AH( quest.getUI8AH() + 1 );
    quest.setUI8CH( quest.getUI8CH() + 1 );
    eventMgr().sendNotice( player, getId(), 0, { quest.getUI8AH(), 3, player.getQuestItemIcon( Item0 ) } );

    if( quest.getUI8AH() >= 3 )
    {
      quest.setSeq( SeqFinish );
      quest.setUI8BH( 3 );
    }
  }

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, NONE, bindSceneReturn( &SubWil036::Scene00000Return ) );
  }

  void Scene00000Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 ) // accept quest
    {
      quest.setSeq( Seq1 );
      Scene00001( quest, player );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00001( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 1, NONE, bindSceneReturn( &SubWil036::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, NONE, bindSceneReturn( &SubWil036::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    auto instance = teriMgr().getTerritoryByGuId( player.getTerritoryId() );
    auto enemy = instance->createBNpcFromLayoutId( Enemy0, 150 /*TODO: Find the right value*/, Common::BNpcType::Enemy, player.getId() );
    enemy->hateListAdd( player.getAsChara(), 10000 );
    enemy->aggro( player.getAsChara() );
    Scene00003( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, NONE, bindSceneReturn( &SubWil036::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, NONE, bindSceneReturn( &SubWil036::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setBitFlag8( 1, true );
    checkCompletition( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, NONE, bindSceneReturn( &SubWil036::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    auto instance = teriMgr().getTerritoryByGuId( player.getTerritoryId() );
    auto enemy = instance->createBNpcFromLayoutId( Enemy1, 150 /*TODO: Find the right value*/, Common::BNpcType::Enemy, player.getId() );
    enemy->hateListAdd( player.getAsChara(), 10000 );
    enemy->aggro( player.getAsChara() );
    Scene00006( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00006( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 6, NONE, bindSceneReturn( &SubWil036::Scene00006Return ) );
  }

  void Scene00006Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

  }

  //////////////////////////////////////////////////////////////////////

  void Scene00007( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 7, NONE, bindSceneReturn( &SubWil036::Scene00007Return ) );
  }

  void Scene00007Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setBitFlag8( 2, true );
    checkCompletition( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00008( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 8, NONE, bindSceneReturn( &SubWil036::Scene00008Return ) );
  }

  void Scene00008Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    auto instance = teriMgr().getTerritoryByGuId( player.getTerritoryId() );
    auto enemy = instance->createBNpcFromLayoutId( Enemy2, 150 /*TODO: Find the right value*/, Common::BNpcType::Enemy, player.getId() );
    enemy->hateListAdd( player.getAsChara(), 10000 );
    enemy->aggro( player.getAsChara() );
    Scene00009( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00009( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 9, NONE, bindSceneReturn( &SubWil036::Scene00009Return ) );
  }

  void Scene00009Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

  }

  //////////////////////////////////////////////////////////////////////

  void Scene00010( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 10, NONE, bindSceneReturn( &SubWil036::Scene00010Return ) );
  }

  void Scene00010Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setBitFlag8( 3, true );
    checkCompletition( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00011( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 11, NONE, bindSceneReturn( &SubWil036::Scene00011Return ) );
  }

  void Scene00011Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      Scene00012( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00012( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 12, NONE, bindSceneReturn( &SubWil036::Scene00012Return ) );
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
    eventMgr().playQuestScene( player, getId(), 13, NONE, bindSceneReturn( &SubWil036::Scene00013Return ) );
  }

  void Scene00013Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

  }
};

EXPOSE_SCRIPT( SubWil036 );