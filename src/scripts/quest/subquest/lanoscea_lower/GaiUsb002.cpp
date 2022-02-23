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

// Quest Script: GaiUsb002_00809
// Quest Name: Tales from the Tidus Slayer
// Quest ID: 66345
// Start NPC: 1006264
// End NPC: 1006264

using namespace Sapphire;

class GaiUsb002 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // BitFlag8
  // UI8AL

  /// Countable Num: 0 Seq: 1 Event: 1 Listener: 2002033
  /// Countable Num: 0 Seq: 255 Event: 5 Listener: 2239
  // Steps in this quest ( 0 is before accepting,
  // 1 is first, 255 means ready for turning it in
  enum Sequence : uint8_t
  {
    Seq0 = 0,
    Seq1 = 1,
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1006264;//Trachtoum
  static constexpr auto Enemy0 = 4291274;
  static constexpr auto Enemy1 = 4291279;
  static constexpr auto Enemy2 = 4291283;
  static constexpr auto Enemy3 = 4291284;
  static constexpr auto Enemy4 = 4291285;
  static constexpr auto Eobject0 = 2002033;
  static constexpr auto EventActionSearch = 1;
  static constexpr auto LocBgm1 = 87;

public:
  GaiUsb002() : Sapphire::ScriptAPI::QuestScript( 66345 ){};
  ~GaiUsb002() = default;

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
          Scene00004( quest, player );
        break;
      }
      case Eobject0:
      {
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
    switch( bnpc.getLayoutId() )
    {
      case Enemy0:
      case Enemy1:
      case Enemy2:
      case Enemy3:
      case Enemy4:
      {
        quest.setUI8AL( quest.getUI8AL() + 1 );
        checkQuestCompletion( quest, player );
        break;
      }
    }
  }

private:
  void checkQuestCompletion( World::Quest& quest, Entity::Player& player )
  {
    if( quest.getUI8AL() == 4 )
    {
      auto instance = teriMgr().getTerritoryByGuId( player.getTerritoryId() );

      auto enemy4 = instance->createBNpcFromLayoutId( Enemy4, 413 /*TODO: Find the right value*/, Common::BNpcType::Enemy, player.getId() );

      enemy4->hateListAdd( player.getAsPlayer(), 1 );
    }
    else if( quest.getUI8AL() >= 5 )
    {
      eventMgr().sendEventNotice( player, getId(), 0, 0 );
      quest.setSeq( SeqFinish );
    }
  }
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &GaiUsb002::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &GaiUsb002::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( Seq1 );
    quest.setUI8AL( 0 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, HIDE_HOTBAR, bindSceneReturn( &GaiUsb002::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, HIDE_HOTBAR, bindSceneReturn( &GaiUsb002::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setBitFlag8( 1, true );

    auto instance = teriMgr().getTerritoryByGuId( player.getTerritoryId() );

    auto enemy0 = instance->createBNpcFromLayoutId( Enemy0, 413 /*TODO: Find the right value*/, Common::BNpcType::Enemy, player.getId() );
    auto enemy1 = instance->createBNpcFromLayoutId( Enemy1, 413 /*TODO: Find the right value*/, Common::BNpcType::Enemy, player.getId() );
    auto enemy2 = instance->createBNpcFromLayoutId( Enemy2, 413 /*TODO: Find the right value*/, Common::BNpcType::Enemy, player.getId() );
    auto enemy3 = instance->createBNpcFromLayoutId( Enemy3, 413 /*TODO: Find the right value*/, Common::BNpcType::Enemy, player.getId() );

    enemy0->hateListAdd( player.getAsPlayer(), 1 );
    enemy1->hateListAdd( player.getAsPlayer(), 1 );
    enemy2->hateListAdd( player.getAsPlayer(), 1 );
    enemy3->hateListAdd( player.getAsPlayer(), 1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, HIDE_HOTBAR, bindSceneReturn( &GaiUsb002::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
    }
  }
};

EXPOSE_SCRIPT( GaiUsb002 );