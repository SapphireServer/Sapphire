// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include <Actor/Player.h>
#include <Actor/BNpc.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>

#include "Manager/TerritoryMgr.h"
#include "Territory/Territory.h"

// Quest Script: SubFst054_00160
// Quest Name: Slimy Hollows
// Quest ID: 65696
// Start NPC: 1000494 (Finnea)
// End NPC: 1000494 (Finnea)

using namespace Sapphire;

class SubFst054 : public Sapphire::ScriptAPI::QuestScript
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

    /// Countable Num: 3 Seq: 1 Event: 1 Listener: 2000043
    /// Countable Num: 1 Seq: 255 Event: 8 Listener: 2000043
    // Steps in this quest ( 0 is before accepting, 
    // 1 is first, 255 means ready for turning it in
    enum Sequence : uint8_t
    {
      Seq0 = 0,
      Seq1 = 1,
      SeqFinish = 255,
    };

    // Entities found in the script data of the quest
    static constexpr auto Actor0 = 1000494; // Finnea ( Pos: 48.796200 -24.002100 220.072006  Teri: 148 )
    static constexpr auto Enemy0 = 1886902; // 
    static constexpr auto Enemy1 = 1886903; // 
    static constexpr auto Enemy2 = 1887083; // 
    static constexpr auto Enemy3 = 1887164; // 
    static constexpr auto Enemy4 = 1887165; // 
    static constexpr auto Enemy5 = 1887166; // 
    static constexpr auto Eobject0 = 2000043; // Moist Depression ( Pos: -56.046398 -32.181301 427.145996  Teri: 148 )
    static constexpr auto Eobject1 = 2000044; // Moist Depression ( Pos: -28.625700 -36.386002 472.592010  Teri: 148 )
    static constexpr auto Eobject2 = 2000045; // Moist Depression ( Pos: -94.169601 -35.144600 478.373993  Teri: 148 )
    static constexpr auto Item0 = 2000100;
    static constexpr auto Seq0Actor0 = 0; // 
    static constexpr auto Seq1Eobject0 = 1; // 
    static constexpr auto Seq1Eobject0Useitemno = 99; // Hecatoncheir Piledriver
    static constexpr auto Seq1Eobject0Useitemok = 100; // Hecatoncheir Blastmaster ( Pos: -135.210007 5.708900 -117.417999  Teri: 141 )
    static constexpr auto Seq1Eobject1 = 2; // Ruins Runner ( Pos: -5.462710 -1.142520 27.215000  Teri: 5 )
    static constexpr auto Seq1Eobject1Useitemno = 97; // Hecatoncheir Stonehauler
    static constexpr auto Seq1Eobject1Useitemok = 98; // Hecatoncheir Shockblocker
    static constexpr auto Seq1Eobject2 = 3; // Antelope Doe
    static constexpr auto Seq1Eobject2Useitemno = 95; // Flux Flan
    static constexpr auto Seq1Eobject2Useitemok = 96; // Hecatoncheir Overseer
    static constexpr auto Seq2Actor0 = 4; // Antelope Stag

  public:
    SubFst054() : Sapphire::ScriptAPI::QuestScript( 65696 ){}; 
    ~SubFst054() = default; 

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
          Scene00004( quest, player );
        break;
      }
      case Eobject0:
      {
        eventMgr().eventActionStart(
                player, getId(), 0x02,
                [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                  Scene00001( quest, player );
                },
                nullptr, 0 );
        break;
      }
      case Eobject1:
      {
        eventMgr().eventActionStart(
                player, getId(), 0x02,
                [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                  Scene00002( quest, player );
                },
                nullptr, 0 );
        break;
      }
      case Eobject2:
      {
        eventMgr().eventActionStart(
                player, getId(), 0x02,
                [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                  Scene00003( quest, player );
                },
                nullptr, 0 );
        break;
      }
    }
  }

  void onEventItem( World::Quest& quest, Entity::Player& player, uint64_t actorId ) override
  {
    switch( actorId )
    {
      case Eobject0:
      {
        if( quest.getSeq() == Seq1 )
          Scene00100( quest, player );
        break;
      }
      case Eobject1:
      {
        if( quest.getSeq() == Seq1 )
          Scene00098( quest, player );
        break;
      }
      case Eobject2:
      {
        if( quest.getSeq() == Seq1 )
          Scene00096( quest, player );
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
        checkCompletition( quest, player, 1 );
        break;
      }
      case Enemy1:
      {
        quest.setUI8BH( 1 );
        checkCompletition( quest, player, 1 );
        break;
      }
      case Enemy2:
      {
        quest.setUI8BL( 1 );
        checkCompletition( quest, player, 2 );
        break;
      }
      case Enemy3:
      {
        quest.setUI8CH( 1 );
        checkCompletition( quest, player, 2 );
        break;
      }
      case Enemy4:
      {
        quest.setUI8CL( 1 );
        checkCompletition( quest, player, 3 );
        break;
      }
      case Enemy5:
      {
        quest.setUI8DH( 1 );
        checkCompletition( quest, player, 3 );
        break;
      }
    }
  }

  private:
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void checkCompletition( World::Quest& quest, Entity::Player& player, uint16_t groupKill )
  {
    auto UI8AH = quest.getUI8AH(); // seq obj counter

    auto UI8AL = quest.getUI8AL();
    auto UI8BH = quest.getUI8BH();
    auto UI8BL = quest.getUI8BL();
    auto UI8CH = quest.getUI8CH();
    auto UI8CL = quest.getUI8CL();
    auto UI8DH = quest.getUI8DH();

    switch ( groupKill )
    {
      case( 1 ):
      {
        if( UI8AL  >= 1 && UI8BH >= 1 )
        {
          quest.setUI8AH( UI8AH + 1 );
          eventMgr().sendEventNotice( player, getId(), 0, 2, UI8AH + 1, 3 );
        }
        break;
      }
      case( 2 ):
      {
        if( UI8BL == 1 && UI8CH == 1 )
        {
          quest.setUI8AH( UI8AH + 1 );
          eventMgr().sendEventNotice( player, getId(), 0, 2, UI8AH + 1, 3 );
        }
        break;
      }
      case( 3 ):
      {
        if( UI8CL == 1 && UI8DH == 1 )
        {
          quest.setUI8AH( UI8AH + 1 );
          eventMgr().sendEventNotice( player, getId(), 0, 2, UI8AH + 1, 3 );
        }
        break;
      }
    }

    if( quest.getUI8AH() == 3 )
      quest.setSeq( SeqFinish );
  }

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, NONE, bindSceneReturn( &SubFst054::Scene00000Return ) );
  }

  void Scene00000Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )// accept quest
    {
      quest.setSeq( Seq1 );
      quest.setUI8DL( 3 );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00001( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 1, NONE, bindSceneReturn( &SubFst054::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, NONE, bindSceneReturn( &SubFst054::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, NONE, bindSceneReturn( &SubFst054::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, NONE, bindSceneReturn( &SubFst054::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00095( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 95, NONE, bindSceneReturn( &SubFst054::Scene00095Return ) );
  }

  void Scene00095Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00096( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 96, NONE, bindSceneReturn( &SubFst054::Scene00096Return ) );
  }

  void Scene00096Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setBitFlag8( 3, true );
    quest.setUI8DL( quest.getUI8DL() - 1 );

    auto instance = teriMgr().getTerritoryByGuId( player.getTerritoryId() );
    auto enemy0 = instance->createBNpcFromLayoutId( Enemy4, 150 /*TODO: Find the right value*/, Common::BNpcType::Enemy, player.getId() );
    auto enemy1 = instance->createBNpcFromLayoutId( Enemy5, 150 /*TODO: Find the right value*/, Common::BNpcType::Enemy, player.getId() );

    enemy0->setFlag( Entity::NoDeaggro );
    enemy0->hateListAdd( player.getAsChara(), 10000 );
    enemy1->setFlag( Entity::NoDeaggro );
    enemy1->hateListAdd( player.getAsChara(), 10000 );

  }

  //////////////////////////////////////////////////////////////////////

  void Scene00097( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 97, NONE, bindSceneReturn( &SubFst054::Scene00097Return ) );
  }

  void Scene00097Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00098( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 98, NONE, bindSceneReturn( &SubFst054::Scene00098Return ) );
  }

  void Scene00098Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setBitFlag8( 2, true );
    quest.setUI8DL( quest.getUI8DL() - 1 );

    auto instance = teriMgr().getTerritoryByGuId( player.getTerritoryId() );
    auto enemy0 = instance->createBNpcFromLayoutId( Enemy2, 150 /*TODO: Find the right value*/, Common::BNpcType::Enemy, player.getId() );
    auto enemy1 = instance->createBNpcFromLayoutId( Enemy3, 150 /*TODO: Find the right value*/, Common::BNpcType::Enemy, player.getId() );

    enemy0->setFlag( Entity::NoDeaggro );
    enemy0->hateListAdd( player.getAsChara(), 10000 );
    enemy1->setFlag( Entity::NoDeaggro );
    enemy1->hateListAdd( player.getAsChara(), 10000 );

  }

  //////////////////////////////////////////////////////////////////////

  void Scene00099( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 99, NONE, bindSceneReturn( &SubFst054::Scene00099Return ) );
  }

  void Scene00099Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00100( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 100, NONE, bindSceneReturn( &SubFst054::Scene00100Return ) );
  }

  void Scene00100Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setBitFlag8( 1, true );
    quest.setUI8DL( quest.getUI8DL() - 1 );

    auto instance = teriMgr().getTerritoryByGuId( player.getTerritoryId() );
    auto enemy0 = instance->createBNpcFromLayoutId( Enemy0, 150 /*TODO: Find the right value*/, Common::BNpcType::Enemy, player.getId() );
    auto enemy1 = instance->createBNpcFromLayoutId( Enemy1, 150 /*TODO: Find the right value*/, Common::BNpcType::Enemy, player.getId() );

    enemy0->setFlag( Entity::NoDeaggro );
    enemy0->hateListAdd( player.getAsChara(), 10000 );
    enemy1->setFlag( Entity::NoDeaggro );
    enemy1->hateListAdd( player.getAsChara(), 10000 );
  }

};

EXPOSE_SCRIPT( SubFst054 );