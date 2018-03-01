#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class TheMinstrelsBalladThordansReign : public InstanceContentScript
{
public:
   TheMinstrelsBalladThordansReign() : InstanceContentScript( 20036 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Unknown0", 2006312, 5922953, 4, { -7.224293f, 0.039305f, -2.496346f }, 1.000000f );
      instance->registerEObj( "Unknown1", 2005944, 5895686, 4, { 12.728000f, 0.012478f, -12.728000f }, 1.000000f );
      instance->registerEObj( "Unknown2", 2005945, 5895687, 4, { 12.728000f, 0.012478f, 12.728000f }, 1.000000f );
      instance->registerEObj( "Unknown3", 2005946, 5895690, 4, { -12.728000f, 0.012478f, 12.728000f }, 1.000000f );
      instance->registerEObj( "Unknown4", 2005947, 5895691, 4, { -12.728000f, 0.012478f, -12.728000f }, 1.000000f );
      instance->registerEObj( "Unknown5", 2005915, 5894863, 4, { 9.000000f, 0.012478f, -16.600000f }, 1.000000f );
      instance->registerEObj( "Unknown6", 2005916, 5894864, 4, { 18.000000f, 0.012478f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown7", 2005917, 5894866, 4, { 9.000000f, 0.012478f, 16.600000f }, 1.000000f );
      instance->registerEObj( "Unknown8", 2005918, 5894867, 4, { -9.000000f, 0.012478f, 16.600000f }, 1.000000f );
      instance->registerEObj( "Unknown9", 2005919, 5894868, 4, { -18.000000f, 0.012478f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown10", 2005920, 5894869, 4, { -9.000000f, 0.012478f, -16.600000f }, 1.000000f );
      instance->registerEObj( "Unknown11", 2005914, 5894871, 4, { 0.000000f, 0.012478f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown12", 2005913, 5894872, 4, { 0.000000f, 0.012478f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown13", 2006575, 6061720, 4, { 0.000000f, 0.039305f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown14", 2006576, 6061721, 4, { 0.000000f, 0.039305f, -19.000000f }, 1.000000f );
      instance->registerEObj( "Unknown15", 2006577, 6061722, 4, { 19.000000f, 0.039305f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown16", 2006578, 6061723, 4, { 0.000000f, 0.039305f, 19.000000f }, 1.000000f );
      instance->registerEObj( "Unknown17", 2006579, 6061724, 4, { -19.000000f, 0.039305f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown18", 2006580, 6061725, 4, { 8.485300f, 0.039305f, -8.485300f }, 1.000000f );
      instance->registerEObj( "Unknown19", 2006581, 6061727, 4, { 8.485300f, 0.039304f, 9.619522f }, 1.000000f );
      instance->registerEObj( "Unknown20", 2006582, 6061728, 4, { -8.499329f, 0.015198f, 9.174744f }, 0.991760f );
      instance->registerEObj( "Unknown21", 2006583, 6061730, 4, { -8.485300f, 0.039305f, -8.485300f }, 1.000000f );
      instance->registerEObj( "Unknown22", 2006567, 6046991, 4, { 0.000000f, 0.039305f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown23", 2006568, 6059913, 4, { 0.000000f, 0.039305f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown24", 2006569, 6059911, 4, { 0.000000f, 0.039305f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown25", 2006570, 6047214, 4, { 0.000000f, 0.039305f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown26", 2006571, 6059909, 4, { 0.000000f, 0.039305f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown27", 2006572, 6047213, 4, { 0.000000f, 0.039305f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown28", 2006573, 6059910, 4, { 0.000000f, 0.039305f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown29", 2006574, 6059912, 4, { 0.000000f, 0.039305f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown30", 2006587, 6056540, 4, { -0.607457f, 0.039305f, -0.008893f }, 1.000000f );
      instance->registerEObj( "Entrance", 2000182, 5854853, 5, { 0.035266f, 0.012478f, 11.380060f }, 1.000000f );
      instance->registerEObj( "Exit", 2000139, 0, 4, { 0.000000f, 0.012478f, -18.000000f }, 1.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};