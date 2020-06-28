#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>

using namespace Sapphire;

// Quest Script: SubFst007_00031
// Quest Name: Essential Oil
// Quest ID: 65567
// Start NPC: 1000705
// End NPC: 1000705

class SubFst007 : public Sapphire::ScriptAPI::EventScript
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
      static constexpr auto RewardExpFactor = 100;
      uint32_t RewardItemOptional[3] = { 3530, 3531, 5823 };
      uint32_t RewardItemOptionalCount[3] = { 1, 1, 3 };

      // Entities found in the script data of the quest
      static constexpr auto Actor0 = 1000705;
      static constexpr auto Enemy0 = 49;
      static constexpr auto Item0 = 2000098;
      static constexpr auto Seq0Actor0 = 0;
      static constexpr auto Seq2Actor0 = 1;
      static constexpr auto Seq2Actor0Npctradeno = 99;
      static constexpr auto Seq2Actor0Npctradeok = 100;

   public:
      SubFst007() : Sapphire::ScriptAPI::EventScript( 65567 ){};
      ~SubFst007(){}; 

   //////////////////////////////////////////////////////////////////////
   // Event Handlers
   void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
   {
     auto pEventMgr = Common::Service< World::Manager::EventMgr >::ref();
     auto actor = pEventMgr.mapEventActorToRealActor( static_cast<uint32_t>( actorId ) );

     if ( actor == Actor0 && !player.hasQuest( getId() ) )
     {
       Scene00000( player );
     }
     if ( actor == Actor0 && player.getQuestSeq( getId() ) == SeqFinish )
     {
       Scene00001( player );
     }
   }

   void onBNpcKill( uint32_t npcId, Entity::Player& player )
   {
     if ( npcId != Enemy0 )
       return;

     auto currentKC = player.getQuestUI8AL( getId() );

     if ( currentKC + 1 >= 6 )
     {
       player.setQuestUI8AL( getId(), currentKC + 1 );
       player.setQuestUI8BH( getId(), currentKC + 1 );
       player.sendQuestMessage( getId(), 0, 2, currentKC + 1, 6 );
       player.updateQuest( getId(), SeqFinish );
     }
     else
     {
        player.sendQuestMessage( getId(), 0, 2, currentKC + 1, 6 );
        player.setQuestUI8AL( getId(), currentKC + 1 );
        player.setQuestUI8BH( getId(), currentKC + 1 );
     }
   }

   private:
   //////////////////////////////////////////////////////////////////////
   // Available Scenes in this quest, not necessarly all are used
   void Scene00000( Entity::Player& player )
   {
      player.playScene( getId(), 0, HIDE_HOTBAR,
                        [&]( Entity::Player& player, const Event::SceneResult& result )
                        {
                          if( result.param2 == 1 )
                            player.updateQuest( getId(), Seq1 );
                        } );
   }

   void Scene00001( Entity::Player& player )
   {
      player.playScene( getId(), 1, HIDE_HOTBAR,
                        [&]( Entity::Player& player, const Event::SceneResult& result )
                        {
                          result.param2 == 1 ? Scene00100( player ) : Scene00099( player );
                        } );
   }

   void Scene00099( Entity::Player& player )
   {
      player.playScene( getId(), 99, HIDE_HOTBAR,
                        [&]( Entity::Player& player, const Event::SceneResult& result )
                        {
                        } );
   }

   void Scene00100( Entity::Player& player )
   {
      player.playScene( getId(), 100, HIDE_HOTBAR,
                        [&]( Entity::Player& player, const Event::SceneResult& result )
                        {
                          if ( result.param2 == 1 )
                          {
                            if ( player.giveQuestRewards( getId(), result.param3 ) )
                            {
                              player.finishQuest( getId() );
                            }
                          }
                        } );
   }
};

EXPOSE_SCRIPT(SubFst007);