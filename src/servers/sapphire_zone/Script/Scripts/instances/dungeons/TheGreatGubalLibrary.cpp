#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class TheGreatGubalLibrary : public InstanceContentScript
{
public:
   TheGreatGubalLibrary() : InstanceContentScript( 31 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Unknown0", 2002735, 0, 4, { 353.541412f, -39.250000f, -59.553089f }, 1.000000f );
      instance->registerEObj( "Unknown1", 2002872, 5419624, 4, { 350.673187f, -39.000000f, -60.588070f }, 1.000000f );
      instance->registerEObj( "OnGarleanHierarchyVolume1", 2005891, 0, 4, { -199.611694f, 6.900000f, -56.354649f }, 1.000000f );
      instance->registerEObj( "OnGarleanHierarchyVolume2", 2005892, 0, 4, { -72.116417f, 0.900000f, -9.577726f }, 1.000000f );
      instance->registerEObj( "Essences&Permutations", 2005893, 0, 4, { 54.309052f, -8.099999f, 62.262531f }, 1.000000f );
      instance->registerEObj( "OvertheHorizon", 2005894, 0, 4, { 113.656601f, -8.153534f, 83.276863f }, 1.000000f );
      instance->registerEObj( "Leatherbounddiary", 2005895, 0, 4, { 253.342499f, -24.000000f, -16.578369f }, 1.000000f );
      instance->registerEObj( "Leatherbounddiary", 2005896, 0, 4, { 252.532898f, -40.000000f, -78.517921f }, 1.000000f );
      instance->registerEObj( "Unknown2", 2002872, 5419606, 4, { -22.327221f, 0.000000f, -0.318492f }, 1.000000f );
      instance->registerEObj( "Unknown3", 2005019, 5419607, 4, { 22.309731f, 0.000000f, -0.124082f }, 1.000000f );
      instance->registerEObj( "Unknown4", 2002735, 0, 4, { -20.486000f, 0.000000f, 0.109200f }, 1.000000f );
      instance->registerEObj( "Unknown5", 2005316, 5774736, 4, { -11.221270f, 0.000000f, -6.534676f }, 1.000000f );
      instance->registerEObj( "Unknown6", 2005328, 5815254, 4, { -10.516900f, 0.000000f, -1.875240f }, 1.000000f );
      instance->registerEObj( "Unknown7", 2002872, 5419612, 4, { 178.337997f, -8.000000f, 53.739559f }, 1.000000f );
      instance->registerEObj( "Unknown8", 2005020, 5419614, 4, { 179.630203f, -8.000000f, 0.354116f }, 1.000000f );
      instance->registerEObj( "Unknown9", 2002735, 0, 4, { 177.873505f, -8.000000f, 52.121300f }, 1.000000f );
      instance->registerEObj( "Unknown10", 2005354, 5852274, 4, { 177.539993f, -7.995000f, 32.977421f }, 1.000000f );
      instance->registerEObj( "Unknown11", 2004942, 5033535, 4, { -316.612915f, -0.015320f, 0.045776f }, 0.991760f );
      instance->registerEObj( "Unknown12", 2004949, 5033537, 4, { -173.408096f, 12.000000f, -33.362572f }, 0.991760f );
      instance->registerEObj( "Unknown13", 2004956, 5033536, 4, { -48.355900f, -0.015320f, 0.747620f }, 0.991760f );
      instance->registerEObj( "Unknown14", 2004957, 5033538, 4, { 43.900150f, -0.015320f, -1.083435f }, 0.991760f );
      instance->registerEObj( "Unknown15", 2004958, 5004619, 4, { 82.139282f, -8.011047f, 69.748901f }, 0.991760f );
      instance->registerEObj( "Unknown16", 2004959, 5004620, 4, { 117.387604f, -9.018127f, 69.291138f }, 0.991760f );
      instance->registerEObj( "Unknown17", 2004960, 5336977, 4, { 138.888000f, -9.018127f, 87.533859f }, 0.991760f );
      instance->registerEObj( "Unknown18", 2004962, 5033543, 4, { 156.328598f, -9.018127f, 95.628304f }, 0.991760f );
      instance->registerEObj( "Unknown19", 2004963, 5004621, 4, { 176.257004f, -8.011047f, -9.414856f }, 0.991760f );
      instance->registerEObj( "Unknown20", 2004964, 5773506, 4, { 297.779785f, -24.002501f, -43.308731f }, 0.991760f );
      instance->registerEObj( "Unknown21", 2004965, 5004586, 4, { 325.666107f, -39.017399f, -59.098209f }, 0.991760f );
      instance->registerEObj( "Entrance", 2000182, 5330520, 5, { -387.057098f, -0.015320f, 4.592957f }, 0.991760f );
      instance->registerEObj( "Shortcut", 2000700, 0, 4, { -381.085205f, -0.015320f, 6.094601f }, 0.991760f );
      instance->registerEObj( "Exit", 2000139, 0, 4, { 393.697998f, -39.047909f, -59.586491f }, 0.991760f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};