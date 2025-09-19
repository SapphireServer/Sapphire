// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include <Actor/Player.h>
#include <Actor/BNpc.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: SubFst015_00042
// Quest Name: Sylphic Gratitude
// Quest ID: 65578
// Start NPC: 1000286
// End NPC: 1000286

using namespace Sapphire;

class SubFst015 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // BitFlag8
  // UI8AL

  /// Countable Num: 6 Seq: 1 Event: 1 Listener: 2000020
  /// Countable Num: 1 Seq: 255 Event: 1 Listener: 2000021
  // Steps in this quest ( 0 is before accepting,
  // 1 is first, 255 means ready for turning it in
  enum Sequence : uint8_t
  {
    Seq0 = 0,
    Seq1 = 1,
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1000286;
  static constexpr auto Eobject0 = 2000020;
  static constexpr auto Eobject1 = 2000021;
  static constexpr auto Eobject2 = 2000022;
  static constexpr auto Eobject3 = 2000023;
  static constexpr auto Eobject4 = 2000024;
  static constexpr auto Eobject5 = 2000025;
  static constexpr auto EventActionSearch = 1;

public:
  SubFst015() : Sapphire::ScriptAPI::QuestScript( 65578 )
  {};

  ~SubFst015() = default;

  //////////////////////////////////////////////////////////////////////
  // Event Handlers
  void onTalk( World::Quest& quest, Entity::Player& player, uint64_t actorId ) override
  {
    switch( actorId )
    {
      case Actor0:
      {
        if( !player.hasQuest( getId() ) )
          Scene00000( quest, player );
        else
          Scene00007( quest, player );
        break;
      }

      case Eobject0:
      {
        eventMgr().eventActionStart( player, getId(), 0x01,
                                     [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional )
                                     {
                                       Scene00001( quest, player );
                                     },
                                     nullptr, 0 );
        break;
      }
      case Eobject1:
      {
        eventMgr().eventActionStart( player, getId(), 0x01,
                                     [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional )
                                     {
                                       Scene00002( quest, player );
                                     },
                                     nullptr, 0 );
        break;
      }
      case Eobject2:
      {
        eventMgr().eventActionStart( player, getId(), 0x01,
                                     [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional )
                                     {
                                       Scene00003( quest, player );
                                     },
                                     nullptr, 0 );
        break;
      }
      case Eobject3:
      {
        eventMgr().eventActionStart( player, getId(), 0x01,
                                     [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional )
                                     {
                                       Scene00004( quest, player );
                                     },
                                     nullptr, 0 );
        break;
      }
      case Eobject4:
      {
        eventMgr().eventActionStart( player, getId(), 0x01,
                                     [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional )
                                     {
                                       Scene00005( quest, player );
                                     },
                                     nullptr, 0 );
        break;
      }
      case Eobject5:
      {
        eventMgr().eventActionStart( player, getId(), 0x01,
                                     [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional )
                                     {
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
    quest.setUI8AL( quest.getUI8AL() + 1 );
    eventMgr().sendEventNotice( player, getId(), 0, 2, quest.getUI8AL(), 6 );

    if( quest.getUI8AL() >= 6 )
      quest.setSeq( SeqFinish );
  }

  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &SubFst015::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, HIDE_HOTBAR, bindSceneReturn( &SubFst015::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    Scene00100( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, HIDE_HOTBAR, bindSceneReturn( &SubFst015::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    Scene00098( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, HIDE_HOTBAR, bindSceneReturn( &SubFst015::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    Scene00096( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, HIDE_HOTBAR, bindSceneReturn( &SubFst015::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    Scene00094( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, HIDE_HOTBAR, bindSceneReturn( &SubFst015::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    Scene00092( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00006( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 6, HIDE_HOTBAR, bindSceneReturn( &SubFst015::Scene00006Return ) );
  }

  void Scene00006Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    Scene00090( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00007( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 7, HIDE_HOTBAR, bindSceneReturn( &SubFst015::Scene00007Return ) );
  }

  void Scene00007Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
    }

  }

  //////////////////////////////////////////////////////////////////////

  void Scene00089( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 89, HIDE_HOTBAR, bindSceneReturn( &SubFst015::Scene00089Return ) );
  }

  void Scene00089Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    //empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00090( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 90, HIDE_HOTBAR, bindSceneReturn( &SubFst015::Scene00090Return ) );
  }

  void Scene00090Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    checkQuestCompletion( quest, player );
    quest.setBitFlag8( 6, true );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00091( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 91, HIDE_HOTBAR, bindSceneReturn( &SubFst015::Scene00091Return ) );
  }

  void Scene00091Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    //empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00092( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 92, HIDE_HOTBAR, bindSceneReturn( &SubFst015::Scene00092Return ) );
  }

  void Scene00092Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    checkQuestCompletion( quest, player );
    quest.setBitFlag8( 5, true );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00093( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 93, HIDE_HOTBAR, bindSceneReturn( &SubFst015::Scene00093Return ) );
  }

  void Scene00093Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    //empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00094( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 94, HIDE_HOTBAR, bindSceneReturn( &SubFst015::Scene00094Return ) );
  }

  void Scene00094Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    checkQuestCompletion( quest, player );
    quest.setBitFlag8( 4, true );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00095( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 95, HIDE_HOTBAR, bindSceneReturn( &SubFst015::Scene00095Return ) );
  }

  void Scene00095Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    //empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00096( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 96, HIDE_HOTBAR, bindSceneReturn( &SubFst015::Scene00096Return ) );
  }

  void Scene00096Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    checkQuestCompletion( quest, player );
    quest.setBitFlag8( 3, true );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00097( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 97, HIDE_HOTBAR, bindSceneReturn( &SubFst015::Scene00097Return ) );
  }

  void Scene00097Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    //empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00098( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 98, HIDE_HOTBAR, bindSceneReturn( &SubFst015::Scene00098Return ) );
  }

  void Scene00098Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    checkQuestCompletion( quest, player );
    quest.setBitFlag8( 2, true );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00099( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 99, HIDE_HOTBAR, bindSceneReturn( &SubFst015::Scene00099Return ) );
  }

  void Scene00099Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    //empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00100( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 100, HIDE_HOTBAR, bindSceneReturn( &SubFst015::Scene00100Return ) );
  }

  void Scene00100Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    checkQuestCompletion( quest, player );
    quest.setBitFlag8( 1, true );
  }

};

EXPOSE_SCRIPT( SubFst015 );