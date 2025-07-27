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

// Quest Script: SubFst033_00127
// Quest Name: Parasite Cleave
// Quest ID: 65663
// Start NPC: 1000461
// End NPC: 1000461

using namespace Sapphire;

class SubFst033 : public Sapphire::ScriptAPI::QuestScript
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
  // UI8DL

  /// Countable Num: 3 Seq: 1 Event: 1 Listener: 2000016
  /// Countable Num: 1 Seq: 255 Event: 8 Listener: 2000016
  // Steps in this quest ( 0 is before accepting,
  // 1 is first, 255 means ready for turning it in
  enum Sequence : uint8_t
  {
    Seq0 = 0,
    Seq1 = 1,
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1000461;//Gabineaux
  static constexpr auto Enemy0 = 2114368;
  static constexpr auto Enemy1 = 2114369;
  static constexpr auto Enemy2 = 2114370;
  static constexpr auto Eobject0 = 2000016;//Decaying Tree (West)
  static constexpr auto Eobject1 = 2000017;//Decaying Tree (South)
  static constexpr auto Eobject2 = 2000018;//Decaying Tree (East)
  static constexpr auto Item0 = 2000061;
  static constexpr auto Item0Icon = 20661;
  static constexpr auto Seq0Actor0 = 0;
  static constexpr auto Seq1Eobject0 = 1;
  static constexpr auto Seq1Eobject0Useitemno = 99;
  static constexpr auto Seq1Eobject0Useitemok = 100;
  static constexpr auto Seq1Eobject1 = 2;
  static constexpr auto Seq1Eobject1Useitemno = 97;
  static constexpr auto Seq1Eobject1Useitemok = 98;
  static constexpr auto Seq1Eobject2 = 3;
  static constexpr auto Seq1Eobject2Useitemno = 95;
  static constexpr auto Seq1Eobject2Useitemok = 96;
  static constexpr auto Seq2Actor0 = 4;

public:
  SubFst033() : Sapphire::ScriptAPI::QuestScript( 65663 ){};
  ~SubFst033() = default;

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
        if( quest.getSeq() == Seq1 )
          Scene00001( quest, player );
        break;
      }
      case Eobject1:
      {
        if( quest.getSeq() == Seq1 )
          Scene00002( quest, player );
        break;
      }
      case Eobject2:
      {
        if( quest.getSeq() == Seq1 )
          Scene00003( quest, player );
        break;
      }
    }
  }

  void onEventItem(World::Quest& quest, Entity::Player& player, uint64_t actorId) override {
    if( quest.getSeq() != Seq1 ) return;

    switch( actorId )
    {
      case Eobject0:
      {
        Scene00100( quest, player );
        break;
      }
      case Eobject1:
      {
        Scene00098( quest, player );
        break;
      }
      case Eobject2:
      {
        Scene00096( quest, player );
        break;
      }
    }
  }

  void onBNpcKill( World::Quest& quest, Sapphire::Entity::BNpc& bnpc, Sapphire::Entity::Player& player ) override
  {
    switch( bnpc.getLayoutId() )
    {
      case Enemy0:
      {
        quest.setUI8AH( quest.getUI8AH() + 1 );
        quest.setUI8AL( 1 );
        checkQuestCompletion( quest, player );
        break;
      }
      case Enemy1:
      {
        quest.setUI8AH( quest.getUI8AH() + 1 );
        quest.setUI8BL( 1 );
        checkQuestCompletion( quest, player );
        break;
      }
      case Enemy2:
      {
        quest.setUI8AH( quest.getUI8AH() + 1 );
        quest.setUI8CL( 1 );
        checkQuestCompletion( quest, player );
        break;
      }
    }
  }

  void onPlayerDeath(World::Quest& quest, Sapphire::Entity::Player& player) override
  {
    auto instance = teriMgr().getTerritoryByGuId( player.getTerritoryId() );

    auto enem0 = instance->getActiveBNpcByLayoutIdAndTriggerOwner( Enemy0, player.getId() );
    auto enem1 = instance->getActiveBNpcByLayoutIdAndTriggerOwner( Enemy1, player.getId() );
    auto enem2 = instance->getActiveBNpcByLayoutIdAndTriggerOwner( Enemy2, player.getId() );

    if (enem0 != nullptr)
    {
      instance->removeActor( enem0 );
      quest.setBitFlag8( 1, false );
    }
    if( enem1 != nullptr )
    {
      instance->removeActor( enem1 );
      quest.setBitFlag8( 2, false );
    }
    if( enem2 != nullptr )
    {
      instance->removeActor( enem2 );
      quest.setBitFlag8( 3, false );
    }
  }

private:
  void checkQuestCompletion( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().sendNotice( player, getId(), 0, { quest.getUI8AH(), 3, Item0Icon } );

    if( quest.getUI8AH() >= 3 )
    {
      quest.setSeq( SeqFinish );
      quest.setUI8AH( 0 );
      quest.setUI8AL( 0 );
      quest.setUI8BH( 0 );
      quest.setUI8BL( 0 );
      quest.setUI8CH( 0 );
      quest.setUI8CL( 0 );
      quest.setUI8DH( 0 );
      quest.setBitFlag8( 1, false );
      quest.setBitFlag8( 2, false );
      quest.setBitFlag8( 3, false );
    }
  }
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, NONE, bindSceneReturn( &SubFst033::Scene00000Return ) );
  }

  void Scene00000Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )// accept quest
    {
      quest.setUI8DL( 1 );
      quest.setSeq( Seq1 );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00001( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 1, NONE, bindSceneReturn( &SubFst033::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, NONE, bindSceneReturn( &SubFst033::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, NONE, bindSceneReturn( &SubFst033::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, NONE, bindSceneReturn( &SubFst033::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult(1) );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00095( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 95, NONE, bindSceneReturn( &SubFst033::Scene00095Return ) );
  }

  void Scene00095Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00096( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 96, NONE, bindSceneReturn( &SubFst033::Scene00096Return ) );
  }

  void Scene00096Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    auto instance = teriMgr().getTerritoryByGuId( player.getTerritoryId() );
    auto enemy = instance->createBNpcFromLayoutId( Enemy2, 1220 /*Find the right value*/, Common::BNpcType::Enemy, player.getId() );
    enemy->hateListAdd( player.getAsPlayer(), 1 );

    quest.setBitFlag8( 3, true );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00097( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 97, NONE, bindSceneReturn( &SubFst033::Scene00097Return ) );
  }

  void Scene00097Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00098( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 98, NONE, bindSceneReturn( &SubFst033::Scene00098Return ) );
  }

  void Scene00098Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    auto instance = teriMgr().getTerritoryByGuId( player.getTerritoryId() );
    auto enemy = instance->createBNpcFromLayoutId( Enemy1, 1220 /*Find the right value*/, Common::BNpcType::Enemy, player.getId() );
    enemy->hateListAdd( player.getAsPlayer(), 1 );

    quest.setBitFlag8( 2, true );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00099( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 99, NONE, bindSceneReturn( &SubFst033::Scene00099Return ) );
  }

  void Scene00099Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00100( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 100, NONE, bindSceneReturn( &SubFst033::Scene00100Return ) );
  }

  void Scene00100Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    auto instance = teriMgr().getTerritoryByGuId( player.getTerritoryId() );
    auto enemy = instance->createBNpcFromLayoutId( Enemy0, 1220 /*Find the right value*/, Common::BNpcType::Enemy, player.getId() );
    enemy->hateListAdd( player.getAsPlayer(), 1 );

    quest.setBitFlag8( 1, true );
  }
};

EXPOSE_SCRIPT( SubFst033 );