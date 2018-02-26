#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class Sastasha : public InstanceContentScript
{
private:
   static void exitOnTalk( Entity::Player& player, uint64_t actorId )
   {
      player.sendDebug( "actor: " + std::to_string( actorId ) );
   }

public:
   Sastasha() : InstanceContentScript( 4 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      auto exit = instance->registerEObj( "Exit", EXIT_OBJECT, 0, EXIT_OBJECT_STATE, { -314.0f, 5.6f, 348.73f } );
      exit->setScale( 0.6f );
      exit->setOnTalkHandler( exitOnTalk );

      instance->registerEObj( "Entrance", START_CIRCLE, START_CIRCLE_MAPLINK, START_CIRCLE_STATE, { 361.0f, 46.0f, -225.0f } );

      auto memo = instance->registerEObj( "BloodyMemo", BLOODY_MEMO_1, 0, BLOODY_MEMO_STATE, { 320.81f, 47.86f, -130.78f } );
      memo->setScale( 0.6f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

private:
   static constexpr auto EXIT_OBJECT = 2000139;
   static constexpr auto EXIT_OBJECT_STATE = 4;

   static constexpr auto START_CIRCLE = 2000182;
   static constexpr auto START_CIRCLE_MAPLINK = 4096706;
   static constexpr auto START_CIRCLE_STATE = 5;

   static constexpr auto BLOODY_MEMO_1 = 2000212;
   static constexpr auto BLOODY_MEMO_2 = 2001548;
   static constexpr auto BLOODY_MEMO_3 = 2001549;
   static constexpr auto BLOODY_MEMO_STATE = 4;
};
