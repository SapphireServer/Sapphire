// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include "Manager/EventMgr.h"
#include <Actor/Player.h>
#include <Actor/BNpc.h>
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: ClsArc100_00219
// Quest Name: My First Bow
// Quest ID: 65755
// Start NPC: 1000200
// End NPC: 1000200

using namespace Sapphire;

class ClsArc100 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // UI8AL
  // UI8BH
  // UI8BL

  /// Countable Num: 3 Seq: 1 Event: 5 Listener: 37
  /// Countable Num: 3 Seq: 1 Event: 5 Listener: 49
  /// Countable Num: 3 Seq: 1 Event: 5 Listener: 47
  /// Countable Num: 1 Seq: 255 Event: 1 Listener: 1000200
  // Steps in this quest ( 0 is before accepting,
  // 1 is first, 255 means ready for turning it in
  enum Sequence : uint8_t
  {
    Seq0 = 0,
    Seq1 = 1,
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1000200;
  static constexpr auto Enemy0 = 37;//Ground Squirrel
  static constexpr auto Enemy1 = 49;//Little Ladybug
  static constexpr auto Enemy2 = 47;//Foest Funguar
  static constexpr auto Seq0Actor0 = 0;
  static constexpr auto Seq2Actor0 = 1;

public:
  ClsArc100() : Sapphire::ScriptAPI::QuestScript( 65755 ){};
  ~ClsArc100() = default;

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
    if( bnpc.getBNpcNameId() != Enemy0 && bnpc.getBNpcNameId() != Enemy1 && bnpc.getBNpcNameId() != Enemy2 )
      return;


    auto currentKC37 = quest.getUI8AL() + 1;
    auto currentKC49 = quest.getUI8BH() + 1;
    auto currentKC47 = quest.getUI8BL() + 1;

    switch( bnpc.getBNpcNameId() )
    {
      case Enemy0:
      {
        if( currentKC37 >= 3 )
        {
          quest.setUI8AL( currentKC37 );
          checkQuestCompletion( quest, player );
          eventMgr().sendEventNotice( player, getId(), 0, 2, currentKC37, 3 );
        }
        else if( currentKC37 < 3 )
        {
          quest.setUI8AL( currentKC37 );
          eventMgr().sendEventNotice( player, getId(), 0, 2, currentKC37, 3 );
        }

        break;
      }
      case Enemy1:
      {
        if( currentKC49 >= 3 )
        {
          quest.setUI8BH( currentKC49 );
          checkQuestCompletion( quest, player );
          eventMgr().sendEventNotice( player, getId(), 1, 2, currentKC49, 3 );
        }
        else if( currentKC49 < 3 )
        {
          quest.setUI8BH( currentKC49 );
          eventMgr().sendEventNotice( player, getId(), 1, 2, currentKC49, 3 );
        }

        break;
      }
      case Enemy2:
      {
        if( currentKC47 >= 3 )
        {
          quest.setUI8BL( currentKC47 );
          checkQuestCompletion( quest, player );
          eventMgr().sendEventNotice( player, getId(), 2, 2, currentKC47, 3 );
        }
        else if( currentKC47 < 3 )
        {
          quest.setUI8BL( currentKC47 );
          eventMgr().sendEventNotice( player, getId(), 2, 2, currentKC47, 3 );
        }

        break;
      }
    }
  }

private:
  void checkQuestCompletion( World::Quest& quest, Entity::Player& player )
  {
    auto currentKC37 = quest.getUI8AL();
    auto currentKC49 = quest.getUI8BH();
    auto currentKC47 = quest.getUI8BL();

    if( currentKC37 == 3 && currentKC49 == 3 && currentKC47 == 3 )
    {
      quest.setUI8AL( 0 );
      quest.setUI8BH( 0 );
      quest.setUI8BL( 0 );
      eventMgr().sendEventNotice( player, getId(), 3, 0 );
      quest.setSeq( SeqFinish );
    }
  }
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, NONE, bindSceneReturn( &ClsArc100::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, NONE, bindSceneReturn( &ClsArc100::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId() );
    }
  }
};

EXPOSE_SCRIPT( ClsArc100 );