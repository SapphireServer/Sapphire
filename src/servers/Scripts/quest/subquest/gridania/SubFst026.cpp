#include <Script/NativeScriptApi.h>
#include <Actor/Player.h>
#include "Event/EventHelper.h"
#include <ScriptObject.h>

// Quest Script: SubFst026_00170
// Quest Name: Jumping at Shadows
// Quest ID: 65706
// Start NPC: 1000629
// End NPC: 1000629

//NEED TEST KILLCREDIT

class SubFst026 : public EventScript
{
   private:
      // Basic quest information 
      // Quest vars / flags used
      // GetQuestUI8AL

      enum Sequence : uint8_t
      {
         Seq0 = 0,
         Seq1 = 1,
         SeqFinish = 255,
      };

      // Quest rewards 
      static constexpr auto RewardExpFactor = 100;
      static constexpr auto RewardGil = 135;

      // Entities found in the script data of the quest
      static constexpr auto Actor0 = 1000629;
      static constexpr auto Enemy0 = 9;
      static constexpr auto Seq0Actor0 = 0;
      static constexpr auto Seq2Actor0 = 1;

   public:
      SubFst026() : EventScript( 65706 )
      { }; 
      ~SubFst026()
      { }; 

   void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
   {
      auto actor = Event::mapEventActorToRealActor( actorId );
   }

   void onMobKill( Entity::Player& player, uint64_t npcId )
   {
      if (npcId != Enemy0)
         return;

      auto currentKC = player.getQuestUI8AL( m_id ) + 1;

      if ( currentKC >= 6 )
         player.updateQuest( m_id, 255 );
      else
      {
         player.setQuestUI8AL( m_id, currentKC );
         player.sendQuestMessage( m_id, 0, 2, currentKC, 6 );
      }
   }

   private:

   void Scene00000( Entity::Player& player )
   {
      player.playScene( m_id, 0, 0,
         [&]( Entity::Player& player, const Event::SceneResult& result )
         {
            if ( result.param2 == 1 )
               player.updateQuest( m_id, 1 );
         } );
   }

   void Scene00001( Entity::Player& player )
   {
      player.playScene( m_id, 1, 0,
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

