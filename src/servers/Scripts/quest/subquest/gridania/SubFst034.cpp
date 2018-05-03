#include <Script/NativeScriptApi.h>
#include <Actor/Player.h>
#include "Event/EventHelper.h"
#include <ScriptObject.h>

// Quest Script: SubFst034_00128
// Quest Name: Eggs over Queasy
// Quest ID: 65664
// Start NPC: 1000421
// End NPC: 1000449

// NEED TO TEST KILLCREDITS

class SubFst034 : public EventScript
{
   private:
      // Basic quest information 
      // Quest vars / flags used
      // GetQuestUI8AL
      // GetQuestUI8BH

      enum Sequence : uint8_t
      {
         Seq0 = 0,
         Seq1 = 1,
         SeqFinish = 255,
      };

      // Quest rewards 
      static constexpr auto RewardExpFactor = 200;
      static constexpr auto RewardGil = 151;
      static constexpr auto RewardItem = 4552;
      static constexpr auto RewardItemCount = 1;

      // Entities found in the script data of the quest
      static constexpr auto Actor0 = 1000421;
      static constexpr auto Actor1 = 1000449;
      static constexpr auto Enemy0 = 43;
      static constexpr auto Item0 = 2000062;
      static constexpr auto Seq0Actor0 = 0;
      static constexpr auto Seq2Actor1 = 1;
      static constexpr auto Seq2Actor1Npctradeno = 99;
      static constexpr auto Seq2Actor1Npctradeok = 100;

   public:
      SubFst034() : EventScript( 65664 )
      { }; 
      ~SubFst034()
      { }; 

   void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
   {
      auto actor = Event::mapEventActorToRealActor( actorId );

      if ( actor == SubFst034::Actor0 )
      {
         Scene00000( player );
      }
      else if ( actor == SubFst034::Actor1 )
      {
         Scene00001( player );
      }
   }

   void onMobKill( Entity::Player& player, uint64_t npcId )
   {
      if ( npcId != Enemy0 )
         return;

      auto currentKC = player.getQuestUI8BH( m_id ) + 1;

      if ( currentKC >= 6 )
         player.updateQuest( m_id, 255 );
      else
      {
         player.setQuestUI8BH( m_id, currentKC );
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
            {  
               player.updateQuest( m_id, 1 );
            }
         } );
   }

   void Scene00001( Entity::Player& player )
   {
      player.playScene( m_id, 1, HIDE_HOTBAR,
         [&]( Entity::Player& player, const Event::SceneResult& result )
         {
            if ( result.param2 == 1 )
            {
               Scene00100( player );
            }
            else
            {
               Scene00099( player );
            }
         } );
   }

   void Scene00099( Entity::Player& player )
   {
      player.playScene( m_id, 99, HIDE_HOTBAR,
         [&]( Entity::Player& player, const Event::SceneResult& result )
         {
            player.playScene( m_id, 99, 0, 0, 0 );
         } );
   }

   void Scene00100( Entity::Player& player )
   {
      player.playScene( m_id, 100, HIDE_HOTBAR,
         [&]( Entity::Player& player, const Event::SceneResult& result )
         {
            if ( result.param2 == 1 )
            {
               player.setQuestUI8BH( m_id, 0 );
               player.setQuestUI8AL( m_id, 1 );

               if ( player.getQuestUI8AL( m_id ) == 1 )
               {
                  if ( player.giveQuestRewards( m_id,0 ) )
                  {
                     player.finishQuest( m_id );
                  }
               }
            }
         } );
   }
};

