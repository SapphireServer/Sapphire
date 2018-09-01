#include <Actor/Player.h>
#include <Event/EventHelper.h>
#include <ScriptObject.h>

// Quest Script: SubSea050_00462
// Quest Name: On to Summerford
// Quest ID: 65998
// Start NPC: 1000972
// End NPC: 1002626

class SubSea050 : public EventScript
{
   private:
      // Basic quest information 
      // Quest vars / flags used

      enum Sequence : uint8_t
      {
         Seq0 = 0,
         SeqFinish = 255,
      };

      // Quest rewards 
      static constexpr auto RewardExpFactor = 200;
      uint16_t RewardItemOptional[3] = { 3762, 3764, 5824 };
      uint16_t RewardItemOptionalCount[3] = { 1, 1, 1 };

      // Entities found in the script data of the quest
      static constexpr auto Actor0 = 1000972;
      static constexpr auto Actor1 = 1002626;
      static constexpr auto LocActor0 = 1003289;
      static constexpr auto LocFace0 = 604;
      static constexpr auto LocFace1 = 617;
      static constexpr auto LocPosActor0 = 4201224;
      static constexpr auto LocPosCam1 = 4201231;
      static constexpr auto LocSe1 = 39;
      static constexpr auto LocSe2 = 40;

   public:
      SubSea050() : EventScript( 65998 )
      {}; 
      ~SubSea050()
      {}; 

   void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
   {
      auto actor = Event::mapEventActorToRealActor( static_cast< uint32_t >( actorId ) );

      if( actor == Actor0 )
      {
         Scene00000( player );
      }
      else if( actor == Actor1 )
      {
         Scene00001( player );
      }
   }

   private:

   void Scene00000( Entity::Player& player )
   {
      player.playScene( getId(), 0, HIDE_HOTBAR,
                         [ & ]( Entity::Player& player, const Event::SceneResult& result )
                         {
                            if( result.param2 == 1 )
                            {
                               player.updateQuest( getId(), SeqFinish );
                            }
                         } );
   }

   void Scene00001( Entity::Player& player )
   {
      player.playScene( getId(), 1, HIDE_HOTBAR,
                         [ & ]( Entity::Player& player, const Event::SceneResult& result )
                         {
                            Scene00002( player );
                         } );
   }

   void Scene00002( Entity::Player& player )
   {
      player.playScene( getId(), 2, SET_EOBJ_BASE | HIDE_HOTBAR | INVIS_EOBJ,
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
};

