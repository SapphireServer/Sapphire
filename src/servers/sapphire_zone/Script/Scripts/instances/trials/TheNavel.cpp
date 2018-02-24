#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class TheNavel : public InstanceContentScript
{
public:
   TheNavel() : InstanceContentScript( 20002 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      Common::FFXIVARR_POSITION3 pos = { 0, 0, -10 };
      auto exit = Entity::make_EventObject( EXIT_OBJECT, 0, EXIT_OBJECT_STATE, pos, "Exit" );
      instance->registerEObj( exit );

      Common::FFXIVARR_POSITION3 pos1 = { 0, 0, 24 };
      auto start = Entity::make_EventObject( START_CIRCLE, START_CIRCLE_MAPLINK, START_CIRCLE_STATE, pos1, "Entrance" );
      instance->registerEObj( start );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

private:
   static constexpr auto EXIT_OBJECT = 2000139;
   static constexpr auto EXIT_OBJECT_STATE = 4;

   static constexpr auto START_CIRCLE = 2000182;
   static constexpr auto START_CIRCLE_MAPLINK = 4236868;
   static constexpr auto START_CIRCLE_STATE = 5;
};