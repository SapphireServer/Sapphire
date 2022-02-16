#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class BrotherfromAnotherMother : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_ENPC_POP_1_ERIC_01 = 4306244;
  static constexpr auto INIT_EOBJ_POP_1_MACHIN_01 = 4306245;
  static constexpr auto INIT_POP_1_IMP_01 = 4306246;
  static constexpr auto INIT_POP_1_IMP_02 = 4306247;
  static constexpr auto INIT_POP_1_IMP_03 = 4306248;
  static constexpr auto INIT_POP_1_IMP_04 = 4306249;
  static constexpr auto INIT_POP_1_IMP_05 = 4306250;
  static constexpr auto INIT_POP_1_IMP_06 = 4306251;
  static constexpr auto INIT_POP_2_IMP_BOSS_01 = 4306253;
  static constexpr auto INIT_POP_3_MASEKIKUN_01 = 4306259;
  static constexpr auto INIT_POP_3_MASEKIKUN_02 = 4306260;
  static constexpr auto INIT_POP_3_MASEKIKUN_03 = 4306261;
  static constexpr auto CUT_END_NCUT = 338;
  static constexpr auto LOC_POS_ACTOR0 = 4324013;
  static constexpr auto LOC_ACTOR0 = 1006749;
  static constexpr auto LOC_ACTOR1 = 1007892;
  static constexpr auto LOC_ACTOR2 = 1007893;
  static constexpr auto LOC_ACTOR3 = 1007894;
  static constexpr auto LOC_POS_ACTOR1 = 4325065;
  static constexpr auto LOC_POS_ACTOR2 = 4325150;

public:
  BrotherfromAnotherMother() : Sapphire::ScriptAPI::QuestBattleScript( 70 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.addEObj( "Herbpatch", 2000269, 0, 3538830, 4, { -168.030701f, -29.340919f, 84.545708f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_0", 2000409, 0, 3747939, 4, { -212.848099f, -33.035831f, 113.542397f }, 0.930786f, 0.000048f, 0); 
    instance.addEObj( "unknown_1", 2000409, 0, 3748525, 4, { -162.298599f, -31.120291f, 110.046402f }, 0.779493f, 0.000048f, 0); 
    instance.addEObj( "unknown_2", 2000409, 0, 3748531, 4, { -275.623810f, -31.509951f, 92.423828f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Entrance", 2001710, 4138533, 4138531, 5, { -152.954300f, -29.048920f, 89.609222f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.addEObj( "Cactusleaf", 2001219, 0, 4163996, 4, { 68.184372f, 2.507450f, -191.363205f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Cactusleaf_1", 2001219, 0, 4163997, 4, { 103.783699f, 1.089769f, -184.676102f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Cactusleaf_2", 2001219, 0, 4163998, 4, { 91.415398f, 3.350578f, -220.746307f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Cactusleaf_3", 2001219, 0, 4163999, 4, { 112.229103f, 1.290796f, -220.902802f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Cactusleaf_4", 2001219, 0, 4164000, 4, { 125.070099f, -0.567415f, -203.612198f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Cactusleaf_5", 2001219, 0, 4164001, 4, { 133.148895f, 1.388501f, -235.169098f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Cactusleaf_6", 2001219, 0, 4164002, 4, { 57.463402f, 0.891828f, -199.581604f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Cactusleaf_7", 2001219, 0, 4164003, 4, { 84.317146f, 1.130788f, -183.062500f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Stolenshippingcrate", 2001222, 0, 4163983, 4, { 115.969299f, 28.946650f, -16.900860f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Stolenshippingcrate_1", 2001222, 0, 4163984, 4, { 147.068100f, 28.574089f, -4.458593f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Stolenshippingcrate_2", 2001222, 0, 4163985, 4, { 149.599197f, 28.624269f, -16.895611f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Stolenshippingcrate_3", 2001222, 0, 4163986, 4, { 135.130203f, 28.626221f, -25.092680f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Stolenshippingcrate_4", 2001222, 0, 4163987, 4, { 128.430801f, 28.722771f, -5.393469f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Stolenshippingcrate_5", 2001222, 0, 4163988, 4, { 138.452301f, 28.674669f, -9.497550f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Stolenshippingcrate_6", 2001222, 0, 4163989, 4, { 121.850197f, 28.614929f, -22.842150f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Stolenshippingcrate_7", 2001222, 0, 4163990, 4, { 134.542099f, 28.635111f, -18.532190f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_3", 2002390, 0, 4306245, 4, { -232.800003f, -28.933470f, 125.320000f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_4", 2004893, 0, 5375028, 4, { -56.192440f, -10.742790f, -71.522552f }, 0.772795f, -1.476827f, 0); 
    instance.addEObj( "Destination", 2005188, 0, 5658022, 4, { -314.058685f, -1.080676f, 44.011101f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_5", 2005168, 0, 5658066, 4, { -339.162292f, 0.289917f, 43.167721f }, 0.381470f, 1.401670f, 0); 
    instance.addEObj( "Destination_1", 2001426, 0, 3976856, 4, { 27.219780f, 12.999960f, 51.848911f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_2", 2001756, 0, 4167293, 4, { 27.219801f, 13.000000f, 51.848900f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Pointofambush", 2001434, 0, 3983423, 4, { -115.745300f, 0.015855f, -149.218002f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_6", 2005626, 0, 5877369, 4, { 77.408943f, 0.414342f, -249.317200f }, 0.991760f, 0.373482f, 0); 
    instance.addEObj( "Destination_3", 2001349, 0, 3954552, 4, { -241.410797f, 8.100866f, -32.214520f }, 0.991789f, 0.000048f, 0); 
    instance.addEObj( "Entrance_1", 2002704, 0, 4374431, 4, { -282.678894f, -6.417949f, -376.681305f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_7", 2004241, 1668222, 4740570, 4, { 118.988602f, 31.920019f, -392.048187f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_4", 2002097, 0, 4296717, 4, { 200.596802f, -1.452231f, -312.203491f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Destination_5", 2002098, 0, 4296718, 4, { 192.300797f, -0.025306f, -336.868805f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_6", 2002099, 0, 4296720, 4, { 176.606506f, -0.096808f, -303.092194f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Destination_7", 2002100, 0, 4296725, 4, { 164.392899f, -0.045770f, -315.728485f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Destination_8", 2001019, 0, 4298981, 4, { -276.600311f, -3.799561f, -368.764801f }, 0.991760f, 0.740418f, 0); 
    instance.addEObj( "unknown_8", 2005071, 0, 5572885, 4, { -289.711914f, 22.829769f, -56.321770f }, 0.991760f, -0.956020f, 0); 
    instance.addEObj( "Faintlight", 2005072, 0, 5572886, 4, { -289.696686f, 22.834881f, -56.297989f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_9", 2005069, 0, 5608173, 4, { -289.149292f, 22.816700f, -56.654640f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_10", 2005070, 0, 5608174, 4, { -289.149292f, 22.816700f, -56.654598f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_11", 2002439, 0, 4308108, 4, { -232.800003f, -28.782459f, 125.320000f }, 0.500000f, 0.000000f, 0); 
    instance.addEObj( "Aetherometer", 2002440, 0, 4308110, 4, { -232.800003f, -28.933500f, 125.320000f }, 1.000000f, -0.000000f, 0); 
    instance.addEObj( "Sprigganscratchings", 2005969, 0, 5900203, 4, { -4.520000f, 27.709999f, -422.200012f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Sprigganscratchings_1", 2005970, 0, 5900225, 4, { -29.160000f, 27.430000f, -417.970001f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Sprigganscratchings_2", 2005971, 0, 5900229, 4, { -11.630000f, 34.040001f, -458.589996f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_9", 2001853, 0, 4236105, 4, { 202.637894f, 14.137880f, 536.905212f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_12", 2001427, 0, 3978247, 4, { 246.948807f, -17.084700f, -131.469604f }, 1.000000f, 0.258268f, 0); 
    instance.addEObj( "unknown_10", 2004678, 0, 5020860, 4, { -97.079391f, -11.350000f, -51.853180f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "???", 2004109, 0, 4722044, 4, { -277.332794f, -0.215080f, -324.116913f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_11", 2004275, 0, 4745260, 4, { 71.205780f, 1.190876f, 250.311096f }, 1.000000f, 1.423589f, 0); 
    instance.addEObj( "Molehill", 2004276, 0, 4745261, 4, { 70.267899f, 1.233000f, 250.565201f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Weedbundle", 2004277, 0, 4745262, 4, { 70.267700f, 1.205444f, 250.537796f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_12", 2004617, 0, 4996407, 4, { -173.785004f, 16.128719f, 276.325592f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_13", 2004848, 0, 5617264, 4, { -199.578003f, 18.684820f, -435.402588f }, 1.000000f, 1.257978f, 0); 
    instance.addEObj( "unknown_14", 2004849, 0, 5617265, 4, { -201.573898f, 18.640739f, -435.082489f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_15", 2004852, 0, 5617283, 4, { -199.034897f, 18.694820f, -434.904205f }, 1.000000f, 1.085238f, 0); 
    instance.addEObj( "unknown_16", 2004853, 0, 5617285, 4, { -199.572800f, 18.631229f, -431.662506f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_17", 2004854, 0, 5617286, 4, { -201.211700f, 18.631580f, -434.045593f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Barreltrap", 2000741, 0, 3708874, 4, { 15.797450f, 0.709689f, -59.381630f }, 0.991789f, 0.514131f, 0); 
    instance.addEObj( "Barreltrap_1", 2000742, 0, 3708875, 4, { 10.260200f, 2.658585f, -28.125950f }, 1.000000f, 0.850329f, 0); 
    instance.addEObj( "Narrowfissure", 2000268, 0, 3505674, 4, { 25.690830f, 13.106330f, 47.828960f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Amajina&Sonscoffer", 2000300, 0, 3727742, 4, { -265.766388f, 22.903749f, -69.596443f }, 0.991760f, -0.009252f, 0); 
    instance.addEObj( "Amajina&Sonscoffer_1", 2000753, 0, 3739377, 4, { -225.100204f, 16.741150f, -57.722778f }, 0.991760f, 0.689701f, 0); 
    instance.addEObj( "Amajina&Sonscoffer_2", 2000754, 0, 3739388, 4, { -262.592499f, 29.007320f, -118.455803f }, 0.991760f, -1.191682f, 0); 
    instance.addEObj( "unknown_18", 2001851, 0, 4217146, 4, { -228.542099f, -30.788321f, 117.384300f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Shrewhill", 2000372, 0, 3630537, 4, { 57.299252f, 1.010623f, 247.151703f }, 1.287683f, 0.000336f, 0); 
    instance.addEObj( "Shrewhill_1", 2000374, 0, 3630544, 4, { 60.213860f, 1.177293f, 239.561600f }, 0.967427f, 0.000240f, 0); 
    instance.addEObj( "Shrewhill_2", 2000373, 0, 3630546, 4, { 68.021507f, 1.098406f, 245.075699f }, 1.213247f, 0.000144f, 0); 
    instance.addEObj( "Pockmarkedsilverore", 2000375, 0, 3632982, 4, { 159.001205f, -1.731532f, -232.957596f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Pockmarkedsilverore_1", 2000377, 0, 3632985, 4, { -134.696396f, 6.168209f, -116.593903f }, 0.961271f, 0.000144f, 0); 
    instance.addEObj( "Pockmarkedsilverore_2", 2000378, 0, 3632986, 4, { -95.958344f, -1.021936f, -163.731293f }, 0.961271f, 0.000144f, 0); 
    instance.addEObj( "Pockmarkedsilverore_3", 2000379, 0, 3632987, 4, { -103.937500f, 0.491295f, -213.694504f }, 0.900235f, 0.000336f, 0); 
    instance.addEObj( "Pockmarkedsilverore_4", 2000380, 0, 3632988, 4, { -1.174594f, -1.322406f, -111.266403f }, 0.991789f, 0.000048f, 0); 
    instance.addEObj( "RawNashachite", 2001378, 0, 3955833, 4, { 127.371201f, 28.603861f, -22.765230f }, 0.991760f, -1.270970f, 0); 
    instance.addEObj( "RawNashachite_1", 2001379, 0, 3955838, 4, { 143.765594f, 28.623640f, -17.852400f }, 0.991760f, 0.647398f, 0); 
    instance.addEObj( "RawNashachite_2", 2001380, 0, 3955842, 4, { 122.105797f, 28.727579f, -13.419090f }, 0.991789f, 0.472838f, 0); 
    instance.addEObj( "unknown_19", 2001740, 0, 4164999, 4, { 127.962799f, 28.633619f, -20.062349f }, 1.200000f, 0.000000f, 0); 
    instance.addEObj( "unknown_20", 2005030, 0, 5448851, 4, { -79.052963f, -11.720520f, -70.536484f }, 1.000000f, -0.464448f, 0); 

  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( BrotherfromAnotherMother );