#include <Script/NativeScriptApi.h>
#include <Actor/Player.h>
#include "Event/EventHelper.h"
#include <ScriptObject.h>

// Quest Script: SubFst042_00198
// Quest Name: Butcher of Greentear
// Quest ID: 65734
// Start NPC: 1000685
// End NPC: 1000685

//NEED TEST KILLCREDIT

class SubFst042 : public EventScript
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
      static constexpr auto RewardExpFactor = 200;
      uint32_t RewardItemOptional[3] = { 4092, 4091, 5824 };
      uint32_t RewardItemOptionalCount[3] = { 1, 1, 1 };

      // Entities found in the script data of the quest
      static constexpr auto Actor0 = 1000685;
      static constexpr auto Enemy0 = 14;
      static constexpr auto Seq0Actor0 = 0;
      static constexpr auto Seq2Actor0 = 1;

   public:
      SubFst042() : EventScript( 65734 )
      { }; 
      ~SubFst042()
      { }; 

   void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
   {
      auto actor = Event::mapEventActorToRealActor( actorId );

      if ( actor == SubFst042::Actor0 && !player.hasQuest( m_id ) )
      {
         Scene00000( player );
      }
      else if ( actor == SubFst042::Actor0 && player.getQuestSeq( m_id ) == SeqFinish )
      {
         Scene00001( player );
      }
   }

   void onMobKill( Entity::Player& player, uint64_t npcId )
   {
      if ( npcId != Enemy0 )
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
      player.playScene( m_id, 0, HIDE_HOTBAR,
         [&]( Entity::Player& player, const Event::SceneResult& result )
         {
            if ( result.param2 == 1 )
               player.updateQuest( m_id, 1 );
         } );
   }

   void Scene00001( Entity::Player& player )
   {
      player.playScene( m_id, 0, HIDE_HOTBAR,
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

