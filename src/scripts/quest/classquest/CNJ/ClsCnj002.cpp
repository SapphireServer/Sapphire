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
// Quest Script: ClsCnj002_00091
// Quest Name: Trial by Wind
// Quest ID: 65627
// Start NPC: 1000692
// End NPC: 1000692

using namespace Sapphire;

class ClsCnj002 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // BitFlag8
  // UI8AL

  /// Countable Num: 1 Seq: 1 Event: 1 Listener: 1000767
  /// Countable Num: 1 Seq: 2 Event: 1 Listener: 2000885
  /// Countable Num: 1 Seq: 3 Event: 5 Listener: 295
  /// Countable Num: 1 Seq: 4 Event: 1 Listener: 1000767
  /// Countable Num: 1 Seq: 5 Event: 1 Listener: 2000887
  /// Countable Num: 1 Seq: 255 Event: 1 Listener: 1000767
  // Steps in this quest ( 0 is before accepting,
  // 1 is first, 255 means ready for turning it in
  enum Sequence : uint8_t
  {
    Seq0 = 0,
    Seq1 = 1,
    Seq2 = 2,
    Seq3 = 3,
    Seq4 = 4,
    Seq5 = 5,
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1000692;  //E-Sumi-Yan (Guildmaster)
  static constexpr auto Actor1 = 1000767;  //Wulfiue
  static constexpr auto Enemy0 = 3768148;  //Honeybee Swarm
  static constexpr auto Eobject0 = 2000885;//Destination (Seq2)
  static constexpr auto Eobject1 = 2000887;//Corrupted Air
  static constexpr auto EventActionSearch = 1;
  static constexpr auto LocActor0 = 1003003;
  static constexpr auto LocActor1 = 1000693;
  static constexpr auto LocFace1 = 617;
  static constexpr auto LocFace2 = 611;
  static constexpr auto LocFace3 = 604;
  static constexpr auto LocPosActor0 = 1170797;
  static constexpr auto Questbattle0 = 54;
  static constexpr auto Territorytype0 = 289;
  static constexpr auto UnlockImageClassCange = 22;
  static constexpr auto UnlockImageGearSet = 29;

public:
  ClsCnj002() : Sapphire::ScriptAPI::QuestScript( 65627 ){};
  ~ClsCnj002() = default;

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
          Scene00010( quest, player );
        break;
      }
      case Actor1:
      {
        if( quest.getSeq() == Seq1 )
          Scene00002( quest, player );
        else if( quest.getSeq() == Seq3 )
          Scene00006( quest, player );
        else if( quest.getSeq() == Seq5 )
          Scene00009( quest, player );
        break;
      }
      case Eobject0:
      {
        if( quest.getSeq() == Seq2 )
        {
          eventMgr().eventActionStart(
                  player, getId(), 0x01,
                  [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                    Scene00004( quest, player );
                  },
                  nullptr, 0 );
        }
        break;
      }
      case Eobject1:
      {
        if( quest.getSeq() == Seq4 )
        {
          eventMgr().sendEventNotice( player, getId(), 3, 0 );
          playerMgr().sendUrgent( player, "QuestBattle content is currently broken. The fight has been skipped for you." );
          quest.setSeq( Seq5 );
          //Actually calling Scene00008 causes the screen to fade before the return is called, softlocking the player without this solution.
          /* eventMgr().eventActionStart(
                  player, getId(), 0x03,
                  [ & ]( Entity::Player &player, uint32_t eventId, uint64_t additional ) {
                    Scene00008( quest, player );
                  },
                  nullptr, 0 );*/
        }
        break;
      }
    }
  }

  void onBNpcKill( World::Quest& quest, uint16_t nameId, uint32_t entityId, Sapphire::Entity::Player& player ) override
  {
    switch( entityId )
    {
      case Enemy0:
      {
        quest.setBitFlag8( 1, false );
        eventMgr().sendEventNotice( player, getId(), 1, 0 );
        quest.setSeq( Seq3 );
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
    eventMgr().playQuestScene( player, getId(), 0, NONE, bindSceneReturn( &ClsCnj002::Scene00000Return ) );
  }

  void Scene00000Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )// accept quest
    {
      Scene00001( quest, player );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00001( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 1, NONE, bindSceneReturn( &ClsCnj002::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( Seq1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, HIDE_HOTBAR, bindSceneReturn( &ClsCnj002::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 0, 0 );
    quest.setSeq( Seq2 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, NONE, bindSceneReturn( &ClsCnj002::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, NONE, bindSceneReturn( &ClsCnj002::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    auto& teriMgr = Common::Service< Sapphire::World::Manager::TerritoryMgr >::ref();
    auto& instance = teriMgr.getTerritoryByGuId( player.getTerritoryId() );
    auto enemy = instance->createBNpcFromInstanceId( Enemy0, 1220 /*Find the right value*/, Common::BNpcType::Enemy );
    enemy->hateListAdd( player.getAsPlayer(), 1 );
    quest.setBitFlag8( 1, true );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, NONE, bindSceneReturn( &ClsCnj002::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00006( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 6, NONE, bindSceneReturn( &ClsCnj002::Scene00006Return ) );
  }

  void Scene00006Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 2, 0 );
    quest.setSeq( Seq4 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00007( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 7, NONE, bindSceneReturn( &ClsCnj002::Scene00007Return ) );
  }

  void Scene00007Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00008( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 8, NONE, bindSceneReturn( &ClsCnj002::Scene00008Return ) );
  }

  void Scene00008Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    //TODO: Quest Battle
    if( result.getResult( 0 ) == 1 )
    {
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00009( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 9, HIDE_HOTBAR, bindSceneReturn( &ClsCnj002::Scene00009Return ) );
  }

  void Scene00009Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 4, 0 );
    quest.setSeq( SeqFinish );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00010( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 10, FADE_OUT | HIDE_UI, bindSceneReturn( &ClsCnj002::Scene00010Return ) );
  }

  void Scene00010Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
    }
  }
};

EXPOSE_SCRIPT( ClsCnj002 );