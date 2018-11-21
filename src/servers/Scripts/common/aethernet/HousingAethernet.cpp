#include <ScriptObject.h>
#include <Actor/Player.h>

#include <Framework.h>
#include <Exd/ExdDataGenerated.h>
#include <Zone/Zone.h>

using namespace Core;

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
      auto pExdData = getFramework()->get< Core::Data::ExdDataGenerated >();
      if( !pExdData )
        return;

      auto housingAethernetIds = pExdData->getHousingAethernetIdList();
      auto terrritoryTypeId = player.getCurrentZone()->getTerritoryTypeId();

      // param2 is the index starting from 0 inside housingaethernet.exd, but the ID column starts at 0x001E0000........ wtf
      auto pHousingAethernet = pExdData->get< Core::Data::HousingAethernet >( getId() + result.param2 );
      if( !pHousingAethernet )
        return;

      // check we're teleporting to the same territorytype
      if( player.getCurrentZone()->getTerritoryTypeId() != pHousingAethernet->territoryType )
        return;

      player.sendDebug( "got level entry: " + std::to_string( pHousingAethernet->level ) );
    } );
  }
};