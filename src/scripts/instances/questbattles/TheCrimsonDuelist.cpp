#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class TheCrimsonDuelist : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto P_BNPC_SIRUN_01 = 6794090;
  static constexpr auto BNPC_WOLF_WAVE1_01 = 6794085;
  static constexpr auto BNPC_WOLF_WAVE1_02 = 6794086;
  static constexpr auto BNPC_THA_WAVE1_01 = 6794087;
  static constexpr auto BNPC_THA_WAVE2_01 = 6794397;
  static constexpr auto BNPC_WOLF_WAVE2_01 = 6794398;
  static constexpr auto BNPC_WOLF_WAVE2_02 = 6794399;
  static constexpr auto BNPC_THA_WAVE3_01 = 6794400;
  static constexpr auto BNPC_WOLF_WAVE3_01 = 6794401;
  static constexpr auto BNPC_WOLF_WAVE3_02 = 6794402;
  static constexpr auto BNPC_WOLF_WAVE3_03 = 6794403;
  static constexpr auto P_BNPC_SIRUN_02 = 6794148;
  static constexpr auto WARP_01 = 6794141;
  static constexpr auto BGM_LATE_BATTLE = 113;
  static constexpr auto BNPC_PACK1_THA_01 = 6794185;
  static constexpr auto BNPC_PACK1_HECT_01 = 6794183;
  static constexpr auto BNPC_PACK1_HECT_02 = 6794184;
  static constexpr auto BNPC_PACK2_THA_01 = 6794189;
  static constexpr auto BNPC_PACK2_AHRI_01 = 6794187;
  static constexpr auto BNPC_PACK2_HECT_01 = 6794188;
  static constexpr auto BNPC_PACK3_THA_01 = 6794193;
  static constexpr auto BNPC_PACK3_AHRI_01 = 6794191;
  static constexpr auto BNPC_PACK3_AHRI_02 = 6794192;
  static constexpr auto BNPC_THA_BOSS = 6794203;
  static constexpr auto BNPC_CERBERUS = 6794201;
  static constexpr auto PR_XRHUNTIA_MOVE_01 = 6794465;
  static constexpr auto PR_XRHUNTIA_MOVE_02 = 6797640;
  static constexpr auto ER_PACK1_START = 6794489;
  static constexpr auto BNPC_DARKBALL_01 = 6796963;
  static constexpr auto BNPC_DARKBALL_02 = 6796964;
  static constexpr auto BNPC_DARKBALL_03 = 6796965;
  static constexpr auto BNPC_DARKBALL_04 = 6796966;
  static constexpr auto PR_DARKBALL_MOVE_01 = 6797005;
  static constexpr auto PR_DARKBALL_MOVE_02 = 6797007;
  static constexpr auto PR_DARKBALL_MOVE_03 = 6797008;
  static constexpr auto PR_DARKBALL_MOVE_04 = 6797010;
  static constexpr auto PR_DARKBALL_MOVE_RELAY_01 = 6797152;
  static constexpr auto PR_DARKBALL_MOVE_RELAY_02 = 6797187;
  static constexpr auto DEF_ACTION_TORRIGER = 3269;
  static constexpr auto BNPC_SUMMON_MAHOUJIN = 6797004;
  static constexpr auto ACTION_CERBERUS_GT = 7873;
  static constexpr auto BNPC_MINIMUM_BALL = 6797750;
  static constexpr auto LOC_LQ_SECONDHALF_01 = 6922587;
  static constexpr auto LOC_ACTOR0 = 1021024;
  static constexpr auto PR_XRHUNTIA_WAVE1_MOVE = 6998616;
  static constexpr auto PR_XRHUNTIA_WAVE2_MOVE = 6998617;
  static constexpr auto PR_XRHUNTIA_MOVE_TO_BOSS = 6998631;
  static constexpr auto CHANNELING_SUMMON = 14;
  static constexpr auto PR_XRHUNTIA_CERBERUS_MOVE = 6998645;
  static constexpr auto EOBJ_SHIELD_CONTROL_01 = 7021131;
  static constexpr auto EOBJ_SHIELD_CONTROL_02 = 7021132;
  static constexpr auto EOBJ_SHIELD_CONTROL_03 = 7021133;

public:
  TheCrimsonDuelist() : Sapphire::ScriptAPI::QuestBattleScript( 161 )
  { }

  void onInit( QuestBattle& instance ) override
  {

  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheCrimsonDuelist );