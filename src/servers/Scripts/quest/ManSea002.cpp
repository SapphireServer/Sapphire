#include <Script/NativeScriptApi.h>
#include <Actor/Player.h>
#include "Event/EventHelper.h"
#include "../ScriptObject.h"

// Quest Script: ManSea002_00108
// Quest Name: Close to Home
// Quest ID: 65644
// Start NPC: 1002697
// End NPC: 1000972

class ManSea002 : public EventScript
{
private:
   static constexpr auto SEQ_0 = 0;
   static constexpr auto SEQ_1 = 1;
   static constexpr auto SEQ_FINISH = 255;


   static constexpr auto ACTOR0 = 1002697;
   static constexpr auto ACTOR1 = 1001217;
   static constexpr auto ACTOR2 = 1000926;
   static constexpr auto ACTOR3 = 1000972;
   static constexpr auto AETHERYTE0 = 8;
   static constexpr auto BIND_ACTOR0 = 6229226;
   static constexpr auto ITEM0 = 2000104;
   static constexpr auto LOC_ACTOR1 = 1001023;
   static constexpr auto LOC_FACE0 = 604;
   static constexpr auto LOC_FACE1 = 605;
   static constexpr auto LOC_POS_CAM1 = 4106696;
   static constexpr auto LOC_POS_CAM2 = 4106698;
   static constexpr auto REWARD0 = 1;
   static constexpr auto SCREENIMAGE0 = 14;
   static constexpr auto UNLOCK_DESION = 14;

public:
   ManSea002() : EventScript( 65644 )
   {}
   ~ManSea002()
   {};

   void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
   {
      auto actor = Event::mapEventActorToRealActor( static_cast<uint32_t>( actorId ) );

      if( actor == ACTOR0 )
         Scene00000( player );
   }

private:

   void Scene00000( Entity::Player& player )
   {
      player.playScene( getId(), 0, HIDE_HOTBAR,
         [&]( Entity::Player& player, const Event::SceneResult& result )
      {
         if( result.param2 == 1 ) // accept quest
            Scene00001( player );
      } );
   }

   void Scene00001( Entity::Player& player )
   {
      player.playScene( getId(), 1, FADE_OUT | CONDITION_CUTSCENE | HIDE_UI,
         [&]( Entity::Player& player, const Event::SceneResult& result )
      {
         // on quest accept
         player.updateQuest( getId(), 1 );
         player.setQuestUI8CH( getId(), 1 ); // receive key item
      } );
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

      player.playScene( getId(), 3, NONE, callback);
   }

   void Scene00004( Entity::Player& player )
   {
      auto callback = [&]( Entity::Player& player, const Event::SceneResult& result )
      {

      };

      player.playScene( getId(), 4, NONE, callback);
   }

   void Scene00005( Entity::Player& player )
   {
      auto callback = [&]( Entity::Player& player, const Event::SceneResult& result )
      {

      };

      player.playScene( getId(), 5, NONE, callback);
   }

   void Scene00006( Entity::Player& player )
   {
      auto callback = [&]( Entity::Player& player, const Event::SceneResult& result )
      {

      };

      player.playScene( getId(), 6, NONE, callback);
   }

   void Scene00007( Entity::Player& player )
   {
      auto callback = [&]( Entity::Player& player, const Event::SceneResult& result )
      {

      };

      player.playScene( getId(), 7, NONE, callback);
   }
};