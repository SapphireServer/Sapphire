#include <ScriptObject.h>
#include <Territory/QuestBattle.h>
#include <Actor/Player.h>
#include <Actor/GameObject.h>
#include <Actor/BNpc.h>

using namespace Sapphire;

class ChasingShadows : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_POP_BOSS = 3802315;
  static constexpr auto INIT_P_POP_IDA = 3802271;
  static constexpr auto INIT_P_POP_PAPARIMO = 3802272;
  static constexpr auto INIT_POP_ENEMY_B_01 = 4094218;
  static constexpr auto INIT_POP_ENEMY_B_02 = 4094220;
  static constexpr auto INIT_POP_ENEMY_B_03 = 4094232;
  static constexpr auto INIT_POP_ENEMY_B_04 = 4094233;
  static constexpr auto INIT_POP_ENEMY_B_05 = 4094474;
  static constexpr auto INIT_POP_ENEMY_B_06 = 4094475;
  static constexpr auto INIT_POP_ENEMY_A_01 = 4094238;
  static constexpr auto INIT_POP_ENEMY_A_02 = 4094239;
  static constexpr auto INIT_POP_ENEMY_A_03 = 4094240;
  static constexpr auto INIT_POP_ENEMY_A_04 = 4094471;
  static constexpr auto INIT_POP_ENEMY_A_05 = 4094472;
  static constexpr auto INIT_POP_ENEMY_A_06 = 4094473;
  static constexpr auto CUT_SCENE_01 = 54;
  static constexpr auto HOW_TO_QIB = 79;

public:
  ChasingShadows() : Sapphire::ScriptAPI::QuestBattleScript( 11 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.addEObj( "unknown_0", 2005192, 5760474, 5766960, 4, { -51.493111f, 0.309087f, 71.436897f }, 1.000000f, -0.000006f, 0); 
    instance.addEObj( "Entrance", 2001710, 4138425, 4138424, 5, { -51.452221f, -36.919319f, 313.645203f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.addEObj( "unknown_1", 2000989, 0, 3823377, 4, { -106.687202f, -4.161253f, -45.643250f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_2", 2000989, 0, 3823379, 4, { -102.746902f, -4.401515f, -49.706520f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_3", 2000989, 0, 3823385, 4, { -104.850403f, -4.340435f, -52.988312f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_4", 2000989, 0, 3823394, 4, { -108.844398f, -4.241153f, -57.010132f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_5", 2000989, 0, 3823397, 4, { -112.659302f, -3.909669f, -61.190521f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_6", 2000989, 0, 3823401, 4, { -118.636398f, -3.518063f, -64.513268f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_7", 2000989, 0, 3823405, 4, { -127.511803f, -2.892640f, -64.478867f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_8", 2000989, 0, 3823412, 4, { -117.353996f, 0.914429f, -50.905491f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_9", 2000989, 0, 3823416, 4, { -111.476799f, -2.111283f, -50.949821f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_10", 2000989, 0, 3823424, 4, { -176.735703f, 41.926590f, -127.297798f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_11", 2000989, 0, 3823431, 4, { -179.201294f, 41.938290f, -125.163200f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_12", 2000989, 0, 3823436, 4, { -185.775101f, 41.956139f, -122.526703f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_13", 2000989, 0, 3823439, 4, { -189.927902f, 41.899849f, -118.977501f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_14", 2000989, 0, 3823443, 4, { -178.272598f, 41.946621f, -131.510803f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_15", 2000989, 0, 3823452, 4, { -182.126297f, 44.093319f, -136.205093f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_16", 2000989, 0, 3823454, 4, { -183.924301f, 45.601589f, -138.584000f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_17", 2000989, 0, 3823474, 4, { -223.369705f, 65.192383f, -170.117294f }, 0.991789f, 0.000048f, 0); 
    instance.addEObj( "unknown_18", 2000989, 0, 3823478, 4, { -227.283203f, 63.083599f, -164.812698f }, 0.991789f, 0.000048f, 0); 
    instance.addEObj( "unknown_19", 2000989, 0, 3823481, 4, { -223.590500f, 61.701698f, -160.998001f }, 0.991789f, 0.000048f, 0); 
    instance.addEObj( "unknown_20", 2000989, 0, 3823485, 4, { -219.593597f, 61.264191f, -160.662399f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_21", 2000989, 0, 3823490, 4, { -224.570404f, 60.000000f, -156.211700f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_22", 2000989, 0, 3823493, 4, { -204.765793f, 57.650002f, -156.189499f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_23", 2000989, 0, 3823593, 4, { -211.505005f, 61.173359f, -163.735794f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_24", 2000989, 0, 3823596, 4, { -215.901398f, 59.658932f, -156.554001f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_25", 2000989, 0, 3823600, 4, { -213.253204f, 60.419998f, -160.382599f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_26", 2000989, 0, 3823601, 4, { -210.509399f, 58.919998f, -157.050201f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_27", 2000989, 0, 3823602, 4, { -223.775101f, 54.810001f, -140.154007f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_28", 2000989, 0, 3823608, 4, { -225.879303f, 58.466068f, -152.178299f }, 0.991789f, 0.000048f, 0); 
    instance.addEObj( "unknown_29", 2000989, 0, 3823617, 4, { -219.775696f, 58.352440f, -151.934097f }, 0.991789f, 0.000048f, 0); 
    instance.addEObj( "unknown_30", 2000989, 0, 3823627, 4, { -225.391098f, 56.995861f, -147.356400f }, 0.991789f, 0.000048f, 0); 
    instance.addEObj( "unknown_31", 2000989, 0, 3824037, 4, { -219.836807f, 59.723690f, -155.840393f }, 0.991789f, 0.000048f, 0); 
    instance.addEObj( "unknown_32", 2000989, 0, 3824042, 4, { -222.053894f, 55.756931f, -142.991104f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_33", 2000989, 0, 3824045, 4, { -212.838898f, 60.007149f, -159.296097f }, 0.991789f, 0.000048f, 0); 
    instance.addEObj( "unknown_34", 2000989, 0, 3824050, 4, { -214.303299f, 55.472000f, -141.913406f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_35", 2000989, 0, 3824055, 4, { -225.233505f, 63.152409f, -164.779999f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_36", 2000989, 0, 3847675, 4, { -219.101303f, 56.439999f, -145.291000f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_37", 2000989, 0, 3847677, 4, { -214.105896f, 57.759998f, -151.189697f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_38", 2000989, 0, 3847679, 4, { -207.002197f, 57.130001f, -152.617004f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_39", 2000989, 0, 3847682, 4, { -213.376205f, 54.914261f, -139.597504f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_40", 2000989, 0, 3847685, 4, { -208.101303f, 54.775131f, -140.642303f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_41", 2000989, 0, 3847687, 4, { -214.426804f, 56.159321f, -145.207993f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "sgpl_w_cnt_box01vfx01", 2001210, 3757610, 3689175, 4, { -120.100601f, 2.405730f, -50.776730f }, 0.991789f, 0.000048f, 0); 
    // States -> off (id: 8) vf_kibako_on (id: 13) 
    instance.addEObj( "sgpl_w_cnt_box01vfx01_1", 2001210, 3757624, 3694554, 4, { -183.001602f, 42.326698f, -124.075798f }, 1.000000f, 1.570451f, 0); 
    // States -> off (id: 8) vf_kibako_on (id: 13) 
    instance.addEObj( "sgpl_w_cnt_box01vfx01_2", 2001210, 3757631, 3694706, 4, { -184.213196f, 45.746380f, -139.125000f }, 1.000000f, 0.000000f, 0); 
    // States -> off (id: 8) vf_kibako_on (id: 13) 
    instance.addEObj( "unknown_42", 2000989, 0, 3915748, 4, { -191.551300f, 41.466888f, -115.594398f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_43", 2000989, 0, 3915752, 4, { -186.462204f, 40.816891f, -115.784302f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_44", 2000989, 0, 3915755, 4, { -191.218307f, 39.463631f, -110.626297f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_45", 2000989, 0, 3915759, 4, { -183.373505f, 37.236629f, -102.680702f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_46", 2000989, 0, 4096563, 4, { -186.592407f, 39.698158f, -111.553299f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_47", 2000989, 0, 4096564, 4, { -181.488998f, 39.372520f, -112.985199f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_48", 2000989, 0, 4096565, 4, { -186.344604f, 36.201031f, -100.555199f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_49", 2000989, 0, 4096566, 4, { -183.355698f, 38.196529f, -107.120499f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_50", 2000989, 0, 4096567, 4, { -178.404999f, 36.720852f, -107.768600f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_51", 2000989, 0, 4096569, 4, { -177.405899f, 35.390881f, -103.573196f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_52", 2000989, 0, 4096570, 4, { -180.021500f, 34.727051f, -98.890297f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_53", 2000989, 0, 4096571, 4, { -182.217804f, 37.690910f, -116.722397f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_54", 2000989, 0, 4096572, 4, { -188.807800f, 38.018028f, -106.121902f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_55", 2000989, 0, 4096573, 4, { -181.309097f, 41.937679f, -130.304199f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_56", 2000989, 0, 4096574, 4, { -182.530396f, 41.919140f, -126.099701f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_57", 2000989, 0, 4096579, 4, { -220.313797f, 59.732182f, -155.807205f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_58", 2000989, 0, 4096580, 4, { -226.965500f, 65.530830f, -170.766495f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_59", 2000989, 0, 4096581, 4, { -215.623703f, 61.881599f, -163.434402f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_60", 2000989, 0, 4096582, 4, { -206.911499f, 60.888500f, -165.796097f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_61", 2000989, 0, 4096583, 4, { -218.172501f, 54.562969f, -138.618103f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_62", 2000989, 0, 4096585, 4, { -222.671097f, 56.018742f, -143.996307f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_63", 2000989, 0, 4096586, 4, { -203.646500f, 55.991982f, -150.696701f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_64", 2000989, 0, 4096587, 4, { -215.205704f, 53.915279f, -133.938293f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Entrance_1", 2001710, 4138438, 4138434, 5, { -46.600349f, -6.881468f, -65.465378f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.addEObj( "Thousandyearplum", 2000690, 0, 3689342, 4, { -288.543304f, 21.433680f, 217.844498f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Thousandyearplum_1", 2000690, 0, 3692613, 4, { -307.137207f, 21.106791f, 215.406006f }, 1.000000f, -1.173999f, 0); 
    instance.addEObj( "Thousandyearplum_2", 2000690, 0, 3692616, 4, { -309.206512f, 21.227430f, 197.596497f }, 1.000000f, 1.119660f, 0); 
    instance.addEObj( "Thousandyearplum_3", 2000690, 0, 3692621, 4, { -339.628204f, 21.199949f, 182.168594f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Thousandyearplum_4", 2000690, 0, 3692622, 4, { -353.139587f, 21.115919f, 196.709503f }, 1.000000f, -1.521987f, 0); 
    instance.addEObj( "Thousandyearplum_5", 2000690, 0, 3692623, 4, { -325.181000f, 21.526649f, 165.853302f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Thousandyearplum_6", 2000690, 0, 3692624, 4, { -307.257202f, 21.154900f, 180.063293f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Thousandyearplum_7", 2000690, 0, 3692626, 4, { -290.881195f, 21.142830f, 187.244507f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Thousandyearplum_8", 2000690, 0, 3692627, 4, { -314.295807f, 21.638201f, 153.309998f }, 1.000000f, 0.649705f, 0); 
    instance.addEObj( "偽造品（�）", 2001513, 0, 4055157, 4, { -216.996704f, 2.351378f, -106.347504f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "偽造品（�）_1", 2001513, 0, 4055416, 4, { -230.467896f, 1.016571f, -80.124969f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "偽造品（�）_2", 2001513, 0, 4055417, 4, { -193.487503f, 3.305519f, -105.677299f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "偽造品（�）_3", 2001513, 0, 4055418, 4, { -197.272202f, 2.239987f, -83.755989f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "偽造品（�）_4", 2001513, 0, 4055419, 4, { -171.876205f, 1.443221f, -46.679409f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "偽造品（�）_5", 2001513, 0, 4055420, 4, { -172.634094f, 2.128752f, -90.899872f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "偽造品（�）_6", 2001513, 0, 4055421, 4, { -175.727707f, 2.985368f, -116.684196f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "偽造品（�）_7", 2001513, 0, 4055423, 4, { -193.761200f, 2.448251f, -55.852360f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Poisonousmushroom", 2001224, 0, 4326452, 4, { -302.516815f, 61.436420f, -25.797960f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Poisonousmushroom_1", 2001224, 0, 4326453, 4, { -344.984314f, 59.804249f, -18.729429f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Poisonousmushroom_2", 2001224, 0, 4326454, 4, { -303.175995f, 62.309429f, -40.030079f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Poisonousmushroom_3", 2001224, 0, 4326455, 4, { -308.257599f, 61.464870f, 15.053400f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Poisonousmushroom_4", 2001224, 0, 4327283, 4, { -327.718506f, 60.582130f, 27.168421f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Poisonousmushroom_5", 2001224, 0, 4327285, 4, { -287.753601f, 62.810261f, 8.191589f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Golemsoulstone", 2001228, 0, 4309325, 4, { -484.262207f, 68.893761f, -283.487610f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Golemsoulstone_1", 2001228, 0, 4309326, 4, { -467.243896f, 65.401413f, -267.285187f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Golemsoulstone_2", 2001228, 0, 4309327, 4, { -526.568726f, 48.359058f, -242.947403f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Golemsoulstone_3", 2001228, 0, 4309329, 4, { -494.978912f, 56.382858f, -228.952805f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Golemsoulstone_4", 2001228, 0, 4309330, 4, { -476.322601f, 61.424740f, -239.722397f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Golemsoulstone_5", 2001228, 0, 4309331, 4, { -461.329712f, 57.476330f, -209.589706f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Golemsoulstone_6", 2001228, 0, 4309332, 4, { -475.152313f, 71.080002f, -299.380310f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Golemsoulstone_7", 2001228, 0, 4309335, 4, { -504.381104f, 72.740913f, -289.261993f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Leiasegg", 2000990, 0, 3867263, 4, { -189.589203f, -26.526510f, 295.983887f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_65", 2005631, 0, 5877891, 4, { 8.426797f, -1.183724f, 29.134689f }, 1.000000f, -1.529657f, 0); 
    instance.addEObj( "unknown_66", 2005709, 0, 5883284, 4, { 8.402201f, -1.185564f, 29.099461f }, 2.937301f, 0.000000f, 0); 
    instance.addEObj( "Entrance_2", 2002697, 0, 4374469, 4, { -114.426003f, -39.751492f, 337.500000f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Entrance_3", 2002701, 0, 4374470, 4, { -572.869080f, 67.006157f, 69.255493f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_67", 2002391, 0, 4306511, 4, { -271.847504f, 19.653130f, 97.400490f }, 0.450000f, 0.000048f, 0); 
    instance.addEObj( "Destination", 2002392, 0, 4306566, 4, { -416.543610f, 61.004581f, -148.623001f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_68", 2002393, 0, 4306573, 4, { -415.938599f, 61.037182f, -147.957199f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_1", 2002408, 0, 4307312, 4, { -316.269989f, 21.219999f, 179.729996f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_69", 2002526, 0, 4322884, 4, { -320.000000f, 22.343000f, 192.000000f }, 1.400000f, 0.000000f, 0); 
    instance.addEObj( "Manorforegate", 2003023, 0, 4515177, 4, { -576.114685f, 68.156097f, 69.422203f }, 1.000000f, -1.570796f, 0); 
    instance.addEObj( "Vegetablescraps", 2004432, 0, 4880287, 4, { -64.613472f, 0.000000f, -5.223570f }, 0.700000f, 0.000000f, 0); 
    instance.addEObj( "Vegetablescraps_1", 2004433, 0, 4880288, 4, { -47.285591f, -0.000000f, -3.996141f }, 0.700000f, 0.000000f, 0); 
    instance.addEObj( "Vegetablescraps_2", 2004434, 0, 4880289, 4, { -51.745281f, 0.200000f, 16.131550f }, 0.700000f, 0.000000f, 0); 
    instance.addEObj( "Vegetablescraps_3", 2004435, 0, 4880290, 4, { -63.280109f, 0.200000f, 16.049021f }, 0.700000f, 0.000000f, 0); 
    instance.addEObj( "Vegetablescraps_4", 2004436, 0, 4880292, 4, { -58.040699f, 0.200000f, 5.385311f }, 0.700000f, 0.000000f, 0); 
    instance.addEObj( "Gigantickrakkaroot", 2004437, 0, 4880306, 4, { -46.908070f, 1.359704f, -34.446602f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Gysahlgreens", 2000999, 0, 3824569, 4, { -39.607590f, 0.306507f, -27.843050f }, 1.000000f, -0.896479f, 0); 
    instance.addEObj( "Feedingtrough", 2001000, 0, 3824611, 4, { -52.674801f, 0.690364f, 2.307330f }, 1.000000f, 0.780778f, 0); 
    instance.addEObj( "Feedingtrough_1", 2001001, 0, 3824623, 4, { -58.842449f, 0.688565f, 2.268953f }, 1.000000f, -1.391104f, 0); 
    instance.addEObj( "Feedingtrough_2", 2001002, 0, 3824646, 4, { 25.841999f, -7.353338f, 83.878792f }, 0.961271f, 0.000144f, 0); 
    instance.addEObj( "Warmegg", 2000053, 0, 1933046, 4, { -189.589203f, -26.526501f, 295.983887f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_70", 2001837, 0, 4189795, 4, { -189.148499f, -26.686420f, 295.526611f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Bluetrumpet", 2000748, 0, 3800559, 4, { -189.227203f, 30.442329f, -98.832733f }, 0.991789f, 0.000048f, 0); 
    instance.addEObj( "Bluetrumpet_1", 2000749, 0, 3800562, 4, { -164.081207f, 23.030020f, -86.162239f }, 0.991789f, 0.000048f, 0); 
    instance.addEObj( "Bluetrumpet_2", 2000750, 0, 3800569, 4, { -151.234299f, 14.383330f, -73.007423f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Bluetrumpet_3", 2000751, 0, 3800617, 4, { -169.299194f, 18.604219f, -72.127853f }, 0.961271f, 0.000144f, 0); 
    instance.addEObj( "Diremiteeggs", 2001083, 0, 3856505, 4, { -184.488998f, 41.923210f, -128.647995f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Diremiteeggs_1", 2001084, 0, 3856507, 4, { -127.775902f, -1.133527f, -60.947330f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Guttedcampfire", 2000688, 0, 3687683, 4, { -98.488190f, 3.855461f, -145.340195f }, 1.000000f, 1.533667f, 0); 
    instance.addEObj( "Wornleatherbag", 2000689, 0, 3687684, 4, { -95.449173f, 3.505787f, -150.786896f }, 0.991789f, 0.000048f, 0); 
    instance.addEObj( "Vultureegg", 2001006, 0, 3838947, 4, { 99.678078f, -15.718380f, 193.019196f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Barrow", 2001007, 0, 3839182, 4, { -98.279739f, -21.903790f, 311.977509f }, 1.000000f, 0.940114f, 0); 
    instance.addEObj( "Barrow_1", 2001008, 0, 3839183, 4, { -146.051102f, -22.564199f, 354.029205f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Barrow_2", 2001009, 0, 3839184, 4, { -146.016998f, -22.573910f, 266.872803f }, 1.000000f, 0.963927f, 0); 
    instance.addEObj( "unknown_71", 2001844, 0, 4192108, 4, { -146.072693f, -22.656740f, 353.832092f }, 1.250000f, 0.000000f, 0); 
    instance.addEObj( "Wellwornfishingrod", 2000685, 0, 3684554, 4, { 370.194000f, -31.954121f, 455.661285f }, 1.000000f, -0.220264f, 0); 
    instance.addEObj( "Crayfishballs", 2001013, 0, 3842357, 4, { 223.775208f, -32.082130f, 324.501404f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "MunTuybeans", 2001014, 0, 3842359, 4, { 221.124893f, -32.106178f, 324.497314f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Platemail", 2001015, 0, 3842360, 4, { 219.229294f, -32.014702f, 323.927307f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Fallencargo", 2001016, 0, 3842564, 4, { 154.196701f, -24.314859f, 503.493011f }, 0.961271f, 0.000144f, 0); 
    instance.addEObj( "Chocobocarriage", 2001017, 0, 3842565, 4, { 150.774307f, -23.544720f, 490.653809f }, 0.961271f, 1.220378f, 0); 
    instance.addEObj( "Brokencrate", 2001086, 0, 3862290, 4, { 151.079498f, -23.709080f, 499.312012f }, 0.991789f, 0.000048f, 0); 
    instance.addEObj( "Brokencrate_1", 2001087, 0, 3862291, 4, { 153.892197f, -24.637360f, 512.884521f }, 0.991789f, 0.000048f, 0); 
    instance.addEObj( "Brokencrate_2", 2001088, 0, 3862293, 4, { 159.563599f, -24.704411f, 516.929810f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Fallencargo_1", 2001018, 0, 3875402, 4, { 161.696503f, -24.596640f, 521.147705f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_72", 2001845, 0, 4192100, 4, { 150.107193f, -23.419970f, 489.839905f }, 1.500000f, 0.000000f, 0); 
    instance.addEObj( "Gysahlgreens_1", 2001467, 0, 4331366, 4, { -54.716320f, 1.473240f, -36.668701f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Gysahlgreens_2", 2001467, 0, 4331374, 4, { -50.674389f, 1.449585f, -41.520790f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Gysahlgreens_3", 2001467, 0, 4331375, 4, { -44.392010f, 1.419067f, -36.840450f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_73", 2004688, 0, 5020959, 4, { 128.063797f, -6.017008f, -53.698460f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_2", 2004270, 0, 4745132, 4, { 7.216083f, 4.765921f, -262.980408f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_74", 2004271, 0, 4745133, 4, { 6.659961f, 4.617394f, -263.823303f }, 0.500000f, 0.000000f, 0); 
    instance.addEObj( "unknown_75", 2004641, 0, 5017655, 4, { -378.257904f, 63.430069f, -205.382706f }, 1.000000f, -0.724250f, 0); 
    instance.addEObj( "unknown_76", 2004642, 0, 5017658, 4, { -378.378601f, 63.435390f, -205.480606f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_3", 2005000, 0, 5392664, 4, { 12.529400f, -8.185400f, 103.547096f }, 1.000000f, 0.464809f, 0); 
    instance.addEObj( "unknown_77", 2005022, 0, 5425089, 4, { 6.499477f, -8.002163f, 100.010300f }, 1.000000f, 0.706921f, 0); 
    instance.addEObj( "Destination_4", 2005049, 0, 5501848, 4, { 168.416107f, -31.543890f, 380.226898f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_5", 2005050, 0, 5501849, 4, { 145.915100f, -24.957020f, 404.797089f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_6", 2005051, 0, 5501850, 4, { 116.441498f, -18.844971f, 449.057587f }, 1.000000f, -1.214116f, 0); 

  }
  enum vars
  {
    SET_1_SPAWNED,
    SET_2_SPAWNED,
    SET_3_SPAWNED,
    SUCCESS_CALLED,
  };

  void onPlayerSetup( Sapphire::QuestBattle& instance, Entity::Player& player ) override
  {
    player.setRot( 3.f );
    player.setPos( { 323.f, -1.28f, -320.f } );
  }


  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {
    auto pair1Spawnd = instance.getDirectorVar( SET_1_SPAWNED );
    auto pair2Spawnd = instance.getDirectorVar( SET_2_SPAWNED );
    auto pair3Spawnd = instance.getDirectorVar( SET_3_SPAWNED );
    auto successCalled = instance.getDirectorVar( SUCCESS_CALLED );

    auto boss = instance.getActiveBNpcByLayoutId( INIT_POP_BOSS );
    auto ida = instance.getActiveBNpcByLayoutId( INIT_P_POP_IDA );
    auto papa = instance.getActiveBNpcByLayoutId( INIT_P_POP_PAPARIMO );
    auto pPlayer = instance.getPlayerPtr();

    uint32_t bossHpPercent = 0;
    if( boss )
      bossHpPercent = boss->getHpPercent();

    if( pPlayer && !pPlayer->isAlive() )
    {
      instance.fail();
      return;
    }

    if( !ida || !papa )
      return;

    if( pair1Spawnd == 0 && bossHpPercent <= 75 )
    {
      instance.setDirectorVar( SET_1_SPAWNED, 1 );
      auto a2 = instance.createBNpcFromLayoutId( INIT_POP_ENEMY_B_03, 1440, Common::BNpcType::Enemy );
      auto a3 = instance.createBNpcFromLayoutId( INIT_POP_ENEMY_B_04, 1440, Common::BNpcType::Enemy );
      a2->setFlag( Entity::NoDeaggro );
      a3->setFlag( Entity::NoDeaggro );

      a2->hateListAdd( ida, 10000 );
      a3->hateListAdd( ida, 10000 );
      a2->hateListAdd( papa, 10000 );
      a3->hateListAdd( papa, 10000 );

      auto a4 = instance.createBNpcFromLayoutId( INIT_POP_ENEMY_A_01, 300, Common::BNpcType::Enemy );
      auto a5 = instance.createBNpcFromLayoutId( INIT_POP_ENEMY_A_02, 300, Common::BNpcType::Enemy );
      a4->setFlag( Entity::NoDeaggro );
      a5->setFlag( Entity::NoDeaggro );

      auto pPlayer = instance.getPlayerPtr();
      a4->hateListAdd( pPlayer, 1 );
      a5->hateListAdd( pPlayer, 1 );
    }

    if( pair2Spawnd == 0 && bossHpPercent <= 50 )
    {
      instance.setDirectorVar( SET_2_SPAWNED, 1 );
      auto a2 = instance.createBNpcFromLayoutId( INIT_POP_ENEMY_B_05, 1440, Common::BNpcType::Enemy );
      auto a3 = instance.createBNpcFromLayoutId( INIT_POP_ENEMY_B_06, 1440, Common::BNpcType::Enemy );
      a2->setFlag( Entity::NoDeaggro );
      a3->setFlag( Entity::NoDeaggro );

      a2->hateListAdd( ida, 10000 );
      a3->hateListAdd( ida, 10000 );
      a2->hateListAdd( papa, 10000 );
      a3->hateListAdd( papa, 10000 );

      auto a4 = instance.createBNpcFromLayoutId( INIT_POP_ENEMY_A_03, 300, Common::BNpcType::Enemy );
      auto a5 = instance.createBNpcFromLayoutId( INIT_POP_ENEMY_A_04, 300, Common::BNpcType::Enemy );
      a4->setFlag( Entity::NoDeaggro );
      a5->setFlag( Entity::NoDeaggro );

      auto pPlayer = instance.getPlayerPtr();
      a4->hateListAdd( pPlayer, 1 );
      a5->hateListAdd( pPlayer, 1 );

    }

    if( pair3Spawnd == 0 && bossHpPercent <= 25 )
    {
      instance.setDirectorVar( SET_3_SPAWNED, 1 );

      auto a4 = instance.createBNpcFromLayoutId( INIT_POP_ENEMY_A_05, 300, Common::BNpcType::Enemy );
      auto a5 = instance.createBNpcFromLayoutId( INIT_POP_ENEMY_A_06, 300, Common::BNpcType::Enemy );
      a4->setFlag( Entity::NoDeaggro );
      a5->setFlag( Entity::NoDeaggro );

      auto pPlayer = instance.getPlayerPtr();
      a4->hateListAdd( pPlayer, 1 );
      a5->hateListAdd( pPlayer, 1 );
    }

    if( instance.getCountEnemyBNpc() == 0 && successCalled == 0 )
    {
      instance.setDirectorVar( SUCCESS_CALLED, 1 );
      instance.success( 6 );
      return;
    }
  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {
    eventMgr().playScene( player, instance.getDirectorId(), 1,
                          NO_DEFAULT_CAMERA | CONDITION_CUTSCENE | SILENT_ENTER_TERRI_ENV |
                          HIDE_HOTBAR | SILENT_ENTER_TERRI_BGM | SILENT_ENTER_TERRI_SE |
                          DISABLE_STEALTH | 0x00100000 | LOCK_HUD | LOCK_HOTBAR |
                          // todo: wtf is 0x00100000
                          DISABLE_CANCEL_EMOTE, [ & ]( Entity::Player& player, const Event::SceneResult& result )
                          {
                            player.setOnEnterEventDone( true );
                          } );

  }

  void onDutyComplete( QuestBattle& instance, Entity::Player& player ) override
  {
    auto idx = player.getQuestIndex( instance.getQuestId() );
    if( idx == -1 )
      return;
    auto& quest = player.getQuestByIndex( idx );
    quest.setSeq( 2 );
  }

  void onDutyCommence( QuestBattle& instance, Entity::Player& player ) override
  {
    auto boss = instance.createBNpcFromLayoutId( INIT_POP_BOSS, 21141, Common::BNpcType::Enemy );
    auto a2 = instance.createBNpcFromLayoutId( INIT_POP_ENEMY_B_01, 1440, Common::BNpcType::Enemy );
    auto a3 = instance.createBNpcFromLayoutId( INIT_POP_ENEMY_B_02, 1440, Common::BNpcType::Enemy );

    auto ida = instance.createBNpcFromLayoutId( INIT_P_POP_IDA, 27780, Common::BNpcType::Friendly );
    auto papa = instance.createBNpcFromLayoutId( INIT_P_POP_PAPARIMO, 27780, Common::BNpcType::Friendly );
    boss->setFlag( Entity::NoDeaggro );
    a2->setFlag( Entity::NoDeaggro );
    a3->setFlag( Entity::NoDeaggro );
    ida->setFlag( Entity::NoDeaggro );
    papa->setFlag( Entity::NoDeaggro );
    boss->hateListAdd( ida, 10000 );
    boss->hateListAdd( papa, 10000 );
    boss->hateListAdd( player.getAsPlayer(), 1 );

    a2->hateListAdd( player.getAsPlayer(), 1 );
    a2->hateListAdd( ida, 10000 );
    a2->hateListAdd( papa, 10000 );

    a3->hateListAdd( player.getAsPlayer(), 1 );
    a3->hateListAdd( ida, 10000 );
    a3->hateListAdd( papa, 10000 );

    ida->hateListAdd( boss, 10000 );
    ida->hateListAdd( a2, 9999 );
    ida->hateListAdd( a3, 9999 );

    papa->hateListAdd( boss, 10000 );
    papa->hateListAdd( a2, 9999 );
    papa->hateListAdd( a3, 9999 );
  }

};

EXPOSE_SCRIPT( ChasingShadows );
