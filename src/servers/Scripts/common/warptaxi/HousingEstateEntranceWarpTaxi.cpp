#include <ScriptObject.h>
#include <Actor/Player.h>

#include "Actor/EventObject.h"

using namespace Sapphire;

class HousingEstateEntranceWarpTaxi :
  public Sapphire::ScriptAPI::EventObjectScript
{
public:
  HousingEstateEntranceWarpTaxi() :
    Sapphire::ScriptAPI::EventObjectScript( 2002737 )
  {
  }

  void onTalk( uint32_t eventId, Entity::Player& player, Entity::EventObject& eobj ) override
  {
    player.sendDebug( "Found plot entrance for plot: " + std::to_string( eobj.getHousingLink() >> 8 ) );

    player.playScene( eventId, 0, 0, []( Entity::Player& player, const Event::SceneResult& result )
    {
      if( result.param2 != 1 )
        return;

      // param2 == 1, zone into instance

    } );
  }
};