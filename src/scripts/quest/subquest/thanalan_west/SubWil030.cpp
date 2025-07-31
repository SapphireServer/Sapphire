// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include "Manager/QuestMgr.h"
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: SubWil030_00222
// Quest Name: Nor Rain nor Heat nor Gloom of Night
// Quest ID: 65758
// Start NPC: 1001992 (Oswell)
// End NPC: 1001992 (Oswell)

using namespace Sapphire;

class SubWil030 : public Sapphire::ScriptAPI::QuestScript
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

    /// Countable Num: 3 Seq: 1 Event: 1 Listener: 2000738
    /// Countable Num: 1 Seq: 255 Event: 1 Listener: 2000739
    // Steps in this quest ( 0 is before accepting, 
    // 1 is first, 255 means ready for turning it in
    enum Sequence : uint8_t
    {
      Seq0 = 0,
      Seq1 = 1,
      SeqFinish = 255,
    };

    // Entities found in the script data of the quest
    static constexpr auto Actor0 = 1001992; // Oswell ( Pos: 223.162994 52.017899 141.253006  Teri: 140 )
    static constexpr auto Eobject0 = 2000738; // Eatc Cargo Crate ( Pos: 217.117996 60.471401 121.538002  Teri: 140 )
    static constexpr auto Eobject1 = 2000739; // Eatc Cargo Crate ( Pos: 212.964996 52.824001 148.000000  Teri: 140 )
    static constexpr auto Eobject2 = 2000740; // Eatc Cargo Crate ( Pos: 228.449005 55.569199 172.082993  Teri: 140 )
    static constexpr auto EventActionSearchShort = 2;
    static constexpr auto Item0 = 2000148;

  public:
    SubWil030() : Sapphire::ScriptAPI::QuestScript( 65758 ){}; 
    ~SubWil030() = default; 

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
          Scene00010( quest, player );
        break;
      }
      case Eobject0:
      {
        eventMgr().eventActionStart(
                player, getId(), EventActionSearchShort,
                [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                  Scene00008( quest, player );
                },
                nullptr, 0 );
        break;
      }
      case Eobject1:
      {
        eventMgr().eventActionStart(
                player, getId(), EventActionSearchShort,
                [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                  Scene00006( quest, player );
                },
                nullptr, 0 );
        break;
      }
      case Eobject2:
      {
        eventMgr().eventActionStart(
                player, getId(), EventActionSearchShort,
                [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                  Scene00004( quest, player );
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

  void onCompletitionCheck(World::Quest& quest, Entity::Player& player)
  {
    if( quest.getSeq() != Seq1 )
      return;

    quest.setUI8AH( quest.getUI8AH() + 1 );
    quest.setUI8CH( quest.getUI8CH() + 1 );

    eventMgr().sendNotice( player, getId(), 0, { quest.getUI8AH(), 3, player.getQuestItemIcon( Item0 ) } );
    //eventMgr().sendEventNotice( player, getId(), 0, 2, quest.getUI8AH(), 3 );

    if( quest.getUI8AH() >= 3 )
    {
      quest.setSeq( SeqFinish );
      quest.setUI8BH( 3 );
    }
  }

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, NONE, bindSceneReturn( &SubWil030::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, NONE, bindSceneReturn( &SubWil030::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, NONE, bindSceneReturn( &SubWil030::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, NONE, bindSceneReturn( &SubWil030::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, NONE, bindSceneReturn( &SubWil030::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setBitFlag8( 3, true );
    onCompletitionCheck( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, NONE, bindSceneReturn( &SubWil030::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

  }

  //////////////////////////////////////////////////////////////////////

  void Scene00006( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 6, NONE, bindSceneReturn( &SubWil030::Scene00006Return ) );
  }

  void Scene00006Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setBitFlag8( 2, true );
    onCompletitionCheck( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00007( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 7, NONE, bindSceneReturn( &SubWil030::Scene00007Return ) );
  }

  void Scene00007Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

  }

  //////////////////////////////////////////////////////////////////////

  void Scene00008( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 8, NONE, bindSceneReturn( &SubWil030::Scene00008Return ) );
  }

  void Scene00008Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setBitFlag8( 1, true );
    onCompletitionCheck( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00009( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 9, NONE, bindSceneReturn( &SubWil030::Scene00009Return ) );
  }

  void Scene00009Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

  }

  //////////////////////////////////////////////////////////////////////

  void Scene00010( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 10, NONE, bindSceneReturn( &SubWil030::Scene00010Return ) );
  }

  void Scene00010Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      Scene00011( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00011( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 11, NONE, bindSceneReturn( &SubWil030::Scene00011Return ) );
  }

  void Scene00011Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
    {
        player.finishQuest( getId(), result.getResult( 1 ) );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00012( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 12, NONE, bindSceneReturn( &SubWil030::Scene00012Return ) );
  }

  void Scene00012Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

  }

};

EXPOSE_SCRIPT( SubWil030 );