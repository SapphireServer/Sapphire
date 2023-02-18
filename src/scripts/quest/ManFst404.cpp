// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include "Manager/EventMgr.h"
#include <Actor/Player.h>
#include <ScriptObject.h>
#include <Service.h>

#include "Manager/TerritoryMgr.h"
#include "Territory/Territory.h"

// Quest Script: ManFst404_00519
// Quest Name: Lady of the Vortex
// Quest ID: 66055
// Start NPC: 1006492
// End NPC: 1006730

using namespace Sapphire;

class ManFst404 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // BitFlag8
  // UI8AH
  // UI8AL

  /// Countable Num: 0 Seq: 1 Event: 1 Listener: 1000106
  /// Countable Num: 0 Seq: 2 Event: 1 Listener: 1007690
  /// Countable Num: 0 Seq: 3 Event: 1 Listener: 1006492
  /// Countable Num: 0 Seq: 255 Event: 1 Listener: 1000106
  // Steps in this quest ( 0 is before accepting,
  // 1 is first, 255 means ready for turning it in
  enum Sequence : uint8_t
  {
    Seq0 = 0,
    Seq1 = 1,
    Seq2 = 2,
    Seq3 = 3,//Fake Seq for Cutscene?
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1006492;//Cid
  static constexpr auto Actor1 = 1000106;//LIONNELLAIS
  static constexpr auto Actor2 = 1007690;//Alphinaud (Seq1/Seq2)
  static constexpr auto Actor4 = 1006730;//Alphinaud (SeqFinish)
  static constexpr auto Actor5 = 1004433;//Elyenora
  static constexpr auto ContentStart = 20003;
  static constexpr auto CutScene01 = 104;
  static constexpr auto CutScene02 = 105;
  static constexpr auto CutScene03 = 106;
  static constexpr auto CutScene04Wol = 107;
  static constexpr auto CutScene05 = 372;
  static constexpr auto CutSceneAfter01 = 108;
  static constexpr auto CutSceneAfter02 = 286;
  static constexpr auto Instancedungeon0 = 20003;
  static constexpr auto Poprange0 = 4103392;
  static constexpr auto Poprange1 = 4313619;
  static constexpr auto Poprange2 = 4332853;
  static constexpr auto Poprange3 = 4103351;
  static constexpr auto ScreenImageUnlock = 115;
  static constexpr auto Territorytype0 = 132;
  static constexpr auto Territorytype1 = 331;
  static constexpr auto Territorytype2 = 130;
  static constexpr auto UnlockAddNewContentToCf = 3702;
  static constexpr auto AchievementCompleteQuest = 787; //Free Wing Night

public:
  ManFst404() : Sapphire::ScriptAPI::QuestScript( 66055 ){};
  ~ManFst404() = default;

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
        else if( quest.getSeq() == Seq1 )
          Scene00004( quest, player );
        break;
      }
      case Actor1:
      {
        if( quest.getSeq() == Seq0 )
          Scene00002( quest, player );
        else if( quest.getSeq() == Seq1 )
          Scene00005( quest, player );
        break;
      }
      case Actor2:
      {
        if( quest.getSeq() == Seq1 )
          Scene00003( quest, player );
        else if( quest.getSeq() == Seq2 )
          Scene00006( quest, player );
        break;
      }
      case Actor4:
      {
        if( quest.getSeq() == SeqFinish )
          Scene00008( quest, player );
        break;
      }
      case Actor5:
      {
        if( quest.getSeq() == SeqFinish )
          Scene00009( quest, player );
        break;
      }
    }
  }

  void onEnterTerritory( World::Quest& quest, Entity::Player& player, uint16_t param1, uint16_t param2 ) override
  {
    if( quest.getSeq() == Seq3 )
      Scene00007( quest, player );
  }


private:
  void travelToPoprange( Entity::Player& player, uint32_t poprangeId )
  {
    auto& objectCache = Common::Service< Sapphire::InstanceObjectCache >::ref();

    auto popRangeInfo = objectCache.getPopRangeInfo( poprangeId );

    if( popRangeInfo )
    {
      auto pTeri = teriMgr().getTerritoryByTypeId( popRangeInfo->m_territoryTypeId );
      warpMgr().requestMoveTerritory( player, Common::WarpType::WARP_TYPE_NORMAL, pTeri->getGuId(), popRangeInfo->m_pos, popRangeInfo->m_rotation );
    }
  }
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this quest, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &ManFst404::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &ManFst404::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( Seq1 );
    //TODO: Needs to be private area/Loaded in
    travelToPoprange( player, Poprange1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, HIDE_HOTBAR, bindSceneReturn( &ManFst404::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
    {
      auto& objectCache = Common::Service< Sapphire::InstanceObjectCache >::ref();

      auto popRangeInfo = objectCache.getPopRangeInfo( Poprange0 );

      if( popRangeInfo )
      {
        //auto pTeri = teriMgr().getZoneByTerritoryTypeId( popRangeInfo->m_territoryTypeId );
        //warpMgr().requestMoveTerritory( player, Common::WarpType::WARP_TYPE_NORMAL, pTeri->getGuId(), popRangeInfo->m_pos, popRangeInfo->m_rotation );
        warpMgr().requestWarp( player, Common::WarpType::WARP_TYPE_NORMAL, popRangeInfo->m_pos, popRangeInfo->m_rotation );
      }
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, HIDE_HOTBAR, bindSceneReturn( &ManFst404::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    //TODO: Unlock The Howling Eye
    quest.setSeq( Seq2 );
    eventMgr().sendEventNotice( player, getId(), 0, 0 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, HIDE_HOTBAR, bindSceneReturn( &ManFst404::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      travelToPoprange( player, Poprange1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00005( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 5, HIDE_HOTBAR, bindSceneReturn( &ManFst404::Scene00005Return ) );
  }

  void Scene00005Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
    {
      auto& objectCache = Common::Service< Sapphire::InstanceObjectCache >::ref();

      auto popRangeInfo = objectCache.getPopRangeInfo( Poprange0 );

      if( popRangeInfo )
      {
        //auto pTeri = teriMgr().getZoneByTerritoryTypeId( popRangeInfo->m_territoryTypeId );
        //warpMgr().requestMoveTerritory( player, Common::WarpType::WARP_TYPE_NORMAL, pTeri->getGuId(), popRangeInfo->m_pos, popRangeInfo->m_rotation );
        warpMgr().requestWarp( player, Common::WarpType::WARP_TYPE_NORMAL, popRangeInfo->m_pos, popRangeInfo->m_rotation );
      }
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00006( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 6, HIDE_HOTBAR, bindSceneReturn( &ManFst404::Scene00006Return ) );
  }

  void Scene00006Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00007( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 7, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &ManFst404::Scene00007Return ) );
  }

  void Scene00007Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    travelToPoprange( player, Poprange2 );
    quest.setSeq( SeqFinish );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00008( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 8, HIDE_HOTBAR, bindSceneReturn( &ManFst404::Scene00008Return ) );
  }

  void Scene00008Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
        player.finishQuest( getId(), result.getResult(1) );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00009( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 9, HIDE_HOTBAR, bindSceneReturn( &ManFst404::Scene00009Return ) );
  }

  void Scene00009Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
    {
      auto& objectCache = Common::Service< Sapphire::InstanceObjectCache >::ref();

      auto popRangeInfo = objectCache.getPopRangeInfo( Poprange3 );

      if( popRangeInfo )
      {
        //auto pTeri = teriMgr().getZoneByTerritoryTypeId( popRangeInfo->m_territoryTypeId );
        //warpMgr().requestMoveTerritory( player, Common::WarpType::WARP_TYPE_NORMAL, pTeri->getGuId(), popRangeInfo->m_pos, popRangeInfo->m_rotation );
        warpMgr().requestWarp( player, Common::WarpType::WARP_TYPE_NORMAL, popRangeInfo->m_pos, popRangeInfo->m_rotation );
      }
    }
  }
};

EXPOSE_SCRIPT( ManFst404 );