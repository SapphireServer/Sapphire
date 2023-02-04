// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include "Manager/EventMgr.h"
#include <Actor/Player.h>
#include <Actor/BNpc.h>
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: SubFst056_00377
// Quest Name: Don't Look Down
// Quest ID: 65913
// Start NPC: 1000435
// End NPC: 1000436

using namespace Sapphire;

class SubFst056 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // BitFlag8
  // UI8AL

  /// Countable Num: 4 Seq: 1 Event: 1 Listener: 2000748
  /// Countable Num: 1 Seq: 255 Event: 1 Listener: 2000749
  // Steps in this quest ( 0 is before accepting,
  // 1 is first, 255 means ready for turning it in
  enum Sequence : uint8_t
  {
    Seq0 = 0,
    Seq1 = 1,
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1000435;//Osha Jaab
  static constexpr auto Actor1 = 1000436;//Theodore
  static constexpr auto Eobject0 = 2000748;
  static constexpr auto Eobject1 = 2000749;//Blue Trumpet
  static constexpr auto Eobject2 = 2000750;//Blue Trumpet
  static constexpr auto Eobject3 = 2000751;
  static constexpr auto EventActionSearch = 1;
  static constexpr auto Seq0Actor0 = 0;
  static constexpr auto Seq1Eobject0 = 1;
  static constexpr auto Seq1Eobject0Eventactionno = 99;
  static constexpr auto Seq1Eobject0Eventactionok = 100;
  static constexpr auto Seq1Eobject1 = 2;
  static constexpr auto Seq1Eobject1Eventactionno = 97;
  static constexpr auto Seq1Eobject1Eventactionok = 98;
  static constexpr auto Seq1Eobject2 = 3;
  static constexpr auto Seq1Eobject2Eventactionno = 95;
  static constexpr auto Seq1Eobject2Eventactionok = 96;
  static constexpr auto Seq1Eobject3 = 4;
  static constexpr auto Seq1Eobject3Eventactionno = 93;
  static constexpr auto Seq1Eobject3Eventactionok = 94;
  static constexpr auto Seq2Actor1 = 5;
  static constexpr auto Seq2Actor1Npctradeno = 91;
  static constexpr auto Seq2Actor1Npctradeok = 92;

public:
  SubFst056() : Sapphire::ScriptAPI::QuestScript( 65913 ){};
  ~SubFst056() = default;

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
          Scene00005( quest, player );
        break;
      }
      case Eobject0:
      {
        if( quest.getSeq() == Seq1 )
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
        if( quest.getSeq() == Seq1 )
          eventMgr().eventActionStart(
                  player, getId(), 0x02,
                  [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                    Scene00002( quest, player );
                  },
                  nullptr, 0 );
        break;
      }
      case Eobject2:
      {
        if( quest.getSeq() == Seq1 )
          eventMgr().eventActionStart(
                  player, getId(), 0x02,
                  [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                    Scene00003( quest, player );
                  },
                  nullptr, 0 );
        break;
      }
      case Eobject3:
      {
        if( quest.getSeq() == Seq1 )
          eventMgr().eventActionStart(
                  player, getId(), 0x02,
                  [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                    Scene00004( quest, player );
                  },
                  nullptr, 0 );
        break;
      }
    }
  }

  void onEventItem( World::Quest& quest, Entity::Player& player, uint64_t actorId ) override
  {
  }


private:
  void checkQuestCompletion( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().sendEventNotice( player, getId(), 0, 2, quest.getUI8AL(), 4 );
    if( quest.getUI8AL() >= 4 )
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
    eventMgr().playQuestScene( player, getId(), 0, NONE, bindSceneReturn( &SubFst056::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, NONE, bindSceneReturn( &SubFst056::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setBitFlag8( 1, true );
    quest.setUI8AL( quest.getUI8AL() + 1 );
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, NONE, bindSceneReturn( &SubFst056::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setBitFlag8( 2, true );
    quest.setUI8AL( quest.getUI8AL() + 1 );
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, NONE, bindSceneReturn( &SubFst056::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setBitFlag8( 3, true );
    quest.setUI8AL( quest.getUI8AL() + 1 );
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, NONE, bindSceneReturn( &SubFst056::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setBitFlag8( 4, true );
    quest.setUI8AL( quest.getUI8AL() + 1 );
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, NONE, bindSceneReturn( &SubFst056::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId() );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00093( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 93, NONE, bindSceneReturn( &SubFst056::Scene00093Return ) );
  }

  void Scene00093Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00094( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 94, NONE, bindSceneReturn( &SubFst056::Scene00094Return ) );
  }

  void Scene00094Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00095( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 95, NONE, bindSceneReturn( &SubFst056::Scene00095Return ) );
  }

  void Scene00095Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00096( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 96, NONE, bindSceneReturn( &SubFst056::Scene00096Return ) );
  }

  void Scene00096Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00097( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 97, NONE, bindSceneReturn( &SubFst056::Scene00097Return ) );
  }

  void Scene00097Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00098( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 98, NONE, bindSceneReturn( &SubFst056::Scene00098Return ) );
  }

  void Scene00098Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00099( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 99, NONE, bindSceneReturn( &SubFst056::Scene00099Return ) );
  }

  void Scene00099Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00100( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 100, NONE, bindSceneReturn( &SubFst056::Scene00100Return ) );
  }

  void Scene00100Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }
};

EXPOSE_SCRIPT( SubFst056 );