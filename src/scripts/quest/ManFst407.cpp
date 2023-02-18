// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include "Manager/EventMgr.h"
#include <Actor/Player.h>
#include <ScriptObject.h>
#include <Service.h>

#include "Inventory/Item.h"
#include "Manager/TerritoryMgr.h"
#include "Territory/Territory.h"

// Quest Script: ManFst407_00521
// Quest Name: Escape from Castrum Centri
// Quest ID: 66057
// Start NPC: 1006555
// End NPC: 1006573

using namespace Sapphire;

class ManFst407 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // BitFlag8
  // UI8AH
  // UI8AL
  // UI8BH
  // UI8BL

  /// Countable Num: 0 Seq: 1 Event: 1 Listener: 1006530
  /// Countable Num: 0 Seq: 2 Event: 1 Listener: 1007538
  /// Countable Num: 0 Seq: 3 Event: 1 Listener: 1007539
  /// Countable Num: 0 Seq: 4 Event: 1 Listener: 1007670
  /// Countable Num: 0 Seq: 5 Event: 1 Listener: 1007537
  /// Countable Num: 0 Seq: 6 Event: 1 Listener: 1006531
  /// Countable Num: 0 Seq: 255 Event: 1 Listener: 1006567
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
    Seq6 = 6,//Fake Seq for Cutscene
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1006555;//Cid (Cid's Workshop)
  static constexpr auto Actor1 = 1006530;//Slafborn
  static constexpr auto Actor2 = 1007538;
  static constexpr auto Actor3 = 1007539;
  static constexpr auto Actor4 = 1007670;
  static constexpr auto Actor5 = 1007537;//Cid (Overworld Seq1/Seq2/Seq3/Seq4)
  static constexpr auto Actor6 = 1006531;//Glaumunt
  static constexpr auto Actor7 = 1006567;//Imperial Decurion
  static constexpr auto Actor8 = 1007614;
  static constexpr auto Actor9 = 1006568; //Imperial Courier
  static constexpr auto Actor10 = 1006569;//Imperial Guard
  static constexpr auto Actor11 = 1007611;//Imperial Centurion
  static constexpr auto Actor12 = 1006562;//Bigs (Castrum)
  static constexpr auto Actor13 = 1007694;
  static constexpr auto Actor14 = 1007696;
  static constexpr auto Actor15 = 1006573;//Minfilia
  static constexpr auto Actor16 = 1004433;//Elyenora
  static constexpr auto CutScene01 = 293;
  static constexpr auto CutScene02 = 113;
  static constexpr auto CutSceneAfter00 = 456;
  static constexpr auto CutSceneAfter01 = 287;
  static constexpr auto CutSceneAfter02 = 114;
  static constexpr auto CutSceneAfter03 = 288;
  static constexpr auto CutSceneAfter04 = 260;
  static constexpr auto Eobject0 = 2002376;//Steel Door
  static constexpr auto EventActionTouchMiddle = 46;
  static constexpr auto Item0 = 2000773;
  static constexpr auto LocAction1 = 990;
  static constexpr auto LocActor0 = 1007697;
  static constexpr auto LocActor1 = 1007006;
  static constexpr auto LocActor2 = 1007023;
  static constexpr auto LocActor8 = 1006563;
  static constexpr auto LocActor9 = 1007614;
  static constexpr auto LocFace1 = 617;
  static constexpr auto LocFace2 = 620;
  static constexpr auto LocPosActor0 = 4332128;
  static constexpr auto LocPosActor1 = 4332129;
  static constexpr auto LocSe1 = 44;
  static constexpr auto LocSe2 = 45;
  static constexpr auto Poprange0 = 4321644;//Cid's Workshop
  static constexpr auto Poprange1 = 4304063;//Castrum Centri
  static constexpr auto Poprange2 = 4305281;//Castrum Centri (Part 2)
  static constexpr auto Poprange3 = 4103351;//Ul'Dah Airship Landing
  static constexpr auto Questbattle0 = 65;
  static constexpr auto Ritem0 = 6223;
  static constexpr auto Ritem1 = 6224;
  static constexpr auto Territorytype0 = 156;
  static constexpr auto Territorytype1 = 335;
  static constexpr auto Territorytype2 = 305;
  static constexpr auto Territorytype3 = 130;

public:
  ManFst407() : Sapphire::ScriptAPI::QuestScript( 66057 ){};
  ~ManFst407() = default;

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
          Scene00003( quest, player );
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
        if( quest.getSeq() == Seq1 )
        {
          if( checkRequiredItems( player ) )
            Scene00008( quest, player );
          else
            Scene00009( quest, player );
        }
        else if( quest.getSeq() == Seq2 )
          Scene00014( quest, player );
        else if( quest.getSeq() == Seq3 )
          Scene00026( quest, player );
        else if( quest.getSeq() == Seq4 )
          Scene00031( quest, player );
        else if( quest.getSeq() == Seq5 )
          Scene00036( quest, player );
        break;
      }
      case Actor6:
      {
        if( quest.getSeq() == Seq1 )
          Scene00010( quest, player );
        else if( quest.getSeq() == Seq2 )
          Scene00015( quest, player );
        else if( quest.getSeq() == Seq3 )
          Scene00027( quest, player );
        else if( quest.getSeq() == Seq4 )
          Scene00032( quest, player );
        else if( quest.getSeq() == Seq5 )
          Scene00037( quest, player );
        break;
      }
      case Actor7:
      {
        if( quest.getSeq() == Seq2 )
          Scene00011( quest, player );
        break;
      }
      case Actor8:
      {
        break;
      }
      case Actor9:
      {
        if( quest.getSeq() == Seq2 )
          Scene00017( quest, player );
        break;
      }
      case Actor10:
      {
        if( quest.getSeq() == Seq2 )
          Scene00020( quest, player );
        break;
      }
      case Actor11:
      {
        if( quest.getSeq() == Seq3 )
          Scene00023( quest, player );
        break;
      }
      case Actor12:
      {
        if( quest.getSeq() == Seq4 )
          Scene00029( quest, player );
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
        if( quest.getSeq() == SeqFinish )
          Scene00041( quest, player );
        break;
      }
      case Actor16:
      {
        if( quest.getSeq() == SeqFinish )
          Scene00042( quest, player );
        break;
      }
      case Eobject0:
      {
        eventMgr().eventActionStart(
                player, getId(), EventActionTouchMiddle,
                [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional ) {
                  //Scene00035( quest, player );
                  Scene00038( quest, player );
                },
                nullptr, 0 );
        break;
      }
    }
  }

  void onEmote( World::Quest& quest, uint64_t actorId, uint32_t emoteId, Entity::Player& player ) override
  {
    //Imperial Salute:59
    if( quest.getSeq() == Seq2 )
    {
      if( actorId == Actor7 )
      {
        if( emoteId == 59 )
          Scene00012( quest, player );
        else
          Scene00013( quest, player );
      }
      else if( actorId == Actor9 )
      {
        if( emoteId == 59 )
          Scene00018( quest, player );
        else
          Scene00019( quest, player );
      }
      else if( actorId == Actor10 )
      {
        if( emoteId == 59 )
          Scene00021( quest, player );
        else
          Scene00022( quest, player );
      }
    }
    else if( quest.getSeq() == Seq3 )
    {
      if( actorId == Actor11 )
      {
        if( emoteId == 59 )
          Scene00024( quest, player );
        else
          Scene00025( quest, player );
      }
    }
  }

  void onEnterTerritory( World::Quest& quest, Entity::Player& player, uint16_t param1, uint16_t param2 ) override
  {
    if( quest.getSeq() == Seq6 )
      Scene00040( quest, player );
  }


private:
  void travelToPoprange( Entity::Player& player, uint32_t poprangeId, bool sameTerritory, bool mustBePrivate = false )
  {
    auto& objectCache = Common::Service< Sapphire::InstanceObjectCache >::ref();

    auto popRangeInfo = objectCache.getPopRangeInfo( poprangeId );

    if( popRangeInfo )
    {
      if( mustBePrivate )
      {
        auto privTeri = teriMgr().createTerritoryInstance( popRangeInfo->m_territoryTypeId );
        warpMgr().requestMoveTerritory( player, Common::WarpType::WARP_TYPE_NORMAL, privTeri->getGuId(), popRangeInfo->m_pos, popRangeInfo->m_rotation );
      }
      else if( sameTerritory )
      {
        warpMgr().requestWarp( player, Common::WarpType::WARP_TYPE_NORMAL, popRangeInfo->m_pos, popRangeInfo->m_rotation );
      }
      else
      {
        auto pTeri = teriMgr().getTerritoryByTypeId( popRangeInfo->m_territoryTypeId );
        warpMgr().requestMoveTerritory( player, Common::WarpType::WARP_TYPE_NORMAL, pTeri->getGuId(), popRangeInfo->m_pos, popRangeInfo->m_rotation );
      }
    }
  }

  bool checkRequiredItems( Entity::Player& player )
  {
    auto headEquipped = player.getItemAt( Common::InventoryType::GearSet0, Common::GearSetSlot::Head );
    auto bodyEquipped = player.getItemAt( Common::InventoryType::GearSet0, Common::GearSetSlot::Body );
    return ( headEquipped && bodyEquipped && headEquipped->getId() == Ritem0 && bodyEquipped->getId() == Ritem1 );
  }

  void giveRequiredItems( Entity::Player& player )
  {
    Inventory::InventoryContainerPair pair;
    std::initializer_list< Common::InventoryType > bagsToCheck = { Common::InventoryType::Bag0, Common::InventoryType::Bag1, Common::InventoryType::Bag2, Common::InventoryType::Bag3, Common::InventoryType::ArmoryHead, Common::InventoryType::ArmoryBody };
    bool hasItem0 = player.findFirstItemWithId( Ritem0, pair, bagsToCheck );
    bool hasItem1 = player.findFirstItemWithId( Ritem1, pair, bagsToCheck );

    if( !hasItem0 )
      player.addItem( Ritem0, 1 );
    if( !hasItem1 )
      player.addItem( Ritem1, 1 );
  }

  void checkQuestCompletion( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().sendEventNotice( player, getId(), 1, 2, quest.getUI8AH(), 3 );
    if( quest.getUI8AH() >= 3 )
    {
      quest.setUI8AH( 0 );
      quest.setUI8BL( 0 );
      quest.setUI8AL( 0 );
      quest.setUI8BH( 0 );
      quest.setSeq( Seq3 );
    }
  }
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, NONE, bindSceneReturn( &ManFst407::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &ManFst407::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( Seq1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, HIDE_HOTBAR, bindSceneReturn( &ManFst407::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, HIDE_HOTBAR, bindSceneReturn( &ManFst407::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      travelToPoprange( player, Poprange0, true );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, HIDE_HOTBAR, bindSceneReturn( &ManFst407::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, HIDE_HOTBAR, bindSceneReturn( &ManFst407::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00006( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 6, HIDE_HOTBAR, bindSceneReturn( &ManFst407::Scene00006Return ) );
  }

  void Scene00006Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00007( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 7, HIDE_HOTBAR, bindSceneReturn( &ManFst407::Scene00007Return ) );
  }

  void Scene00007Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00008( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 8, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &ManFst407::Scene00008Return ) );
  }

  void Scene00008Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( Seq2 );
    eventMgr().sendEventNotice( player, getId(), 0, 0 );
    travelToPoprange( player, Poprange1, false, true );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00009( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 9, HIDE_HOTBAR, bindSceneReturn( &ManFst407::Scene00009Return ) );
  }

  void Scene00009Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00010( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 10, HIDE_HOTBAR, bindSceneReturn( &ManFst407::Scene00010Return ) );
  }

  void Scene00010Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    giveRequiredItems( player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00011( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 11, HIDE_HOTBAR, bindSceneReturn( &ManFst407::Scene00011Return ) );
  }

  void Scene00011Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00012( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 12, HIDE_HOTBAR, bindSceneReturn( &ManFst407::Scene00012Return ) );
  }

  void Scene00012Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8AH( quest.getUI8AH() + 1 );
    quest.setUI8BL( 1 );
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00013( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 13, HIDE_HOTBAR, bindSceneReturn( &ManFst407::Scene00013Return ) );
  }

  void Scene00013Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00014( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 14, HIDE_HOTBAR, bindSceneReturn( &ManFst407::Scene00014Return ) );
  }

  void Scene00014Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      travelToPoprange( player, Poprange1, false, true );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00015( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 15, HIDE_HOTBAR, bindSceneReturn( &ManFst407::Scene00015Return ) );
  }

  void Scene00015Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    giveRequiredItems( player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00016( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 16, HIDE_HOTBAR, bindSceneReturn( &ManFst407::Scene00016Return ) );
  }

  void Scene00016Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00017( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 17, HIDE_HOTBAR, bindSceneReturn( &ManFst407::Scene00017Return ) );
  }

  void Scene00017Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00018( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 18, HIDE_HOTBAR, bindSceneReturn( &ManFst407::Scene00018Return ) );
  }

  void Scene00018Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8AH( quest.getUI8AH() + 1 );
    quest.setUI8AL( 1 );
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00019( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 19, HIDE_HOTBAR, bindSceneReturn( &ManFst407::Scene00019Return ) );
  }

  void Scene00019Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00020( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 20, HIDE_HOTBAR, bindSceneReturn( &ManFst407::Scene00020Return ) );
  }

  void Scene00020Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00021( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 21, HIDE_HOTBAR, bindSceneReturn( &ManFst407::Scene00021Return ) );
  }

  void Scene00021Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8AH( quest.getUI8AH() + 1 );
    quest.setUI8BH( 1 );
    checkQuestCompletion( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00022( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 22, HIDE_HOTBAR, bindSceneReturn( &ManFst407::Scene00022Return ) );
  }

  void Scene00022Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00023( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 23, HIDE_HOTBAR, bindSceneReturn( &ManFst407::Scene00023Return ) );
  }

  void Scene00023Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00024( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 24, HIDE_HOTBAR, bindSceneReturn( &ManFst407::Scene00024Return ) );
  }

  void Scene00024Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setUI8BH( 1 );
    quest.setSeq( Seq4 );
    eventMgr().sendEventNotice( player, getId(), 2, 0 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00025( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 25, HIDE_HOTBAR, bindSceneReturn( &ManFst407::Scene00025Return ) );
  }

  void Scene00025Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00026( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 26, HIDE_HOTBAR, bindSceneReturn( &ManFst407::Scene00026Return ) );
  }

  void Scene00026Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      travelToPoprange( player, Poprange1, false, true );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00027( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 27, HIDE_HOTBAR, bindSceneReturn( &ManFst407::Scene00027Return ) );
  }

  void Scene00027Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    giveRequiredItems( player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00028( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 28, HIDE_HOTBAR, bindSceneReturn( &ManFst407::Scene00028Return ) );
  }

  void Scene00028Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00029( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 29, HIDE_HOTBAR, bindSceneReturn( &ManFst407::Scene00029Return ) );
  }

  void Scene00029Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      Scene00030( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00030( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 30, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &ManFst407::Scene00030Return ) );
  }

  void Scene00030Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().sendEventNotice( player, getId(), 3, 0 );
    quest.setSeq( Seq5 );
    quest.setUI8BH( 0 );
    travelToPoprange( player, Poprange2, false, true );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00031( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 31, HIDE_HOTBAR, bindSceneReturn( &ManFst407::Scene00031Return ) );
  }

  void Scene00031Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      travelToPoprange( player, Poprange1, false, true );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00032( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 32, HIDE_HOTBAR, bindSceneReturn( &ManFst407::Scene00032Return ) );
  }

  void Scene00032Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    giveRequiredItems( player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00033( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 33, HIDE_HOTBAR, bindSceneReturn( &ManFst407::Scene00033Return ) );
  }

  void Scene00033Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00034( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 34, HIDE_HOTBAR, bindSceneReturn( &ManFst407::Scene00034Return ) );
  }

  void Scene00034Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00035( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 35, HIDE_HOTBAR, bindSceneReturn( &ManFst407::Scene00035Return ) );
  }

  void Scene00035Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
    {
      auto& pTeriMgr = Common::Service< Sapphire::World::Manager::TerritoryMgr >::ref();

      eventMgr().eventFinish( player, result.eventId, 0 );
      pTeriMgr.createAndJoinQuestBattle( player, Questbattle0 );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00036( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 36, HIDE_HOTBAR, bindSceneReturn( &ManFst407::Scene00036Return ) );
  }

  void Scene00036Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      travelToPoprange( player, Poprange2, false, true );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00037( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 37, HIDE_HOTBAR, bindSceneReturn( &ManFst407::Scene00037Return ) );
  }

  void Scene00037Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    giveRequiredItems( player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00038( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 38, HIDE_HOTBAR, bindSceneReturn( &ManFst407::Scene00038Return ) );
  }

  void Scene00038Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    //TODO: Empty Scene being used for quest battle skipping purposes
    quest.setSeq( Seq6 );
    eventMgr().sendEventNotice( player, getId(), 4, 0 );
    playerMgr().sendUrgent( player, "QuestBattle Unimplemented, skipping..." );
    player.exitInstance();
    travelToPoprange( player, Poprange3, false );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00039( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 39, HIDE_HOTBAR, bindSceneReturn( &ManFst407::Scene00039Return ) );
  }

  void Scene00039Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00040( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 40, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &ManFst407::Scene00040Return ) );
  }

  void Scene00040Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( SeqFinish );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00041( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 41, HIDE_HOTBAR, bindSceneReturn( &ManFst407::Scene00041Return ) );
  }

  void Scene00041Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId() );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00042( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 42, HIDE_HOTBAR, bindSceneReturn( &ManFst407::Scene00042Return ) );
  }

  void Scene00042Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      travelToPoprange( player, Poprange3, true );
  }
};

EXPOSE_SCRIPT( ManFst407 );