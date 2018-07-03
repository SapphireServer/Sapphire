#include <ScriptObject.h>
#include <Actor/Player.h>

class CmnDefMogLetter : public EventScript
{
public:
   CmnDefMogLetter() : EventScript( 720898 )
   {}

   void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
   {
      Scene00001( player );
   }

   void Scene00001( Entity::Player& player )
   {
      player.playScene( getId(), 1, 0,
         [&]( Entity::Player& player, const Event::SceneResult& result )
         {
         } );
   }
};