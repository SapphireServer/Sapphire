#include <ScriptObject.h>
#include <Actor/Player.h>

#include <Exd/ExdData.h>
#include <datReader/DatCategories/bg/LgbTypes.h>
#include <datReader/DatCategories/bg/lgb.h>
#include <Util/UtilMath.h>

#include "Territory/InstanceObjectCache.h"
#include "Territory/Territory.h"
#include "Territory/Housing/HousingInteriorTerritory.h"

using namespace Sapphire;

class HousingWarpTaxiExitEstate : public Sapphire::ScriptAPI::EventScript
{
public:
  HousingWarpTaxiExitEstate() :
    Sapphire::ScriptAPI::EventScript( 0x0002004d )
  {
  }

  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    eventMgr().playScene( player, eventId, 0, 0, [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      if( result.getResult( 0 ) == 1 )
      {
        auto& terriMgr = Common::Service< Sapphire::World::Manager::TerritoryMgr >::ref();
        auto pHZone = terriMgr.getTerritoryByGuId( player.getTerritoryId() );
        if( !pHZone )
          return;
        auto zone = std::dynamic_pointer_cast< World::Territory::Housing::HousingInteriorTerritory >( pHZone );
        if( !zone )
          return;

        auto landIdent = zone->getLandIdent();

        int housingIndex;
        if( landIdent.territoryTypeId == 339 )
          housingIndex = 0;
        else if( landIdent.territoryTypeId == 340 )
          housingIndex = 1;
        else if( landIdent.territoryTypeId == 341 )
          housingIndex = 2;

        auto& exdData = Common::Service< Data::ExdData >::ref();
        auto info = exdData.getRow< Excel::HousingLandSet >( housingIndex );

        auto landInfo = info->_data.Lands[ landIdent.landId ];
        auto& instanceObjectCache = Common::Service< InstanceObjectCache >::ref();
        auto exitRange = instanceObjectCache.getPopRange( landInfo.ExitPopRange );

        Common::FFXIVARR_POSITION3 pos{ exitRange->data.transform.translation.x, exitRange->data.transform.translation.y, exitRange->data.transform.translation.z };
        float rot = Common::Util::eulerToDirection( { exitRange->data.transform.rotation.x, exitRange->data.transform.rotation.y, exitRange->data.transform.rotation.z } );

        warpMgr().requestMoveTerritory( player, Common::WarpType::WARP_TYPE_NORMAL, landIdent.territoryTypeId << 16 | landIdent.wardNum, pos, rot );
      }
    } );
  }
};

EXPOSE_SCRIPT( HousingWarpTaxiExitEstate );