#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class TheSecondCoilofBahamutSavageTurn3 : public InstanceContentScript
{
public:
   TheSecondCoilofBahamutSavageTurn3() : InstanceContentScript( 30014 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Fragrantbloom", 2003342, 0, 4, { 5.540659f, -506.930115f, 105.670197f }, 1.000000f );
      instance->registerEObj( "Destination", 2003387, 0, 4, { 5.248638f, -506.929993f, 104.130501f }, 1.000000f );
      instance->registerEObj( "Sylphpodling", 2003348, 0, 4, { 4.584954f, -506.929993f, 106.997597f }, 1.000000f );
      instance->registerEObj( "Skybulb", 2003358, 0, 4, { 3.469964f, -506.929993f, 104.900299f }, 1.000000f );
      instance->registerEObj( "Destination", 2003289, 4681305, 4, { -28.488001f, -506.700012f, 105.307297f }, 1.000000f );
      instance->registerEObj( "Destination", 2003289, 4681302, 4, { -2.644600f, -506.700012f, 79.710602f }, 1.000000f );
      instance->registerEObj( "Destination", 2003289, 4681303, 4, { 23.007401f, -506.700012f, 105.309097f }, 1.000000f );
      instance->registerEObj( "Destination", 2003289, 4681304, 4, { -2.685100f, -506.700012f, 131.011307f }, 1.000000f );
      instance->registerEObj( "Entrance", 2000182, 4649322, 5, { 71.763351f, -505.710297f, -183.265305f }, 1.000000f );
      instance->registerEObj( "Shortcut", 2000700, 0, 4, { 78.751831f, -508.192688f, -166.063995f }, 0.991760f );
      instance->registerEObj( "Unknown1", 2003117, 4649426, 4, { 71.787033f, -523.938416f, -91.769341f }, 1.000000f );
      instance->registerEObj( "Unknown2", 2003149, 4649428, 4, { 71.647507f, -539.766907f, -10.543050f }, 1.000000f );
      instance->registerEObj( "Unknown3", 2003178, 4649429, 4, { -72.118347f, -523.848206f, -91.955490f }, 1.000000f );
      instance->registerEObj( "Unknown4", 2003179, 4649430, 4, { -71.857773f, -539.706909f, -11.043210f }, 1.000000f );
      instance->registerEObj( "Unknown5", 2003180, 4649427, 4, { 32.211380f, -491.286011f, -105.322304f }, 1.000000f );
      instance->registerEObj( "Unknown6", 2003187, 4649436, 4, { 31.604389f, -498.100800f, -68.374847f }, 1.000000f );
      instance->registerEObj( "Unknown7", 2003188, 4649435, 4, { 31.776440f, -506.867188f, -22.942039f }, 1.000000f );
      instance->registerEObj( "Unknown8", 2003196, 4649437, 4, { 31.800430f, -514.005920f, 12.637740f }, 1.000000f );
      instance->registerEObj( "Unknown9", 2003198, 4649442, 4, { -32.055038f, -491.285187f, -104.874397f }, 1.000000f );
      instance->registerEObj( "Unknown10", 2003200, 4649444, 4, { -31.019110f, -497.691315f, -68.166161f }, 1.000000f );
      instance->registerEObj( "Unknown11", 2003201, 4649443, 4, { -32.114700f, -507.132690f, -23.686880f }, 1.000000f );
      instance->registerEObj( "Unknown12", 2003202, 4649445, 4, { -32.647800f, -514.520386f, 12.987520f }, 1.000000f );
      instance->registerEObj( "Unknown13", 2003203, 4649441, 4, { 39.004780f, -451.620209f, -100.687401f }, 1.000000f );
      instance->registerEObj( "Unknown14", 2003204, 4649439, 4, { 36.536411f, -459.008911f, -57.215809f }, 1.000000f );
      instance->registerEObj( "Unknown15", 2003211, 4649440, 4, { 36.232590f, -468.665405f, -16.744450f }, 1.000000f );
      instance->registerEObj( "Unknown16", 2003212, 4649438, 4, { 39.456009f, -475.805695f, 24.956329f }, 1.000000f );
      instance->registerEObj( "Unknown17", 2003220, 4649449, 4, { -38.816181f, -450.369904f, -100.764801f }, 1.000000f );
      instance->registerEObj( "Unknown18", 2003272, 4649447, 4, { -39.033329f, -459.976013f, -57.518230f }, 1.000000f );
      instance->registerEObj( "Unknown19", 2003273, 4649448, 4, { -38.558640f, -467.593109f, -20.011221f }, 1.000000f );
      instance->registerEObj( "Unknown20", 2003274, 4649446, 4, { -39.651970f, -475.626709f, 24.849569f }, 1.000000f );
      instance->registerEObj( "Unknown21", 2003275, 4649434, 4, { 72.266907f, -442.713989f, -75.343910f }, 1.000000f );
      instance->registerEObj( "Unknown22", 2003286, 4649431, 4, { 71.894348f, -458.468506f, 5.267881f }, 1.000000f );
      instance->registerEObj( "Unknown23", 2003287, 4649432, 4, { -71.852654f, -442.697113f, -75.916992f }, 1.000000f );
      instance->registerEObj( "Unknown24", 2003288, 4649433, 4, { -71.777451f, -458.403107f, 4.927437f }, 1.000000f );
      instance->registerEObj( "Unknown25", 2002473, 4649110, 4, { 71.824219f, -515.343018f, -132.707794f }, 0.991760f );
      instance->registerEObj( "Unknown26", 2002474, 4649108, 4, { 71.847183f, -531.168091f, -51.265450f }, 1.000000f );
      instance->registerEObj( "Unknown27", 2002579, 4649109, 4, { 71.850891f, -546.907227f, 29.809669f }, 0.991760f );
      instance->registerEObj( "Boxofcrystals", 2002592, 4649105, 4, { -71.854797f, -515.314209f, -132.724899f }, 0.991760f );
      instance->registerEObj( "Boxofcrystals", 2002593, 4649103, 4, { -71.848587f, -531.122681f, -51.389240f }, 1.000000f );
      instance->registerEObj( "Boxofcrystals", 2002594, 4649104, 4, { -71.852577f, -547.315125f, 29.686489f }, 0.991760f );
      instance->registerEObj( "Unknown28", 2002885, 4649106, 4, { -0.000875f, -482.805389f, -84.219566f }, 0.991760f );
      instance->registerEObj( "Unknown29", 2002886, 4649107, 4, { -0.003072f, -498.601105f, -3.013031f }, 1.000000f );
      instance->registerEObj( "Unknown30", 2003453, 4672990, 4, { 0.015892f, -506.314087f, 46.485531f }, 1.000000f );
      instance->registerEObj( "Unknown31", 2002872, 4649551, 4, { -2.840854f, -506.553986f, 68.877274f }, 0.991760f );
      instance->registerEObj( "Unknown32", 2002735, 0, 4, { -2.788200f, -507.313385f, 68.893646f }, 1.000000f );
      instance->registerEObj( "Allaganterminal", 2003418, 4672991, 4, { -2.071490f, -506.798004f, 144.172394f }, 1.000000f );
      instance->registerEObj( "Frontalbulkhead", 2003420, 4649112, 4, { -0.091233f, -505.180695f, 26.463760f }, 1.000000f );
      instance->registerEObj( "Unknown33", 2003422, 4651265, 4, { -2.657619f, -506.929993f, 124.653297f }, 1.000000f );
      instance->registerEObj( "Unknown34", 2003677, 4681484, 4, { -2.678503f, -506.980103f, 84.769417f }, 1.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};