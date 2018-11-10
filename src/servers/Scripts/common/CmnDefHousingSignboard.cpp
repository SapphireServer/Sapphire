#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Zone/Zone.h>
#include <Zone/HousingZone.h>

using namespace Core;

class CmnDefHousingSignboard : public EventScript
{
public:
  CmnDefHousingSignboard() : EventScript( 721031 )
  {
  }

  void Scene00000( Entity::Player& player )
  {
    auto callback = [ this ]( Entity::Player& player, const Event::SceneResult& result )
    {
      // Purchase Land
      if( result.param2 == 2 )
      {
        auto activeLand = player.getActiveLand();
        auto territoryId = player.getTerritoryId();

        auto pTerritory = player.getCurrentZone();
        auto pHousing = std::dynamic_pointer_cast< HousingZone >( pTerritory );
        
        pHousing->playerPurchseLand( player, activeLand.plot, result.param2 );

      }
    };

    player.playScene( getId(), 0, HIDE_HOTBAR, 0, 0, callback );

  }

  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    Scene00000( player );
  }
};