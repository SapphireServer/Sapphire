// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include <Actor/Player.h>
#include <Actor/BNpc.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: SubFst051_00157
// Quest Name: Extending Fences
// Quest ID: 65693
// Start NPC: 1000471 (Luquelot)
// End NPC: 1000471 (Luquelot)

using namespace Sapphire;

class SubFst051 : public Sapphire::ScriptAPI::QuestScript
{
  private:
    // Basic quest information 
    // Quest vars / flags used
    // UI8AL
    // UI8BH

    /// Countable Num: 6 Seq: 1 Event: 9 Listener: 10
    /// Countable Num: 1 Seq: 255 Event: 1 Listener: 1000471
    // Steps in this quest ( 0 is before accepting, 
    // 1 is first, 255 means ready for turning it in
    enum Sequence : uint8_t
    {
      Seq0 = 0,
      Seq1 = 1,
      SeqFinish = 255,
    };

    // Entities found in the script data of the quest
    static constexpr auto Actor0 = 1000471; // Luquelot ( Pos: -60.461201 0.199996 6.331730  Teri: 148 )
    static constexpr auto Enemy0 = 10; // Diremite ( Pos: -11.962200 -2.344680 21.032700  Teri: 5 )
    static constexpr auto Item0 = 2000093;
    static constexpr auto Seq0Actor0 = 0; // 
    static constexpr auto Seq2Actor0 = 1; // 
    static constexpr auto Seq2Actor0Npctradeno = 99; // Hecatoncheir Piledriver
    static constexpr auto Seq2Actor0Npctradeok = 100; // Hecatoncheir Blastmaster ( Pos: -135.210007 5.708900 -117.417999  Teri: 141 )

  public:
    SubFst051() : Sapphire::ScriptAPI::QuestScript( 65693 ){}; 
    ~SubFst051() = default; 

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
    if( bnpc.getBNpcNameId() != Enemy0 )
      return;
    else
    {
      auto currentKC = quest.getUI8AL();
      if( currentKC <= 6 )
      {
        eventMgr().sendEventNotice( player, getId(), 0, 2, currentKC + 1, 6 );
        quest.setUI8AL( currentKC + 1 );
        quest.setUI8BH( currentKC + 1 );
        checkQuestCompletion( quest, player );
      }
    }
  }

  private:
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void checkQuestCompletion( World::Quest& quest, Entity::Player& player )
  {
    if( quest.getUI8AL() >= 6 )
    {
      quest.setUI8AL( 0 );
      quest.setSeq( SeqFinish );
    }
  }

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, NONE, bindSceneReturn( &SubFst051::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, NONE, bindSceneReturn( &SubFst051::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      Scene00100( quest, player );
    else
      Scene00099( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00099( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 99, NONE, bindSceneReturn( &SubFst051::Scene00099Return ) );
  }

  void Scene00099Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00100( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 100, NONE, bindSceneReturn( &SubFst051::Scene00100Return ) );
  }

  void Scene00100Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
    {
        player.finishQuest( getId(), result.getResult( 1 ) );
    }
  }

};

EXPOSE_SCRIPT( SubFst051 );