// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include "Manager/EventMgr.h"
#include <Actor/Player.h>
#include <Actor/BNpc.h>
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: GaiUsa302_00734
// Quest Name: Microbrewing
// Quest ID: 66270
// Start NPC: 1006193
// End NPC: 1006193

using namespace Sapphire;

class GaiUsa302 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // BitFlag8
  // UI8AL
  // UI8BH
  // UI8BL
  // UI8CH
  // UI8CL

  /// Countable Num: 0 Seq: 1 Event: 1 Listener: 2001945
  /// Countable Num: 0 Seq: 1 Event: 8 Listener: 2001945
  /// Countable Num: 0 Seq: 255 Event: 9 Listener: 28
  // Steps in this quest ( 0 is before accepting,
  // 1 is first, 255 means ready for turning it in
  enum Sequence : uint8_t
  {
    Seq0 = 0,
    Seq1 = 1,
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1006193;  //Teteroon
  static constexpr auto Enemy0 = 28;       //Coeurl Pup
  static constexpr auto Eobject0 = 2001945;//Destination
  static constexpr auto Item0 = 2000588;   //Empty Barrel
  static constexpr auto Item1 = 2000589;
  static constexpr auto Item2 = 2000590;

public:
  GaiUsa302() : Sapphire::ScriptAPI::QuestScript( 66270 ){};
  ~GaiUsa302() = default;

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
          Scene00003( quest, player );
        break;
      }
      case Eobject0:
      {
        Scene00001( quest, player );
        break;
      }
    }
  }

  void onBNpcKill( World::Quest& quest, Entity::BNpc& bnpc, Entity::Player& player ) override
  {
    switch( bnpc.getBNpcNameId() )
    {
      case Enemy0:
      {
        quest.setUI8CL( quest.getUI8CL() + 1 );
        quest.setUI8AL( quest.getUI8AL() + 1 );
        eventMgr().sendEventNotice( player, getId(), 1, 2, quest.getUI8AL(), 5 );
        checkQuestCompletion( quest, player );
        break;
      }
    }
  }

  void onEventItem( World::Quest& quest, Entity::Player& player, uint64_t actorId ) override
  {
    if( actorId == Eobject0 )
    {
      eventMgr().sendEventNotice( player, getId(), 0, 0 );
      quest.setUI8CH( 1 );
      quest.setUI8BL( 0 );
      quest.setUI8BH( 1 );
      quest.setBitFlag8( 1, true );
      checkQuestCompletion( quest, player );
    }
  }

private:
  void checkQuestCompletion( World::Quest& quest, Entity::Player& player )
  {
    if( quest.getUI8BH() >= 1 && quest.getUI8AL() >= 5 )
    {
      quest.setUI8BH( quest.getUI8BL() );
      quest.setUI8BL( quest.getUI8CH() );
      quest.setUI8CH( quest.getUI8CL() );
      quest.setUI8CL( 0 );
      quest.setUI8AL( 0 );
      quest.setBitFlag8( 1, false );
      quest.setSeq( SeqFinish );
    }
  }
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, NONE, bindSceneReturn( &GaiUsa302::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, NONE, bindSceneReturn( &GaiUsa302::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, NONE, bindSceneReturn( &GaiUsa302::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, NONE, bindSceneReturn( &GaiUsa302::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      Scene00004( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, NONE, bindSceneReturn( &GaiUsa302::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
    }
  }
};

EXPOSE_SCRIPT( GaiUsa302 );