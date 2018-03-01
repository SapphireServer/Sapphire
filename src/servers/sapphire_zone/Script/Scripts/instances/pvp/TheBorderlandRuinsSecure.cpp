#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class TheBorderlandRuinsSecure : public InstanceContentScript
{
public:
   TheBorderlandRuinsSecure() : InstanceContentScript( 50001 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Unknown0", 2005078, 5573675, 4, { -150.601807f, -15.195440f, 86.396042f }, 0.991760f );
      instance->registerEObj( "Unknown1", 2005079, 5573676, 4, { -160.177505f, -15.426880f, 111.877502f }, 0.991760f );
      instance->registerEObj( "Unknown2", 2005080, 5573677, 4, { -178.133102f, -15.426880f, 85.038406f }, 0.991760f );
      instance->registerEObj( "Unknown3", 2005081, 5573687, 4, { 147.790497f, -15.205700f, 85.606216f }, 0.991760f );
      instance->registerEObj( "Unknown4", 2005082, 5573688, 4, { 181.170303f, -15.426880f, 81.284790f }, 0.991760f );
      instance->registerEObj( "Unknown5", 2005083, 5573689, 4, { 160.730392f, -15.457460f, 117.518303f }, 0.991760f );
      instance->registerEObj( "Unknown6", 2005084, 5573690, 4, { -0.015320f, -15.426880f, -162.924103f }, 0.991760f );
      instance->registerEObj( "Unknown7", 2005085, 5573691, 4, { 19.010229f, -15.416970f, -200.015396f }, 1.000000f );
      instance->registerEObj( "Unknown8", 2005086, 5573692, 4, { -18.994471f, -15.426880f, -199.992905f }, 0.991760f );
      instance->registerEObj( "Unknown9", 2004187, 4724282, 4, { -0.007111f, 12.000000f, -386.299896f }, 1.000000f );
      instance->registerEObj( "Unknown10", 2004188, 4724284, 4, { 335.025513f, 12.000000f, 193.711899f }, 1.000000f );
      instance->registerEObj( "Unknown11", 2004189, 4724283, 4, { -334.556213f, 12.000000f, 193.274796f }, 1.000000f );
      instance->registerEObj( "Unknown12", 2004202, 4797506, 4, { -0.101569f, 30.000000f, 1.413736f }, 1.000000f );
      instance->registerEObj( "Magitekreaper", 2007710, 0, 4, { -0.135500f, 28.501801f, 18.021700f }, 1.000000f );
      instance->registerEObj( "Unknown13", 2007722, 6642830, 4, { 7.805808f, 29.000000f, 0.239120f }, 1.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};