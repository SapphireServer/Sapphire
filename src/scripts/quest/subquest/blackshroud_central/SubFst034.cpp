// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include <Actor/Player.h>
#include <Actor/BNpc.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: SubFst034_00128
// Quest Name: Eggs over Queasy
// Quest ID: 65664
// Start NPC: 1000421
// End NPC: 1000449

using namespace Sapphire;

class SubFst034 : public Sapphire::ScriptAPI::QuestScript
{
  private:
    // Basic quest information 
    // Quest vars / flags used
    // UI8AL
    // UI8BH

    /// Countable Num: 8 Seq: 1 Event: 9 Listener: 43
    /// Countable Num: 1 Seq: 255 Event: 1 Listener: 1000449
    // Steps in this quest ( 0 is before accepting, 
    // 1 is first, 255 means ready for turning it in
    enum Sequence : uint8_t
    {
      Seq0 = 0,
      Seq1 = 1,
      SeqFinish = 255,
    };

    // Entities found in the script data of the quest
    static constexpr auto Actor0 = 1000421;
    static constexpr auto Actor1 = 1000449;
    static constexpr auto Enemy0 = 43;
    static constexpr auto Item0 = 2000062;
    static constexpr auto Seq0Actor0 = 0;
    static constexpr auto Seq2Actor1 = 1;
    static constexpr auto Seq2Actor1Npctradeno = 99;
    static constexpr auto Seq2Actor1Npctradeok = 100;

  public:
    SubFst034() : Sapphire::ScriptAPI::QuestScript( 65664 ){}; 
    ~SubFst034() = default; 

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

  void onBNpcKill( World::Quest& quest, Entity::BNpc& bnpc, Entity::Player& player ) override
  {
    if( quest.getSeq() == Seq1 )
    {
      if( bnpc.getBNpcNameId() != Enemy0 )
        return;

      quest.setUI8AL( quest.getUI8AL() + 1 );
      quest.setUI8BH( quest.getUI8BH() + 1 );
      eventMgr().sendEventNotice( player, getId(), 0, 3, quest.getUI8AL(), 8 );

      if( quest.getUI8AL() >= 8 )
        quest.setSeq( SeqFinish );
    }
  }

  private:
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, NONE, bindSceneReturn( &SubFst034::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, NONE, bindSceneReturn( &SubFst034::Scene00001Return ) );
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
    eventMgr().playQuestScene( player, getId(), 99, NONE, bindSceneReturn( &SubFst034::Scene00099Return ) );
  }

  void Scene00099Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

  }

  //////////////////////////////////////////////////////////////////////

  void Scene00100( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 100, NONE, bindSceneReturn( &SubFst034::Scene00100Return ) );
  }

  void Scene00100Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
    }
  }

};

EXPOSE_SCRIPT( SubFst034 );