// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include "Manager/EventMgr.h"
#include <Actor/Player.h>
#include <Actor/BNpc.h>
#include <ScriptObject.h>
#include <Service.h>

#include "Actor/BNpc.h"
#include "Manager/TerritoryMgr.h"
#include "Territory/Territory.h"

// Quest Script: SubWil073_00327
// Quest Name: Spriggan Cleaning
// Quest ID: 65863
// Start NPC: 1001447 (Warin)
// End NPC: 1001447 (Warin)

using namespace Sapphire;

class SubWil073 : public Sapphire::ScriptAPI::QuestScript
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
    // UI8DL
    // UI8EH

    /// Countable Num: 4 Seq: 1 Event: 1 Listener: 2000377
    /// Countable Num: 1 Seq: 255 Event: 5 Listener: 100
    // Steps in this quest ( 0 is before accepting, 
    // 1 is first, 255 means ready for turning it in
    enum Sequence : uint8_t
    {
      Seq0 = 0,
      Seq1 = 1,
      SeqFinish = 255,
    };

    // Entities found in the script data of the quest
    static constexpr auto Actor0 = 1001447; // Warin ( Pos: -32.639099 -1.033260 -148.485992  Teri: 141 )
    static constexpr auto Enemy0 = 3742257; // 
    static constexpr auto Enemy1 = 3742258; // 
    static constexpr auto Enemy2 = 3742259; // 
    static constexpr auto Enemy3 = 3742261; // 
    static constexpr auto Eobject0 = 2000377; // Pockmarked Silver Ore ( Pos: -134.695999 6.168210 -116.594002  Teri: 141 )
    static constexpr auto Eobject1 = 2000378; // Pockmarked Silver Ore ( Pos: -95.958298 -1.021940 -163.731003  Teri: 141 )
    static constexpr auto Eobject2 = 2000379; // Pockmarked Silver Ore ( Pos: -103.938004 0.491295 -213.695007  Teri: 141 )
    static constexpr auto Eobject3 = 2000380; // Pockmarked Silver Ore ( Pos: -1.174590 -1.322410 -111.265999  Teri: 141 )
    static constexpr auto EventActionSearch = 1;
    static constexpr auto Seq0Actor0 = 0; // 
    static constexpr auto Seq1Eobject0 = 1; // 
    static constexpr auto Seq1Eobject0Eventactionno = 99; // Hecatoncheir Piledriver
    static constexpr auto Seq1Eobject0Eventactionok = 100; // Hecatoncheir Blastmaster ( Pos: -135.210007 5.708900 -117.417999  Teri: 141 )
    static constexpr auto Seq1Eobject1 = 2; // Ruins Runner ( Pos: -5.462710 -1.142520 27.215000  Teri: 5 )
    static constexpr auto Seq1Eobject1Eventactionno = 97; // Hecatoncheir Stonehauler
    static constexpr auto Seq1Eobject1Eventactionok = 98; // Hecatoncheir Shockblocker
    static constexpr auto Seq1Eobject2 = 3; // Antelope Doe
    static constexpr auto Seq1Eobject2Eventactionno = 95; // Flux Flan
    static constexpr auto Seq1Eobject2Eventactionok = 96; // Hecatoncheir Overseer
    static constexpr auto Seq1Eobject3 = 4; // Antelope Stag
    static constexpr auto Seq1Eobject3Eventactionno = 93; // Sargas
    static constexpr auto Seq1Eobject3Eventactionok = 94; // Shaula
    static constexpr auto Seq2Actor0 = 5; // Opo-opo

  public:
    SubWil073() : Sapphire::ScriptAPI::QuestScript( 65863 ){}; 
    ~SubWil073() = default; 

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
          Scene00005( quest, player );
        break;
      }
      case Eobject0:
      {
        eventMgr().eventActionStart(
                player, getId(), EventActionSearch,
                [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                  Scene00094( quest, player );
                },
                nullptr, 0 );
        break;

      }
      case Eobject1:
      {
        eventMgr().eventActionStart(
                player, getId(), EventActionSearch,
                [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                  Scene00095( quest, player );
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
      case Eobject3:
      {
        eventMgr().eventActionStart(
                player, getId(), EventActionSearch,
                [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                  Scene00097( quest, player );
                },
                nullptr, 0 );
        break;
      }
    }
  }

  void onEventItem( World::Quest& quest, Entity::Player& player, uint64_t actorId ) override
  {
  }

  void onBNpcKill( World::Quest& quest, Entity::BNpc& bnpc, Entity::Player& player ) override
  {
    switch (bnpc.getLayoutId())
    {
      case Enemy0:
      {
        quest.setUI8AL( 1 );
        quest.setUI8BH( 1 );
        checkQuestCompletion( quest, player );
        break;
      }
      case Enemy1:
      {
        quest.setUI8BL( 1 );
        quest.setUI8CH( 1 );
        checkQuestCompletion( quest, player );
        break;
      }
      case Enemy2:
      {
        quest.setUI8CL( 1 );
        quest.setUI8DH( 1 );
        checkQuestCompletion( quest, player );
        break;
      }
      case Enemy3:
      {
        quest.setUI8DL( 1 );
        quest.setUI8EH( 1 );
        checkQuestCompletion( quest, player );
        break;
      }
    }
  }

  private:
    void checkQuestCompletion( World::Quest& quest, Entity::Player& player )
    {
      quest.setUI8AH( quest.getUI8AH() + 1 );
      eventMgr().sendEventNotice( player, getId(), 0, 2, quest.getUI8AH(), 4 );

      if( quest.getUI8AH() >= 4 )
      {
        quest.setUI8AL( 0 );
        quest.setUI8BH( 0 );
        quest.setUI8BL( 0 );
        quest.setUI8CH( 0 );
        quest.setUI8CL( 0 );
        quest.setUI8DH( 0 );
        quest.setUI8DL( 0 );
        quest.setUI8EH( 0 );
        quest.setUI8AH( 0 );
        quest.setBitFlag8( 1, false );
        quest.setBitFlag8( 2, false );
        quest.setBitFlag8( 3, false );
        quest.setBitFlag8( 4, false );
        quest.setSeq( SeqFinish );
      }
    }
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &SubWil073::Scene00000Return ) );
  }

  void Scene00000Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 ) // accept quest
    {
      Scene00001( quest, player );
    }


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00001( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 1, HIDE_HOTBAR, bindSceneReturn( &SubWil073::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( Seq1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, NONE, bindSceneReturn( &SubWil073::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, NONE, bindSceneReturn( &SubWil073::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, NONE, bindSceneReturn( &SubWil073::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, HIDE_HOTBAR, bindSceneReturn( &SubWil073::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
    }

  }

  //////////////////////////////////////////////////////////////////////

  void Scene00093( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 93, NONE, bindSceneReturn( &SubWil073::Scene00093Return ) );
  }

  void Scene00093Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00094( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 94, NONE, bindSceneReturn( &SubWil073::Scene00094Return ) );
  }

  void Scene00094Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    auto instance = teriMgr().getTerritoryByGuId( player.getTerritoryId() );
    auto enemy = instance->createBNpcFromLayoutId( Enemy0, 1220 /*Find the right value*/, Common::BNpcType::Enemy );

    enemy->setTriggerOwnerId( player.getId() );
    enemy->hateListAddDelayed( player.getAsPlayer(), 1 );
    quest.setBitFlag8( 1, true );

  }

  //////////////////////////////////////////////////////////////////////

  void Scene00095( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 95, NONE, bindSceneReturn( &SubWil073::Scene00095Return ) );
  }

  void Scene00095Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    auto instance = teriMgr().getTerritoryByGuId( player.getTerritoryId() );
    auto enemy = instance->createBNpcFromLayoutId( Enemy1, 1220 /*Find the right value*/, Common::BNpcType::Enemy );

    enemy->setTriggerOwnerId( player.getId() );
    enemy->hateListAddDelayed( player.getAsPlayer(), 1 );
    quest.setBitFlag8( 2, true );

  }

  //////////////////////////////////////////////////////////////////////

  void Scene00096( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 96, NONE, bindSceneReturn( &SubWil073::Scene00096Return ) );
  }

  void Scene00096Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    auto instance = teriMgr().getTerritoryByGuId( player.getTerritoryId() );
    auto enemy = instance->createBNpcFromLayoutId( Enemy2, 1220 /*Find the right value*/, Common::BNpcType::Enemy );

    enemy->setTriggerOwnerId( player.getId() );
    enemy->hateListAddDelayed( player.getAsPlayer(), 1 );
    quest.setBitFlag8( 3, true );


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00097( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 97, NONE, bindSceneReturn( &SubWil073::Scene00097Return ) );
  }

  void Scene00097Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    auto instance = teriMgr().getTerritoryByGuId( player.getTerritoryId() );
    auto enemy = instance->createBNpcFromLayoutId( Enemy3, 1220 /*Find the right value*/, Common::BNpcType::Enemy );

    enemy->setTriggerOwnerId( player.getId() );
    enemy->hateListAddDelayed( player.getAsPlayer(), 1 );
    quest.setBitFlag8( 4, true );

  }

  //////////////////////////////////////////////////////////////////////

  void Scene00098( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 98, NONE, bindSceneReturn( &SubWil073::Scene00098Return ) );
  }

  void Scene00098Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00099( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 99, NONE, bindSceneReturn( &SubWil073::Scene00099Return ) );
  }

  void Scene00099Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00100( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 100, NONE, bindSceneReturn( &SubWil073::Scene00100Return ) );
  }

  void Scene00100Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

};

EXPOSE_SCRIPT( SubWil073 );