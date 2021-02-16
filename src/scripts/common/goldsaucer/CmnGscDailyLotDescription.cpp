#include <ScriptObject.h>
#include <Actor/Player.h>

using namespace Sapphire;

class CmnGscDailyLotDescription :
  public Sapphire::ScriptAPI::EventScript
{
public:
  CmnGscDailyLotDescription() :
    Sapphire::ScriptAPI::EventScript( 721122 )
  {
  }

  void Scene00000( Entity::Player& player )
  {
    player.playScene( getId(), 0, HIDE_HOTBAR, 0, 0 );
  }

  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    Scene00000( player );
  }
};

EXPOSE_SCRIPT( CmnGscDailyLotDescription );