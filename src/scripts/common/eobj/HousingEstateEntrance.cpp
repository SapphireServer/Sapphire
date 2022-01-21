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
    eventMgr().playScene( player, eventId, 0, 0, [this, eobj]( Entity::Player& player, const Event::SceneResult& result )
    {
      // param2 == 1 when player wants to enter house
      if( result.getResult( 0 ) != 1 )
        return;

      auto& terriMgr = Common::Service< Sapphire::World::Manager::TerritoryMgr >::ref();

      auto pHZone = terriMgr.getZoneByTerritoryTypeId( player.getTerritoryTypeId() );
      auto zone = std::dynamic_pointer_cast< HousingZone >( pHZone );
      if( !zone )
        return;

      Common::LandIdent ident;
      ident.landId = eobj.getHousingLink() >> 8;
      ident.territoryTypeId = zone->getTerritoryTypeId();
      ident.wardNum = zone->getWardNum();
      ident.worldId = 67;

      auto internalZone = terriMgr.findOrCreateHousingInterior( ident );
      if( !internalZone )
      {
        // an error occurred during event movement
        // lol
        PlayerMgr::sendLogMessage( player, 1311 );
        eventMgr().eventFinish( player, result.eventId, 1 );
        return;
      }

      eventMgr().eventFinish( player, result.eventId, 1 );

      Common::FFXIVARR_POSITION3 pos {};

      auto land = zone->getLand( eobj.getHousingLink() >> 8 );
      if( !land )
        return;

      switch( land->getSize() )
      {
        // todo: think there's actually a poprange for this? double czech
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

      //player.setInstance( internalZone->getGuId(), pos );
    } );
  }
};

EXPOSE_SCRIPT( HousingEstateEntrance );