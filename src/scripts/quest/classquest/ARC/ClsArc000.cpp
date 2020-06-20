#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>

using namespace Sapphire;

// Quest Script: ClsArc000_00021
// Quest Name: Way of the Archer
// Quest ID: 65557
// Start NPC: 1000197
// End NPC: 1000200

class ClsArc000 : public Sapphire::ScriptAPI::EventScript
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
      ClsArc000() : Sapphire::ScriptAPI::EventScript( 65557 ){}; 
      ~ClsArc000(){}; 

  //////////////////////////////////////////////////////////////////////
  // Event Handlers
   void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
   {
      auto pEventMgr = Common::Service< World::Manager::EventMgr >::ref();
      auto actor = pEventMgr.mapEventActorToRealActor( static_cast< uint32_t >( actorId ) );

      if( actor == Actor0 )
         Scene00000( player );
      if( actor == Actor1 && player.getQuestSeq( getId() ) == Seq1 )
         Scene00001( player );
      if( actor == Actor1 && player.getQuestSeq( getId() ) == SeqFinish )
         Scene00002( player );
   }

   void onBNpcKill( uint32_t npcId, Entity::Player& player ) override
   {
      if( npcId != Enemy0 && npcId != Enemy1 && npcId != Enemy2 )
         return;

      if ( npcId == Enemy0 )
      {
        auto currentKC37 = player.getQuestUI8AL( getId() );

        if ( currentKC37 + 1 >= 3 )
        {
          checkQuestCompletion( player, 1 );
          player.setQuestUI8AL( getId(), currentKC37 + 1 );
        }
        else
        {
          player.setQuestUI8AL( getId(), currentKC37 + 1 );
          player.sendQuestMessage( getId(), 1, 2, currentKC37 + 1, 3 );
        }
      }

      if ( npcId == Enemy1 )
      {
        auto currentKC49 = player.getQuestUI8BH( getId() );

        if ( currentKC49 + 1 >= 3 )
        {
          checkQuestCompletion( player, 2 );
          player.setQuestUI8BH( getId(), currentKC49 + 1 );
        }
        else
        {
          player.setQuestUI8BH( getId(), currentKC49 + 1 );
          player.sendQuestMessage( getId(), 2, 2, currentKC49 + 1, 3 );
        }
      }

      if ( npcId == Enemy2 )
      {
        auto currentKC47 = player.getQuestUI8BL( getId() );

        if ( currentKC47 + 1 >= 3 )
        {
          checkQuestCompletion( player, 3 );
          player.setQuestUI8BL( getId(), currentKC47 + 1 );
        }
        else
        {
          player.setQuestUI8BL( getId(), currentKC47 + 1 );
          player.sendQuestMessage( getId(), 3, 2, currentKC47 + 1, 3 );
        }
      }
   }

   private:

   void checkQuestCompletion( Entity::Player& player, uint32_t varIdx )
   {
      if( varIdx == 1 )
         player.sendQuestMessage( getId(), 1, 0, 0, 0 );
      else if( varIdx == 2 )
         player.sendQuestMessage( getId(), 2, 0, 0, 0 );
      else
         player.sendQuestMessage( getId(), 3, 0, 0, 0 );

      auto questId = getId();

      auto QUEST_ONKILL_37 = player.getQuestUI8AL( questId );
      auto QUEST_ONKILL_49 = player.getQuestUI8BH( questId );
      auto QUEST_ONKILL_47 = player.getQuestUI8BL( questId );

      if( QUEST_ONKILL_37 >= 3 && QUEST_ONKILL_49 >= 3 && QUEST_ONKILL_47 >= 3 )
      {
         player.updateQuest( questId, SeqFinish );
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
      player.playScene( getId(), 1, SET_EOBJ_BASE | HIDE_HOTBAR | INVIS_EOBJ,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
                        {
                          if( result.param2 == 1 )
                          {
                              player.sendQuestMessage( getId(), 0, 0, 0, 0 );
                              player.updateQuest( getId(), Seq2 );
                          }
                        } );
   }

   void Scene00002( Entity::Player& player )
   {
      player.playScene( getId(), 2, HIDE_HOTBAR,
                        [ & ]( Entity::Player& player, const Event::SceneResult& result )
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

EXPOSE_SCRIPT( ClsArc000 );