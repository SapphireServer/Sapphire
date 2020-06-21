#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>

using namespace Sapphire;

// Quest Script: ClsArc005_00071
// Quest Name: Homecoming
// Quest ID: 65607
// Start NPC: 1000200
// End NPC: 1000200

class ClsArc005 : public Sapphire::ScriptAPI::EventScript
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
         SeqFinish = 255,
      };

      // Quest rewards 
      static constexpr auto RewardExpFactor = 100;
      static constexpr auto RewardItem = 1905;
      static constexpr auto RewardItemCount = 1;
      uint16_t RewardItemOptional[5] = { 3066, 2729, 3576, 3808, 5825 };
      uint16_t RewardItemOptionalCount[5] = { 1, 1, 1, 1, 2 };

      // Entities found in the script data of the quest
      static constexpr auto Actor0 = 1000200;
      static constexpr auto Actor1 = 1000204;
      static constexpr auto Actor2 = 1000199;
      static constexpr auto Actor3 = 1000534;
      static constexpr auto Actor4 = 1001284;
      static constexpr auto Actor5 = 1003025;
      static constexpr auto Actor6 = 1003026;
      static constexpr auto Eobject0 = 2000951;
      static constexpr auto Eobject1 = 2001840;
      static constexpr auto EventActionSearch = 1;
      static constexpr auto EventActionWaiting = 10;
      static constexpr auto LocActor5Action1 = 834;
      static constexpr auto LocPosActor5 = 3877820;
      static constexpr auto LocPosPc = 3877813;
      static constexpr auto Questbattle0 = 4;
      static constexpr auto Territorytype0 = 230;

   public:
      ClsArc005() : Sapphire::ScriptAPI::EventScript( 65607 ){}; 
      ~ClsArc005(){}; 

   void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
   {
      auto pEventMgr = Common::Service< World::Manager::EventMgr >::ref();
      auto actor = pEventMgr.mapEventActorToRealActor( static_cast<uint32_t>( actorId ) );

      if( actor == Actor0 && !player.hasQuest( getId() ) )
         Scene00000( player );
      if( actor == Actor1 && player.getQuestSeq( getId() ) == Seq1 )
         Scene00002( player );
      if( actor == Actor2 && player.getQuestSeq( getId() ) == Seq2 )
         Scene00003( player );
      if( actor == Actor3 && player.getQuestSeq( getId() ) == Seq4 )
         Scene00006( player );
      if( actor == Actor0 && player.getQuestSeq( getId() ) == SeqFinish )
         Scene00010( player );
      //EOBJECTS
      else if( actor == Eobject0 )
         player.eventActionStart( getId(), 0x0A,
                                  [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional )
                                  {
                                     Scene00004( player );
                                     player.sendQuestMessage( getId(), 2, 2, 0, 0 );
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
      player.playScene( getId(), 1, HIDE_HOTBAR,
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
                          player.sendQuestMessage( getId(), 0, 2, 0, 0 );
                          player.updateQuest( getId(), Seq2 );
                        } );
   }

   void Scene00003( Entity::Player& player )
   {
      player.playScene( getId(), 3, HIDE_HOTBAR,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {
                          player.sendQuestMessage( getId(), 1, 2, 0, 0 );
                          player.updateQuest( getId(), Seq3 );
                        } );
   }

   void Scene00004( Entity::Player& player )
   {
      player.playScene( getId(), 4, HIDE_HOTBAR,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {
                          Scene00005( player );
                        } );
   }

   void Scene00005( Entity::Player& player )
   {
      player.playScene( getId(), 5, SET_EOBJ_BASE | HIDE_HOTBAR | INVIS_EOBJ,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {
                          player.updateQuest( getId(), Seq4 );
                        } );
   }

   void Scene00006( Entity::Player& player )
   {
      player.playScene( getId(), 6, HIDE_HOTBAR,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {
                          Scene00007( player );
                        } );
   }

   void Scene00007( Entity::Player& player )
   {
      player.playScene( getId(), 7, HIDE_HOTBAR,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {
                          if( result.param2 == 1 )
                          {
                              player.updateQuest( getId(), SeqFinish );
                              // QuestBattle doesn't work
                              /*auto& pTeriMgr = Common::Service< Sapphire::World::Manager::TerritoryMgr >::ref();

                              player.eventFinish(result.eventId, 0);
                              pTeriMgr.createAndJoinQuestBattle(player, Questbattle0);*/
                          }
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

EXPOSE_SCRIPT(ClsArc005);