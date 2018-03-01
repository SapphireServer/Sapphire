#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class ContainmentBayZ1T9 : public InstanceContentScript
{
public:
   ContainmentBayZ1T9() : InstanceContentScript( 20043 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Unknown0", 2007719, 0, 4, { 5.447040f, 0.000002f, -9.308832f }, 1.000000f );
      instance->registerEObj( "Unknown1", 2007720, 0, 4, { 9.576125f, 0.000002f, -3.402662f }, 1.000000f );
      instance->registerEObj( "Unknown2", 2007716, 0, 4, { 11.420000f, 0.000004f, 11.783210f }, 1.000000f );
      instance->registerEObj( "Unknown3", 2007717, 0, 4, { -11.656410f, -0.000002f, 12.218210f }, 1.000000f );
      instance->registerEObj( "Unknown4", 2007718, 0, 4, { -17.805031f, 0.000000f, 4.207765f }, 1.000000f );
      instance->registerEObj( "Entrance", 2000182, 6625715, 5, { 0.000000f, 0.000000f, 14.500000f }, 1.000000f );
      instance->registerEObj( "Exit", 2000139, 0, 4, { 0.000000f, 0.000000f, -14.500000f }, 1.000000f );
      instance->registerEObj( "Unknown6", 2007689, 6621345, 4, { -3.765648f, 0.000001f, 14.953240f }, 1.000000f );
      instance->registerEObj( "Unknown7", 2007690, 6643541, 4, { -12.141200f, -0.000001f, 4.715301f }, 1.000000f );
      instance->registerEObj( "Unknown8", 2007691, 6621347, 4, { 5.404188f, 0.000000f, -14.762600f }, 1.000000f );
      instance->registerEObj( "Unknown9", 2007692, 6621352, 4, { 14.969930f, 0.000002f, -2.525420f }, 1.000000f );
      instance->registerEObj( "Unknown10", 2007693, 6621398, 4, { -1.996956f, 0.000000f, 6.613101f }, 1.000000f );
      instance->registerEObj( "Unknown11", 2007694, 6621516, 4, { 5.478731f, 0.000000f, 9.952977f }, 1.000000f );
      instance->registerEObj( "Unknown12", 2007695, 0, 4, { 5.515548f, 0.000000f, 11.770850f }, 1.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};