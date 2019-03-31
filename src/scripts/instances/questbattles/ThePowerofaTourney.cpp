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
    instance.registerEObj( "sgbg_w_qic_001_04a", 2006993, 6235274, 4, { -35.822102f, 298.899994f, -205.263199f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_0", 2006952, 0, 4, { -35.712589f, 298.899994f, -204.878006f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 556.049377f, 348.102509f, -752.435730f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Entrance", 2000182, 4600289, 5, { 523.532471f, 348.223389f, -736.685730f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "unknown_1", 2002332, 0, 4, { 533.090881f, 348.691895f, -742.750916f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_2", 2002333, 0, 4, { 539.940430f, 348.836395f, -734.401489f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_3", 2000608, 3967803, 4, { 202.369598f, 257.761108f, 80.435272f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_4", 2000608, 3976993, 4, { 273.634705f, 254.600204f, 106.048500f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_5", 2000608, 3986797, 4, { 205.504898f, 246.188995f, 194.875702f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_6", 2000608, 3986798, 4, { 326.313385f, 239.193497f, 221.138901f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_7", 2000608, 2718481, 4, { 240.552307f, 302.769714f, -199.979996f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_8", 2000608, 4065433, 4, { 204.970001f, 302.119995f, -216.311600f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_9", 2000608, 2814617, 4, { 205.869995f, 302.219086f, -276.681396f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_10", 2000608, 2763112, 4, { -433.000000f, 211.007706f, -216.148605f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_11", 2000608, 4187649, 4, { -453.000000f, 211.000000f, -281.046600f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_12", 2000608, 4187961, 4, { -416.000000f, 210.788193f, -279.813812f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( QuestBattle& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( ThePowerofaTourney );