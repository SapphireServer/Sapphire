#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class DragoonsFate : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto BNPC_BLDDRG_GROUND_01 = 5896375;
  static constexpr auto P_BNPC_HEUSTIENNE_01 = 5896376;
  static constexpr auto BNPC_BLDDRG_FLY_01 = 5896420;
  static constexpr auto POP_FLY_FRONT_01 = 5896427;
  static constexpr auto POP_FLY_FRONT_02 = 5896433;
  static constexpr auto POP_FLY_FRONT_03 = 5896438;
  static constexpr auto POP_FLY_LEFT_01 = 5896440;
  static constexpr auto POP_FLY_LEFT_02 = 5896442;
  static constexpr auto POP_FLY_LEFT_03 = 5896443;
  static constexpr auto POP_FLY_BACK_01 = 5896447;
  static constexpr auto POP_FLY_BACK_02 = 5896448;
  static constexpr auto POP_FLY_BACK_03 = 5896468;
  static constexpr auto POP_FLY_RIGHT_01 = 5896469;
  static constexpr auto POP_FLY_RIGHT_02 = 5896473;
  static constexpr auto POP_FLY_RIGHT_03 = 5896477;
  static constexpr auto BNPC_ICE_PATTERN_A_RIGHT_UP = 5896559;
  static constexpr auto BNPC_ICE_PATTERN_A_LEFT_UP = 5896825;
  static constexpr auto BNPC_ICE_PATTERN_A_LEFT_DOWN = 5896826;
  static constexpr auto BNPC_ICE_PATTERN_A_RIGHT_DOWN = 5896827;
  static constexpr auto BNPC_ICE_PATTERN_B_UP = 5896828;
  static constexpr auto BNPC_ICE_PATTERN_B_LEFT = 5896829;
  static constexpr auto BNPC_ICE_PATTERN_B_DOWN = 5896830;
  static constexpr auto BNPC_ICE_PATTERN_B_RIGHT = 5896831;
  static constexpr auto STATUS_FREEZE = 1519;
  static constexpr auto LOCK_ON_MARK = 22;
  static constexpr auto ACTION_DRAGON_FLY = 4258;
  static constexpr auto ACTION_CAUTERIZE = 4260;
  static constexpr auto ACTION_TOUCH_DOWN = 4998;
  static constexpr auto STATUS_PARAM_MARKING = 1726;
  static constexpr auto STATUS_PARAM_ANTI_MARKING = 1729;
  static constexpr auto STATUS_MARKING = 904;
  static constexpr auto STATUS_ANTI_MARKING = 475;
  static constexpr auto LOC_ACTOR_BLDDRG = 1014530;
  static constexpr auto LOC_ACTOR_HEUS = 1014531;
  static constexpr auto LEVEL_POINT_HEUS = 5883420;
  static constexpr auto LEVEL_POINT_BLDDRG = 5883423;
  static constexpr auto LOC_FACE1 = 616;
  static constexpr auto ACTION_TIMELINE_EVENT_BASE_MUNE_OSAE = 4222;
  static constexpr auto LOC_BGM1 = 91;
  static constexpr auto BNPC_TOUMEI_PLAYER = 5936683;
  static constexpr auto BNPC_TOUMEI_PLAYER_B = 5963092;

public:
  DragoonsFate() : Sapphire::ScriptAPI::QuestBattleScript( 142 )
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

EXPOSE_SCRIPT( DragoonsFate );