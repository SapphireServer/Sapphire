#include <Script/NativeScriptApi.h>
#include <Actor/Player.h>
#include "Event/EventHelper.h"
#include <ScriptObject.h>

// Quest Script: SubSea001_00111
// Quest Name: Making a Name
// Quest ID: 65647
// Start NPC: 1002698
// End NPC: 1003604

class SubSea001 : public EventScript
{
private:
   // Basic quest information 
   // Quest vars / flags used
   // GetQuestBitFlag8
   // GetQuestUI8AL
   // GetQuestUI8BH

   enum Sequence : uint8_t
   {
      Seq0 = 0,
      Seq1 = 1,
      Seq2 = 2,
      SeqFinish = 255,
   };

   // Quest rewards 
   static constexpr auto RewardExpFactor = 50;
   static constexpr auto RewardItem = 4551;
   static constexpr auto RewardItemCount = 2;

   // Entities found in the script data of the quest
   static constexpr auto Actor0 = 1002698;
   static constexpr auto Actor1 = 1000969;
   static constexpr auto Actor2 = 1003604;
   static constexpr auto Eobject0 = 2001563;
   static constexpr auto Eobject1 = 2001564;
   static constexpr auto Eobject2 = 2001565;
   static constexpr auto Eobject3 = 2001566;
   static constexpr auto Eobject4 = 2001567;
   static constexpr auto Eobject5 = 2001568;
   static constexpr auto EventActionProcess = 14;
   static constexpr auto Item0 = 2000447;
   static constexpr auto Poprange0 = 4161445;
   static constexpr auto Quest0 = 65644;
   static constexpr auto Quest1 = 65645;
   static constexpr auto Territorytype0 = 129;

public:
   SubSea001() : EventScript(65647)
   {};
   ~SubSea001()
   {};

   void onTalk(uint32_t eventId, Entity::Player& player, uint64_t actorId) override
   {
      auto actor = Event::mapEventActorToRealActor(actorId);
      auto currentCC = player.getQuestUI8AL(getId());

      auto despawn1 = player.getQuestUI8FL(getId());
      auto despawn2 = player.getQuestUI8FH(getId());

      if (actor == SubSea001::Actor0)
      {
         Scene00000(player);
      }
      else if (actor == SubSea001::Actor1)
      {
         Scene00002(player);
      }
      else if (actor == SubSea001::Actor2)
      {
         Scene00016(player);
      }
      //EOBJECTS CHECK
      else if (actor == SubSea001::Eobject0) 
      {
         player.eventActionStart(getId(), 0x0E,
            [&](Entity::Player& player, uint32_t eventId, uint64_t additional)
         {
            despawn2 = despawn2 | 8;
            player.setQuestUI8FL(getId(), despawn2);
            Scene00003(player);
         },
            [&](Entity::Player& player, uint32_t eventId, uint64_t additional)
         {},
            eventId);
      }
      else if (actor == SubSea001::Eobject1) 
      {
         player.eventActionStart(getId(), 0x0E,
            [&](Entity::Player& player, uint32_t eventId, uint64_t additional)
         {
            despawn2 = despawn2 | 4;
            player.setQuestUI8FL(getId(), despawn2);
            Scene00005(player);
         },
            [&](Entity::Player& player, uint32_t eventId, uint64_t additional)
         {},
            eventId);
      }
      else if (actor == SubSea001::Eobject2) 
      {
         player.eventActionStart(getId(), 0x0E,
            [&](Entity::Player& player, uint32_t eventId, uint64_t additional)
         {
            despawn2 = despawn2 | 2;
            player.setQuestUI8FL(getId(), despawn2);
            Scene00007(player);
         },
            [&](Entity::Player& player, uint32_t eventId, uint64_t additional)
         {},
            eventId);
      }
      else if (actor == SubSea001::Eobject3) 
      {
         player.eventActionStart(getId(), 0x0E,
            [&](Entity::Player& player, uint32_t eventId, uint64_t additional)
         {
            despawn2 = despawn2 | 1;
            player.setQuestUI8FL(getId(), despawn2);
            Scene00009(player);
         },
            [&](Entity::Player& player, uint32_t eventId, uint64_t additional)
         {},
            eventId);
      }
      else if (actor == SubSea001::Eobject4)
      {
         player.eventActionStart(getId(), 0x0E,
            [&](Entity::Player& player, uint32_t eventId, uint64_t additional)
         {
            despawn2 = despawn2 | 8;
            player.setQuestUI8FL(getId(), despawn2);
            Scene00011(player);
         },
            [&](Entity::Player& player, uint32_t eventId, uint64_t additional)
         {},
            eventId);
      }
      else if (actor == SubSea001::Eobject5)
      {
         player.eventActionStart(getId(), 0x0E,
            [&](Entity::Player& player, uint32_t eventId, uint64_t additional)
         {
            despawn2 = despawn2 | 4;
            player.setQuestUI8FL(getId(), despawn2);
            Scene00013(player);
         },
            [&](Entity::Player& player, uint32_t eventId, uint64_t additional)
         {},
            eventId);
      }
   };

private:

   void checkQuestcompletion(Entity::Player& player, uint32_t varIdx, uint32_t actorId)
   {
      auto currentCC = player.getQuestUI8AL(getId());

      if (varIdx == 1)
      {
         player.sendQuestMessage(getId(), 0, 2, currentCC + 1, 6);//sendquestMessage(eventId, 0, 2, currVegetal + 1, 6);

         if (currentCC + 1 == 6)
         {
            player.updateQuest(getId(), SeqFinish);//questUpdate(eventId, SubFst015.SEQ_FINISH);
         }
         else
         {
            player.setQuestUI8AL(getId(), currentCC + 1);
         }
      }

      /*auto eobj = Event::mapEventActorToRealActor(actorId);
      auto currentCC = player.getQuestUI8BH(getId());

      auto despawn1 = player.getQuestUI8FL(getId());
      auto despawn2 = player.getQuestUI8FH(getId());

      //if(varIdx == 0)
      if (eobj == SubSea001::Eobject0 && varIdx == 0)
      {
         despawn2 = despawn2 | 8;
         player.setQuestUI8FH(getId(), despawn2);
      }
      //if (varIdx == 1)
      else if (eobj == SubSea001::Eobject1 && varIdx == 1)
      {
         despawn2 = despawn2 | 4;
         player.setQuestUI8FH(getId(), despawn2);
      }
      //if (varIdx == 2)
      else if (eobj == SubSea001::Eobject2 && varIdx == 2)
      {
         despawn2 = despawn2 | 2;
         player.setQuestUI8FH(getId(), despawn2);
      }
      //if (varIdx == 3)
      else if (eobj == SubSea001::Eobject3 && varIdx == 3)
      {
         despawn2 = despawn2 | 1;
         player.setQuestUI8FH(getId(), despawn2);
      }
      //if(varIdx == 4)
      else if (eobj == SubSea001::Eobject4 && varIdx == 4)
      {
         despawn2 = despawn2 | 8;
         player.setQuestUI8FH(getId(), despawn2);
      }
      //if(varIdx == 5)
      else if (eobj == SubSea001::Eobject5 && varIdx == 5)
      {
         despawn2 = despawn2 | 4;
         player.setQuestUI8FH(getId(), despawn2);
      }

      player.sendQuestMessage(getId(), 0, 2, currentCC + 1, 6);//sendquestMessage(eventId, 0, 2, currVegetal + 1, 6);

      if (currentCC + 1 == 6)
      {
         player.updateQuest(getId(), SeqFinish);//questUpdate(eventId, SubFst015.SEQ_FINISH);
      }
      else
      {
         player.setQuestUI8BH(getId(), currentCC + 1);
      }*/
   };

   void Scene00000( Entity::Player& player )
   {
      player.playScene( getId(), 0, HIDE_HOTBAR,
         [&]( Entity::Player& player, const Event::SceneResult& result )
         {
            if( result.param2 == 1 )
               player.updateQuest( getId(), 1 );
         } );
   }

   void Scene00001( Entity::Player& player )
   {
      player.playScene( getId(), 1, HIDE_HOTBAR,
         [&]( Entity::Player& player, const Event::SceneResult& result )
         {
         } );
   }

   void Scene00002( Entity::Player& player )
   {
      player.playScene( getId(), 2, HIDE_HOTBAR,
         [&]( Entity::Player& player, const Event::SceneResult& result )
         {
            if( player.hasQuest(65644) && result.param2 == 1 )
            {
               player.updateQuest( getId(), 2);
               player.changePosition( 10, 21, 13, -2 );
               player.forceZoneing( Territorytype0 ); // teleport to real limsa
            }
            else return;
         } );
   }

   void Scene00003( Entity::Player& player )
   {
      player.playScene( getId(), 3, HIDE_HOTBAR,
         [&]( Entity::Player& player, const Event::SceneResult& result )
         {
            Scene00004(player);
         } );
   }

   void Scene00004( Entity::Player& player )
   {
      player.playScene( getId(), 4, HIDE_HOTBAR,
         [&]( Entity::Player& player, const Event::SceneResult& result )
         {
            player.playScene(getId(), 4, 0, 0, 0);
         } );
   }

   void Scene00005( Entity::Player& player )
   {
      player.playScene( getId(), 5, HIDE_HOTBAR,
         [&]( Entity::Player& player, const Event::SceneResult& result )
         {
            Scene00006(player);
         } );
   }

   void Scene00006( Entity::Player& player )
   {
      player.playScene( getId(), 6, HIDE_HOTBAR,
         [&]( Entity::Player& player, const Event::SceneResult& result )
         {
            player.playScene(getId(), 6, 0, 0, 0);
         } );
   }

   void Scene00007( Entity::Player& player )
   {
      player.playScene( getId(), 7, HIDE_HOTBAR,
         [&]( Entity::Player& player, const Event::SceneResult& result )
         {
            Scene00008(player);
         } );
   }

   void Scene00008( Entity::Player& player )
   {
      player.playScene( getId(), 8, HIDE_HOTBAR,
         [&]( Entity::Player& player, const Event::SceneResult& result )
         {
            player.playScene(getId(), 8, 0, 0, 0);
         } );
   }

   void Scene00009( Entity::Player& player )
   {
      player.playScene( getId(), 9, HIDE_HOTBAR,
         [&]( Entity::Player& player, const Event::SceneResult& result )
         {
            Scene00010(player);
         } );
   }

   void Scene00010( Entity::Player& player )
   {
      player.playScene( getId(), 10, HIDE_HOTBAR,
         [&]( Entity::Player& player, const Event::SceneResult& result )
         {
            player.playScene(getId(), 10, 0, 0, 0);
         } );
   }

   void Scene00011( Entity::Player& player )
   {
      player.playScene( getId(), 11, HIDE_HOTBAR,
         [&]( Entity::Player& player, const Event::SceneResult& result )
         {
            Scene00012(player);
         } );
   }

   void Scene00012( Entity::Player& player )
   {
      player.playScene( getId(), 12, HIDE_HOTBAR,
         [&]( Entity::Player& player, const Event::SceneResult& result )
         {
            player.playScene(getId(), 12, 0, 0, 0);
         } );
   }

   void Scene00013( Entity::Player& player )
   {
      player.playScene( getId(), 13, HIDE_HOTBAR,
         [&]( Entity::Player& player, const Event::SceneResult& result )
         {
            Scene00014(player);
         } );
   }

   void Scene00014( Entity::Player& player )
   {
      player.playScene( getId(), 14, HIDE_HOTBAR,
         [&]( Entity::Player& player, const Event::SceneResult& result )
         {
            player.playScene(getId(), 14, 0, 0, 0);
         } );
   }

   void Scene00015( Entity::Player& player )
   {
      player.playScene( getId(), 15, HIDE_HOTBAR,
         [&]( Entity::Player& player, const Event::SceneResult& result )
         {
         } );
   }

   void Scene00016( Entity::Player& player )
   {
      player.playScene( getId(), 16, HIDE_HOTBAR,
         [&]( Entity::Player& player, const Event::SceneResult& result )
         {
            if( result.param2 == 1 )
            {
               Scene00017( player );
            }
            else return;
         } );
   }

   void Scene00017( Entity::Player& player )
   {
      player.playScene( getId(), 17, HIDE_HOTBAR,
         [&]( Entity::Player& player, const Event::SceneResult& result )
         {
            player.setQuestUI8BH( getId(), 0 );

            if( player.giveQuestRewards( getId(), 0 ) )
               player.finishQuest( getId() );
         } );
   }

};

