// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>
#include "Manager/TerritoryMgr.h"
//Temporrary because QuestBattles are broken
#include "Manager/PlayerMgr.h"

// Quest Script: ClsArc005_00071
// Quest Name: Homecoming
// Quest ID: 65607
// Start NPC: 1000200
// End NPC: 1000200

using namespace Sapphire;

class ClsArc005 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // BitFlag8
  // UI8AL

  /// Countable Num: 1 Seq: 1 Event: 1 Listener: 1000204
  /// Countable Num: 1 Seq: 2 Event: 1 Listener: 1000199
  /// Countable Num: 1 Seq: 3 Event: 1 Listener: 2000951
  /// Countable Num: 1 Seq: 4 Event: 1 Listener: 1000534
  /// Countable Num: 1 Seq: 255 Event: 1 Listener: 2001840
  // Steps in this quest ( 0 is before accepting,
  // 1 is first, 255 means ready for turning it in
  enum Sequence : uint8_t
  {
    Seq0 = 0,
    Seq1 = 1,
    Seq2 = 2,
    Seq3 = 3,
    Seq4 = 4,
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1000200;
  static constexpr auto Actor1 = 1000204;
  static constexpr auto Actor2 = 1000199;
  static constexpr auto Actor3 = 1000534;
  static constexpr auto Actor4 = 1001284;
  static constexpr auto Actor5 = 1003025;
  static constexpr auto Actor6 = 1003026;
  static constexpr auto Eobject0 = 2000951;
  static constexpr auto Eobject1 = 2001840;
  static constexpr auto EventActionSearch = 1;
  static constexpr auto EventActionWaiting = 10;
  static constexpr auto LocActor5Action1 = 834;
  static constexpr auto LocPosActor5 = 3877820;
  static constexpr auto LocPosPc = 3877813;
  static constexpr auto Questbattle0 = 4;
  static constexpr auto Territorytype0 = 230;

public:
  ClsArc005() : Sapphire::ScriptAPI::QuestScript( 65607 )
  {};

  ~ClsArc005() = default;

  //////////////////////////////////////////////////////////////////////
  // Event Handlers
  void onTalk( World::Quest &quest, Entity::Player &player, uint64_t actorId ) override
  {
    switch( actorId )
    {
      case Actor0:
      {
        if( !player.hasQuest( getId()))
          Scene00000( quest, player );
        else if( quest.getSeq() == SeqFinish )
          Scene00010( quest, player );

        break;
      }
      case Actor1:
      {
        if( quest.getSeq() == Seq1 )
          Scene00002( quest, player );
        break;
      }
      case Actor2:
      {
        if( quest.getSeq() == Seq2 )
          Scene00003( quest, player );
        break;
      }
      case Actor3:
      {
        if( quest.getSeq() == Seq4 )
          Scene00006( quest, player );
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
      case Actor6:
      {
        break;
      }
      case Eobject0:
      {
        eventMgr().eventActionStart( player, getId(), 0x0A,
                                     [ & ]( Entity::Player &player, uint32_t eventId, uint64_t additional )
                                     {
                                       Scene00004( quest, player );
                                       eventMgr().sendEventNotice( player, getId(), 2, 2, 0, 0 );
                                     },
                                     nullptr, 0 );
        break;
      }
    }
  }


private:
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest &quest, Entity::Player &player )
  {
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &ClsArc005::Scene00000Return ) );
  }

  void Scene00000Return( World::Quest &quest, Entity::Player &player, const Event::SceneResult &result )
  {
    if( result.getResult( 0 ) == 1 ) // accept quest
    {
      Scene00001( quest, player );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00001( World::Quest &quest, Entity::Player &player )
  {
    eventMgr().playQuestScene( player, getId(), 1, HIDE_HOTBAR, bindSceneReturn( &ClsArc005::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest &quest, Entity::Player &player, const Event::SceneResult &result )
  {
    quest.setSeq( Seq1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest &quest, Entity::Player &player )
  {
    eventMgr().playQuestScene( player, getId(), 2, HIDE_HOTBAR, bindSceneReturn( &ClsArc005::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest &quest, Entity::Player &player, const Event::SceneResult &result )
  {
    eventMgr().sendEventNotice( player, getId(), 0, 2, 0, 0 );
    quest.setSeq( Seq2 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest &quest, Entity::Player &player )
  {
    eventMgr().playQuestScene( player, getId(), 3, HIDE_HOTBAR, bindSceneReturn( &ClsArc005::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest &quest, Entity::Player &player, const Event::SceneResult &result )
  {
    eventMgr().sendEventNotice( player, getId(), 1, 2, 0, 0 );
    quest.setSeq( Seq3 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest &quest, Entity::Player &player )
  {
    eventMgr().playQuestScene( player, getId(), 4, HIDE_HOTBAR, bindSceneReturn( &ClsArc005::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest &quest, Entity::Player &player, const Event::SceneResult &result )
  {
    Scene00005( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest &quest, Entity::Player &player )
  {
    eventMgr().playQuestScene( player, getId(), 5, SET_EOBJ_BASE | HIDE_HOTBAR | INVIS_EOBJ, bindSceneReturn( &ClsArc005::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest &quest, Entity::Player &player, const Event::SceneResult &result )
  {
    quest.setSeq( Seq4 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00006( World::Quest &quest, Entity::Player &player )
  {
    eventMgr().playQuestScene( player, getId(), 6, HIDE_HOTBAR, bindSceneReturn( &ClsArc005::Scene00006Return ) );
  }

  void Scene00006Return( World::Quest &quest, Entity::Player &player, const Event::SceneResult &result )
  {
    Scene00007( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00007( World::Quest &quest, Entity::Player &player )
  {
    eventMgr().playQuestScene( player, getId(), 7, HIDE_HOTBAR, bindSceneReturn( &ClsArc005::Scene00007Return ) );
  }

  void Scene00007Return( World::Quest &quest, Entity::Player &player, const Event::SceneResult &result )
  {
    if( result.getResult( 0 ) == 1 )
    {
      //Questbattles be broken
      quest.setSeq( SeqFinish );
      Sapphire::World::Manager::PlayerMgr::sendDebug(player, "QuestBattle content is currently broken. The fight has been skipped for you.");
      /*auto& pTeriMgr = Common::Service< Sapphire::World::Manager::TerritoryMgr >::ref();

      eventMgr().eventFinish( player, result.eventId, 0 );
      pTeriMgr.createAndJoinQuestBattle( player, Questbattle0 );*/
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00008( World::Quest &quest, Entity::Player &player )
  {
    eventMgr().playQuestScene( player, getId(), 8, HIDE_HOTBAR, bindSceneReturn( &ClsArc005::Scene00008Return ) );
  }

  void Scene00008Return( World::Quest &quest, Entity::Player &player, const Event::SceneResult &result )
  {
    //Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00009( World::Quest &quest, Entity::Player &player )
  {
    eventMgr().playQuestScene( player, getId(), 9, HIDE_HOTBAR, bindSceneReturn( &ClsArc005::Scene00009Return ) );
  }

  void Scene00009Return( World::Quest &quest, Entity::Player &player, const Event::SceneResult &result )
  {
    //Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00010( World::Quest &quest, Entity::Player &player )
  {
    eventMgr().playQuestScene( player, getId(), 10, HIDE_HOTBAR, bindSceneReturn( &ClsArc005::Scene00010Return ) );
  }

  void Scene00010Return( World::Quest &quest, Entity::Player &player, const Event::SceneResult &result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
    }

  }

};

EXPOSE_SCRIPT( ClsArc005 );