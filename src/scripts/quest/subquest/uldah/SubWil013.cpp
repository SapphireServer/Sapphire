// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include "Actor/BNpc.h"
#include "Manager/EventMgr.h"
#include <Actor/Player.h>
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: SubWil013_00571
// Quest Name: Beet-red Beetles Beat Red
// Quest ID: 66107
// Start NPC: 1003896 (Wolkan)
// End NPC: 1003896 (Wolkan)

using namespace Sapphire;

class SubWil013 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // UI8AL

  /// Countable Num: 4 Seq: 1 Event: 5 Listener: 49
  /// Countable Num: 1 Seq: 255 Event: 1 Listener: 1003896
  // Steps in this quest ( 0 is before accepting,
  // 1 is first, 255 means ready for turning it in
  enum Sequence : uint8_t
  {
    Seq0 = 0,
    Seq1 = 1,
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1003896;// Wolkan ( Pos: -96.147102 6.546070 21.286301  Teri: 131 )
  static constexpr auto Enemy0 = 49;     // Little Ladybug ( Pos: 230.500000 52.037998 138.003998  Teri: 140 )

public:
  SubWil013() : Sapphire::ScriptAPI::QuestScript( 66107 ){};
  ~SubWil013() = default;

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
        Scene00001( quest, player );
      }
    }
  }

  void onBNpcKill( World::Quest& quest, Entity::BNpc& bnpc, Entity::Player& player ) override
  {
    if( bnpc.getBNpcBaseId() != Enemy0 )
      return;
    if( quest.getUI8AL() < 4 )
    {
      quest.setUI8AL( quest.getUI8AL() + 1 );
      eventMgr().sendEventNotice( player, getId(), 0, 2, quest.getUI8AL(), 4 );

      if( quest.getUI8AL() == 4 )
      {
        quest.setSeq( SeqFinish );
      }
    }
  }

private:
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, NONE, bindSceneReturn( &SubWil013::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, NONE, bindSceneReturn( &SubWil013::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    Scene00002( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, NONE, bindSceneReturn( &SubWil013::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 && quest.getSeq() == SeqFinish )
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
    }
  }
};

EXPOSE_SCRIPT( SubWil013 );