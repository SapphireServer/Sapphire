// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>
#include <Actor/BNpc.h>

// Quest Script: ClsGla100_00261
// Quest Name: Ul'dah's Most Wanted
// Quest ID: 65797
// Start NPC: 1001739 (Mylla)
// End NPC: 1001739 (Mylla)

using namespace Sapphire;

class ClsGla100 : public Sapphire::ScriptAPI::QuestScript
{
  private:
    // Basic quest information 
    // Quest vars / flags used
    // BitFlag8
    // UI8AL

    /// Countable Num: 2 Seq: 1 Event: 1 Listener: 1002296
    /// Countable Num: 1 Seq: 2 Event: 5 Listener: 1245
    /// Countable Num: 1 Seq: 3 Event: 5 Listener: 1245
    /// Countable Num: 1 Seq: 4 Event: 1 Listener: 1002296
    /// Countable Num: 1 Seq: 5 Event: 1 Listener: 1001739
    /// Countable Num: 1 Seq: 255 Event: 1 Listener: 2001426
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
    static constexpr auto Actor0 = 1001739; // Mylla ( Pos: -94.529701 6.499970 39.810699  Teri: 131 )
    static constexpr auto Actor1 = 1002296; // Gutless Gladiator ( Pos: -139.417007 4.182130 205.052994  Teri: 141 )
    static constexpr auto Actor2 = 1003945; // Bruce The Big ( Pos: 24.935200 12.999900 50.166599  Teri: 141 )
    static constexpr auto Enemy0 = 3976825; // Duskwight Freelancer
    static constexpr auto Enemy1 = 3976826; // Duskwight Freelancer
    static constexpr Common::QuestEobject Eobject0 = { 2001426, 141, { 27.219801, 13.000000, 51.848900 }, 1.000000 }; // Destination
    static constexpr auto EventActionWaiting = 10;
    static constexpr auto LocActor0 = 1004302; // Bruce
    static constexpr auto Questbattle0 = 19;
    static constexpr auto Territorytype0 = 253;
    static constexpr auto UnlockCheckLeveReward = 5;
    static constexpr auto UnlockImageClassCange = 22;
    static constexpr auto UnlockImageGearSet = 29;
    static constexpr auto UnlockImageLeve = 20;

  public:
    ClsGla100() : Sapphire::ScriptAPI::QuestScript( 65797 ){}; 
    ~ClsGla100() = default; 

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
        else if( quest.getSeq() == Seq3 )
          Scene00003( quest, player );
        else if( quest.getSeq() == SeqFinish )
          Scene00009( quest, player );
        break;
      }
      case Actor1:
      {
        if( quest.getSeq() == Seq1 && !checkAlive( player, Enemy0 ) && !checkAlive( player, Enemy1 ) )
          Scene00001( quest, player );
        else if( quest.getSeq() == Seq2 )
          Scene00002( quest, player );
        break;
      }
      case Actor2:
      {
        if( quest.getSeq() == Seq4 )
          Scene00007( quest, player );
        else if( quest.getSeq() == Seq5 )
          Scene00008( quest, player );
        break;
      }
      case Eobject0.id:
      {
        if( quest.getSeq() == Seq4 )
          eventMgr().eventActionStart( player, getId(), EventActionWaiting, [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) { Scene00005( quest, player ); }, nullptr, 0 );
        break;
      }
    }
  }

  void onBNpcKill( World::Quest& quest, Entity::BNpc& bnpc, Entity::Player& player ) override
  {
    if( bnpc.getLayoutId() != Enemy0 && bnpc.getLayoutId() != Enemy1 )
      return;

    auto currentKC = quest.getUI8AL() + 1;

    switch( bnpc.getLayoutId() )
    {
      case Enemy0:
      case Enemy1:
      {
        if( currentKC <= 2 )
        {
          quest.setUI8AL( currentKC );
          if( currentKC == 2 )
            checkQuestCompletion( quest, player );
        }
        break;
      }
    }
  }

  private:
  void checkQuestCompletion( World::Quest& quest, Entity::Player& player )
  {
    auto currentKC = quest.getUI8AL();

    if( currentKC == 2 )
    {
      quest.setUI8AL( 0 );
      eventMgr().sendEventNotice( player, getId(), 0, 0, 0, 0 ); // search for the freelanders in stonesthrow completion message
      quest.setSeq( Seq2 );
    }
  }

  bool checkAlive( Entity::Player& player, uint32_t layoutId )
  {
    auto bnpc = teriMgr().getTerritoryByGuId( player.getTerritoryId() )->getActiveBNpcByLayoutId( layoutId );
    if( bnpc && bnpc->getTriggerOwnerId() == player.getId() && bnpc->isAlive() )
      return true;
    return false;
  }
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &ClsGla100::Scene00000Return ) );
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
    //Don't kill me, please! I'm not the one you want!
    //You hear several sets of approaching foorsteps...
    eventMgr().playQuestScene( player, getId(), 1, HIDE_HOTBAR, bindSceneReturn( &ClsGla100::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    auto instance = teriMgr().getTerritoryByGuId( player.getTerritoryId() );
    auto enemy0 = instance->createBNpcFromLayoutId( Enemy0, 1220 /*Find the right value*/, Common::BNpcType::Enemy, player.getId() );
    enemy0->hateListAdd( player.getAsPlayer(), 1 );
    auto enemy1 = instance->createBNpcFromLayoutId( Enemy1, 1220 /*Find the right value*/, Common::BNpcType::Enemy, player.getId() );
    enemy1->hateListAdd( player.getAsPlayer(), 1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    //Thank you, thank you !Th - They appeared out of nowhere, asked me if I was Aldis at spearpoint.I said no, but they attacked me anyway !Wh - What did I do to deserve this ?
    eventMgr().playQuestScene( player, getId(), 2, HIDE_HOTBAR, bindSceneReturn( &ClsGla100::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 1, 0, 0, 0 ); //speak with completion message
    quest.setSeq( Seq3 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    //So they were indeed the murderers we sought!
    eventMgr().playQuestScene( player, getId(), 3, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &ClsGla100::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 2, 0, 0, 0 ); //report to mylla completion message
    quest.setSeq( Seq4 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, HIDE_HOTBAR, bindSceneReturn( &ClsGla100::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    // Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    //duity question
    eventMgr().playQuestScene( player, getId(), 5, HIDE_HOTBAR, bindSceneReturn( &ClsGla100::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
    {
      auto& pTeriMgr = Common::Service< Sapphire::World::Manager::TerritoryMgr >::ref();

      eventMgr().eventFinish( player, result.eventId, 0 );
      pTeriMgr.createAndJoinQuestBattle( player, m_id, Questbattle0 );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00006( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 6, HIDE_HOTBAR, bindSceneReturn( &ClsGla100::Scene00006Return ) );
  }

  void Scene00006Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    // Empty
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00007( World::Quest& quest, Entity::Player& player )
  {
    //Hmmm...seems no one's home. What say we wait here and ambush 'em when they return?
    eventMgr().playQuestScene( player, getId(), 7, HIDE_HOTBAR, bindSceneReturn( &ClsGla100::Scene00007Return ) );
  }

  void Scene00007Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00008( World::Quest& quest, Entity::Player& player )
  {
    //Looks like we're done here. Let's head home, Rafela─I could use a drink.
    eventMgr().playQuestScene( player, getId(), 8, HIDE_HOTBAR, bindSceneReturn( &ClsGla100::Scene00008Return ) );
  }

  void Scene00008Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 3, 0, 0, 0 );//speak with completion message
    quest.setSeq( SeqFinish );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00009( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 9, HIDE_HOTBAR, bindSceneReturn( &ClsGla100::Scene00009Return ) );
  }

  void Scene00009Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
      player.setRewardFlag( Common::UnlockEntry::GearSets );
    }

  }

};

EXPOSE_SCRIPT( ClsGla100 );