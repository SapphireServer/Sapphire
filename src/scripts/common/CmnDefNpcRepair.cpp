#include <ScriptObject.h>
#include <Actor/Player.h>

using namespace Sapphire;

class CmnDefNpcRepair :
  public Sapphire::ScriptAPI::EventScript
{
public:
  CmnDefNpcRepair() :
    Sapphire::ScriptAPI::EventScript( 0xB0013 )
  {
  }

  void Scene00000( Entity::Player& player )
  {
    player.playScene( getId(), 0, HIDE_HOTBAR, 0, 1 );
  }

  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    Scene00000( player );
  }
};

EXPOSE_SCRIPT( CmnDefNpcRepair );