#include <Actor/Player.h>
#include <Manager/EventMgr.h>
#include <ScriptObject.h>
#include <ctime>
#include "Framework.h"

using namespace Sapphire;

// Quest Script: SubWil020_00393
// Quest Name: Vox Populi
// Quest ID: 65929
// Start NPC: 1001685
// End NPC: 1001945

class SubWil020 : public Sapphire::ScriptAPI::EventScript
{
   private:
      // Basic quest information 
      // Quest vars / flags used
      // GetQuestBitFlag8
      // GetQuestUI8AH
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
      static constexpr auto RewardExpFactor = 55;
      static constexpr auto RewardGil = 109;

      // Entities found in the script data of the quest
      static constexpr auto Actor0 = 1001685;
      static constexpr auto Actor1 = 1001940;
      static constexpr auto Actor2 = 1001937;
      static constexpr auto Actor3 = 1001939;
      static constexpr auto Actor4 = 1001942;
      static constexpr auto Actor5 = 1001949;
      static constexpr auto Actor6 = 1003902;
      static constexpr auto Actor7 = 1001914;
      static constexpr auto Actor8 = 1003899;
      static constexpr auto Actor9 = 1001945;

   public:
      SubWil020() : EventScript( 65929 ) {};
      ~SubWil020() {};

      void checkQuestProgression( Entity::Player& player )
      {
        if( player.getQuestUI8AL( getId() ) == 6 && player.getQuestUI8BH( getId() ) == 2 )
        {
          player.updateQuest( getId(), SeqFinish );
        }
      }

   //////////////////////////////////////////////////////////////////////
   // Event Handlers
   void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
   {
     auto pEventMgr = m_framework->get< World::Manager::EventMgr >();
     auto actor = pEventMgr->mapEventActorToRealActor( static_cast< uint32_t >( actorId ) );

     /*player.setQuestUI8BH( getId(), 0 );
     player.setQuestUI8AL( getId(), 0 );
     player.setQuestBitFlag8( getId(), 0, false );
     player.setQuestBitFlag8( getId(), 1, false );
     player.setQuestBitFlag8( getId(), 2, false );
     player.setQuestBitFlag8( getId(), 3, false );
     player.setQuestBitFlag8( getId(), 4, false );
     player.setQuestBitFlag8( getId(), 5, false );
     player.setQuestBitFlag8( getId(), 6, false );
     player.setQuestBitFlag8( getId(), 7, false );
     player.setQuestBitFlag8( getId(), 8, false );*/

     if( actor == Actor0 )
     {
       Scene00000( player );
     }
     else if( actor == Actor1 )
     {
       if( !player.getQuestBitFlag8( getId(), 1 ) )
         Scene00001( player );
       else
         Scene00002( player );
     }
     else if( actor == Actor2 )
     {
       if( !player.getQuestBitFlag8( getId(), 2 ) )
         Scene00002( player );
       else
         Scene00003( player );
     }
     else if( actor == Actor3 )
     {
       if( !player.getQuestBitFlag8( getId(), 3 ) )
         Scene00005( player );
       else
         Scene00006( player );
     }
     else if( actor == Actor4 )
     {
       if( !player.getQuestBitFlag8( getId(), 4 ) )
         Scene00007( player );
       else
         Scene00008( player );
     }
     else if( actor == Actor5 )
     {
       if( !player.getQuestBitFlag8( getId(), 5 ) )
         Scene00009( player );
       else
         Scene00010( player );
     }
     else if( actor == Actor6 )
     {
       if( !player.getQuestBitFlag8( getId(), 6 ) )
         Scene00011( player );
       else
         Scene00012( player );
     }
     else if( actor == Actor7 )
     {
       if( !player.getQuestBitFlag8( getId(), 7 ) )
         Scene00013( player );
       else
         Scene00014( player );
     }
     else if( actor == Actor8 )
     {
       if( !player.getQuestBitFlag8( getId(), 0 ) )
         Scene00015( player );
       else
         Scene00016( player );
     }
     else if( actor == Actor9 )
     {
       Scene00017( player );
     }
   }

   private:
   //////////////////////////////////////////////////////////////////////
   // Available Scenes in this quest, not necessarly all are used
   void Scene00000( Entity::Player& player )
   {
      player.playScene( getId(), 0, NONE,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {
                          if( result.param2 == 1 )
                          {
                            player.updateQuest( getId(), Seq1 );
                          }
                        } );
   }

   void Scene00001( Entity::Player& player )
   {
      player.playScene( getId(), 1, NONE,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {
                          auto hustCount = player.getQuestUI8AL( getId() );
                          hustCount += 1;
                          player.setQuestUI8AL( getId(), hustCount );
                          player.sendQuestMessage( getId(), 0, 2, hustCount, 6 );
                          player.setQuestBitFlag8( getId(), 1, true );
                          checkQuestProgression( player );
                        } );
   }

   void Scene00002( Entity::Player& player )
   {
      player.playScene( getId(), 2, NONE,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {
                          auto hustCount = player.getQuestUI8AL( getId() );
                          hustCount += 1;
                          player.setQuestUI8AL( getId(), hustCount );
                          player.sendQuestMessage( getId(), 0, 2, hustCount, 6 );
                          player.setQuestBitFlag8( getId(), 2, true );
                          checkQuestProgression( player );
                        } );
   }

   void Scene00003( Entity::Player& player )
   {
      player.playScene( getId(), 3, NONE,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {
                          auto hustCount = player.getQuestUI8AL( getId() );
                          hustCount += 1;
                          player.setQuestUI8AL( getId(), hustCount );
                          player.sendQuestMessage( getId(), 0, 2, hustCount, 6 );
                          player.setQuestBitFlag8( getId(), 3, true );
                          checkQuestProgression( player );
                        } );
   }

   void Scene00004( Entity::Player& player )
   {
      player.playScene( getId(), 4, NONE,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {
                          auto hustCount = player.getQuestUI8AL( getId() );
                          hustCount += 1;
                          player.setQuestUI8AL( getId(), hustCount );
                          player.sendQuestMessage( getId(), 0, 2, hustCount, 6 );
                          player.setQuestBitFlag8( getId(), 4, true );
                          checkQuestProgression( player );
                        } );
   }

   void Scene00005( Entity::Player& player )
   {
      player.playScene( getId(), 5, NONE,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {
                          auto hustCount = player.getQuestUI8AL( getId() );
                          hustCount += 1;
                          player.setQuestUI8AL( getId(), hustCount );
                          player.sendQuestMessage( getId(), 0, 2, hustCount, 6 );
                          player.setQuestBitFlag8( getId(), 5, true );
                          checkQuestProgression( player );
                        } );
   }

   void Scene00006( Entity::Player& player )
   {
      player.playScene( getId(), 6, NONE,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {
                          auto hustCount = player.getQuestUI8AL( getId() );
                          hustCount += 1;
                          player.setQuestUI8AL( getId(), hustCount );
                          player.sendQuestMessage( getId(), 0, 2, hustCount, 6 );
                          player.setQuestBitFlag8( getId(), 6, true );
                          checkQuestProgression( player );
                        } );
   }

   void Scene00007( Entity::Player& player )
   {
      player.playScene( getId(), 7, NONE,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {
                          auto thalCount = player.getQuestUI8BH( getId() );
                          thalCount += 1;
                          player.setQuestUI8BH( getId(), thalCount );
                          player.sendQuestMessage( getId(), 1, 2, thalCount, 2 );
                          player.setQuestBitFlag8( getId(), 7, true );
                          checkQuestProgression( player );
                        } );
   }

   void Scene00008( Entity::Player& player )
   {
      player.playScene( getId(), 8, NONE,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {
                          auto thalCount = player.getQuestUI8BH( getId() );
                          thalCount += 1;
                          player.setQuestUI8BH( getId(), thalCount );
                          player.sendQuestMessage( getId(), 1, 2, thalCount, 2 );
                          player.setQuestBitFlag8( getId(), 8, true );
                          checkQuestProgression( player );
                        } );
   }

   void Scene00009( Entity::Player& player )
   {
      player.playScene( getId(), 9, NONE,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {} );
   }

   void Scene00010( Entity::Player& player )
   {
      player.playScene( getId(), 10, NONE,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {} );
   }

   void Scene00011( Entity::Player& player )
   {
      player.playScene( getId(), 11, NONE,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {} );
   }

   void Scene00012( Entity::Player& player )
   {
      player.playScene( getId(), 12, NONE,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {} );
   }

   void Scene00013( Entity::Player& player )
   {
      player.playScene( getId(), 13, NONE,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {} );
   }

   void Scene00014( Entity::Player& player )
   {
      player.playScene( getId(), 14, NONE,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {} );
   }

   void Scene00015( Entity::Player& player )
   {
      player.playScene( getId(), 15, NONE,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {} );
   }

   void Scene00016( Entity::Player& player )
   {
      player.playScene( getId(), 16, NONE,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {} );
   }

   void Scene00017( Entity::Player& player )
   {
      player.playScene( getId(), 17, NONE,
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

   void Scene00018( Entity::Player& player )
   {
      player.playScene( getId(), 18, NONE,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {} );
   }

   void Scene00019( Entity::Player& player )
   {
      player.playScene( getId(), 19, NONE,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {} );
   }

   void Scene00020( Entity::Player& player )
   {
      player.playScene( getId(), 20, NONE,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {} );
   }

   void Scene00021( Entity::Player& player )
   {
      player.playScene( getId(), 21, NONE,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {} );
   }

   void Scene00022( Entity::Player& player )
   {
      player.playScene( getId(), 22, NONE,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {} );
   }

   void Scene00023( Entity::Player& player )
   {
      player.playScene( getId(), 23, NONE,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {} );
   }

   void Scene00024( Entity::Player& player )
   {
      player.playScene( getId(), 24, NONE,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {} );
   }

   void Scene00025( Entity::Player& player )
   {
      player.playScene( getId(), 25, NONE,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {} );
   }

};

EXPOSE_SCRIPT( SubWil020 );