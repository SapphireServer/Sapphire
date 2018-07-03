#include <Script/NativeScriptApi.h>
#include <Actor/Player.h>
#include "Event/EventHelper.h"
#include <ScriptObject.h>

// Quest Script: SubFst045_00201
// Quest Name: Passing Muster
// Quest ID: 65737
// Start NPC: 1000421
// End NPC: 1000421

class SubFst045 : public EventScript
{
   private:
      // Basic quest information 
      // Quest vars / flags used
      // GetQuestUI8AL

      enum Sequence : uint8_t
      {
         Seq0 = 0,
         SeqFinish = 255,
      };

      // Quest rewards 
      static constexpr auto RewardExpFactor = 200;
      static constexpr auto RewardGil = 128;

      // Entities found in the script data of the quest
      static constexpr auto Actor0 = 1000421;
      static constexpr auto Seq0Actor0 = 0;
      static constexpr auto Seq1Actor0 = 1;

   public:
      SubFst045() : EventScript( 65737 ){}; 
      ~SubFst045(){}; 

   void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
   {
      auto actor = Event::mapEventActorToRealActor( actorId );

      if ( actor == Actor0 && !player.hasQuest( getId() ) )
      {
         Scene00000( player );
      }
      else
      {
         Scene00001( player );
      }
   }

   private:

   void Scene00000( Entity::Player& player )
   {
      player.playScene( getId(), 0, HIDE_HOTBAR,
         [&]( Entity::Player& player, const Event::SceneResult& result )
         {
            if( result.param2 == 1 )
               {
                  player.updateQuest( getId(), 255 );
               }
         } );
   }

   void Scene00001( Entity::Player& player )
   {
      player.playScene( getId(), 1, HIDE_HOTBAR,
         [&]( Entity::Player& player, const Event::SceneResult& result )
         {
            if( result.param2 == 1 )
            {
               if( player.giveQuestRewards( getId(), 0 ) )
               {
                  player.finishQuest( getId() );
               }
            }
         } );
   }
};

