#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include "Manager/TerritoryMgr.h"
#include <ScriptObject.h>
#include <Service.h>

using namespace Sapphire;

// Quest Script: ClsArc003_00068
// Quest Name: Violators Will Be Shot
// Quest ID: 65604
// Start NPC: 1000200
// End NPC: 1000200

class ClsArc003 : public Sapphire::ScriptAPI::EventScript
{
   private:
      // Basic quest information 
      // Quest vars / flags used
      // GetQuestBitFlag8
      // GetQuestUI8AL

      enum Sequence : uint8_t
      {
         Seq0 = 0,
         Seq1 = 1,
         Seq2 = 2,
         Seq3 = 3,
         Seq4 = 4,
         Seq5 = 5,
         SeqFinish = 255,
      };

      // Quest rewards 
      static constexpr auto RewardExpFactor = 100;
      static constexpr auto RewardAction = 112;
      static constexpr auto RewardItem = 1895;
      static constexpr auto RewardItemCount = 1;
      uint16_t RewardItemOptional[5] = { 3028, 2677, 3546, 3780, 5824 };
      uint16_t RewardItemOptionalCount[5] = { 1, 1, 1, 1, 3 };

      // Entities found in the script data of the quest
      static constexpr auto Action0 = 97;
      static constexpr auto Actor0 = 1000200;
      static constexpr auto Actor1 = 1000204;
      static constexpr auto Actor2 = 1000199;
      static constexpr auto Eobject0 = 2000941;
      static constexpr auto Eobject1 = 2000942;
      static constexpr auto Eobject2 = 2000943;
      static constexpr auto Eobject3 = 2000944;
      static constexpr auto Eobject4 = 2000945;
      static constexpr auto Eobject5 = 2000946;
      static constexpr auto Eobject6 = 2001179;
      static constexpr auto Eobject7 = 2001180;
      static constexpr auto Eobject8 = 2000962;
      static constexpr auto EventActionWaiting2Middle = 12;
      static constexpr auto EventMotZephyr = 366;
      static constexpr auto LocAction0 = 995;
      static constexpr auto LocVfx = 241;
      static constexpr auto LocWs = 112;
      static constexpr auto Questbattle0 = 6;
      static constexpr auto Territorytype0 = 228;

   public:
      ClsArc003() : Sapphire::ScriptAPI::EventScript( 65604 ){}; 
      ~ClsArc003(){}; 

   void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
   {
      auto pEventMgr = Common::Service< World::Manager::EventMgr >::ref();
      auto actor = pEventMgr.mapEventActorToRealActor( static_cast<uint32_t>( actorId ) );

      if( actor == Actor0 && !player.hasQuest( getId() ) )
         Scene00000( player );
      if( actor == Actor1 && player.getQuestSeq( getId() ) == Seq1 )
         Scene00001( player );
      if( actor == Actor1 && player.getQuestSeq( getId() ) == Seq3 )
         Scene00026( player );
      if( actor == Actor1 && player.getQuestSeq( getId() ) == Seq5 )
         Scene00030( player );
      if( actor == Actor0 && player.getQuestSeq( getId() ) == SeqFinish )
         Scene00031( player );
   }

   void onEObjHit( Entity::Player& player, uint64_t actorId, uint32_t actionId )
   {
     auto pEventMgr = Common::Service< World::Manager::EventMgr >::ref();
     auto actor = pEventMgr.mapEventActorToRealActor( static_cast<uint32_t>( actorId ) );

     //Eobjects
     // eventActionStart let crash world.exe
     // eventStart is hardcode fix
     if ( actor == Eobject0 )
     {
       player.eventStart( actor, getId(), Event::EventHandler::Nest, 0, 0 );
       Scene00002( player );
     }
     else if ( actor == Eobject1 )
     {
       player.eventStart( actor, getId(), Event::EventHandler::Nest, 0, 0 );
       Scene00003( player );
     }
     else if ( actor == Eobject2 )
     {
       player.eventStart( actor, getId(), Event::EventHandler::Nest, 0, 0 );
       Scene00004( player );
     }
     else if ( actor == Eobject3 )
     {
       player.eventStart( actor, getId(), Event::EventHandler::Nest, 0, 0 );
       Scene00005( player );
     }
     else if ( actor == Eobject4 )
     {
       player.eventStart( actor, getId(), Event::EventHandler::Nest, 0, 0 );
       Scene00006( player );
     }
     else if ( actor == Eobject5 )
     {
       player.eventStart( actor, getId(), Event::EventHandler::Nest, 0, 0 );
       Scene00007( player );
     }
     else if ( actor == Eobject6 )
     {
       player.eventStart( actor, getId(), Event::EventHandler::Nest, 0, 0 );
       Scene00008( player );
     }
     else if ( actor == Eobject7 )
     {
       player.eventStart( actor, getId(), Event::EventHandler::Nest, 0, 0 );
       Scene00009( player );
     }
     else if ( actor == Eobject8 )
     {
       player.eventStart( actor, getId(), Event::EventHandler::Nest, 0, 0 );
       Scene00027( player );
     }
   }

   private:

   void checkQuestCompletion( Entity::Player& player )
   {
      auto currentCC = player.getQuestUI8AL( getId() );

      player.sendQuestMessage( getId(), 1, 2, currentCC + 1, 6 );

      if( currentCC + 1 >= 6 )
      {
        player.setQuestUI8AL( getId(), 0 );
        player.updateQuest( getId(), Seq3 );
      }
      else
      {
        player.setQuestUI8AL( getId(), currentCC + 1 );
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
                          }
                        } );
   }

   void Scene00001( Entity::Player& player )
   {
      player.playScene( getId(), 1, HIDE_HOTBAR,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {
                          player.sendQuestMessage( getId(), 0, 2, 0, 0 );
                          player.updateQuest( getId(), Seq2 );
                        } );
   }

   void Scene00002( Entity::Player& player )
   {
      player.playScene( getId(), 2, HIDE_HOTBAR,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {
                            checkQuestCompletion( player );
                            player.setQuestBitFlag8( getId(), 1, true );
                        } );
   }

   void Scene00003( Entity::Player& player )
   {
      player.playScene( getId(), 3, HIDE_HOTBAR,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {
                            checkQuestCompletion( player );
                            player.setQuestBitFlag8( getId(), 2, true );
                        } );
   }

   void Scene00004( Entity::Player& player )
   {
      player.playScene( getId(), 4, HIDE_HOTBAR,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {
                            checkQuestCompletion( player );
                            player.setQuestBitFlag8( getId(), 3, true );
                        } );
   }

   void Scene00005( Entity::Player& player )
   {
      player.playScene( getId(), 5, HIDE_HOTBAR,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {
                           checkQuestCompletion( player );
                           player.setQuestBitFlag8( getId(), 4, true );
                        } );
   }

   void Scene00006( Entity::Player& player )
   {
      player.playScene( getId(), 6, HIDE_HOTBAR,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {
                           checkQuestCompletion( player );
                           player.setQuestBitFlag8( getId(), 5, true );
                        } );
   }

   void Scene00007( Entity::Player& player )
   {
      player.playScene( getId(), 7, HIDE_HOTBAR,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {
                           checkQuestCompletion( player );
                           player.setQuestBitFlag8( getId(), 6, true );
                        } );
   }

   void Scene00008( Entity::Player& player )
   {
      player.playScene( getId(), 8, HIDE_HOTBAR,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {
                           checkQuestCompletion( player );
                           player.setQuestBitFlag8( getId(), 7, true );
                        } );
   }

   void Scene00009( Entity::Player& player )
   {
      player.playScene( getId(), 9, HIDE_HOTBAR,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {
                            checkQuestCompletion( player );
                            player.setQuestBitFlag8( getId(), 8, true );
                        } );
   }

   void Scene00010( Entity::Player& player )
   {
      player.playScene( getId(), 10, HIDE_HOTBAR,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {
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

   void Scene00014( Entity::Player& player )
   {
      player.playScene( getId(), 14, HIDE_HOTBAR,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {
                        } );
   }

   void Scene00015( Entity::Player& player )
   {
      player.playScene( getId(), 15, HIDE_HOTBAR,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {
                        } );
   }

   void Scene00016( Entity::Player& player )
   {
      player.playScene( getId(), 16, HIDE_HOTBAR,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {
                        } );
   }

   void Scene00017( Entity::Player& player )
   {
      player.playScene( getId(), 17, HIDE_HOTBAR,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {
                        } );
   }

   void Scene00018( Entity::Player& player )
   {
      player.playScene( getId(), 18, HIDE_HOTBAR,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {
                        } );
   }

   void Scene00019( Entity::Player& player )
   {
      player.playScene( getId(), 19, HIDE_HOTBAR,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {
                        } );
   }

   void Scene00020( Entity::Player& player )
   {
      player.playScene( getId(), 20, HIDE_HOTBAR,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {
                        } );
   }

   void Scene00021( Entity::Player& player )
   {
      player.playScene( getId(), 21, HIDE_HOTBAR,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {
                        } );
   }

   void Scene00022( Entity::Player& player )
   {
      player.playScene( getId(), 22, HIDE_HOTBAR,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {
                        } );
   }

   void Scene00023( Entity::Player& player )
   {
      player.playScene( getId(), 23, HIDE_HOTBAR,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {
                        } );
   }

   void Scene00024( Entity::Player& player )
   {
      player.playScene( getId(), 24, HIDE_HOTBAR,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {
                        } );
   }

   void Scene00025( Entity::Player& player )
   {
      player.playScene( getId(), 25, HIDE_HOTBAR,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {
                        } );
   }

   void Scene00026( Entity::Player& player )
   {
      player.playScene( getId(), 26, HIDE_HOTBAR,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {
                          player.setQuestUI8AL( getId(), 0 );
                          player.sendQuestMessage( getId(), 2, 2, 0, 0 );
                          player.updateQuest( getId(), Seq4 );
                        } );
   }

   void Scene00027( Entity::Player& player )
   {
      player.playScene( getId(), 27, HIDE_HOTBAR,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {
                          Scene00028( player );
                        } );
   }

   void Scene00028( Entity::Player& player )
   {
      player.playScene( getId(), 28, HIDE_HOTBAR,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {
                          if( result.param2 == 1 )
                          {
                              player.updateQuest( getId(), Seq5 );
                              // QuestBattle doesn't work
                              /*auto& pTeriMgr = Common::Service< Sapphire::World::Manager::TerritoryMgr >::ref();

                              player.eventFinish( result.eventId, 0 );
                              pTeriMgr.createAndJoinQuestBattle( player, Questbattle0 );*/
                          }
                        } );
   }

   void Scene00029( Entity::Player& player )
   {
      player.playScene( getId(), 29, HIDE_HOTBAR,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {
                        } );
   }

   void Scene00030( Entity::Player& player )
   {
      player.playScene( getId(), 30, HIDE_HOTBAR,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {
                          player.sendQuestMessage( getId(), 4, 2, 0, 0 );
                          player.updateQuest( getId(), SeqFinish );
                        } );
   }

   void Scene00031( Entity::Player& player )
   {
      player.playScene( getId(), 31, SET_EOBJ_BASE | HIDE_HOTBAR | INVIS_EOBJ,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {
                          if( result.param2 == 1 )
                          {
                              if( player.giveQuestRewards( getId(), result.param3 ) )
                              {
                                player.finishQuest( getId() );
                              }
                          }
                        } );
   }
};

EXPOSE_SCRIPT(ClsArc003);