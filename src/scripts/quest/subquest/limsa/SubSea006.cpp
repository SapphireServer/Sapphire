// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>
#include <Actor/BNpc.h>

// Quest Script: SubSea006_00116
// Quest Name: A Sheepish Request
// Quest ID: 65652
// Start NPC: 1000959 (H'lahono)
// End NPC: 1000959 (H'lahono)

using namespace Sapphire;

class SubSea006 : public Sapphire::ScriptAPI::QuestScript
{
  private:
    // Basic quest information 
    // Quest vars / flags used
    // UI8AL
    // UI8BH

    /// Countable Num: 1 Seq: 1 Event: 1 Listener: 1003603
    /// Countable Num: 1 Seq: 2 Event: 9 Listener: 338
    /// Countable Num: 0 Seq: 255 Event: 1 Listener: 1000959
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
    static constexpr auto Actor0 = 1000959; // H'lahono ( Pos: -65.629097 41.977501 -139.421997  Teri: 128 )
    static constexpr auto Actor1 = 1003603; // Abylfarr ( Pos: 20.345800 20.000000 4.328660  Teri: 129 )
    static constexpr auto Enemy0 = 392;
    static constexpr auto Item0 = 2000450;

  public:
    SubSea006() : Sapphire::ScriptAPI::QuestScript( 65652 ){}; 
    ~SubSea006() = default; 

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
          Scene00003( quest, player );
        break;
      }
      case Actor1:
      {
        if( quest.getSeq() == Seq1 )
          Scene00002( quest, player );
        break;
      }
    }
  }

  void onBNpcKill( World::Quest& quest, Entity::BNpc& bnpc, Entity::Player& player ) override
  {
    if( quest.getSeq() == Seq2 )
    {
      switch( bnpc.getBNpcNameId() )
      {
        case Enemy0:
        {
          quest.setUI8AL( quest.getUI8AL() + 1 );
          quest.setUI8BH( quest.getUI8BH() + 1 );

          //eventMgr().sendEventNotice( player, getId(), 1, 2, quest.getUI8AL(), 4 );
          eventMgr().sendNotice( player, getId(), 1, { quest.getUI8AL(), 4, player.getQuestItemIcon( Item0 ) } );

          if( quest.getUI8AL() >= 4 )
            quest.setSeq( SeqFinish );
          break;
        }
      }
    }
  }

  private:
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, NONE, bindSceneReturn( &SubSea006::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, NONE, bindSceneReturn( &SubSea006::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, NONE, bindSceneReturn( &SubSea006::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 0, 0 );
    quest.setSeq( Seq2 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, NONE, bindSceneReturn( &SubSea006::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      Scene00004( quest, player );

  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, NONE, bindSceneReturn( &SubSea006::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
    {
        player.finishQuest( getId(), result.getResult( 1 ) );
    }
  }

};

EXPOSE_SCRIPT( SubSea006 );