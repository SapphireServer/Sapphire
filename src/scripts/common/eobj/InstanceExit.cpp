#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Service.h>

#include "Actor/EventObject.h"
#include "Territory/HousingZone.h"
#include "Manager/TerritoryMgr.h"
#include "Manager/PlayerMgr.h"
#include "Territory/Land.h"


using namespace Sapphire;
using namespace Sapphire::World::Manager;

class InstanceExit :
  public Sapphire::ScriptAPI::EventObjectScript
{
public:
  InstanceExit() :
    Sapphire::ScriptAPI::EventObjectScript( 2000139 )
  {
  }

  void onTalk( uint32_t eventId, Entity::Player& player, Entity::EventObject& eobj ) override
  {
    eventMgr().playScene( player, eventId, 1, 0, [this, eobj]( Entity::Player& player, const Event::SceneResult& result )
    {
      if( result.getResult( 0 ) != 1 )
        playerMgr().onExitInstance( player );
    } );
  }
};

EXPOSE_SCRIPT( InstanceExit );