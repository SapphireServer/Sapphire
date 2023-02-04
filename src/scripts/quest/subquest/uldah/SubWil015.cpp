// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include "Actor/BNpc.h"
#include "Manager/EventMgr.h"
#include <Actor/Player.h>
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: SubWil015_00163
// Quest Name: Tougher than Leather
// Quest ID: 65699
// Start NPC: 1003898 (Jajakuta)
// End NPC: 1003898 (Jajakuta)

using namespace Sapphire;

class SubWil015 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // UI8AL
  // UI8BH

  /// Countable Num: 5 Seq: 1 Event: 9 Listener: 205
  /// Countable Num: 1 Seq: 255 Event: 1 Listener: 1003898
  // Steps in this quest ( 0 is before accepting,
  // 1 is first, 255 means ready for turning it in
  enum Sequence : uint8_t
  {
    Seq0 = 0,
    Seq1 = 1,
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1003898;// Jajakuta ( Pos: -109.903999 4.500090 -73.801903  Teri: 130 )
  static constexpr auto Enemy0 = 205;    // Mottled Eft ( Pos: 15.554700 0.648601 -59.534698  Teri: 141 )
  static constexpr auto Item0 = 2000138;

public:
  SubWil015() : Sapphire::ScriptAPI::QuestScript( 65699 ){};
  ~SubWil015() = default;

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
    }
  }

  void onEventItem( World::Quest& quest, Entity::Player& player, uint64_t actorId ) override
  {
    if( quest.getSeq() != Seq1 ) return;

    quest.setUI8AL( quest.getUI8AL() + 1); //increases the counter
    eventMgr().sendEventNotice( player, getId(), 1, 2, quest.getUI8AL(), 5 );
    Sapphire::World::Manager::PlayerMgr::sendDebug( player, "UI8BH: {0} UI8AL: {1}", quest.getUI8BH(), quest.getUI8AL() );
    //increase UI8BH by 1
//    if( actorId == Enemy0 )
//    {
//      quest.setUI8BH( quest.getUI8BH() + 1 );
//    }
  }

  void onBNpcKill( World::Quest& quest, Entity::BNpc& bnpc, Entity::Player& player ) override
  {
    if( bnpc.getBNpcBaseId() != Enemy0 )
      return;
    else
    {
      quest.setUI8BH( quest.getUI8BH() + 1 ); //adds to key items
      onEventItem(quest,player,0);

//      auto currentKillCount = quest.getUI8AL();
//      if( currentKillCount < 6 )
//      {
//        quest.setUI8AL( 1 );
//        player.addItem(Item0, 1, false, false, true);
//        quest.setUI8BH( quest.getUI8BH() + 1 );
//        eventMgr().sendEventNotice( player, getId(), 1, 2, currentKillCount + 1, 6 );
////        quest.setUI8AL( currentKillCount + 1 );
//      }
    }
  }

private:
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &SubWil015::Scene00000Return ) );
  }

  void Scene00000Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )// accept quest
    {
      quest.setSeq( Seq1 );
      Scene00001( quest, player );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00001( World::Quest& quest, Entity::Player& player )
  {
    //inventory trade scene
    eventMgr().playQuestScene( player, getId(), 1, NONE, bindSceneReturn( &SubWil015::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, NONE, bindSceneReturn( &SubWil015::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    //if obtained all items
    //Scene00003(quest, player);
  }

  //////////////////////////////////////////////////////////////////////

  //Turn quest in
  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, NONE, bindSceneReturn( &SubWil015::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult( 1 ) );//calls into questMgr().giveQuestRewards
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, NONE, bindSceneReturn( &SubWil015::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }
};

EXPOSE_SCRIPT( SubWil015 );