#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class TheNavel : public InstanceContentScript
{
public:
   TheNavel() : InstanceContentScript( 20002 )
   { }

   void onInit( InstanceContent& instance ) override
   {
      auto exit = new Entity::InstanceObject( EXIT_OBJECT, 0, { 0, 0, -10 } );
      instance.registerInstanceObj( Entity::InstanceObjectPtr( exit ) );

      auto start = new Entity::InstanceObject( START_CIRCLE, 4236868, { 0, 0, 24 } );
      instance.registerInstanceObj( Entity::InstanceObjectPtr( start ) );
   }

   void onUpdate( InstanceContent& instance, uint32_t currTime ) override
   {

   }

private:
   static constexpr auto EXIT_OBJECT = 2000139;
   static constexpr auto START_CIRCLE = 2000182;
};