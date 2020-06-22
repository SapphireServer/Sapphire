#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include "Manager/TerritoryMgr.h"
#include <ScriptObject.h>
#include <Service.h>

// Quest Script: ManFst005_00445
// Quest Name: Chasing Shadows
// Quest ID: 65981
// Start NPC: 1000421
// End NPC: 1000421

using namespace Sapphire;

class ManFst005 : public Sapphire::ScriptAPI::EventScript
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
         Seq2 = 2,
         Seq3 = 3,
         SeqFinish = 255,
      };

      // Quest rewards 
      static constexpr auto RewardExpFactor = 200;
      static constexpr auto RewardGil = 132;
      static constexpr auto RewardItem = { 0, 0, 0, 0, 0, 0 };
      static constexpr auto RewardItemCount = { 0, 0, 0, 0, 0, 0 };
      static constexpr auto RewardItemOptional = { 0, 0, 0, 0, 0 };
      static constexpr auto RewardItemOptionalCount = { 0, 0, 0, 0, 0 };

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

   public:
      ManFst005() : Sapphire::ScriptAPI::EventScript( 65981 ){};
      ~ManFst005(){}; 

   //////////////////////////////////////////////////////////////////////
   // Event Handlers
   void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
   {
     auto& pEventMgr = Common::Service< World::Manager::EventMgr >::ref();
     auto actor = pEventMgr.mapEventActorToRealActor( static_cast< uint32_t >( actorId ) );

     if( actor == Actor0 )
     {
       if( !player.hasQuest( eventId ) )
       {
         Scene00000( player );
       }
       else
       {
         Scene00009( player );
       }
     }

     if( actor == Eobject0 )
       Scene00002( player );
     if( actor == Eobject1 )
     {
       player.eventActionStart( getId(), EventActionProcessShor,
                                [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional )
                                {
                                  player.updateQuest( getId(), SeqFinish );
                                },
                                nullptr, getId() );
     }
   }

   void onEnterTerritory( Entity::Player& player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {
     if( player.getQuestSeq( eventId ) == Seq2 )
     {
       Scene00005( player );
     }
   }

   private:
   //////////////////////////////////////////////////////////////////////
   // Available Scenes in this quest, not necessarly all are used
   void Scene00000( Entity::Player& player )
   {
     player.playScene( getId(), 0, HIDE_HOTBAR,
                       [ & ]( Entity::Player& player, const Event::SceneResult& result )
                       {
                         if( result.param2 == 1 ) // accept quest
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
                         player.eventActionStart( getId(), EventActionProcessShor,
                                                  [ & ]( Entity::Player& player, uint32_t eventId, uint64_t additional )
                                                  {
                                                    Scene00003( player );
                                                  },
                                                  nullptr, getId() );
                       } );
   }

   void Scene00003( Entity::Player& player )
   {
     player.playScene( getId(), 3, HIDE_HOTBAR,
                       [ & ]( Entity::Player& player, const Event::SceneResult& result )
                       {
                         if( result.param2 == 1 )
                         {
                           //auto& pTeriMgr = Common::Service< Sapphire::World::Manager::TerritoryMgr >::ref();
                           auto& pTeriMgr = *reinterpret_cast< Sapphire::World::Manager::TerritoryMgr* >( player.getTerritoryMgr() );

                           player.eventFinish( result.eventId, 0 );
                           pTeriMgr.createAndJoinQuestBattle( player, Questbattle0 );
                         }
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
     player.playScene( getId(), 5, NO_DEFAULT_CAMERA | CONDITION_CUTSCENE | SILENT_ENTER_TERRI_ENV |
                                   HIDE_HOTBAR | SILENT_ENTER_TERRI_BGM | SILENT_ENTER_TERRI_SE |
                                   DISABLE_STEALTH | 0x00100000 | LOCK_HUD | LOCK_HOTBAR |
                                   // todo: wtf is 0x00100000
                                   DISABLE_CANCEL_EMOTE,
                       [ & ]( Entity::Player& player, const Event::SceneResult& result )
                       {
                         player.updateQuest( result.eventId, Seq3 );
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
                         Scene00010( player );
                       } );
   }

   void Scene00010( Entity::Player& player )
   {
     player.playScene( getId(), 10, FADE_OUT | HIDE_HOTBAR | CONDITION_CUTSCENE | HIDE_UI,
                       [ & ]( Entity::Player& player, const Event::SceneResult& result )
                       {
                         if( result.param2 == 1 )
                           if( player.giveQuestRewards( getId(), 0 ) )
                           {
                             player.finishQuest( getId() );
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

};

EXPOSE_SCRIPT( ManFst005 );