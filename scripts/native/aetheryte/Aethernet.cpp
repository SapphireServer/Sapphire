#include "../ScriptObject.h"

#define ACTION_ATTUNE 0x13

#define AetheryteBaseId 0x50000
#define AETHERYTE_MENU_AETHERNET 1
#define AETHERYTE_MENU_HOUSING 2
#define AETHERYTE_MENU_HOME_POINT 3
#define AETHERYTE_MENU_FAVORITE_POINT 4
#define AETHERYTE_MENU_FAVORITE_POINT_SECURITY_TOKEN 5

class Aethernet : public EventScript
{
public:
   Aethernet() : EventScript( "Aethernet", EVENTSCRIPT_AETHERNET_ID )
   {}

   void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
   {
      if( player.isAetheryteRegistered( eventId & 0xFFFF ) )
      {
         player.eventPlay( eventId, 2, 0, []( Entity::Player& player, uint32_t eventId, uint16_t param1, uint16_t param2, uint16_t param3 )
         {
            if( param1 == 256 )
            {
               player.teleport( param2, 2 );
            }
         } );
      }
      else
      {
         player.eventActionStart( eventId, ACTION_ATTUNE, []( Entity::Player& player, uint32_t eventId, uint64_t additional )
         {
            player.registerAetheryte( eventId & 0xFFFF );
            player.eventPlay( eventId, 3, 0, 0, 0 );
         },
         [] ( Entity::Player& ply, uint32_t evntId, uint64_t additional )
         {

         }, 0 );

         player.unlock();
      }

   }
};

EXPORT_SCRIPTOBJECT( Aethernet )