#include <Script/NativeScriptApi.h>
#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include "Framework.h"

using namespace Sapphire;

// Quest Script: SubSea012_00122
// Quest Name: Glory Days
// Quest ID: 65658
// Start NPC: 1003601
// End NPC: 1000972

class SubSea012 : public EventScript
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
         SeqFinish = 255,
      };

      // Quest rewards 
      static constexpr auto RewardExpFactor = 100;
      static constexpr auto RewardItem[] = { 0, 0, 0, 0, 0, 0 };
      static constexpr auto RewardItemCount[] = { 0, 0, 0, 0, 0, 0 };
      static constexpr auto RewardItemOptional[] = { 2999, 3010, 5823, 0, 0 };
      static constexpr auto RewardItemOptionalCount[] = { 1, 1, 3, 0, 0 };

      // Entities found in the script data of the quest
      static constexpr auto Actor0 = 1003601;
      static constexpr auto Actor1 = 1001024;
      static constexpr auto Actor2 = 1000972;
      static constexpr auto Enemy0 = 324;
      static constexpr auto Item0 = 2000454;

   public:
      SubSea012() : EventScript( 65658 ){}; 
      ~SubSea012(){}; 

   //////////////////////////////////////////////////////////////////////
   // Event Handlers
   void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
   {
      auto pEventMgr = m_framework->get< World::Manager::EventMgr >();
      auto actor = pEventMgr->mapEventActorToRealActor( static_cast< uint32_t >( actorId ) );
    if( actor == Actor0 )
    {
      Scene00000( player );
    }
    else if( actor == Actor1 )
    {
      Scene00003( player );
    }
    else if( actor == Actor2 )
    {
      Scene00004( player );
    }
   }

     void onMobKill( Entity::Player& player, uint64_t npcId )
  {
    if( npcId != Enemy0 )
      return;

    auto currentKC = player.getQuestUI8AL( getId() ) + 1;

    if( currentKC >= 4 )
      player.updateQuest( getId(), SeqFinish );
    else
    {
      player.setQuestUI8AL( getId(), currentKC );
      player.sendQuestMessage( getId(), 0, 2, currentKC, 4 );
    }
}

   private:
   //////////////////////////////////////////////////////////////////////
   // Available Scenes in this quest, not necessarly all are used
  void checkQuestCompletion( Entity::Player& player )
  {
    auto currentCC = player.getQuestUI8BH( getId() );

    player.sendQuestMessage( getId(), X, Y, currentCC + 1, Z );

    if( currentCC + 1 >= Z )
    {
      player.updateQuest( getId(), SeqFinish );
      player.setQuestUI8BH( getId(), currentCC + 1 );
      player.setQuestUI8AL( getId(), currentCC + 1 );
    }
    else
    {
      player.setQuestUI8BH( getId(), currentCC + 1 );
      player.setQuestUI8AL( getId(), currentCC + 1 );
    }
  }

   void Scene00000( Entity::Player& player )
  {
    player.playScene( getId(), 0, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        if( result.param2 == 1 )
                          player.updateQuest( getId(), 1 );
                      } );
  }

   void Scene00001( Entity::Player& player )
  {
    player.playScene( getId(), 1, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                      } );
  }

   void Scene00002( Entity::Player& player )
  {
    player.playScene( getId(), 2, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                      } );
  }

   void Scene00003( Entity::Player& player )
  {
    player.playScene( getId(), 3, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        if( result.param2 == 1 )
                          player.updateQuest( getId(), 2 );
                      } );
  }

   void Scene00004( Entity::Player& player )
  {
    player.playScene( getId(), 4, HIDE_HOTBAR,
                      [ & ]( Entity::Player& player, const Event::SceneResult& result )
                      {
                        if( result.param2 == 1 )
                          if( player.giveQuestRewards( getId(), 0 ) )
                            player.finishQuest( getId() );
                        }
                      } );
  }

};