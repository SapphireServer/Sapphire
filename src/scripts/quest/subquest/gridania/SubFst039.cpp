#include <Script/NativeScriptApi.h>
#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include "Framework.h"

using namespace Sapphire;

// Quest Script: SubFst039_00196
// Quest Name: An Eft for Effort
// Quest ID: 65732
// Start NPC: 1000421
// End NPC: 1000421

class SubFst039 : public Sapphire::ScriptAPI::EventScript
{
   private:
      // Basic quest information 
      // Quest vars / flags used
      // GetQuestUI8AL

      // Steps in this quest ( 0 is before accepting, 
      // 1 is first, 255 means ready for turning it in
      enum Sequence : uint8_t
      {
         Seq0 = 0,
         Seq1 = 1,
         SeqFinish = 255,
      };

      // Entities found in the script data of the quest
      static constexpr auto Actor0 = 1000421;
      static constexpr auto Enemy0 = 196;
      static constexpr auto Seq0Actor0 = 0;
      static constexpr auto Seq2Actor0 = 1;

   public:
      SubFst039() : Sapphire::ScriptAPI::EventScript( 65732 ){};
      ~SubFst039(){}; 

   //////////////////////////////////////////////////////////////////////
   // Event Handlers
   void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
   {
     auto pEventMgr = m_framework->get< World::Manager::EventMgr >();
     auto actor = pEventMgr->mapEventActorToRealActor( static_cast< uint32_t >( actorId ) );

     if( actor == Actor0 && !player.hasQuest( getId() ) )
     {
       Scene00000( player );
     }
     else if( actor == Actor0 && player.getQuestSeq( getId() ) == SeqFinish )
     {
       Scene00001( player );
     }
   }

   void onBNpcKill( uint32_t npcId, Entity::Player& player ) override
   {
      if( npcId != Enemy0 )
         return;

      auto currentKC = player.getQuestUI8AL( getId() ) + 1;

      if( currentKC >= 4 )
         player.updateQuest( getId(), SeqFinish );
      else
      {
         player.setQuestUI8AL( getId(), currentKC );
      }
      player.sendQuestMessage( getId(), 0, 2, currentKC, 4 );
  }

   private:
   //////////////////////////////////////////////////////////////////////
   // Available Scenes in this quest, not necessarly all are used
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
                        if( result.param2 == 1 )
                        {
                          if( player.giveQuestRewards( getId(), 0 ) )
                          {
                            player.finishQuest( getId() );
                          }
                        }
                      } );
  };

};

EXPOSE_SCRIPT( SubFst039 );