// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>
#include <Actor/BNpc.h>

#include "Manager/TerritoryMgr.h"
#include "Territory/Territory.h"

// Quest Script: SubWil038_00230
// Quest Name: Search and Seizure
// Quest ID: 65766
// Start NPC: 1002014 (Kikipu)
// End NPC: 1001353 (Momodi)

using namespace Sapphire;

class SubWil038 : public Sapphire::ScriptAPI::QuestScript
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

    /// Countable Num: 4 Seq: 1 Event: 1 Listener: 1003685
    /// Countable Num: 1 Seq: 2 Event: 10 Listener: 5000000
    /// Countable Num: 1 Seq: 3 Event: 1 Listener: 2001456
    /// Countable Num: 1 Seq: 255 Event: 5 Listener: 778
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
    static constexpr auto Actor0 = 1002014; // Kikipu ( Pos: -253.427002 33.219002 404.062988  Teri: 140 )
    static constexpr auto Actor1 = 1003685; // Kenrick ( Pos: -218.401993 31.717400 365.945007  Teri: 140 )
    static constexpr auto Actor2 = 1001353; // Momodi ( Pos: 21.072599 7.450000 -78.782303  Teri: 130 )
    static constexpr auto Enemy0 = 4086831; // 
    static constexpr auto Enemy1 = 4086832; // 
    static constexpr auto Enemy2 = 4086833; // 
    static constexpr auto Enemy3 = 4086834; // 
    static constexpr auto Eobject0 = 2001456; // Writ Of Seizure ( Pos: -246.576996 35.180302 383.316010  Teri: 140 )
    static constexpr auto Eobject1 = 2001457; // Writ Of Seizure ( Pos: -218.018997 35.816601 426.026001  Teri: 140 )
    static constexpr auto Eobject2 = 2001458; // Writ Of Seizure ( Pos: -282.082001 35.200500 438.834015  Teri: 140 )
    static constexpr auto Eobject3 = 2001459; // Writ Of Seizure ( Pos: -306.981995 34.317501 396.963013  Teri: 140 )
    static constexpr auto Eventrange0 = 4187339;
    static constexpr auto Eventrange1 = 4187340;
    static constexpr auto Eventrange2 = 4187344;
    static constexpr auto Eventrange3 = 4187347;
    static constexpr auto EventActionProcessUpperShort = 31;
    static constexpr auto Item0 = 2000413;
    static constexpr auto Item1 = 2000165;
    static constexpr auto LocActor0 = 1002033; // Kenrick
    static constexpr auto LocActor1 = 1002027; // Fafafono ( Pos: -255.229004 33.233601 407.295013  Teri: 140 )
    static constexpr auto LocActor2 = 1002044; // Galfridus ( Pos: -253.479996 33.229099 409.988007  Teri: 140 )
    static constexpr auto LocFace0 = 604;
    static constexpr auto LocFace1 = 605;
    static constexpr auto LocFace2 = 617;
    static constexpr auto LocPosCam1 = 4072493;
    static constexpr auto Seq0Actor0Lq = 90; // Spriggan Collector

  public:
    SubWil038() : Sapphire::ScriptAPI::QuestScript( 65766 ){}; 
    ~SubWil038() = default; 

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
          Scene00017( quest, player );
        break;
      }
      case Actor1:
      {
        if( quest.getSeq() == Seq2 )
          Scene00015( quest, player );
        break;
      }
      case Actor2:
      {
        if( quest.getSeq() == SeqFinish )
          Scene00018( quest, player );
        break;
      }
      case Eobject0:
      {
        eventMgr().eventActionStart(
                player, getId(), EventActionProcessUpperShort,
                [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                  Scene00005( quest, player );
                },
                nullptr, 0 );
        break;
      }
      case Eobject1:
      {
        eventMgr().eventActionStart(
                player, getId(), EventActionProcessUpperShort,
                [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                  Scene00008( quest, player );
                },
                nullptr, 0 );
        break;
      }
      case Eobject2:
      {
        eventMgr().eventActionStart(
                player, getId(), EventActionProcessUpperShort,
                [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                  Scene00011( quest, player );
                },
                nullptr, 0 );
        break;
      }
      case Eobject3:
      {
        eventMgr().eventActionStart(
                player, getId(), EventActionProcessUpperShort,
                [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                  Scene00014( quest, player );
                },
                nullptr, 0 );
        break;
      }
    }
  }

  void onWithinRange( World::Quest& quest, Entity::Player& player, uint32_t eventId, uint32_t param1, float x, float y, float z )
  {
    switch( param1 )
    {
      case( Eventrange0 ):
      {
        if( quest.getUI8AL() == 0 )
          Scene00003( quest, player );
        break;
      }
      case( Eventrange1 ):
      {
        if( quest.getUI8BH() == 0 )
          Scene00006( quest, player );
        break;
      }
      case( Eventrange2 ):
      {
        if( quest.getUI8BL() == 0 )
          Scene00009( quest, player );
        break;
      }
      case( Eventrange3 ):
      {
        if( quest.getUI8CH() == 0 )
          Scene00012( quest, player );
        break;
      }
    }
  }

  void onBNpcKill( World::Quest& quest, Entity::BNpc& bnpc, Entity::Player& player ) override
  {
    switch( bnpc.getLayoutId() )
    {
      case Enemy0:
      {
        quest.setUI8AL( 1 );
        break;
      }
      case Enemy1:
      {
        quest.setUI8BH( 1 );
        break;
      }
      case Enemy2:
      {
        quest.setUI8BL( 1 );
        break;
      }
      case Enemy3:
      {
        quest.setUI8CH( 1 );
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
    quest.setUI8AH( quest.getUI8AH() + 1 );
    quest.setUI8CL( quest.getUI8CL() + 1 );

    eventMgr().sendNotice( player, getId(), 0, { quest.getUI8AH(), 4, player.getQuestItemIcon( Item0 ) } );

    if( quest.getUI8AH() >= 4 )
    {
      quest.setUI8AL( 0 );
      quest.setSeq( Seq2 );
      quest.setUI8BH( 4 );
    }
  }

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, NONE, bindSceneReturn( &SubWil038::Scene00000Return ) );
  }

  void Scene00000Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 ) // accept quest
    {
      Scene00090( quest, player );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, NONE, bindSceneReturn( &SubWil038::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, NONE, bindSceneReturn( &SubWil038::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    auto instance = teriMgr().getTerritoryByGuId( player.getTerritoryId() );
    auto enemy = instance->createBNpcFromLayoutId( Enemy0, 150 /*TODO: Find the right value*/, Common::BNpcType::Enemy, player.getId() );
    enemy->hateListAdd( player.getAsChara(), 10000 );
    enemy->aggro( player.getAsChara() );
    Scene00004( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, NONE, bindSceneReturn( &SubWil038::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, NONE, bindSceneReturn( &SubWil038::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setBitFlag8( 2, true );
    checkCompletition( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00006( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 6, NONE, bindSceneReturn( &SubWil038::Scene00006Return ) );
  }

  void Scene00006Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    auto instance = teriMgr().getTerritoryByGuId( player.getTerritoryId() );
    auto enemy = instance->createBNpcFromLayoutId( Enemy1, 150 /*TODO: Find the right value*/, Common::BNpcType::Enemy, player.getId() );
    enemy->hateListAdd( player.getAsChara(), 10000 );
    enemy->aggro( player.getAsChara() );
    Scene00007( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00007( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 7, NONE, bindSceneReturn( &SubWil038::Scene00007Return ) );
  }

  void Scene00007Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

  }

  //////////////////////////////////////////////////////////////////////

  void Scene00008( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 8, NONE, bindSceneReturn( &SubWil038::Scene00008Return ) );
  }

  void Scene00008Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setBitFlag8( 3, true );
    checkCompletition( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00009( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 9, NONE, bindSceneReturn( &SubWil038::Scene00009Return ) );
  }

  void Scene00009Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    auto instance = teriMgr().getTerritoryByGuId( player.getTerritoryId() );
    auto enemy = instance->createBNpcFromLayoutId( Enemy2, 150 /*TODO: Find the right value*/, Common::BNpcType::Enemy, player.getId() );
    enemy->hateListAdd( player.getAsChara(), 10000 );
    enemy->aggro( player.getAsChara() );
    Scene00010( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00010( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 10, NONE, bindSceneReturn( &SubWil038::Scene00010Return ) );
  }

  void Scene00010Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

  }

  //////////////////////////////////////////////////////////////////////

  void Scene00011( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 11, NONE, bindSceneReturn( &SubWil038::Scene00011Return ) );
  }

  void Scene00011Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setBitFlag8( 4, true );
    checkCompletition( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00012( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 12, NONE, bindSceneReturn( &SubWil038::Scene00012Return ) );
  }

  void Scene00012Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    auto instance = teriMgr().getTerritoryByGuId( player.getTerritoryId() );
    auto enemy = instance->createBNpcFromLayoutId( Enemy3, 150 /*TODO: Find the right value*/, Common::BNpcType::Enemy, player.getId() );
    enemy->hateListAdd( player.getAsChara(), 10000 );
    enemy->aggro( player.getAsChara() );
    Scene00013( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00013( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 13, NONE, bindSceneReturn( &SubWil038::Scene00013Return ) );
  }

  void Scene00013Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

  }

  //////////////////////////////////////////////////////////////////////

  void Scene00014( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 14, NONE, bindSceneReturn( &SubWil038::Scene00014Return ) );
  }

  void Scene00014Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setBitFlag8( 5, true );
    checkCompletition( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00015( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 15, NONE, bindSceneReturn( &SubWil038::Scene00015Return ) );
  }

  void Scene00015Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      Scene00016( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00016( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 16, NONE, bindSceneReturn( &SubWil038::Scene00016Return ) );
  }

  void Scene00016Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 1, 0 );
    quest.setSeq( Seq3 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00017( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 17, FADE_OUT | HIDE_UI, bindSceneReturn( &SubWil038::Scene00017Return ) );
  }

  void Scene00017Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendNotice( player, getId(), 2, { player.getQuestItemIcon( Item1 ) } );
    quest.setSeq( SeqFinish );
    quest.setUI8BH( 1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00018( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 18, NONE, bindSceneReturn( &SubWil038::Scene00018Return ) );
  }

  void Scene00018Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      Scene00019( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00019( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 19, NONE, bindSceneReturn( &SubWil038::Scene00019Return ) );
  }

  void Scene00019Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
    {
        player.finishQuest( getId(), result.getResult( 1 ) );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00090( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 90, FADE_OUT | HIDE_UI, bindSceneReturn( &SubWil038::Scene00090Return ) );
  }

  void Scene00090Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( Seq1 );
  }
};

EXPOSE_SCRIPT( SubWil038 );