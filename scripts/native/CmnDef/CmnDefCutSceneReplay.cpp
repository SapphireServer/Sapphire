#include "../ScriptObject.h"

class CmnDefCutSceneReplay : public EventScript
{
public:
   CmnDefCutSceneReplay() : EventScript( "CmnDefCutSceneReplay", 721028 )
   {}

   void Scene00000( Entity::Player& player )
   {
      auto callback = [ this ]( Entity::Player& player, uint32_t eventId, uint16_t param1, uint16_t param2, uint16_t param3 )
      {
         if( param2 != 0 )
         {
            Scene00001( player, param2 );
         }
      };

      player.eventPlay( getId(), 0, 0x2000, 0, 1, callback );
   }

   void Scene00001( Entity::Player& player, uint16_t returnScene )
   {
      auto callback = []( Entity::Player& player, uint32_t eventId, uint16_t param1, uint16_t param2, uint16_t param3 )
      {
         // todo: this is fucked
      };

      player.eventPlay( getId(), 1, 0xFB2EC8F8, 0, 1, returnScene, callback );
   }

   void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
   {
      Scene00000( player );
   }
};

EXPORT_SCRIPTOBJECT( CmnDefCutSceneReplay )