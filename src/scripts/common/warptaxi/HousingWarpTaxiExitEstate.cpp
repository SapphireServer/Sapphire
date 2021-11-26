#include <ScriptObject.h>
#include <Actor/Player.h>

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
        eventMgr().eventFinish( player, result.eventId, 1 );
        player.exitInstance();
      }
    } );
  }
};

EXPOSE_SCRIPT( HousingWarpTaxiExitEstate );