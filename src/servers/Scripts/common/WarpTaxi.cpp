#include <ScriptObject.h>
#include <Actor/Player.h>

#include <Exd/ExdDataGenerated.h>
#include <Zone/TerritoryMgr.h>
#include <Zone/HousingMgr.h>
#include <Zone/ZonePosition.h>
#include <Framework.h>

using namespace Core;

class WarpTaxi : public Sapphire::ScriptAPI::EventScript
{
public:
  WarpTaxi() :
    Sapphire::ScriptAPI::EventScript( 0x0002005a )
  {
  }

  void inner( Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.param1 == 256 ) // exit
    {
      player.eventFinish( 1310721, 0 );
      player.eventFinish( getId(), 1 );
    }
    else if( result.param1 == 768 ) // teleport to ward
    {
      player.eventFinish( 1310721, 0 );
      player.eventFinish( getId(), 1 );

      // todo: this is shit, move to housingmgr? handle moving players in and out of it there?
      auto exdData = getFramework()->get< Core::Data::ExdDataGenerated >();

      auto warp = exdData->get< Core::Data::Warp >( getId() );
      if( !warp )
        return;

      auto level = exdData->get< Core::Data::Level >( warp->level );
      if( !level )
      {

        // fetch from cache
        auto teriMgr = getFramework()->get< Core::TerritoryMgr >();

        auto pos = teriMgr->getTerritoryPosition( warp->level );
        if( !pos )
          return;

        // lookup instance
        auto housingMgr = getFramework()->get< Core::HousingMgr >();
        auto landSetId = housingMgr->toLandSetId( 341, result.param3 );
        auto hZone = housingMgr->getHousingZoneByLandSetId( landSetId );

        if( !hZone )
          return;

        player.setPos( pos->getTargetPosition() );
        player.setRot( pos->getTargetRotation() );
        player.setInstance( hZone );

      }
    }
    else
    {
      player.playScene( 1310721, 0, HIDE_HOTBAR, 0, 1, 341, std::bind( &WarpTaxi::inner, this, std::placeholders::_1, std::placeholders::_2 ) );
    }
  }

  void inner2( Entity::Player& player, uint64_t actorId )
  {
    player.playScene( getId(), 0, HIDE_HOTBAR, 0, 0, 32529, [this, actorId]( Entity::Player& player, const Event::SceneResult& result )
    {
      player.eventStart( actorId, 1310721, Event::EventHandler::Nest, 1, 0 );

      player.playScene( 1310721, 0, HIDE_HOTBAR, 0, 1, 341, std::bind( &WarpTaxi::inner, this, std::placeholders::_1, std::placeholders::_2 ) );
    } );
  }

  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    auto exdData = getFramework()->get< Core::Data::ExdDataGenerated >();
    if( !exdData )
      return;

    auto warp = exdData->get< Core::Data::Warp >( eventId );
    if( !warp )
      return;

    player.eventStart( actorId, warp->defaultTalk1, Event::EventHandler::Nest, 0, 0, std::bind( &WarpTaxi::inner2, this, std::placeholders::_1, std::placeholders::_2 ) );
    player.playScene( warp->defaultTalk1, 0, HIDE_HOTBAR, 0, 0, 7, nullptr );
  }
};