#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class TheFeast4on4LightParty : public InstanceContentScript
{
public:
   TheFeast4on4LightParty() : InstanceContentScript( 40012 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Unknown0", 2006819, 6218908, 4, { -89.012909f, 8.477110f, -0.326954f }, 1.000000f );
      instance->registerEObj( "Unknown1", 2006818, 6218909, 4, { 95.872437f, 8.468750f, -0.320496f }, 0.991760f );
      instance->registerEObj( "Unknown2", 2002618, 6220121, 4, { -78.605072f, 0.920299f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown3", 2002618, 6220123, 4, { 79.651703f, 0.811267f, -0.306571f }, 0.991760f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};