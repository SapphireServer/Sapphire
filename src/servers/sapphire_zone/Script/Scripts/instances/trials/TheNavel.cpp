#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class TheNavel : public InstanceContentScript
{
public:
   TheNavel() : InstanceContentScript( 20002 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      auto exit = Entity::EventObjectPtr( new Entity::EventObject( EXIT_OBJECT, 0, 4, { 0, 0, -10 } ) );
      instance->registerEObj( exit );

      auto start = Entity::EventObjectPtr( new Entity::EventObject( START_CIRCLE, 4236868, 5, { 0, 0, 24 } ) );
      instance->registerEObj( start );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

private:
   static constexpr auto EXIT_OBJECT = 2000139;
   static constexpr auto START_CIRCLE = 2000182;
};