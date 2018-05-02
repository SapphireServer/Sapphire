#include <Script/NativeScriptApi.h>
#include <Actor/Player.h>
#include "Event/EventHelper.h"
#include <ScriptObject.h>

// Quest Script: SubFst008_00032
// Quest Name: A Hard Nut to Crack
// Quest ID: 65568
// Start NPC: 1000372
// End NPC: 1000629

class SubFst008 : public EventScript
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
      uint32_t RewardItemOptional[3] = { 2999, 3010, 5824 };
      uint32_t RewardItemOptionalCount[3] = { 1, 1, 1 };

      // Entities found in the script data of the quest
      static constexpr auto Actor0 = 1000372;
      static constexpr auto Actor1 = 1000311;
      static constexpr auto Actor2 = 1000629;
      static constexpr auto Item0 = 2000029;
      static constexpr auto Seq0Actor0 = 0;
      static constexpr auto Seq1Actor1 = 1;
      static constexpr auto Seq2Actor2 = 2;
      static constexpr auto Seq2Actor2Npctradeno = 99;
      static constexpr auto Seq2Actor2Npctradeok = 100;

   public:
      SubFst008() : EventScript( 65568 )
      { }; 
      ~SubFst008()
      { }; 

   void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
   {
      auto actor = Event::mapEventActorToRealActor( actorId );

      if ( actor == SubFst008::Actor0 )
      {
         Scene00000( player );
      }
      else if ( actor == SubFst008::Actor1 )
      {
         Scene00001( player );
      }
      else if ( Actor2 == SubFst008::Actor2 )
      {
         Scene00002( player );
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
                  player.updateQuest( m_id, 1 );
               }
         } );
   }

   void Scene00001( Entity::Player& player )
   {
      player.playScene( m_id, 1, 8192,
         [&]( Entity::Player& player, const Event::SceneResult& result )
         {
            player.setQuestUI8BH( m_id, 1 );
            player.updateQuest( m_id, 255 );
         } );
   }

   void Scene00002( Entity::Player& player )
   {
      player.playScene( m_id, 2, 8192,
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
      player.playScene( m_id, 99, 8192,
         [&]( Entity::Player& player, const Event::SceneResult& result )
         {
         player.playScene( m_id, 99, 0, 0, 0 );
         } );
   }

   void Scene00100( Entity::Player& player )
   {
      player.playScene( m_id, 100, 8192,
         [&]( Entity::Player& player, const Event::SceneResult& result )
         {
            player.sendQuestMessage( m_id, 1, 0, 0, 0 );
            player.setQuestUI8BH( m_id, 0 );
            player.setQuestUI8AL( m_id, 1 );

            if ( player.getQuestUI8AL( m_id ) == 1 )
               { 
                  if ( player.giveQuestRewards( m_id, 0 ) )
                     player.finishQuest( m_id );
               }
         } );
   }

};

