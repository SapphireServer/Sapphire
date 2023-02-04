// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include "Manager/EventMgr.h"
#include <Actor/Player.h>
#include <Actor/BNpc.h>
#include <ScriptObject.h>
#include <Service.h>

#include "Manager/WarpMgr.h"
#include "Territory/Territory.h"

// Quest Script: ManFst209_00343
// Quest Name: Lord of the Inferno
// Quest ID: 65879
// Start NPC: 1005116
// End NPC: 1005012

using namespace Sapphire;

class ManFst209 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // BitFlag16
  // BitFlag8
  // UI8AH
  // UI8AL

  /// Countable Num: 0 Seq: 1 Event: 1 Listener: 1004584
  /// Countable Num: 0 Seq: 2 Event: 1 Listener: 1004585
  /// Countable Num: 0 Seq: 3 Event: 1 Listener: 1004586
  /// Countable Num: 0 Seq: 4 Event: 1 Listener: 1004587
  /// Countable Num: 0 Seq: 5 Event: 1 Listener: 1005161
  /// Countable Num: 0 Seq: 255 Event: 1 Listener: 2001592
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
  static constexpr auto Actor0 = 1005116;//Minfilia
  static constexpr auto Actor1 = 1004584;//Flame Sergeant (Camp Drybone)
  static constexpr auto Actor2 = 1004585;
  static constexpr auto Actor3 = 1004586;
  static constexpr auto Actor4 = 1004587;
  static constexpr auto Actor5 = 1005161;
  static constexpr auto Actor6 = 1005017;//Flame Sergeant
  static constexpr auto Actor7 = 1004605;//Captured Flame Private (West)
  static constexpr auto Actor8 = 1004606;
  static constexpr auto Actor9 = 1004608;//Captured Flame Private (East)
  static constexpr auto Actor10 = 1004610;//Amalj'aa Warrior (Next to ifrit entrance)
  static constexpr auto Actor11 = 1004611;
  static constexpr auto Actor12 = 1005140;
  static constexpr auto Actor13 = 1005141;
  static constexpr auto Actor14 = 1005142;
  static constexpr auto Actor15 = 1005143;
  static constexpr auto Actor16 = 1005144;
  static constexpr auto Actor17 = 1005145;
  static constexpr auto Actor18 = 1005018;//Adala
  static constexpr auto Actor20 = 1005156;//Thancred
  static constexpr auto Actor21 = 1005146;
  static constexpr auto Actor22 = 1005147;
  static constexpr auto Actor23 = 1005148;
  static constexpr auto Actor24 = 1005149;
  static constexpr auto Actor25 = 1005150;
  static constexpr auto Actor26 = 1005151;
  static constexpr auto Actor27 = 1005152;
  static constexpr auto Actor28 = 1005153;
  static constexpr auto Actor29 = 1005154;
  static constexpr auto Actor30 = 1005155;
  static constexpr auto Actor31 = 1005012;//Scion of the Seventh Dawn
  static constexpr auto CutManfst20950 = 88;
  static constexpr auto Eobject0 = 2001592;
  static constexpr auto EventActionWaitingShor = 11;
  static constexpr auto Instancedungeon0 = 20001;
  static constexpr auto Poprange0 = 4165046;
  static constexpr auto Poprange1 = 4156164;
  static constexpr auto Poprange2 = 4148347;
  static constexpr auto Questbattle0 = 45;
  static constexpr auto Territorytype0 = 275;
  static constexpr auto Territorytype1 = 146;
  static constexpr auto UnlockAddNewContentToCf = 3702;
  static constexpr auto UnlockImageDungeon = 77;

public:
  ManFst209() : Sapphire::ScriptAPI::QuestScript( 65879 ){};
  ~ManFst209() = default;

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
        if( quest.getSeq() == Seq1 )
          Scene00002( quest, player );
        break;
      }
      case Actor2:
      {
        break;
      }
      case Actor3:
      {
        break;
      }
      case Actor4:
      {
        break;
      }
      case Actor5:
      {
        break;
      }
      case Actor6:
      {
        if( quest.getSeq() == Seq3 )
          Scene00014( quest, player );
        else if( quest.getSeq() == Seq4 )
          Scene00032( quest, player );
        break;
      }
      case Actor7:
      {
        if( quest.getSeq() == Seq3 )
          Scene00017( quest, player );
        else if( quest.getSeq() == Seq4 )
          Scene00029( quest, player );
        break;
      }
      case Actor8:
      {
        break;
      }
      case Actor9:
      {
        if( quest.getSeq() == Seq3 )
          Scene00015( quest, player );
        else if( quest.getSeq() == Seq4 )
          Scene00027( quest, player );
        break;
      }
      case Actor10:
      {
        if( quest.getSeq() == Seq3 )
          Scene00018( quest, player );
        else if( quest.getSeq() == Seq4 )
          Scene00030( quest, player );
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
        if( quest.getSeq() == Seq3 )
          Scene00026( quest, player );
        else if( quest.getSeq() == Seq4 )
          Scene00039( quest, player );
        break;
      }
      case Actor20:
      {
        if( quest.getSeq() == Seq5 )
          Scene00040( quest, player );
        break;
      }
      case Actor21:
      {
        break;
      }
      case Actor22:
      {
        break;
      }
      case Actor23:
      {
        break;
      }
      case Actor24:
      {
        break;
      }
      case Actor25:
      {
        break;
      }
      case Actor26:
      {
        break;
      }
      case Actor27:
      {
        break;
      }
      case Actor28:
      {
        break;
      }
      case Actor29:
      {
        break;
      }
      case Actor30:
      {
        break;
      }
      case Actor31:
      {
        if( quest.getSeq() == SeqFinish )
          Scene00051( quest, player );
        break;
      }
      case Eobject0:
      {
        eventMgr().eventActionStart(
                player, getId(), EventActionWaitingShor,
                [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                  Scene00008( quest, player );
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
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( Seq1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 0, 0 );
    quest.setSeq( Seq2 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00006( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 6, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00006Return ) );
  }

  void Scene00006Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00007( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 7, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00007Return ) );
  }

  void Scene00007Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00008( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 8, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00008Return ) );
  }

  void Scene00008Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
    {
      auto& pTeriMgr = Common::Service< Sapphire::World::Manager::TerritoryMgr >::ref();

      eventMgr().eventFinish( player, result.eventId, 0 );
      pTeriMgr.createAndJoinQuestBattle( player, Questbattle0 );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00009( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 9, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00009Return ) );
  }

  void Scene00009Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00010( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 10, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00010Return ) );
  }

  void Scene00010Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00011( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 11, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00011Return ) );
  }

  void Scene00011Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00012( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 12, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00012Return ) );
  }

  void Scene00012Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00013( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 13, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00013Return ) );
  }

  void Scene00013Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00014( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 14, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00014Return ) );
  }

  void Scene00014Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( Seq4 );
    eventMgr().sendEventNotice( player, getId(), 2, 0 );
    //TODO:Unlock Bowl of Embers
    //TODO:Unlock trials tab in duty roulette
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00015( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 15, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00015Return ) );
  }

  void Scene00015Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00016( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 16, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00016Return ) );
  }

  void Scene00016Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00017( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 17, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00017Return ) );
  }

  void Scene00017Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00018( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 18, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00018Return ) );
  }

  void Scene00018Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00019( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 19, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00019Return ) );
  }

  void Scene00019Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00020( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 20, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00020Return ) );
  }

  void Scene00020Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00021( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 21, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00021Return ) );
  }

  void Scene00021Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00022( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 22, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00022Return ) );
  }

  void Scene00022Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00023( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 23, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00023Return ) );
  }

  void Scene00023Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00024( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 24, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00024Return ) );
  }

  void Scene00024Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00025( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 25, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00025Return ) );
  }

  void Scene00025Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00026( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 26, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00026Return ) );
  }

  void Scene00026Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
    {
      auto dest = teriMgr().getZoneByTerritoryTypeId( Territorytype1 );
      warpMgr().requestMoveTerritory( player, Common::WarpType::WARP_TYPE_NORMAL, dest->getGuId(), { -53.4502f, -24.0946f, -567.494f }, -0.550531f );//Manual Pos
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00027( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 27, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00027Return ) );
  }

  void Scene00027Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00028( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 28, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00028Return ) );
  }

  void Scene00028Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00029( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 29, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00029Return ) );
  }

  void Scene00029Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00030( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 30, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00030Return ) );
  }

  void Scene00030Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00031( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 31, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00031Return ) );
  }

  void Scene00031Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00032( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 32, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00032Return ) );
  }

  void Scene00032Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00033( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 33, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00033Return ) );
  }

  void Scene00033Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00034( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 34, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00034Return ) );
  }

  void Scene00034Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00035( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 35, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00035Return ) );
  }

  void Scene00035Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00036( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 36, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00036Return ) );
  }

  void Scene00036Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00037( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 37, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00037Return ) );
  }

  void Scene00037Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00038( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 38, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00038Return ) );
  }

  void Scene00038Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00039( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 39, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00039Return ) );
  }

  void Scene00039Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
    {
      auto dest = teriMgr().getZoneByTerritoryTypeId( Territorytype1 );
      warpMgr().requestMoveTerritory( player, Common::WarpType::WARP_TYPE_NORMAL, dest->getGuId(), { -53.4502f, -24.0946f, -567.494f }, -0.550531f );//Manual Pos
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00040( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 40, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00040Return ) );
  }

  void Scene00040Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( SeqFinish );
    eventMgr().sendEventNotice( player, getId(), 4, 0 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00041( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 41, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00041Return ) );
  }

  void Scene00041Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00042( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 42, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00042Return ) );
  }

  void Scene00042Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00043( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 43, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00043Return ) );
  }

  void Scene00043Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00044( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 44, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00044Return ) );
  }

  void Scene00044Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00045( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 45, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00045Return ) );
  }

  void Scene00045Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00046( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 46, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00046Return ) );
  }

  void Scene00046Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00047( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 47, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00047Return ) );
  }

  void Scene00047Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00048( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 48, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00048Return ) );
  }

  void Scene00048Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00049( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 49, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00049Return ) );
  }

  void Scene00049Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00050( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 50, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00050Return ) );
  }

  void Scene00050Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00051( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 51, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00051Return ) );
  }

  void Scene00051Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      Scene00052( quest, player );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00052( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 52, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &ManFst209::Scene00052Return ) );
  }

  void Scene00052Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    //TODO: Should I warp the player into The Solar here?
    player.finishQuest( getId() );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00053( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 53, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00053Return ) );
  }

  void Scene00053Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00054( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 54, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00054Return ) );
  }

  void Scene00054Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00055( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 55, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00055Return ) );
  }

  void Scene00055Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00056( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 56, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00056Return ) );
  }

  void Scene00056Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00057( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 57, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00057Return ) );
  }

  void Scene00057Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00058( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 58, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00058Return ) );
  }

  void Scene00058Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00059( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 59, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00059Return ) );
  }

  void Scene00059Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00060( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 60, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00060Return ) );
  }

  void Scene00060Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00061( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 61, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00061Return ) );
  }

  void Scene00061Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00062( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 62, HIDE_HOTBAR, bindSceneReturn( &ManFst209::Scene00062Return ) );
  }

  void Scene00062Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }
};

EXPOSE_SCRIPT( ManFst209 );