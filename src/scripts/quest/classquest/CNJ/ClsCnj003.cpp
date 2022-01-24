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

// Quest Script: ClsCnj003_00092
// Quest Name: Trial by Water
// Quest ID: 65628
// Start NPC: 1000692
// End NPC: 1000692

using namespace Sapphire;

class ClsCnj003 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // BitFlag24
  // BitFlag8
  // UI8AH
  // UI8AL
  // UI8BH
  // UI8BL
  // UI8CH

  /// Countable Num: 1 Seq: 1 Event: 1 Listener: 2000889
  /// Countable Num: 1 Seq: 2 Event: 8 Listener: 2000889
  /// Countable Num: 1 Seq: 3 Event: 5 Listener: 297
  /// Countable Num: 1 Seq: 4 Event: 1 Listener: 1000561
  /// Countable Num: 1 Seq: 5 Event: 1 Listener: 1000619
  /// Countable Num: 1 Seq: 6 Event: 1 Listener: 1003001
  /// Countable Num: 1 Seq: 7 Event: 18 Listener: 1003001
  /// Countable Num: 1 Seq: 255 Event: 1 Listener: 1003000
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
    Seq6 = 6,
    Seq7 = 7,
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Action0 = 120;
  static constexpr auto Actor0 = 1000692;//E-Sumi-Yan
  static constexpr auto Actor1 = 1000561;//Joacin
  static constexpr auto Actor2 = 1000619;//Anuid
  static constexpr auto Actor3 = 1003001;//Wounded Wood Wailer
  static constexpr auto Actor4 = 1003000;
  static constexpr auto Actor5 = 1003057;//Harried Healer
  static constexpr auto Actor6 = 1001213;//Gods' Quiver Bow
  static constexpr auto Actor7 = 1002960;//Sylphie (pre-QuestBattle)
  static constexpr auto Actor8 = 1006154;
  static constexpr auto Actor9 = 1006155;
  static constexpr auto Actor10 = 1006156;
  static constexpr auto Actor11 = 1006152;
  static constexpr auto Actor12 = 1006153;
  static constexpr auto Actor13 = 1006157;
  static constexpr auto Actor14 = 1006158;
  static constexpr auto Actor15 = 1006159;
  static constexpr auto Actor16 = 1006160;
  static constexpr auto Actor17 = 1006161;
  static constexpr auto Actor18 = 1003006; //Sylphie (post-QuestBattle)
  static constexpr auto Enemy0 = 3799227;  //Tainted Water Sprite
  static constexpr auto Eobject0 = 2000889;//Corrupted Water
  static constexpr auto Eobject1 = 2001838;
  static constexpr auto Eventrange0 = 4195892;
  static constexpr auto EventActionSearch = 1;
  static constexpr auto Item0 = 2000121;//Pristine Water? UI8BH
  static constexpr auto LocAction0 = 995;
  static constexpr auto LocActor0 = 1000569;
  static constexpr auto LocActor1 = 1000693;
  static constexpr auto LocFace1 = 611;
  static constexpr auto LocFace2 = 620;
  static constexpr auto LocFace3 = 612;
  static constexpr auto LocPosActor0 = 1170797;
  static constexpr auto LocVfx = 241;
  static constexpr auto LocWs = 134;
  static constexpr auto NqPoint001 = 8;
  static constexpr auto NqPoint002 = 9;
  static constexpr auto Questbattle0 = 16;
  static constexpr auto Territorytype0 = 234;

public:
  ClsCnj003() : Sapphire::ScriptAPI::QuestScript( 65628 ){};
  ~ClsCnj003() = default;

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
          Scene00036( quest, player );
        break;
      }
      case Actor1:
      {
        if( quest.getSeq() == Seq2 )
          Scene00007( quest, player );
        break;
      }
      case Actor2:
      {
        if( quest.getSeq() == Seq3 )
          Scene00008( quest, player );
        break;
      }
      case Actor3:
      {
        if( quest.getSeq() == Seq4 )
          Scene00009( quest, player );
        else if( quest.getSeq() == Seq5 )
          Scene00010( quest, player );
        break;
      }
      case Actor4:
      {
        break;
      }
      case Actor5:
      {
        if( quest.getSeq() == Seq4 )
          Scene00013( quest, player );
        else if( quest.getSeq() == Seq5 )
          Scene00014( quest, player );
        else if( quest.getSeq() == Seq6 )
          Scene00021( quest, player );
        break;
      }
      case Actor6:
      {
        if( quest.getSeq() == Seq6 )
          Scene00017( quest, player );//34 is a dupe?
        break;
      }
      case Actor7:
      {
        if( quest.getSeq() == Seq6 )
          Scene00018( quest, player );
        break;
      }
      case Actor8:
      {
        break;
      }
      case Actor9:
      {
        break;
      }
      case Actor10:
      {
        break;
      }
      case Actor11:
      {
        break;
      }
      case Actor12:
      {
        break;
      }
      case Actor13:
      {
        break;
      }
      case Actor14:
      {
        break;
      }
      case Actor15:
      {
        break;
      }
      case Actor16:
      {
        break;
      }
      case Actor17:
      {
        break;
      }
      case Actor18:
      {
        if( quest.getSeq() == Seq7 )
          Scene00035( quest, player );
        break;
      }
      case Eobject0:
      {
        //Opens key-item inventory
        Scene00001( quest, player );
        break;
      }
    }
  }

  void onEventItem( World::Quest& quest, Entity::Player& player, uint64_t actor ) override
  {

    if( actor == Eobject0 )
    {
      Scene00002( quest, player );
    }
  }

  void onBNpcKill( World::Quest& quest, uint16_t nameId, uint32_t entityId, Sapphire::Entity::Player& player ) override
  {
    if( entityId != Enemy0 )
      return;
    else if( entityId == Enemy0 && quest.getSeq() == Seq1 )
    {
      eventMgr().sendEventNotice( player, getId(), 0, 0 );
      quest.setUI8BH( 0 );
      quest.setSeq( Seq2 );
    }
  }

  void onEObjHit( World::Quest& quest, Sapphire::Entity::Player& player, uint64_t actor, uint32_t actionId ) override
  {

    if( actor == Actor3 && actionId == Action0 )
    {
      eventMgr().sendEventNotice( player, getId(), 3, 0 );
      quest.setSeq( Seq5 );
    }
  }

private:
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, NONE, bindSceneReturn( &ClsCnj003::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, NONE, bindSceneReturn( &ClsCnj003::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8BH( 1 );
    quest.setSeq( Seq1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, HIDE_HOTBAR, bindSceneReturn( &ClsCnj003::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    auto& teriMgr = Common::Service< Sapphire::World::Manager::TerritoryMgr >::ref();
    auto instance = teriMgr.getTerritoryByGuId( player.getTerritoryId() );
    auto enemy = instance->createBNpcFromInstanceId( Enemy0, 319 /*Find the right value*/, Common::BNpcType::Enemy );
    enemy->setTriggerOwnerId( player.getId() );
    enemy->hateListAddDelayed( player.getAsPlayer(), 1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, NONE, bindSceneReturn( &ClsCnj003::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, NONE, bindSceneReturn( &ClsCnj003::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, NONE, bindSceneReturn( &ClsCnj003::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00006( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 6, NONE, bindSceneReturn( &ClsCnj003::Scene00006Return ) );
  }

  void Scene00006Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00007( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 7, FADE_OUT | HIDE_UI | CONDITION_CUTSCENE, bindSceneReturn( &ClsCnj003::Scene00007Return ) );
  }

  void Scene00007Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 1, 0 );
    quest.setSeq( Seq3 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00008( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 8, NONE, bindSceneReturn( &ClsCnj003::Scene00008Return ) );
  }

  void Scene00008Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 2, 0 );
    quest.setSeq( Seq4 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00009( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 9, NONE, bindSceneReturn( &ClsCnj003::Scene00009Return ) );
  }

  void Scene00009Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00010( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 10, NONE, bindSceneReturn( &ClsCnj003::Scene00010Return ) );
  }

  void Scene00010Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00011( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 11, NONE, bindSceneReturn( &ClsCnj003::Scene00011Return ) );
  }

  void Scene00011Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00012( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 12, NONE, bindSceneReturn( &ClsCnj003::Scene00012Return ) );
  }

  void Scene00012Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00013( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 13, NONE, bindSceneReturn( &ClsCnj003::Scene00013Return ) );
  }

  void Scene00013Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00014( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 14, HIDE_HOTBAR, bindSceneReturn( &ClsCnj003::Scene00014Return ) );
  }

  void Scene00014Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 4, 0 );
    quest.setSeq( Seq6 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00015( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 15, NONE, bindSceneReturn( &ClsCnj003::Scene00015Return ) );
  }

  void Scene00015Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00016( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 16, NONE, bindSceneReturn( &ClsCnj003::Scene00016Return ) );
  }

  void Scene00016Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00017( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 17, HIDE_HOTBAR, bindSceneReturn( &ClsCnj003::Scene00017Return ) );
  }

  void Scene00017Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    //TODO: QuestBattle
    playerMgr().sendUrgent( player, "QuestBattle content is currently broken. The fight has been skipped for you." );
    eventMgr().sendEventNotice( player, getId(), 5, 0 );
    quest.setSeq( Seq7 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00018( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 18, NONE, bindSceneReturn( &ClsCnj003::Scene00018Return ) );
  }

  void Scene00018Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00019( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 19, NONE, bindSceneReturn( &ClsCnj003::Scene00019Return ) );
  }

  void Scene00019Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00020( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 20, NONE, bindSceneReturn( &ClsCnj003::Scene00020Return ) );
  }

  void Scene00020Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00021( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 21, NONE, bindSceneReturn( &ClsCnj003::Scene00021Return ) );
  }

  void Scene00021Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00022( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 22, NONE, bindSceneReturn( &ClsCnj003::Scene00022Return ) );
  }

  void Scene00022Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00023( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 23, NONE, bindSceneReturn( &ClsCnj003::Scene00023Return ) );
  }

  void Scene00023Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00024( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 24, NONE, bindSceneReturn( &ClsCnj003::Scene00024Return ) );
  }

  void Scene00024Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00025( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 25, NONE, bindSceneReturn( &ClsCnj003::Scene00025Return ) );
  }

  void Scene00025Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00026( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 26, NONE, bindSceneReturn( &ClsCnj003::Scene00026Return ) );
  }

  void Scene00026Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00027( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 27, NONE, bindSceneReturn( &ClsCnj003::Scene00027Return ) );
  }

  void Scene00027Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00028( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 28, NONE, bindSceneReturn( &ClsCnj003::Scene00028Return ) );
  }

  void Scene00028Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00029( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 29, NONE, bindSceneReturn( &ClsCnj003::Scene00029Return ) );
  }

  void Scene00029Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00030( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 30, NONE, bindSceneReturn( &ClsCnj003::Scene00030Return ) );
  }

  void Scene00030Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00031( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 31, NONE, bindSceneReturn( &ClsCnj003::Scene00031Return ) );
  }

  void Scene00031Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00032( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 32, NONE, bindSceneReturn( &ClsCnj003::Scene00032Return ) );
  }

  void Scene00032Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00033( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 33, NONE, bindSceneReturn( &ClsCnj003::Scene00033Return ) );
  }

  void Scene00033Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00034( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 34, NONE, bindSceneReturn( &ClsCnj003::Scene00034Return ) );
  }

  void Scene00034Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00035( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 35, HIDE_HOTBAR, bindSceneReturn( &ClsCnj003::Scene00035Return ) );
  }

  void Scene00035Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 6, 0 );
    quest.setSeq( SeqFinish );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00036( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 36, FADE_OUT | HIDE_UI | CONDITION_CUTSCENE, bindSceneReturn( &ClsCnj003::Scene00036Return ) );
  }

  void Scene00036Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult( 1 ) );
    }
  }
};

EXPOSE_SCRIPT( ClsCnj003 );