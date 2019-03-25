#include <ScriptObject.h>
#include <Actor/Player.h>

#include <Framework.h>
#include <Exd/ExdDataGenerated.h>
#include <Territory/HousingZone.h>
#include <Manager/PlayerMgr.h>

using namespace Sapphire;

class HousingAethernet :
  public Sapphire::ScriptAPI::EventScript
{
public:
  HousingAethernet() :
    Sapphire::ScriptAPI::EventScript( 0x001E0000 )
  {
  }

  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    player.playScene( eventId, 0, HIDE_HOTBAR | NO_DEFAULT_CAMERA, [this, eventId]( Entity::Player& player, const Event::SceneResult& result )
    {
      auto pExdData = framework()->get< Sapphire::Data::ExdDataGenerated >();
      if( !pExdData )
        return;

      auto housingZone = std::dynamic_pointer_cast< HousingZone >( player.getCurrentZone() );
      if( !housingZone )
        return;

      // param2 is the index starting from 0 inside housingaethernet.exd, but the ID column starts at 0x001E0000........ wtf
      auto pHousingAethernet = pExdData->get< Sapphire::Data::HousingAethernet >( getId() + result.param2 );
      if( !pHousingAethernet )
        return;

      // check we're teleporting to the same territorytype
      if( player.getCurrentZone()->getTerritoryTypeId() != pHousingAethernet->territoryType )
        return;

      // todo: this needs to be done properly and used queued zoning + aethernet animation
      // moving a player inside an event will crash the game so we end it hre
      player.eventFinish( eventId, 1 );

      auto playerMgr = framework()->get< Sapphire::World::Manager::PlayerMgr >();
      playerMgr->movePlayerToLandDestination( player, pHousingAethernet->level, housingZone->getWardNum() );
    } );
  }
};

EXPOSE_SCRIPT( HousingAethernet );