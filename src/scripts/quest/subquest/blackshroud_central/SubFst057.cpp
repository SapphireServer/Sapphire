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

// Quest Script: SubFst057_00378
// Quest Name: Look, but Won't Touch
// Quest ID: 65914
// Start NPC: 1000748 (Roseline)
// End NPC: 1000748 (Roseline)

using namespace Sapphire;

class SubFst057 : public Sapphire::ScriptAPI::QuestScript
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

    /// Countable Num: 2 Seq: 1 Event: 1 Listener: 2001083
    /// Countable Num: 1 Seq: 255 Event: 5 Listener: 10
    // Steps in this quest ( 0 is before accepting, 
    // 1 is first, 255 means ready for turning it in
    enum Sequence : uint8_t
    {
      Seq0 = 0,
      Seq1 = 1,
      SeqFinish = 255,
    };

    // Entities found in the script data of the quest
    static constexpr auto Actor0 = 1000748; // Roseline ( Pos: -125.220001 4.157380 -43.570301  Teri: 148 )
    static constexpr auto Enemy0 = 3812252; // 
    static constexpr auto Enemy1 = 3856501; // 
    static constexpr auto Eobject0 = 2001083; // Diremite Eggs ( Pos: -184.488998 41.923199 -128.647995  Teri: 148 )
    static constexpr auto Eobject1 = 2001084; // Diremite Eggs ( Pos: -127.776001 -1.133530 -60.947300  Teri: 148 )
    static constexpr auto EventActionSearch = 1;
    static constexpr auto Seq0Actor0 = 0; // 
    static constexpr auto Seq1Eobject0 = 1; // 
    static constexpr auto Seq1Eobject0Eventactionno = 99; // Hecatoncheir Piledriver
    static constexpr auto Seq1Eobject0Eventactionok = 100; // Hecatoncheir Blastmaster ( Pos: -135.210007 5.708900 -117.417999  Teri: 141 )
    static constexpr auto Seq1Eobject1 = 2; // Ruins Runner ( Pos: -5.462710 -1.142520 27.215000  Teri: 5 )
    static constexpr auto Seq1Eobject1Eventactionno = 97; // Hecatoncheir Stonehauler
    static constexpr auto Seq1Eobject1Eventactionok = 98; // Hecatoncheir Shockblocker
    static constexpr auto Seq2Actor0 = 3; // Antelope Doe

  public:
    SubFst057() : Sapphire::ScriptAPI::QuestScript( 65914 ){}; 
    ~SubFst057() = default; 

  //////////////////////////////////////////////////////////////////////
  // Event Handlers
  void onTalk( World::Quest& quest, Entity::Player& player, uint64_t actorId ) override
  {
    switch( actorId )
    {
      case Actor0:
      {
        if ( quest.getSeq() == Seq0 )
          Scene00000( quest, player );
        else if ( quest.getSeq() == SeqFinish )
          Scene00003( quest, player );
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
    }
  }

  void onEventItem( World::Quest& quest, Entity::Player& player, uint64_t actorId ) override
  {
  }

  void onBNpcKill( World::Quest& quest, Entity::BNpc& bnpc, Entity::Player& player ) override
  {
    switch( bnpc.getLayoutId() )
    {
      case Enemy0:
      {
        quest.setUI8AH( quest.getUI8AH() + 1 );
        eventMgr().sendEventNotice( player, getId(), 0, 2, quest.getUI8AH(), 2 );
        break;
      }
      case Enemy1:
      {
        quest.setUI8AH( quest.getUI8AH() + 1 );
        eventMgr().sendEventNotice( player, getId(), 0, 2, quest.getUI8AH(), 2 );
        break;
      }
    }

    if (quest.getUI8AH() == 2)
    {
      quest.setSeq( SeqFinish );
    }
  }

  private:
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, NONE, bindSceneReturn( &SubFst057::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, NONE, bindSceneReturn( &SubFst057::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    Scene00100( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, NONE, bindSceneReturn( &SubFst057::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    Scene00098( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, NONE, bindSceneReturn( &SubFst057::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00097( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 97, NONE, bindSceneReturn( &SubFst057::Scene00097Return ) );
  }

  void Scene00097Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00098( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 98, NONE, bindSceneReturn( &SubFst057::Scene00098Return ) );
  }

  void Scene00098Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setBitFlag8( 2, true );

    auto instance = teriMgr().getTerritoryByGuId( player.getTerritoryId() );
    auto enemy0 = instance->createBNpcFromLayoutId( Enemy1, 150 /*TODO: Find the right value*/, Common::BNpcType::Enemy, player.getId() );

    enemy0->setFlag( Entity::NoDeaggro );
    enemy0->hateListAdd( player.getAsChara(), 10000 );

  }

  //////////////////////////////////////////////////////////////////////

  void Scene00099( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 99, NONE, bindSceneReturn( &SubFst057::Scene00099Return ) );
  }

  void Scene00099Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00100( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 100, NONE, bindSceneReturn( &SubFst057::Scene00100Return ) );
  }

  void Scene00100Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setBitFlag8( 1, true );

    auto instance = teriMgr().getTerritoryByGuId( player.getTerritoryId() );
    auto enemy0 = instance->createBNpcFromLayoutId( Enemy0, 150 /*TODO: Find the right value*/, Common::BNpcType::Enemy, player.getId() );

    enemy0->setFlag( Entity::NoDeaggro );
    enemy0->hateListAdd( player.getAsChara(), 10000 );
  }

};

EXPOSE_SCRIPT( SubFst057 );