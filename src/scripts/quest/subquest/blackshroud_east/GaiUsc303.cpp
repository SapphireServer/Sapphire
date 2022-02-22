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

// Quest Script: GaiUsc303_00970
// Quest Name: Some Seedy Business
// Quest ID: 66506
// Start NPC: 1000617
// End NPC: 1006715

using namespace Sapphire;

class GaiUsc303 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // BitFlag8
  // UI8AH
  // UI8AL
  // UI8BH
  // UI8CH

  /// Countable Num: 0 Seq: 1 Event: 1 Listener: 1000587
  /// Countable Num: 0 Seq: 2 Event: 1 Listener: 2002190
  /// Countable Num: 0 Seq: 255 Event: 9 Listener: 762
  // Steps in this quest ( 0 is before accepting,
  // 1 is first, 255 means ready for turning it in
  enum Sequence : uint8_t
  {
    Seq0 = 0,
    Seq1 = 1,
    Seq2 = 2,
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1000617;//Jeulerand
  static constexpr auto Actor1 = 1000587;//Dellexia
  static constexpr auto Actor2 = 1006715;//Kain
  static constexpr auto Enemy0 = 4300392;
  static constexpr auto Enemy1 = 4300395;
  static constexpr auto Enemy2 = 4300397;
  static constexpr auto Eobject0 = 2002190;//Sylvan Lily Seed (Southern-most) 
  static constexpr auto Eobject1 = 2002191;//Sylvan Lily Seed (Center) 
  static constexpr auto Eobject2 = 2002192;//Sylvan Lily Seed (Northern-most) 
  static constexpr auto EventActionGatherShort = 6;
  static constexpr auto EventActionSearch = 1;
  static constexpr auto Item0 = 2000749;
  static constexpr auto Item1 = 2000750;

public:
  GaiUsc303() : Sapphire::ScriptAPI::QuestScript( 66506 ){};
  ~GaiUsc303() = default;

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
          Scene00002( quest, player );
        break;
      }
      case Actor2:
      {
        if( quest.getSeq() == SeqFinish )
          Scene00010( quest, player );
        break;
      }
      case Eobject0:
      {
        eventMgr().eventActionStart(
                player, getId(), 0x02,
                [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                  Scene00005( quest, player );
                },
                nullptr, 0 );
        break;
      }
      case Eobject1:
      {
        eventMgr().eventActionStart(
                player, getId(), 0x02,
                [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                  Scene00007( quest, player );
                },
                nullptr, 0 );
        break;
      }
      case Eobject2:
      {
        eventMgr().eventActionStart(
                player, getId(), 0x02,
                [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                  Scene00009( quest, player );
                },
                nullptr, 0 );
        break;
      }
    }
  }

  void onEventItem( World::Quest& quest, Entity::Player& player, uint64_t actorId ) override
  {
  }

  void onBNpcKill( World::Quest& quest, uint16_t nameId, uint32_t entityId, Entity::Player& player ) override
  {
    switch( entityId )
    {
      case Enemy0:
      {
        break;
      }
      case Enemy1:
      {
        break;
      }
      case Enemy2:
      {
        break;
      }
    }
  }

private:
  void checkQuestCompletion( World::Quest& quest, Entity::Player& player )
  {
    if( quest.getUI8AH() >= 3 && quest.getUI8CH() >= 3 )
    {
      quest.setUI8BH( 3 );
      quest.setSeq( SeqFinish );
    }
  }
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &GaiUsc303::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, HIDE_HOTBAR, bindSceneReturn( &GaiUsc303::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( Seq1 );
    quest.setUI8BH( 1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, NONE, bindSceneReturn( &GaiUsc303::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult(0) == 1 )
      Scene00003(quest, player);
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, NONE, bindSceneReturn( &GaiUsc303::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( Seq2 );
    eventMgr().sendEventNotice( player, getId(), 0, 0 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, NONE, bindSceneReturn( &GaiUsc303::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, NONE, bindSceneReturn( &GaiUsc303::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8AH( quest.getUI8AH() + 1 );
    quest.setUI8CH( quest.getUI8CH() + 1 );
    eventMgr().sendEventNotice( player, getId(), 1, 2, quest.getUI8AH(), 3 );
    quest.setBitFlag8( 1, true );
    if( quest.getUI8CH() < 3 )
    {
      auto instance = teriMgr().getTerritoryByGuId( player.getTerritoryId() );
      auto enemy0 = instance->createBNpcFromLayoutId( Enemy0, 413 /*TODO: Find the right value*/, Common::BNpcType::Enemy );
      enemy0->setTriggerOwnerId( player.getId() );
      enemy0->hateListAddDelayed( player.getAsPlayer(), 1 );
    }
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00006( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 6, NONE, bindSceneReturn( &GaiUsc303::Scene00006Return ) );
  }

  void Scene00006Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00007( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 7, NONE, bindSceneReturn( &GaiUsc303::Scene00007Return ) );
  }

  void Scene00007Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8AH( quest.getUI8AH() + 1 );
    quest.setUI8CH( quest.getUI8CH() + 1 );
    eventMgr().sendEventNotice( player, getId(), 1, 2, quest.getUI8AH(), 3 );
    quest.setBitFlag8( 2, true );
    if( quest.getUI8CH() < 3 )
    {
      auto instance = teriMgr().getTerritoryByGuId( player.getTerritoryId() );
      auto enemy1 = instance->createBNpcFromLayoutId( Enemy1, 413 /*TODO: Find the right value*/, Common::BNpcType::Enemy );
      enemy1->setTriggerOwnerId( player.getId() );
      enemy1->hateListAddDelayed( player.getAsPlayer(), 1 );
    }
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00008( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 8, NONE, bindSceneReturn( &GaiUsc303::Scene00008Return ) );
  }

  void Scene00008Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00009( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 9, NONE, bindSceneReturn( &GaiUsc303::Scene00009Return ) );
  }

  void Scene00009Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8AH( quest.getUI8AH() + 1 );
    quest.setUI8CH( quest.getUI8CH() + 1 );
    eventMgr().sendEventNotice( player, getId(), 1, 2, quest.getUI8AH(), 3 );
    quest.setBitFlag8( 3, true );
    if( quest.getUI8CH() < 3 )
    {
      auto instance = teriMgr().getTerritoryByGuId( player.getTerritoryId() );
      auto enemy2 = instance->createBNpcFromLayoutId( Enemy2, 413 /*TODO: Find the right value*/, Common::BNpcType::Enemy );
      enemy2->setTriggerOwnerId( player.getId() );
      enemy2->hateListAddDelayed( player.getAsPlayer(), 1 );
    }
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00010( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 10, NONE, bindSceneReturn( &GaiUsc303::Scene00010Return ) );
  }

  void Scene00010Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      Scene00011( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00011( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 11, NONE, bindSceneReturn( &GaiUsc303::Scene00011Return ) );
  }

  void Scene00011Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult(1) );
    }
  }
};

EXPOSE_SCRIPT( GaiUsc303 );