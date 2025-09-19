// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>
#include <Actor/BNpc.h>

// Quest Script: SubWil068_00322
// Quest Name: Listen to Your Fish
// Quest ID: 65858
// Start NPC: 1001457 (Hihiyaja)
// End NPC: 1001460 (Wowobaru)

using namespace Sapphire;

class SubWil068 : public Sapphire::ScriptAPI::QuestScript
{
  private:
    // Basic quest information 
    // Quest vars / flags used
    // UI8AL
    // UI8BH

    /// Countable Num: 7 Seq: 1 Event: 9 Listener: 302
    /// Countable Num: 1 Seq: 255 Event: 1 Listener: 1001460
    // Steps in this quest ( 0 is before accepting, 
    // 1 is first, 255 means ready for turning it in
    enum Sequence : uint8_t
    {
      Seq0 = 0,
      Seq1 = 1,
      SeqFinish = 255,
    };

    // Entities found in the script data of the quest
    static constexpr auto Actor0 = 1001457; // Hihiyaja ( Pos: 67.078903 0.919069 255.649002  Teri: 141 )
    static constexpr auto Actor1 = 1001460; // Wowobaru ( Pos: -97.032204 -11.350000 -48.684399  Teri: 141 )
    static constexpr auto Enemy0 = 308;     //wrong -> 302 Dusty Mongrel ( Pos: -181.960999 0.178183 435.544006  Teri: 153 )
    static constexpr auto Item0 = 2000214;

  public:
    SubWil068() : Sapphire::ScriptAPI::QuestScript( 65858 ){}; 
    ~SubWil068() = default; 

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
          Scene00002( quest, player );
        break;
      }
    }
  }

  void onEventItem( World::Quest& quest, Entity::Player& player, uint64_t actorId ) override
  {
  }

  void onBNpcKill( World::Quest& quest, Entity::BNpc& bnpc, Entity::Player& player ) override
  {
    if( quest.getSeq() == Seq1 && quest.getUI8AL() < 4 )
    {
      switch( bnpc.getBNpcNameId() )
      {
        case Enemy0:
        {
          quest.setUI8AL( quest.getUI8AL() + 1 );
          quest.setUI8BH( quest.getUI8BH() + 1 );

          
          eventMgr().sendNotice( player, getId(), 0, { quest.getUI8AL(), 4, player.getQuestItemIcon( Item0 ) } );
          break;
        }
      }

      if ( quest.getUI8AL() >= 4 )
        quest.setSeq( SeqFinish );
    }
    
  }

  private:
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, NONE, bindSceneReturn( &SubWil068::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, NONE, bindSceneReturn( &SubWil068::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, NONE, bindSceneReturn( &SubWil068::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      Scene00003( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, NONE, bindSceneReturn( &SubWil068::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
    {
        player.finishQuest( getId(), result.getResult( 1 ) );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, NONE, bindSceneReturn( &SubWil068::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {


  }

};

EXPOSE_SCRIPT( SubWil068 );