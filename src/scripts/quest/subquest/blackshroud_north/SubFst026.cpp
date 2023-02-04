// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include "Manager/EventMgr.h"
#include <Actor/Player.h>
#include <Actor/BNpc.h>
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: SubFst026_00170
// Quest Name: Jumping at Shadows
// Quest ID: 65706
// Start NPC: 1000629
// End NPC: 1000629

using namespace Sapphire;

class SubFst026 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // UI8AL

  /// Countable Num: 6 Seq: 1 Event: 5 Listener: 9
  /// Countable Num: 1 Seq: 255 Event: 1 Listener: 1000629
  // Steps in this quest ( 0 is before accepting,
  // 1 is first, 255 means ready for turning it in
  enum Sequence : uint8_t
  {
    Seq0 = 0,
    Seq1 = 1,
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1000629;
  static constexpr auto Enemy0 = 9;
  static constexpr auto Seq0Actor0 = 0;
  static constexpr auto Seq2Actor0 = 1;

public:
  SubFst026() : Sapphire::ScriptAPI::QuestScript( 65706 ){};
  ~SubFst026() = default;

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
          Scene00001( quest, player );
        break;
      }
    }
  }

  void onBNpcKill( World::Quest& quest, Sapphire::Entity::BNpc& bnpc, Sapphire::Entity::Player& player ) override
  {
    if( bnpc.getBNpcNameId() != Enemy0 )
      return;

    auto currentKC = quest.getUI8AL();

    if( currentKC + 1 >= 6 )
    {
      eventMgr().sendEventNotice( player, getId(), 0, 2, currentKC + 1, 6 );
      quest.setSeq( SeqFinish );
    }
    else
    {
      quest.setUI8AL( currentKC + 1 );
      eventMgr().sendEventNotice( player, getId(), 0, 2, currentKC + 1, 6 );
    }
  }

private:
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, NONE, bindSceneReturn( &SubFst026::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, NONE, bindSceneReturn( &SubFst026::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId() );
    }
  }
};

EXPOSE_SCRIPT( SubFst026 );