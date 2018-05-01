#include <Script/NativeScriptApi.h>
#include <Actor/Player.h>
#include "Event/EventHelper.h"
#include <ScriptObject.h>

// Quest Script: SubFst004_00027
// Quest Name: Preserving the Past
// Quest ID: 65563
// Start NPC: 1000194
// End NPC: 1000789

class SubFst004 : public EventScript
{
   private:
      // Basic quest information 
      // Quest vars / flags used
      // GetQuestUI8AL
      // GetQuestUI8BH

      // Steps in this quest ( 0 is before accepting, 
      // 1 is first, 255 means ready for turning it in
      enum Sequence : uint8_t
      {
         Seq0 = 0,
         Seq1 = 1,
         SeqFinish = 255,
      };

      // Quest rewards 
      static constexpr auto RewardExpFactor = 50;
      static constexpr auto RewardItem = 5594;
      static constexpr auto RewardItemCount = 10 ;

      // Entities found in the script data of the quest
      static constexpr auto Actor0 = 1000194;
      static constexpr auto Actor1 = 1000686;
      static constexpr auto Actor2 = 1000789;
      static constexpr auto Item0 = 2000024;
      static constexpr auto Seq0Actor0 = 0;
      static constexpr auto Seq1Actor1 = 1;
      static constexpr auto Seq2Actor2 = 2;
      static constexpr auto Seq2Actor2Npctradeno = 99;
      static constexpr auto Seq2Actor2Npctradeok = 100;

   public:
      SubFst004() : EventScript( 65563 )
      { }; 
      ~SubFst004()
      { }; 

   void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
   {
      auto actor = Event::mapEventActorToRealActor( actorId );

      if ( actor == SubFst004::Actor0 )
      {
         Scene00000( player );
      }
      else if ( actor == SubFst004::Actor1 )
      {
         Scene00001( player );
      }
      else if ( actor == SubFst004::Actor2 && player.getQuestUI8AL( m_id ) == 1 )
      {
         Scene00002( player );
      }
   }

   private:

   void checkQuestCompletion( Entity::Player& player, uint32_t varIdx )
   {
      if ( varIdx == 0 )
      {
         player.setQuestUI8AL( m_id, 1 );
         player.sendQuestMessage( m_id, 1, 0, 21002, 0 );
      }
      else if (varIdx == 1)
      {
         player.sendQuestMessage( m_id, 1, 0, 0, 0 );
         player.setQuestUI8BH( m_id, 1 );
         player.setQuestUI8AL( m_id, 0 );
      }
   }

   void Scene00000( Entity::Player& player )
   {
      player.playScene( m_id, 0, 8192,
         [&]( Entity::Player& player, const Event::SceneResult& result )
      {
         if ( result.param2 == 1 ) // accept quest
            player.updateQuest( m_id, 1 );
      } );
   }

   void Scene00001( Entity::Player& player )
   {
      player.playScene( m_id, 1, 8192,
         [&]( Entity::Player& player, const Event::SceneResult& result )
         {
            player.setQuestUI8BH( m_id, 1 );
            checkQuestCompletion( player, 0 );
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
            Scene00002( player );
         } );
   }

   void Scene00100( Entity::Player& player )
   {
      player.playScene( m_id, 100, 8192,
         [&]( Entity::Player& player, const Event::SceneResult& result )
      {
         checkQuestCompletion( player, 1 );

         if ( player.getQuestUI8BH( m_id ) == 1 )
         {
            if ( player.giveQuestRewards( m_id, 0 ) )
            {
               player.finishQuest( m_id );
            }
         }
      } );
   }
};

