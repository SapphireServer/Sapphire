#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class SealRockSeize : public InstanceContentScript
{
public:
   SealRockSeize() : InstanceContentScript( 50004 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Unknown0", 2005325, 5810980, 4, { 187.869202f, 8.108603f, 250.084000f }, 1.000000f );
      instance->registerEObj( "Unknown1", 2005326, 5810982, 4, { 57.053249f, 17.165449f, -249.904694f }, 1.000000f );
      instance->registerEObj( "Unknown2", 2005327, 5810983, 4, { -314.464996f, 41.657890f, 126.635803f }, 1.000000f );
      instance->registerEObj( "AllagantomelithA1", 2005338, 5821682, 4, { 18.148529f, 18.849100f, 267.572693f }, 0.991760f );
      instance->registerEObj( "Unknown3", 2005502, 5821737, 4, { 18.255230f, 16.804850f, 267.227814f }, 1.000000f );
      instance->registerEObj( "AllagantomelithA2", 2005339, 5821685, 4, { 8.120948f, 21.013821f, 167.772705f }, 0.991760f );
      instance->registerEObj( "Unknown4", 2005503, 5821738, 4, { 8.225257f, 19.763350f, 167.312195f }, 1.000000f );
      instance->registerEObj( "AllagantomelithA3", 2005340, 5821686, 4, { 96.414833f, 34.135899f, 108.177002f }, 0.991760f );
      instance->registerEObj( "Unknown5", 2005504, 5821739, 4, { 96.322990f, 33.288559f, 107.972397f }, 1.000000f );
      instance->registerEObj( "AllagantomelithA4", 2005341, 5821687, 4, { 200.335693f, 30.775141f, 68.234734f }, 0.991760f );
      instance->registerEObj( "Unknown6", 2005505, 5821740, 4, { 200.310593f, 29.688540f, 68.217537f }, 1.000000f );
      instance->registerEObj( "AllagantomelithB1", 2005342, 5821688, 4, { 157.733093f, 4.437783f, -49.087921f }, 0.991760f );
      instance->registerEObj( "Unknown7", 2005506, 5821741, 4, { 157.696793f, 2.356474f, -49.159088f }, 1.000000f );
      instance->registerEObj( "AllagantomelithB2", 2005343, 5821689, 4, { 51.290970f, 32.733749f, -82.673607f }, 0.991760f );
      instance->registerEObj( "Unknown8", 2005507, 5821743, 4, { 51.310070f, 31.154039f, -82.935127f }, 1.000000f );
      instance->registerEObj( "AllagantomelithB3", 2005344, 5821690, 4, { 74.829063f, 13.976150f, -16.412930f }, 0.991760f );
      instance->registerEObj( "Unknown9", 2005508, 5821744, 4, { 74.846779f, 11.294810f, -16.719721f }, 1.000000f );
      instance->registerEObj( "AllagantomelithB4", 2005345, 5821691, 4, { -47.222630f, 31.708929f, -92.240723f }, 0.991760f );
      instance->registerEObj( "Unknown10", 2005509, 5821746, 4, { -47.175869f, 29.272760f, -92.573776f }, 1.000000f );
      instance->registerEObj( "AllagantomelithC2", 2005346, 5821693, 4, { -163.868805f, 46.920021f, 1.751138f }, 0.991760f );
      instance->registerEObj( "Unknown11", 2005510, 5821747, 4, { -164.055405f, 45.557041f, 1.093665f }, 1.000000f );
      instance->registerEObj( "AllagantomelithD2", 2005347, 5821695, 4, { -32.930420f, 18.645050f, 19.141041f }, 0.991760f );
      instance->registerEObj( "Unknown12", 2005511, 5821748, 4, { -32.986580f, 17.328630f, 18.981670f }, 1.000000f );
      instance->registerEObj( "AllagantomelithD3", 2005348, 5821697, 4, { -62.119572f, 40.360111f, 48.813599f }, 0.991760f );
      instance->registerEObj( "Unknown13", 2005512, 5821749, 4, { -62.187111f, 38.493420f, 48.440479f }, 1.000000f );
      instance->registerEObj( "AllagantomelithC4", 2005349, 5821698, 4, { -148.508499f, 43.280338f, 161.458603f }, 0.991760f );
      instance->registerEObj( "Unknown14", 2005513, 5821750, 4, { -148.519196f, 41.333549f, 161.070908f }, 1.000000f );
      instance->registerEObj( "AllagantomelithC3", 2005350, 5821699, 4, { -167.072998f, 26.487570f, 71.059898f }, 0.991760f );
      instance->registerEObj( "Unknown15", 2005514, 5821751, 4, { -167.089294f, 24.449400f, 70.683212f }, 1.000000f );
      instance->registerEObj( "AllagantomelithC1", 2005351, 5821700, 4, { -120.087196f, 28.019110f, -46.859772f }, 0.991760f );
      instance->registerEObj( "Unknown16", 2005515, 5821752, 4, { -120.122597f, 27.122120f, -47.061981f }, 1.000000f );
      instance->registerEObj( "AllagantomelithD1", 2005352, 5821701, 4, { 15.841110f, 19.797770f, 101.591301f }, 0.991760f );
      instance->registerEObj( "Unknown17", 2005516, 5821753, 4, { 15.812600f, 18.748220f, 101.435699f }, 1.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};