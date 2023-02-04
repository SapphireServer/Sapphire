// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include "Manager/EventMgr.h"
#include <Actor/Player.h>
#include <ScriptObject.h>
#include <Service.h>

#include "Manager/TerritoryMgr.h"
#include "Territory/Territory.h"

// Quest Script: GaiUsc607_01007
// Quest Name: Primal Fear
// Quest ID: 66543
// Start NPC: 1007478
// End NPC: 1003061

using namespace Sapphire;

class GaiUsc607 : public Sapphire::ScriptAPI::QuestScript
{
private:
  // Basic quest information
  // Quest vars / flags used
  // UI8AH

  /// Countable Num: 0 Seq: 255 Event: 1 Listener: 1003061
  // Steps in this quest ( 0 is before accepting,
  // 1 is first, 255 means ready for turning it in
  enum Sequence : uint8_t
  {
    Seq0 = 0,
    SeqFinish = 255,
  };

  // Entities found in the script data of the quest
  static constexpr auto Actor0 = 1007478;//Urianger
  static constexpr auto Actor1 = 1003061;//Lewin
  static constexpr auto Actor2 = 1000423;//Gods' Quiver Bow
  static constexpr auto Poprange0 = 3884000;
  static constexpr auto Territorytype0 = 204;

public:
  GaiUsc607() : Sapphire::ScriptAPI::QuestScript( 66543 ){};
  ~GaiUsc607() = default;

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
          Scene00003( quest, player );
        break;
      }
    }
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
    eventMgr().playQuestScene( player, getId(), 0, NONE, bindSceneReturn( &GaiUsc607::Scene00000Return ) );
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
    eventMgr().playQuestScene( player, getId(), 1, NONE, bindSceneReturn( &GaiUsc607::Scene00001Return ) );
  }

  void Scene00001Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    quest.setSeq( SeqFinish );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 2, NONE, bindSceneReturn( &GaiUsc607::Scene00002Return ) );
  }

  void Scene00002Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {

    if( result.getResult( 0 ) == 1 )
    {
      player.finishQuest( getId() );
    }
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( World::Quest& quest, Entity::Player& player )
  {
    eventMgr().playQuestScene( player, getId(), 3, NONE, bindSceneReturn( &GaiUsc607::Scene00003Return ) );
  }

  void Scene00003Return( World::Quest& quest, Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
    {
      travelToPoprange( player, Poprange0, false );
    }
  }
};

EXPOSE_SCRIPT( GaiUsc607 );