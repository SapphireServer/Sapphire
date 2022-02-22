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

// Quest Script: SubFst053_00159
// Quest Name: Lights Out
// Quest ID: 65695
// Start NPC: 1000503
// End NPC: 1000503

using namespace Sapphire;

class SubFst053 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // BitFlag8
  // UI8AL
  // UI8BH
  // UI8BL

  /// Countable Num: 0 Seq: 1 Event: 1 Listener: 2000042
  /// Countable Num: 1 Seq: 255 Event: 8 Listener: 2000042
  // Steps in this quest ( 0 is before accepting,
  // 1 is first, 255 means ready for turning it in
  enum Sequence : uint8_t
  {
    Seq0 = 0,
    Seq1 = 1,
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1000503;//Armelle
  static constexpr auto Enemy0 = 1943223;
  static constexpr auto Enemy1 = 1943224;
  static constexpr auto Enemy2 = 1943225;
  static constexpr auto Eobject0 = 2000042;//Destination (Seq1)
  static constexpr auto Item0 = 2000095;
  static constexpr auto Seq0Actor0 = 0;
  static constexpr auto Seq1Eobject0 = 1;
  static constexpr auto Seq1Eobject0Useitemno = 99;
  static constexpr auto Seq1Eobject0Useitemok = 100;
  static constexpr auto Seq2Actor0 = 2;

public:
  SubFst053() : Sapphire::ScriptAPI::QuestScript( 65695 ){};
  ~SubFst053() = default;

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
          Scene00002( quest, player );
        break;
      }
      case Eobject0:
      {
        if( quest.getSeq() == Seq1 )
          Scene00001( quest, player );
      }
    }
  }

  void onEventItem( World::Quest& quest, Entity::Player& player, uint64_t actorId ) override
  {
    if( actorId != Eobject0 )
      return;
    else
      Scene00100( quest, player );
  }

  void onBNpcKill( World::Quest& quest, uint16_t nameId, uint32_t entityId, Entity::Player& player ) override
  {
    switch( entityId )
    {
      case Enemy0:
      case Enemy1:
      case Enemy2:
      {
        quest.setUI8BH( quest.getUI8BH() + 1 );
        if( quest.getUI8BH() >= 3 )
        {
          eventMgr().sendEventNotice( player, getId(), 0, 0 );
          quest.setUI8BH( 0 );
          quest.setBitFlag8( 1, false );
          quest.setUI8BL( 0 );
          quest.setSeq( SeqFinish );
        }
        break;
      }
    }
  }

  void onTriggerOwnerDeaggro( World::Quest& quest, Sapphire::Entity::BNpc& bnpc, Sapphire::Entity::Player& player ) override
  {
    /* if( quest.getSeq() == Seq1 )
    {
      quest.setUI8BH( 0 );
      quest.setBitFlag8( 1, false );
    }*/
  }

private:
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &SubFst053::Scene00000Return ) );
  }

  void Scene00000Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )// accept quest
    {
      quest.setSeq( Seq1 );
      quest.setUI8BL( 1 );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00001( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 1, NONE, bindSceneReturn( &SubFst053::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    //Opens KeyItem Inventory
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, NONE, bindSceneReturn( &SubFst053::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00099( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 99, NONE, bindSceneReturn( &SubFst053::Scene00099Return ) );
  }

  void Scene00099Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00100( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 100, NONE, bindSceneReturn( &SubFst053::Scene00100Return ) );
  }

  void Scene00100Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setBitFlag8( 1, true );
    auto instance = teriMgr().getTerritoryByGuId( player.getTerritoryId() );
    auto enemy0 = instance->createBNpcFromLayoutId( Enemy0, 413 /*TODO: Find the right value*/, Common::BNpcType::Enemy );
    auto enemy1 = instance->createBNpcFromLayoutId( Enemy1, 413 /*TODO: Find the right value*/, Common::BNpcType::Enemy );
    auto enemy2 = instance->createBNpcFromLayoutId( Enemy2, 413 /*TODO: Find the right value*/, Common::BNpcType::Enemy );
    enemy0->setTriggerOwnerId( player.getId() );
    enemy1->setTriggerOwnerId( player.getId() );
    enemy2->setTriggerOwnerId( player.getId() );
    enemy0->hateListAddDelayed( player.getAsPlayer(), 1 );
    enemy1->hateListAddDelayed( player.getAsPlayer(), 1 );
    enemy2->hateListAddDelayed( player.getAsPlayer(), 1 );
  }
};

EXPOSE_SCRIPT( SubFst053 );