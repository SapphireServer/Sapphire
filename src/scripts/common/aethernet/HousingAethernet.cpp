#include <ScriptObject.h>
#include <Actor/Player.h>

#include <Exd/ExdData.h>
#include <Territory/HousingZone.h>
#include <Manager/PlayerMgr.h>
#include <Service.h>

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
    eventMgr().playScene( player, eventId, 0, HIDE_HOTBAR | NO_DEFAULT_CAMERA, [this, eventId]( Entity::Player& player, const Event::SceneResult& result )
    {
      auto& exdData = Common::Service< Sapphire::Data::ExdData >::ref();

      auto housingZoneId = player.getTerritoryTypeId();
      auto activeLand = player.getActiveLand();

      return;
      // param2 is the index starting from 0 inside housingaethernet.exd, but the ID column starts at 0x001E0000........ wtf
      /*auto pHousingAethernet = exdData.getRow< Excel::HousingAethernet >( getId() + result.param2 );
      if( !pHousingAethernet )
        return;

      // check we're teleporting to the same territorytype
      if( player.getTerritoryTypeId() != pHousingAethernet->territoryType )
        return;

      // todo: this needs to be done properly and used queued zoning + aethernet animation
      // moving a player inside an event will crash the game so we end it here
      player.eventFinish( eventId, 1 );

      auto& playerMgr = Common::Service< Sapphire::World::Manager::PlayerMgr >::ref();
      playerMgr.movePlayerToLandDestination( player, pHousingAethernet->level, housingZone->getWardNum() );*/
    } );
  }
};

EXPOSE_SCRIPT( HousingAethernet );