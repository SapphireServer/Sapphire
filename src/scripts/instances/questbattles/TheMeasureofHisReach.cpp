#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class TheMeasureofHisReach : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_WARP_POINT_001 = 6851576;
  static constexpr auto LOC_MARKER_001 = 6851574;
  static constexpr auto P_BNPC_ALPHINAUD = 6875022;
  static constexpr auto P_BNPC_CARBUNCLE = 6875024;
  static constexpr auto BNPC_HAKUROU = 6875464;
  static constexpr auto BNPC_WOLFMAN_LNC_ALPHINAUD_01 = 6851697;
  static constexpr auto BNPC_WOLFMAN_LNC_PC_01 = 6851698;
  static constexpr auto BNPC_WOLFMAN_LNC_PC_02 = 6851699;
  static constexpr auto BNPC_WOLFMAN_LNC_ALPHINAUD_02 = 6851700;
  static constexpr auto BNPC_WOLFMAN_LNC_PC_03 = 6851708;
  static constexpr auto BNPC_WOLFMAN_LNC_ALPHINAUD_03 = 6851709;
  static constexpr auto BNPC_WOLFMAN_ARC_ALPHINAUD_01 = 6851710;
  static constexpr auto BNPC_WOLFMAN_ARC_PC_01 = 6851713;
  static constexpr auto BNPC_TOUMEI_ACTION_01 = 6875112;
  static constexpr auto BNPC_TOUMEI_ACTION_02 = 6875137;
  static constexpr auto BNPC_TOUMEI_ACTION_03 = 6875138;
  static constexpr auto BNPC_TOUMEI_ACTION_04 = 6875139;
  static constexpr auto BNPC_TOUMEI_ACTION_05 = 6875140;
  static constexpr auto BNPC_TOUMEI_ACTION_06 = 6875141;
  static constexpr auto BNPC_TOUMEI_ACTION_07 = 6875142;
  static constexpr auto BNPC_TOUMEI_ACTION_08 = 6875143;
  static constexpr auto BNPC_TOUMEI_ACTION_09 = 6875144;
  static constexpr auto BNPC_TOUMEI_ACTION_10 = 6875145;
  static constexpr auto BNPC_TOUMEI_ACTION_11 = 6875146;
  static constexpr auto BNPC_TOUMEI_ACTION_12 = 6875147;
  static constexpr auto BNPC_TOUMEI_ACTION_13 = 6875148;
  static constexpr auto BNPC_TOUMEI_ACTION_14 = 6875149;
  static constexpr auto BNPC_TOUMEI_ACTION_15 = 6875150;
  static constexpr auto BNPC_TOUMEI_ACTION_16 = 6875151;
  static constexpr auto BNPC_TOUMEI_ACTION_17 = 6875152;
  static constexpr auto BNPC_TOUMEI_ACTION_18 = 6875153;
  static constexpr auto BNPC_TOUMEI_ACTION_19 = 6875154;
  static constexpr auto BNPC_TOUMEI_ACTION_20 = 6875155;
  static constexpr auto BNPC_TOUMEI_ACTION_21 = 6876717;
  static constexpr auto PRANGE_YUKIKAZE_EAST_01 = 6875051;
  static constexpr auto PRANGE_YUKIKAZE_EAST_02 = 6875050;
  static constexpr auto PRANGE_YUKIKAZE_EAST_03 = 6875049;
  static constexpr auto PRANGE_YUKIKAZE_EAST_04 = 6875048;
  static constexpr auto PRANGE_YUKIKAZE_EAST_05 = 6875034;
  static constexpr auto PRANGE_YUKIKAZE_EAST_06 = 6875053;
  static constexpr auto PRANGE_YUKIKAZE_EAST_07 = 6875052;
  static constexpr auto PRANGE_YUKIKAZE_EAST_08 = 6875054;
  static constexpr auto PRANGE_YUKIKAZE_EAST_09 = 6875056;
  static constexpr auto PRANGE_YUKIKAZE_EAST_10 = 6875057;
  static constexpr auto PRANGE_YUKIKAZE_SOUTH_01 = 6875070;
  static constexpr auto PRANGE_YUKIKAZE_SOUTH_02 = 6875063;
  static constexpr auto PRANGE_YUKIKAZE_SOUTH_03 = 6875062;
  static constexpr auto PRANGE_YUKIKAZE_SOUTH_04 = 6875061;
  static constexpr auto PRANGE_YUKIKAZE_SOUTH_05 = 6875060;
  static constexpr auto PRANGE_YUKIKAZE_SOUTH_06 = 6875046;
  static constexpr auto PRANGE_YUKIKAZE_SOUTH_07 = 6875045;
  static constexpr auto PRANGE_YUKIKAZE_SOUTH_08 = 6875055;
  static constexpr auto PRANGE_YUKIKAZE_SOUTH_09 = 6875058;
  static constexpr auto PRANGE_YUKIKAZE_SOUTH_10 = 6875059;
  static constexpr auto PRANGE_HANAGURUMA_LEVEL01_000 = 6875084;
  static constexpr auto PRANGE_HANAGURUMA_LEVEL01_180 = 6875085;
  static constexpr auto PRANGE_HANAGURUMA_LEVEL01_090 = 6876844;
  static constexpr auto PRANGE_HANAGURUMA_LEVEL01_270 = 6876845;
  static constexpr auto PRANGE_HANAGURUMA_LEVEL02_293 = 6875098;
  static constexpr auto PRANGE_HANAGURUMA_LEVEL02_023 = 6875099;
  static constexpr auto PRANGE_HANAGURUMA_LEVEL02_203 = 6875100;
  static constexpr auto PRANGE_HANAGURUMA_LEVEL02_113 = 6875101;
  static constexpr auto PRANGE_HANAGURUMA_LEVEL03_068 = 6877062;
  static constexpr auto PRANGE_HANAGURUMA_LEVEL03_158 = 6877063;
  static constexpr auto PRANGE_HANAGURUMA_LEVEL03_248 = 6877064;
  static constexpr auto PRANGE_HANAGURUMA_LEVEL03_338 = 6877065;
  static constexpr auto PRANGE_HANAGURUMA_LEVEL04_045 = 6875105;
  static constexpr auto PRANGE_HANAGURUMA_LEVEL04_135 = 6875106;
  static constexpr auto PRANGE_HANAGURUMA_LEVEL04_315 = 6875107;
  static constexpr auto PRANGE_HANAGURUMA_LEVEL04_225 = 6875108;
  static constexpr auto PRANGE_HANAGURUMA_LEVEL04_090 = 6875086;
  static constexpr auto PRANGE_HANAGURUMA_LEVEL04_270 = 6875088;
  static constexpr auto PRANGE_HANAGURUMA_LEVEL04_180 = 6875091;
  static constexpr auto PRANGE_HANAGURUMA_LEVEL04_000 = 6875092;
  static constexpr auto ACTION_YUKIKAZE = 8400;
  static constexpr auto ACTION_GEKKO = 8401;
  static constexpr auto ACTION_HANAGURUMA = 8402;
  static constexpr auto ACTION_SUMMON_RYUZU = 8449;
  static constexpr auto ACTION_TOUMEI_GEKKO = 8398;
  static constexpr auto ACTION_SMN_CARBUNCLE_WHITE = 9158;
  static constexpr auto ACTION_CARBUNCLE_W_BUFF_AREA = 9396;
  static constexpr auto BNPC_RYUZU_A01 = 6877318;
  static constexpr auto BNPC_RYUZU_A02 = 6956324;
  static constexpr auto BNPC_RYUZU_A03 = 6956325;
  static constexpr auto BNPC_RYUZU_A04 = 6956326;
  static constexpr auto BNPC_RYUZU_B01 = 6877355;
  static constexpr auto BNPC_RYUZU_B02 = 6956327;
  static constexpr auto BNPC_RYUZU_B03 = 6956328;
  static constexpr auto BNPC_RYUZU_B04 = 6956329;
  static constexpr auto BGM_BOSS_BATTLE = 406;
  static constexpr auto P_BNPC_CARBUNCLE_WHITE = 6972241;
  static constexpr auto BNPC_CARBUNCLE_W_BUFF_AREA = 6972395;
  static constexpr auto STATUS_PARAM_BUFFAREA = 3298;
  static constexpr auto LOC_ACTOR_01 = 1011887;
  static constexpr auto LOC_ACTOR_02 = 1022007;
  static constexpr auto LOC_ACTOR_03 = 1022008;
  static constexpr auto LOC_ACTOR_04 = 1022009;
  static constexpr auto LOC_IDLE_01 = 34;
  static constexpr auto ENPC_HAKUROU = 7011709;
  static constexpr auto BNPC_TOUMEI_TAKED_HATE = 7022975;

public:
  TheMeasureofHisReach() : Sapphire::ScriptAPI::QuestBattleScript( 167 )
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

EXPOSE_SCRIPT( TheMeasureofHisReach );