// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include "Manager/EventMgr.h"
#include <Actor/Player.h>
#include <Actor/BNpc.h>
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: SubSea013_00661
// Quest Name: The Rats in the Wharf
// Quest ID: 66197
// Start NPC: 1001000 (H'naanza)
// End NPC: 1000972 (Baderon)

using namespace Sapphire;

class SubSea013 : public Sapphire::ScriptAPI::QuestScript
{
  private:
    // Basic quest information 
    // Quest vars / flags used
    // UI8AL

    /// Countable Num: 0 Seq: 1 Event: 5 Listener: 347
    /// Countable Num: 0 Seq: 255 Event: 1 Listener: 1000972
    // Steps in this quest ( 0 is before accepting, 
    // 1 is first, 255 means ready for turning it in
    enum Sequence : uint8_t
    {
      Seq0 = 0,
      Seq1 = 1,
      SeqFinish = 255,
    };

    // Entities found in the script data of the quest
    static constexpr auto Actor0 = 1001000; // H'naanza ( Pos: -32.011700 41.500000 208.397003  Teri: 128 )
    static constexpr auto Actor1 = 1000972; // Baderon ( Pos: 20.297800 40.199902 -6.102400  Teri: 128 )
    static constexpr auto Enemy0 = 417;

  public:
    SubSea013() : Sapphire::ScriptAPI::QuestScript( 66197 ){}; 
    ~SubSea013() = default; 

  //////////////////////////////////////////////////////////////////////
  // Event Handlers
  void onTalk( World::Quest& quest, Entity::Player& player, uint64_t actorId ) override
  {
    switch( actorId )
    {
      case Actor0:
      {
        Scene00000( quest, player );
        break;
      }
      case Actor1:
      {
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

    if( currentKC + 1 >= 5 )
    {
      eventMgr().sendEventNotice( player, getId(), 0, 2, currentKC + 1, 5 );
      quest.setSeq( SeqFinish );
    }
    else
    {
      quest.setUI8AL( currentKC + 1 );
      eventMgr().sendEventNotice( player, getId(), 0, 2, currentKC + 1, 5 );
    }
  }

  private:
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, NONE, bindSceneReturn( &SubSea013::Scene00000Return ) );
  }

  void Scene00000Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 ) // accept quest
    {
      quest.setSeq( Seq1 );
    }


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00001( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 1, NONE, bindSceneReturn( &SubSea013::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 ) // complete quest
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
    }

  }

};

EXPOSE_SCRIPT( SubSea013 );