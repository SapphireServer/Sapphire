// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include "Manager/EventMgr.h"
#include <Actor/Player.h>
#include <Actor/BNpc.h>
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: SubFst047_00374
// Quest Name: Feeding Time
// Quest ID: 65910
// Start NPC: 1000470
// End NPC: 1000470

using namespace Sapphire;

class SubFst047 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // BitFlag8
  // UI8AL
  // UI8BH

  /// Countable Num: 1 Seq: 1 Event: 1 Listener: 2000999
  /// Countable Num: 3 Seq: 2 Event: 1 Listener: 2001000
  /// Countable Num: 1 Seq: 255 Event: 8 Listener: 2001000
  // Steps in this quest ( 0 is before accepting,
  // 1 is first, 255 means ready for turning it in
  enum Sequence : uint8_t
  {
    Seq0 = 0,
    Seq1 = 1,
    Seq2 = 2,
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1000470;  //Keitha
  static constexpr auto Eobject0 = 2000999;//Gyshal Greens
  static constexpr auto Eobject1 = 2001000;//Feeding Trough
  static constexpr auto Eobject2 = 2001001;//Feeding Trough
  static constexpr auto Eobject3 = 2001002;//Feeding Trough
  static constexpr auto EventActionSearch = 1;
  static constexpr auto Item0 = 2000242;
  static constexpr auto Seq0Actor0 = 0;
  static constexpr auto Seq1Eobject0 = 1;
  static constexpr auto Seq1Eobject0Eventactionno = 99;
  static constexpr auto Seq1Eobject0Eventactionok = 100;
  static constexpr auto Seq2Eobject1 = 2;
  static constexpr auto Seq2Eobject1Useitemno = 97;
  static constexpr auto Seq2Eobject1Useitemok = 98;
  static constexpr auto Seq2Eobject2 = 3;
  static constexpr auto Seq2Eobject2Useitemno = 95;
  static constexpr auto Seq2Eobject2Useitemok = 96;
  static constexpr auto Seq2Eobject3 = 4;
  static constexpr auto Seq2Eobject3Useitemno = 93;
  static constexpr auto Seq2Eobject3Useitemok = 94;
  static constexpr auto Seq3Actor0 = 5;
  static constexpr auto Seq3Eobject1 = 6;
  static constexpr auto Seq3Eobject1Eventactionno = 91;
  static constexpr auto Seq3Eobject1Eventactionok = 92;
  static constexpr auto Seq3Eobject2 = 7;
  static constexpr auto Seq3Eobject2Eventactionno = 89;
  static constexpr auto Seq3Eobject2Eventactionok = 90;
  static constexpr auto Seq3Eobject3 = 8;
  static constexpr auto Seq3Eobject3Eventactionno = 87;
  static constexpr auto Seq3Eobject3Eventactionok = 88;

public:
  SubFst047() : Sapphire::ScriptAPI::QuestScript( 65910 ){};
  ~SubFst047() = default;

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
          Scene00005( quest, player );
        break;
      }
      case Eobject0:
      {
        eventMgr().eventActionStart(
                player, getId(), 0x02,
                [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                  Scene00001( quest, player );
                },
                nullptr, 0 );
        break;
      }
      case Eobject1:
      {
        Scene00002( quest, player );
        break;
      }
      case Eobject2:
      {
        Scene00003( quest, player );
        break;
      }
      case Eobject3:
      {
        Scene00004( quest, player );
        break;
      }
    }
  }

  void onEventItem( World::Quest& quest, Entity::Player& player, uint64_t actorId ) override
  {
    switch( actorId )
    {
      case Eobject1:
      {
        Scene00098( quest, player );
        break;
      }
      case Eobject2:
      {
        Scene00096( quest, player );
        break;
      }
      case Eobject3:
      {
        Scene00094( quest, player );
        break;
      }
    }
  }


private:
  void checkQuestCompletion( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().sendEventNotice( player, getId(), 1, 2, quest.getUI8AL(), 3 );
    if( quest.getUI8AL() >= 3 )
    {
      quest.setUI8AL( 0 );
      quest.setSeq( SeqFinish );
    }
  }
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, NONE, bindSceneReturn( &SubFst047::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, NONE, bindSceneReturn( &SubFst047::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 0, 0 );
    quest.setSeq( Seq2 );
    quest.setUI8BH( 3 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, NONE, bindSceneReturn( &SubFst047::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, NONE, bindSceneReturn( &SubFst047::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, NONE, bindSceneReturn( &SubFst047::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, NONE, bindSceneReturn( &SubFst047::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00006( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 6, NONE, bindSceneReturn( &SubFst047::Scene00006Return ) );
  }

  void Scene00006Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00007( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 7, NONE, bindSceneReturn( &SubFst047::Scene00007Return ) );
  }

  void Scene00007Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00008( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 8, NONE, bindSceneReturn( &SubFst047::Scene00008Return ) );
  }

  void Scene00008Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00087( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 87, NONE, bindSceneReturn( &SubFst047::Scene00087Return ) );
  }

  void Scene00087Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00088( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 88, NONE, bindSceneReturn( &SubFst047::Scene00088Return ) );
  }

  void Scene00088Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00089( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 89, NONE, bindSceneReturn( &SubFst047::Scene00089Return ) );
  }

  void Scene00089Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00090( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 90, NONE, bindSceneReturn( &SubFst047::Scene00090Return ) );
  }

  void Scene00090Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00091( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 91, NONE, bindSceneReturn( &SubFst047::Scene00091Return ) );
  }

  void Scene00091Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00092( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 92, NONE, bindSceneReturn( &SubFst047::Scene00092Return ) );
  }

  void Scene00092Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00093( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 93, NONE, bindSceneReturn( &SubFst047::Scene00093Return ) );
  }

  void Scene00093Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00094( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 94, NONE, bindSceneReturn( &SubFst047::Scene00094Return ) );
  }

  void Scene00094Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setBitFlag8( 3, true );
    quest.setUI8AL( quest.getUI8AL() + 1 );
    quest.setUI8BH( quest.getUI8BH() - 1 );
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00095( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 95, NONE, bindSceneReturn( &SubFst047::Scene00095Return ) );
  }

  void Scene00095Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00096( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 96, NONE, bindSceneReturn( &SubFst047::Scene00096Return ) );
  }

  void Scene00096Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setBitFlag8( 2, true );
    quest.setUI8AL( quest.getUI8AL() + 1 );
    quest.setUI8BH( quest.getUI8BH() - 1 );
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00097( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 97, NONE, bindSceneReturn( &SubFst047::Scene00097Return ) );
  }

  void Scene00097Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00098( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 98, NONE, bindSceneReturn( &SubFst047::Scene00098Return ) );
  }

  void Scene00098Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setBitFlag8( 1, true );
    quest.setUI8AL( quest.getUI8AL() + 1 );
    quest.setUI8BH( quest.getUI8BH() - 1 );
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00099( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 99, NONE, bindSceneReturn( &SubFst047::Scene00099Return ) );
  }

  void Scene00099Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00100( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 100, NONE, bindSceneReturn( &SubFst047::Scene00100Return ) );
  }

  void Scene00100Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }
};

EXPOSE_SCRIPT( SubFst047 );