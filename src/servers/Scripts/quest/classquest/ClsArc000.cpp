#include <Actor/Player.h>
#include <Event/EventHelper.h>
#include <ScriptObject.h>

// Quest Script: ClsArc000_00021
// Quest Name: Way of the Archer
// Quest ID: 65557
// Start NPC: 1000197
// End NPC: 1000200

class ClsArc000 : public EventScript
{
   private:
      // Basic quest information 
      // Quest vars / flags used
      // GetQuestUI8AL
      // GetQuestUI8BH
      // GetQuestUI8BL

      // Steps in this quest ( 0 is before accepting, 
      // 1 is first, 255 means ready for turning it in
      enum Sequence : uint8_t
      {
         Seq0 = 0,
         Seq1 = 1,
         Seq2 = 2,
         SeqFinish = 255,
      };

      // Quest rewards 
      static constexpr auto RewardExpFactor = 100;
      static constexpr auto RewardItem = 4657;
      static constexpr auto RewardItemCount = 5;

      // Entities found in the script data of the quest
      static constexpr auto Actor0 = 1000197;
      static constexpr auto Actor1 = 1000200;
      static constexpr auto Enemy0 = 37;
      static constexpr auto Enemy1 = 49;
      static constexpr auto Enemy2 = 47;
      static constexpr auto LocFace0 = 604;
      static constexpr auto LocFace1 = 605;
      static constexpr auto LogmessageMonsterNotePageUnlock = 1008;
      static constexpr auto Seq0Actor0 = 0;
      static constexpr auto Seq1Actor1 = 1;
      static constexpr auto Seq3Actor1 = 2;
      static constexpr auto UnlockImageMonsterNote = 32;

   public:
      ClsArc000() : EventScript( 65557 )
      {}; 
      ~ClsArc000()
      {}; 

   void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
   {
      auto actor = Event::mapEventActorToRealActor( actorId );

      if( actor == Actor0 )
      {
         Scene00000( player );
      }
      else if( actor == Actor1 && player.getQuestSeq( getId() ) == 1 )
      {
         Scene00001( player );
      }
      else if( actor == Actor1 && player.getQuestSeq( getId() ) == SeqFinish )
      {
         Scene00002( player );
      }
   }

   void onMobKill( Entity::Player& player, uint64_t npcId )
   {
      if( npcId != Enemy0 || Enemy1 || Enemy2 )
         return;

      auto currentKC37 = player.getQuestUI8AL( getId() ) + 1;
      auto currentKC49 = player.getQuestUI8BH( getId() ) + 1;
      auto currentKC47 = player.getQuestUI8BL( getId() ) + 1;

      if( currentKC37 >= 6 )
      {
         checkQuestCompletion( player, 3 );
      }
      else if( currentKC49 >= 6 )
      {
         checkQuestCompletion( player, 2 );
      }
      else if( currentKC47 >= 6 )
      {
         checkQuestCompletion( player, 0 );
      }

      else if( currentKC37 < 6 )
      {
         player.setQuestUI8AL( getId() , currentKC37 );
         player.sendQuestMessage( getId() , 0, 2, currentKC37, 6 );
      }
      else if( currentKC49 < 6 )
      {
         player.setQuestUI8BH( getId() , currentKC49 );
         player.sendQuestMessage( getId() , 0, 2, currentKC49, 6 );
      }
      else if( currentKC47 < 6 )
      {
         player.setQuestUI8BL( getId() , currentKC47 );
         player.sendQuestMessage( getId() , 0, 2, currentKC47, 6 );
      }
   }

   private:

   void checkQuestCompletion( Entity::Player& player, uint32_t varIdx )
   {
      if( varIdx == 3 )
      {
         player.sendQuestMessage( getId(), 2, 0, 0, 0 );
      }
      else if( varIdx == 2 )
      {
         player.sendQuestMessage( getId(), 3, 0, 0, 0 );
      }
      else
      {
         player.sendQuestMessage( getId(), 1, 0, 0, 0 );
      }

      auto questId = getId();

      auto QUEST_ONKILL_37 = player.getQuestUI8AL( questId );
      auto QUEST_ONKILL_49 = player.getQuestUI8BH( questId );
      auto QUEST_ONKILL_47 = player.getQuestUI8BL( questId );

      if( QUEST_ONKILL_37 == 1 && QUEST_ONKILL_49 == 1 && QUEST_ONKILL_47 == 1 )
      {
         player.updateQuest( questId, SeqFinish );
      }
   }

   void Scene00000( Entity::Player& player )
   {
      player.playScene( getId() , 0, HIDE_HOTBAR,
         [&]( Entity::Player& player, const Event::SceneResult& result )
         {
            if( result.param2 == 1 )
               player.updateQuest( getId() , 1 );
         } );
   }

   void Scene00001( Entity::Player& player )
   {
      player.playScene( getId() , 1, SET_EOBJ_BASE | HIDE_HOTBAR | INVIS_EOBJ,
         [&]( Entity::Player& player, const Event::SceneResult& result )
         {
            if( result.param2 == 1 )
            {
               player.sendQuestMessage( getId(), 0, 0, 0, 0 );
               player.updateQuest( getId(), 2 );
            }
         } );
   }

   void Scene00002( Entity::Player& player )
   {
      player.playScene( getId() , 2, HIDE_HOTBAR,
         [&]( Entity::Player& player, const Event::SceneResult& result )
         {
            if( result.param2 == 1 )
            {
               if( player.giveQuestRewards( getId(), 0 ) )
               {
                  player.learnAction( 21 );
                  player.finishQuest( getId() );
               }
            }
         } );
   }
};

