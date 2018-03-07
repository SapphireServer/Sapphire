#include <Script/NativeScriptApi.h>
#include <Actor/Player.h>
#include "../ScriptObject.h"
#include "Event/EventHelper.h"

// Quest Script: ManFst001_00039
// Quest Name: Coming to Gridania
// Quest ID: 65575
// Start NPC: 1001148
// End NPC: 1001140

class ManFst001 : public EventScript
{
private:
   static constexpr auto SEQ_0 = 0;
   static constexpr auto SEQ_FINISH = 255;

   static constexpr auto RewardExpFactor = 50;
   static constexpr auto RewardGil = 103;

   static constexpr auto ACTOR0 = 1001148;
   static constexpr auto ACTOR1 = 1001140;
   static constexpr auto CUT_EVENT = 29;
   static constexpr auto EOBJECT0 = 2001659;
   static constexpr auto EOBJECT1 = 2001660;
   static constexpr auto EOBJECT7 = 2616477;
   static constexpr auto EVENT_ACTION_SEARCH = 1;
   static constexpr auto HOWTO_QUEST_ACCEPT = 12;
   static constexpr auto HOWTO_QUEST_ANNOUNCE = 2;
   static constexpr auto HOWTO_REWARD = 11;
   static constexpr auto HOWTO_TODO = 3;
   static constexpr auto OPENING_EVENT_HANDLER = 1245186;
   static constexpr auto SEQ_2_ACTOR1 = 2;

   void Scene00000( Entity::Player& player )
   {
      auto callback = [&]( Entity::Player& player, uint32_t eventId, uint16_t param1, uint16_t param2, uint16_t param3 )
      {
         if( param2 == 1 ) // accept quest
         {
            player.setOpeningSequence( 2 );
            Scene00001( player );
         }
      };

      player.eventPlay( getId(), 0, HIDE_HOTBAR, 0, 0, callback );
   }

   void Scene00001( Entity::Player& player )
   {
      auto callback = [&]( Entity::Player& player, uint32_t eventId, uint16_t param1, uint16_t param2, uint16_t param3 )
      {
         Scene00002( player );
      };

      player.eventPlay( getId(), 1, 0xF8482EFB, 0, 0, callback );
   }

   void Scene00002( Entity::Player& player )
   {
      auto callback = [&]( Entity::Player& player, uint32_t eventId, uint16_t param1, uint16_t param2, uint16_t param3 )
      {
         player.updateQuest( getId(), SEQ_FINISH );

         player.eventPlay( OPENING_EVENT_HANDLER, 0x1E, HIDE_HOTBAR | NO_DEFAULT_CAMERA, 0, 0 );
      };

      player.eventPlay( getId(), 2, 0, 0, 0, callback );
   }

   void Scene00004( Entity::Player& player )
   {
      auto callback = [&]( Entity::Player& player, uint32_t eventId, uint16_t param1, uint16_t param2, uint16_t param3 )
      {
         Scene00005( player );
      };

      player.eventPlay( getId(), 4, 0x2c02, 0, 0, callback );
   }

   void Scene00005( Entity::Player& player )
   {
      auto callback = [&]( Entity::Player& player, uint32_t eventId, uint16_t param1, uint16_t param2, uint16_t param3 )
      {
         if( param2 == 1 )
         {
            if( player.giveQuestRewards( getId(), 0 ) )
               player.finishQuest( getId() );
         }
      };

      player.eventPlay( getId(), 5, INVIS_OTHER_PC, 0, 0, callback );
   }

public:
   ManFst001() : EventScript( 65575 ) {}

   void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
   {
      auto actor = Event::mapEventActorToRealActor( static_cast< uint32_t >( actorId ) );

      if( actor == ACTOR0 )
         Scene00000( player );
      else if( actor == ACTOR1 )
         Scene00004( player );
   }
};