#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class DunScaith : public InstanceContentScript
{
public:
   DunScaith() : InstanceContentScript( 30047 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Unknown0", 2002872, 6610729, 4, { 331.572388f, 2.765574f, 418.256012f }, 1.000000f );
      instance->registerEObj( "Unknown1", 2007602, 6610730, 4, { 266.946014f, 2.765530f, 420.309692f }, 0.991760f );
      instance->registerEObj( "Unknown2", 2007609, 6612545, 4, { 276.236511f, 2.869957f, 402.357910f }, 1.000000f );
      instance->registerEObj( "Unknown3", 2007610, 6612547, 4, { 291.404297f, 2.869957f, 402.158112f }, 1.000000f );
      instance->registerEObj( "Unknown4", 2007611, 6612549, 4, { 306.464600f, 2.869963f, 402.176208f }, 1.000000f );
      instance->registerEObj( "Unknown5", 2007612, 6612551, 4, { 321.436493f, 2.869970f, 402.213196f }, 1.000000f );
      instance->registerEObj( "Unknown6", 2007613, 6612544, 4, { 276.728699f, 2.869961f, 417.200195f }, 1.000000f );
      instance->registerEObj( "Unknown7", 2007614, 6612546, 4, { 291.491791f, 2.869957f, 417.279388f }, 1.000000f );
      instance->registerEObj( "Unknown8", 2007615, 6612548, 4, { 306.298187f, 2.869963f, 417.075897f }, 1.000000f );
      instance->registerEObj( "Unknown9", 2007616, 6612550, 4, { 321.398895f, 2.869969f, 417.089905f }, 1.000000f );
      instance->registerEObj( "Unknown10", 2007603, 6612604, 4, { 279.000000f, 2.869900f, 398.600006f }, 1.000000f );
      instance->registerEObj( "Unknown11", 2007604, 6612605, 4, { 305.000000f, 2.870000f, 398.600006f }, 1.000000f );
      instance->registerEObj( "Unknown12", 2007605, 6612606, 4, { 319.000000f, 2.870000f, 398.600006f }, 1.000000f );
      instance->registerEObj( "Unknown13", 2007606, 6612608, 4, { 287.000000f, 2.869900f, 420.600006f }, 1.000000f );
      instance->registerEObj( "Unknown14", 2007607, 6612609, 4, { 305.000000f, 2.870000f, 420.600006f }, 1.000000f );
      instance->registerEObj( "Unknown15", 2007608, 6612611, 4, { 315.000000f, 2.870000f, 420.600006f }, 1.000000f );
      instance->registerEObj( "Unknown16", 2007619, 6613747, 4, { 299.266815f, 2.869962f, 409.699585f }, 1.000000f );
      instance->registerEObj( "Unknown17", 2007617, 6584508, 4, { 255.549805f, 2.765237f, 401.452301f }, 1.000000f );
      instance->registerEObj( "Unknown18", 2007783, 0, 4, { 316.110107f, 2.869910f, 411.214813f }, 1.000000f );
      instance->registerEObj( "Unknown19", 2007791, 0, 4, { 329.623108f, 2.825000f, 409.616913f }, 1.250000f );
      instance->registerEObj( "Unknown20", 2002872, 6613229, 4, { -348.000000f, -7.000000f, 256.488800f }, 1.000000f );
      instance->registerEObj( "Unknown21", 2002587, 0, 4, { -350.000000f, -7.000000f, 255.088806f }, 1.400000f );
      instance->registerEObj( "Unknown22", 2007620, 0, 4, { -366.689606f, -7.003906f, 224.200806f }, 0.991760f );
      instance->registerEObj( "Unknown23", 2007621, 0, 4, { -361.958405f, -7.000000f, 224.734894f }, 1.000000f );
      instance->registerEObj( "Unknown24", 2002872, 6620377, 4, { -0.071279f, -600.000000f, -18.220051f }, 1.000000f );
      instance->registerEObj( "Unknown25", 2007630, 0, 4, { -4.827496f, -600.000000f, -58.405430f }, 1.000000f );
      instance->registerEObj( "Unknown26", 2007631, 0, 4, { 7.122071f, -600.000000f, -58.051449f }, 1.000000f );
      instance->registerEObj( "Unknown27", 2007636, 6563525, 4, { -16.708380f, -600.000000f, -41.601891f }, 1.000000f );
      instance->registerEObj( "Unknown28", 2007637, 6588851, 4, { -18.625420f, -600.000000f, -43.212120f }, 1.000000f );
      instance->registerEObj( "Unknown29", 2007791, 0, 4, { 0.000000f, -600.000000f, -20.142851f }, 0.750000f );
      instance->registerEObj( "Unknown30", 2002872, 6620064, 4, { -317.914093f, 1.360948f, -445.124115f }, 1.000000f );
      instance->registerEObj( "Unknown31", 2002587, 0, 4, { -320.546295f, 0.991760f, -444.693695f }, 0.991760f );
      instance->registerEObj( "Unknown32", 2007630, 0, 4, { -351.186401f, 0.991760f, -466.178406f }, 0.991760f );
      instance->registerEObj( "Unknown33", 2007631, 0, 4, { -366.506500f, 0.991760f, -461.936401f }, 0.991760f );
      instance->registerEObj( "Unknown34", 2007632, 0, 4, { -359.822998f, 0.991760f, -429.373688f }, 0.991760f );
      instance->registerEObj( "Unknown35", 2007633, 0, 4, { -347.127502f, 0.991760f, -428.549713f }, 0.991760f );
      instance->registerEObj( "Unknown36", 2007638, 6586142, 4, { 343.046997f, -300.000000f, -447.157593f }, 1.000000f );
      instance->registerEObj( "Unknown37", 2007653, 6637716, 4, { -335.860596f, 1.000000f, -437.835388f }, 1.000000f );
      instance->registerEObj( "Unknown38", 2007654, 6629695, 4, { -335.609100f, 1.000000f, -440.386108f }, 1.000000f );
      instance->registerEObj( "Unknown39", 2007655, 6629831, 4, { -332.752014f, 1.000000f, -437.575012f }, 1.000000f );
      instance->registerEObj( "Unknown40", 2007656, 6637880, 4, { -332.460205f, 1.000000f, -440.058685f }, 1.000000f );
      instance->registerEObj( "Unknown41", 2007697, 0, 4, { -346.146393f, 1.000000f, -424.946991f }, 1.000000f );
      instance->registerEObj( "Unknown42", 2007787, 6752662, 4, { -368.030212f, 0.974755f, -434.419312f }, 1.000000f );
      instance->registerEObj( "Basicconveyanceunit", 2007660, 6610748, 4, { 231.338699f, -6.515625f, 346.216797f }, 0.991760f );
      instance->registerEObj( "Basicconveyanceunit", 2007661, 6610750, 4, { -356.222900f, -7.000000f, 287.132996f }, 1.000000f );
      instance->registerEObj( "Basicconveyanceunit", 2007699, 0, 4, { 397.550415f, 2.656644f, 398.343109f }, 1.000000f );
      instance->registerEObj( "Unknown43", 2007667, 6606266, 4, { 188.339996f, -6.500000f, 359.549011f }, 1.000000f );
      instance->registerEObj( "Unknown44", 2007668, 6606267, 4, { 19.479019f, -6.500000f, 316.675598f }, 1.000000f );
      instance->registerEObj( "Unknown45", 2007669, 6606268, 4, { -110.310303f, 1.500000f, 315.310303f }, 1.000000f );
      instance->registerEObj( "Unknown46", 2007670, 6606273, 4, { -357.075592f, -7.000000f, 201.676895f }, 1.000000f );
      instance->registerEObj( "Basicconveyanceunit", 2007662, 6610755, 4, { -357.847107f, 12.985350f, 16.963461f }, 0.991760f );
      instance->registerEObj( "Basicconveyanceunit", 2007663, 6610756, 4, { -342.946594f, 13.000000f, -123.268700f }, 0.991760f );
      instance->registerEObj( "Unknown47", 2007671, 6601719, 4, { -356.908508f, 13.000000f, 12.522250f }, 1.000000f );
      instance->registerEObj( "Unknown48", 2007672, 6601720, 4, { -356.563599f, 1.000000f, -74.405586f }, 1.000000f );
      instance->registerEObj( "Unknown49", 2007698, 0, 4, { -94.983139f, 1.500000f, 320.626312f }, 1.000000f );
      instance->registerEObj( "Unknown50", 2007703, 0, 4, { -94.909897f, 1.500000f, 313.278015f }, 1.000000f );
      instance->registerEObj( "Unknown51", 2007702, 0, 4, { -364.034485f, 0.991760f, -43.015259f }, 0.991760f );
      instance->registerEObj( "Entrance", 2000182, 6610725, 5, { 386.739899f, 2.618790f, 416.983307f }, 0.991760f );
      instance->registerEObj( "Exit", 2000139, 0, 4, { -371.922791f, 1.000000f, -444.704590f }, 1.000000f );
      instance->registerEObj( "Unknown53", 2002872, 6638848, 4, { -344.433014f, 13.000000f, 7.243163f }, 1.000000f );
      instance->registerEObj( "Unknown54", 2002587, 0, 4, { -350.500793f, 13.000000f, 5.113899f }, 1.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};