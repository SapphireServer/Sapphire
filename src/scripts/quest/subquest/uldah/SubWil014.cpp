// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include "Actor/BNpc.h"
#include "Manager/EventMgr.h"
#include <Actor/Player.h>
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: SubWil014_00572
// Quest Name: In the Name of Science
// Quest ID: 66108
// Start NPC: 1003897 (Erasmus)
// End NPC: 1003897 (Erasmus)

using namespace Sapphire;

class SubWil014 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // UI8AL
  // UI8BH

  /// Countable Num: 6 Seq: 1 Event: 9 Listener: 351
  /// Countable Num: 1 Seq: 255 Event: 1 Listener: 1003897
  // Steps in this quest ( 0 is before accepting,
  // 1 is first, 255 means ready for turning it in
  enum Sequence : uint8_t
  {
    Seq0 = 0,
    Seq1 = 1,
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1003897;// Erasmus ( Pos: -195.421997 17.990400 60.532501  Teri: 130 )
  static constexpr auto Enemy0 = 351;    // Qiqirn Gullroaster
  static constexpr auto Item0 = 2000385;

public:
  SubWil014() : Sapphire::ScriptAPI::QuestScript( 66108 ){};
  ~SubWil014() = default;

  //////////////////////////////////////////////////////////////////////
  // Event Handlers
  void onTalk( World::Quest& quest, Entity::Player& player, uint64_t actorId ) override
  {
    if( actorId == Actor0 )
    {
      if( quest.getSeq() == Seq0 )
      {
        Scene00000( quest, player );
      }
      else
      {
        Scene00002( quest, player );
      }
    }
  }

  void onEventItem( World::Quest& quest, Entity::Player& player, uint64_t actorId ) override
  {
    if( quest.getSeq() != Seq1 ) return;

    quest.setUI8AL( quest.getUI8AL() + 1 );
    eventMgr().sendEventNotice( player, getId(), 0, 2, quest.getUI8AL(), 5 );
    if( quest.getUI8AL() >= 5 )
    {
      quest.setSeq( SeqFinish );
    }
  }

  void onBNpcKill( World::Quest& quest, Entity::BNpc& bnpc, Entity::Player& player ) override
  {
    if( bnpc.getBNpcBaseId() != Enemy0 )
      return;
    else
    {
      if( quest.getUI8BH() <= 5 )
      {
        quest.setUI8BH( quest.getUI8BH() + 1 );//adds to key items
        onEventItem( quest, player, 0 );
      }
    }
  }

private:
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, NONE, bindSceneReturn( &SubWil014::Scene00000Return ) );
  }

  void Scene00000Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )// accept quest
    {
      quest.setSeq( Seq1 );
      Scene00001( quest, player );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00001( World::Quest& quest, Entity::Player& player )
  {
    //talking scene
    eventMgr().playQuestScene( player, getId(), 1, NONE, bindSceneReturn( &SubWil014::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    //inventory scene
    eventMgr().playQuestScene( player, getId(), 2, NONE, bindSceneReturn( &SubWil014::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
    {
      Scene00003( quest, player );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, NONE, bindSceneReturn( &SubWil014::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
    }
    else
    {
      Scene00004( quest, player );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, NONE, bindSceneReturn( &SubWil014::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }
};

EXPOSE_SCRIPT( SubWil014 );