#include <ScriptObject.h>
#include <Zone/InstanceContent.h>
#include <boost/make_shared.hpp>
class TheNavel : public InstanceContentScript
{
public:
   TheNavel() : InstanceContentScript( 20002 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      Common::FFXIVARR_POSITION3 pos = { 0, 0, -10 };
      auto exit = Entity::make_EventObject( EXIT_OBJECT, 0, 4, pos, "Entrance" );
      instance->registerEObj( exit );

      Common::FFXIVARR_POSITION3 pos1 = { 0, 0, 24 };
      auto start = Entity::make_EventObject( START_CIRCLE, 4236868, 5, pos1, "Exit" );
      instance->registerEObj( start );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

private:
   static constexpr auto EXIT_OBJECT = 2000139;
   static constexpr auto START_CIRCLE = 2000182;
};