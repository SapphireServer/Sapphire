#include "PlayerMgr.h"

#include <Exd/ExdDataGenerated.h>

#include <Manager/TerritoryMgr.h>
#include <Territory/ZonePosition.h>
#include <Territory/Territory.h>

#include <Manager/HousingMgr.h>

#include <Actor/Player.h>
#include <Service.h>

using namespace Sapphire::World::Manager;

void Sapphire::World::Manager::PlayerMgr::movePlayerToLandDestination( Sapphire::Entity::Player& player, uint32_t landId, uint16_t param )
{
  // check if we have one in the db first
  //auto& terriMgr = Common::Service< TerritoryMgr >::ref();
  auto& terriMgr = *reinterpret_cast< Sapphire::World::Manager::TerritoryMgr* >( player.getTerritoryMgr() );

  Sapphire::TerritoryPtr destinationZone;

  auto terriPos = terriMgr.getTerritoryPosition( landId );
  if( terriPos )
  {
    // check if its a housing zone, zoning is different here
    if( terriMgr.isHousingTerritory( terriPos->getTargetZoneId() ) )
    {
      auto& housingMgr = Common::Service< HousingMgr >::ref();
      auto landSetId = housingMgr.toLandSetId( terriPos->getTargetZoneId(), param );

      auto housingZone = housingMgr.getHousingZoneByLandSetId( landSetId );

      if( !housingZone )
        return;

      destinationZone = housingZone;
    }
    else if( terriMgr.isInstanceContentTerritory( terriPos->getTargetZoneId() ) )
    {
      // todo: instance dungeon handling
      // will need to use setInstance so old pos gets set
      return;
    }
    else
    {
      // normal zones
      destinationZone = terriMgr.getZoneByTerritoryTypeId( terriPos->getTargetZoneId() );
    }
  }
  else
  {
    // todo: lookup land.exd and see if it's in there if its not in our db
    return;
  }

  if( !destinationZone )
  {
    player.sendDebug( "Unable to find applicable territory for Warp#{0}. "
                      "Check that it exists inside zonepositions table.",
                      landId );
    return;
  }

  player.setPos( terriPos->getTargetPosition() );
  player.setRot( terriPos->getTargetRotation() );

  terriMgr.movePlayer( destinationZone, player.getAsPlayer() );
}
