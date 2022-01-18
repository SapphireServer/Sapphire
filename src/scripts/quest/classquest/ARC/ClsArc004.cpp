// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include "Manager/EventMgr.h"
#include "Manager/TerritoryMgr.h"
#include <Actor/Player.h>
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: ClsArc004_00070
// Quest Name: To Catch a Poacher
// Quest ID: 65606
// Start NPC: 1000200
// End NPC: 1000200

using namespace Sapphire;

class ClsArc004 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // BitFlag8
  // UI8AL

  /// Countable Num: 1 Seq: 1 Event: 1 Listener: 1000590
  /// Countable Num: 3 Seq: 2 Event: 1 Listener: 2000947
  /// Countable Num: 1 Seq: 3 Event: 1 Listener: 2000948
  /// Countable Num: 0 Seq: 4 Event: 1 Listener: 2000949
  /// Countable Num: 1 Seq: 5 Event: 1 Listener: 2001105
  /// Countable Num: 1 Seq: 255 Event: 1 Listener: 2000136
  // Steps in this quest ( 0 is before accepting,
  // 1 is first, 255 means ready for turning it in
  enum Sequence : uint8_t
  {
    Seq0 = 0,
    Seq1 = 1,
    Seq2 = 2,
    Seq3 = 3,
    Seq4 = 4,
    Seq5 = 5,
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1000200;
  static constexpr auto Actor1 = 1000590;
  static constexpr auto Actor2 = 1000731;
  static constexpr auto Actor3 = 1000732;
  static constexpr auto Actor4 = 1000199;
  static constexpr auto Actor5 = 1000204;
  static constexpr auto Eobject0 = 2000947;
  static constexpr auto Eobject1 = 2000948;
  static constexpr auto Eobject2 = 2000949;
  static constexpr auto Eobject3 = 2001105;
  static constexpr auto Eobject4 = 2000136;
  static constexpr auto EventActionGatherMiddle = 7;
  static constexpr auto EventActionSearch = 1;
  static constexpr auto EventActionWaiting = 10;
  static constexpr auto LocPosActor5 = 3875531;
  static constexpr auto Questbattle0 = 5;
  static constexpr auto Seq0Actor0Lq = 90;
  static constexpr auto Territorytype0 = 229;

public:
  ClsArc004() : Sapphire::ScriptAPI::QuestScript( 65606 ){};
  ~ClsArc004() = default;

  //////////////////////////////////////////////////////////////////////
  // Event Handlers
  void onTalk( World::Quest &quest, Entity::Player &player, uint64_t actorId ) override
  {
    switch( actorId )
    {
      case Actor0:
      {
        if( quest.getSeq() == Seq0 )
          Scene00000( quest, player );
        else if( quest.getSeq() == SeqFinish )
          Scene00021( quest, player );

        break;
      }
      case Actor1:
      {
        if( quest.getSeq() == Seq1 )
          Scene00002( quest, player );
        else if( quest.getSeq() == Seq5 )//Master claims we can't talk with this NPC
          Scene00018( quest, player );

        break;
      }
      case Actor2:
      {
        if( quest.getSeq() == Seq5 )
          Scene00020( quest, player );
        break;
      }
      case Actor3:
      {
        if( quest.getSeq() == Seq5 )
          Scene00019( quest, player );
        break;
      }
      case Actor4:
      {
        break;
      }
      case Actor5:
      {
        break;
      }
      case Eobject0:
      {
        eventMgr().eventActionStart(
                player, getId(), 0x07,
                [ & ]( Entity::Player &player, uint32_t eventId, uint64_t additional ) {
                  Scene00003( quest, player );
                },
                nullptr, 0 );
        break;
      }
      case Eobject1:
      {
        eventMgr().eventActionStart(
                player, getId(), 0x07,
                [ & ]( Entity::Player &player, uint32_t eventId, uint64_t additional ) {
                  Scene00004( quest, player );
                },
                nullptr, 0 );
        break;
      }
      case Eobject2:
      {
        eventMgr().eventActionStart(
                player, getId(), 0x07,
                [ & ]( Entity::Player &player, uint32_t eventId, uint64_t additional ) {
                  Scene00005( quest, player );
                },
                nullptr, 0 );
        break;
      }
      case Eobject3:
      {
        eventMgr().eventActionStart(
                player, getId(), 0x0A,
                [ & ]( Entity::Player &player, uint32_t eventId, uint64_t additional ) {
                  Scene00013( quest, player );
                  eventMgr().sendEventNotice( player, getId(), 2, 2, 0, 0 );
                },
                nullptr, 0 );
        break;
      }
      case Eobject4:
      {
        eventMgr().eventActionStart(
                player, getId(), 0x01,
                [ & ]( Entity::Player &player, uint32_t eventId, uint64_t additional ) {
                  Scene00015( quest, player );
                },
                nullptr, 0 );
        break;
      }
    }
  }


private:
  void checkQuestCompletion( World::Quest &quest, Entity::Player &player )
  {
    auto currentCC = quest.getUI8AL();

    eventMgr().sendEventNotice( player, getId(), 1, 2, currentCC + 1, 3 );

    if( currentCC + 1 >= 3 )
    {
      quest.setSeq( Seq3 );
      quest.setUI8AL( 0 );
    }
    else
    {
      quest.setUI8AL( currentCC + 1 );
    }
  }

  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest &quest, Entity::Player &player )
  {
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &ClsArc004::Scene00000Return ) );
  }

  void Scene00000Return( World::Quest &quest, Entity::Player &player, const Event::SceneResult &result )
  {
    if( result.getResult( 0 ) == 1 )// accept quest
    {
      Scene00001( quest, player );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00001( World::Quest &quest, Entity::Player &player )
  {
    eventMgr().playQuestScene( player, getId(), 1, SET_EOBJ_BASE | HIDE_HOTBAR | INVIS_EOBJ, bindSceneReturn( &ClsArc004::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest &quest, Entity::Player &player, const Event::SceneResult &result )
  {
    quest.setSeq( Seq1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest &quest, Entity::Player &player )
  {
    eventMgr().playQuestScene( player, getId(), 2, SET_EOBJ_BASE | HIDE_HOTBAR | INVIS_EOBJ, bindSceneReturn( &ClsArc004::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest &quest, Entity::Player &player, const Event::SceneResult &result )
  {
    eventMgr().sendEventNotice( player, getId(), 0, 2, 0, 0 );
    quest.setSeq( Seq2 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest &quest, Entity::Player &player )
  {
    eventMgr().playQuestScene( player, getId(), 3, HIDE_HOTBAR, bindSceneReturn( &ClsArc004::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest &quest, Entity::Player &player, const Event::SceneResult &result )
  {
    quest.setBitFlag8( 1, true );
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest &quest, Entity::Player &player )
  {
    eventMgr().playQuestScene( player, getId(), 4, HIDE_HOTBAR, bindSceneReturn( &ClsArc004::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest &quest, Entity::Player &player, const Event::SceneResult &result )
  {
    quest.setBitFlag8( 2, true );
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest &quest, Entity::Player &player )
  {
    eventMgr().playQuestScene( player, getId(), 5, HIDE_HOTBAR, bindSceneReturn( &ClsArc004::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest &quest, Entity::Player &player, const Event::SceneResult &result )
  {
    quest.setBitFlag8( 3, true );
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00006( World::Quest &quest, Entity::Player &player )
  {
    eventMgr().playQuestScene( player, getId(), 6, HIDE_HOTBAR, bindSceneReturn( &ClsArc004::Scene00006Return ) );
  }

  void Scene00006Return( World::Quest &quest, Entity::Player &player, const Event::SceneResult &result )
  {
    //Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00007( World::Quest &quest, Entity::Player &player )
  {
    eventMgr().playQuestScene( player, getId(), 7, HIDE_HOTBAR, bindSceneReturn( &ClsArc004::Scene00007Return ) );
  }

  void Scene00007Return( World::Quest &quest, Entity::Player &player, const Event::SceneResult &result )
  {
    //Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00008( World::Quest &quest, Entity::Player &player )
  {
    eventMgr().playQuestScene( player, getId(), 8, HIDE_HOTBAR, bindSceneReturn( &ClsArc004::Scene00008Return ) );
  }

  void Scene00008Return( World::Quest &quest, Entity::Player &player, const Event::SceneResult &result )
  {
    //Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00009( World::Quest &quest, Entity::Player &player )
  {
    eventMgr().playQuestScene( player, getId(), 9, HIDE_HOTBAR, bindSceneReturn( &ClsArc004::Scene00009Return ) );
  }

  void Scene00009Return( World::Quest &quest, Entity::Player &player, const Event::SceneResult &result )
  {
    //Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00010( World::Quest &quest, Entity::Player &player )
  {
    eventMgr().playQuestScene( player, getId(), 10, HIDE_HOTBAR, bindSceneReturn( &ClsArc004::Scene00010Return ) );
  }

  void Scene00010Return( World::Quest &quest, Entity::Player &player, const Event::SceneResult &result )
  {
    //Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00011( World::Quest &quest, Entity::Player &player )
  {
    eventMgr().playQuestScene( player, getId(), 11, HIDE_HOTBAR, bindSceneReturn( &ClsArc004::Scene00011Return ) );
  }

  void Scene00011Return( World::Quest &quest, Entity::Player &player, const Event::SceneResult &result )
  {
    //Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00012( World::Quest &quest, Entity::Player &player )
  {
    eventMgr().playQuestScene( player, getId(), 12, HIDE_HOTBAR, bindSceneReturn( &ClsArc004::Scene00012Return ) );
  }

  void Scene00012Return( World::Quest &quest, Entity::Player &player, const Event::SceneResult &result )
  {
    //Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00013( World::Quest &quest, Entity::Player &player )
  {
    eventMgr().playQuestScene( player, getId(), 13, SET_EOBJ_BASE | HIDE_HOTBAR | INVIS_EOBJ, bindSceneReturn( &ClsArc004::Scene00013Return ) );
  }

  void Scene00013Return( World::Quest &quest, Entity::Player &player, const Event::SceneResult &result )
  {
    quest.setSeq( Seq4 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00014( World::Quest &quest, Entity::Player &player )
  {
    eventMgr().playQuestScene( player, getId(), 14, HIDE_HOTBAR, bindSceneReturn( &ClsArc004::Scene00014Return ) );
  }

  void Scene00014Return( World::Quest &quest, Entity::Player &player, const Event::SceneResult &result )
  {
    //Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00015( World::Quest &quest, Entity::Player &player )
  {
    eventMgr().playQuestScene( player, getId(), 15, HIDE_HOTBAR, bindSceneReturn( &ClsArc004::Scene00015Return ) );
  }

  void Scene00015Return( World::Quest &quest, Entity::Player &player, const Event::SceneResult &result )
  {
    Scene00016( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00016( World::Quest &quest, Entity::Player &player )
  {
    eventMgr().playQuestScene( player, getId(), 16, HIDE_HOTBAR, bindSceneReturn( &ClsArc004::Scene00016Return ) );
  }

  void Scene00016Return( World::Quest &quest, Entity::Player &player, const Event::SceneResult &result )
  {
    if( result.getResult( 0 ) == 1 )
    {
      //TODO: QuestBattles are broken
      playerMgr().sendUrgent( player, "QuestBattle content is currently broken. The fight has been skipped for you." );
      eventMgr().sendEventNotice( player, getId(), 3, 0 );
      quest.setSeq( Seq5 );
      quest.setBitFlag8( 1, false );
      quest.setBitFlag8( 2, false );
      quest.setBitFlag8( 3, false );

      /*auto& pTeriMgr = Common::Service< Sapphire::World::Manager::TerritoryMgr >::ref();

      eventMgr().eventFinish( player, result.eventId, 0 );
      pTeriMgr.createAndJoinQuestBattle( player, Questbattle0 );*/
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00017( World::Quest &quest, Entity::Player &player )
  {
    eventMgr().playQuestScene( player, getId(), 17, HIDE_HOTBAR, bindSceneReturn( &ClsArc004::Scene00017Return ) );
  }

  void Scene00017Return( World::Quest &quest, Entity::Player &player, const Event::SceneResult &result )
  {
    //Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00018( World::Quest &quest, Entity::Player &player )
  {
    eventMgr().playQuestScene( player, getId(), 18, HIDE_HOTBAR, bindSceneReturn( &ClsArc004::Scene00018Return ) );
  }

  void Scene00018Return( World::Quest &quest, Entity::Player &player, const Event::SceneResult &result )
  {
    eventMgr().sendEventNotice( player, getId(), 4, 2, 0, 0 );
    quest.setSeq( SeqFinish );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00019( World::Quest &quest, Entity::Player &player )
  {
    eventMgr().playQuestScene( player, getId(), 19, HIDE_HOTBAR, bindSceneReturn( &ClsArc004::Scene00019Return ) );
  }

  void Scene00019Return( World::Quest &quest, Entity::Player &player, const Event::SceneResult &result )
  {
    //Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00020( World::Quest &quest, Entity::Player &player )
  {
    eventMgr().playQuestScene( player, getId(), 20, HIDE_HOTBAR, bindSceneReturn( &ClsArc004::Scene00020Return ) );
  }

  void Scene00020Return( World::Quest &quest, Entity::Player &player, const Event::SceneResult &result )
  {
    //Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00021( World::Quest &quest, Entity::Player &player )
  {
    eventMgr().playQuestScene( player, getId(), 21, HIDE_HOTBAR, bindSceneReturn( &ClsArc004::Scene00021Return ) );
  }

  void Scene00021Return( World::Quest &quest, Entity::Player &player, const Event::SceneResult &result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
    }
  }
};

EXPOSE_SCRIPT( ClsArc004 );