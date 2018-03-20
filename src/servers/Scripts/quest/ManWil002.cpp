#include <Script/NativeScriptApi.h>
#include <Actor/Player.h>
#include "Event/EventHelper.h"
#include "../ScriptObject.h"

// Quest Script: ManWil002_00568
// Quest Name: Close to Home
// Quest ID: 66104
// Start NPC: 1003988
// End NPC: 1001353

class ManWil002 : public EventScript
{
private:
   static constexpr auto SEQ_0 = 0;
   static constexpr auto SEQ_1 = 1;
   static constexpr auto SEQ_FINISH = 255;


   static constexpr auto ACTOR0 = 1003988;
   static constexpr auto ACTOR1 = 1002277;
   static constexpr auto ACTOR2 = 1003908;
   static constexpr auto ACTOR20 = 1001637;
   static constexpr auto ACTOR3 = 1001353;
   static constexpr auto AETHERYTE0 = 9;
   static constexpr auto BIND_ACTOR0 = 6229228;
   static constexpr auto ITEM0 = 2000386;
   static constexpr auto LOC_ACTION1 = 605;
   static constexpr auto LOC_ACTION2 = 1005;
   static constexpr auto LOC_MARKER_01 = 4009142;
   static constexpr auto LOC_MARKER_02 = 4009152;
   static constexpr auto LOC_POS_CAM1 = 4105872;
   static constexpr auto LOC_POS_CAM2 = 4105874;
   static constexpr auto LOC_POS_CAM3 = 4009150;
   static constexpr auto LOC_POS_CAM4 = 4143488;
   static constexpr auto POPRANGE0 = 4110794;
   static constexpr auto REWARD0 = 1;
   static constexpr auto SCREENIMAGE0 = 14;
   static constexpr auto SEQ_0_ACTOR0_LQ = 50;
   static constexpr auto TERRITORYTYPE0 = 130;

   void Scene00000( Entity::Player& player )
   {
      auto callback = [&]( Entity::Player& player, const Event::SceneResult& result )
      {
         if( result.param2 == 1 ) // accept quest
            Scene00050( player );
      };

      player.playScene( getId(), 0, HIDE_HOTBAR, 0, 0, callback );
   }

   void Scene00001( Entity::Player& player )
   {
      auto callback = [&]( Entity::Player& player, const Event::SceneResult& result )
      {

      };

      player.playScene( getId(), 1, NONE, callback );
   }

   void Scene00002( Entity::Player& player )
   {
      auto callback = [&]( Entity::Player& player, const Event::SceneResult& result )
      {

      };

      player.playScene( getId(), 2, NONE, callback );
   }

   void Scene00003( Entity::Player& player )
   {
      auto callback = [&]( Entity::Player& player, const Event::SceneResult& result )
      {

      };

      player.playScene( getId(), 3, NONE, callback );
   }

   void Scene00004( Entity::Player& player )
   {
      auto callback = [&]( Entity::Player& player, const Event::SceneResult& result )
      {

      };

      player.playScene( getId(), 4, NONE, callback );
   }

   void Scene00005( Entity::Player& player )
   {
      auto callback = [&]( Entity::Player& player, const Event::SceneResult& result )
      {

      };

      player.playScene( getId(), 5, NONE, callback );
   }

   void Scene00006( Entity::Player& player )
   {
      auto callback = [&]( Entity::Player& player, const Event::SceneResult& result )
      {

      };

      player.playScene( getId(), 6, NONE, callback );
   }

   void Scene00007( Entity::Player& player )
   {
      auto callback = [&]( Entity::Player& player, const Event::SceneResult& result )
      {

      };

      player.playScene( getId(), 7, NONE, callback );
   }

   void Scene00008( Entity::Player& player )
   {
      auto callback = [&]( Entity::Player& player, const Event::SceneResult& result )
      {

      };

      player.playScene( getId(), 8, NONE, callback );
   }

   void Scene00050( Entity::Player& player )
   {
      auto callback = [&]( Entity::Player& player, const Event::SceneResult& result )
      {
         // on quest accept
         player.updateQuest( getId(), 1 );
         player.setQuestUI8CH( getId(), 1 ); // receive key item

         // teleport to real gridania
         player.forceZoneing( 130 );
      };

      player.playScene( getId(), 50, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI, 0, 0, callback );
   }


public:
   ManWil002() : EventScript( 66104 )
   { }

   void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
   {
      auto actor = Event::mapEventActorToRealActor( static_cast< uint32_t >( actorId ) );

      if( actor == ACTOR0 )
         Scene00000( player );
   }
};