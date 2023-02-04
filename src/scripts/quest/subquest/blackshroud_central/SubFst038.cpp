// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include "Manager/EventMgr.h"
#include <Actor/Player.h>
#include <Actor/BNpc.h>
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: SubFst038_00175
// Quest Name: Surveying the Damage
// Quest ID: 65711
// Start NPC: 1000449
// End NPC: 1000685

using namespace Sapphire;

class SubFst038 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // BitFlag8
  // UI8AL
  // UI8BH //Survey Records
  // UI8BL //Surveyor's Rope (2?)
  // UI8CH
  // UI8CL
  // UI8DH

  /// Countable Num: 1 Seq: 1 Event: 1 Listener: 2000141
  /// Countable Num: 2 Seq: 1 Event: 1 Listener: 2000147
  /// Countable Num: 1 Seq: 1 Event: 1 Listener: 2000148
  /// Countable Num: 1 Seq: 255 Event: 1 Listener: 2000149
  // Steps in this quest ( 0 is before accepting,
  // 1 is first, 255 means ready for turning it in
  enum Sequence : uint8_t
  {
    Seq0 = 0,
    Seq1 = 1,
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1000449;  //Monranguin
  static constexpr auto Actor1 = 1000685;  //Pauline
  static constexpr auto Eobject0 = 2000141;//Survey Records
  static constexpr auto Eobject1 = 2000147;//Surveyor's Instruments (X24Y23)
  static constexpr auto Eobject2 = 2000148;//Surveyor's Instruments (X24Y24)
  static constexpr auto Eobject3 = 2000149;//Surveyor's Rope
  static constexpr auto EventActionSearch = 1;
  static constexpr auto Item0 = 2000141;
  static constexpr auto Item1 = 2000146;
  static constexpr auto Item2 = 2000147;

public:
  SubFst038() : Sapphire::ScriptAPI::QuestScript( 65711 ){};
  ~SubFst038() = default;

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
    if( quest.getUI8AL() >= 1 && quest.getUI8BH() >= 2 && quest.getUI8BL() >= 1 )
    {
      //quest.setUI8CH( 1 );
      //quest.setUI8CL( 1 );
      //quest.setUI8DH( 1 );
      quest.setSeq( SeqFinish );
      /* quest.setBitFlag8( 2, false );
      quest.setBitFlag8( 3, false );
      quest.setUI8AL( 0 );
      quest.setUI8BH( 0 );
      quest.setUI8BL( 0 ); */
    }
  }
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, NONE, bindSceneReturn( &SubFst038::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, NONE, bindSceneReturn( &SubFst038::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 0, 0 );
    quest.setUI8AL( 1 );
    quest.setUI8CH( 1 );
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, NONE, bindSceneReturn( &SubFst038::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 1, 2, quest.getUI8BH() + 1, 2 );
    quest.setUI8BH( quest.getUI8BH() + 1 );
    quest.setUI8CL( quest.getUI8CL() + 1 );
    quest.setBitFlag8( 2, true );//Makes the Eobj fade out
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, NONE, bindSceneReturn( &SubFst038::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 1, 2, quest.getUI8BH() + 1, 2 );
    quest.setUI8BH( quest.getUI8BH() + 1 );
    quest.setUI8CL( quest.getUI8CL() + 1 );
    quest.setBitFlag8( 3, true );//Makes the Eobj fade out
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, NONE, bindSceneReturn( &SubFst038::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 2, 0 );
    quest.setUI8BL( 1 );
    quest.setUI8DH( 1 );
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, NONE, bindSceneReturn( &SubFst038::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    playerMgr().sendUrgent( player, "Handing in the items is weird. This has been skipped." );
    Scene00092( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00091( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 91, NONE, bindSceneReturn( &SubFst038::Scene00091Return ) );
  }

  void Scene00091Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00092( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 92, NONE, bindSceneReturn( &SubFst038::Scene00092Return ) );
  }

  void Scene00092Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00093( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 93, NONE, bindSceneReturn( &SubFst038::Scene00093Return ) );
  }

  void Scene00093Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00094( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 94, NONE, bindSceneReturn( &SubFst038::Scene00094Return ) );
  }

  void Scene00094Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00095( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 95, NONE, bindSceneReturn( &SubFst038::Scene00095Return ) );
  }

  void Scene00095Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00096( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 96, NONE, bindSceneReturn( &SubFst038::Scene00096Return ) );
  }

  void Scene00096Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00097( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 97, NONE, bindSceneReturn( &SubFst038::Scene00097Return ) );
  }

  void Scene00097Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00098( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 98, NONE, bindSceneReturn( &SubFst038::Scene00098Return ) );
  }

  void Scene00098Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00099( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 99, NONE, bindSceneReturn( &SubFst038::Scene00099Return ) );
  }

  void Scene00099Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00100( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 100, NONE, bindSceneReturn( &SubFst038::Scene00100Return ) );
  }

  void Scene00100Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }
};

EXPOSE_SCRIPT( SubFst038 );