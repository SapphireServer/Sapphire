// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>
#include <Actor/BNpc.h>

// Quest Script: SubWil032_00224
// Quest Name: I Believe You Can Fly
// Quest ID: 65760
// Start NPC: 1001992 (Oswell)
// End NPC: 1002014 (Kikipu)

using namespace Sapphire;

class SubWil032 : public Sapphire::ScriptAPI::QuestScript
{
  private:
    // Basic quest information 
    // Quest vars / flags used
    // UI8AL
    // UI8BH
    // UI8BL

    /// Countable Num: 5 Seq: 1 Event: 9 Listener: 431
    /// Countable Num: 1 Seq: 255 Event: 1 Listener: 1002014
    // Steps in this quest ( 0 is before accepting, 
    // 1 is first, 255 means ready for turning it in
    enum Sequence : uint8_t
    {
      Seq0 = 0,
      Seq1 = 1,
      SeqFinish = 255,
    };

    // Entities found in the script data of the quest
    static constexpr auto Actor0 = 1001992; // Oswell ( Pos: 223.162994 52.017899 141.253006  Teri: 140 )
    static constexpr auto Actor1 = 1002014; // Kikipu ( Pos: -253.427002 33.219002 404.062988  Teri: 140 )
    static constexpr auto Enemy0 = 282; // Attack Hound
    static constexpr auto Item0 = 2000354;
    static constexpr auto Item1 = 2000355;

  public:
    SubWil032() : Sapphire::ScriptAPI::QuestScript( 65760 ){}; 
    ~SubWil032() = default; 

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
          Scene00001( quest, player );
        break;
      }
    }
  }

  void onEventItem( World::Quest& quest, Entity::Player& player, uint64_t actorId ) override
  {
  }

  void onBNpcKill( World::Quest& quest, Entity::BNpc& bnpc, Entity::Player& player ) override
  {
    if( !bnpc.getBNpcNameId() )
      return;

    if( quest.getSeq() == Seq1 )
    {
      quest.setUI8AL( quest.getUI8AL() + 1 );
      quest.setUI8BL( quest.getUI8BL() + 1 );
      eventMgr().sendEventNotice( player, getId(), 0, 2, quest.getUI8AL(), 5 );

      if( quest.getUI8AL() >= 5 )
        quest.setSeq( SeqFinish );
    }
  }

  private:
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, NONE, bindSceneReturn( &SubWil032::Scene00000Return ) );
  }

  void Scene00000Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 ) // accept quest
    {
      quest.setSeq( Seq1 );
      quest.setUI8BH( 1 );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00001( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 1, NONE, bindSceneReturn( &SubWil032::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 && result.getResult( 2 ) == 1 && result.getResult( 5 ) == 5 )
      Scene00100( quest, player );
    else
      Scene00099( quest, player );

  }

  //////////////////////////////////////////////////////////////////////

  void Scene00099( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 99, NONE, bindSceneReturn( &SubWil032::Scene00099Return ) );
  }

  void Scene00099Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

  }

  //////////////////////////////////////////////////////////////////////

  void Scene00100( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 100, NONE, bindSceneReturn( &SubWil032::Scene00100Return ) );
  }

  void Scene00100Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
    {
        player.finishQuest( getId(), result.getResult( 1 ) );
    }
  }

};

EXPOSE_SCRIPT( SubWil032 );