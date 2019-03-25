#include <ScriptObject.h>
#include <Actor/Player.h>

#include <Framework.h>
#include <Manager/ShopMgr.h>

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
    player.playScene( eventId, 0, SCENE_FLAGS, 0, 2, std::bind( &GilShop::shopCallback, this, std::placeholders::_1, std::placeholders::_2 ) );
  }

private:
  void shopInteractionCallback( Entity::Player& player, const Event::SceneResult& result )
  {
    // item purchase
    if( result.param1 == 768 )
    {
      // buy
      if( result.param2 == 1 )
      {
        auto shopMgr = framework()->get< Sapphire::World::Manager::ShopMgr >();

        shopMgr->purchaseGilShopItem( player, result.eventId, result.param3, result.param4 );
      }

      // sell
      // can't sell if the vendor is yourself (eg, housing permit shop)
      else if( result.param2 == 2 && result.actorId != player.getId() )
      {

      }

      player.playGilShop( result.eventId, SCENE_FLAGS, std::bind( &GilShop::shopInteractionCallback, this, std::placeholders::_1, std::placeholders::_2 ) );
      return;
    }

    // exit
    player.playScene( result.eventId, 255, SCENE_FLAGS );
  }

  void shopCallback( Entity::Player& player, const Event::SceneResult& result )
  {
    player.playGilShop( result.eventId, SCENE_FLAGS, std::bind( &GilShop::shopInteractionCallback, this, std::placeholders::_1, std::placeholders::_2 ) );
  }
};

EXPOSE_SCRIPT( GilShop );