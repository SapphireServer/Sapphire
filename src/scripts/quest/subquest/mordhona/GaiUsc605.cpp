// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include "Manager/EventMgr.h"
#include <Actor/Player.h>
#include <ScriptObject.h>
#include <Service.h>

#include "Manager/TerritoryMgr.h"
#include "Territory/Territory.h"

// Quest Script: GaiUsc605_01005
// Quest Name: Every Little Thing She Does Is Magitek
// Quest ID: 66541
// Start NPC: 1006555
// End NPC: 1006555

using namespace Sapphire;

class GaiUsc605 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // BitFlag8
  // UI8AH
  // UI8AL
  // UI8BH

  /// Countable Num: 0 Seq: 1 Event: 1 Listener: 1006530
  /// Countable Num: 0 Seq: 2 Event: 1 Listener: 1006557
  /// Countable Num: 0 Seq: 3 Event: 1 Listener: 1006530
  /// Countable Num: 0 Seq: 4 Event: 1 Listener: 1004093
  /// Countable Num: 0 Seq: 5 Event: 1 Listener: 1006557
  /// Countable Num: 0 Seq: 6 Event: 1 Listener: 1006530
  /// Countable Num: 0 Seq: 7 Event: 1 Listener: 1006559
  /// Countable Num: 0 Seq: 8 Event: 1 Listener: 1006558
  /// Countable Num: 0 Seq: 9 Event: 1 Listener: 1006560
  /// Countable Num: 0 Seq: 10 Event: 1 Listener: 1006561
  /// Countable Num: 0 Seq: 255 Event: 10 Listener: 5000000
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
    Seq8 = 8,
    Seq9 = 9,
    Seq10 = 10,
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1006555;//Cid (Cid's Workshop)
  static constexpr auto Actor1 = 1006530;//Slafborn
  static constexpr auto Actor2 = 1006557;//Wedge (Cid's Workshop)
  static constexpr auto Actor3 = 1004093;//Serendipity
  static constexpr auto Actor4 = 1006559;//Wedge (Overworld)
  static constexpr auto Actor5 = 1006558;//Cid (Overworld)
  static constexpr auto Actor6 = 1006560;//Biggs (Overworld)
  static constexpr auto Actor7 = 1006561;//Magitek Armor
  static constexpr auto Eobject0 = 2002523;
  static constexpr auto Eobject1 = 2002524;
  static constexpr auto Eobject2 = 2002525;
  static constexpr auto Eobject3 = 2002531;
  static constexpr auto Eventrange0 = 4322856;
  static constexpr auto Eventrange1 = 4322857;
  static constexpr auto Eventrange2 = 4322858;
  static constexpr auto EventActionSearch = 1;
  static constexpr auto Item0 = 2000772;
  static constexpr auto LevelArmorId = 4265706;
  static constexpr auto LevelBiggsId = 4265705;
  static constexpr auto LevelCidId = 4265703;
  static constexpr auto LevelWedgeId = 4265704;
  static constexpr auto LinkSe1 = 42;
  static constexpr auto LinkTalkshape1 = 6;
  static constexpr auto LocAction0 = 1015;
  static constexpr auto LocAction1 = 858;
  static constexpr auto LocAction2 = 112;
  static constexpr auto LocAction3 = 1005;
  static constexpr auto LocActor0 = 1002908;
  static constexpr auto LocActor1 = 1003837;
  static constexpr auto LocActor2 = 1003855;
  static constexpr auto LocActor3 = 1003836;
  static constexpr auto LocActor9 = 1003075;
  static constexpr auto LocFace0 = 604;
  static constexpr auto LocFace1 = 605;
  static constexpr auto LocFace2 = 620;
  static constexpr auto LocPosActor0 = 4330073;
  static constexpr auto LocPosActor1 = 4330075;
  static constexpr auto LocSe1 = 46;
  static constexpr auto Mount0 = 14;        //Magitek Armor (Quest version)
  static constexpr auto Poprange0 = 4321644;//Cid's Workshop
  static constexpr auto Poprange1 = 4322935;
  static constexpr auto Questbattle0 = 64;
  static constexpr auto Territorytype0 = 156;
  static constexpr auto Territorytype1 = 309;

public:
  GaiUsc605() : Sapphire::ScriptAPI::QuestScript( 66541 ){};
  ~GaiUsc605() = default;

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
          Scene00050( quest, player );
        break;
      }
      case Actor1:
      {
        if( quest.getSeq() == Seq0 )
          Scene00002( quest, player );
        else if( quest.getSeq() == Seq1 )
          Scene00004( quest, player );
        else if( quest.getSeq() == Seq3 )
          Scene00008( quest, player );
        else if( quest.getSeq() == SeqFinish )
          Scene00051( quest, player );
        break;
      }
      case Actor2:
      {
        if( quest.getSeq() == Seq1 )
          Scene00003( quest, player );
        else if( quest.getSeq() == Seq3 )
          Scene00006( quest, player );
        break;
      }
      case Actor3:
      {
        if( quest.getSeq() == Seq2 )
          Scene00005( quest, player );
        break;
      }
      case Actor4:
      {
        if( quest.getSeq() == Seq4 )
          Scene00009( quest, player );
        else if( quest.getSeq() == Seq5 )
          Scene00017( quest, player );
        else if( quest.getSeq() == Seq6 )
          Scene00023( quest, player );
        else if( quest.getSeq() == Seq7 )
          Scene00030( quest, player );
        else if( quest.getSeq() == Seq8 )
          Scene00034( quest, player );
        else if( quest.getSeq() == Seq9 )
          Scene00038( quest, player );
        else if( quest.getSeq() == Seq10 )
          Scene00046( quest, player );
        break;
      }
      case Actor5:
      {
        if( quest.getSeq() == Seq4 )
          Scene00010( quest, player );
        else if( quest.getSeq() == Seq5 )
          Scene00016( quest, player );
        else if( quest.getSeq() == Seq6 )
          Scene00022( quest, player );
        else if( quest.getSeq() == Seq7 )
          Scene00029( quest, player );
        else if( quest.getSeq() == Seq8 )
          Scene00035( quest, player );
        else if( quest.getSeq() == Seq9 )
          Scene00039( quest, player );
        else if( quest.getSeq() == Seq10 )
          Scene00045( quest, player );
        break;
      }
      case Actor6:
      {
        if( quest.getSeq() == Seq4 )
          Scene00011( quest, player );
        else if( quest.getSeq() == Seq5 )
          Scene00018( quest, player );
        else if( quest.getSeq() == Seq6 )
          Scene00024( quest, player );
        else if( quest.getSeq() == Seq7 )
          Scene00031( quest, player );
        else if( quest.getSeq() == Seq8 )
          Scene00036( quest, player );
        else if( quest.getSeq() == Seq9 )
          Scene00040( quest, player );
        else if( quest.getSeq() == Seq10 )
        {
          playerMgr().sendUrgent( player, "QuestBattle Unimplemented, skipping..." );
          eventMgr().sendEventNotice( player, getId(), 9, 0 );
          quest.setSeq( SeqFinish );
        }
          //Scene00044( quest, player );
        break;
      }
      case Actor7:
      {
        if( quest.getSeq() == Seq4 )
          Scene00012( quest, player );
        else if( quest.getSeq() == Seq8 )
          Scene00037( quest, player );
        else if( quest.getSeq() == Seq9 )
          Scene00041( quest, player );
        else if( quest.getSeq() == Seq10 )
          Scene00047( quest, player );
        break;
      }
    }
  }

  void onEmote( World::Quest& quest, uint64_t actorId, uint32_t emoteId, Entity::Player& player ) override
  {
    if( actorId == Actor7 && quest.getSeq() == Seq9 )
    {
      if( emoteId == 41 )//Welcome emtoe
        Scene00042( quest, player );
      else
        Scene00043( quest, player );
    }
  }

  void onWithinRange( World::Quest& quest, Entity::Player& player, uint32_t eventId, uint32_t param1, float x, float y, float z ) override
  {
    if( param1 == Eventrange0 )
      Scene00014( quest, player );
    else if( param1 == Eventrange1 )
      Scene00021( quest, player );
    else if( param1 == Eventrange2 )
      Scene00027( quest, player );
  }


private:
  void travelToPoprange( Entity::Player& player, uint32_t poprangeId, bool sameTerritory )
  {
    auto& objectCache = Common::Service< Sapphire::InstanceObjectCache >::ref();

    auto popRangeInfo = objectCache.getPopRangeInfo( poprangeId );

    if( popRangeInfo )
    {
      if( sameTerritory )
      {
        warpMgr().requestWarp( player, Common::WarpType::WARP_TYPE_NORMAL, popRangeInfo->m_pos, popRangeInfo->m_rotation );
      }
      else
      {
        auto pTeri = teriMgr().getZoneByTerritoryTypeId( popRangeInfo->m_territoryTypeId );
        warpMgr().requestMoveTerritory( player, Common::WarpType::WARP_TYPE_NORMAL, pTeri->getGuId(), popRangeInfo->m_pos, popRangeInfo->m_rotation );
      }
    }
  }
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &GaiUsc605::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, HIDE_HOTBAR, bindSceneReturn( &GaiUsc605::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( Seq1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, HIDE_HOTBAR, bindSceneReturn( &GaiUsc605::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      travelToPoprange( player, Poprange0, true );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, HIDE_HOTBAR, bindSceneReturn( &GaiUsc605::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 0, 0 );
    quest.setSeq( Seq2 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, HIDE_HOTBAR, bindSceneReturn( &GaiUsc605::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      travelToPoprange( player, Poprange0, true );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, HIDE_HOTBAR, bindSceneReturn( &GaiUsc605::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 1, 0 );
    quest.setSeq( Seq3 );
    quest.setUI8BH( 1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00006( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 6, HIDE_HOTBAR, bindSceneReturn( &GaiUsc605::Scene00006Return ) );
  }

  void Scene00006Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      Scene00007( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00007( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 7, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &GaiUsc605::Scene00007Return ) );
  }

  void Scene00007Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 2, 0 );
    quest.setSeq( Seq4 );
    quest.setUI8BH( 0 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00008( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 8, HIDE_HOTBAR, bindSceneReturn( &GaiUsc605::Scene00008Return ) );
  }

  void Scene00008Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      travelToPoprange( player, Poprange0, true );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00009( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 9, HIDE_HOTBAR, bindSceneReturn( &GaiUsc605::Scene00009Return ) );
  }

  void Scene00009Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 3, 0 );
    quest.setSeq( Seq5 );
    playerMgr().onMountUpdate( player, Mount0 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00010( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 10, HIDE_HOTBAR, bindSceneReturn( &GaiUsc605::Scene00010Return ) );
  }

  void Scene00010Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00011( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 11, HIDE_HOTBAR, bindSceneReturn( &GaiUsc605::Scene00011Return ) );
  }

  void Scene00011Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00012( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 12, HIDE_HOTBAR, bindSceneReturn( &GaiUsc605::Scene00012Return ) );
  }

  void Scene00012Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00013( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 13, HIDE_HOTBAR, bindSceneReturn( &GaiUsc605::Scene00013Return ) );
  }

  void Scene00013Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00014( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 14, HIDE_HOTBAR, bindSceneReturn( &GaiUsc605::Scene00014Return ) );
  }

  void Scene00014Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( player.getCurrentMount() == Mount0 )
    {
      eventMgr().sendEventNotice( player, getId(), 4, 0 );
      quest.setSeq( Seq6 );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00015( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 15, HIDE_HOTBAR, bindSceneReturn( &GaiUsc605::Scene00015Return ) );
  }

  void Scene00015Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00016( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 16, HIDE_HOTBAR, bindSceneReturn( &GaiUsc605::Scene00016Return ) );
  }

  void Scene00016Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00017( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 17, HIDE_HOTBAR, bindSceneReturn( &GaiUsc605::Scene00017Return ) );
  }

  void Scene00017Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    playerMgr().onMountUpdate( player, Mount0 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00018( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 18, HIDE_HOTBAR, bindSceneReturn( &GaiUsc605::Scene00018Return ) );
  }

  void Scene00018Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00019( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 19, HIDE_HOTBAR, bindSceneReturn( &GaiUsc605::Scene00019Return ) );
  }

  void Scene00019Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00020( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 20, HIDE_HOTBAR, bindSceneReturn( &GaiUsc605::Scene00020Return ) );
  }

  void Scene00020Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00021( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 21, HIDE_HOTBAR, bindSceneReturn( &GaiUsc605::Scene00021Return ) );
  }

  void Scene00021Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( player.getCurrentMount() == Mount0 )
    {
      eventMgr().sendEventNotice( player, getId(), 5, 0 );
      quest.setSeq( Seq7 );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00022( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 22, HIDE_HOTBAR, bindSceneReturn( &GaiUsc605::Scene00022Return ) );
  }

  void Scene00022Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00023( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 23, HIDE_HOTBAR, bindSceneReturn( &GaiUsc605::Scene00023Return ) );
  }

  void Scene00023Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    playerMgr().onMountUpdate( player, Mount0 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00024( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 24, HIDE_HOTBAR, bindSceneReturn( &GaiUsc605::Scene00024Return ) );
  }

  void Scene00024Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00025( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 25, HIDE_HOTBAR, bindSceneReturn( &GaiUsc605::Scene00025Return ) );
  }

  void Scene00025Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00026( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 26, HIDE_HOTBAR, bindSceneReturn( &GaiUsc605::Scene00026Return ) );
  }

  void Scene00026Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00027( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 27, HIDE_HOTBAR, bindSceneReturn( &GaiUsc605::Scene00027Return ) );
  }

  void Scene00027Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( player.getCurrentMount() == Mount0 )
    {
      eventMgr().sendEventNotice( player, getId(), 6, 0 );
      quest.setSeq( Seq8 );
      playerMgr().onMountUpdate( player, 0 );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00028( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 28, HIDE_HOTBAR, bindSceneReturn( &GaiUsc605::Scene00028Return ) );
  }

  void Scene00028Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00029( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 29, HIDE_HOTBAR, bindSceneReturn( &GaiUsc605::Scene00029Return ) );
  }

  void Scene00029Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00030( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 30, HIDE_HOTBAR, bindSceneReturn( &GaiUsc605::Scene00030Return ) );
  }

  void Scene00030Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    playerMgr().onMountUpdate( player, Mount0 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00031( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 31, HIDE_HOTBAR, bindSceneReturn( &GaiUsc605::Scene00031Return ) );
  }

  void Scene00031Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00032( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 32, HIDE_HOTBAR, bindSceneReturn( &GaiUsc605::Scene00032Return ) );
  }

  void Scene00032Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00033( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 33, HIDE_HOTBAR, bindSceneReturn( &GaiUsc605::Scene00033Return ) );
  }

  void Scene00033Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00034( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 34, HIDE_HOTBAR, bindSceneReturn( &GaiUsc605::Scene00034Return ) );
  }

  void Scene00034Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 7, 0 );
    quest.setSeq( Seq9 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00035( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 35, HIDE_HOTBAR, bindSceneReturn( &GaiUsc605::Scene00035Return ) );
  }

  void Scene00035Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00036( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 36, HIDE_HOTBAR, bindSceneReturn( &GaiUsc605::Scene00036Return ) );
  }

  void Scene00036Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00037( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 37, HIDE_HOTBAR, bindSceneReturn( &GaiUsc605::Scene00037Return ) );
  }

  void Scene00037Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00038( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 38, HIDE_HOTBAR, bindSceneReturn( &GaiUsc605::Scene00038Return ) );
  }

  void Scene00038Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00039( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 39, HIDE_HOTBAR, bindSceneReturn( &GaiUsc605::Scene00039Return ) );
  }

  void Scene00039Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00040( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 40, HIDE_HOTBAR, bindSceneReturn( &GaiUsc605::Scene00040Return ) );
  }

  void Scene00040Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00041( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 41, HIDE_HOTBAR, bindSceneReturn( &GaiUsc605::Scene00041Return ) );
  }

  void Scene00041Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00042( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 42, HIDE_HOTBAR, bindSceneReturn( &GaiUsc605::Scene00042Return ) );
  }

  void Scene00042Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 8, 0 );
    quest.setSeq( Seq10 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00043( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 43, HIDE_HOTBAR, bindSceneReturn( &GaiUsc605::Scene00043Return ) );
  }

  void Scene00043Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00044( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 44, HIDE_HOTBAR, bindSceneReturn( &GaiUsc605::Scene00044Return ) );
  }

  void Scene00044Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
    {
      auto& pTeriMgr = Common::Service< Sapphire::World::Manager::TerritoryMgr >::ref();

      eventMgr().eventFinish( player, result.eventId, 0 );
      pTeriMgr.createAndJoinQuestBattle( player, Questbattle0 );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00045( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 45, HIDE_HOTBAR, bindSceneReturn( &GaiUsc605::Scene00045Return ) );
  }

  void Scene00045Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00046( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 46, HIDE_HOTBAR, bindSceneReturn( &GaiUsc605::Scene00046Return ) );
  }

  void Scene00046Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00047( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 47, HIDE_HOTBAR, bindSceneReturn( &GaiUsc605::Scene00047Return ) );
  }

  void Scene00047Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00048( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 48, HIDE_HOTBAR, bindSceneReturn( &GaiUsc605::Scene00048Return ) );
  }

  void Scene00048Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00049( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 49, HIDE_HOTBAR, bindSceneReturn( &GaiUsc605::Scene00049Return ) );
  }

  void Scene00049Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00050( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 50, HIDE_HOTBAR, bindSceneReturn( &GaiUsc605::Scene00050Return ) );
  }

  void Scene00050Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId() );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00051( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 51, HIDE_HOTBAR, bindSceneReturn( &GaiUsc605::Scene00051Return ) );
  }

  void Scene00051Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      travelToPoprange( player, Poprange0, true );
  }
};

EXPOSE_SCRIPT( GaiUsc605 );