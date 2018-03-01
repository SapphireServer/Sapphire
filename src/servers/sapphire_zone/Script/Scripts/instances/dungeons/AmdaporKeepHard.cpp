#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class AmdaporKeepHard : public InstanceContentScript
{
public:
   AmdaporKeepHard() : InstanceContentScript( 29 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Unknown0", 2002872, 5040923, 4, { 203.452301f, 0.116688f, 208.657593f }, 1.000000f );
      instance->registerEObj( "Unknown1", 2002735, 0, 4, { 199.471802f, 0.116693f, 210.128204f }, 1.000000f );
      instance->registerEObj( "Unknown2", 2005153, 5619221, 4, { 198.706802f, -20.000010f, 229.113907f }, 1.000000f );
      instance->registerEObj( "Unknown3", 2004696, 5009720, 4, { -200.316895f, -4.301562f, -43.621670f }, 1.000000f );
      instance->registerEObj( "Unknown4", 2004697, 5009721, 4, { -47.771290f, -0.000000f, -71.658272f }, 1.000000f );
      instance->registerEObj( "Unknown5", 2004698, 5031991, 4, { -125.087196f, -2.000000f, 28.417601f }, 1.000000f );
      instance->registerEObj( "Unknown6", 2004699, 5031992, 4, { -104.790604f, -2.000000f, 47.174728f }, 1.000000f );
      instance->registerEObj( "Unknown7", 2004700, 0, 4, { 2.343430f, 48.179089f, -2.083742f }, 1.000000f );
      instance->registerEObj( "Unknown8", 2004702, 5009732, 4, { 125.604897f, 43.999989f, 3.999085f }, 1.000000f );
      instance->registerEObj( "Unknown9", 2004701, 0, 4, { 149.666000f, 44.200001f, -0.006115f }, 1.000000f );
      instance->registerEObj( "Unknown10", 2004703, 5010816, 4, { 196.927399f, 44.000019f, -101.381798f }, 1.000000f );
      instance->registerEObj( "Unknown11", 2004704, 5032163, 4, { 199.696106f, 44.000000f, -181.197006f }, 1.000000f );
      instance->registerEObj( "Aetherialflow", 2004705, 5032164, 4, { 199.682800f, 44.163898f, -180.392395f }, 1.000000f );
      instance->registerEObj( "Fellorb", 2004706, 5009746, 4, { 200.094101f, -0.000008f, 0.050249f }, 1.000000f );
      instance->registerEObj( "Aetherialflow", 2004707, 5033533, 4, { 199.899506f, 0.000000f, -3.297300f }, 1.000000f );
      instance->registerEObj( "Unknown12", 2004768, 5033548, 4, { 210.649307f, 0.116687f, -6.120441f }, 1.000000f );
      instance->registerEObj( "Unknown13", 2004769, 5033549, 4, { 189.489807f, 0.116688f, -6.804901f }, 1.000000f );
      instance->registerEObj( "Unknown14", 2004770, 5033551, 4, { 204.506500f, 0.116687f, 9.902725f }, 1.000000f );
      instance->registerEObj( "Unknown15", 2004708, 5034801, 4, { -119.510101f, -2.400002f, 18.885540f }, 1.000000f );
      instance->registerEObj( "Unknown16", 2002872, 5034800, 4, { -130.314606f, -2.400000f, -18.221069f }, 1.000000f );
      instance->registerEObj( "Unknown17", 2002735, 0, 4, { -125.041801f, -1.964380f, -20.543480f }, 1.000000f );
      instance->registerEObj( "Unknown18", 2004996, 5390927, 4, { -112.845497f, -2.400000f, 12.122500f }, 1.000000f );
      instance->registerEObj( "Unknown19", 2004997, 5390928, 4, { -112.845497f, -2.400000f, -12.378100f }, 1.000000f );
      instance->registerEObj( "Unknown20", 2004998, 5390929, 4, { -137.250000f, -2.400000f, 12.122500f }, 1.000000f );
      instance->registerEObj( "Unknown21", 2004999, 5390930, 4, { -137.396194f, -2.400000f, -12.366500f }, 1.000000f );
      instance->registerEObj( "Unknown22", 2004782, 5038257, 4, { 198.459198f, 43.991699f, -172.369705f }, 1.000000f );
      instance->registerEObj( "Unknown23", 2002872, 5038255, 4, { 197.802597f, 43.991699f, -125.932701f }, 1.000000f );
      instance->registerEObj( "Unknown24", 2002735, 0, 4, { 199.511703f, 44.022221f, -130.601303f }, 1.000000f );
      instance->registerEObj( "Entrance", 2000182, 5018466, 5, { -255.724792f, -9.199999f, -5.249732f }, 1.000000f );
      instance->registerEObj( "Shortcut", 2000700, 0, 4, { -252.173401f, -9.199999f, 5.737248f }, 1.000000f );
      instance->registerEObj( "Exit", 2000139, 0, 4, { 200.798599f, -0.000008f, 240.880905f }, 1.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};