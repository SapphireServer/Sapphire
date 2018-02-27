#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class CastrumAbania : public InstanceContentScript
{
public:
   CastrumAbania() : InstanceContentScript( 55 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Unknown0", 2002735, 0, 4, { 277.157013f, 20.000000f, -7.932621f }, 1.000000f );
      instance->registerEObj( "Unknown1", 2002872, 6841714, 4, { 276.710388f, 20.000000f, -6.315289f }, 1.000000f );
      instance->registerEObj( "Exit", 2000139, 0, 4, { 286.855713f, 20.000000f, -43.546181f }, 1.000000f );
      instance->registerEObj( "Unknown2", 2007457, 6777074, 4, { 281.592285f, 20.000000f, -45.737782f }, 1.000000f );
      instance->registerEObj( "Entrance", 2000182, 6828612, 5, { -406.401794f, -17.924580f, 314.141907f }, 1.000000f );
      instance->registerEObj( "Shortcut", 2000700, 0, 4, { -414.573212f, -18.000120f, 306.364807f }, 1.000000f );
      instance->registerEObj( "Unknown4", 2008027, 6738153, 4, { -362.172913f, -10.025270f, 237.292999f }, 0.991760f );
      instance->registerEObj( "Unknown5", 2008029, 6739981, 4, { -291.220795f, -6.000043f, 108.329102f }, 1.000000f );
      instance->registerEObj( "Unknown6", 2008030, 6739980, 4, { -298.753113f, -6.000044f, 108.051498f }, 1.000000f );
      instance->registerEObj( "Unknown7", 2008031, 6739979, 4, { -305.840515f, -6.000044f, 107.763603f }, 1.000000f );
      instance->registerEObj( "Unknown8", 2008032, 6739982, 4, { -281.123505f, -6.000060f, 118.299301f }, 1.000000f );
      instance->registerEObj( "Unknown9", 2008033, 6739984, 4, { -280.565704f, -6.000067f, 125.491203f }, 1.000000f );
      instance->registerEObj( "Unknown10", 2008034, 6739983, 4, { -280.552185f, -6.000068f, 132.687302f }, 1.000000f );
      instance->registerEObj( "Unknown11", 2008035, 6869663, 4, { -273.854889f, -6.000038f, 100.620499f }, 1.000000f );
      instance->registerEObj( "Unknown12", 2008036, 6740009, 4, { -213.504593f, -6.129103f, 82.266739f }, 1.000000f );
      instance->registerEObj( "Unknown13", 2008037, 6740016, 4, { -213.045807f, -1.999959f, 131.946198f }, 1.000000f );
      instance->registerEObj( "Unknown14", 2008038, 6914793, 4, { -179.395294f, 2.138688f, 279.671387f }, 1.000000f );
      instance->registerEObj( "Unknown15", 2008041, 6752603, 4, { -167.801697f, 2.138688f, 273.763214f }, 1.000000f );
      instance->registerEObj( "Unknown16", 2008042, 6752604, 4, { -167.091507f, 2.138688f, 278.924805f }, 1.000000f );
      instance->registerEObj( "Unknown17", 2008043, 6752601, 4, { -180.179504f, 2.138688f, 292.024200f }, 1.000000f );
      instance->registerEObj( "Unknown18", 2008044, 6752602, 4, { -184.772797f, 2.138688f, 291.367188f }, 1.000000f );
      instance->registerEObj( "Unknown19", 2008047, 6752608, 4, { -166.154602f, 2.000032f, 293.249298f }, 1.000000f );
      instance->registerEObj( "Unknown20", 2008039, 6914794, 4, { -101.486900f, 6.138662f, 311.254791f }, 1.000000f );
      instance->registerEObj( "Unknown21", 2008050, 6752644, 4, { -81.520500f, 6.000006f, 290.652313f }, 1.000000f );
      instance->registerEObj( "Unknown22", 2008051, 6752643, 4, { -81.142883f, 6.000006f, 332.866211f }, 1.000000f );
      instance->registerEObj( "Unknown23", 2008048, 6752633, 4, { -80.650719f, 6.138662f, 311.338989f }, 1.000000f );
      instance->registerEObj( "Unknown24", 2008040, 6914795, 4, { -22.122820f, 10.138660f, 278.146912f }, 1.000000f );
      instance->registerEObj( "Unknown25", 2008045, 6752689, 4, { -27.394449f, 10.138660f, 265.483795f }, 1.000000f );
      instance->registerEObj( "Unknown26", 2008046, 6752679, 4, { -16.694490f, 10.138650f, 265.926208f }, 1.000000f );
      instance->registerEObj( "Unknown27", 2008070, 6752690, 4, { -9.852131f, 10.138650f, 272.919403f }, 1.000000f );
      instance->registerEObj( "Unknown28", 2008089, 6752691, 4, { -9.914229f, 10.138650f, 283.758392f }, 1.000000f );
      instance->registerEObj( "Unknown29", 2008052, 6752695, 4, { -21.991831f, 9.999999f, 250.500702f }, 1.000000f );
      instance->registerEObj( "Unknown30", 2008053, 6752694, 4, { 5.133811f, 9.999997f, 278.283295f }, 1.000000f );
      instance->registerEObj( "Unknown31", 2008049, 6752681, 4, { -8.415267f, 9.999998f, 264.128204f }, 1.000000f );
      instance->registerEObj( "Unknown32", 2008320, 6869673, 4, { -84.465187f, 6.000006f, 311.371613f }, 1.000000f );
      instance->registerEObj( "Unknown33", 2008054, 6785102, 4, { 22.499630f, 14.184900f, 175.166702f }, 1.000000f );
      instance->registerEObj( "Unknown34", 2008056, 6741815, 4, { 110.871597f, 26.000059f, 144.405807f }, 1.000000f );
      instance->registerEObj( "Unknown35", 2008055, 6698733, 4, { 178.971298f, 20.000139f, 81.701027f }, 1.000000f );
      instance->registerEObj( "Unknown36", 2008057, 6717638, 4, { 154.867996f, 20.000160f, 106.733902f }, 1.000000f );
      instance->registerEObj( "Unknown37", 2008058, 6717639, 4, { 165.172699f, 20.000019f, 86.256683f }, 1.000000f );
      instance->registerEObj( "Unknown38", 2008059, 6717640, 4, { 195.091507f, 20.000170f, 51.864651f }, 1.000000f );
      instance->registerEObj( "Unknown39", 2008060, 6717641, 4, { 200.323502f, 20.000179f, 46.925930f }, 1.000000f );
      instance->registerEObj( "Unknown40", 2008061, 6717642, 4, { 203.790298f, 20.000200f, 59.565971f }, 1.000000f );
      instance->registerEObj( "Unknown41", 2008062, 6717643, 4, { 209.140793f, 20.000191f, 54.901482f }, 1.000000f );
      instance->registerEObj( "Unknown42", 2008063, 6772873, 4, { 172.971100f, 20.100290f, 82.304329f }, 1.000000f );
      instance->registerEObj( "Unknown43", 2008064, 6773603, 4, { 267.862396f, 20.100000f, 30.848459f }, 1.000000f );
      instance->registerEObj( "Unknown44", 2008455, 6790661, 4, { 294.476715f, 20.000000f, -39.619999f }, 1.000000f );
      instance->registerEObj( "Unknown45", 2008527, 6914797, 4, { 21.803070f, 14.184900f, 182.260696f }, 1.000000f );
      instance->registerEObj( "Unknown46", 2007457, 6842146, 4, { 205.204193f, 20.000271f, 41.332821f }, 1.000000f );
      instance->registerEObj( "Unknown47", 2007457, 6842148, 4, { 214.202393f, 20.000271f, 49.597000f }, 1.000000f );
      instance->registerEObj( "Unknown48", 2002735, 0, 4, { -212.960007f, -2.000000f, 167.038193f }, 1.000000f );
      instance->registerEObj( "Unknown49", 2002872, 6841858, 4, { -212.643799f, -2.000000f, 164.712097f }, 1.000000f );
      instance->registerEObj( "Unknown50", 2008071, 6841865, 4, { -212.474792f, -1.815126f, 204.927307f }, 1.000000f );
      instance->registerEObj( "Unknown51", 2002872, 6841875, 4, { 10.483370f, 14.000030f, 208.476395f }, 1.000000f );
      instance->registerEObj( "Unknown52", 2002735, 0, 4, { 10.447360f, 14.000030f, 206.708298f }, 1.000000f );
      instance->registerEObj( "Unknown53", 2008072, 6841959, 4, { 28.276699f, 14.184900f, 186.737000f }, 1.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};