// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include "Manager/EventMgr.h"
#include <Actor/Player.h>
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: SubFst072_00386
// Quest Name: Walking the Planks
// Quest ID: 65922
// Start NPC: 1000501
// End NPC: 1000501

using namespace Sapphire;

class SubFst072 : public Sapphire::ScriptAPI::QuestScript
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
  // UI8CL
  // UI8DH

  /// Countable Num: 3 Seq: 1 Event: 1 Listener: 2001013
  /// Countable Num: 3 Seq: 2 Event: 1 Listener: 2001014
  /// Countable Num: 1 Seq: 255 Event: 1 Listener: 2001015
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
  static constexpr auto Actor0 = 1000501;  //Waltheof
  static constexpr auto Actor1 = 1000502;  //Berthe
  static constexpr auto Actor2 = 1000507;  //Kyleigh
  static constexpr auto Actor3 = 1000505;  //Daranmert
  static constexpr auto Eobject0 = 2001013;//Crayfish Balls
  static constexpr auto Eobject1 = 2001014;//Muy-Tuy Beans
  static constexpr auto Eobject2 = 2001015;//Pate Mail
  static constexpr auto EventActionSearch = 1;
  static constexpr auto Item0 = 2000246;
  static constexpr auto Item1 = 2000247;
  static constexpr auto Item2 = 2000248;
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
  static constexpr auto Seq2Actor1 = 4;
  static constexpr auto Seq2Actor1Npctradeno = 93;
  static constexpr auto Seq2Actor1Npctradeok = 94;
  static constexpr auto Seq2Actor2 = 5;
  static constexpr auto Seq2Actor2Npctradeno = 91;
  static constexpr auto Seq2Actor2Npctradeok = 92;
  static constexpr auto Seq2Actor3 = 6;
  static constexpr auto Seq2Actor3Npctradeno = 89;
  static constexpr auto Seq2Actor3Npctradeok = 90;
  static constexpr auto Seq3Actor0 = 7;

public:
  SubFst072() : Sapphire::ScriptAPI::QuestScript( 65922 ){};
  ~SubFst072() = default;

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
          Scene00007( quest, player );
        break;
      }
      case Actor1:
      {
        if( quest.getSeq() == Seq2 )
          Scene00004( quest, player );
        break;
      }
      case Actor2:
      {
        if( quest.getSeq() == Seq2 )
          Scene00005( quest, player );
        break;
      }
      case Actor3:
      {
        if( quest.getSeq() == Seq2 )
          Scene00006( quest, player );
        break;
      }
      case Eobject0:
      {
        eventMgr().eventActionStart(
                player, getId(), EventActionSearch,
                [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                  Scene00100( quest, player );
                },
                nullptr, 0 );
        break;
      }
      case Eobject1:
      {
        eventMgr().eventActionStart(
                player, getId(), EventActionSearch,
                [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                  Scene00098( quest, player );
                },
                nullptr, 0 );
        break;
      }
      case Eobject2:
      {
        eventMgr().eventActionStart(
                player, getId(), EventActionSearch,
                [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                  Scene00096( quest, player );
                },
                nullptr, 0 );
        break;
      }
    }
  }


private:
  void checkQuestCompletion( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().sendEventNotice( player, getId(), ( quest.getSeq() == Seq1 ) ? 0 : 1, 2, quest.getUI8AH(), 3 );
    if( quest.getUI8AH() >= 3 )
    {
      quest.setUI8AH( 0 );
      quest.setBitFlag8( 1, false );
      quest.setBitFlag8( 2, false );
      quest.setBitFlag8( 3, false );
      if( quest.getSeq() == Seq1 )
        quest.setSeq( Seq2 );
      else if( quest.getSeq() == Seq2 )
        quest.setSeq( SeqFinish );
    }
  }
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &SubFst072::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, NONE, bindSceneReturn( &SubFst072::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, NONE, bindSceneReturn( &SubFst072::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, NONE, bindSceneReturn( &SubFst072::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, HIDE_HOTBAR, bindSceneReturn( &SubFst072::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      Scene00094( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, HIDE_HOTBAR, bindSceneReturn( &SubFst072::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      Scene00092( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00006( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 6, HIDE_HOTBAR, bindSceneReturn( &SubFst072::Scene00006Return ) );
  }

  void Scene00006Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      Scene00090( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00007( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 7, HIDE_HOTBAR, bindSceneReturn( &SubFst072::Scene00007Return ) );
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
    eventMgr().playQuestScene( player, getId(), 89, NONE, bindSceneReturn( &SubFst072::Scene00089Return ) );
  }

  void Scene00089Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00090( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 90, HIDE_HOTBAR, bindSceneReturn( &SubFst072::Scene00090Return ) );
  }

  void Scene00090Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8AH( quest.getUI8AH() + 1 );
    quest.setUI8DH( 0 );
    quest.setBitFlag8( 3, true );
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00091( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 91, NONE, bindSceneReturn( &SubFst072::Scene00091Return ) );
  }

  void Scene00091Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00092( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 92, HIDE_HOTBAR, bindSceneReturn( &SubFst072::Scene00092Return ) );
  }

  void Scene00092Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8AH( quest.getUI8AH() + 1 );
    quest.setUI8CL( 0 );
    quest.setBitFlag8( 2, true );
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00093( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 93, NONE, bindSceneReturn( &SubFst072::Scene00093Return ) );
  }

  void Scene00093Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00094( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 94, HIDE_HOTBAR, bindSceneReturn( &SubFst072::Scene00094Return ) );
  }

  void Scene00094Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8AH( quest.getUI8AH() + 1 );
    quest.setUI8CH( 0 );
    quest.setBitFlag8( 1, true );
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00095( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 95, NONE, bindSceneReturn( &SubFst072::Scene00095Return ) );
  }

  void Scene00095Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00096( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 96, NONE, bindSceneReturn( &SubFst072::Scene00096Return ) );
  }

  void Scene00096Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8AH( quest.getUI8AH() + 1 );
    quest.setUI8DH( 1 );
    quest.setBitFlag8( 3, true );
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00097( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 97, NONE, bindSceneReturn( &SubFst072::Scene00097Return ) );
  }

  void Scene00097Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00098( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 98, NONE, bindSceneReturn( &SubFst072::Scene00098Return ) );
  }

  void Scene00098Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8AH( quest.getUI8AH() + 1 );
    quest.setUI8CL( 1 );
    quest.setBitFlag8( 2, true );
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00099( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 99, NONE, bindSceneReturn( &SubFst072::Scene00099Return ) );
  }

  void Scene00099Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00100( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 100, NONE, bindSceneReturn( &SubFst072::Scene00100Return ) );
  }

  void Scene00100Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8AH( quest.getUI8AH() + 1 );
    quest.setUI8CH( 1 );
    quest.setBitFlag8( 1, true );
    checkQuestCompletion( quest, player );
  }
};

EXPOSE_SCRIPT( SubFst072 );