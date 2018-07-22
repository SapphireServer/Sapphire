#include <ScriptObject.h>
#include <Actor/Player.h>

class GilShop : public EventScript
{
public:
   GilShop() : EventScript( 0x00041 )
   {}

   void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
   {
      auto callback = [actorId]( Entity::Player& player, const Event::SceneResult& result )
      {
         player.playGilShop( actorId, result.eventId, HIDE_HOTBAR | NO_DEFAULT_CAMERA );
      };

      player.playScene( eventId, 0, HIDE_HOTBAR | NO_DEFAULT_CAMERA, 0, 2, callback );
   }
};