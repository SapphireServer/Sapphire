#include <ScriptObject.h>
#include <Actor/Player.h>

#include "Actor/EventObject.h"
#include "Territory/HousingZone.h"
#include "Manager/TerritoryMgr.h"
#include "Territory/Land.h"
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
    player.playScene( eventId, 0, 0, [this, eobj]( Entity::Player& player, const Event::SceneResult& result )
    {
      // param2 == 1 when player wants to enter house
      if( result.param2 != 1 )
        return;

      auto terriMgr = framework()->get< Sapphire::World::Manager::TerritoryMgr >();
      if( !terriMgr )
        return;

      auto zone = std::dynamic_pointer_cast< HousingZone >( player.getCurrentZone() );
      if( !zone )
        return;

      Common::LandIdent ident;
      ident.landId = eobj.getHousingLink() >> 8;
      ident.territoryTypeId = zone->getTerritoryTypeId();
      ident.wardNum = zone->getWardNum();
      ident.worldId = 67;

      auto internalZone = terriMgr->findOrCreateHousingInterior( ident );
      if( !internalZone )
      {
        // an error occurred during event movement
        // lol
        player.sendLogMessage( 1311 );
        player.eventFinish( result.eventId, 1 );
        return;
      }

      player.eventFinish( result.eventId, 1 );

      Common::FFXIVARR_POSITION3 pos {};

      auto land = zone->getLand( eobj.getHousingLink() >> 8 );
      if( !land )
        return;

      switch( land->getSize() )
      {
        case 0:
        {
          pos = { 0.1321167f, 0.f, 2.746273f };
          break;
        }
        case 1:
        {
          pos = { 1.337722f, 0.f, 3.995964f };
          break;
        }
        case 2:
        {
          pos = { 0.07214607f, 0.f, 8.217761f };
          break;
        }
        default:
          return;
      }

      player.setInstance( internalZone, pos );
    } );
  }
};

EXPOSE_SCRIPT( HousingEstateEntrance );