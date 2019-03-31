#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class SchismbetweenSisters : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto P_BNPC_ALPA = 7230510;
  static constexpr auto P_BNPC_JOLHMYN = 7230511;
  static constexpr auto P_BNPC_MZHETTIA = 7230512;
  static constexpr auto P_BNPC_TAHLAMOLKOH = 7230513;
  static constexpr auto P_BNPC_KARYANA_ALLY_1 = 7230515;
  static constexpr auto P_BNPC_KARYANA_ALLY_2 = 7230516;
  static constexpr auto P_BNPC_KARYANA_ALLY_3 = 7230517;
  static constexpr auto P_BNPC_KARYANA_ALLY_4 = 7230518;
  static constexpr auto P_BNPC_KARYANA_ALLY_5 = 7230520;
  static constexpr auto BNPC_KARYANA_ENEMY_BOSS = 7230521;
  static constexpr auto BNPC_KARYANA_ENEMY_W1_01 = 7230573;
  static constexpr auto BNPC_KARYANA_ENEMY_W1_02 = 7230574;
  static constexpr auto BNPC_KARYANA_ENEMY_W1_03 = 7230575;
  static constexpr auto BNPC_KARYANA_ENEMY_W1_04 = 7230576;
  static constexpr auto BNPC_KARYANA_ENEMY_W1_05 = 7230578;
  static constexpr auto BNPC_KARYANA_ENEMY_W2_01 = 7230581;
  static constexpr auto BNPC_KARYANA_ENEMY_W2_02 = 7230582;
  static constexpr auto BNPC_KARYANA_ENEMY_W2_03 = 7230583;
  static constexpr auto BNPC_KARYANA_ENEMY_W2_04 = 7230584;
  static constexpr auto BNPC_KARYANA_ENEMY_W2_05 = 7230585;
  static constexpr auto BNPC_KARYANA_ENEMY_W3_01 = 7230588;
  static constexpr auto BNPC_KARYANA_ENEMY_W3_02 = 7230589;
  static constexpr auto BNPC_KARYANA_ENEMY_W3_03 = 7230590;
  static constexpr auto BNPC_KARYANA_ENEMY_W3_04 = 7230591;
  static constexpr auto BNPC_KARYANA_ENEMY_W3_05 = 7230592;
  static constexpr auto BNPC_KARYANA_ENEMY_W3_06 = 7230593;
  static constexpr auto BNPC_KARYANA_ENEMY_W3_07 = 7230594;
  static constexpr auto BNPC_KARYANA_ENEMY_W3_08 = 7230595;
  static constexpr auto POP_RANGE_ALLY_APPEAR_MOVE_01 = 7230864;
  static constexpr auto POP_RANGE_ALLY_APPEAR_MOVE_02 = 7230866;
  static constexpr auto POP_RANGE_ALLY_APPEAR_MOVE_03 = 7230867;
  static constexpr auto POP_RANGE_ALLY_APPEAR_MOVE_04 = 7230868;
  static constexpr auto POP_RANGE_ALLY_APPEAR_MOVE_05 = 7230869;
  static constexpr auto POP_RANGE_ALPA_APPEAR_MOVE_01 = 7231055;
  static constexpr auto POP_RANGE_ENEMY_APPEAR_MOVE_01 = 7231058;
  static constexpr auto POP_RANGE_ENEMY_APPEAR_MOVE_02 = 7231059;
  static constexpr auto POP_RANGE_ENEMY_APPEAR_MOVE_03 = 7231060;
  static constexpr auto POP_RANGE_ENEMY_APPEAR_MOVE_04 = 7231061;
  static constexpr auto POP_RANGE_ENEMY_APPEAR_MOVE_05 = 7231062;
  static constexpr auto POP_RANGE_ALLY_APPEAR_MOVE_06 = 7231232;
  static constexpr auto POP_RANGE_ALLY_APPEAR_MOVE_07 = 7231233;
  static constexpr auto POP_RANGE_ALLY_APPEAR_MOVE_08 = 7231234;
  static constexpr auto POP_RANGE_ALLY_APPEAR_MOVE_09 = 7231235;
  static constexpr auto POP_RANGE_ALLY_APPEAR_MOVE_10 = 7231236;
  static constexpr auto BEHAVIOR_BATTLE_ACTIVE_IDLE = 30102;
  static constexpr auto YELL_ALPA_BTLSTART_01 = 6639;
  static constexpr auto YELL_JOLHMYN_BTLSTART_01 = 6640;
  static constexpr auto POP_RANGE_ALLY_DISAPPEAR_MOVE_01 = 7233013;
  static constexpr auto POP_RANGE_ALLY_DISAPPEAR_MOVE_02 = 7233014;
  static constexpr auto POP_RANGE_ALLY_DISAPPEAR_MOVE_03 = 7233015;
  static constexpr auto POP_RANGE_ALPA_BLOCKING_MOVE_01 = 7235669;
  static constexpr auto YELL_JOLHMYN_COVER_01 = 6641;
  static constexpr auto EOBJ_BATTLE_CIRCLE = 7230536;
  static constexpr auto POP_RANGE_INIT_WARP_01 = 7188887;
  static constexpr auto BNPC_KARYANA_ENEMY_W4_01 = 7236312;
  static constexpr auto BNPC_KARYANA_ENEMY_W4_02 = 7236313;
  static constexpr auto BNPC_KARYANA_ENEMY_W4_03 = 7236314;
  static constexpr auto POP_RANGE_P3_ENEMY_APPEAR_MOVE_01 = 7237538;
  static constexpr auto POP_RANGE_P3_ENEMY_APPEAR_MOVE_02 = 7237539;
  static constexpr auto POP_RANGE_P3_ENEMY_APPEAR_MOVE_03 = 7237540;
  static constexpr auto POP_RANGE_P3_ENEMY_APPEAR_MOVE_04 = 7237541;
  static constexpr auto POP_RANGE_P3_ENEMY_APPEAR_MOVE_05 = 7237542;
  static constexpr auto POP_RANGE_P3_ENEMY_APPEAR_MOVE_06 = 7237543;
  static constexpr auto POP_RANGE_P3_ENEMY_APPEAR_MOVE_07 = 7237544;
  static constexpr auto POP_RANGE_P3_ENEMY_APPEAR_MOVE_08 = 7237545;
  static constexpr auto ACTION_SCRIPT_TRIGGER = 3269;
  static constexpr auto YELL_ALPA_THANKS_01 = 6644;
  static constexpr auto YELL_KARYANASOLDIER_DISAPPEAR_01 = 6650;
  static constexpr auto YELL_KARYANASOLDIER_DISAPPEAR_02 = 6651;
  static constexpr auto BNPC_KARYANA_ENEMY_W4_04 = 7241988;
  static constexpr auto BNPC_KARYANA_ENEMY_W4_05 = 7241989;
  static constexpr auto BNPC_KARYANA_ENEMY_W4_06 = 7241990;
  static constexpr auto BNPC_KARYANA_ENEMY_W4_GIMMICK_01 = 7242000;
  static constexpr auto BNPC_KARYANA_ENEMY_W4_GIMMICK_02 = 7242002;
  static constexpr auto BNPC_KARYANA_ENEMY_W4_GIMMICK_03 = 7242003;
  static constexpr auto BNPC_KARYANA_ENEMY_W4_GIMMICK_04 = 7242004;
  static constexpr auto BNPC_KARYANA_ENEMY_W4_GIMMICK_05 = 7242005;
  static constexpr auto BNPC_KARYANA_ENEMY_W4_GIMMICK_06 = 7242006;
  static constexpr auto ACTION_ATEL_SHARE = 10722;
  static constexpr auto CHANNELING_WIND = 4;
  static constexpr auto ACTION_FLARE_SHARE = 10735;
  static constexpr auto LOCKON_SHARE = 62;
  static constexpr auto YELL_MZHETTIA_SHARE_01 = 6659;
  static constexpr auto LOC_LQ_00 = 7244089;
  static constexpr auto LOC_ACTOR_00 = 1024769;
  static constexpr auto LOC_ACTOR_01 = 1024752;
  static constexpr auto LOC_ACTOR_02 = 1022043;
  static constexpr auto LOC_ACTOR_03 = 1024756;
  static constexpr auto LOC_ACTOR_04 = 1024764;
  static constexpr auto LOC_ACTOR_05 = 1024770;
  static constexpr auto LOC_ACTION_00 = 953;
  static constexpr auto LOC_ACTION_01 = 954;
  static constexpr auto LOC_ACTION_02 = 3778;
  static constexpr auto LOC_ACTION_03 = 4676;
  static constexpr auto LOC_ACTION_04 = 72;
  static constexpr auto LOC_SE_00 = 85;
  static constexpr auto LOC_SE_01 = 80;
  static constexpr auto LOC_BGM_00 = 113;
  static constexpr auto BNPCBASE_ANANTA_CON_GIMMICK = 8566;
  static constexpr auto ACTION_WATERGA = 10757;
  static constexpr auto LOC_ACTOR_06 = 1023863;
  static constexpr auto LOCKON_DEPLOY = 87;
  static constexpr auto P_BNPC_HATE = 7256361;
  static constexpr auto BNPC_BOSS_GIMMICK_01 = 7256362;
  static constexpr auto BNPC_BOSS_GIMMICK_02 = 7256363;
  static constexpr auto BNPC_BOSS_GIMMICK_03 = 7256364;
  static constexpr auto ACTION_SCRIPT_TRIGGER_B = 4777;
  static constexpr auto ACTION_DEPLOY_GIMMICK = 10873;
  static constexpr auto LOC_BGM_01 = 165;

public:
  SchismbetweenSisters() : Sapphire::ScriptAPI::QuestBattleScript( 182 )
  { }

  void onInit( QuestBattle& instance ) override
  {

  }

  void onUpdate( QuestBattle& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( SchismbetweenSisters );