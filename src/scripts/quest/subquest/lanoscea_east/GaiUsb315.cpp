// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include "Manager/EventMgr.h"
#include <Actor/Player.h>
#include <Actor/BNpc.h>
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: GaiUsb315_00856
// Quest Name: As You Wish
// Quest ID: 66392
// Start NPC: 1006266
// End NPC: 1006341

using namespace Sapphire;

class GaiUsb315 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // BitFlag8
  // UI8AH
  // UI8AL
  // UI8BH
  // UI8BL

  /// Countable Num: 0 Seq: 1 Event: 1 Listener: 2002083
  /// Countable Num: 0 Seq: 255 Event: 1 Listener: 2002084
  // Steps in this quest ( 0 is before accepting,
  // 1 is first, 255 means ready for turning it in
  enum Sequence : uint8_t
  {
    Seq0 = 0,
    Seq1 = 1,
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1006266;//Wheiskaet
  static constexpr auto Actor1 = 1006341;//Riol
  static constexpr auto Eobject0 = 2002083;
  static constexpr auto Eobject1 = 2002084;
  static constexpr auto Eobject2 = 2002085;
  static constexpr auto EventAction = 30;

public:
  GaiUsb315() : Sapphire::ScriptAPI::QuestScript( 66392 ){};
  ~GaiUsb315() = default;

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
          Scene00008( quest, player );
        break;
      }
      case Eobject0:
      {
        eventMgr().eventActionStart(
                player, getId(), EventAction,
                [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                  Scene00002( quest, player );
                },
                nullptr, 0 );
        break;
      }
      case Eobject1:
      {
        eventMgr().eventActionStart(
                player, getId(), EventAction,
                [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                  Scene00004( quest, player );
                },
                nullptr, 0 );
        break;
      }
      case Eobject2:
      {
        eventMgr().eventActionStart(
                player, getId(), EventAction,
                [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                  Scene00006( quest, player );
                },
                nullptr, 0 );
        break;
      }
    }
  }


private:
  void checkQuestCompletion( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().sendEventNotice( player, getId(), 0, 2, quest.getUI8AH(), 3 );
    if( quest.getUI8AH() >= 3 )
    {
      quest.setSeq( SeqFinish );
    }
  }
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &GaiUsb315::Scene00000Return ) );
  }

  void Scene00000Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )// accept quest
    {
      Scene00001( quest, player );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00001( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 1, HIDE_HOTBAR, bindSceneReturn( &GaiUsb315::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( Seq1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, HIDE_HOTBAR, bindSceneReturn( &GaiUsb315::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8AL( 1 );                   //Hide EObj
    quest.setUI8AH( quest.getUI8AH() + 1 );//Increment Journal
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, HIDE_HOTBAR, bindSceneReturn( &GaiUsb315::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, HIDE_HOTBAR, bindSceneReturn( &GaiUsb315::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8BH( 1 );                   //Hide EObj
    quest.setUI8AH( quest.getUI8AH() + 1 );//Increment Journal
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, HIDE_HOTBAR, bindSceneReturn( &GaiUsb315::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00006( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 6, HIDE_HOTBAR, bindSceneReturn( &GaiUsb315::Scene00006Return ) );
  }

  void Scene00006Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8BL( 1 );                   //Hide EObj
    quest.setUI8AH( quest.getUI8AH() + 1 );//Increment Journal
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00007( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 7, HIDE_HOTBAR, bindSceneReturn( &GaiUsb315::Scene00007Return ) );
  }

  void Scene00007Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00008( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 8, HIDE_HOTBAR, bindSceneReturn( &GaiUsb315::Scene00008Return ) );
  }

  void Scene00008Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId() );
    }
  }
};

EXPOSE_SCRIPT( GaiUsb315 );