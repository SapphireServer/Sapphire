#include "../ScriptObject.h"

#define ACTION_CREATE 2
#define ACTION_RENAME 3
#define ACTION_REMOVE 4

class CmnDefLinkShell : public EventScript
{
public:
   CmnDefLinkShell() : EventScript( "CmnDefLinkShell", 0xB0006 )
   {}

   void Scene00001( Entity::Player& player )
   {
      auto callback = [ this ]( Entity::Player& player, uint32_t eventId, uint16_t param1, uint16_t param2, uint16_t param3 )
      {
         switch( param2 )
         {
            case ACTION_CREATE:
               Scene00002( player );
               break;

            case ACTION_RENAME:
               Scene00003( player );
               break;

            case ACTION_REMOVE:
               Scene00004( player );
               break;
         }
      };

      player.eventPlay( getId(), 1, 0, 0, 0, callback );
   }

   // create linkshell
   void Scene00002( Entity::Player& player )
   {
      player.eventPlay( getId(), 2, 0, 0, 0 );
   }

   // rename linkshell
   void Scene00003( Entity::Player& player )
   {
      player.eventPlay( getId(), 3, 0, 0, 0 );
   }

   // remove linkshell
   void Scene00004( Entity::Player& player )
   {
      player.eventPlay( getId(), 4, 0, 0, 0 );
   }

   void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
   {
      Scene00001( player );
   }
};

EXPORT_SCRIPTOBJECT( CmnDefLinkShell )