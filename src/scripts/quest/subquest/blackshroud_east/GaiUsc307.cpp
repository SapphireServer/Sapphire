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

// Quest Script: GaiUsc307_00974
// Quest Name: Crazy Enough to Work
// Quest ID: 66510
// Start NPC: 1006716
// End NPC: 1006710

using namespace Sapphire;

class GaiUsc307 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // BitFlag8
  // UI8AL
  // UI8BH
  // UI8BL

  /// Countable Num: 0 Seq: 1 Event: 1 Listener: 2002193
  /// Countable Num: 0 Seq: 2 Event: 9 Listener: 1893
  /// Countable Num: 0 Seq: 3 Event: 1 Listener: 2002194
  /// Countable Num: 0 Seq: 4 Event: 8 Listener: 2002194
  /// Countable Num: 0 Seq: 255 Event: 1 Listener: 1006686
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
  static constexpr auto Actor0 = 1006716;//Maerwynn
  static constexpr auto Actor1 = 1006686;//Tiggy (Seq2/Seq3)
  static constexpr auto Actor2 = 1006710;//Hedyn
  static constexpr auto Enemy0 = 4300660;
  static constexpr auto Enemy1 = 4300668;
  static constexpr auto Eobject0 = 2002193;//Destination (Seq1)
  static constexpr auto Eobject1 = 2002194;//Amberscale Rock
  static constexpr auto Eobject2 = 2002195;//Destination (Seq4)
  static constexpr auto EventActionSearch = 1;
  static constexpr auto EventActionWaitingShor = 11;
  static constexpr auto Item0 = 2000930;
  static constexpr auto Item1 = 2000752;
  static constexpr auto Item2 = 2000932;

public:
  GaiUsc307() : Sapphire::ScriptAPI::QuestScript( 66510 ){};
  ~GaiUsc307() = default;

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
        if( quest.getSeq() == Seq2 )
          Scene00006( quest, player );
        else if( quest.getSeq() == Seq3 )
          Scene00007( quest, player );
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
                player, getId(), EventActionWaitingShor,
                [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                  Scene00003( quest, player );
                },
                nullptr, 0 );
        break;
      }
      case Eobject1:
      {
        Scene00004( quest, player );
        break;
      }
      case Eobject2:
      {
        Scene00008( quest, player );
        break;
      }
    }
  }

  void onEventItem( World::Quest& quest, Entity::Player& player, uint64_t actorId ) override
  {
    if( actorId == Eobject1 )
      Scene00005( quest, player );
    else if( actorId == Eobject2 )
      Scene00009( quest, player );
  }

  void onBNpcKill( World::Quest& quest, Entity::BNpc& bnpc, Entity::Player& player ) override
  {
    switch( bnpc.getLayoutId() )
    {
      case Enemy0:
      {
        quest.setUI8BL( 1 );
        quest.setSeq( Seq2 );
        eventMgr().sendEventNotice( player, getId(), 0, 0 );
        quest.setBitFlag8( 1, false );
        break;
      }
      case Enemy1:
      {
        quest.setSeq( SeqFinish );
        eventMgr().sendEventNotice( player, getId(), 3, 0 );
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
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &GaiUsc307::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, HIDE_HOTBAR, bindSceneReturn( &GaiUsc307::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( Seq1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, HIDE_HOTBAR, bindSceneReturn( &GaiUsc307::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, HIDE_HOTBAR, bindSceneReturn( &GaiUsc307::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setBitFlag8( 1, true );
    auto instance = teriMgr().getTerritoryByGuId( player.getTerritoryId() );
    auto enemy = instance->createBNpcFromLayoutId( Enemy0, 1220 /*Find the right value*/, Common::BNpcType::Enemy, player.getId() );
    enemy->hateListAddDelayed( player.getAsPlayer(), 1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, HIDE_HOTBAR, bindSceneReturn( &GaiUsc307::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, HIDE_HOTBAR, bindSceneReturn( &GaiUsc307::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( Seq3 );
    eventMgr().sendEventNotice( player, getId(), 1, 0 );
    quest.setUI8BH( 1 );
    quest.setUI8BL( 0 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00006( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 6, HIDE_HOTBAR, bindSceneReturn( &GaiUsc307::Scene00006Return ) );
  }

  void Scene00006Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00007( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 7, HIDE_HOTBAR, bindSceneReturn( &GaiUsc307::Scene00007Return ) );
  }

  void Scene00007Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( Seq4 );
    eventMgr().sendEventNotice( player, getId(), 2, 0 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00008( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 8, HIDE_HOTBAR, bindSceneReturn( &GaiUsc307::Scene00008Return ) );
  }

  void Scene00008Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00009( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 9, HIDE_HOTBAR, bindSceneReturn( &GaiUsc307::Scene00009Return ) );
  }

  void Scene00009Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setBitFlag8( 1, true );
    auto instance = teriMgr().getTerritoryByGuId( player.getTerritoryId() );
    auto enemy = instance->createBNpcFromLayoutId( Enemy1, 1220 /*Find the right value*/, Common::BNpcType::Enemy, player.getId() );
    enemy->hateListAddDelayed( player.getAsPlayer(), 1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00010( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 10, HIDE_HOTBAR, bindSceneReturn( &GaiUsc307::Scene00010Return ) );
  }

  void Scene00010Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      Scene00011( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00011( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 11, HIDE_HOTBAR, bindSceneReturn( &GaiUsc307::Scene00011Return ) );
  }

  void Scene00011Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId() );
    }
  }
};

EXPOSE_SCRIPT( GaiUsc307 );