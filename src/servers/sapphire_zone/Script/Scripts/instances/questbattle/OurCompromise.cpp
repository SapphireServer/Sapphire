#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class OurCompromise : public InstanceContentScript
{
public:
   OurCompromise() : InstanceContentScript( 5020 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Unknown0", 2007457, 6941254, 4, { -613.766602f, 59.266399f, -460.085205f }, 1.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};