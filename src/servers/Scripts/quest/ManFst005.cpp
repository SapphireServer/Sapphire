#include <Script/NativeScriptApi.h>
#include <Actor/Player.h>
#include "Event/EventHelper.h"
#include <ScriptObject.h>

// Quest Script: ManFst005_00445
// Quest Name: Chasing Shadows
// Quest ID: 65981
// Start NPC: 1000421
// End NPC: 1000421

class ManFst005 : public EventScript
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
         Seq2 = 2,
         Seq3 = 3,
         SeqFinish = 255,
      };

      // Quest rewards 
      static constexpr auto RewardExpFactor = 200;
      static constexpr auto RewardGil = 132;

      // Entities found in the script data of the quest
      static constexpr auto Actor0 = 1000421;
      static constexpr auto CutScene02 = 55;
      static constexpr auto CutScene03 = 56;
      static constexpr auto CutScene04 = 57;
      static constexpr auto Eobject0 = 2000953;
      static constexpr auto Eobject1 = 2001194;
      static constexpr auto EventActionProcessShor = 15;
      static constexpr auto Item0 = 2000229;
      static constexpr auto Questbattle0 = 11;
      static constexpr auto Seq0Actor0Lq = 90;
      static constexpr auto Territorytype0 = 233;
      static constexpr auto Territorytype1 = 148;

      static constexpr auto ManFst005QB = 2147876875;

   public:
      ManFst005() : EventScript( 65981 )
      {}; 
      ~ManFst005()
      {}; 

   void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
   {
      auto actor = Event::mapEventActorToRealActor( actorId );

      if(  actor == Actor0 && !player.hasQuest( getId() ) )
      {
         Scene00000( player );
      }
      else if(  actor == Actor0 )
      {
         Scene00009( player );
      }
      // EOBJECTS
      else if( actor == Eobject0 )
      {
         player.eventActionStart( getId(), 0x0F,
            [&]( Entity::Player& player, uint32_t eventId, uint64_t additional )
         {
            Scene00002( player );
         },
            [&]( Entity::Player& player, uint32_t eventId, uint64_t additional )
         {},
            eventId );
      }
      else if( actor == Eobject1 )
      {
         player.eventActionStart( getId(), 0x0F,
            [&]( Entity::Player& player, uint32_t eventId, uint64_t additional )
         {
            Scene00006( player );
         },
            [&]( Entity::Player& player, uint32_t eventId, uint64_t additional )
         {},
            eventId );
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
               Scene00001( player );
            }
         } );
   }

   void Scene00001( Entity::Player& player )
   {
      player.playScene( getId(), 1, SET_EOBJ_BASE | HIDE_HOTBAR | INVIS_EOBJ,
         [&]( Entity::Player& player, const Event::SceneResult& result )
         {
            player.updateQuest( getId(), 1 );
         } );
   }

   void Scene00002( Entity::Player& player )
   {
      player.playScene( getId(), 2, HIDE_HOTBAR,
         [&]( Entity::Player& player, const Event::SceneResult& result )
         {
            Scene00003( player );
         } );
   }

   void Scene00003( Entity::Player& player )
   {
      player.playScene( getId(), 3, HIDE_HOTBAR,
         [&]( Entity::Player& player, const Event::SceneResult& result )
         {
            if( result.param2 == 1)
            {
               player.updateQuest( getId(), 3 );
               player.sendNotice("QuestBattle actually disabled, goat said it...it's not my fault!" );
            }
         } );
   }

   void Scene00004( Entity::Player& player )
   {
      player.playScene( getId(), 4, HIDE_HOTBAR,
         [&]( Entity::Player& player, const Event::SceneResult& result )
         {
         } );
   }

   void Scene00005( Entity::Player& player )
   {
      player.playScene( getId(), 5, HIDE_HOTBAR,
         [&]( Entity::Player& player, const Event::SceneResult& result )
         {
            player.updateQuest( getId(), 3 );
         } );
   }

   void Scene00006( Entity::Player& player )
   {
      player.playScene( getId(), 6, HIDE_HOTBAR,
         [&]( Entity::Player& player, const Event::SceneResult& result )
         {
            Scene00007( player );
         } );
   }

   void Scene00007( Entity::Player& player )
   {
      player.playScene( getId(), 7, HIDE_HOTBAR,
         [&]( Entity::Player& player, const Event::SceneResult& result )
         {
            player.sendQuestMessage( getId(), 2, 1, 30426, 3750473944 );
            player.setQuestUI8BH( getId(), 1 );
            player.updateQuest( getId(), 255 );
         } );
   }

   void Scene00008( Entity::Player& player )
   {
      player.playScene( getId(), 8, HIDE_HOTBAR,
         [&]( Entity::Player& player, const Event::SceneResult& result )
         {
         } );
   }

   void Scene00009( Entity::Player& player )
   {
      player.playScene( getId(), 9, HIDE_HOTBAR,
         [&]( Entity::Player& player, const Event::SceneResult& result )
         {
            if( result.param2 == 1 )
            {
               Scene00010( player );
            }
         } );
   }

   void Scene00010( Entity::Player& player )
   {
      player.playScene( getId(), 10, SET_EOBJ_BASE | HIDE_HOTBAR | INVIS_EOBJ,
         [&]( Entity::Player& player, const Event::SceneResult& result )
         {
            if( player.giveQuestRewards( getId(), 0 ) )
            {
               player.finishQuest( getId() );
            }
         } );
   }

   void Scene00011( Entity::Player& player )
   {
      player.playScene( getId(), 11, HIDE_HOTBAR,
         [&]( Entity::Player& player, const Event::SceneResult& result )
         {
         } );
   }
};