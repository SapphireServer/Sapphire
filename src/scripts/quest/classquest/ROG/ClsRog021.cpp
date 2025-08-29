// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>
#include <Actor/BNpc.h>

// Quest Script: ClsRog021_00104
// Quest Name: Stabbers in Yer Fambles
// Quest ID: 65640
// Start NPC: 1009943 (Jacke)
// End NPC: 1009943 (Jacke)

using namespace Sapphire;

class ClsRog021 : public Sapphire::ScriptAPI::QuestScript
{
  private:
    // Basic quest information 
    // Quest vars / flags used
    // UI8AL
    // UI8BH
    // UI8BL

    /// Countable Num: 3 Seq: 1 Event: 5 Listener: 338
    /// Countable Num: 3 Seq: 1 Event: 5 Listener: 347
    /// Countable Num: 3 Seq: 1 Event: 5 Listener: 383
    /// Countable Num: 1 Seq: 255 Event: 1 Listener: 1009943
    // Steps in this quest ( 0 is before accepting, 
    // 1 is first, 255 means ready for turning it in
    enum Sequence : uint8_t
    {
      Seq0 = 0,
      Seq1 = 1,
      SeqFinish = 255,
    };

    // Entities found in the script data of the quest
    static constexpr auto Actor0 = 1009943; // Jacke ( Pos: -153.367004 -129.440002 265.907990  Teri: 129 )
    static constexpr auto Enemy0 = 338; // Tempered Champion
    static constexpr auto Enemy1 = 347; // Shelfscale Reaver
    static constexpr auto Enemy2 = 383; // Yarzon Bleeder ( Pos: 668.431030 9.000000 488.699005  Teri: 137 )

  public:
    ClsRog021() : Sapphire::ScriptAPI::QuestScript( 65640 ){}; 
    ~ClsRog021() = default; 

  //////////////////////////////////////////////////////////////////////
  // Event Handlers
  void onTalk( World::Quest& quest, Entity::Player& player, uint64_t actorId ) override
  {
    if( actorId == Actor0 )
    {
      switch( quest.getSeq() )
      {
        case Seq0:
        {
          Scene00000( quest, player );
          break;
        }
        case Seq1:
        {
          Scene00002( quest, player );
          break;
        }
        case SeqFinish:
        {
          Scene00003( quest, player );
          break;
        }
      }
    }
  }

  void onBNpcKill( World::Quest& quest, Entity::BNpc& bnpc, Entity::Player& player ) override
  {
    if( bnpc.getBNpcBaseId() != Enemy0 && bnpc.getBNpcBaseId() != Enemy1 && bnpc.getBNpcBaseId() != Enemy2 )
      return;


    auto currentKC338 = quest.getUI8AL() + 1;
    auto currentKC347 = quest.getUI8BH() + 1;
    auto currentKC383 = quest.getUI8BL() + 1;

    switch( bnpc.getBNpcBaseId() )
    {
      case Enemy0:
      {
        if( currentKC338 <= 3 )
        {
          quest.setUI8AL( currentKC338 );
          eventMgr().sendEventNotice( player, getId(), 1, 2, currentKC338, 3 );
          if( currentKC338 == 3 )
            checkQuestCompletion( quest, player );
        }
        break;
      }
      case Enemy1:
      {
        if( currentKC347 <= 3 )
        {
          quest.setUI8BH( currentKC347 );
          eventMgr().sendEventNotice( player, getId(), 2, 2, currentKC347, 3 );
          if( currentKC347 == 3 )
            checkQuestCompletion( quest, player );
        }
        break;
      }
      case Enemy2:
      {
        if( currentKC383 <= 3 )
        {
          quest.setUI8BL( currentKC383 );
          eventMgr().sendEventNotice( player, getId(), 3, 2, currentKC383, 3 );
          if( currentKC383 == 3 )
            checkQuestCompletion( quest, player );
        }
        break;
      }
    }
  }

private:
  void checkQuestCompletion( World::Quest& quest, Entity::Player& player )
  {
    auto currentKC338 = quest.getUI8AL();
    auto currentKC347 = quest.getUI8BH();
    auto currentKC383 = quest.getUI8BL();

    if( currentKC338 == 3 && currentKC347 == 3 && currentKC383 == 3 )
    {
      quest.setUI8AL( 0 );
      quest.setUI8BH( 0 );
      quest.setUI8BL( 0 );
      quest.setSeq( SeqFinish );
    }
  }
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &ClsRog021::Scene00000Return ) );
  }

  void Scene00000Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 ) // accept quest
    {
      Scene00001( quest, player );
    }


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00001( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 1, HIDE_HOTBAR, bindSceneReturn( &ClsRog021::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( Seq1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    //Head out into the fields an' test yer blades on some o' the local pests. Aye, a few lambs an' rats, an' then some pugils for a bit of a challenge.
    eventMgr().playQuestScene( player, getId(), 2, HIDE_HOTBAR, bindSceneReturn( &ClsRog021::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, HIDE_HOTBAR, bindSceneReturn( &ClsRog021::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
    }

  }

};

EXPOSE_SCRIPT( ClsRog021 );