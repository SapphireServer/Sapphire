#include <ScriptObject.h>
#include <Actor/Player.h>

class GilShop : public EventScript
{
public:
   GilShop() : EventScript( 0x00041 )
   {}

   constexpr static auto SCENE_FLAGS = HIDE_HOTBAR | NO_DEFAULT_CAMERA;

   static void shopInteractionCallback( Entity::Player& player, const Event::SceneResult& result )
   {
      // item purchase
      if( result.param1 == 768 )
      {
         //player.playGilShop( result.eventId, HIDE_HOTBAR | NO_DEFAULT_CAMERA, shopInteractionCallback );

         player.sendDebug("got tradeQuantity: " + std::to_string( result.tradeQuantity ) );
         player.playScene( result.eventId, 10, SCENE_FLAGS, 0, 0, shopInteractionCallback );
         return;
      }

      // exit
      player.playScene( result.eventId, 255, SCENE_FLAGS );
   }

   static void shopCallback( Entity::Player& player, const Event::SceneResult& result )
   {
      //player.playGilShop( result.eventId, HIDE_HOTBAR | NO_DEFAULT_CAMERA, shopInteractionCallback );

      player.playScene( result.eventId, 10, SCENE_FLAGS, 0, 0, shopInteractionCallback );
   }

   void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
   {
      player.playScene( eventId, 0, SCENE_FLAGS, 0, 2, shopCallback );
   }
};