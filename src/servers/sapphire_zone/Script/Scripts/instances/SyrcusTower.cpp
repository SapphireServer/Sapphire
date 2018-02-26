#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class SyrcusTower : public InstanceContentScript
{
public:
   SyrcusTower() : InstanceContentScript( 30011 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Unknown0", 2002587, 0, 4, { -370.000000f, 500.115387f, -199.956299f }, 0.700000f );
      instance->registerEObj( "Unknown1", 2002872, 4738783, 4, { -394.730194f, 500.000000f, -199.572800f }, 0.991760f );
      instance->registerEObj( "Exit", 2000139, 0, 4, { -415.668213f, 500.000000f, -200.003296f }, 1.000000f );
      instance->registerEObj( "Unknown2", 2004244, 4757482, 4, { -390.384705f, 500.000000f, -194.533203f }, 1.000000f );
      instance->registerEObj( "Unknown3", 2004292, 4757483, 4, { -401.338287f, 500.000000f, -196.787003f }, 1.000000f );
      instance->registerEObj( "Unknown4", 2004293, 4757484, 4, { -403.504913f, 500.000000f, -196.539597f }, 1.000000f );
      instance->registerEObj( "Unknown5", 2004294, 4757485, 4, { -405.170593f, 500.000000f, -202.118393f }, 1.000000f );
      instance->registerEObj( "Unknown6", 2004295, 4757486, 4, { -400.173798f, 500.000000f, -200.892807f }, 1.000000f );
      instance->registerEObj( "Unknown7", 2004296, 4757487, 4, { -395.280304f, 500.000000f, -200.854401f }, 1.000000f );
      instance->registerEObj( "Unknown8", 2004243, 4757498, 4, { -400.242615f, 500.000000f, -197.116501f }, 1.000000f );
      instance->registerEObj( "Unknown9", 2004354, 0, 4, { -397.029785f, 500.000000f, -196.979202f }, 1.000000f );
      instance->registerEObj( "Unknown10", 2004355, 0, 4, { -459.071411f, 506.001801f, -196.468506f }, 1.000000f );
      instance->registerEObj( "Unknown11", 2004236, 4759659, 4, { -1.397732f, -589.900085f, -194.801498f }, 1.000000f );
      instance->registerEObj( "Unknown12", 2004237, 0, 4, { 2.182007f, -589.929077f, -198.077499f }, 0.991760f );
      instance->registerEObj( "Unknown13", 2002587, 0, 4, { -0.015320f, -590.000000f, -152.513794f }, 0.686646f );
      instance->registerEObj( "Unknown14", 2002872, 4725495, 4, { 0.228821f, -590.000000f, -174.995300f }, 0.991760f );
      instance->registerEObj( "Unknown15", 2002587, 0, 4, { -0.883440f, -4.000000f, -141.001801f }, 0.700000f );
      instance->registerEObj( "Unknown16", 2002872, 4738653, 4, { -0.991882f, 0.000000f, -196.720993f }, 0.991760f );
      instance->registerEObj( "Unknown17", 2004245, 4711823, 4, { -0.379705f, 0.000000f, -145.342300f }, 1.000000f );
      instance->registerEObj( "Unknown18", 2004246, 4711824, 4, { 0.710614f, 0.000000f, -199.171204f }, 0.991760f );
      instance->registerEObj( "Unknown19", 2004247, 4711825, 4, { 0.439319f, 0.000001f, -201.553802f }, 1.000000f );
      instance->registerEObj( "Unknown20", 2004248, 4711828, 4, { 0.202690f, 0.000000f, -199.270599f }, 1.000000f );
      instance->registerEObj( "Unknown21", 2004250, 4867789, 4, { -0.142451f, -0.000001f, -199.916000f }, 1.000000f );
      instance->registerEObj( "Unknown22", 2004251, 4771487, 4, { 6.207808f, 0.025001f, -197.716293f }, 1.000000f );
      instance->registerEObj( "Unknown23", 2004252, 4771488, 4, { 0.912855f, 0.000000f, -200.229401f }, 1.000000f );
      instance->registerEObj( "Unknown24", 2004253, 4771264, 4, { -0.249095f, 0.000000f, -200.632095f }, 1.000000f );
      instance->registerEObj( "Unknown25", 2004540, 0, 4, { 2.310606f, 0.000000f, -199.315903f }, 1.000000f );
      instance->registerEObj( "Unknown26", 2002587, 0, 4, { 16.500000f, 600.000000f, -175.000000f }, 0.700000f );
      instance->registerEObj( "Unknown27", 2002872, 4738751, 4, { 6.038667f, 600.000000f, -191.625595f }, 1.000000f );
      instance->registerEObj( "Unknown28", 2004249, 0, 4, { 0.534058f, 600.000000f, -204.089493f }, 0.991760f );
      instance->registerEObj( "Unknown29", 2004372, 0, 4, { 2.491530f, 600.000000f, -197.343201f }, 1.000000f );
      instance->registerEObj( "Unknown30", 2004498, 0, 4, { 7.797371f, 600.000000f, -197.855301f }, 1.000000f );
      instance->registerEObj( "Unknown31", 2002587, 0, 4, { 0.000000f, -700.000000f, 79.955803f }, 0.700000f );
      instance->registerEObj( "Unknown32", 2002872, 4725557, 4, { -0.328611f, -700.000000f, 53.732899f }, 1.000000f );
      instance->registerEObj( "Unknown33", 2002587, 0, 4, { 29.805300f, -400.000000f, -200.000000f }, 0.700000f );
      instance->registerEObj( "Unknown34", 2002872, 4725580, 4, { 5.249963f, -400.000000f, -199.878006f }, 0.991760f );
      instance->registerEObj( "Unknown35", 2002587, 0, 4, { 0.000000f, 200.000000f, -229.757797f }, 0.700000f );
      instance->registerEObj( "Unknown36", 2002872, 4738682, 4, { 0.542766f, 199.899994f, -231.713898f }, 1.000000f );
      instance->registerEObj( "Entrance", 2000182, 4723157, 5, { -0.325782f, -897.940918f, 371.584106f }, 1.000000f );
      instance->registerEObj( "Allaganteleporter", 2004154, 4645409, 4, { -5.014030f, -894.781982f, 324.891296f }, 0.991760f );
      instance->registerEObj( "Allaganteleporter", 2004155, 4645410, 4, { 8.084772f, -708.339111f, 175.045898f }, 0.991760f );
      instance->registerEObj( "Allaganteleporter", 2004158, 4645412, 4, { 7.971835f, -598.362915f, -76.990211f }, 0.991760f );
      instance->registerEObj( "Allaganteleporter", 2004156, 4652344, 4, { 72.370857f, -402.456696f, -206.931000f }, 0.991760f );
      instance->registerEObj( "Allaganteleporter", 2004159, 4645415, 4, { -6.906353f, -2.365848f, -126.353897f }, 0.991760f );
      instance->registerEObj( "Allaganteleporter", 2004157, 4645417, 4, { -6.845924f, 197.827805f, -274.836700f }, 0.991760f );
      instance->registerEObj( "Allaganteleporter", 2004160, 4651219, 4, { 29.220949f, 599.725220f, -140.581406f }, 0.991760f );
      instance->registerEObj( "Allaganteleporter", 2004161, 4636419, 4, { -317.290192f, 500.821808f, -189.288193f }, 0.991760f );
      instance->registerEObj( "Unknown38", 2004164, 4738634, 4, { 0.448093f, -700.000000f, 104.558601f }, 1.000000f );
      instance->registerEObj( "Unknown39", 2004173, 4720323, 4, { 0.019809f, -590.000000f, -150.897903f }, 1.000000f );
      instance->registerEObj( "Unknown40", 2004167, 4711138, 4, { 44.295219f, -403.598602f, -199.389694f }, 0.991760f );
      instance->registerEObj( "Unknown41", 2004176, 4710992, 4, { 0.045776f, 0.000000f, -180.284607f }, 0.991760f );
      instance->registerEObj( "Unknown42", 2004170, 4710494, 4, { 0.449279f, 196.100006f, -262.072296f }, 0.991760f );
      instance->registerEObj( "Unknown43", 2004179, 4742340, 4, { 28.708071f, 598.000183f, -156.658600f }, 1.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};