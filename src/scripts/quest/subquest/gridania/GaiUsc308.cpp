// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include "Manager/EventMgr.h"
#include <Actor/Player.h>
#include <ScriptObject.h>
#include <Service.h>

#include "Manager/TerritoryMgr.h"
#include "Territory/Territory.h"

// Quest Script: GaiUsc308_00975
// Quest Name: Better Late than Never
// Quest ID: 66511
// Start NPC: 1006710
// End NPC: 1006492

using namespace Sapphire;

class GaiUsc308 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // UI8AL
  // UI8BH

  /// Countable Num: 0 Seq: 255 Event: 1 Listener: 1006492
  // Steps in this quest ( 0 is before accepting,
  // 1 is first, 255 means ready for turning it in
  enum Sequence : uint8_t
  {
    Seq0 = 0,
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1006710;//Hedyn
  static constexpr auto Actor1 = 1006492;//Cid
  static constexpr auto Actor2 = 1000106;//LIONNELLAIS
  static constexpr auto Item0 = 2000753;
  static constexpr auto LocActor0 = 1004145;
  static constexpr auto LocActor9 = 1006491;
  static constexpr auto LocBgm1 = 82;
  static constexpr auto Poprange0 = 4103392;
  static constexpr auto Territorytype0 = 132;

public:
  GaiUsc308() : Sapphire::ScriptAPI::QuestScript( 66511 ){};
  ~GaiUsc308() = default;

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
        if( quest.getSeq() == SeqFinish )
          Scene00002( quest, player );
        break;
      }
      case Actor2:
      {
        if( quest.getSeq() == SeqFinish )
          Scene00004( quest, player );
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
    eventMgr().playQuestScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &GaiUsc308::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, HIDE_HOTBAR, bindSceneReturn( &GaiUsc308::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( SeqFinish );
    quest.setUI8BH( 1 );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, HIDE_HOTBAR, bindSceneReturn( &GaiUsc308::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      Scene00003( quest, player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, bindSceneReturn( &GaiUsc308::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId(), result.getResult(1) );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00004( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 4, HIDE_HOTBAR, bindSceneReturn( &GaiUsc308::Scene00004Return ) );
  }

  void Scene00004Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
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
};

EXPOSE_SCRIPT( GaiUsc308 );