#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class EscapefromCastrumCentri : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_P_POP_1_BIGGS = 4278226;
  static constexpr auto INIT_P_POP_1_ARMOR_WEDGE = 4278227;
  static constexpr auto INIT_POP_1_1_EXC_LEADER = 4278232;
  static constexpr auto INIT_POP_1_1_LNC_01 = 4278234;
  static constexpr auto INIT_POP_1_1_THM_01 = 4278235;
  static constexpr auto INIT_P_POP_1_PAPALYMO = 4278239;
  static constexpr auto INIT_P_POP_1_URIANGER = 4278243;
  static constexpr auto INIT_ENPC_1_MINFILIA = 4278275;
  static constexpr auto INIT_ENPC_1_TATARU = 4278277;
  static constexpr auto INIT_POP_1_2_LNC_01 = 4278298;
  static constexpr auto INIT_POP_1_2_CNJ_01 = 4278300;
  static constexpr auto INIT_POP_1_2_GLA_01 = 4278305;
  static constexpr auto INIT_ENPC_2_MINFILIA = 4288517;
  static constexpr auto INIT_ENPC_2_TATARU = 4288518;
  static constexpr auto INIT_ENPC_2_BIGGS = 4288515;
  static constexpr auto INIT_P_POP_2_PAPALYMO = 4278513;
  static constexpr auto INIT_P_POP_2_URIANGER = 4278521;
  static constexpr auto INIT_POP_2_1_LNC_01 = 4278529;
  static constexpr auto INIT_POP_2_1_GLA_01 = 4278538;
  static constexpr auto INIT_POP_2_1_CNJ_01 = 4278558;
  static constexpr auto INIT_POP_2_1_KIL_01 = 4278569;
  static constexpr auto INIT_POP_2_1_THM_01 = 4278577;
  static constexpr auto INIT_POP_2_2_KIL_01 = 4285260;
  static constexpr auto INIT_POP_2_2_KIL_02 = 4285261;
  static constexpr auto INIT_POP_2_2_LNC_01 = 4285274;
  static constexpr auto INIT_POP_2_2_THM_01 = 4285278;
  static constexpr auto INIT_POP_2_2_THM_02 = 4285317;
  static constexpr auto INIT_POP_2_2_TOOL_01 = 4286888;
  static constexpr auto INIT_POP_2_2_TOOL_02 = 4286889;
  static constexpr auto INIT_POP_2_2_TOOL_03 = 4286891;
  static constexpr auto INIT_POP_2_3_STL_03 = 4287242;
  static constexpr auto INIT_POP_2_2_CNJ_03 = 4287243;
  static constexpr auto INIT_P_POP_PET = 4308235;
  static constexpr auto WARP_01 = 4278503;
  static constexpr auto INIT_EO_POP_URIANGER_HANDS_ON = 4307830;
  static constexpr auto INIT_EO_POP_PAPALYMO_HANDS_ON = 4307829;
  static constexpr auto EVENT_ACTION_01 = 42;
  static constexpr auto INIT_ENPC_POP_URIANGER = 4307929;
  static constexpr auto INIT_ENPC_POP_PAPALYMO = 4307930;
  static constexpr auto YELL_QIB_URIANGER_01 = 1192;
  static constexpr auto YELL_QIB_PAPALYMO_01 = 1193;
  static constexpr auto YELL_QIB_01 = 1693;
  static constexpr auto YELL_QIB_02 = 1694;
  static constexpr auto YELL_QIB_03 = 1695;
  static constexpr auto LOGMESSAGE_QIB_01 = 3214;
  static constexpr auto LOGMESSAGE_QIB_02 = 3215;
  static constexpr auto LOGMESSAGE_QIB_03 = 3216;
  static constexpr auto DEF_ACTION_SUMMON_PET_BNPC = 1307;
  static constexpr auto STATUS_CUSTOM_REGEN = 691;
  static constexpr auto CUT_SCENE_01 = 258;
  static constexpr auto CUT_SCENE_02 = 259;
  static constexpr auto BGM_BATTLE_2ND = 36;
  static constexpr auto DEF_WEATHER_SUNY = 2;

public:
  EscapefromCastrumCentri() : Sapphire::ScriptAPI::QuestBattleScript( 65 )
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

EXPOSE_SCRIPT( EscapefromCastrumCentri );