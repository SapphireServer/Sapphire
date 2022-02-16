#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class ThePowerofaTourney : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto BNPC_COMPANION_FLAG = 5888334;
  static constexpr auto BNPC_COMPANION_GENNAI = 5888338;
  static constexpr auto BNPC_COMPANION_MAYAYA = 5888340;
  static constexpr auto BNPC_COMPANION_SEREST = 5888341;
  static constexpr auto BNPC_ENEMY_FLAG = 5888345;
  static constexpr auto EOBJ_KIRAKIRA_COMPANION_FLAG = 5888358;
  static constexpr auto EOBJ_KIRAKIRA_ENEMY_FLAG = 5888366;
  static constexpr auto EOBJ_KIRAKIRA_FUKUHEI = 5888373;
  static constexpr auto EOBJ_SHINGOUDAN_HASSHA = 5888383;
  static constexpr auto POP_RANGE_FUKUHEI = 5888367;
  static constexpr auto POP_RANGE_ENEMY_FLAG = 5888374;
  static constexpr auto POP_RANGE_SHINGOUDAN_HASSHA = 5888387;
  static constexpr auto POP_RANGE_GENNAI_INSTRUCTION_END = 5888692;
  static constexpr auto EVENT_ACTION_01 = 50;
  static constexpr auto EVENT_ACTION_02 = 61;
  static constexpr auto EOBJ_GENNAI_INSTRUCTION_END = 5888701;
  static constexpr auto BEHAVIOR_GENNAI = 30582;
  static constexpr auto BEHAVIOR_MAYAYA = 30583;
  static constexpr auto BEHAVIOR_SEREST = 30584;
  static constexpr auto POP_RANGE_PLAYER_START_FOR_BATTLE = 5889656;
  static constexpr auto BGM_BOSS_BATTLE = 91;
  static constexpr auto BNPC_COMPANION_MAYAYA_BATTLE = 5889759;
  static constexpr auto BNPC_COMPANION_GENNAI_BATTLE = 5889760;
  static constexpr auto BNPC_COMPANION_MCH_DEFENSE_01 = 5889761;
  static constexpr auto BNPC_COMPANION_MCH_DEFENSE_02 = 5889762;
  static constexpr auto BNPC_COMPANION_MCH_DEFENSE_03 = 5889763;
  static constexpr auto BNPC_COMPANION_FORTEMPS_GLA_01 = 5889764;
  static constexpr auto BNPC_COMPANION_FORTEMPS_GLA_02 = 5889765;
  static constexpr auto BNPC_COMPANION_FORTEMPS_GLA_03 = 5889766;
  static constexpr auto BNPC_COMPANION_HAILLENARTE_GLA_01 = 5889767;
  static constexpr auto BNPC_COMPANION_HAILLENARTE_LNC_02 = 5889768;
  static constexpr auto BNPC_COMPANION_HAILLENARTE_LNC_03 = 5889769;
  static constexpr auto BNPC_ENEMY_DZEMAEL_LEADER = 5889773;
  static constexpr auto BNPC_ENEMY_DURENDAIRE_LEADER = 5889774;
  static constexpr auto BNPC_ENEMY_PACK_A_GLA_01 = 5889775;
  static constexpr auto BNPC_ENEMY_PACK_A_GLA_02 = 5889776;
  static constexpr auto BNPC_ENEMY_PACK_A_GLA_03 = 5889777;
  static constexpr auto BNPC_ENEMY_PACK_C_GLA = 5889778;
  static constexpr auto BNPC_ENEMY_PACK_C_LNC = 5889779;
  static constexpr auto BNPC_ENEMY_PACK_C_CNJ = 5889780;
  static constexpr auto BNPC_ENEMY_PACK_B_LNC_01 = 5889781;
  static constexpr auto BNPC_ENEMY_PACK_B_LNC_02 = 5889782;
  static constexpr auto BNPC_ENEMY_PACK_B_LNC_03 = 5889783;
  static constexpr auto BNPC_ENEMY_PACK_D_ARC_01 = 5889944;
  static constexpr auto BNPC_ENEMY_PACK_D_ARC_02 = 5889945;
  static constexpr auto BNPC_ENEMY_PACK_D_ARC_03 = 5889946;
  static constexpr auto BNPC_ENEMY_PACK_D_ARC_04 = 5889947;
  static constexpr auto EOBJ_SKIP_INSTRUCTION = 5890069;
  static constexpr auto EOBJ_HEAL_AREA_COMPANION = 5890169;
  static constexpr auto EOBJ_HEAL_AREA_ENEMY = 5890172;
  static constexpr auto POP_RANGE_HEAL_AREA_COMPANION = 5890186;
  static constexpr auto POP_RANGE_HEAL_AREA_ENEMY = 5890187;
  static constexpr auto STATUS_PARAM_HEAL_AREA = 1684;
  static constexpr auto BNPC_ENEMY_ADD_CNJ_01 = 5890333;
  static constexpr auto BNPC_ENEMY_ADD_CNJ_02 = 5890338;
  static constexpr auto BNPC_ENEMY_ADD_CNJ_03 = 5890339;
  static constexpr auto BNPC_COMPANION_MCH_FUKUHEI_01 = 5891009;
  static constexpr auto BNPC_COMPANION_MCH_FUKUHEI_02 = 5891011;
  static constexpr auto BNPC_COMPANION_MCH_FUKUHEI_03 = 5891012;
  static constexpr auto BNPC_COMPANION_MCH_FUKUHEI_04 = 5891013;
  static constexpr auto BNPC_COMPANION_MCH_FUKUHEI_05 = 5891014;
  static constexpr auto BNPC_COMPANION_SEREST_BATTLE = 5891015;
  static constexpr auto EOBJ_SHINGOUDAN_HASSHA_BATTLE = 5891005;
  static constexpr auto ACTION_SCRIPT_TRIGGER = 3269;
  static constexpr auto ACTION_SCRIPT_TRIGGER_B = 4777;
  static constexpr auto EOBJ_SHINGOUDAN_HASSHA_KIRAKIRA_BATTLE = 5910901;
  static constexpr auto EOBJ_SHINGOUDAN_HASSHA_KIRAKIRA = 5910902;
  static constexpr auto ENPC_SKIP_INSTRUCTION = 5930950;
  static constexpr auto LOC_ACTOR0 = 1014579;
  static constexpr auto LOC_ACTOR1 = 1015124;
  static constexpr auto LOC_ACTOR2 = 1014585;
  static constexpr auto LOC_ACTOR3 = 1014584;
  static constexpr auto LOC_ACTOR4 = 1015056;
  static constexpr auto LOC_ACTOR5 = 1015057;
  static constexpr auto LOC_MARKER_01 = 5932738;
  static constexpr auto LOG_MESSAGE_01 = 5346;

public:
  ThePowerofaTourney() : Sapphire::ScriptAPI::QuestBattleScript( 129 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.addEObj( "Earthspritecore", 2001221, 0, 4317453, 4, { 24.254431f, 33.082001f, 77.006813f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Earthspritecore_1", 2001221, 0, 4317463, 4, { 36.383110f, 29.327450f, 97.069283f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Earthspritecore_2", 2001221, 0, 4317464, 4, { 57.943031f, 25.847639f, 102.136200f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Earthspritecore_3", 2001221, 0, 4317465, 4, { 81.398323f, 27.585211f, 72.983543f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Earthspritecore_4", 2001221, 0, 4317466, 4, { 71.316971f, 31.176069f, 55.866718f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Earthspritecore_5", 2001221, 0, 4317467, 4, { 57.775848f, 35.021290f, 42.465599f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Earthspritecore_6", 2001221, 0, 4317468, 4, { 51.790691f, 29.262480f, 76.374199f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Ceruleumenginepart", 2001209, 0, 4325253, 4, { -132.622604f, 81.568703f, -302.813812f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Ceruleumenginepart_1", 2001209, 0, 4325254, 4, { -137.231293f, 79.621353f, -288.497406f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Ceruleumenginepart_2", 2001209, 0, 4325255, 4, { -117.845001f, 77.342613f, -251.100601f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Ceruleumenginepart_3", 2001209, 0, 4325256, 4, { -106.409897f, 75.083290f, -235.247192f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Ceruleumenginepart_4", 2001209, 0, 4325257, 4, { -98.687920f, 77.810257f, -248.015793f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Ceruleumenginepart_5", 2001209, 0, 4325258, 4, { -146.210403f, 77.813263f, -231.622803f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Ceruleumenginepart_6", 2001209, 0, 4325259, 4, { -156.901703f, 81.039307f, -272.390900f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Ceruleumenginepart_7", 2001209, 0, 4325260, 4, { -161.449203f, 80.542236f, -280.232788f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_0", 2004967, 0, 5346846, 4, { -215.762695f, 72.531464f, -137.223999f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_1", 2003660, 0, 4622487, 4, { 11.235560f, 2.821239f, 321.140198f }, 0.991760f, -1.332051f, 0); 
    instance.addEObj( "Doblyncarcass", 2003664, 0, 4622488, 4, { 11.337400f, 2.700494f, 320.942993f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_2", 2003661, 0, 4622490, 4, { 34.500610f, 12.139650f, 254.291504f }, 0.991760f, -1.227347f, 0); 
    instance.addEObj( "Basiliskcarcass", 2003665, 0, 4622493, 4, { 34.509411f, 12.196140f, 254.139694f }, 0.991760f, 0.407997f, 0); 
    instance.addEObj( "unknown_3", 2003662, 0, 4622494, 4, { 111.039803f, 19.412701f, 121.171898f }, 1.000000f, -0.480383f, 0); 
    instance.addEObj( "Ahrimancarcass", 2003666, 0, 4622505, 4, { 111.192497f, 19.424681f, 121.202400f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_4", 2004001, 0, 4663924, 4, { 111.039803f, 19.412701f, 121.171898f }, 1.000000f, -0.480383f, 0); 
    instance.addEObj( "Destination", 2003667, 0, 4622529, 4, { 139.496094f, 20.302320f, 102.932297f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_5", 2003668, 0, 4622532, 4, { 111.039803f, 19.412701f, 121.171898f }, 1.000000f, -0.480383f, 0); 
    instance.addEObj( "unknown_6", 2003669, 0, 4622535, 4, { 143.256897f, 22.211861f, 99.952293f }, 0.991760f, -1.218139f, 0); 
    instance.addEObj( "unknown_7", 2003669, 0, 4672804, 4, { 143.965698f, 24.472570f, 97.224312f }, 1.000000f, -0.528366f, 0); 
    instance.addEObj( "unknown_8", 2003669, 0, 4672806, 4, { 146.976303f, 22.584490f, 102.764603f }, 1.000000f, -0.758763f, 0); 
    instance.addEObj( "Entrance", 2002710, 0, 4374399, 4, { -295.177307f, 87.969727f, -230.999893f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Entrance_1", 2002711, 0, 4374400, 4, { -113.188698f, 47.372391f, 29.594910f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Entrance_2", 2004608, 0, 5000002, 4, { -105.105698f, 51.999939f, -56.570549f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Processedceruleum", 2002153, 0, 4293192, 4, { -44.022282f, 5.045057f, 417.990204f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Processedceruleum_1", 2002154, 0, 4293193, 4, { -27.000000f, 5.203161f, 412.000000f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Processedceruleum_2", 2002155, 0, 4293194, 4, { -26.000000f, 5.283132f, 424.000000f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_9", 2002620, 0, 4334534, 4, { -44.022301f, 3.781800f, 417.990204f }, 0.991800f, 0.000047f, 0); 
    instance.addEObj( "unknown_10", 2002621, 0, 4334535, 4, { -27.000000f, 3.946200f, 412.000000f }, 1.000000f, -0.000000f, 0); 
    instance.addEObj( "unknown_11", 2002622, 0, 4334536, 4, { -26.000000f, 4.000000f, 424.000000f }, 1.000000f, -0.000000f, 0); 
    instance.addEObj( "ImmortalFlamesstandard", 2002253, 0, 4301858, 4, { -60.000000f, 2.932424f, 354.000000f }, 1.000000f, 0.409934f, 0); 
    instance.addEObj( "ImmortalFlamesstandard_1", 2002254, 0, 4301860, 4, { -77.188232f, -2.772532f, 299.580414f }, 0.991760f, -0.544017f, 0); 
    instance.addEObj( "ImmortalFlamesstandard_2", 2002255, 0, 4301867, 4, { -12.426380f, 14.597930f, 302.749115f }, 1.000000f, -0.109793f, 0); 
    instance.addEObj( "Bubblingcauldron", 2002256, 0, 4301959, 4, { 1.311151f, 5.523519f, 370.846191f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_1", 2002257, 0, 4302006, 4, { 136.919098f, 31.709431f, 20.126650f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Earthcradledaethersand", 2002892, 0, 4499347, 4, { 259.396210f, 25.000000f, 44.199390f }, 1.000000f, 1.549783f, 0); 
    instance.addEObj( "unknown_12", 2004607, 0, 5000001, 4, { -60.850719f, 76.542351f, -204.866196f }, 1.000000f, -0.750814f, 0); 
    instance.addEObj( "unknown_13", 2004662, 0, 5041823, 4, { -140.094604f, 58.324821f, -82.053299f }, 0.750000f, 0.000000f, 0); 
    instance.addEObj( "Inconspicuouslysuspiciousitem", 2004584, 0, 5579049, 4, { -31.810011f, 74.102127f, -67.880402f }, 0.930753f, -0.935053f, 0); 
    instance.addEObj( "Inconspicuouslysuspiciousitem_1", 2004585, 0, 5579050, 4, { -112.687798f, 47.959061f, -17.198910f }, 0.961271f, -0.119064f, 0); 
    instance.addEObj( "Inconspicuouslysuspiciousitem_2", 2004586, 0, 5579051, 4, { 39.601330f, 46.999962f, -10.585770f }, 0.839199f, -0.613074f, 0); 
    instance.addEObj( "Inconspicuouslysuspiciousitem_3", 2004587, 0, 5579052, 4, { -32.369720f, 47.999901f, -71.890587f }, 0.961271f, -1.563805f, 0); 
    instance.addEObj( "unknown_14", 2005162, 0, 5655563, 4, { -111.936600f, 47.372768f, 6.455512f }, 1.000000f, 0.925671f, 0); 
    instance.addEObj( "unknown_15", 2005043, 0, 5579220, 4, { -257.404510f, 60.227310f, -65.842720f }, 1.000000f, 0.000614f, 0); 
    instance.addEObj( "unknown_16", 2005044, 0, 5579226, 4, { -265.613800f, 82.291847f, -178.606903f }, 0.961271f, 0.000144f, 0); 
    instance.addEObj( "Frayedsack", 2002529, 0, 4323822, 4, { -324.697113f, 87.986061f, -133.499893f }, 1.000000f, -1.349706f, 0); 
    instance.addEObj( "Stolenbox", 2002448, 0, 4308579, 4, { 213.706497f, 30.221649f, 61.050491f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_17", 2006183, 0, 5914836, 4, { -78.274399f, 68.351097f, -157.326004f }, 1.000000f, 1.277591f, 0); 
    instance.addEObj( "unknown_18", 2005977, 0, 5899996, 4, { 1.601733f, 21.326450f, 181.886902f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Destination_2", 2005978, 0, 5899997, 4, { 1.601700f, 21.326500f, 181.886902f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_19", 2005973, 0, 5899823, 4, { 6.830000f, 4.980000f, 283.290009f }, 1.000000f, 0.710417f, 0); 
    instance.addEObj( "Destination_3", 2005972, 0, 5899864, 4, { -6.841051f, 5.745786f, 290.887299f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_20", 2005974, 0, 5899898, 4, { 14.348940f, 5.631089f, 276.770386f }, 1.150000f, 0.000000f, 0); 
    instance.addEObj( "Epitaphtofluidity", 2002398, 0, 4306727, 4, { -253.447205f, 60.704689f, -43.897030f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_21", 2002544, 0, 4324095, 4, { -117.235100f, 48.050659f, 37.186161f }, 0.991760f, 1.020544f, 0); 
    instance.addEObj( "???", 2004125, 0, 4722825, 4, { -18.028811f, 22.392469f, 398.605286f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_22", 2002363, 0, 4330174, 4, { 53.850471f, 13.990370f, 236.686096f }, 0.900000f, -0.639573f, 0); 

  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( ThePowerofaTourney );