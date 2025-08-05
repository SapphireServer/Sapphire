// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: SubSea010_00120
// Quest Name: I Stay the Streetlight
// Quest ID: 65656
// Start NPC: 1002434 (N'tanmo)
// End NPC: 1000857 (Sisipu)

using namespace Sapphire;

class SubSea010 : public Sapphire::ScriptAPI::QuestScript
{
  private:
    // Basic quest information 
    // Quest vars / flags used
    // BitFlag8
    // UI8AL
    // UI8BH

    /// Countable Num: 1 Seq: 1 Event: 1 Listener: 2001578
    /// Countable Num: 0 Seq: 255 Event: 8 Listener: 2001578
    // Steps in this quest ( 0 is before accepting, 
    // 1 is first, 255 means ready for turning it in
    enum Sequence : uint8_t
    {
      Seq0 = 0,
      Seq1 = 1,
      SeqFinish = 255,
    };

    // Entities found in the script data of the quest
    static constexpr auto Actor0 = 1002434; // N'tanmo ( Pos: -6.731810 20.333300 0.557258  Teri: 129 )
    static constexpr auto Actor1 = 1000857; // Sisipu ( Pos: -165.270004 5.233830 164.294006  Teri: 129 )
    static constexpr auto Eobject0 = 2001578; // Guttering Streetlamp ( Pos: -65.683998 20.675900 17.784599  Teri: 129 )
    static constexpr auto Eobject1 = 2001572; // Guttering Streetlamp ( Pos: -65.368500 21.581499 54.410801  Teri: 129 )
    static constexpr auto Eobject2 = 2001573; // Guttering Streetlamp ( Pos: -84.382698 21.506001 81.176903  Teri: 129 )
    static constexpr auto Eobject3 = 2001574; // Guttering Streetlamp ( Pos: -117.660004 21.596300 134.942993  Teri: 129 )
    static constexpr auto Eobject4 = 2001575; // Guttering Streetlamp ( Pos: -145.330994 22.955999 159.746994  Teri: 129 )
    static constexpr auto Eobject5 = 2001576; // Guttering Streetlamp ( Pos: -162.470993 15.090300 136.587997  Teri: 129 )
    static constexpr auto Eobject6 = 2001577; // Guttering Streetlamp ( Pos: -137.529999 9.802420 170.656006  Teri: 129 )
    static constexpr auto Item0 = 2000444;

  public:
    SubSea010() : Sapphire::ScriptAPI::QuestScript( 65656 ){}; 
    ~SubSea010() = default; 

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
          Scene00016( quest, player );
        break;
      }
      case Eobject0:
      {
        if( quest.getSeq() == Seq1 )
          Scene00002( quest, player );
        break;
      }
      case Eobject1:
      {
        if( quest.getSeq() == Seq1 )
          Scene00004( quest, player );
        break;
      }
      case Eobject2:
      {
        if( quest.getSeq() == Seq1 )
          Scene00006( quest, player );
        break;
      }
      case Eobject3:
      {
        if( quest.getSeq() == Seq1 )
          Scene00008( quest, player );
        break;
      }
      case Eobject4:
      {
        if( quest.getSeq() == Seq1 )
          Scene00010( quest, player );
        break;
      }
      case Eobject5:
      {
        if( quest.getSeq() == Seq1 )
          Scene00012( quest, player );
        break;
      }
      case Eobject6:
      {
        if( quest.getSeq() == Seq1 )
          Scene00010( quest, player );
        break;
      }
    }
  }

  void onEventItem( World::Quest& quest, Entity::Player& player, uint64_t actorId ) override
  {
    if( quest.getSeq() != Seq1 )
      return;

    switch( actorId )
    {
      case Eobject0:
      {
        Scene00003( quest, player );
        break;
      }
      case Eobject1:
      {
        Scene00005( quest, player );
        break;
      }
      case Eobject2:
      {
        Scene00007( quest, player );
        break;
      }
      case Eobject3:
      {
        Scene00009( quest, player );
        break;
      }
      case Eobject4:
      {
        Scene00011( quest, player );
        break;
      }
      case Eobject5:
      {
        Scene00013( quest, player );
        break;
      }
      case Eobject6:
      {
        Scene00015( quest, player );
        break;
      }
    }
  }

  private:
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void checkCompletition(World::Quest& quest, Entity::Player& player)
  {
    if( quest.getSeq() == Seq1 )
    {
      quest.setUI8AL( quest.getUI8AL() + 1 );
      quest.setUI8BH( quest.getUI8BH() - 1 );

      eventMgr().sendEventNotice( player, getId(), 0, 2, quest.getUI8AL(), 7 );

      if( quest.getUI8AL() >= 7 )
        quest.setSeq( SeqFinish );
    }
  }

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, NONE, bindSceneReturn( &SubSea010::Scene00000Return ) );
  }

  void Scene00000Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 ) // accept quest
    {
      quest.setSeq( Seq1 );
      quest.setUI8BH( 7 );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00001( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 1, NONE, bindSceneReturn( &SubSea010::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, NONE, bindSceneReturn( &SubSea010::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, AUTO_LOC_CAMERA, bindSceneReturn( &SubSea010::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setBitFlag8( 1, true );
    checkCompletition( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, NONE, bindSceneReturn( &SubSea010::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, AUTO_LOC_CAMERA, bindSceneReturn( &SubSea010::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setBitFlag8( 2, true );
    checkCompletition( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00006( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 6, NONE, bindSceneReturn( &SubSea010::Scene00006Return ) );
  }

  void Scene00006Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

  }

  //////////////////////////////////////////////////////////////////////

  void Scene00007( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 7, AUTO_LOC_CAMERA, bindSceneReturn( &SubSea010::Scene00007Return ) );
  }

  void Scene00007Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setBitFlag8( 3, true );
    checkCompletition( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00008( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 8, NONE, bindSceneReturn( &SubSea010::Scene00008Return ) );
  }

  void Scene00008Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

  }

  //////////////////////////////////////////////////////////////////////

  void Scene00009( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 9, AUTO_LOC_CAMERA, bindSceneReturn( &SubSea010::Scene00009Return ) );
  }

  void Scene00009Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setBitFlag8( 4, true );
    checkCompletition( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00010( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 10, NONE, bindSceneReturn( &SubSea010::Scene00010Return ) );
  }

  void Scene00010Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

  }

  //////////////////////////////////////////////////////////////////////

  void Scene00011( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 11, AUTO_LOC_CAMERA, bindSceneReturn( &SubSea010::Scene00011Return ) );
  }

  void Scene00011Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setBitFlag8( 5, true );
    checkCompletition( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00012( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 12, NONE, bindSceneReturn( &SubSea010::Scene00012Return ) );
  }

  void Scene00012Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

  }

  //////////////////////////////////////////////////////////////////////

  void Scene00013( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 13, AUTO_LOC_CAMERA, bindSceneReturn( &SubSea010::Scene00013Return ) );
  }

  void Scene00013Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setBitFlag8( 6, true );
    checkCompletition( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00014( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 14, NONE, bindSceneReturn( &SubSea010::Scene00014Return ) );
  }

  void Scene00014Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

  }

  //////////////////////////////////////////////////////////////////////

  void Scene00015( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 15, AUTO_LOC_CAMERA, bindSceneReturn( &SubSea010::Scene00015Return ) );
  }

  void Scene00015Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setBitFlag8( 7, true );
    checkCompletition( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00016( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 16, NONE, bindSceneReturn( &SubSea010::Scene00016Return ) );
  }

  void Scene00016Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
    }
  }
};

EXPOSE_SCRIPT( SubSea010 );