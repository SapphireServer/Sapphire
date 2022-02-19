#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class FeatherintheCap : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto BNPC_LUNA_01 = 5886119;
  static constexpr auto BNPC_SEBASTIAN_01 = 5886120;
  static constexpr auto BNPC_HUNTER_01 = 5886154;
  static constexpr auto BNPC_HUNTER_02 = 5886155;
  static constexpr auto BNPC_HUNTER_03 = 5886156;
  static constexpr auto BNPC_HUNTER_04 = 5886157;
  static constexpr auto BNPC_P1_GLD_01 = 5886121;
  static constexpr auto BNPC_P1_LNC_01 = 5886122;
  static constexpr auto BNPC_P1_LNC_02 = 5886123;
  static constexpr auto BNPC_P2_ACN_01 = 5886146;
  static constexpr auto BNPC_P2_LNC_01 = 5886147;
  static constexpr auto BNPC_P2_LNC_02 = 5886148;
  static constexpr auto BNPC_P2_ARC_01 = 5886149;
  static constexpr auto BNPC_P2_ARC_02 = 5886150;
  static constexpr auto BNPC_P2_ARC_03 = 5886151;
  static constexpr auto BNPC_P2_ARC_04 = 5886152;
  static constexpr auto BNPC_P2_ARC_05 = 5886153;
  static constexpr auto BNPC_P2_BANDERSNATCH_01 = 5890660;
  static constexpr auto ACTION_SUMMON = 4779;
  static constexpr auto LOC_ACTOR_HUNTER_01 = 1015097;
  static constexpr auto LOC_ACTOR_HUNTER_02 = 1015098;
  static constexpr auto LOC_ACTOR_HUNTER_03 = 1015099;
  static constexpr auto LOC_ACTOR_HUNTER_04 = 1015100;
  static constexpr auto LOC_ACTOR_JANE = 1014691;
  static constexpr auto LOC_ACTOR_QUIMP = 1014685;
  static constexpr auto LOC_ACTOR_LEVE = 1014684;
  static constexpr auto LOC_ACTOR_CELIE = 1015074;
  static constexpr auto LOC_ACTOR_ENEMY_01 = 1015101;
  static constexpr auto LOC_ACTOR_ENEMY_02 = 1015102;
  static constexpr auto LOC_ACTOR_ENEMY_03 = 1015103;
  static constexpr auto LOC_LEVEL_ENEMY_01 = 5936432;
  static constexpr auto LOC_LEVEL_LEVE_01 = 5935764;
  static constexpr auto LOC_LEVEL_QUIMP_01 = 5935771;
  static constexpr auto LOC_BGM0 = 39;

public:
  FeatherintheCap() : Sapphire::ScriptAPI::QuestBattleScript( 121 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.addEObj( "Companychest", 2000470, 4255757, 4255756, 4, { 90.371834f, 41.346722f, 60.735680f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Huntboard", 2004438, 4887771, 4889754, 4, { 94.366341f, 40.247021f, 60.480110f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "sgpl_a_evt_bind_collision01", 2001679, 4105300, 4105298, 4, { -57.398460f, 17.999990f, 0.063036f }, 1.000000f, 0.000000f, 0); 
    // States -> collision_on (id: 14) collision_off (id: 15) 
    instance.addEObj( "sgpl_a_evt_bind_collision01_1", 2001680, 4105307, 4105305, 4, { -35.055031f, 19.999969f, -0.014301f }, 1.000000f, 0.000000f, 0); 
    // States -> collision_on (id: 14) collision_off (id: 15) 
    instance.addEObj( "unknown_0", 2004875, 0, 5071851, 4, { -36.347130f, 40.000000f, 5.575495f }, 1.000000f, 1.361288f, 0); 
    instance.addEObj( "unknown_1", 2004876, 0, 5071920, 4, { -36.347141f, 39.999969f, 5.575503f }, 1.000000f, 1.361287f, 0); 
    instance.addEObj( "unknown_2", 2000608, 2153761, 5289659, 4, { -48.001610f, 40.000000f, 130.437393f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Townsperson", 2005851, 0, 5901646, 4, { 6.698669f, 44.511238f, -41.336731f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Townsperson_1", 2005851, 0, 5901650, 4, { -39.593559f, 40.780991f, 7.926595f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Townsperson_2", 2005851, 0, 5901653, 4, { -40.360168f, 39.929359f, 64.927116f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Boundastrologian", 2006044, 0, 5901657, 4, { -11.083020f, 32.196159f, -35.527569f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Augustastrologian", 2006045, 0, 5901659, 4, { 15.786880f, 33.157841f, 34.241970f }, 0.991760f, -0.377700f, 0); 
    instance.addEObj( "Adolescentastrologian", 2006046, 0, 5901660, 4, { 16.178289f, 33.035770f, 36.880890f }, 0.991760f, -0.373961f, 0); 
    instance.addEObj( "unknown_3", 2006359, 0, 5939794, 4, { 79.729858f, 45.197559f, 136.568695f }, 1.000000f, -0.988154f, 0); 
    instance.addEObj( "Destination", 2004863, 0, 5110041, 4, { 4.455012f, 44.500000f, 121.299599f }, 0.700000f, 0.000000f, 0); 
    instance.addEObj( "Entrance", 2004332, 0, 4841589, 4, { -21.039770f, 92.187500f, -0.505822f }, 0.600000f, 0.000000f, 0); 
    instance.addEObj( "Rendezvouspoint", 2006316, 0, 5927102, 4, { 17.718969f, 47.599998f, -160.464706f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_4", 2004533, 0, 4892452, 4, { -10.129350f, 32.000000f, -38.963039f }, 1.000000f, -0.742274f, 0); 
    instance.addEObj( "MarkoftheNavigator", 2004591, 0, 4982807, 4, { -189.306595f, 41.927990f, 172.457108f }, 1.000000f, 1.503480f, 0); 
    instance.addEObj( "unknown_5", 2004670, 0, 5018803, 4, { -51.736969f, 36.861851f, 114.053703f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_6", 2004676, 0, 5018849, 4, { -66.923607f, 42.299999f, -153.630295f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_7", 2004677, 0, 5018898, 4, { 6.084933f, 46.219479f, -157.694199f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_8", 2004673, 0, 5018795, 4, { -51.309132f, 36.844730f, 114.013397f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "???", 2004153, 0, 4723149, 4, { 6.481973f, 46.423531f, -265.443787f }, 0.991760f, 0.000048f, 0); 

  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( FeatherintheCap );