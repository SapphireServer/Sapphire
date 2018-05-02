#include <Script/NativeScriptApi.h>
#include <Actor/Player.h>
#include "Event/EventHelper.h"
#include <ScriptObject.h>

// Quest Script: SubFst011_00037
// Quest Name: Population Control
// Quest ID: 65573
// Start NPC: 1000195
// End NPC: 1000195

//NEED TEST KILLCREDIT

class SubFst011 : public EventScript
{
private:
   // GetQuestUI8AL

   enum Sequence : uint8_t
   {
      Seq0 = 0,
      Seq1 = 1,
      SeqFinish = 255,
   };

   // Quest rewards 
   static constexpr auto RewardExpFactor = 100;
   uint32_t RewardItemOptional[3] = { 2653, 2655, 5823 };
   uint32_t RewardItemCount[3] = { 1, 1, 3 };

   static constexpr auto Actor0 = 1000195;
   static constexpr auto Enemy0 = 47;
   static constexpr auto Seq0Actor0 = 0;
   static constexpr auto Seq2Actor0 = 1;

public:
   SubFst011() : EventScript( 65573 ) 
   { };
   ~SubFst011() 
   { };

   void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
   {
      auto actor = Event::mapEventActorToRealActor( actorId );

      if ( actor == SubFst011::Actor0 && !player.hasQuest( m_id ) )
      {
         Scene00000( player );
      }
      else if ( actor == SubFst011::Actor0 && player.getQuestSeq( m_id ) == SeqFinish )
      {
         Scene00001( player );
      }
   }

   void onMobKill( Entity::Player& player, uint64_t npcId)
   {
      if ( npcId != Enemy0 )
         return;

      auto currentKC = player.getQuestUI8AL( m_id ) + 1;

      if ( currentKC >= 6 )
         player.updateQuest(getId(), 255);
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
         if ( result.param2 == 1 ) // accept quest
            player.updateQuest( m_id, 1 );
      } );
   }

   void Scene00001( Entity::Player& player )
   {
      player.playScene( m_id, 1, 0,
         [&]( Entity::Player& player, const Event::SceneResult& result )
      {
         if ( result.param2 == 1 ) // finish quest
         {
            if ( player.giveQuestRewards( m_id, 0 ) )
               player.finishQuest( m_id );
         }
      } );
   };
};