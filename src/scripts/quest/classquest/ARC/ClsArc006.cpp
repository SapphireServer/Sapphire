#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>

using namespace Sapphire;

// Quest Script: ClsArc006_00076
// Quest Name: The One That Got Away
// Quest ID: 65612
// Start NPC: 1000200
// End NPC: 1000200

class ClsArc006 : public Sapphire::ScriptAPI::EventScript
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
         SeqFinish = 255,
      };

      // Quest rewards 
      static constexpr auto RewardExpFactor = 100;
      static constexpr auto RewardAction = 113;
      static constexpr auto RewardItem = 1915;
      static constexpr auto RewardItemCount = 1;
      uint16_t RewardItemOptional[5] = { 3100, 2753, 3597, 3827, 5825 };
      uint16_t RewardItemOptionalCount[5] = { 1, 1, 1, 1, 3 };

      // Entities found in the script data of the quest
      static constexpr auto Actor0 = 1000200;
      static constexpr auto Actor1 = 1000795;
      static constexpr auto Actor2 = 1000796;
      static constexpr auto Actor3 = 1000797;
      static constexpr auto Actor4 = 1000798;
      static constexpr auto Actor5 = 1000799;
      static constexpr auto Actor6 = 1000800;
      static constexpr auto Actor7 = 1003066; // silver
      static constexpr auto Actor8 = 1003067; // lea
      static constexpr auto Actor9 = 1003068; // pawah
      static constexpr auto Eobject0 = 2001841;
      static constexpr auto Eobject1 = 2000709;
      static constexpr auto EventAction = 27;
      static constexpr auto EventActionSearch = 1;
      static constexpr auto EventMotZephyr = 366;
      static constexpr auto LocAction0 = 995;
      static constexpr auto LocActor0 = 1000199;
      static constexpr auto LocActor1 = 1000204;
      static constexpr auto LocVfx = 241;
      static constexpr auto LocWs = 113;
      static constexpr auto Questbattle0 = 2;
      static constexpr auto Questbattle1 = 3;
      static constexpr auto Seq0Actor0Lq = 98;
      static constexpr auto Territorytype0 = 231;
      static constexpr auto Territorytype1 = 236;

   public:
      ClsArc006() : Sapphire::ScriptAPI::EventScript( 65612 ){}; 
      ~ClsArc006(){}; 

   void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
   {
      auto pEventMgr = Common::Service< World::Manager::EventMgr >::ref();
      auto actor = pEventMgr.mapEventActorToRealActor( static_cast<uint32_t>( actorId ) );

      if( actor == Actor0 && !player.hasQuest( getId() ) )
         Scene00000( player );
      if( actor == Actor1 && player.getQuestSeq( getId() ) == Seq1 )
         Scene00002( player );
      if( actor == Actor0 && player.getQuestSeq( getId() ) == SeqFinish )
         Scene00013( player );
      if( actor == Actor7 && player.getQuestSeq( getId() ) == SeqFinish )
         Scene00014( player );
      if( actor == Actor8 && player.getQuestSeq( getId() ) == SeqFinish )
         Scene00015( player );
      if( actor == Actor9 && player.getQuestSeq( getId() ) == SeqFinish )
         Scene00016( player );
      //EOBJECTS
      else if( actor == Eobject1 )
         player.eventActionStart( getId(), 0x1B,
                                  [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional )
                                  {
                                     Scene00011( player );
                                  },
                                  nullptr, eventId );
   }

   private:

   void Scene00000( Entity::Player& player )
   {
      player.playScene( getId(), 0, HIDE_HOTBAR,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
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
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {
                          player.updateQuest( getId(), Seq1 );
                        } );
   }

   void Scene00002( Entity::Player& player )
   {
      player.playScene( getId(), 2, HIDE_HOTBAR,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {
                          if( result.param2 == 1 )
                          {
                              player.updateQuest( getId(), Seq2 );
                              // QuestBattle doesn't work
                              /*auto& pTeriMgr = Common::Service< Sapphire::World::Manager::TerritoryMgr >::ref();

                              player.eventFinish(result.eventId, 0);
                              pTeriMgr.createAndJoinQuestBattle(player, Questbattle0);*/
                          }
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
                        } );
   }

   void Scene00005( Entity::Player& player )
   {
      player.playScene( getId(), 5, HIDE_HOTBAR,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {
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
                        } );
   }

   void Scene00008( Entity::Player& player )
   {
      player.playScene( getId(), 8, HIDE_HOTBAR,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {
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
                        } );
   }

   void Scene00011( Entity::Player& player )
   {
      player.playScene( getId(), 11, HIDE_HOTBAR,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {
                          if( result.param2 == 1 )
                          {
                              player.updateQuest( getId(), SeqFinish );
                              // QuestBattle doesn't work
                              /*auto& pTeriMgr = Common::Service< Sapphire::World::Manager::TerritoryMgr >::ref();

                              player.eventFinish(result.eventId, 0);
                              pTeriMgr.createAndJoinQuestBattle(player, Questbattle1);*/
                          }
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
      player.playScene( getId(), 13, SET_EOBJ_BASE | HIDE_HOTBAR | INVIS_EOBJ,
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
};

EXPOSE_SCRIPT(ClsArc006);