#include <ScriptObject.h>
#include <Actor/Player.h>

#include <datReader/DatCategories/bg/LgbTypes.h>
#include <datReader/DatCategories/bg/lgb.h>

#include "Territory/InstanceObjectCache.h"

#include <Exd/ExdData.h>
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
/*    if( result.numOfResults == 1 ) // exit
    {
      eventMgr().eventFinish( player, 1310721, 0 );
      eventMgr().eventFinish( player, getId(), 1 );
    }
    else if( result.numOfResults == 2 ) // teleport to ward
    {
      eventMgr().eventFinish( player, 1310721, 0 );
      eventMgr().eventFinish( player, getId(), 1 );

      auto& exdData = Common::Service< Data::ExdData >::ref();
      auto& popRange = Common::Service< Sapphire::InstanceObjectCache >::ref();

      auto warp = exdData.getRow< Excel::Warp >( getId() );
      if( !warp )
        return;

      auto& playerMgr = Common::Service< Sapphire::World::Manager::PlayerMgr >::ref();

      // EXD TODO: This was TerritoryType from warp before...
      auto pPop = popRange.getPopRange( player.getTerritoryTypeId(), warp->data().PopRange );

      if( !pPop )
      {
        std::cout << "not found...";
      }
      else
      {
        std::cout << "found!!";
      }

      playerMgr.movePlayerToLandDestination( player, warp->data().PopRange, result.getResult( 1 ) );
    }
    else
    {
      eventMgr().playScene( player, 1310721, 0, HIDE_HOTBAR, { 1, 341 },
                            std::bind( &WarpTaxi::inner, this, std::placeholders::_1, std::placeholders::_2 ) );
    }*/
  }

  void inner2( Entity::Player& player, uint64_t actorId )
  {
 /*   eventMgr().playScene( player, getId(), 0, HIDE_HOTBAR, { 32529 },
                      [this, actorId]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        eventMgr().eventStart( player, actorId, 1310721, Event::EventHandler::Nest, 1, 0 );

                        eventMgr().playScene( player, 1310721, 0, HIDE_HOTBAR, { 1, 341 },
                                              std::bind( &WarpTaxi::inner, this, std::placeholders::_1, std::placeholders::_2 ) );
                      } );*/
  }

  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
/*    auto& exdData = Common::Service< Sapphire::Data::ExdData >::ref();

    auto warp = exdData.getRow< Excel::Warp >( eventId );
    if( !warp )
      return;

    // EXD TODO: Not sure Warpcondition is correct here
    eventMgr().eventStart( player, actorId, warp->data().WarpCondition, Event::EventHandler::Nest, 0, 0,
                           std::bind( &WarpTaxi::inner2, this, std::placeholders::_1, std::placeholders::_2 ) );
    eventMgr().playScene( player, warp->data().WarpCondition, 0, HIDE_HOTBAR, { 7 }, nullptr );*/
  }
};

EXPOSE_SCRIPT( WarpTaxi );