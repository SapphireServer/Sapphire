#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class TheThousandMawsOfTotoRak : public InstanceContentScript
{
public:
   TheThousandMawsOfTotoRak() : InstanceContentScript( 1 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      instance->registerEObj( "Exit", EXIT_OBJECT, 0, EXIT_OBJECT_STATE, { 237, -39, -144 } );
      instance->getEObjByName( "Exit" )->setScale( 0.6f );
      instance->registerEObj( "Entrance", START_CIRCLE, START_CIRCLE_MAPLINK, START_CIRCLE_STATE, { -322, 12, -78 } );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

private:
   static constexpr auto EXIT_OBJECT = 2000683;
   static constexpr auto EXIT_OBJECT_STATE = 4;

   static constexpr auto START_CIRCLE = 2000182;
   static constexpr auto START_CIRCLE_MAPLINK = 4127435;
   static constexpr auto START_CIRCLE_STATE = 5;
};