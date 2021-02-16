#include <ScriptObject.h>
#include <Actor/Player.h>

using namespace Sapphire;

class CmnGscEMJGameTable :
  public Sapphire::ScriptAPI::EventScript
{
public:
  CmnGscEMJGameTable() :
    Sapphire::ScriptAPI::EventScript( 721443 )
  {
  }

  void Scene00000( Entity::Player& player )
  {
    player.playScene( getId(), 0, HIDE_HOTBAR, 0, 0 );
    // All client side magic!
  }

  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    Scene00000( player );
  }
};

EXPOSE_SCRIPT( CmnGscEMJGameTable );