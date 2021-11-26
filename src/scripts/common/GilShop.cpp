#include <ScriptObject.h>
#include <Actor/Player.h>

#include <Manager/ShopMgr.h>
#include <Service.h>

using namespace Sapphire;

class GilShop :
  public Sapphire::ScriptAPI::EventScript
{
public:
  GilShop() :
    Sapphire::ScriptAPI::EventScript( 0x00040000 )
  {
  }

  constexpr static auto SCENE_FLAGS = HIDE_HOTBAR | NO_DEFAULT_CAMERA;

  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    eventMgr().playScene( player, eventId, 0, SCENE_FLAGS, { 2 }, std::bind( &GilShop::shopCallback, this, std::placeholders::_1, std::placeholders::_2 ) );
  }

private:
  void shopInteractionCallback( Entity::Player& player, const Event::SceneResult& result )
  {
    // item purchase
    if( result.numOfResults == 255 )
    {
      // buy
      if( result.getResult( 1 ) == 1 )
      {
        auto& shopMgr = Common::Service< Sapphire::World::Manager::ShopMgr >::ref();
        shopMgr.purchaseGilShopItem( player, result.getResult( 4 ), result.getResult( 6 ), result.getResult( 5 ) );
      }

      // sell
      // can't sell if the vendor is yourself (eg, housing permit shop)
      else if( result.getResult( 1 ) == 2 && result.actorId != player.getId() )
      {
        auto& shopMgr = Common::Service< Sapphire::World::Manager::ShopMgr >::ref();
        shopMgr.sellGilShopItem( player, result.getResult( 2 ), result.getResult( 3 ), result.getResult( 6 ), result.getResult( 5 ) );
      }

      eventMgr().playGilShop( player, result.eventId, SCENE_FLAGS, result.getResult( 0 ), [ & ]( Entity::Player& player, const Event::SceneResult& result )
      {
        shopInteractionCallback( player, result );
      });
      return;
    }

    // exit
    eventMgr().eventFinish( player, result.eventId, 1 );
  }

  void shopCallback( Entity::Player& player, const Event::SceneResult& result )
  {
    eventMgr().playGilShop( player, result.eventId, SCENE_FLAGS, 0, [ & ]( Entity::Player& player, const Event::SceneResult& result )
    {
      shopInteractionCallback( player, result );
    });
  }
};

EXPOSE_SCRIPT( GilShop );