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

// Quest Script: SubFst022_00170
// Quest Name: Harriers of the Hedgetree
// Quest ID: 65633
// Start NPC: 1000640
// End NPC: 1000612

using namespace Sapphire;

class SubFst022 : public Sapphire::ScriptAPI::QuestScript
{
  private:
    // Basic quest information 
    // Quest vars / flags used
    // BitFlag8
    // UI8AL
    // UI8BH

    /// Countable Num: 1 Seq: 1 Event: 1 Listener: 2000008 (Hedgetree)
    /// Countable Num: 5 Seq: 2 Event: 5 Listener: 113 (Harrier)
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
    static constexpr auto Actor0 = 1000640;   // Eadbert (Start NPC)
    static constexpr auto Enemy0 = 1450088;   // Harrier
    static constexpr auto Eobject0 = 2000008; // Hedgetree
    static constexpr auto EventActionSearch = 1;

  public:
    SubFst022() : Sapphire::ScriptAPI::QuestScript( 65633 ) {}; 
    ~SubFst022() = default; 

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
        if( quest.getSeq() == SeqFinish )
          Scene00002( quest, player );
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
        quest.setSeq( SeqFinish );
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
      eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &SubFst022::Scene00000Return ) );
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
      eventMgr().playQuestScene( player, getId(), 1, HIDE_HOTBAR, bindSceneReturn( &SubFst022::Scene00001Return ) );
    }

    void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
    {
      Scene00100( quest, player );
    }

    //////////////////////////////////////////////////////////////////////

    void Scene00002( World::Quest& quest, Entity::Player& player )
    {
      eventMgr().playQuestScene( player, getId(), 2, HIDE_HOTBAR, bindSceneReturn( &SubFst022::Scene00002Return ) );
    }

    void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
    {
      if( result.getResult( 0 ) == 1 )
      {
        player.finishQuest( getId(), result.getResult( 1 ) );
      }
    }

    void Scene00100( World::Quest& quest, Entity::Player& player )
    {
      eventMgr().playQuestScene( player, getId(), 100, HIDE_HOTBAR, bindSceneReturn( &SubFst022::Scene00100Return ) );
    }

    void Scene00100Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
    {
      quest.setBitFlag8( 1, true );
      auto instance = teriMgr().getTerritoryByGuId( player.getTerritoryId() );
      auto enemy = instance->createBNpcFromLayoutId( Enemy0, 150 /*TODO: Find the right value*/, Common::BNpcType::Enemy, player.getId() );
    }

    void Scene00099( World::Quest& quest, Entity::Player& player )
    {

    }
};

EXPOSE_SCRIPT( SubFst022 );