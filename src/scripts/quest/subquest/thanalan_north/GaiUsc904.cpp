// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include "Manager/EventMgr.h"
#include <Actor/Player.h>
#include <ScriptObject.h>
#include <Service.h>

#include "Actor/BNpc.h"

// Quest Script: GaiUsc904_01039
// Quest Name: The Ladle in the Darkness
// Quest ID: 66575
// Start NPC: 1006638
// End NPC: 1006638

using namespace Sapphire;

class GaiUsc904 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // BitFlag8
  // UI8AH
  // UI8AL
  // UI8BH
  // UI8BL
  // UI8CH

  /// Countable Num: 0 Seq: 1 Event: 9 Listener: 173
  /// Countable Num: 0 Seq: 2 Event: 1 Listener: 2002256
  /// Countable Num: 0 Seq: 3 Event: 1 Listener: 2002256
  /// Countable Num: 0 Seq: 4 Event: 1 Listener: 2002256
  /// Countable Num: 0 Seq: 5 Event: 1 Listener: 1006639
  /// Countable Num: 0 Seq: 255 Event: 1 Listener: 1006640
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
  static constexpr auto Actor0 = 1006638;//Cracked FIst
  static constexpr auto Actor1 = 1006639;//Zezeragi
  static constexpr auto Actor2 = 1006640;//
  static constexpr auto Actor3 = 1006641;//
  static constexpr auto Enemy0 = 173;
  static constexpr auto Eobject0 = 2002256;//Bubbling Cauldron
  static constexpr auto EventActionSearch = 1;
  static constexpr auto EventActionWaitingShor = 11;
  static constexpr auto Item0 = 2000785;
  static constexpr auto Item1 = 2000786;

public:
  GaiUsc904() : Sapphire::ScriptAPI::QuestScript( 66575 ){};
  ~GaiUsc904() = default;

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
          Scene00014( quest, player );
        break;
      }
      case Actor1:
      {
        if( quest.getSeq() == Seq5 )
          Scene00008( quest, player );
        break;
      }
      case Actor2:
      {
        if( quest.getSeq() == Seq5 )
          Scene00010( quest, player );
        break;
      }
      case Actor3:
      {
        if( quest.getSeq() == Seq5 )
          Scene00012( quest, player );
        break;
      }
      case Eobject0:
      {
        if( quest.getSeq() == Seq2 )
          Scene00002( quest, player );
        else if(quest.getSeq() == Seq3)
          eventMgr().eventActionStart(
                  player, getId(), EventActionWaitingShor,
                  [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                    Scene00004( quest, player );
                  },
                  nullptr, 0 );
        else if( quest.getSeq() == Seq4 )
          eventMgr().eventActionStart(
                  player, getId(), EventActionWaitingShor,
                  [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                    Scene00006( quest, player );
                  },
                  nullptr, 0 );
        break;
      }
    }
  }

  void onBNpcKill( World::Quest& quest, Entity::BNpc& bnpc, Entity::Player& player ) override
  {
    switch( bnpc.getBNpcBaseId() )
    {
      case Enemy0:
      {
        quest.setUI8BH( quest.getUI8BH() + 1 );
        eventMgr().sendEventNotice( player, getId(), 0, 2, quest.getUI8BH(), 3 );

        if( quest.getUI8BH() >= 3 )
        {
          quest.setSeq( Seq2 );
        }
        break;
      }
    }
  }

private:
  void checkQuestCompletion( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().sendEventNotice( player, getId(), 4, 2, quest.getUI8AH(), 3 );
    if( quest.getUI8AH() >= 3 )
    {
      quest.setUI8AH( 0 );
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
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &GaiUsc904::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, HIDE_HOTBAR, bindSceneReturn( &GaiUsc904::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( Seq1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, HIDE_HOTBAR, bindSceneReturn( &GaiUsc904::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      Scene00003( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, HIDE_HOTBAR, bindSceneReturn( &GaiUsc904::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8BH( 0 );
    eventMgr().sendEventNotice( player, getId(), 1, 0 );
    quest.setSeq( Seq3 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, HIDE_HOTBAR, bindSceneReturn( &GaiUsc904::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 2, 0 );
    quest.setSeq( Seq4 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, HIDE_HOTBAR, bindSceneReturn( &GaiUsc904::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00006( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 6, HIDE_HOTBAR, bindSceneReturn( &GaiUsc904::Scene00006Return ) );
  }

  void Scene00006Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 3, 0 );
    quest.setSeq( Seq5 );
    quest.setUI8CH( 3 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00007( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 7, HIDE_HOTBAR, bindSceneReturn( &GaiUsc904::Scene00007Return ) );
  }

  void Scene00007Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00008( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 8, HIDE_HOTBAR, bindSceneReturn( &GaiUsc904::Scene00008Return ) );
  }

  void Scene00008Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      Scene00009( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00009( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 9, HIDE_HOTBAR, bindSceneReturn( &GaiUsc904::Scene00009Return ) );
  }

  void Scene00009Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8AH( quest.getUI8AH() + 1 );
    quest.setUI8CH( quest.getUI8CH() - 1 );
    quest.setUI8AL( 1 );
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00010( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 10, HIDE_HOTBAR, bindSceneReturn( &GaiUsc904::Scene00010Return ) );
  }

  void Scene00010Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      Scene00011( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00011( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 11, HIDE_HOTBAR, bindSceneReturn( &GaiUsc904::Scene00011Return ) );
  }

  void Scene00011Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8AH( quest.getUI8AH() + 1 );
    quest.setUI8CH( quest.getUI8CH() - 1 );
    quest.setUI8BH( 1 );
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00012( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 12, HIDE_HOTBAR, bindSceneReturn( &GaiUsc904::Scene00012Return ) );
  }

  void Scene00012Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      Scene00013( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00013( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 13, HIDE_HOTBAR, bindSceneReturn( &GaiUsc904::Scene00013Return ) );
  }

  void Scene00013Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8AH( quest.getUI8AH() + 1 );
    quest.setUI8CH( quest.getUI8CH() - 1 );
    quest.setUI8BL( 1 );
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00014( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 14, HIDE_HOTBAR, bindSceneReturn( &GaiUsc904::Scene00014Return ) );
  }

  void Scene00014Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
    }
  }
};

EXPOSE_SCRIPT( GaiUsc904 );