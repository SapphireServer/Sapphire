#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class CastrumAbania :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  CastrumAbania() :
    Sapphire::ScriptAPI::InstanceContentScript( 55 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2002735, 0, 4, { 277.157013f, 20.000000f, -7.932621f }, 1.000000f, 0.305963f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118", 2002872, 6841714, 4, { 276.710388f, 20.000000f, -6.315289f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 286.855713f, 20.000000f, -43.546181f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_1", 2007457, 6777074, 4, { 281.592285f, 20.000000f, -45.737782f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Entrance", 2000182, 6828612, 5, { -406.401794f, -17.924580f, 314.141907f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { -414.573212f, -18.000120f, 306.364807f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_2", 2008027, 6738153, 4, { -362.172913f, -10.025270f, 237.292999f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_3", 2008029, 6739981, 4, { -291.220795f, -6.000043f, 108.329102f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_4", 2008030, 6739980, 4, { -298.753113f, -6.000044f, 108.051498f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_5", 2008031, 6739979, 4, { -305.840515f, -6.000044f, 107.763603f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_6", 2008032, 6739982, 4, { -281.123505f, -6.000060f, 118.299301f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_7", 2008033, 6739984, 4, { -280.565704f, -6.000067f, 125.491203f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_8", 2008034, 6739983, 4, { -280.552185f, -6.000068f, 132.687302f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_9", 2008035, 6869663, 4, { -273.854889f, -6.000038f, 100.620499f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_10", 2008036, 6740009, 4, { -213.504593f, -6.129103f, 82.266739f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_11", 2008037, 6740016, 4, { -213.045807f, -1.999959f, 131.946198f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_12", 2008038, 6914793, 4, { -179.395294f, 2.138688f, 279.671387f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_13", 2008041, 6752603, 4, { -167.801697f, 2.138688f, 273.763214f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_14", 2008042, 6752604, 4, { -167.091507f, 2.138688f, 278.924805f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_15", 2008043, 6752601, 4, { -180.179504f, 2.138688f, 292.024200f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_16", 2008044, 6752602, 4, { -184.772797f, 2.138688f, 291.367188f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_17", 2008047, 6752608, 4, { -166.154602f, 2.000032f, 293.249298f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_18", 2008039, 6914794, 4, { -101.486900f, 6.138662f, 311.254791f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_19", 2008050, 6752644, 4, { -81.520500f, 6.000006f, 290.652313f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_20", 2008051, 6752643, 4, { -81.142883f, 6.000006f, 332.866211f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_21", 2008048, 6752633, 4, { -80.650719f, 6.138662f, 311.338989f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_22", 2008040, 6914795, 4, { -22.122820f, 10.138660f, 278.146912f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_23", 2008045, 6752689, 4, { -27.394449f, 10.138660f, 265.483795f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_24", 2008046, 6752679, 4, { -16.694490f, 10.138650f, 265.926208f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_25", 2008070, 6752690, 4, { -9.852131f, 10.138650f, 272.919403f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_26", 2008089, 6752691, 4, { -9.914229f, 10.138650f, 283.758392f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_27", 2008052, 6752695, 4, { -21.991831f, 9.999999f, 250.500702f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_28", 2008053, 6752694, 4, { 5.133811f, 9.999997f, 278.283295f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_29", 2008049, 6752681, 4, { -8.415267f, 9.999998f, 264.128204f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_30", 2008320, 6869673, 4, { -84.465187f, 6.000006f, 311.371613f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_31", 2008054, 6785102, 4, { 22.499630f, 14.184900f, 175.166702f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_32", 2008056, 6741815, 4, { 110.871597f, 26.000059f, 144.405807f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_33", 2008055, 6698733, 4, { 178.971298f, 20.000139f, 81.701027f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_34", 2008057, 6717638, 4, { 154.867996f, 20.000160f, 106.733902f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_35", 2008058, 6717639, 4, { 165.172699f, 20.000019f, 86.256683f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_36", 2008059, 6717640, 4, { 195.091507f, 20.000170f, 51.864651f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_37", 2008060, 6717641, 4, { 200.323502f, 20.000179f, 46.925930f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_38", 2008061, 6717642, 4, { 203.790298f, 20.000200f, 59.565971f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_39", 2008062, 6717643, 4, { 209.140793f, 20.000191f, 54.901482f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_40", 2008063, 6772873, 4, { 172.971100f, 20.100290f, 82.304329f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_41", 2008064, 6773603, 4, { 267.862396f, 20.100000f, 30.848459f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_42", 2008455, 6790661, 4, { 294.476715f, 20.000000f, -39.619999f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_43", 2008527, 6914797, 4, { 21.803070f, 14.184900f, 182.260696f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_44", 2007457, 6842146, 4, { 205.204193f, 20.000271f, 41.332821f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_45", 2007457, 6842148, 4, { 214.202393f, 20.000271f, 49.597000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_46", 2002735, 0, 4, { -212.960007f, -2.000000f, 167.038193f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2002872, 6841858, 4, { -212.643799f, -2.000000f, 164.712097f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2008071, 6841865, 4, { -212.474792f, -1.815126f, 204.927307f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2002872, 6841875, 4, { 10.483370f, 14.000030f, 208.476395f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_47", 2002735, 0, 4, { 10.447360f, 14.000030f, 206.708298f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_4", 2008072, 6841959, 4, { 28.276699f, 14.184900f, 186.737000f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( CastrumAbania );