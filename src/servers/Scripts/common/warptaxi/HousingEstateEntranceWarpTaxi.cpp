#include <ScriptObject.h>
#include <Actor/Player.h>

#include "Zone/HousingZone.h"
#include "Actor/EventObject.h"

using namespace Sapphire;

class HousingEstateEntranceWarpTaxi :
  public Sapphire::ScriptAPI::EventScript
{
public:
  HousingEstateEntranceWarpTaxi() :
    Sapphire::ScriptAPI::EventScript( 0x0002004c )
  {
  }

  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    auto zone = std::dynamic_pointer_cast< HousingZone >( player.getCurrentZone() );
    if( !zone )
      return;

    auto eobj = zone->getEObj( actorId );
    if( !eobj )
      return;

    player.sendDebug( "Found plot entrance for plot: " + std::to_string( eobj->getHousingLink() >> 8 ) );

    player.playScene( getId(), 0, 0, []( Entity::Player& player, const Event::SceneResult& result )
    {
      if( result.param2 != 1 )
        return;

      // param2 == 1, zone into instance
    } );
  }
};