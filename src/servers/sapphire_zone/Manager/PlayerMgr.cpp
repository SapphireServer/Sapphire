#include "PlayerMgr.h"

#include <Framework.h>
#include <Exd/ExdDataGenerated.h>

#include <Zone/TerritoryMgr.h>
#include <Zone/ZonePosition.h>

#include <Zone/HousingMgr.h>

#include <Actor/Player.h>

extern Sapphire::Framework g_fw;

void Sapphire::World::Manager::PlayerMgr::movePlayerToLandDestination( Sapphire::Entity::Player& player, uint32_t landId, uint16_t param )
{
  // check if we have one in the db first
  auto terriMgr = g_fw.get< Sapphire::TerritoryMgr >();
  if( !terriMgr )
    return;

  Sapphire::ZonePtr destinationZone;

  auto terriPos = terriMgr->getTerritoryPosition( landId );
  if( terriPos )
  {
    // check if its a housing zone, zoning is different here
    if( terriMgr->isHousingTerritory( terriPos->getTargetZoneId() ) )
    {
      auto housingMgr = g_fw.get< Sapphire::HousingMgr >();
      auto landSetId = housingMgr->toLandSetId( terriPos->getTargetZoneId(), param );

      auto housingZone = housingMgr->getHousingZoneByLandSetId( landSetId );

      if( !housingZone )
        return;

      destinationZone = housingZone;
    }
    else if( terriMgr->isInstanceContentTerritory( terriPos->getTargetZoneId() ) )
    {
      // todo: instance dungeon handling
      // will need to use setInstance so old pos gets set
      return;
    }
    else
    {
      // normal zones
      destinationZone = terriMgr->getZoneByTerritoryTypeId( terriPos->getTargetZoneId() );
    }
  }
  else
  {
    // todo: lookup land.exd and see if it's in there if its not in our db
    return;
  }

  if( !destinationZone )
    return;

  player.setPos( terriPos->getTargetPosition() );
  player.setRot( terriPos->getTargetRotation() );

  if( terriMgr->movePlayer( destinationZone, player.getAsPlayer() ) )
    player.sendZonePackets();
}