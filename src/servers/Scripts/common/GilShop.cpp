#include <ScriptObject.h>
#include <Actor/Player.h>

#include <Framework.h>
#include <Manager/ShopMgr.h>

using namespace Core;

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
        auto shopMgr = getFramework()->get< Sapphire::World::Manager::ShopMgr >();

        shopMgr->purchaseGilShopItem( player, result.eventId, result.param3, result.param4 );
      }

      // sell
      else if( result.param2 == 2 )
      {
        // so apparently shops will always show a sell window
        // BUT won't always let you sell stuff (eg, housing permit menu)
        // there doesn't seem to be anything in gilshop exd for that, so maybe it's some shitty server hack?
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