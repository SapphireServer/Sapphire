// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>
#include <Actor/BNpc.h>

// Quest Script: ClsPgl150_00558
// Quest Name: The Spirit Is Willing
// Quest ID: 66094
// Start NPC: 1003817 (Hamon)
// End NPC: 1003827 (Chuchuto)

using namespace Sapphire;

class ClsPgl150 : public Sapphire::ScriptAPI::QuestScript
{
  private:
    // Basic quest information 
    // Quest vars / flags used
    // BitFlag8
    // UI8AL
    // UI8BH

    /// Countable Num: 5 Seq: 1 Event: 9 Listener: 26
    /// Countable Num: 1 Seq: 2 Event: 1 Listener: 1003817
    /// Countable Num: 3 Seq: 3 Event: 1 Listener: 1003822
    /// Countable Num: 1 Seq: 4 Event: 1 Listener: 1004147
    /// Countable Num: 1 Seq: 5 Event: 1 Listener: 1001578
    /// Countable Num: 1 Seq: 6 Event: 1 Listener: 1001445
    /// Countable Num: 1 Seq: 255 Event: 1 Listener: 1004148
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
      Seq6 = 6,
      SeqFinish = 255,
    };

    // Entities found in the script data of the quest
    static constexpr auto Actor0 = 1003817; // Hamon ( Pos: -74.541298 1.999990 -42.379501  Teri: 130 )
    static constexpr auto Actor1 = 1003822; // Hamon ( Pos: -27.370199 -2.059960 -146.899002  Teri: 141 )
    static constexpr auto Actor2 = 1004147; // Chuchuto ( Pos: -26.567200 -2.056170 -146.658005  Teri: 141 )
    static constexpr auto Actor3 = 1001578; // Zuzumeda ( Pos: -35.416199 -2.057690 -154.925003  Teri: 141 )
    static constexpr auto Actor4 = 1001445; // Osbert ( Pos: -13.046500 -2.072270 -184.404999  Teri: 141 )
    static constexpr auto Actor5 = 1004148; // Chuchuto ( Pos: 5.722110 -1.985180 -172.778000  Teri: 141 )
    static constexpr auto Actor6 = 1004149; // Hamon ( Pos: -242.828003 7.405040 -29.289700  Teri: 141 )
    static constexpr auto Actor7 = 1004150; // Chuchuto ( Pos: -241.970993 7.161570 -26.863701  Teri: 141 )
    static constexpr auto Actor8 = 1003827; // Chuchuto ( Pos: -65.656097 0.948195 -51.983002  Teri: 130 )
    static constexpr auto Enemy0 = 216;  //Wrong 26; // Gigantoad ( Pos: 298.914001 3.191500 104.051003  Teri: 148 )
    static constexpr auto Eobject0 = 2001349; // Destination ( Pos: -241.410995 8.100870 -32.214500  Teri: 141 )
    static constexpr auto EventActionWaitingShor = 11;
    static constexpr auto Item0 = 2000408;
    static constexpr auto LocAction0 = 995;
    static constexpr auto LocActor0 = 1003827; // Chuchuto ( Pos: -65.656097 0.948195 -51.983002  Teri: 130 )
    static constexpr auto LocActor1 = 1002024; // Nanajapi
    static constexpr auto LocVfx = 241;
    static constexpr auto LocWs = 68;
    static constexpr auto Ncut15010 = 164;
    static constexpr auto Questbattle0 = 30;
    static constexpr auto Territorytype0 = 258;

  public:
    ClsPgl150() : Sapphire::ScriptAPI::QuestScript( 66094 ){}; 
    ~ClsPgl150() = default; 

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
          Scene00001( quest, player );
        break;
      }
      case Actor1:
      {
        if( quest.getSeq() == Seq2 )
          Scene00002( quest, player );
        else if( quest.getSeq() == Seq3 )
          Scene00010( quest, player );
        else if( quest.getSeq() == Seq4 )
          Scene00011( quest, player );
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
        if( quest.getSeq() == Seq3 )
          Scene00006( quest, player );
        break;
      }
      case Actor4:
      {
        if( quest.getSeq() == Seq3 )
          Scene00007( quest, player );
        break;
      }
      case Actor5:
      {
        if( quest.getSeq() == Seq3 )
          Scene00008( quest, player );
        else if( quest.getSeq() == Seq4 )
          Scene00009( quest, player );
        break;
      }
      case Actor6:
      {
        if( quest.getSeq() == Seq6 )
          Scene00018( quest, player );
        else if( quest.getSeq() == SeqFinish )
          Scene00021( quest, player );
        break;
      }
      case Actor7:
      {
        if( quest.getSeq() == Seq6 )
          Scene00019( quest, player );
        else if( quest.getSeq() == SeqFinish )
          Scene00022( quest, player );
        break;
      }
      case Actor8:
      {
        if( quest.getSeq() == SeqFinish )
          Scene00020( quest, player );
        break;
      }
      case Eobject0:
      {
        eventMgr().eventActionStart(
                player, getId(), EventActionWaitingShor,
                [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                  Scene00014( quest, player );
                },
                nullptr, getId() );
        break;
      }
    }
  }

  void onEventItem( World::Quest& quest, Entity::Player& player, uint64_t actorId ) override
  {
  }

  void onBNpcKill( World::Quest& quest, Entity::BNpc& bnpc, Entity::Player& player ) override
  {
    if( quest.getSeq() == Seq1 )
    {
      switch( bnpc.getBNpcNameId() )
      {
        case Enemy0:
        {
          checkCompletition( quest, player );
          break;
        }
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
      quest.setUI8AL( quest.getUI8AL() + 1 );
      quest.setUI8BH( quest.getUI8BH() + 1 );
      eventMgr().sendNotice( player, getId(), 0, { quest.getUI8AL(), 5, player.getQuestItemIcon( Item0 ) } );

      if( quest.getUI8AL() >= 5 )
      {
        quest.setUI8AL( 0 );
        quest.setSeq( Seq2 );
      }
    }
    else if (quest.getSeq() == Seq3)
    {
      quest.setUI8AL( quest.getUI8AL() + 1 );
      eventMgr().sendEventNotice( player, getId(), 2, 2, quest.getUI8AL(), 3 );

      if( quest.getUI8AL() >= 3 )
      {
        quest.setBitFlag8( 1, false );
        quest.setBitFlag8( 2, false );
        quest.setBitFlag8( 3, false );
        quest.setUI8AL( 0 );
        quest.setSeq( Seq4 );
      }
    }
    
  }

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, NONE, bindSceneReturn( &ClsPgl150::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, NONE, bindSceneReturn( &ClsPgl150::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, NONE, bindSceneReturn( &ClsPgl150::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      Scene00003( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, FADE_OUT | HIDE_UI | CONDITION_CUTSCENE, bindSceneReturn( &ClsPgl150::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 1, 0 );
    quest.setSeq( Seq3 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, NONE, bindSceneReturn( &ClsPgl150::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, NONE, bindSceneReturn( &ClsPgl150::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00006( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 6, NONE, bindSceneReturn( &ClsPgl150::Scene00006Return ) );
  }

  void Scene00006Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    checkCompletition( quest, player );
    quest.setBitFlag8( 1, true );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00007( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 7, NONE, bindSceneReturn( &ClsPgl150::Scene00007Return ) );
  }

  void Scene00007Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    checkCompletition( quest, player );
    quest.setBitFlag8( 2, true );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00008( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 8, NONE, bindSceneReturn( &ClsPgl150::Scene00008Return ) );
  }

  void Scene00008Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    checkCompletition( quest, player );
    quest.setBitFlag8( 3, true );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00009( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 9, NONE, bindSceneReturn( &ClsPgl150::Scene00009Return ) );
  }

  void Scene00009Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00010( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 10, NONE, bindSceneReturn( &ClsPgl150::Scene00010Return ) );
  }

  void Scene00010Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00011( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 11, NONE, bindSceneReturn( &ClsPgl150::Scene00011Return ) );
  }

  void Scene00011Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 3, 0 );
    quest.setSeq( Seq5 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00012( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 12, NONE, bindSceneReturn( &ClsPgl150::Scene00012Return ) );
  }

  void Scene00012Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00013( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 13, NONE, bindSceneReturn( &ClsPgl150::Scene00013Return ) );
  }

  void Scene00013Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00014( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 14, HIDE_HOTBAR, bindSceneReturn( &ClsPgl150::Scene00014Return ) );
  }

  void Scene00014Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult(0) == 1 )
    {
      auto& pTeriMgr = Common::Service< Sapphire::World::Manager::TerritoryMgr >::ref();

      eventMgr().eventFinish( player, result.eventId, 0 );
      pTeriMgr.createAndJoinQuestBattle( player, Questbattle0 );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00015( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 15, NONE, bindSceneReturn( &ClsPgl150::Scene00015Return ) );
  }

  void Scene00015Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00016( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 16, NONE, bindSceneReturn( &ClsPgl150::Scene00016Return ) );
  }

  void Scene00016Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00017( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 17, NONE, bindSceneReturn( &ClsPgl150::Scene00017Return ) );
  }

  void Scene00017Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00018( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 18, NONE, bindSceneReturn( &ClsPgl150::Scene00018Return ) );
  }

  void Scene00018Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( SeqFinish );
    eventMgr().sendEventNotice( player, getId(), 5, 0 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00019( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 19, NONE, bindSceneReturn( &ClsPgl150::Scene00019Return ) );
  }

  void Scene00019Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00020( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 20, FADE_OUT | HIDE_UI, bindSceneReturn( &ClsPgl150::Scene00020Return ) );
  }

  void Scene00020Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
    {
        player.finishQuest( getId(), result.getResult( 1 ) );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00021( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 21, NONE, bindSceneReturn( &ClsPgl150::Scene00021Return ) );
  }

  void Scene00021Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00022( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 22, NONE, bindSceneReturn( &ClsPgl150::Scene00022Return ) );
  }

  void Scene00022Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

};

EXPOSE_SCRIPT( ClsPgl150 );