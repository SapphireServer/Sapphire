// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include "Manager/EventMgr.h"
#include <Actor/Player.h>
#include <ScriptObject.h>
#include <Service.h>

#include "Manager/TerritoryMgr.h"
#include "Territory/Territory.h"
#include <Manager/WarpMgr.h>

// Quest Script: ManFst200_00507
// Quest Name: The Gridanian Envoy
// Quest ID: 66043
// Start NPC: 1003027
// End NPC: 1001821

using namespace Sapphire;

class ManFst200 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // BitFlag8
  // UI8AL
  // UI8BH
  // UI8BL

  /// Countable Num: 1 Seq: 1 Event: 1 Listener: 1000460
  /// Countable Num: 0 Seq: 2 Event: 1 Listener: 1000100
  /// Countable Num: 0 Seq: 3 Event: 1 Listener: 1000106
  /// Countable Num: 0 Seq: 4 Event: 1 Listener: 2001674
  /// Countable Num: 0 Seq: 5 Event: 1 Listener: 2001666
  /// Countable Num: 0 Seq: 6 Event: 1 Listener: 1000106
  /// Countable Num: 0 Seq: 7 Event: 1 Listener: 2001674
  /// Countable Num: 0 Seq: 8 Event: 1 Listener: 1002693
  /// Countable Num: 0 Seq: 255 Event: 1 Listener: 1002703
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
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1003027;
  static constexpr auto Actor1 = 1000460;
  static constexpr auto Actor2 = 1000100; //Mother Miounne
  static constexpr auto Actor3 = 1000106; //Lionnellais <Airship Ticketer>
  static constexpr auto Actor4 = 1002693; //Storm Honor Guard (Limsa Airship Landing)
  static constexpr auto Actor5 = 1002703; //Arrivals Attendant (Limsa Airship Exit)
  static constexpr auto Actor6 = 1001029; //Zanthael <Storm Sergent>
  static constexpr auto Actor7 = 1002695; //L'nophlo <Airship Ticketer>
  static constexpr auto Actor8 = 1004336; //Flame Honor Guard (Ul'dah Airship Landing)
  static constexpr auto Actor9 = 1004434; //Arrivals Attendant (Ul'dah Airship Exit)
  static constexpr auto Actor10 = 1001821;//Batholomew
  static constexpr auto Eobject0 = 2001674;
  static constexpr auto Eobject1 = 2001666;//Gangplank (Gridania)
  static constexpr auto Eobject2 = 2001677;
  static constexpr auto Eobject3 = 2001669;//Gangplank (Limsa)
  static constexpr auto Eobject4 = 2001687;
  static constexpr auto EventActionWaitingShor = 11;
  static constexpr auto Item0 = 2000456;
  static constexpr auto Item1 = 2000457;
  static constexpr auto NcutEvent001 = 64;
  static constexpr auto NcutEvent002 = 65;
  static constexpr auto NcutEvent003 = 66;
  static constexpr auto NcutEvent004 = 154;
  static constexpr auto NcutEvent005 = 67;
  static constexpr auto NcutEvent006 = 74;
  static constexpr auto NcutEvent007 = 155;
  static constexpr auto NcutEvent008 = 75;
  static constexpr auto NcutEvent009 = 158;
  static constexpr auto NcutEvent010 = 230;
  static constexpr auto NcutEvent011 = 229;
  static constexpr auto NcutEvent012 = 228;
  static constexpr auto NcutEvent013 = 227;
  static constexpr auto NcutEvent014 = 231;
  static constexpr auto NcutEvent015 = 229;
  static constexpr auto Poprange0 = 3877982;
  static constexpr auto Poprange1 = 4103392;
  static constexpr auto Poprange2 = 4102790;
  static constexpr auto Poprange3 = 4103399;
  static constexpr auto Poprange4 = 4103402;
  static constexpr auto Poprange5 = 4102780;
  static constexpr auto Poprange6 = 4103339;
  static constexpr auto Territorytype0 = 205;//Lotus Stand
  static constexpr auto Territorytype1 = 132;
  static constexpr auto Territorytype2 = 128;//Limsa
  static constexpr auto Territorytype3 = 130;//Ul'dah
  static constexpr auto UnlockImageAirship = 68;

public:
  ManFst200() : Sapphire::ScriptAPI::QuestScript( 66043 ){};
  ~ManFst200() = default;

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
        if( quest.getSeq() == Seq0 )
          Scene00002( quest, player );//Assumed to be the correct actor
        break;
      }
      case Actor2:
      {
        if( quest.getSeq() == Seq1 )
          Scene00003( quest, player );
        break;
      }
      case Actor3:
      {
        if( quest.getSeq() == Seq2 )
          Scene00004( quest, player );
        else if( quest.getSeq() == Seq3 )
          Scene00009( quest, player );
        else if( quest.getSeq() == Seq4 )
          Scene00014( quest, player );
        else if( quest.getSeq() == Seq5 )
          Scene00022( quest, player );
        else if( quest.getSeq() == Seq6 )
          Scene00026( quest, player );
        else if( quest.getSeq() == Seq7 )
          Scene00033( quest, player );
        else if( quest.getSeq() == Seq8 )
          Scene00038( quest, player );
        else if( quest.getSeq() == SeqFinish )
          Scene00049( quest, player );
        break;
      }
      case Actor4:
      {
        if( quest.getSeq() == Seq4 )
          Scene00011( quest, player );
        else if( quest.getSeq() == Seq5 )
          Scene00020( quest, player );
        break;
      }
      case Actor5:
      {
        if( quest.getSeq() == Seq4 )
          Scene00012( quest, player );
        break;
      }
      case Actor6:
      {
        if( quest.getSeq() == Seq5 )
          Scene00016( quest, player );
        break;
      }
      case Actor7:
      {
        if( quest.getSeq() == Seq6 )
          Scene00024( quest, player );
        else if( quest.getSeq() == Seq7 )
          Scene00031( quest, player );
        else if( quest.getSeq() == Seq8 )
          Scene00040( quest, player );
        else if( quest.getSeq() == SeqFinish )
          Scene00051( quest, player );
        break;
      }
      case Actor8:
      {
        if( quest.getSeq() == Seq8 )
          Scene00035( quest, player );
        else if( quest.getSeq() == SeqFinish )
          Scene00047( quest, player );
        break;
      }
      case Actor9:
      {
        if( quest.getSeq() == Seq8 )
          Scene00036( quest, player );
        break;
      }
      case Actor10:
      {
        if( quest.getSeq() == SeqFinish )
          Scene00042( quest, player );
        break;
      }
      case Eobject1:
      {
        eventMgr().eventActionStart(
                player, getId(), 0x0A,
                [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                  Scene00007( quest, player );
                },
                nullptr, 0 );
        break;
      }
      case Eobject3:
      {
        eventMgr().eventActionStart(
                player, getId(), 0x0A,
                [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                  Scene00029( quest, player );
                },
                nullptr, 0 );
        break;
      }
    }
  }

  void onEventItem( World::Quest& quest, Entity::Player& player, uint64_t actorId ) override
  {
  }


private:
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, NONE, bindSceneReturn( &ManFst200::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &ManFst200::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( Seq1 );
    quest.setUI8BH( 1 );
    quest.setUI8BL( 1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, HIDE_HOTBAR, bindSceneReturn( &ManFst200::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
    {
      auto instance = teriMgr().createTerritoryInstance( Territorytype0 );
      warpMgr().requestMoveTerritory( player, Common::WarpType::WARP_TYPE_NORMAL, instance->getGuId(), { 31.f, 1.6f, 25.5f }, -2.68533f );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &ManFst200::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( Seq2 );
    eventMgr().sendEventNotice( player, getId(), 0, 0 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, NONE, bindSceneReturn( &ManFst200::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.errorCode != 50 )
    {
      warpMgr().requestWarp( player, Common::WarpType::WARP_TYPE_NORMAL_POS, { 22.55f, -19.f, 114.2f }, 0.f );
      quest.setSeq( Seq3 );
      eventMgr().sendEventNotice( player, getId(), 1, 0 );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, NONE, bindSceneReturn( &ManFst200::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00006( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 6, NONE, bindSceneReturn( &ManFst200::Scene00006Return ) );
  }

  void Scene00006Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00007( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 7, HIDE_HOTBAR, bindSceneReturn( &ManFst200::Scene00007Return ) );
  }

  void Scene00007Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.errorCode != 50 )//Yes
    {
      Scene00008( quest, player );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00008( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 8, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &ManFst200::Scene00008Return ) );
  }

  void Scene00008Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    auto dest = teriMgr().getZoneByTerritoryTypeId( Territorytype2 );
    warpMgr().requestMoveTerritory( player, Common::WarpType::WARP_TYPE_NORMAL, dest->getGuId(), { -11.86f, 92.f, 17.f }, -1.95f );
    quest.setSeq( Seq4 );
    eventMgr().sendEventNotice( player, getId(), 2, 0 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00009( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 9, NONE, bindSceneReturn( &ManFst200::Scene00009Return ) );
  }

  void Scene00009Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.errorCode != 50 )
      warpMgr().requestWarp( player, Common::WarpType::WARP_TYPE_NORMAL_POS, { 22.55f, -19.f, 114.2f }, 0.f );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00010( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 10, NONE, bindSceneReturn( &ManFst200::Scene00010Return ) );
  }

  void Scene00010Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00011( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 11, HIDE_HOTBAR, bindSceneReturn( &ManFst200::Scene00011Return ) );
  }

  void Scene00011Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( Seq5 );
    eventMgr().sendEventNotice( player, getId(), 3, 0 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00012( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 12, NONE, bindSceneReturn( &ManFst200::Scene00012Return ) );
  }

  void Scene00012Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.errorCode != 50 )
      warpMgr().requestWarp( player, Common::WarpType::WARP_TYPE_NORMAL_POS, { -13.95f, 91.5f, -5.88f }, 2.89f );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00013( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 13, NONE, bindSceneReturn( &ManFst200::Scene00013Return ) );
  }

  void Scene00013Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00014( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 14, NONE, bindSceneReturn( &ManFst200::Scene00014Return ) );
  }

  void Scene00014Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.errorCode != 50 )
      warpMgr().requestWarp( player, Common::WarpType::WARP_TYPE_NORMAL_POS, { 22.55f, -19.f, 114.2f }, 0.f );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00015( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 15, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &ManFst200::Scene00015Return ) );
  }

  void Scene00015Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00016( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 16, HIDE_HOTBAR, bindSceneReturn( &ManFst200::Scene00016Return ) );
  }

  void Scene00016Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
    {
      Scene00017( quest, player );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00017( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 17, HIDE_HOTBAR, bindSceneReturn( &ManFst200::Scene00017Return ) );
  }

  void Scene00017Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    Scene00018( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00018( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 18, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &ManFst200::Scene00018Return ) );
  }

  void Scene00018Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 3, 0 );
    quest.setSeq( Seq6 );
    quest.setUI8BL( 0 );//BH and BL swap uses after this, so this is the correct var to 0
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00019( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 19, NONE, bindSceneReturn( &ManFst200::Scene00019Return ) );
  }

  void Scene00019Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00020( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 20, NONE, bindSceneReturn( &ManFst200::Scene00020Return ) );
  }

  void Scene00020Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00021( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 21, NONE, bindSceneReturn( &ManFst200::Scene00021Return ) );
  }

  void Scene00021Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00022( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 22, NONE, bindSceneReturn( &ManFst200::Scene00022Return ) );
  }

  void Scene00022Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.errorCode != 50 )
      warpMgr().requestWarp( player, Common::WarpType::WARP_TYPE_NORMAL_POS, { 22.55f, -19.f, 114.2f }, 0.f );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00023( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 23, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &ManFst200::Scene00023Return ) );
  }

  void Scene00023Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00024( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 24, HIDE_HOTBAR, bindSceneReturn( &ManFst200::Scene00024Return ) );
  }

  void Scene00024Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.errorCode != 50 )
    {
      eventMgr().sendEventNotice( player, getId(), 5, 0 );
      warpMgr().requestWarp( player, Common::WarpType::WARP_TYPE_NORMAL_POS, { -24.3f, 92.f, 2.47f }, -0.37f );
      quest.setSeq( Seq7 );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00025( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 25, NONE, bindSceneReturn( &ManFst200::Scene00025Return ) );
  }

  void Scene00025Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00026( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 26, NONE, bindSceneReturn( &ManFst200::Scene00026Return ) );
  }

  void Scene00026Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.errorCode != 50 )
      warpMgr().requestWarp( player, Common::WarpType::WARP_TYPE_NORMAL_POS, { 22.55f, -19.f, 114.2f }, 0.f );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00027( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 27, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &ManFst200::Scene00027Return ) );
  }

  void Scene00027Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00028( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 28, NONE, bindSceneReturn( &ManFst200::Scene00028Return ) );
  }

  void Scene00028Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00029( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 29, HIDE_HOTBAR, bindSceneReturn( &ManFst200::Scene00029Return ) );
  }

  void Scene00029Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.errorCode != 50 )
      Scene00030( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00030( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 30, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &ManFst200::Scene00030Return ) );
  }

  void Scene00030Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    auto dest = teriMgr().getZoneByTerritoryTypeId( Territorytype3 );
    warpMgr().requestMoveTerritory( player, Common::WarpType::WARP_TYPE_NORMAL, dest->getGuId(), { -44.14f, 84.f, -0.47f }, 1.3f );
    quest.setSeq( Seq8 );
    eventMgr().sendEventNotice( player, getId(), 2, 0 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00031( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 31, HIDE_HOTBAR, bindSceneReturn( &ManFst200::Scene00031Return ) );
  }

  void Scene00031Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.errorCode != 50 )
      warpMgr().requestWarp( player, Common::WarpType::WARP_TYPE_NORMAL_POS, { -24.3f, 92.f, 2.47f }, -0.37f );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00032( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 32, NONE, bindSceneReturn( &ManFst200::Scene00032Return ) );
  }

  void Scene00032Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00033( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 33, NONE, bindSceneReturn( &ManFst200::Scene00033Return ) );
  }

  void Scene00033Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.errorCode != 50 )
      warpMgr().requestWarp( player, Common::WarpType::WARP_TYPE_NORMAL_POS, { 22.55f, -19.f, 114.2f }, 0.f );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00034( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 34, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &ManFst200::Scene00034Return ) );
  }

  void Scene00034Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00035( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 35, HIDE_HOTBAR, bindSceneReturn( &ManFst200::Scene00035Return ) );
  }

  void Scene00035Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( SeqFinish );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00036( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 36, NONE, bindSceneReturn( &ManFst200::Scene00036Return ) );
  }

  void Scene00036Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.errorCode != 50 )
      warpMgr().requestWarp( player, Common::WarpType::WARP_TYPE_NORMAL_POS, { -19.45f, 83.2f, 3.85f }, 1.8f );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00037( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 37, NONE, bindSceneReturn( &ManFst200::Scene00037Return ) );
  }

  void Scene00037Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00038( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 38, NONE, bindSceneReturn( &ManFst200::Scene00038Return ) );
  }

  void Scene00038Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.errorCode != 50 )
      warpMgr().requestWarp( player, Common::WarpType::WARP_TYPE_NORMAL_POS, { 22.55f, -19.f, 114.2f }, 0.f );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00039( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 39, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &ManFst200::Scene00039Return ) );
  }

  void Scene00039Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00040( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 40, HIDE_HOTBAR, bindSceneReturn( &ManFst200::Scene00040Return ) );
  }

  void Scene00040Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.errorCode != 50 )
      warpMgr().requestWarp( player, Common::WarpType::WARP_TYPE_NORMAL_POS, { -24.3f, 92.f, 2.47f }, -0.37f );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00041( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 41, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &ManFst200::Scene00041Return ) );
  }

  void Scene00041Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00042( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 42, HIDE_HOTBAR, bindSceneReturn( &ManFst200::Scene00042Return ) );
  }

  void Scene00042Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      Scene00043( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00043( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 43, NONE, bindSceneReturn( &ManFst200::Scene00043Return ) );
  }

  void Scene00043Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    Scene00044( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00044( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 44, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &ManFst200::Scene00044Return ) );
  }

  void Scene00044Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    Scene00045( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00045( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 45, NONE, bindSceneReturn( &ManFst200::Scene00045Return ) );
  }

  void Scene00045Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId() );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00046( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 46, NONE, bindSceneReturn( &ManFst200::Scene00046Return ) );
  }

  void Scene00046Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00047( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 47, HIDE_HOTBAR, bindSceneReturn( &ManFst200::Scene00047Return ) );
  }

  void Scene00047Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00048( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 48, NONE, bindSceneReturn( &ManFst200::Scene00048Return ) );
  }

  void Scene00048Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00049( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 49, NONE, bindSceneReturn( &ManFst200::Scene00049Return ) );
  }

  void Scene00049Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.errorCode != 50 )
      warpMgr().requestWarp( player, Common::WarpType::WARP_TYPE_NORMAL_POS, { 22.55f, -19.f, 114.2f }, 0.f );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00050( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 50, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &ManFst200::Scene00050Return ) );
  }

  void Scene00050Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00051( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 51, HIDE_HOTBAR, bindSceneReturn( &ManFst200::Scene00051Return ) );
  }

  void Scene00051Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.errorCode != 50 )
      warpMgr().requestWarp( player, Common::WarpType::WARP_TYPE_NORMAL_POS, { -24.3f, 92.f, 2.47f }, -0.37f );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00052( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 52, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &ManFst200::Scene00052Return ) );
  }

  void Scene00052Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }
};

EXPOSE_SCRIPT( ManFst200 );