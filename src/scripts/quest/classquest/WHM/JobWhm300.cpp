// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include "Manager/EventMgr.h"
#include <Actor/Player.h>
#include <ScriptObject.h>
#include <Service.h>


#include "Actor/BNpc.h"
#include "Manager/TerritoryMgr.h"
#include "Territory/Territory.h"

// Quest Script: JobWhm300_01079
// Quest Name: Seer Folly
// Quest ID: 66615
// Start NPC: 1000692
// End NPC: 1006751

using namespace Sapphire;

class JobWhm300 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // BitFlag8
  // UI8AL
  // UI8BH

  /// Countable Num: 0 Seq: 1 Event: 1 Listener: 1007850
  /// Countable Num: 0 Seq: 255 Event: 1 Listener: 2002391
  // Steps in this quest ( 0 is before accepting,
  // 1 is first, 255 means ready for turning it in
  enum Sequence : uint8_t
  {
    Seq0 = 0,
    Seq1 = 1,
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1000692;//E-Sumi-Yan
  static constexpr auto Actor1 = 1007850;//Raya-O-Senna (Seq1)
  static constexpr auto Actor2 = 1007851;
  static constexpr auto Actor3 = 1006751;//Raya-O-Senna (SeqFinish)
  static constexpr auto Eobject0 = 2002391;
  static constexpr auto EventActionSearch = 1;
  static constexpr auto GearsetUnlock = 1905;
  static constexpr auto Item0 = 2000938;
  static constexpr auto LocAction0Wsget = 995;
  static constexpr auto LocLogMes = 3651;
  static constexpr auto LocVfx1 = 241;
  static constexpr auto LocVfx2 = 413;
  static constexpr auto LocWs = 136;
  static constexpr auto Questbattle0 = 75;
  static constexpr auto Territorytype0 = 319;
  static constexpr auto UnlockImageClass = 59;

public:
  JobWhm300() : Sapphire::ScriptAPI::QuestScript( 66615 ){};
  ~JobWhm300() = default;

  //////////////////////////////////////////////////////////////////////
  // Event Handlers
  void onTalk( World::Quest &quest, Entity::Player &player, uint64_t actorId ) override
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
        if( quest.getSeq() == Seq1 )
        {
          //TODO: Selecting "Procede" causes the game to fade out, so if we don't send the player to an instance it soft-locks them.
          //Scene00002( quest, player );
          playerMgr().sendUrgent( player, "QuestBattle content is currently broken. The fight has been skipped for you." );
          eventMgr().sendEventNotice( player, getId(), 0, 0 );
          quest.setSeq( SeqFinish );
        }
        break;
      }
      case Actor2:
      {
        break;
      }
      case Actor3:
      {
        if( quest.getSeq() == SeqFinish )
          Scene00006( quest, player );
        break;
      }
    }
  }

  void onEventItem( World::Quest &quest, Entity::Player &player, uint64_t actorId ) override
  {
  }


private:
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest &quest, Entity::Player &player )
  {
    eventMgr().playQuestScene( player, getId(), 0, NONE, bindSceneReturn( &JobWhm300::Scene00000Return ) );
  }

  void Scene00000Return( World::Quest &quest, Entity::Player &player, const Event::SceneResult &result )
  {
    if( result.getResult( 0 ) == 1 )// accept quest
    {
      Scene00001( quest, player );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00001( World::Quest &quest, Entity::Player &player )
  {
    eventMgr().playQuestScene( player, getId(), 1, NONE, bindSceneReturn( &JobWhm300::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest &quest, Entity::Player &player, const Event::SceneResult &result )
  {
    quest.setSeq( Seq1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest &quest, Entity::Player &player )
  {
    eventMgr().playQuestScene( player, getId(), 2, NONE, bindSceneReturn( &JobWhm300::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest &quest, Entity::Player &player, const Event::SceneResult &result )
  {
    if( result.getResult( 0 ) == 1 )
    {
      //TODO: QuestBattle content

      auto &pTeriMgr = Common::Service< Sapphire::World::Manager::TerritoryMgr >::ref();

      eventMgr().eventFinish( player, result.eventId, 0 );
      pTeriMgr.createAndJoinQuestBattle( player, Questbattle0 );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest &quest, Entity::Player &player )
  {
    eventMgr().playQuestScene( player, getId(), 3, NONE, bindSceneReturn( &JobWhm300::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest &quest, Entity::Player &player, const Event::SceneResult &result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest &quest, Entity::Player &player )
  {
    eventMgr().playQuestScene( player, getId(), 4, NONE, bindSceneReturn( &JobWhm300::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest &quest, Entity::Player &player, const Event::SceneResult &result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest &quest, Entity::Player &player )
  {
    eventMgr().playQuestScene( player, getId(), 5, NONE, bindSceneReturn( &JobWhm300::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest &quest, Entity::Player &player, const Event::SceneResult &result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00006( World::Quest &quest, Entity::Player &player )
  {
    eventMgr().playQuestScene( player, getId(), 6, NONE, bindSceneReturn( &JobWhm300::Scene00006Return ) );
  }

  void Scene00006Return( World::Quest &quest, Entity::Player &player, const Event::SceneResult &result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      Scene00007( quest, player );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00007( World::Quest &quest, Entity::Player &player )
  {
    eventMgr().playQuestScene( player, getId(), 7, FADE_OUT | HIDE_UI, bindSceneReturn( &JobWhm300::Scene00007Return ) );
  }

  void Scene00007Return( World::Quest &quest, Entity::Player &player, const Event::SceneResult &result )
  {
    //TODO: Unlock Skill
    player.finishQuest( getId() );
    player.setMaxGearSets( player.getMaxGearSets() + 1 );
  }
};

EXPOSE_SCRIPT( JobWhm300 );