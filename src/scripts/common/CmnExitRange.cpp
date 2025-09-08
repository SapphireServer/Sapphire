#include <ScriptObject.h>
#include <Actor/Player.h>
#include "DatCategories/InstanceObjectParser.h"
#include "Manager/HousingMgr.h"

using namespace Sapphire;

class CmnExitRange : public Sapphire::ScriptAPI::EventScript
{
public:
  CmnExitRange() :
    Sapphire::ScriptAPI::EventScript( 0x140001 )
  {
  }

  void performWarp( Entity::Player& player, uint32_t popRangeId, uint32_t territoryId,
                    Sapphire::Common::WarpType warpType, float halfPi )
  {
    auto pop = instanceObjectCache().getPopRangeInfo( popRangeId );
    if( !pop )
      return;

    warpMgr().requestMoveTerritory( player, warpType, territoryId,
                                    pop->m_pos, pop->m_rotation + halfPi );
  }

  void Scene00000Return( Entity::Player& player, const Event::SceneResult& result )
  {
    auto exitRangeId = player.getEvent( result.eventId )->getEventParam();
    auto exitRangeInfo = instanceObjectCache().getExitRange( player.getTerritoryTypeId(), exitRangeId );

    if( !exitRangeInfo )
      return;

    const float halfPi = 3.14159265358979323846f * 0.5f;

    if( result.getResult( 0 ) == 0 )
    {
      // Return to zoneline
      performWarp( player, exitRangeInfo->header.returnInstanceObjectId,
                   player.getTerritoryId(), Sapphire::Common::WARP_TYPE_TOWN_TRANSLATE, halfPi );
    }
    else
    {
      uint32_t arg1 = result.getResult( 1 );

      if( arg1 != 0xFFFFFFFF )
      {
        // Go to specific ward
        uint16_t housingTeriId;
        uint32_t popRangeId;

        if( teriMgr().isHousingTerritory( player.getTerritoryTypeId() ) )
        {
          housingTeriId = player.getTerritoryTypeId();
          popRangeId = exitRangeInfo->header.returnInstanceObjectId;
        }
        else
        {
          housingTeriId = exitRangeInfo->header.destTerritoryType;
          popRangeId = exitRangeInfo->header.destInstanceObjectId;
        }

        auto& housingMgr = Common::Service< World::Manager::HousingMgr >::ref();
        auto landSetId = housingMgr.toLandSetId( housingTeriId, static_cast< int8_t >( arg1 ) );
        auto pTeri = teriMgr().getTerritoryByGuId( landSetId );

        if( !pTeri )
          return;

        performWarp( player, popRangeId, pTeri->getGuId(), Sapphire::Common::WARP_TYPE_EXIT_RANGE, halfPi );
      }
      else
      {
        // Go to destination territory
        auto pTeri = teriMgr().getTerritoryByTypeId( exitRangeInfo->header.destTerritoryType );
        if( !pTeri )
          return;

        performWarp( player, exitRangeInfo->header.destInstanceObjectId,
                     pTeri->getGuId(), Sapphire::Common::WARP_TYPE_TOWN_TRANSLATE, halfPi );
      }
    }
  }


  void Scene00000( Entity::Player& player, uint32_t eventId, uint32_t exitRangeId )
  {
    auto exitRangeInfo = instanceObjectCache().getExitRange( player.getTerritoryTypeId(), exitRangeId );
    if( exitRangeInfo )
    {
      eventMgr().playScene( player, eventId, 0, NO_DEFAULT_CAMERA | HIDE_HOTBAR,
                            { 2, exitRangeInfo->header.destTerritoryType },
                            bindSceneReturn( &CmnExitRange::Scene00000Return ) );
    }
  }

  void onWithinRange( Entity::Player& player, uint32_t eventId, uint32_t param1, float x, float y, float z ) override
  {
    Scene00000( player, eventId, param1 );
  }
};

EXPOSE_SCRIPT( CmnExitRange );
