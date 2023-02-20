// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: SubSea004_00114
// Quest Name: The Right Price
// Quest ID: 65650
// Start NPC: 1001217 (Swozblaet)
// End NPC: 1003272 (Baensyng)

using namespace Sapphire;

class SubSea004 : public Sapphire::ScriptAPI::QuestScript
{
  private:
    // Basic quest information 
    // Quest vars / flags used
    // BitFlag8
    // UI8AL
    // UI8BH
    // UI8BL
    // UI8CH

    /// Countable Num: 4 Seq: 1 Event: 1 Listener: 1001203
    /// Countable Num: 1 Seq: 1 Event: 1 Listener: 1001208
    /// Countable Num: 0 Seq: 1 Event: 1 Listener: 1003254
    /// Countable Num: 0 Seq: 255 Event: 1 Listener: 1003272
    // Steps in this quest ( 0 is before accepting, 
    // 1 is first, 255 means ready for turning it in
    enum Sequence : uint8_t
    {
      Seq0 = 0,
      Seq1 = 1,
      SeqFinish = 255,
    };

    // Entities found in the script data of the quest
    static constexpr auto Actor0 = 1001217; // Swozblaet ( Pos: -140.856003 18.173401 17.013700  Teri: 129 )
    static constexpr auto Actor1 = 1001203; // Iron Thunder ( Pos: -156.602997 18.173401 20.920000  Teri: 129 )
    static constexpr auto Actor2 = 1001208; // Kyokyoroon ( Pos: -228.167999 15.976100 50.644600  Teri: 129 )
    static constexpr auto Actor3 = 1003254; // Syneyhil ( Pos: -246.600998 16.189800 37.125099  Teri: 129 )
    static constexpr auto Actor4 = 1003272; // Baensyng ( Pos: -262.928009 16.159300 51.407600  Teri: 129 )
    static constexpr auto Item0 = 2000460;

  public:
    SubSea004() : Sapphire::ScriptAPI::QuestScript( 65650 ){}; 
    ~SubSea004() = default; 

  //////////////////////////////////////////////////////////////////////
  // Event Handlers
  void onTalk( World::Quest& quest, Entity::Player& player, uint64_t actorId ) override
  {
    switch( actorId )
    {
      case Actor0:
      {
        Scene00000( quest, player );
        break;
      }
      case Actor1:
      {
        Scene00002( quest, player );
        break;
      }
      case Actor2:
      {
        Scene00003( quest, player );
        break;
      }
      case Actor3:
      {
        Scene00004( quest, player );
        break;
      }
      case Actor4:
      {
        Scene00005( quest, player );
        break;
      }
    }
  }

  void onEventItem( World::Quest& quest, Entity::Player& player, uint64_t actorId ) override
  {
  }


private:
  void checkQuestCompletion( World::Quest& quest, Entity::Player& player, uint32_t varIdx )
  {
    if (varIdx == 1)
    {
      auto actor1Talked = quest.getUI8AL();
      auto actor2Talked = quest.getUI8BH();
      auto actor3Talked = quest.getUI8BL();
      if( actor1Talked && actor2Talked && actor3Talked )
      {
        quest.setSeq( SeqFinish );
        quest.setUI8CH( 1 );
      }
    }
  }
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &SubSea004::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, HIDE_HOTBAR, bindSceneReturn( &SubSea004::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( Seq1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, HIDE_HOTBAR, bindSceneReturn( &SubSea004::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 0, 0 );
    quest.setUI8AL( 1 );
    checkQuestCompletion( quest, player, 1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, HIDE_HOTBAR, bindSceneReturn( &SubSea004::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 1, 0 );
    quest.setUI8BH( 1 );
    checkQuestCompletion( quest, player, 1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, HIDE_HOTBAR, bindSceneReturn( &SubSea004::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 2, 0 );
    quest.setUI8BL( 1 );
    checkQuestCompletion( quest, player, 1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, HIDE_HOTBAR, bindSceneReturn( &SubSea004::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 ) // hand in item
    {
      Scene00006( quest, player );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00006( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 6, HIDE_HOTBAR, bindSceneReturn( &SubSea004::Scene00006Return ) );
  }

  void Scene00006Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId() );
    }
  }

};

EXPOSE_SCRIPT( SubSea004 );