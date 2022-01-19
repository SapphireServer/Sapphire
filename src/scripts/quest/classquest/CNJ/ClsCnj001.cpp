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

// Quest Script: ClsCnj001_00048
// Quest Name: Trial by Earth
// Quest ID: 65584
// Start NPC: 1000692
// End NPC: 1000692

using namespace Sapphire;

class ClsCnj001 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // BitFlag8
  // UI8AL
  // UI8BH

  /// Countable Num: 1 Seq: 1 Event: 1 Listener: 1000764
  /// Countable Num: 1 Seq: 2 Event: 1 Listener: 2000883
  /// Countable Num: 1 Seq: 3 Event: 5 Listener: 294
  /// Countable Num: 1 Seq: 255 Event: 1 Listener: 1000764
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
  static constexpr auto Actor0 = 1000692;  //E-Sumi-Yan
  static constexpr auto Actor1 = 1000764;  //Nolanel
  static constexpr auto Enemy0 = 2320919;  //Tainted Earth Sprite
  static constexpr auto Eobject0 = 2000883;//Corrupted Soil
  static constexpr auto EventActionSearch = 1;
  static constexpr auto NqPoint001 = 4;
  static constexpr auto Seq0Actor0 = 0;
  static constexpr auto Seq1Actor1 = 1;
  static constexpr auto Seq2Eobject0 = 2;
  static constexpr auto Seq2Eobject0Eventactionno = 99;
  static constexpr auto Seq2Eobject0Eventactionok = 100;
  static constexpr auto Seq3Actor1 = 3;
  static constexpr auto Seq4Actor0 = 4;

public:
  ClsCnj001() : Sapphire::ScriptAPI::QuestScript( 65584 ){};
  ~ClsCnj001() = default;

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
      case Actor1:
      {
        if( quest.getSeq() == Seq1 )
          Scene00001( quest, player );
        else if( quest.getSeq() == Seq3 )
          Scene00003( quest, player );
        break;
      }
      case Eobject0:
      {
        if( quest.getSeq() == Seq2 )
          Scene00100( quest, player );
      }
    }
  }

  void onBNpcKill( World::Quest& quest, uint16_t nameId, uint32_t entityId, Sapphire::Entity::Player& player ) override
  {
    switch( entityId )
    {
      case Enemy0:
      {
        quest.setBitFlag8( 1, false );
        eventMgr().sendEventNotice( player, getId(), 1, 0 );
        quest.setSeq( Seq3 );
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
    eventMgr().playQuestScene( player, getId(), 0, NONE, bindSceneReturn( &ClsCnj001::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, HIDE_HOTBAR, bindSceneReturn( &ClsCnj001::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( Seq2 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, NONE, bindSceneReturn( &ClsCnj001::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &ClsCnj001::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( SeqFinish );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, NONE, bindSceneReturn( &ClsCnj001::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00099( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 99, NONE, bindSceneReturn( &ClsCnj001::Scene00099Return ) );
  }

  void Scene00099Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00100( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 100, NONE, bindSceneReturn( &ClsCnj001::Scene00100Return ) );
  }

  void Scene00100Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    auto teriMgr = Common::Service< Sapphire::World::Manager::TerritoryMgr >::ref();
    auto instance = teriMgr.getTerritoryByGuId( player.getTerritoryId() );
    auto enemy = instance->createBNpcFromInstanceId( Enemy0, 1220 /*Find the right value*/, Common::BNpcType::Enemy );
    enemy->hateListAdd( player.getAsPlayer(), 1 );

    quest.setBitFlag8( 1, true );
  }
};

EXPOSE_SCRIPT( ClsCnj001 );