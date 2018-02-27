#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class Sastasha : public InstanceContentScript
{
public:
   Sastasha() : InstanceContentScript( 4 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Unknown0", 2000211, 0, 4, { 367.827087f, 47.400051f, -226.694305f }, 4.714991f );
      instance->registerEObj( "Unknown1", 2001504, 4323996, 4, { 94.597588f, 26.865030f, -68.584061f }, 1.000000f );
      instance->registerEObj( "Unknown2", 2001505, 4323997, 4, { 95.510597f, 26.620729f, -67.853653f }, 1.000000f );
      instance->registerEObj( "Unknown3", 2001506, 3653862, 4, { -9.239832f, 24.789940f, 35.778252f }, 0.991760f );
      instance->registerEObj( "Unknown4", 2001507, 4035750, 4, { -2.841087f, 23.114571f, 38.090420f }, 0.991760f );
      instance->registerEObj( "Unknown5", 2001539, 3653864, 4, { -158.560898f, 8.099012f, 214.344803f }, 0.991760f );
      instance->registerEObj( "Unknown6", 2001540, 4056793, 4, { -163.598602f, 8.026373f, 214.030106f }, 0.991760f );
      instance->registerEObj( "Unknown7", 2001508, 4236989, 4, { -303.983612f, 5.576412f, 276.214111f }, 1.000000f );
      instance->registerEObj( "Unknown8", 2001509, 4236990, 4, { -305.302002f, 5.542851f, 275.750885f }, 1.000000f );
      instance->registerEObj( "Entrance", 2000182, 4096706, 5, { 361.881714f, 46.092751f, -225.181305f }, 1.000000f );
      instance->registerEObj( "Shortcut", 2000700, 0, 4, { 344.705688f, 43.781551f, -217.365997f }, 0.991760f );
      instance->registerEObj( "Exit", 2000139, 0, 4, { -314.279114f, 5.630589f, 348.735596f }, 0.900235f );
      instance->registerEObj( "Bluecoralformation", 2000213, 3668215, 4, { 75.869797f, 35.101421f, -32.537209f }, 0.930753f );
      instance->registerEObj( "Redcoralformation", 2000214, 3668214, 4, { 88.769371f, 31.135691f, -40.869640f }, 0.930753f );
      instance->registerEObj( "Greencoralformation", 2000215, 3668216, 4, { 64.988159f, 33.672821f, -56.690559f }, 0.991789f );
      instance->registerEObj( "Inconspicuousswitch", 2000216, 3653858, 4, { 62.907951f, 33.969521f, -31.172279f }, 1.000000f );
      instance->registerEObj( "Hiddendoor", 2000217, 3653517, 4, { 59.000000f, 32.000000f, -35.000000f }, 1.000000f );
      instance->registerEObj( "Giantclam", 2000222, 4208408, 4, { 181.170303f, 32.104599f, -128.069000f }, 0.991789f );
      instance->registerEObj( "Unknown10", 2000260, 4208409, 4, { 166.318695f, 30.735420f, -128.312103f }, 0.991789f );
      instance->registerEObj( "Unknown11", 2000261, 4208410, 4, { 158.800598f, 28.586321f, -76.340927f }, 0.991789f );
      instance->registerEObj( "Unknown12", 2000262, 4208411, 4, { 125.463402f, 29.260550f, -51.934608f }, 0.991789f );
      instance->registerEObj( "Unknown13", 2000263, 4208412, 4, { 126.070198f, 28.913260f, -99.908722f }, 1.000000f );
      instance->registerEObj( "Unknown14", 2000264, 4208413, 4, { 97.055313f, 27.081551f, -70.264381f }, 0.991789f );
      instance->registerEObj( "Bloodymemo", 2000212, 0, 4, { 320.812988f, 47.862450f, -130.776306f }, 0.600000f );
      instance->registerEObj( "Bloodymemo", 2001548, 0, 4, { 320.812988f, 47.862450f, -130.776306f }, 0.600000f );
      instance->registerEObj( "Bloodymemo", 2001549, 0, 4, { 320.812988f, 47.862450f, -130.776306f }, 0.600000f );
      instance->registerEObj( "Rambadedoor", 2000225, 3653865, 4, { -35.299999f, 24.000000f, 60.799999f }, 1.000000f );
      instance->registerEObj( "Captainsquarters", 2000227, 3687697, 4, { -95.044670f, 20.513069f, 172.039597f }, 0.991789f );
      instance->registerEObj( "WaveriderGate", 2000231, 3655909, 4, { -130.600006f, 16.000000f, 156.800003f }, 1.000000f );
      instance->registerEObj( "TheHole", 2000232, 3656260, 4, { -36.000000f, 16.500000f, 163.300003f }, 1.000000f );
      instance->registerEObj( "Rambadedoor", 2000236, 3655908, 4, { -190.000000f, 7.000000f, 252.000000f }, 1.000000f );
      instance->registerEObj( "Unknown15", 2000235, 3656262, 4, { -156.500000f, 8.600000f, 252.500000f }, 1.000000f );
      instance->registerEObj( "WaveriderGatekey", 2000255, 0, 4, { -95.515343f, 20.000000f, 177.197800f }, 1.000000f );
      instance->registerEObj( "KeytotheHole", 2000256, 0, 4, { -38.076599f, 17.232731f, 158.839401f }, 0.991760f );
      instance->registerEObj( "Captainsquarterskey", 2000250, 0, 4, { -100.625000f, 15.600010f, 137.150696f }, 1.000000f );
      instance->registerEObj( "Unknown16", 2000223, 4200832, 4, { -24.018980f, 18.475060f, 111.404900f }, 1.000000f );
      instance->registerEObj( "Unnaturalripples", 2000405, 3992454, 4, { -301.973206f, 6.500000f, 300.029388f }, 0.991789f );
      instance->registerEObj( "Unnaturalripples", 2000406, 3992452, 4, { -302.037598f, 6.500000f, 336.047302f }, 1.000000f );
      instance->registerEObj( "Unnaturalripples", 2000407, 3992449, 4, { -338.036499f, 6.500000f, 300.206512f }, 0.991789f );
      instance->registerEObj( "Unnaturalripples", 2000408, 3992453, 4, { -337.929596f, 6.500000f, 335.975311f }, 1.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};