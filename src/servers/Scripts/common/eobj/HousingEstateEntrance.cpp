#include <ScriptObject.h>
#include <Actor/Player.h>

#include "Actor/EventObject.h"
#include "Territory/HousingZone.h"
#include "Manager/TerritoryMgr.h"
#include "Framework.h"

using namespace Sapphire;

class HousingEstateEntrance :
  public Sapphire::ScriptAPI::EventObjectScript
{
public:
  HousingEstateEntrance() :
    Sapphire::ScriptAPI::EventObjectScript( 2002737 )
  {
  }

  void onTalk( uint32_t eventId, Entity::Player& player, Entity::EventObject& eobj ) override
  {
    player.sendDebug( "Found plot entrance for plot: " + std::to_string( eobj.getHousingLink() >> 8 ) );

    player.playScene( eventId, 0, 0, [this, eobj]( Entity::Player& player, const Event::SceneResult& result )
    {
      auto terriMgr = getFramework()->get< Sapphire::World::Manager::TerritoryMgr >();
      if( !terriMgr )
        return;

      auto zone = std::dynamic_pointer_cast< HousingZone >( player.getCurrentZone() );
      if( !zone )
        return;

      Common::LandIdent ident;
      ident.landId = eobj.getHousingLink() >> 8;
      ident.territoryTypeId = zone->getTerritoryTypeId();
      ident.wardNum = zone->getWardNum();

      auto internalZone = terriMgr->findOrCreateHousingInterior( ident );
      if( internalZone )
      {
        player.sendDebug( "created zone with guid: " + std::to_string( internalZone->getGuId() ) + "\nname: " + internalZone->getName() );
      }

      if( result.param2 != 1 )
        return;

      // param2 == 1, zone into instance
    } );
  }
};