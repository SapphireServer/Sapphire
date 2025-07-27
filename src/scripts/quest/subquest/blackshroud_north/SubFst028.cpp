// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include "Manager/EventMgr.h"
#include <Actor/BNpc.h>
#include <Actor/Player.h>
#include <ScriptObject.h>
#include <Service.h>

#include "Manager/TerritoryMgr.h"
#include "Territory/Territory.h"

// Quest Script: SubFst028_00171
// Quest Name: The Valued Vilekin
// Quest ID: 65707
// Start NPC: 1000629
// End NPC: 1000612

using namespace Sapphire;

class SubFst028 : public Sapphire::ScriptAPI::QuestScript
{

private:
  // Basic quest information
  // Quest vars / flags used
  // BitFlag8
  // UI8AL
  // UI8BH

  /// Countable Num: 1 Seq: 1 Event: 1 Listener: 2000140
  /// Countable Num: 1 Seq: 2 Event: 5 Listener: 163
  /// Countable Num: 1 Seq: 255 Event: 1 Listener: 2000142
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
  static constexpr auto Actor0 = 1000629;  // Bodwine ( Pos: 345.510010 -5.569580 343.891998  Teri: 154 )
  static constexpr auto Actor1 = 1000612;  // Guithrit ( Pos: 357.983002 8.934140 214.492004  Teri: 154 )
  static constexpr auto Enemy0 = 2653890;  //
  static constexpr auto Eobject0 = 2000140;// Tangled Undergrowth ( Pos: 200.882004 -30.272900 346.106995  Teri: 154 )
  static constexpr auto Eobject1 = 2000142;// Tangled Undergrowth ( Pos: 200.942993 -29.967100 346.170013  Teri: 154 )
  static constexpr auto EventActionSearch = 1;
  static constexpr auto Item0 = 2000144;
  static constexpr auto Seq0Actor0 = 0;                 //
  static constexpr auto Seq1Eobject0 = 1;               //
  static constexpr auto Seq1Eobject0Eventactionno = 99; // Hecatoncheir Piledriver
  static constexpr auto Seq1Eobject0Eventactionok = 100;// Hecatoncheir Blastmaster ( Pos: -135.210007 5.708900 -117.417999  Teri: 141 )
  static constexpr auto Seq2Eobject1 = 2;               // Ruins Runner ( Pos: -5.462710 -1.142520 27.215000  Teri: 5 )
  static constexpr auto Seq2Eobject1Eventactionno = 97; // Hecatoncheir Stonehauler
  static constexpr auto Seq2Eobject1Eventactionok = 98; // Hecatoncheir Shockblocker
  static constexpr auto Seq3Actor1 = 3;                 // Antelope Doe
  static constexpr auto Seq3Actor1Npctradeno = 95;      // Flux Flan
  static constexpr auto Seq3Actor1Npctradeok = 96;      // Hecatoncheir Overseer


public:
  SubFst028() : Sapphire::ScriptAPI::QuestScript( 65707 ) {};
  ~SubFst028() = default;

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
          Scene00003( quest, player );
        break;
      }
      case Eobject0:
      {
        if( quest.getSeq() == Seq1 )
        {
          eventMgr().eventActionStart(
                  player, getId(), EventActionSearch,
                  [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                    Scene00001( quest, player );
                  },
                  nullptr, 0 );
        }
        break;
      }
      case Eobject1:
      {
        if( quest.getSeq() == Seq2 )
        {
          eventMgr().eventActionStart(
                  player, getId(), EventActionSearch,
                  [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                    Scene00002( quest, player );
                  },
                  nullptr, 0 );
        }
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
        eventMgr().sendEventNotice( player, getId(), 0, 0 );
        quest.setSeq( Seq2 );
        break;
      }
    }
  }

private:
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &SubFst028::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, NONE, bindSceneReturn( &SubFst028::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    Scene00100( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, NONE, bindSceneReturn( &SubFst028::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    Scene00098( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, NONE, bindSceneReturn( &SubFst028::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      Scene00096( quest, player );
    else
      Scene00095( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00095( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 95, NONE, bindSceneReturn( &SubFst028::Scene00095Return ) );
  }

  void Scene00095Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00096( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 96, NONE, bindSceneReturn( &SubFst028::Scene00096Return ) );
  }

  void Scene00096Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
    {
        player.finishQuest( getId(), result.getResult( 1 ) );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00097( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 97, NONE, bindSceneReturn( &SubFst028::Scene00097Return ) );
  }

  void Scene00097Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00098( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 98, NONE, bindSceneReturn( &SubFst028::Scene00098Return ) );
  }

  void Scene00098Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8BH( 1 );
    eventMgr().sendEventNotice( player, getId(), 1, 0 );
    quest.setSeq( SeqFinish );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00099( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 99, NONE, bindSceneReturn( &SubFst028::Scene00099Return ) );
  }

  void Scene00099Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00100( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 100, NONE, bindSceneReturn( &SubFst028::Scene00100Return ) );
  }

  void Scene00100Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setBitFlag8( 1, true );
    auto instance = teriMgr().getTerritoryByGuId( player.getTerritoryId() );
    auto enemy = instance->createBNpcFromLayoutId( Enemy0, 150 /*TODO: Find the right value*/, Common::BNpcType::Enemy, player.getId() );
  }
};

EXPOSE_SCRIPT( SubFst028 );