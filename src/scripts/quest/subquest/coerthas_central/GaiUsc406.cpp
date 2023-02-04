// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include "Manager/EventMgr.h"
#include <Actor/Player.h>
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: GaiUsc406_00981
// Quest Name: Footprints in the Snow
// Quest ID: 66517
// Start NPC: 1006518
// End NPC: 1006521

using namespace Sapphire;

class GaiUsc406 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // BitFlag8
  // UI8AL

  /// Countable Num: 0 Seq: 1 Event: 1 Listener: 2002196
  /// Countable Num: 0 Seq: 2 Event: 1 Listener: 2002681
  /// Countable Num: 0 Seq: 3 Event: 1 Listener: 2002682
  /// Countable Num: 0 Seq: 4 Event: 1 Listener: 2002683
  /// Countable Num: 0 Seq: 5 Event: 1 Listener: 2002684
  /// Countable Num: 0 Seq: 6 Event: 1 Listener: 2002685
  /// Countable Num: 0 Seq: 255 Event: 1 Listener: 2002197
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
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1006518;//PIERREMONS
  static constexpr auto Actor1 = 1006519;//Wedge
  static constexpr auto Actor2 = 1006521;//Abeline
  static constexpr auto Eobject0 = 2002196;//Footprints (Seq1)
  static constexpr auto Eobject1 = 2002681;
  static constexpr auto Eobject2 = 2002682;
  static constexpr auto Eobject3 = 2002683;
  static constexpr auto Eobject4 = 2002684;
  static constexpr auto Eobject5 = 2002685;
  static constexpr auto Eobject6 = 2002197;//Footprints (Seq2)
  static constexpr auto Eobject7 = 2002198;//Footprints (Seq3)
  static constexpr auto Eobject8 = 2002199;//Footprints (Seq4)
  static constexpr auto Eobject9 = 2002200;//Footprints (Seq5)
  static constexpr auto EventActionLookoutLong = 41;
  static constexpr auto EventActionSearch = 1;
  static constexpr auto LocAction1 = 936;
  static constexpr auto LocAction2 = 985;
  static constexpr auto LocAction3 = 1002;
  static constexpr auto LocActor0 = 1003837;
  static constexpr auto LocActor1 = 1003855;
  static constexpr auto LocBgm1 = 93;
  static constexpr auto LocPosActor0 = 4322708;
  static constexpr auto LocPosActor1 = 4273899;
  static constexpr auto LocSe1 = 42;
  static constexpr auto LocTalkshape1 = 6;

public:
  GaiUsc406() : Sapphire::ScriptAPI::QuestScript( 66517 ){};
  ~GaiUsc406() = default;

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
        if( quest.getSeq() == Seq6 )
          Scene00062( quest, player );
        break;
      }
      case Actor2:
      {
        if( quest.getSeq() == SeqFinish )
          Scene00073( quest, player );
        break;
      }
      case Eobject0:
      {
        eventMgr().eventActionStart(
                player, getId(), EventActionLookoutLong,
                [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                  Scene00002( quest, player );
                },
                nullptr, 0 );
        break;
      }
      case Eobject6:
      {
        eventMgr().eventActionStart(
                player, getId(), EventActionLookoutLong,
                [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                  Scene00003( quest, player );
                },
                nullptr, 0 );
        break;
      }
      case Eobject7:
      {
        eventMgr().eventActionStart(
                player, getId(), EventActionLookoutLong,
                [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                  Scene00004( quest, player );
                },
                nullptr, 0 );
        break;
      }
      case Eobject8:
      {
        eventMgr().eventActionStart(
                player, getId(), EventActionLookoutLong,
                [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                  Scene00005( quest, player );
                },
                nullptr, 0 );
        break;
      }
      case Eobject9:
      {
        eventMgr().eventActionStart(
                player, getId(), EventActionLookoutLong,
                [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                  Scene00006( quest, player );
                },
                nullptr, 0 );
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
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &GaiUsc406::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, HIDE_HOTBAR, bindSceneReturn( &GaiUsc406::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( Seq1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, NONE, bindSceneReturn( &GaiUsc406::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 0, 0 );
    quest.setSeq( Seq2 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, NONE, bindSceneReturn( &GaiUsc406::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 1, 0 );
    quest.setSeq( Seq3 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, NONE, bindSceneReturn( &GaiUsc406::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 2, 0 );
    quest.setSeq( Seq4 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, NONE, bindSceneReturn( &GaiUsc406::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 3, 0 );
    quest.setSeq( Seq5 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00006( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 6, NONE, bindSceneReturn( &GaiUsc406::Scene00006Return ) );
  }

  void Scene00006Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 4, 0 );
    quest.setSeq( Seq6 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00007( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 7, NONE, bindSceneReturn( &GaiUsc406::Scene00007Return ) );
  }

  void Scene00007Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00008( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 8, NONE, bindSceneReturn( &GaiUsc406::Scene00008Return ) );
  }

  void Scene00008Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00009( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 9, NONE, bindSceneReturn( &GaiUsc406::Scene00009Return ) );
  }

  void Scene00009Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00010( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 10, NONE, bindSceneReturn( &GaiUsc406::Scene00010Return ) );
  }

  void Scene00010Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00011( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 11, NONE, bindSceneReturn( &GaiUsc406::Scene00011Return ) );
  }

  void Scene00011Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00012( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 12, NONE, bindSceneReturn( &GaiUsc406::Scene00012Return ) );
  }

  void Scene00012Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00013( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 13, NONE, bindSceneReturn( &GaiUsc406::Scene00013Return ) );
  }

  void Scene00013Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00014( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 14, NONE, bindSceneReturn( &GaiUsc406::Scene00014Return ) );
  }

  void Scene00014Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00015( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 15, NONE, bindSceneReturn( &GaiUsc406::Scene00015Return ) );
  }

  void Scene00015Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00016( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 16, NONE, bindSceneReturn( &GaiUsc406::Scene00016Return ) );
  }

  void Scene00016Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00017( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 17, NONE, bindSceneReturn( &GaiUsc406::Scene00017Return ) );
  }

  void Scene00017Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00018( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 18, NONE, bindSceneReturn( &GaiUsc406::Scene00018Return ) );
  }

  void Scene00018Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00019( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 19, NONE, bindSceneReturn( &GaiUsc406::Scene00019Return ) );
  }

  void Scene00019Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00020( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 20, NONE, bindSceneReturn( &GaiUsc406::Scene00020Return ) );
  }

  void Scene00020Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00021( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 21, NONE, bindSceneReturn( &GaiUsc406::Scene00021Return ) );
  }

  void Scene00021Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00022( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 22, NONE, bindSceneReturn( &GaiUsc406::Scene00022Return ) );
  }

  void Scene00022Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00023( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 23, NONE, bindSceneReturn( &GaiUsc406::Scene00023Return ) );
  }

  void Scene00023Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00024( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 24, NONE, bindSceneReturn( &GaiUsc406::Scene00024Return ) );
  }

  void Scene00024Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00025( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 25, NONE, bindSceneReturn( &GaiUsc406::Scene00025Return ) );
  }

  void Scene00025Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00026( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 26, NONE, bindSceneReturn( &GaiUsc406::Scene00026Return ) );
  }

  void Scene00026Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00027( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 27, NONE, bindSceneReturn( &GaiUsc406::Scene00027Return ) );
  }

  void Scene00027Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00028( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 28, NONE, bindSceneReturn( &GaiUsc406::Scene00028Return ) );
  }

  void Scene00028Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00029( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 29, NONE, bindSceneReturn( &GaiUsc406::Scene00029Return ) );
  }

  void Scene00029Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00030( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 30, NONE, bindSceneReturn( &GaiUsc406::Scene00030Return ) );
  }

  void Scene00030Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00031( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 31, NONE, bindSceneReturn( &GaiUsc406::Scene00031Return ) );
  }

  void Scene00031Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00032( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 32, NONE, bindSceneReturn( &GaiUsc406::Scene00032Return ) );
  }

  void Scene00032Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00033( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 33, NONE, bindSceneReturn( &GaiUsc406::Scene00033Return ) );
  }

  void Scene00033Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00034( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 34, NONE, bindSceneReturn( &GaiUsc406::Scene00034Return ) );
  }

  void Scene00034Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00035( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 35, NONE, bindSceneReturn( &GaiUsc406::Scene00035Return ) );
  }

  void Scene00035Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00036( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 36, NONE, bindSceneReturn( &GaiUsc406::Scene00036Return ) );
  }

  void Scene00036Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00037( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 37, NONE, bindSceneReturn( &GaiUsc406::Scene00037Return ) );
  }

  void Scene00037Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00038( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 38, NONE, bindSceneReturn( &GaiUsc406::Scene00038Return ) );
  }

  void Scene00038Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00039( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 39, NONE, bindSceneReturn( &GaiUsc406::Scene00039Return ) );
  }

  void Scene00039Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00040( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 40, NONE, bindSceneReturn( &GaiUsc406::Scene00040Return ) );
  }

  void Scene00040Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00041( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 41, NONE, bindSceneReturn( &GaiUsc406::Scene00041Return ) );
  }

  void Scene00041Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00042( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 42, NONE, bindSceneReturn( &GaiUsc406::Scene00042Return ) );
  }

  void Scene00042Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00043( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 43, NONE, bindSceneReturn( &GaiUsc406::Scene00043Return ) );
  }

  void Scene00043Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00044( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 44, NONE, bindSceneReturn( &GaiUsc406::Scene00044Return ) );
  }

  void Scene00044Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00045( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 45, NONE, bindSceneReturn( &GaiUsc406::Scene00045Return ) );
  }

  void Scene00045Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00046( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 46, NONE, bindSceneReturn( &GaiUsc406::Scene00046Return ) );
  }

  void Scene00046Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00047( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 47, NONE, bindSceneReturn( &GaiUsc406::Scene00047Return ) );
  }

  void Scene00047Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00048( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 48, NONE, bindSceneReturn( &GaiUsc406::Scene00048Return ) );
  }

  void Scene00048Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00049( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 49, NONE, bindSceneReturn( &GaiUsc406::Scene00049Return ) );
  }

  void Scene00049Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00050( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 50, NONE, bindSceneReturn( &GaiUsc406::Scene00050Return ) );
  }

  void Scene00050Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00051( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 51, NONE, bindSceneReturn( &GaiUsc406::Scene00051Return ) );
  }

  void Scene00051Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00052( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 52, NONE, bindSceneReturn( &GaiUsc406::Scene00052Return ) );
  }

  void Scene00052Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00053( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 53, NONE, bindSceneReturn( &GaiUsc406::Scene00053Return ) );
  }

  void Scene00053Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00054( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 54, NONE, bindSceneReturn( &GaiUsc406::Scene00054Return ) );
  }

  void Scene00054Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00055( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 55, NONE, bindSceneReturn( &GaiUsc406::Scene00055Return ) );
  }

  void Scene00055Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00056( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 56, NONE, bindSceneReturn( &GaiUsc406::Scene00056Return ) );
  }

  void Scene00056Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00057( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 57, NONE, bindSceneReturn( &GaiUsc406::Scene00057Return ) );
  }

  void Scene00057Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00058( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 58, NONE, bindSceneReturn( &GaiUsc406::Scene00058Return ) );
  }

  void Scene00058Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00059( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 59, NONE, bindSceneReturn( &GaiUsc406::Scene00059Return ) );
  }

  void Scene00059Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00060( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 60, NONE, bindSceneReturn( &GaiUsc406::Scene00060Return ) );
  }

  void Scene00060Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00061( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 61, NONE, bindSceneReturn( &GaiUsc406::Scene00061Return ) );
  }

  void Scene00061Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00062( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 62, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &GaiUsc406::Scene00062Return ) );
  }

  void Scene00062Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 5, 0 );
    quest.setSeq( SeqFinish );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00063( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 63, NONE, bindSceneReturn( &GaiUsc406::Scene00063Return ) );
  }

  void Scene00063Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00064( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 64, NONE, bindSceneReturn( &GaiUsc406::Scene00064Return ) );
  }

  void Scene00064Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00065( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 65, NONE, bindSceneReturn( &GaiUsc406::Scene00065Return ) );
  }

  void Scene00065Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00066( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 66, NONE, bindSceneReturn( &GaiUsc406::Scene00066Return ) );
  }

  void Scene00066Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00067( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 67, NONE, bindSceneReturn( &GaiUsc406::Scene00067Return ) );
  }

  void Scene00067Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00068( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 68, NONE, bindSceneReturn( &GaiUsc406::Scene00068Return ) );
  }

  void Scene00068Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00069( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 69, NONE, bindSceneReturn( &GaiUsc406::Scene00069Return ) );
  }

  void Scene00069Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00070( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 70, NONE, bindSceneReturn( &GaiUsc406::Scene00070Return ) );
  }

  void Scene00070Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00071( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 71, NONE, bindSceneReturn( &GaiUsc406::Scene00071Return ) );
  }

  void Scene00071Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00072( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 72, NONE, bindSceneReturn( &GaiUsc406::Scene00072Return ) );
  }

  void Scene00072Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00073( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 73, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &GaiUsc406::Scene00073Return ) );
  }

  void Scene00073Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
        player.finishQuest( getId() );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00074( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 74, NONE, bindSceneReturn( &GaiUsc406::Scene00074Return ) );
  }

  void Scene00074Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00075( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 75, NONE, bindSceneReturn( &GaiUsc406::Scene00075Return ) );
  }

  void Scene00075Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00076( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 76, NONE, bindSceneReturn( &GaiUsc406::Scene00076Return ) );
  }

  void Scene00076Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00077( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 77, NONE, bindSceneReturn( &GaiUsc406::Scene00077Return ) );
  }

  void Scene00077Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00078( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 78, NONE, bindSceneReturn( &GaiUsc406::Scene00078Return ) );
  }

  void Scene00078Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00079( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 79, NONE, bindSceneReturn( &GaiUsc406::Scene00079Return ) );
  }

  void Scene00079Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00080( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 80, NONE, bindSceneReturn( &GaiUsc406::Scene00080Return ) );
  }

  void Scene00080Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00081( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 81, NONE, bindSceneReturn( &GaiUsc406::Scene00081Return ) );
  }

  void Scene00081Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00082( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 82, NONE, bindSceneReturn( &GaiUsc406::Scene00082Return ) );
  }

  void Scene00082Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00083( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 83, NONE, bindSceneReturn( &GaiUsc406::Scene00083Return ) );
  }

  void Scene00083Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }
};

EXPOSE_SCRIPT( GaiUsc406 );