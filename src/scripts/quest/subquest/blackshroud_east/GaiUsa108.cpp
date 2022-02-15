// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include "Manager/EventMgr.h"
#include <Actor/Player.h>
#include <ScriptObject.h>
#include <Service.h>

#include "Actor/BNpc.h"
#include "Manager/TerritoryMgr.h"
#include "Territory/Territory.h"

// Quest Script: GaiUsa108_00722
// Quest Name: A Porcine Plight
// Quest ID: 66258
// Start NPC: 1000563
// End NPC: 1000563

using namespace Sapphire;

class GaiUsa108 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // BitFlag8
  // UI8AL
  // UI8BH

  /// Countable Num: 0 Seq: 1 Event: 1 Listener: 2001920
  /// Countable Num: 0 Seq: 1 Event: 5 Listener: 15
  /// Countable Num: 0 Seq: 255 Event: 5 Listener: 15
  // Steps in this quest ( 0 is before accepting,
  // 1 is first, 255 means ready for turning it in
  enum Sequence : uint8_t
  {
    Seq0 = 0,
    Seq1 = 1,
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1000563;//Ameexia
  static constexpr auto Enemy0 = 4278237;
  static constexpr auto Enemy1 = 4278233;
  static constexpr auto Enemy2 = 4278251;
  static constexpr auto Eobject0 = 2001920;//Suspicious Thicket (South)
  static constexpr auto Eobject1 = 2001921;//Suspicious Thicket (North)
  static constexpr auto EventActionSearch = 1;

public:
  GaiUsa108() : Sapphire::ScriptAPI::QuestScript( 66258 ){};
  ~GaiUsa108() = default;

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
          Scene00006( quest, player );
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
      case Eobject1:
      {
        eventMgr().eventActionStart(
                player, getId(), EventActionSearch,
                [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                  Scene00005( quest, player );
                },
                nullptr, 0 );
        break;
      }
    }
  }

  void onBNpcKill( World::Quest& quest, uint16_t nameId, uint32_t entityId, Entity::Player& player ) override
  {
    switch( entityId )
    {
      case Enemy0:
      case Enemy1:
      {
        quest.setUI8AL( quest.getUI8AL() + 1 );
        checkQuestCompletion( quest, player );
        break;
      }
      case Enemy2:
      {
        quest.setUI8BH( 1 );
        eventMgr().sendEventNotice( player, getId(), 1, 0 );
        checkQuestCompletion( quest, player );
        break;
      }
    }
  }

private:
  void checkQuestCompletion( World::Quest& quest, Entity::Player& player )
  {
    if( quest.getUI8AL() >= 2 && quest.getUI8BH() >= 3 )
    {
      quest.setSeq( SeqFinish );
    }
    else if( quest.getUI8AL() == 2 )
    {
      eventMgr().sendEventNotice( player, getId(), 0, 0 );
    }
  }
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, NONE, bindSceneReturn( &GaiUsa108::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, NONE, bindSceneReturn( &GaiUsa108::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    quest.setSeq( Seq1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, NONE, bindSceneReturn( &GaiUsa108::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, NONE, bindSceneReturn( &GaiUsa108::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setBitFlag8( 1, true );
    auto instance = teriMgr().getTerritoryByGuId( player.getTerritoryId() );
    auto enemy0 = instance->createBNpcFromInstanceId( Enemy0, 413 /*TODO: Find the right value*/, Common::BNpcType::Enemy, player.getId() );
    auto enemy1 = instance->createBNpcFromInstanceId( Enemy1, 413 /*TODO: Find the right value*/, Common::BNpcType::Enemy, player.getId() );
    enemy0->hateListAddDelayed( player.getAsPlayer(), 1 );
    enemy1->hateListAddDelayed( player.getAsPlayer(), 1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, NONE, bindSceneReturn( &GaiUsa108::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, NONE, bindSceneReturn( &GaiUsa108::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setBitFlag8( 2, true );
    auto instance = teriMgr().getTerritoryByGuId( player.getTerritoryId() );
    auto enemy2 = instance->createBNpcFromInstanceId( Enemy2, 413 /*TODO: Find the right value*/, Common::BNpcType::Enemy, player.getId() );
    enemy2->hateListAddDelayed( player.getAsPlayer(), 1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00006( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 6, NONE, bindSceneReturn( &GaiUsa108::Scene00006Return ) );
  }

  void Scene00006Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
    }
  }
};

EXPOSE_SCRIPT( GaiUsa108 );