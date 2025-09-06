// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>
#include <Actor/BNpc.h>

// Quest Script: ClsPgl100_00555
// Quest Name: Burning Up the Quarter Malm
// Quest ID: 66091
// Start NPC: 1003817 (Hamon)
// End NPC: 1003817 (Hamon)

using namespace Sapphire;

class ClsPgl100 : public Sapphire::ScriptAPI::QuestScript
{
  private:
    // Basic quest information 
    // Quest vars / flags used
    // BitFlag24
    // BitFlag8
    // UI8AH
    // UI8AL
    // UI8BH
    // UI8BL
    // UI8CH
    // UI8CL

    /// Countable Num: 8 Seq: 1 Event: 1 Listener: 2001718
    /// Countable Num: 1 Seq: 2 Event: 18 Listener: 2001718
    /// Countable Num: 1 Seq: 3 Event: 1 Listener: 2001719
    /// Countable Num: 1 Seq: 255 Event: 18 Listener: 2001719
    // Steps in this quest ( 0 is before accepting, 
    // 1 is first, 255 means ready for turning it in
    enum Sequence : uint8_t
    {
      Seq0 = 0,
      Seq1 = 1,
      Seq2 = 2,
      Seq3 = 3,
      SeqFinish = 255,
    };

    // Entities found in the script data of the quest
    static constexpr auto Action0 = 53;
    static constexpr auto Action1 = 56;
    static constexpr auto Actor0 = 1003817; // Hamon ( Pos: -74.541298 1.999990 -42.379501  Teri: 130 )
    static constexpr auto Actor1 = 1004382; // 
    static constexpr auto Actor2 = 1004383; // 
    static constexpr auto Actor3 = 1004384; // 
    static constexpr auto Actor4 = 1004385; // 
    static constexpr auto Actor5 = 1004386; // 
    static constexpr auto Actor6 = 1004387; // 
    static constexpr auto Actor7 = 1004388; // 
    static constexpr auto Actor8 = 1004389; // 
    static constexpr auto Actor9 = 1004390; // 
    static constexpr auto Actor10 = 1004391; // 
    static constexpr auto Actor11 = 1004392; // 
    static constexpr auto Actor20 = 1003827; // Chuchuto ( Pos: -65.656097 0.948195 -51.983002  Teri: 130 )
    static constexpr auto Enemy0 = 226;  // wrong 771; // 
    static constexpr auto Eobject0 = 2001718; // Striking Dummy ( Pos: -108.202003 4.989690 -105.760002  Teri: 130 )
    static constexpr auto Eobject1 = 2001719; // Striking Dummy ( Pos: -105.936996 4.965500 -107.862000  Teri: 130 )
    static constexpr auto Eobject2 = 2001720; // Striking Dummy ( Pos: -77.893799 5.034210 -129.177994  Teri: 130 )
    static constexpr auto Eobject3 = 2001721; // Striking Dummy ( Pos: -74.884003 4.902520 -130.975998  Teri: 130 )
    static constexpr auto Eobject4 = 2001722; // Striking Dummy ( Pos: -71.704002 5.038770 -132.641006  Teri: 130 )
    static constexpr auto Eobject5 = 2001514; // Striking Dummy ( Pos: -105.897003 4.000000 -107.874001  Teri: 130 )
    static constexpr auto Eobject6 = 2001515; // Striking Dummy ( Pos: -108.155998 4.000000 -105.799004  Teri: 130 )
    static constexpr auto Eobject7 = 2001516; // Striking Dummy ( Pos: -77.768600 4.000000 -129.233994  Teri: 130 )
    static constexpr auto Eobject8 = 2001517; // Striking Dummy ( Pos: -74.850304 4.000000 -130.992996  Teri: 130 )
    static constexpr auto Eobject9 = 2001518; // Striking Dummy ( Pos: -71.576302 4.000000 -132.753006  Teri: 130 )
    static constexpr auto UnlockImageClassCange = 22;
    static constexpr auto UnlockImageGearSet = 29;

  public:
    ClsPgl100() : Sapphire::ScriptAPI::QuestScript( 66091 ){}; 
    ~ClsPgl100() = default; 

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
        else if( quest.getSeq() == Seq1 )
          Scene00027( quest, player );
        else if( quest.getSeq() == Seq2 )
          Scene00028( quest, player );
        else if( quest.getSeq() == Seq3 )
          Scene00045( quest, player );
        else if( quest.getSeq() == SeqFinish )
          Scene00046( quest, player );
        break;
      }
      case Actor1:
      {
        break;
      }
      case Actor2:
      {
        break;
      }
      case Actor3:
      {
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
      case Actor7:
      {
        break;
      }
      case Actor8:
      {
        break;
      }
      case Actor9:
      {
        break;
      }
      case Actor10:
      {
        break;
      }
      case Actor11:
      {
        break;
      }
      case Actor20:
      {
        break;
      }
      case Eobject0:
      {
        Scene00001( quest, player );
        break;
      }
      case Eobject1:
      {
        Scene00003( quest, player );
        break;
      }
      case Eobject2:
      {
        Scene00005( quest, player );
        break;
      }
      case Eobject3:
      {
        Scene00007( quest, player );
        break;
      }
      case Eobject4:
      {
        Scene00009( quest, player );
        break;
      }
    }
  }

  void onBNpcKill( World::Quest& quest, Entity::BNpc& bnpc, Entity::Player& player ) override
  {

  }

  void onEObjHit( World::Quest& quest, Sapphire::Entity::Player& player, uint64_t actorId, uint32_t actionId ) override
  {
    if( actionId != Action0 && actionId != Action1 )
      return;

    eventMgr().eventStart( player, actorId, getId(), Event::EventHandler::Nest, 0, 0 );

    switch( actorId )
    {
      case Eobject0:
      {
        if( actionId == Action0 )
          Scene00002( quest, player );
        break;
      }
      case Eobject1:
      {
        if( actionId == Action0 )
          Scene00004( quest, player );
        break;
      }
      case Eobject2:
      {
        if( actionId == Action0 )
          Scene00006( quest, player );
        break;
      }
      case Eobject3:
      {
        if( actionId == Action0 )
          Scene00008( quest, player );
        break;
      }
      case Eobject4:
      {
        if( actionId == Action0 )
          Scene00010( quest, player );
        break;
      }
      case Enemy0:
      {
        if(actionId == Action1 )
          checkCompletition( quest, player );
        break;
      }
    }
  }

  private:
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void checkCompletition( World::Quest& quest, Entity::Player& player )
  {
    if( quest.getSeq() == Seq1 )
    {
      quest.setUI8AH( quest.getUI8AH() + 1 );
      eventMgr().sendEventNotice( player, getId(), 0, 2, quest.getUI8AH(), 5 );

      if( quest.getUI8AH() >= 5 )
      {
        quest.setUI8AH( 0 );
        quest.setUI8AL( 0 );
        quest.setUI8BL( 0 );
        quest.setUI8BH( 0 );
        quest.setUI8CL( 0 );
        quest.setBitFlag24( 1, false );
        quest.setBitFlag24( 1, false );
        quest.setBitFlag24( 1, false );
        quest.setBitFlag24( 1, false );
        quest.setBitFlag24( 1, false );
        quest.setSeq( Seq2 );
      }
    }
    else if( quest.getSeq() == Seq3 )
    {
      quest.setUI8AL( quest.getUI8AL() + 1 );

      if( quest.getUI8AH() >= 3 )
      {
        eventMgr().sendEventNotice( player, getId(), 2, 0 );
        quest.setSeq( SeqFinish );
      }
    }
  }

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, NONE, bindSceneReturn( &ClsPgl100::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, NONE, bindSceneReturn( &ClsPgl100::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, NONE, bindSceneReturn( &ClsPgl100::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8AL( 1 );
    quest.setBitFlag24( 1, true );
    checkCompletition( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, NONE, bindSceneReturn( &ClsPgl100::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, NONE, bindSceneReturn( &ClsPgl100::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8BH( 1 );
    quest.setBitFlag24( 2, true );
    checkCompletition( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, NONE, bindSceneReturn( &ClsPgl100::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00006( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 6, NONE, bindSceneReturn( &ClsPgl100::Scene00006Return ) );
  }

  void Scene00006Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8BL( 1 );
    quest.setBitFlag24( 3, true );
    checkCompletition( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00007( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 7, NONE, bindSceneReturn( &ClsPgl100::Scene00007Return ) );
  }

  void Scene00007Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00008( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 8, NONE, bindSceneReturn( &ClsPgl100::Scene00008Return ) );
  }

  void Scene00008Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8CH( 1 );
    quest.setBitFlag24( 4, true );
    checkCompletition( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00009( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 9, NONE, bindSceneReturn( &ClsPgl100::Scene00009Return ) );
  }

  void Scene00009Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00010( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 10, NONE, bindSceneReturn( &ClsPgl100::Scene00010Return ) );
  }

  void Scene00010Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8CL( 1 );
    quest.setBitFlag24( 5, true );
    checkCompletition( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00011( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 11, NONE, bindSceneReturn( &ClsPgl100::Scene00011Return ) );
  }

  void Scene00011Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00012( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 12, NONE, bindSceneReturn( &ClsPgl100::Scene00012Return ) );
  }

  void Scene00012Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00013( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 13, NONE, bindSceneReturn( &ClsPgl100::Scene00013Return ) );
  }

  void Scene00013Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00014( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 14, NONE, bindSceneReturn( &ClsPgl100::Scene00014Return ) );
  }

  void Scene00014Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00015( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 15, NONE, bindSceneReturn( &ClsPgl100::Scene00015Return ) );
  }

  void Scene00015Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00016( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 16, NONE, bindSceneReturn( &ClsPgl100::Scene00016Return ) );
  }

  void Scene00016Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00017( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 17, NONE, bindSceneReturn( &ClsPgl100::Scene00017Return ) );
  }

  void Scene00017Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00018( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 18, NONE, bindSceneReturn( &ClsPgl100::Scene00018Return ) );
  }

  void Scene00018Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00019( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 19, NONE, bindSceneReturn( &ClsPgl100::Scene00019Return ) );
  }

  void Scene00019Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00020( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 20, NONE, bindSceneReturn( &ClsPgl100::Scene00020Return ) );
  }

  void Scene00020Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00021( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 21, NONE, bindSceneReturn( &ClsPgl100::Scene00021Return ) );
  }

  void Scene00021Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00022( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 22, NONE, bindSceneReturn( &ClsPgl100::Scene00022Return ) );
  }

  void Scene00022Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00023( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 23, NONE, bindSceneReturn( &ClsPgl100::Scene00023Return ) );
  }

  void Scene00023Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00024( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 24, NONE, bindSceneReturn( &ClsPgl100::Scene00024Return ) );
  }

  void Scene00024Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00025( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 25, NONE, bindSceneReturn( &ClsPgl100::Scene00025Return ) );
  }

  void Scene00025Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00026( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 26, NONE, bindSceneReturn( &ClsPgl100::Scene00026Return ) );
  }

  void Scene00026Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00027( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 27, NONE, bindSceneReturn( &ClsPgl100::Scene00027Return ) );
  }

  void Scene00027Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00028( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 28, NONE, bindSceneReturn( &ClsPgl100::Scene00028Return ) );
  }

  void Scene00028Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 1, 0 );
    // Seq3 need to hit BNpcs with Action1
    // Actually there is no function that help to check if a BNpc is hitted by an ability
    // Actual bypass is to set to SeqFinish and complete the quest.
    // quest.setSeq( Seq3 );
    World::Manager::PlayerMgr::sendDebug( player, "Seq3 need to hit BNpcs with Action1 and there is no function that help to check if a BNpc is hitted by an ability" );
    World::Manager::PlayerMgr::sendDebug( player, "Quest will skip to SeqFinish until a fix" );
    quest.setSeq( SeqFinish );

  }

  //////////////////////////////////////////////////////////////////////

  void Scene00029( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 29, NONE, bindSceneReturn( &ClsPgl100::Scene00029Return ) );
  }

  void Scene00029Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00030( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 30, NONE, bindSceneReturn( &ClsPgl100::Scene00030Return ) );
  }

  void Scene00030Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00031( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 31, NONE, bindSceneReturn( &ClsPgl100::Scene00031Return ) );
  }

  void Scene00031Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00032( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 32, NONE, bindSceneReturn( &ClsPgl100::Scene00032Return ) );
  }

  void Scene00032Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00033( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 33, NONE, bindSceneReturn( &ClsPgl100::Scene00033Return ) );
  }

  void Scene00033Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00034( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 34, NONE, bindSceneReturn( &ClsPgl100::Scene00034Return ) );
  }

  void Scene00034Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00035( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 35, NONE, bindSceneReturn( &ClsPgl100::Scene00035Return ) );
  }

  void Scene00035Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00036( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 36, NONE, bindSceneReturn( &ClsPgl100::Scene00036Return ) );
  }

  void Scene00036Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00037( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 37, NONE, bindSceneReturn( &ClsPgl100::Scene00037Return ) );
  }

  void Scene00037Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00038( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 38, NONE, bindSceneReturn( &ClsPgl100::Scene00038Return ) );
  }

  void Scene00038Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00039( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 39, NONE, bindSceneReturn( &ClsPgl100::Scene00039Return ) );
  }

  void Scene00039Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00040( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 40, NONE, bindSceneReturn( &ClsPgl100::Scene00040Return ) );
  }

  void Scene00040Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00041( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 41, NONE, bindSceneReturn( &ClsPgl100::Scene00041Return ) );
  }

  void Scene00041Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00042( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 42, NONE, bindSceneReturn( &ClsPgl100::Scene00042Return ) );
  }

  void Scene00042Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00043( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 43, NONE, bindSceneReturn( &ClsPgl100::Scene00043Return ) );
  }

  void Scene00043Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00044( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 44, NONE, bindSceneReturn( &ClsPgl100::Scene00044Return ) );
  }

  void Scene00044Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00045( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 45, NONE, bindSceneReturn( &ClsPgl100::Scene00045Return ) );
  }

  void Scene00045Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00046( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 46, FADE_OUT | HIDE_UI | CONDITION_CUTSCENE, bindSceneReturn( &ClsPgl100::Scene00046Return ) );
  }

  void Scene00046Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    Scene00047( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00047( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 47, NONE, bindSceneReturn( &ClsPgl100::Scene00047Return ) );
  }

  void Scene00047Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
    {
        player.finishQuest( getId(), result.getResult( 1 ) );
    }
  }

};

EXPOSE_SCRIPT( ClsPgl100 );