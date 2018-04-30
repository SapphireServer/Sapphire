#include <Script/NativeScriptApi.h>
#include <Actor/Player.h>
#include "Event/EventHelper.h"
#include <ScriptObject.h>

// Quest Script: SubFst003_00026
// Quest Name: Once Bitten, Twice Shy
// Quest ID: 65562
// Start NPC: 1000297
// End NPC: 1000315

class SubFst003 : public EventScript
{
   private:
      // Basic quest information 
      // Quest vars / flags used
      // GetQuestUI8AL
      // GetQuestUI8BH

      enum Sequence : uint8_t
      {
         Seq0 = 0,
         SeqFinish = 255,
      };

      // Quest rewards 
      static constexpr auto RewardExpFactor = 50;
      static constexpr auto RewardGil = 118;

      // Entities found in the script data of the quest
      static constexpr auto Actor0 = 1000297;
      static constexpr auto Actor1 = 1000315;
      static constexpr auto Item0 = 2000028;
      static constexpr auto Seq0Actor0 = 0;
      static constexpr auto Seq1Actor1 = 1;
      static constexpr auto Seq1Actor1Npctradeno = 99;
      static constexpr auto Seq1Actor1Npctradeok = 100;

   public:
      SubFst003( ) : EventScript( 65562 )
      { }; 
      ~SubFst003( )
      { }; 

      void onTalk(uint32_t eventId, Entity::Player& player, uint64_t actorId) override
      {
         auto actor = Event::mapEventActorToRealActor(actorId);

         if (actor == SubFst003::Actor0)
         {
            Scene00000(player);
         }
         else if (actor == SubFst003::Actor1 && player.getQuestUI8AL(m_id) == 1)
         {
            Scene00001(player);
         }
      }

   private:

   void Scene00000(Entity::Player& player)
   {
      player.playScene(m_id, 0, 8192,
         [&](Entity::Player& player, const Event::SceneResult& result)
      {
         if (result.param2 == 1) // accept quest
         {
            player.updateQuest(m_id, 255);
            player.setQuestUI8AL(m_id, 1);
         }
      });
   }

   void Scene00001(Entity::Player& player)
   {
      player.playScene(m_id, 1, 8192,
         [&](Entity::Player& player, const Event::SceneResult& result)
      {
         if (result.param2 == 1)
         {
            Scene00100(player);
         }
         else
         {
            Scene00099(player);
         }
      });
   }

   void Scene00099( Entity::Player& player )
   {
      player.playScene(m_id, 99, 8192,
         [&](Entity::Player& player, const Event::SceneResult& result)
         {
            player.playScene(m_id, 99, 0, 0, 0);
         });
   }

   void Scene00100( Entity::Player& player )
   {
      player.playScene(m_id, 100, 8192,
         [&](Entity::Player& player, const Event::SceneResult& result)
         {
            player.sendQuestMessage(m_id, 1, 0, 0, 0);
            player.setQuestUI8BH(m_id, 1);
            player.setQuestUI8AL(m_id, 0);

            if (player.getQuestUI8BH(m_id) == 1)
            {
               if (player.giveQuestRewards(m_id, 0))
               {
                  player.finishQuest(m_id);
               }
            }
         });
   }
};

