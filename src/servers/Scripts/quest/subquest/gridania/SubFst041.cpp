#include <Script/NativeScriptApi.h>
#include <Actor/Player.h>
#include "Event/EventHelper.h"
#include <ScriptObject.h>

// Quest Script: SubFst041_00197
// Quest Name: Splitting Shells
// Quest ID: 65733
// Start NPC: 1000432
// End NPC: 1000411

//NEED TEST KILLCREDIT

class SubFst041 : public EventScript
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
      static constexpr auto RewardExpFactor = 100;
      uint32_t RewardItemOptional[3] = { 4657, 4658, 5823 };
      uint32_t RewardItemOptionalCount[3] = { 3, 3, 3 };

      // Entities found in the script data of the quest
      static constexpr auto Actor0 = 1000432;
      static constexpr auto Actor1 = 1000411;
      static constexpr auto Enemy0 = 159;
      static constexpr auto Item0 = 2000142;
      static constexpr auto Seq0Actor0 = 0;
      static constexpr auto Seq2Actor1 = 1;
      static constexpr auto Seq2Actor1Npctradeno = 99;
      static constexpr auto Seq2Actor1Npctradeok = 100;

   public:
      SubFst041() : EventScript( 65733 )
      { }; 
      ~SubFst041()
      { }; 

   void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
   {
      auto actor = Event::mapEventActorToRealActor( actorId );

      if ( actor == SubFst041::Actor0 )
      {
         Scene00000( player );
      }
      if ( actor == SubFst041::Actor1 )
      {
         Scene00001(player);
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
      player.playScene( m_id, 0, 0,
         [&]( Entity::Player& player, const Event::SceneResult& result )
         {

         } );
   }

   void Scene00001( Entity::Player& player )
   {
      player.playScene( m_id, 1, 0,
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
      player.playScene( m_id, 99, 0,
         [&]( Entity::Player& player, const Event::SceneResult& result )
         {
            player.playScene( m_id, 99, 0, 0, 0 );
         } );
   }

   void Scene00100( Entity::Player& player )
   {
      player.playScene( m_id, 100, 0,
         [&]( Entity::Player& player, const Event::SceneResult& result )
         {
            player.sendQuestMessage( m_id, 1, 0, 0, 0 );
            player.setQuestUI8BH( m_id, 0 );
            player.setQuestUI8AL( m_id, 1 );

            if ( player.getQuestUI8AL( m_id ) == 1 )
            {
               if ( player.giveQuestRewards( m_id, 0 ) )
               {
                  player.finishQuest( m_id );
               }
            }
         } );
   }

};

