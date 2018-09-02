#include <Actor/Player.h>
#include <Event/EventHelper.h>
#include <ScriptObject.h>

// Quest Script: ManWil005_00550
// Quest Name: Underneath the Sultantree
// Quest ID: 66086
// Start NPC: 1003995
// End NPC: 1003995

class ManWil005 :
   public EventScript
{
   private:
      // Basic quest information 
      // Quest vars / flags used
      // GetQuestBitFlag8
      // GetQuestUI8AL

      enum Sequence :
         uint8_t
      {
         Seq0 = 0,
         Seq1 = 1,
         Seq2 = 2,
         SeqFinish = 255,
      };

      // Quest rewards 
      static constexpr auto RewardExpFactor = 200;
      static constexpr auto RewardGil = 132;

      // Entities found in the script data of the quest
      static constexpr auto Actor0 = 1003995;
      static constexpr auto Actor1 = 1003996;
      static constexpr auto Actor2 = 1003997;
      static constexpr auto Actor20 = 1006171;
      static constexpr auto Actor3 = 1003998;
      static constexpr auto Actor30 = 1006167;
      static constexpr auto Actor4 = 1003999;
      static constexpr auto Actor40 = 1006168;
      static constexpr auto Actor5 = 1004000;
      static constexpr auto Actor50 = 1006169;
      static constexpr auto Actor6 = 1004001;
      static constexpr auto Actor60 = 1006170;
      static constexpr auto CutScene02 = 141;
      static constexpr auto CutScene03 = 56;
      static constexpr auto CutScene04 = 142;
      static constexpr auto Eobject0 = 2001853;
      static constexpr auto EventActionSearch = 1;
      static constexpr auto Questbattle0 = 37;
      static constexpr auto Seq0Actor0Lq = 50;
      static constexpr auto Territorytype0 = 270;
      static constexpr auto Territorytype1 = 141;

   public:
      ManWil005() :
         EventScript( 66086 ){}; 

   void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
   {
      auto actor = Event::mapEventActorToRealActor( static_cast< uint32_t >( actorId ) );

      if( actor == Actor0 && !player.hasQuest( getId() ) )
      {
         Scene00000( player );
      }
      if( actor == Actor0 && player.getQuestSeq( getId() ) == SeqFinish )
      {
         Scene00006( player );
      }
      if( actor == Actor1 )
      {
         Scene00002( player );
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
                           if (result.param2 == 1)
                           {
                              Scene00001(player);
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
                           Scene00003( player );
                         } );
   }

   void Scene00003( Entity::Player& player )
   {
      player.playScene( getId(), 3, HIDE_HOTBAR,
                         [ & ]( Entity::Player& player, const Event::SceneResult& result )
                         {
                           if( result.param2 == 1 )
                           {
                              player.updateQuest( getId(), SeqFinish );
                              player.sendNotice( "QuestBattle actually disabled, goat said it...it's not my fault!" );
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
      player.playScene( getId(), 5, HIDE_HOTBAR,
                         [ & ]( Entity::Player& player, const Event::SceneResult& result )
                         {
                         } );
   }

   void Scene00006( Entity::Player& player )
   {
      player.playScene( getId(), 6, SET_EOBJ_BASE | HIDE_HOTBAR | INVIS_EOBJ,
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
};

