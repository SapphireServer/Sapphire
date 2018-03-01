#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class TheDrownedCityofSkalla : public InstanceContentScript
{
public:
   TheDrownedCityofSkalla() : InstanceContentScript( 58 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Unknown0", 2002872, 7068116, 4, { 459.000000f, -14.000000f, 4.000000f }, 1.000000f );
      instance->registerEObj( "Unknown1", 2002735, 0, 4, { 459.000000f, -14.000000f, 4.000000f }, 1.000000f );
      instance->registerEObj( "Exit", 2000139, 0, 4, { 491.000000f, -14.000000f, 4.000000f }, 1.000000f );
      instance->registerEObj( "Unknown2", 2002872, 7068596, 4, { -245.000000f, -2.000000f, 4.000000f }, 1.000000f );
      instance->registerEObj( "Unknown3", 2002872, 7068599, 4, { -194.500000f, -2.000000f, 4.000000f }, 1.000000f );
      instance->registerEObj( "Unknown4", 2007457, 7072874, 4, { -220.044601f, -2.000000f, 3.151932f }, 1.000000f );
      instance->registerEObj( "Unknown5", 2009045, 0, 4, { -224.806396f, -2.000000f, 8.647594f }, 1.000000f );
      instance->registerEObj( "Unknown6", 2002735, 0, 4, { -245.000000f, -2.000000f, 4.000000f }, 1.400000f );
      instance->registerEObj( "Unknown7", 2002872, 7068491, 4, { 95.000000f, 9.000000f, 4.000000f }, 1.000000f );
      instance->registerEObj( "Unknown8", 2002735, 0, 4, { 95.000000f, 9.000000f, 4.000000f }, 1.400000f );
      instance->registerEObj( "Unknown9", 2002872, 7068496, 4, { 135.000000f, 9.000000f, 4.000000f }, 1.000000f );
      instance->registerEObj( "Unknown10", 2009046, 0, 4, { 111.907600f, 9.000000f, 4.017264f }, 1.000000f );
      instance->registerEObj( "Unknown11", 2007457, 7075163, 4, { -335.663391f, 1.815782f, -38.379379f }, 1.000000f );
      instance->registerEObj( "Unknown12", 2007457, 7075164, 4, { -324.520203f, 1.008244f, -28.697809f }, 1.000000f );
      instance->registerEObj( "Unknown13", 2007457, 7032771, 4, { -380.099701f, 5.500000f, -16.441790f }, 1.000000f );
      instance->registerEObj( "Unknown14", 2007457, 7075174, 4, { -298.365204f, 1.706293f, -25.538429f }, 1.000000f );
      instance->registerEObj( "Unknown15", 2007457, 7075175, 4, { -290.733002f, 1.250000f, -27.983721f }, 1.000000f );
      instance->registerEObj( "Unknown16", 2007457, 7065309, 4, { -273.437195f, 1.281705f, 3.216716f }, 1.000000f );
      instance->registerEObj( "Unknown17", 2007457, 7132450, 4, { -322.497589f, 1.008244f, -34.442020f }, 1.000000f );
      instance->registerEObj( "Unknown18", 2007457, 7132455, 4, { -293.498108f, 1.972912f, -19.170090f }, 1.000000f );
      instance->registerEObj( "Unknown19", 2007457, 7132456, 4, { -287.911407f, 1.972912f, -26.723471f }, 1.000000f );
      instance->registerEObj( "Unknown20", 2007457, 7034067, 4, { -67.254761f, 3.500000f, -34.435638f }, 1.000000f );
      instance->registerEObj( "Unknown21", 2007457, 7065310, 4, { 68.873291f, 7.500000f, 3.740700f }, 1.000000f );
      instance->registerEObj( "Unknown22", 2007457, 0, 4, { 133.644806f, 9.000000f, 3.453697f }, 1.000000f );
      instance->registerEObj( "Unknown23", 2007457, 7029084, 4, { 272.652802f, -12.000000f, 48.014309f }, 1.000000f );
      instance->registerEObj( "Unknown24", 2007457, 7032009, 4, { 276.325592f, -12.008910f, -34.378601f }, 0.991760f );
      instance->registerEObj( "Unknown25", 2007457, 7034222, 4, { 433.853088f, -15.937500f, 3.644273f }, 1.000000f );
      instance->registerEObj( "Entrance", 2000182, 7042417, 5, { -488.282501f, -3.750000f, 2.201033f }, 1.000000f );
      instance->registerEObj( "Shortcut", 2000700, 0, 4, { -457.918304f, -3.860892f, 14.784940f }, 1.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};