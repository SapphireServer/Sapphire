#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>

using namespace Sapphire;

// Quest Script: ClsArc004_00070
// Quest Name: To Catch a Poacher
// Quest ID: 65606
// Start NPC: 1000200
// End NPC: 1000200

class ClsArc004 : public Sapphire::ScriptAPI::EventScript
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
      static constexpr auto RewardItem = 1899;
      static constexpr auto RewardItemCount = 1;
      uint16_t RewardItemOptional[5] = { 3043, 2708, 3559, 3791, 5824 };
      uint16_t RewardItemOptionalCount[5] = { 1, 1, 1, 1, 5 };

      // Entities found in the script data of the quest
      static constexpr auto Actor0 = 1000200;
      static constexpr auto Actor1 = 1000590;
      static constexpr auto Actor2 = 1000731;
      static constexpr auto Actor3 = 1000732;
      static constexpr auto Actor4 = 1000199;
      static constexpr auto Actor5 = 1000204;
      static constexpr auto Eobject0 = 2000947;
      static constexpr auto Eobject1 = 2000948;
      static constexpr auto Eobject2 = 2000949;
      static constexpr auto Eobject3 = 2001105;
      static constexpr auto Eobject4 = 2000136;
      static constexpr auto EventActionGatherMiddle = 7;
      static constexpr auto EventActionSearch = 1;
      static constexpr auto EventActionWaiting = 10;
      static constexpr auto LocPosActor5 = 3875531;
      static constexpr auto Questbattle0 = 5;
      static constexpr auto Seq0Actor0Lq = 90;
      static constexpr auto Territorytype0 = 229;

   public:
      ClsArc004() : Sapphire::ScriptAPI::EventScript( 65606 ){}; 
      ~ClsArc004(){}; 

   void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
   {
      auto pEventMgr = Common::Service< World::Manager::EventMgr >::ref();
      auto actor = pEventMgr.mapEventActorToRealActor( static_cast<uint32_t>( actorId ) );

      if( actor == Actor0 && !player.hasQuest( getId() ) )
         Scene00000( player );
      if( actor == Actor1 && player.getQuestSeq( getId() ) == Seq1 )
         Scene00002( player );
      if( actor == Actor1 && player.getQuestSeq( getId() ) == Seq5 ) // <- Player can't talk with NPC... idk
         Scene00018( player );
      if( actor == Actor3 && player.getQuestSeq( getId() ) == Seq5 )
         Scene00019( player );
      if( actor == Actor2 && player.getQuestSeq( getId() ) == Seq5 )
         Scene00020( player );
      if( actor == Actor0 && player.getQuestSeq( getId() ) == SeqFinish )
         Scene00021( player );
      //Eobjects
      else if( actor == Eobject0 )
         player.eventActionStart( getId(), 0x07,
            [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional )
            {
               Scene00003( player );
            },
            nullptr, eventId );
      else if( actor == Eobject1 )
         player.eventActionStart( getId(), 0x07,
            [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional )
            {
               Scene00004( player );
            },
            nullptr, eventId );
      else if( actor == Eobject2 )
         player.eventActionStart( getId(), 0x07,
            [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional )
            {
               Scene00005( player );
            },
            nullptr, eventId );
      else if( actor == Eobject3 )
         player.eventActionStart( getId(), 0x0A,
            [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional )
            {
               Scene00013( player );
               player.sendQuestMessage( getId(), 2, 2, 0, 0 );
            },
            nullptr, eventId );
      else if( actor == Eobject4 )
         player.eventActionStart( getId(), 0x01,
            [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional )
            {
               Scene00015( player );
            },
            nullptr, eventId );
   }

   private:

   void checkQuestCompletion( Entity::Player& player )
   {
      auto currentCC = player.getQuestUI8AL( getId() );

      player.sendQuestMessage( getId(), 1, 2, currentCC + 1, 3 );

      if( currentCC + 1 >= 3 )
      {
         player.updateQuest( getId(), Seq3 );
         player.setQuestUI8AL( getId(), 0 );
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
      player.playScene( getId(), 2, SET_EOBJ_BASE | HIDE_HOTBAR | INVIS_EOBJ,
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
                          player.setQuestBitFlag8( getId(), 1, true );
                          checkQuestCompletion( player );
                        } );
   }

   void Scene00004( Entity::Player& player )
   {
      player.playScene( getId(), 4, HIDE_HOTBAR,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {
                          player.setQuestBitFlag8(getId(), 2, true);
                          checkQuestCompletion( player );
                        } );
   }

   void Scene00005( Entity::Player& player )
   {
      player.playScene( getId(), 5, HIDE_HOTBAR,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {
                          player.setQuestBitFlag8(getId(), 3, true);
                          checkQuestCompletion( player );
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
                          player.updateQuest( getId(), Seq4 );
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
                          Scene00016( player );
                        } );
   }

   void Scene00016( Entity::Player& player )
   {
      player.playScene( getId(), 16, HIDE_HOTBAR,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {
                          if( result.param2 == 1 )
                          {
                              player.updateQuest( getId(), Seq5 );
                              // QuestBattle doesn't work
                              /*auto& pTeriMgr = Common::Service< Sapphire::World::Manager::TerritoryMgr >::ref();

                              player.eventFinish(result.eventId, 0);
                              pTeriMgr.createAndJoinQuestBattle(player, Questbattle0);*/
                          }
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
                          player.sendQuestMessage( getId(), 4, 2, 0, 0 );
                          player.updateQuest( getId(), SeqFinish );
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

EXPOSE_SCRIPT(ClsArc004);