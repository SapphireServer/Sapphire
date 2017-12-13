#include "../ScriptObject.h"

class CmnDefInnBed : public EventScript
{
public:
   CmnDefInnBed() : EventScript( "CmnDefInnBed", 720916 )
   {}

   // menu
   void Scene00000( Entity::Player& player )
   {
      auto callback = [ this ]( Entity::Player& player, uint32_t eventId, uint16_t param1, uint16_t param2, uint16_t param3 )
      {
         if( param2 > 0 )
            Scene00001( player, param2 );
      };

      player.eventPlay( getId(), 0, 0x2000, 0, 1, callback );
   }

   // lay down
   void Scene00001( Entity::Player& player, uint16_t param )
   {
      auto callback = [ this ]( Entity::Player& player, uint32_t eventId, uint16_t param1, uint16_t param2, uint16_t param3 )
      {
         Scene00002( player, param2 );
      };

      player.eventPlay( getId(), 1, 0xF32E48F8, 0, 1, param, callback );
   }

   // logout
   void Scene00002( Entity::Player& player, uint16_t param )
   {
      player.eventPlay( getId(), 2, 0xF32E48F8, 0, 1, param, nullptr );
   }

   // wake up
   void Scene00100( Entity::Player& player )
   {
      auto callback = []( Entity::Player& player, uint32_t eventId, uint16_t param1, uint16_t param2, uint16_t param3 )
      {};

      player.eventPlay( getId(), 100, 0x800, 0, 0, callback );
   }

   void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
   {
      Scene00000( player );
   }

   void onEnterZone( Entity::Player& player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {
      Scene00100( player );
   }
};

EXPORT_SCRIPTOBJECT( CmnDefInnBed )