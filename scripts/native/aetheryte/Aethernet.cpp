#include "../ScriptObject.h"

#define ACTION_ATTUNE 0x13

#define AetheryteBaseId 0x50000
#define AETHERYTE_MENU_AETHERNET 1
#define AETHERYTE_MENU_HOUSING 2
#define AETHERYTE_MENU_HOME_POINT 3
#define AETHERYTE_MENU_FAVORITE_POINT 4
#define AETHERYTE_MENU_FAVORITE_POINT_SECURITY_TOKEN 5

class Aethernet : public QuestScript
{
public:
   Aethernet() : QuestScript( "Aethernet", 0x50001 )
   {}

   virtual void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId )
   {
      if( player.isAetheryteRegistered( eventId & 0xFFFF ) )
      {
         player.eventPlay( eventId, 2, 0, []( Entity::Player& ply, uint32_t evntId, uint16_t p1, uint16_t p2, uint16_t p3 )
         {
            if( p1 == 256 )
            {
               ply.teleport( p2, 2 );
            }
         } );
      }
      else
      {
         player.eventActionStart( eventId, ACTION_ATTUNE, []( Entity::Player& ply, uint32_t evntId, uint64_t additional )
         {
            ply.registerAetheryte( evntId & 0xFFFF );
            ply.eventPlay( evntId, 3, 0, 0, 0 );
         },
         [] ( Entity::Player& ply, uint32_t evntId, uint64_t additional )
         {

         }, 0 );

         player.unlock();
      }

   }
};

EXPORT_SCRIPTOBJECT( Aethernet )