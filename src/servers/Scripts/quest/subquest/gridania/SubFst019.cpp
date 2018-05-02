#include <Script/NativeScriptApi.h>
#include <Actor/Player.h>
#include "Event/EventHelper.h"
#include <ScriptObject.h>

// Quest Script: SubFst019_00049
// Quest Name: I Am Millicent, Hear Me Roar
// Quest ID: 65585
// Start NPC: 1000788
// End NPC: 1000429

class SubFst019 : public EventScript
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
      static constexpr auto RewardExpFactor = 50;
      static constexpr auto RewardItem = 4551;
      static constexpr auto RewardItemCount = 5;

      // Entities found in the script data of the quest
      static constexpr auto Actor0 = 1000788;
      static constexpr auto Actor1 = 1000429;
      static constexpr auto Seq0Actor0 = 0;
      static constexpr auto Seq1Actor1 = 1;

   public:
      SubFst019() : EventScript( 65585 )
      { }; 
      ~SubFst019()
      { }; 

   void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
   {
      auto actor = Event::mapEventActorToRealActor( actorId );

      if ( actor == SubFst019::Actor0 )
      {
         Scene00000( player );
      }
      else if ( actor == SubFst019::Actor1 )
      {
         Scene00001( player );
      }
   }

   private:

   void Scene00000( Entity::Player& player )
   {
      player.playScene( m_id, 0, 8192,
         [&]( Entity::Player& player, const Event::SceneResult& result )
         {
            if ( result.param2 == 1 )
            {
               player.updateQuest( m_id, 255 );
            }
         } );
   }

   void Scene00001( Entity::Player& player )
   {
      player.playScene( m_id, 1, 8192,
         [&]( Entity::Player& player, const Event::SceneResult& result )
         {
            if ( result.param2 == 1 )
            {
               if ( player.giveQuestRewards( m_id, 0 ) )
                  player.finishQuest( m_id );
            }
         } );
   }

};

