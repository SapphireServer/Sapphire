#include <Actor/Player.h>
#include <Event/EventHelper.h>
#include <ScriptObject.h>

// Quest Script: SubWil025_00671
// Quest Name: Nothing to See Here
// Quest ID: 66207
// Start NPC: 1003995
// End NPC: 1003995

class SubWil025 :
   public EventScript
{
   private:
      // Basic quest information 
      // Quest vars / flags used
      // GetQuestBitFlag8
      // GetQuestUI8AH KC Seq1
      // GetQuestUI8AL Despawn act1 map
      // GetQuestUI8BH Despawn act2 map
      // GetQuestUI8BL Despawn act3 map
      // GetQuestUI8CH Items Seq1
      // GetQuestUI8CL

      enum Sequence :
         uint8_t
      {
         Seq0 = 0,
         Seq1 = 1,
         SeqFinish = 255,
      };

      // Quest rewards 
      static constexpr auto RewardExpFactor = 200;
      static constexpr auto RewardItem = 4551;
      static constexpr auto RewardItemCount = 5;

      // Entities found in the script data of the quest
      static constexpr auto Actor0 = 1003995;
      static constexpr auto Actor1 = 1004599;
      static constexpr auto Actor2 = 1004600;
      static constexpr auto Actor3 = 1004601;
      static constexpr auto Item0 = 2000463;

   public:
      SubWil025() :
         EventScript( 66207 )
      {
      }; 

   void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
   {
      auto actor = Event::mapEventActorToRealActor( static_cast< uint32_t >( actorId ) );

      if( actor == Actor0 && !player.hasQuest( getId() ) )
      {
         Scene00000( player );
      }
      if( actor == Actor0 && player.getQuestSeq( getId() ) == SeqFinish )
      {
         Scene00010( player );
      }
      if( actor == Actor1 && player.getQuestUI8AL( getId() ) != 1 )
      {
         Scene00001( player );
      }
      if (actor == Actor1 && player.getQuestUI8AL( getId() ) == 1 )
      {
         Scene00011( player );
      }
      if( actor == Actor2 && player.getQuestUI8BH( getId() ) != 1 )
      {
         Scene00004( player );
      }
      if( actor == Actor2 && player.getQuestUI8BH( getId() ) == 1 )
      {
         Scene00012( player );
      }
      if( actor == Actor3 && player.getQuestUI8BL( getId() ) != 1 )
      {
         Scene00007( player );
      }
      if( actor == Actor3 && player.getQuestUI8BL( getId() ) == 1 )
      {
         Scene00013( player );
      }
   }

   private:

    void checkQuestCompletion( Entity::Player& player )
    {
       auto currentQC = player.getQuestUI8AH( getId() ) + 1;
       auto currentIC = player.getQuestUI8CH( getId() ) - 1;

       if( currentQC >= 3 )
       {
          player.updateQuest( getId(), SeqFinish );
          player.sendQuestMessage( getId(), 1, 2, 0, 0 );
       }
       else
       {
          player.setQuestUI8AH( getId(), currentQC );
          player.sendQuestMessage( getId(), 0, 2, currentQC, 3 );
          player.setQuestUI8CH( getId(), currentIC );
       }
    }

   void Scene00000( Entity::Player& player )
   {
      player.playScene( getId(), 0, HIDE_HOTBAR,
                       [ & ]( Entity::Player& player, const Event::SceneResult& result )
                       {
                          if( result.param2 == 1 )
                          {
                             player.updateQuest( getId(), Seq1 );
                             player.setQuestUI8CH( getId(), 3 );
                          }
                       } );
   }

   void Scene00001( Entity::Player& player )
   {
      player.playScene( getId(), 1, HIDE_HOTBAR,
                         [ & ]( Entity::Player& player, const Event::SceneResult& result )
                         {
                           if( result.param2 == 1 )
                           {
                              Scene00002( player );
                           }
                           else
                           {
                              Scene00003( player );
                           }
                         } );
   }

   void Scene00002( Entity::Player& player )
   {
      player.playScene( getId(), 2, HIDE_HOTBAR,
                         [ & ]( Entity::Player& player, const Event::SceneResult& result )
                         {
                           player.setQuestUI8AL( getId(), 1 );
                           checkQuestCompletion( player );
                           player.setQuestBitFlag8( getId(), 7, true );
                         } );
   }

   void Scene00003( Entity::Player& player )
   {
      player.playScene( getId(), 3, HIDE_HOTBAR,
                         [ & ]( Entity::Player& player, const Event::SceneResult& result )
                         {
                         } );
   }

   void Scene00004( Entity::Player& player )
   {
      player.playScene( getId(), 4, HIDE_HOTBAR,
                         [ & ]( Entity::Player& player, const Event::SceneResult& result )
                         {
                           if( result.param2 == 1 )
                           {
                              Scene00005( player );
                           }
                           else
                           {
                              Scene00006( player );
                           }
                         } );
   }

   void Scene00005( Entity::Player& player )
   {
      player.playScene( getId(), 5, HIDE_HOTBAR,
                         [ & ]( Entity::Player& player, const Event::SceneResult& result )
                         {
                           player.setQuestUI8BH( getId(), 1 );
                           checkQuestCompletion( player );
                           player.setQuestBitFlag8( getId(), 6, true );
                         } );
   }

   void Scene00006( Entity::Player& player )
   {
      player.playScene( getId(), 6, HIDE_HOTBAR,
                         [ & ]( Entity::Player& player, const Event::SceneResult& result )
                         {
                         } );
   }

   void Scene00007( Entity::Player& player )
   {
      player.playScene( getId(), 7, HIDE_HOTBAR,
                         [ & ]( Entity::Player& player, const Event::SceneResult& result )
                         {
                           if( result.param2 == 1 )
                           {
                              Scene00008( player );
                           }
                           else
                           {
                              Scene00009( player );
                           }
                         } );
   }

   void Scene00008( Entity::Player& player )
   {
      player.playScene( getId(), 8, HIDE_HOTBAR,
                         [ & ]( Entity::Player& player, const Event::SceneResult& result )
                         {
                           player.setQuestUI8BL( getId(), 1 );
                           checkQuestCompletion( player );
                           player.setQuestBitFlag8( getId(), 5, true );
                         } );
   }

   void Scene00009( Entity::Player& player )
   {
      player.playScene( getId(), 9, HIDE_HOTBAR,
                         [ & ]( Entity::Player& player, const Event::SceneResult& result )
                         {
                         } );
   }

   void Scene00010( Entity::Player& player )
   {
      player.playScene( getId(), 10, HIDE_HOTBAR,
                         [ & ]( Entity::Player& player, const Event::SceneResult& result )
                         {
                           if( result.param2 == 1 )
                           {
                              if( player.giveQuestRewards( getId(), 0 ) )
                              {
                                 player.finishQuest( getId() );
                              }
                           }
                         } );
   }

   void Scene00011( Entity::Player& player )
   {
      player.playScene( getId(), 11, HIDE_HOTBAR,
                         [ & ]( Entity::Player& player, const Event::SceneResult& result )
                         {
                         } );
   }

   void Scene00012( Entity::Player& player )
   {
      player.playScene( getId(), 12, HIDE_HOTBAR,
                         [ & ]( Entity::Player& player, const Event::SceneResult& result )
                         {
                         } );
   }

   void Scene00013( Entity::Player& player )
   {
      player.playScene( getId(), 13, HIDE_HOTBAR,
                         [ & ]( Entity::Player& player, const Event::SceneResult& result )
                         {
                         } );
   }
};

