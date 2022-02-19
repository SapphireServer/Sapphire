#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class BleederofthePack : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_P_POP_1ST_01 = 4126558;
  static constexpr auto INIT_POP_1ST_01 = 4126546;
  static constexpr auto INIT_POP_1ST_02 = 4126547;
  static constexpr auto INIT_POP_1ST_03 = 4126548;
  static constexpr auto INIT_POP_1ST_04 = 4126549;
  static constexpr auto INIT_POP_1ST_05 = 4126550;
  static constexpr auto INIT_POP_1ST_06 = 4126551;
  static constexpr auto INIT_POP_2ST_01 = 4126569;
  static constexpr auto INIT_POP_2ST_02 = 4126570;
  static constexpr auto INIT_POP_2ST_03 = 4126571;
  static constexpr auto INIT_POP_2ST_04 = 4126573;
  static constexpr auto INIT_POP_2ST_05 = 4126574;
  static constexpr auto INIT_POP_2ST_06 = 4126575;
  static constexpr auto INIT_POP_3ST_01 = 4126627;
  static constexpr auto INIT_POP_3ST_02 = 4126628;
  static constexpr auto INIT_POP_3ST_03 = 4126629;
  static constexpr auto INIT_POP_3ST_04 = 4126631;
  static constexpr auto INIT_POP_3ST_05 = 4126632;
  static constexpr auto INIT_POP_3ST_06 = 4126633;
  static constexpr auto INIT_POP_4ST_01 = 4126649;
  static constexpr auto INIT_POP_4ST_02 = 4126655;
  static constexpr auto INIT_POP_4ST_03 = 4126656;
  static constexpr auto INIT_POP_4ST_04 = 4126657;
  static constexpr auto INIT_POP_4ST_05 = 4126658;
  static constexpr auto INIT_POP_5ST_01 = 4126659;
  static constexpr auto P_WARP_01 = 4127467;
  static constexpr auto INIT_ENPC_POP_01 = 4097270;
  static constexpr auto BGM_01 = 37;
  static constexpr auto LOC_ACTOR0 = 1003497;
  static constexpr auto LOC_ACTOR1 = 1002696;
  static constexpr auto LOC_ACTOR2 = 1003498;
  static constexpr auto LOC_ACTOR3 = 1003499;
  static constexpr auto LOC_POS_ACTOR0 = 4097270;
  static constexpr auto LOC_POS_ACTOR1 = 4164696;
  static constexpr auto LOC_POS_ACTOR2 = 4164697;
  static constexpr auto LOC_ACTION1 = 961;
  static constexpr auto LOC_ACTION2 = 824;
  static constexpr auto LOC_ACTION3 = 795;
  static constexpr auto LOC_ACTION4 = 934;

public:
  BleederofthePack() : Sapphire::ScriptAPI::QuestBattleScript( 27 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.addEObj( "Companychest", 2000470, 4255821, 4255820, 4, { -149.301498f, 4.552717f, -91.365868f }, 0.991760f, -0.619932f, 0); 
    instance.addEObj( "Huntboard", 2004440, 2217635, 4889667, 4, { -152.330902f, 4.230781f, -92.351143f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "sgpl_a_evt_bind_collision01", 2001681, 4105389, 4105388, 4, { 44.785252f, 4.000000f, -150.783905f }, 1.000000f, 0.314892f, 0); 
    // States -> collision_on (id: 14) collision_off (id: 15) 
    instance.addEObj( "sgpl_a_evt_bind_collision01_1", 2001682, 4105393, 4105391, 4, { 30.722040f, 4.644863f, -140.090500f }, 1.000000f, 0.000000f, 0); 
    // States -> collision_on (id: 14) collision_off (id: 15) 
    instance.addEObj( "sgpl_a_evt_bind_collision01_2", 2001683, 4105395, 4105394, 4, { 23.643730f, 5.152849f, -152.244293f }, 1.000000f, 0.000000f, 0); 
    // States -> collision_on (id: 14) collision_off (id: 15) 
    instance.addEObj( "sgpl_a_evt_bind_collision01_3", 2001706, 4126566, 4126565, 4, { 41.066471f, 4.000000f, -159.784195f }, 1.000000f, 0.000000f, 0); 
    // States -> collision_on (id: 14) collision_off (id: 15) 
    instance.addEObj( "unknown_0", 2000608, 2091611, 4324003, 4, { 32.197731f, 8.099938f, -119.738602f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_1", 2000608, 2091609, 4324012, 4, { 47.756962f, 8.099940f, -92.824043f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_2", 2000608, 2091610, 4324014, 4, { 5.026391f, 8.099938f, -104.277901f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_3", 2002999, 0, 4511449, 4, { -69.924294f, 4.000000f, -117.409302f }, 1.000000f, 1.457064f, 0); 
    instance.addEObj( "Conspicuouscrates", 2003000, 0, 4511461, 4, { -144.792892f, 12.002940f, -3.465488f }, 1.000000f, 0.124494f, 0); 
    instance.addEObj( "Conspicuouscrates_1", 2003001, 0, 4511524, 4, { -144.792892f, 12.006590f, -3.465488f }, 1.000000f, 0.124494f, 0); 
    instance.addEObj( "unknown_4", 2003002, 0, 4511529, 4, { -146.013596f, 12.000000f, -5.172852f }, 0.991760f, 0.391955f, 0); 
    instance.addEObj( "unknown_5", 2003002, 0, 4511534, 4, { -145.996506f, 11.978270f, -3.452308f }, 0.991760f, 1.250262f, 0); 
    instance.addEObj( "unknown_6", 2003002, 0, 4511536, 4, { -143.861801f, 11.978270f, -3.127099f }, 0.991760f, 0.230245f, 0); 
    instance.addEObj( "unknown_7", 2003003, 0, 4511541, 4, { -145.240295f, 12.043620f, -2.238888f }, 1.174927f, 1.197722f, 0); 
    instance.addEObj( "unknown_8", 2001727, 0, 4162335, 4, { 24.351500f, 7.199998f, -102.732201f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Fadedgilcoins", 2001280, 0, 3947581, 4, { -162.442902f, 17.486099f, 60.224781f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Fadedgilcoins_1", 2001281, 0, 3947688, 4, { -254.726807f, 18.000000f, 67.353157f }, 0.930753f, 0.000240f, 0); 
    instance.addEObj( "Fadedgilcoins_2", 2001282, 0, 3947846, 4, { -21.744141f, 10.018190f, -78.477226f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Fadedgilcoins_3", 2001283, 0, 3947866, 4, { 37.064110f, 7.249538f, -98.893761f }, 0.991789f, 0.000048f, 0); 
    instance.addEObj( "Fadedgilcoins_4", 2001285, 0, 3948843, 4, { -80.338791f, 0.700921f, -59.525490f }, 0.991789f, 0.000048f, 0); 
    instance.addEObj( "Strikingdummy", 2001514, 0, 4055676, 4, { -105.897400f, 4.000000f, -107.874001f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Strikingdummy_1", 2001515, 0, 4055678, 4, { -108.155701f, 4.000000f, -105.798698f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Strikingdummy_2", 2001516, 0, 4055679, 4, { -77.768631f, 4.000000f, -129.233795f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Strikingdummy_3", 2001517, 0, 4055680, 4, { -74.850319f, 4.000000f, -130.992599f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Strikingdummy_4", 2001518, 0, 4055682, 4, { -71.576271f, 4.000000f, -132.753403f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Strikingdummy_5", 2001718, 0, 4148351, 4, { -108.201698f, 4.989685f, -105.760300f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Strikingdummy_6", 2001719, 0, 4148352, 4, { -105.936501f, 4.965500f, -107.861801f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Strikingdummy_7", 2001720, 0, 4148353, 4, { -77.893806f, 5.034212f, -129.178299f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Strikingdummy_8", 2001721, 0, 4148354, 4, { -74.883957f, 4.902517f, -130.975800f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Strikingdummy_9", 2001722, 0, 4148355, 4, { -71.704048f, 5.038770f, -132.640503f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Strikingdummy_10", 2001790, 0, 4175145, 4, { -105.597397f, 4.000000f, -107.573997f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Strikingdummy_11", 2001791, 0, 4175146, 4, { -107.855698f, 4.000000f, -105.498703f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Strikingdummy_12", 2001792, 0, 4175147, 4, { -77.468628f, 4.000000f, -128.933807f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Strikingdummy_13", 2001793, 0, 4175148, 4, { -74.550323f, 4.000000f, -130.692596f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Strikingdummy_14", 2001794, 0, 4175149, 4, { -71.276268f, 4.000000f, -132.453400f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Strikingdummy_15", 2001798, 0, 4175151, 4, { -107.901703f, 4.989685f, -105.460297f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Strikingdummy_16", 2001799, 0, 4175152, 4, { -105.636497f, 4.965500f, -107.561798f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Strikingdummy_17", 2001800, 0, 4175153, 4, { -77.593803f, 5.034212f, -128.878296f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Strikingdummy_18", 2001801, 0, 4175154, 4, { -74.583946f, 4.902517f, -130.675797f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Strikingdummy_19", 2001802, 0, 4175155, 4, { -71.404053f, 5.038770f, -132.340500f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_9", 2001855, 0, 4236085, 4, { -74.549492f, 1.998901f, -42.330700f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_10", 2001858, 0, 4236092, 4, { -21.827080f, 4.000000f, -145.139603f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Entrance", 2004333, 0, 4841588, 4, { -31.627710f, 83.199989f, -9.434661f }, 0.781000f, 0.000000f, 0); 
    instance.addEObj( "unknown_11", 2002599, 0, 4331656, 4, { -53.801319f, 84.180733f, -3.045938f }, 1.000000f, 0.257016f, 0); 
    instance.addEObj( "unknown_12", 2005975, 0, 5900174, 4, { -20.222401f, 83.199997f, -1.470200f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Gangplank", 2001667, 0, 4103454, 4, { -45.336491f, 84.112282f, -0.782598f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_13", 2001673, 0, 4105162, 4, { -53.769249f, 84.138092f, -3.106336f }, 1.000000f, 0.269064f, 0); 
    instance.addEObj( "unknown_14", 2001687, 0, 4105450, 4, { -53.769299f, 84.138100f, -3.106300f }, 1.000000f, 0.269065f, 0); 
    instance.addEObj( "unknown_15", 2001688, 0, 4105451, 4, { -53.769299f, 84.138100f, -3.106300f }, 1.000000f, 0.269065f, 0); 
    instance.addEObj( "unknown_16", 2001854, 0, 4217237, 4, { 23.093679f, 6.999992f, -86.289658f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "MarkoftheDuskTrader", 2004594, 0, 4982836, 4, { -211.852798f, 19.620060f, 74.792130f }, 0.991760f, 1.283258f, 0); 
    instance.addEObj( "unknown_17", 2004674, 0, 5018811, 4, { -161.551102f, 12.604210f, -0.449216f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_18", 2004675, 0, 5018813, 4, { -71.322380f, 4.651390f, -107.042099f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "???", 2004112, 0, 4722118, 4, { -122.176003f, 4.031771f, -107.250999f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_19", 2004890, 0, 5119584, 4, { -196.586807f, 18.949970f, 61.085331f }, 0.600000f, 0.447360f, 0); 
    instance.addEObj( "Narrowgap", 2004885, 0, 5119653, 4, { -206.488297f, 19.203131f, 49.958370f }, 0.750000f, -0.324806f, 0); 
    instance.addEObj( "Narrowgap_1", 2004886, 0, 5119655, 4, { -245.193802f, 19.177999f, 63.680901f }, 0.747620f, -0.330557f, 0); 
    instance.addEObj( "Narrowgap_2", 2004887, 0, 5119656, 4, { -194.092804f, 19.152691f, 91.340134f }, 0.750000f, 0.342493f, 0); 
    instance.addEObj( "Narrowgap_3", 2004888, 0, 5119657, 4, { -243.610901f, 20.084900f, 104.425697f }, 0.750000f, -1.239528f, 0); 
    instance.addEObj( "Destination", 2004889, 0, 5121155, 4, { -136.539398f, 12.000000f, 23.541731f }, 1.000000f, 1.081450f, 0); 
    instance.addEObj( "Destination_1", 2005193, 0, 5668682, 4, { -38.091930f, 4.000000f, -141.329895f }, 1.000000f, 0.285269f, 0); 

  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( BleederofthePack );