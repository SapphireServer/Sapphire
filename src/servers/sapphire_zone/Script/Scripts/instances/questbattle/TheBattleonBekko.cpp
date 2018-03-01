#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class TheBattleonBekko : public InstanceContentScript
{
public:
   TheBattleonBekko() : InstanceContentScript( 5012 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Unknown0", 2008480, 6894787, 4, { 564.783630f, -60.304729f, -136.444901f }, 1.000000f );
      instance->registerEObj( "Unknown1", 2004541, 0, 4, { 800.087585f, 0.000000f, 44.317749f }, 1.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};