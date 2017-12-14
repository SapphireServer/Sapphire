#include "../ScriptObject.h"

#define ERANGE_HOWTO_ANN_AND_QUEST 2117539
#define ERANGE_HOWTO_QUEST_REWARD 2366417
#define ERANGE_SEQ_1_CLOSED_1 2351918
#define POS_SEQ_1_CLOSED_RETURN_1 2351921
#define ERANGE_SEQ_1_CLOSED_2 2351919
#define POS_SEQ_1_CLOSED_RETURN_2 2351921
#define ERANGE_ALWAYS_CLOSED_1 2280846
#define POS_ALWAYS_CLOSED_RETURN_1 2320804
#define ENPC_ALWAYS_CLOSED_1 2367988
#define ERANGE_ALWAYS_CLOSED_3 2280851
#define POS_ALWAYS_CLOSED_RETURN_3 2320811
#define ENPC_ALWAYS_CLOSED_3 2563491
#define BGM_MUSIC_ZONE_FST_TWN 1003
#define NCUT_FST_1 3
#define NCUT_FST_2 53
#define NCUT_FST_3 226
#define ENPC_QUEST_OFFER 1985150
#define NCUT_LIGHT_ALL 2
#define NCUT_LIGHT_FST_1 147
#define NCUT_LIGHT_FST_2 146

class OpeningGridania : public EventScript
{
public:
   OpeningGridania() : EventScript( "OpeningGridania", 1245186 )
   {}

   void Scene00000( Entity::Player& player )
   {
      auto callback = [ this ]( Entity::Player& player, uint32_t eventId, uint16_t param1, uint16_t param2, uint16_t param3 )
      {
         player.setOpeningSequence( 1 );
         Scene00001( player );
      };

      player.eventPlay( getId(), 0, 0x04AC05, 0, 1, callback );
   }

   void Scene00001( Entity::Player& player )
   {
      player.eventPlay( getId(), 1, 0x2001, 1, 0x32 );
   }

   void Scene00020( Entity::Player& player )
   {
      player.eventPlay( getId(), 20, 0x2001, 0, 1 );
   }

   void Scene00030( Entity::Player& player )
   {
      player.eventPlay( getId(), 30, 0x2001, 0, 0 );
   }

   void Scene00040( Entity::Player& player )
   {
      auto callback = [ this ]( Entity::Player& player, uint32_t eventId, uint16_t param1, uint16_t param2, uint16_t param3 )
      {
         if( player.getOpeningSequence() == 2 )
         {
            // update the instance boundaries
            Scene00030( player );
         }
      };

      player.eventPlay( getId(), 40, 1, 2, 1, callback );
   }

   ///////////////////////////////

   void onEnterZone( Entity::Player& player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {
      if( player.getOpeningSequence() == 0 )
      {
         Scene00000( player );
      }
      else
      {
         Scene00040( player );
      }
   }

   void onWithinRange( Entity::Player& player, uint32_t eventId, uint32_t param1, float x, float y, float z ) override
   {
      if( param1 == ERANGE_SEQ_1_CLOSED_1 || param1 == ERANGE_SEQ_1_CLOSED_2 )
      {
         Scene00020( player );
      }
   }
};

EXPORT_SCRIPTOBJECT( OpeningGridania )