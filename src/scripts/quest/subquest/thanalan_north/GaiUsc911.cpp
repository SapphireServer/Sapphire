// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include "Manager/EventMgr.h"
#include <Actor/Player.h>
#include <ScriptObject.h>
#include <Service.h>

#include "Actor/BNpc.h"

// Quest Script: GaiUsc911_01046
// Quest Name: Setting the Stage
// Quest ID: 66582
// Start NPC: 1006646
// End NPC: 1006657

using namespace Sapphire;

class GaiUsc911 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // UI8AL
  // UI8BH

  /// Countable Num: 0 Seq: 1 Event: 5 Listener: 62
  /// Countable Num: 0 Seq: 1 Event: 5 Listener: 63
  /// Countable Num: 0 Seq: 255 Event: 5 Listener: 64
  // Steps in this quest ( 0 is before accepting,
  // 1 is first, 255 means ready for turning it in
  enum Sequence : uint8_t
  {
    Seq0 = 0,
    Seq1 = 1,
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1006646;//Edelstein
  static constexpr auto Actor1 = 1006657;//Raubahn
  static constexpr auto Enemy0 = 62;
  static constexpr auto Enemy1 = 63;
  static constexpr auto Enemy2 = 64;
  static constexpr auto Enemy3 = 55;
  static constexpr auto Enemy4 = 61;
  static constexpr auto Enemy5 = 200;

public:
  GaiUsc911() : Sapphire::ScriptAPI::QuestScript( 66582 ){};
  ~GaiUsc911() = default;

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
          Scene00002( quest, player );
        break;
      }
    }
  }

  void onBNpcKill( World::Quest& quest, Entity::BNpc& bnpc, Entity::Player& player ) override
  {
    playerMgr().sendUrgent( player, std::to_string( bnpc.getBNpcBaseId() ) );
    switch( bnpc.getBNpcBaseId() )
    {
      case Enemy0:
      case Enemy1:
      case Enemy2:
      case Enemy3:
      case Enemy4:
      {
        quest.setUI8BH( quest.getUI8BH() + 1 );
        eventMgr().sendEventNotice( player, getId(), 0, 2, quest.getUI8BH(), 3 );
        checkQuestCompletion( quest, player );
        break;
      }
      case Enemy5:
      {
        quest.setUI8AL( quest.getUI8AL() + 1 );
        eventMgr().sendEventNotice( player, getId(), 1, 2, quest.getUI8AL(), 3 );
        checkQuestCompletion( quest, player );
        break;
      }
    }
  }

private:
  void checkQuestCompletion( World::Quest& quest, Entity::Player& player )
  {
    if( quest.getUI8AL() >= 3 && quest.getUI8BH() >= 3 )
    {
      quest.setUI8BH( 0 );
      quest.setUI8AL( 0 );
      quest.setSeq( SeqFinish );
    }
  }
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &GaiUsc911::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, HIDE_HOTBAR, bindSceneReturn( &GaiUsc911::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( Seq1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, HIDE_HOTBAR, bindSceneReturn( &GaiUsc911::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
    }
  }
};

EXPOSE_SCRIPT( GaiUsc911 );