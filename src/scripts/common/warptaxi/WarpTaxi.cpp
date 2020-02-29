#include <ScriptObject.h>
#include <Actor/Player.h>

#include <datReader/DatCategories/bg/LgbTypes.h>
#include <datReader/DatCategories/bg/lgb.h>

#include "Territory/InstanceObjectCache.h"

#include <Exd/ExdDataGenerated.h>
#include <Manager/PlayerMgr.h>
#include <Service.h>

using namespace Sapphire;

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

      auto& exdData = Common::Service< Data::ExdDataGenerated >::ref();
      auto& popRange = Common::Service< Sapphire::InstanceObjectCache >::ref();

      auto warp = exdData.get< Sapphire::Data::Warp >( getId() );
      if( !warp )
        return;

      auto& playerMgr = Common::Service< Sapphire::World::Manager::PlayerMgr >::ref();

      auto pPop = popRange.getPopRange( warp->territoryType, warp->popRange );

      if( !pPop )
      {
        std::cout << "not found...";
      }
      else
      {
        std::cout << "found!!";
      }

      playerMgr.movePlayerToLandDestination( player, warp->popRange, result.param3 );
    }
    else
    {
      player.playScene( 1310721, 0, HIDE_HOTBAR, 0, 1, 341,
                        std::bind( &WarpTaxi::inner, this, std::placeholders::_1, std::placeholders::_2 ) );
    }
  }

  void inner2( Entity::Player& player, uint64_t actorId )
  {
    player.playScene( getId(), 0, HIDE_HOTBAR, 0, 0, 32529,
                      [this, actorId]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        player.eventStart( actorId, 1310721, Event::EventHandler::Nest, 1, 0 );

                        player.playScene( 1310721, 0, HIDE_HOTBAR, 0, 1, 341,
                                          std::bind( &WarpTaxi::inner, this, std::placeholders::_1, std::placeholders::_2 ) );
                      } );
  }

  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    auto exdData = Common::Service< Sapphire::Data::ExdDataGenerated >::ref();

    auto warp = exdData.get< Sapphire::Data::Warp >( eventId );
    if( !warp )
      return;

    player.eventStart( actorId, warp->conditionSuccessEvent, Event::EventHandler::Nest, 0, 0,
                       std::bind( &WarpTaxi::inner2, this, std::placeholders::_1, std::placeholders::_2 ) );
    player.playScene( warp->conditionSuccessEvent, 0, HIDE_HOTBAR, 0, 0, 7, nullptr );
  }
};

EXPOSE_SCRIPT( WarpTaxi );