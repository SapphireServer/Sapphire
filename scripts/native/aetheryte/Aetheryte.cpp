#include "../ScriptObject.h"

#define ACTION_ATTUNE 0x13
#define ACTION_TELEPORT 0x4

#define AetheryteBaseId 0x50000
#define AETHERYTE_MENU_AETHERNET 1
#define AETHERYTE_MENU_HOUSING 2
#define AETHERYTE_MENU_HOME_POINT 3
#define AETHERYTE_MENU_FAVORITE_POINT 4
#define AETHERYTE_MENU_FAVORITE_POINT_SECURITY_TOKEN 5

class Aetheryte : public EventScript
{
public:
   Aetheryte() : EventScript( "Aetheryte", EVENTSCRIPT_AETHERYTE_ID )
   {}

   void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
   {
      if( player.isAetheryteRegistered( eventId & 0xFFFF ) )
      {
         player.eventPlay( eventId, 0, 1, []( Entity::Player& player, uint32_t eventId, uint16_t param1, uint16_t param2, uint16_t param3 )
         {
            if( param1 == 256 ) // set homepoint
            {
               player.setHomepoint( eventId & 0xFFFF );
               player.sendQuestMessage( eventId, 2, 0xEA, 0, 0 );
            }
            else if( param1 == 512 ) // aethernet access
            {
               if( param2 == 4 )
               {
                  player.teleport( param3, 2 );
               }
               else if( param2 == 2 ) // register favored destination
               {

               }
//               else if( param2 == 0xC3E1 ) // register free destination
//               {
//
//               }

            }
         } );
      }
      else
      {
         player.eventActionStart( eventId, ACTION_ATTUNE, []( Entity::Player& player, uint32_t eventId, uint64_t additional )
         {
            player.registerAetheryte( eventId & 0xFFFF );

            if( player.isActionLearned( ACTION_TELEPORT ) )
            {
               player.sendQuestMessage( eventId, 0, 2, 0, 0 );
            }
            else
            {
               player.sendQuestMessage( eventId, 0, 1, 1, 0 );
               player.learnAction( ACTION_TELEPORT );
            }
         },
         [] ( Entity::Player& player, uint32_t eventId, uint64_t additional )
         {}, 0 );
      }
   }
};

EXPORT_SCRIPTOBJECT( Aetheryte )