#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class DestructionintheNameofJustice : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto BNPC_P1_BLM_A_01 = 5874136;
  static constexpr auto BNPC_P1_BLM_A_02 = 5874137;
  static constexpr auto BNPC_P1_BLM_B_01 = 5874139;
  static constexpr auto BNPC_P2_BLM_B_01 = 5874143;
  static constexpr auto BNPC_P2_BLM_B_02 = 5874290;
  static constexpr auto BNPC_P2_GATE_01 = 5874291;
  static constexpr auto BNPC_P2_GATE_02 = 5874292;
  static constexpr auto BNPC_P2_PURIN_01 = 5887399;
  static constexpr auto BNPC_P2_PURIN_02 = 5887400;
  static constexpr auto BNPC_P3_BLM_A_01 = 5874293;
  static constexpr auto BNPC_P3_BLM_B_01 = 5874296;
  static constexpr auto BNPC_P3_GATE_01 = 5874590;
  static constexpr auto BNPC_P3_GATE_02 = 5874591;
  static constexpr auto BNPC_P3_GATE_03 = 5874592;
  static constexpr auto BNPC_P3_GARGOYLE_01 = 5887401;
  static constexpr auto BNPC_P3_GARGOYLE_02 = 5887402;
  static constexpr auto BNPC_P3_GARGOYLE_03 = 5887403;
  static constexpr auto ENPC_DOUSHI_01 = 5874135;
  static constexpr auto POPTIME_PURIN = 30;
  static constexpr auto POPTIME_GARGOYLE = 30;
  static constexpr auto LOC_POS_ACTOR1 = 5911929;
  static constexpr auto LOC_POS_ACTOR2 = 5911966;
  static constexpr auto LOC_ACTOR1 = 1013068;
  static constexpr auto LOC_POS_ACTOR3 = 5911967;
  static constexpr auto LOC_POS_ACTOR4 = 5911968;
  static constexpr auto LOC_ACTOR2 = 1013052;
  static constexpr auto LOC_ACTOR3 = 1013053;
  static constexpr auto LOC_ACTOR4 = 1013054;
  static constexpr auto LOC_BGM_1 = 39;
  static constexpr auto LOC_ACTION_1 = 1039;
  static constexpr auto LOC_ACTION_2 = 1014;

public:
  DestructionintheNameofJustice() : Sapphire::ScriptAPI::QuestBattleScript( 114 )
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

EXPOSE_SCRIPT( DestructionintheNameofJustice );