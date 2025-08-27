// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: ClsGla021_00286
// Quest Name: My First Gladius
// Quest ID: 65822
// Start NPC: 1001739 (Mylla)
// End NPC: 1001739 (Mylla)

using namespace Sapphire;

class ClsGla021 : public Sapphire::ScriptAPI::QuestScript
{
  private:
    // Basic quest information 
    // Quest vars / flags used
    // UI8AL
    // UI8BH
    // UI8BL

    /// Countable Num: 3 Seq: 1 Event: 5 Listener: 351
    /// Countable Num: 3 Seq: 1 Event: 5 Listener: 385
    /// Countable Num: 3 Seq: 1 Event: 5 Listener: 205
    /// Countable Num: 1 Seq: 255 Event: 1 Listener: 1001739
    // Steps in this quest ( 0 is before accepting, 
    // 1 is first, 255 means ready for turning it in
    enum Sequence : uint8_t
    {
      Seq0 = 0,
      Seq1 = 1,
      SeqFinish = 255,
    };

    // Entities found in the script data of the quest
    static constexpr auto Actor0 = 1001739; // Mylla ( Pos: -94.529701 6.499970 39.810699  Teri: 131 )
    static constexpr auto Enemy0 = 351; // Qiqirn Gullroaster
    static constexpr auto Enemy1 = 385; // Trenchclaw Sahagin ( Pos: 80.837502 68.925400 -218.042999  Teri: 134 )
    static constexpr auto Enemy2 = 205; // Mottled Eft ( Pos: 15.554700 0.648601 -59.534698  Teri: 141 )

  public:
    ClsGla021() : Sapphire::ScriptAPI::QuestScript( 65822 ){}; 
    ~ClsGla021() = default; 

  //////////////////////////////////////////////////////////////////////
  // Event Handlers
  void onTalk( World::Quest& quest, Entity::Player& player, uint64_t actorId ) override
  {
    if( actorId == Actor0 )
    {
      switch( quest.getSeq() )
      {
        case Seq0:
          Scene00000( quest, player );
          break;
        case SeqFinish:
          Scene00001( quest, player );
          break;
      }
    }
  }

  void onBNpcKill( World::Quest& quest, Entity::BNpc& bnpc, Entity::Player& player ) override
  {
    if( bnpc.getBNpcBaseId() != Enemy0 && bnpc.getBNpcBaseId() != Enemy1 && bnpc.getBNpcBaseId() != Enemy2 )
      return;


    auto currentKC351 = quest.getUI8AL() + 1;
    auto currentKC385 = quest.getUI8BH() + 1;
    auto currentKC205 = quest.getUI8BL() + 1;

    switch( bnpc.getBNpcBaseId() )
    {
      case Enemy0:
      {
        if( currentKC351 <= 3 )
        {
          quest.setUI8AL( currentKC351 );
          eventMgr().sendEventNotice( player, getId(), 1, 2, currentKC351, 3 );
          if( currentKC351 == 3 )
            checkQuestCompletion( quest, player );
        }
        break;
      }
      case Enemy1:
      {
        if( currentKC385 <= 3 )
        {
          quest.setUI8BH( currentKC385 );
          eventMgr().sendEventNotice( player, getId(), 2, 2, currentKC385, 3 );
          if( currentKC385 == 3 )
            checkQuestCompletion( quest, player );
        }
        break;
      }
      case Enemy2:
      {
        if( currentKC205 <= 3 )
        {
          quest.setUI8BL( currentKC205 );
          eventMgr().sendEventNotice( player, getId(), 3, 2, currentKC205, 3 );
          if( currentKC205 == 3 )
            checkQuestCompletion( quest, player );
        }
        break;
      }
    }
  }

private:
  void checkQuestCompletion( World::Quest& quest, Entity::Player& player )
  {
    auto currentKC351 = quest.getUI8AL();
    auto currentKC385 = quest.getUI8BH();
    auto currentKC205 = quest.getUI8BL();

    if( currentKC351 == 3 && currentKC385 == 3 && currentKC205 == 3 )
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
    eventMgr().playQuestScene( player, getId(), 0, NONE, bindSceneReturn( &ClsGla021::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, NONE, bindSceneReturn( &ClsGla021::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
    }

  }

};

EXPOSE_SCRIPT( ClsGla021 );