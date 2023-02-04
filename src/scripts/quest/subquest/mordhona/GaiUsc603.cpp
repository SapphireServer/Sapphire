// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include "Manager/EventMgr.h"
#include <Actor/Player.h>
#include <ScriptObject.h>
#include <Service.h>

#include <Actor/BNpc.h>

// Quest Script: GaiUsc603_01003
// Quest Name: Dressed for Conquest
// Quest ID: 66539
// Start NPC: 1006552
// End NPC: 1006552

using namespace Sapphire;

class GaiUsc603 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // BitFlag8
  // UI8AL
  // UI8BH
  // UI8BL
  // UI8CH

  /// Countable Num: 0 Seq: 1 Event: 9 Listener: 64
  /// Countable Num: 0 Seq: 1 Event: 9 Listener: 63
  /// Countable Num: 0 Seq: 2 Event: 9 Listener: 62
  /// Countable Num: 0 Seq: 3 Event: 9 Listener: 55
  /// Countable Num: 0 Seq: 3 Event: 9 Listener: 61
  /// Countable Num: 0 Seq: 255 Event: 1 Listener: 1006552
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
  static constexpr auto Actor0 = 1006552;//Sark Malark
  static constexpr auto Actor1 = 1001685;//Aethelwine
  static constexpr auto Actor2 = 1001000;
  static constexpr auto Enemy0 = 64;//5th Cohort Signifer
  static constexpr auto Enemy1 = 63;//5th Cohort Secutor
  static constexpr auto Enemy2 = 62;//5th Cohort Eques
  static constexpr auto Enemy3 = 55;//5th Cohort Hoplomachus
  static constexpr auto Enemy4 = 61;//5th Cohort Laquearius
  static constexpr auto Item0 = 2000767;
  static constexpr auto Item1 = 2000768;
  static constexpr auto Item2 = 2000769;
  static constexpr auto Item3 = 2000770;
  static constexpr auto LocActor1 = 1001682;
  static constexpr auto LocActor2 = 1001013;
  static constexpr auto LocPosActor1 = 4308329;
  static constexpr auto LocPosActor2 = 2367980;

public:
  GaiUsc603() : Sapphire::ScriptAPI::QuestScript( 66539 ){};
  ~GaiUsc603() = default;

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
          Scene00002( quest, player );
        else if( quest.getSeq() == SeqFinish )
          Scene00008( quest, player );
        break;
      }
      case Actor1:
      {
        if( quest.getSeq() == Seq3 )
          Scene00004( quest, player );
        break;
      }
      case Actor2:
      {
        if( quest.getSeq() == Seq3 )
          Scene00006( quest, player );
        break;
      }
    }
  }

  void onBNpcKill( World::Quest& quest, Entity::BNpc& bnpc, Entity::Player& player ) override
  {
    switch( bnpc.getBNpcBaseId() )
    {
      case Enemy0:
      case Enemy1:
      case Enemy2:
      {
        quest.setUI8BL( quest.getUI8BL() + 1 );
        eventMgr().sendEventNotice( player, getId(), 0, 2, quest.getUI8BL(), 3 );
        checkQuestCompletion( quest, player );
        break;
      }
      case Enemy3:
      case Enemy4:
      {
        quest.setUI8CH( quest.getUI8CH() + 1 );
        eventMgr().sendEventNotice( player, getId(), 1, 2, quest.getUI8CH(), 3 );
        checkQuestCompletion( quest, player );
        break;
      }
    }
  }

private:
  void checkQuestCompletion( World::Quest& quest, Entity::Player& player, bool secondSeqCheck = false )
  {
    if( !secondSeqCheck )
    {
      if( quest.getUI8CH() >= 3 && quest.getUI8BL() >= 3 )
      {
        quest.setUI8BH( 3 );
        quest.setUI8BL( 3 );
        quest.setUI8AH( 0 );
        quest.setSeq( Seq2 );
      }
    }
    else
    {
      if( quest.getUI8AL() > 0 && quest.getUI8BH() > 0 )
      {
        quest.setSeq( SeqFinish );
        quest.setUI8BH( 3 );
        quest.setUI8BL( 3 );
        quest.setUI8AL( 0 );
        quest.setUI8AH( 0 );
      }
    }
  }
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &GaiUsc603::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, HIDE_HOTBAR, bindSceneReturn( &GaiUsc603::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( Seq1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, HIDE_HOTBAR, bindSceneReturn( &GaiUsc603::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      Scene00003( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, HIDE_HOTBAR, bindSceneReturn( &GaiUsc603::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 2, 0 );
    quest.setSeq( Seq3 );
    quest.setUI8AL( 0 );
    quest.setUI8BH( 0 );
    quest.setUI8BL( 3 );
    quest.setUI8CH( 3 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, HIDE_HOTBAR, bindSceneReturn( &GaiUsc603::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      Scene00005( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &GaiUsc603::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8AL( 1 );
    eventMgr().sendEventNotice( player, getId(), 3, 0 );
    checkQuestCompletion( quest, player, true );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00006( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 6, HIDE_HOTBAR, bindSceneReturn( &GaiUsc603::Scene00006Return ) );
  }

  void Scene00006Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      Scene00007( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00007( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 7, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &GaiUsc603::Scene00007Return ) );
  }

  void Scene00007Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8BH( 1 );
    eventMgr().sendEventNotice( player, getId(), 4, 0 );
    checkQuestCompletion( quest, player, true );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00008( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 8, HIDE_HOTBAR, bindSceneReturn( &GaiUsc603::Scene00008Return ) );
  }

  void Scene00008Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      Scene00009( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00009( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 9, HIDE_HOTBAR, bindSceneReturn( &GaiUsc603::Scene00009Return ) );
  }

  void Scene00009Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId() );
    }
  }
};

EXPOSE_SCRIPT( GaiUsc603 );