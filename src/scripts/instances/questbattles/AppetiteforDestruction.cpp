#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class AppetiteforDestruction : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto BNPC_COMPANION_WIDARGELT_01 = 5908791;
  static constexpr auto BNPC_COMPANION_OTCHAKHA_01 = 5908792;
  static constexpr auto BNPC_ENEMY_HRAHATIA_01 = 5908804;
  static constexpr auto BNPC_ENEMY_PACK_A_MNK_01 = 5908820;
  static constexpr auto BNPC_ENEMY_PACK_A_MNK_02 = 5908821;
  static constexpr auto BNPC_ENEMY_PACK_A_MNK_03 = 5908822;
  static constexpr auto BNPC_ENEMY_PACK_A_MNK_04 = 5908823;
  static constexpr auto BNPC_ENEMY_PACK_B_MNK_01 = 5908838;
  static constexpr auto BNPC_ENEMY_PACK_B_MNK_02 = 5908840;
  static constexpr auto BNPC_COMPANION_WIDARGELT_02 = 5908845;
  static constexpr auto BNPC_COMPANION_OTCHAKHA_02 = 5908847;
  static constexpr auto BNPC_COMPANION_DZENTSA_01 = 5908849;
  static constexpr auto BNPC_ENEMY_HRAHATIA_02 = 5908852;
  static constexpr auto BNPC_ENEMY_PACK_C_MNK_01 = 5908854;
  static constexpr auto BNPC_ENEMY_PACK_C_MNK_02 = 5908856;
  static constexpr auto BNPC_ENEMY_PACK_C_MNK_03 = 5908857;
  static constexpr auto BNPC_ENEMY_PACK_C_MNK_04 = 5908858;
  static constexpr auto BNPC_ENEMY_PACK_C_MNK_05 = 5908860;
  static constexpr auto BNPC_ENEMY_PACK_C_MNK_06 = 5908861;
  static constexpr auto BNPC_ENEMY_POP_MNK_01 = 5908862;
  static constexpr auto BNPC_ENEMY_POP_MNK_02 = 5915942;
  static constexpr auto BNPC_ENEMY_POP_MNK_03 = 5915943;
  static constexpr auto BNPC_ENEMY_POP_MNK_04 = 5915944;
  static constexpr auto ENPC_DZENTSA_01 = 5908803;
  static constexpr auto WARP_PC_POINT_01 = 5908843;
  static constexpr auto LOGMESSAGE_SHADOW_CHAKURA = 3270;
  static constexpr auto LOGMESSAGE_KAIHUKU = 3213;
  static constexpr auto LOGMESSAGE_POWER_UP = 3271;
  static constexpr auto BNPC_TYPE_MNK = 4653;
  static constexpr auto MNK_POP_INTERVAL_1 = 20;
  static constexpr auto CUT_SCENE_01 = 960;
  static constexpr auto BNPC_ENEMY_ENERGY_BALL_THUNDER_01 = 5912441;
  static constexpr auto BNPC_ENEMY_ENERGY_BALL_BLACK_01 = 5912448;
  static constexpr auto BNPC_ENEMY_ENERGY_BALL_BLACK_02 = 5912449;
  static constexpr auto BNPC_ENEMY_ENERGY_BALL_BLACK_03 = 5912450;
  static constexpr auto BNPC_ACTION_SUMMON_ENERGY_BALL_THUNDER = 1094;
  static constexpr auto BNPC_ACTION_SUMMON_ENERGY_BALL_BLACK = 4760;
  static constexpr auto BNPC_ACTION_THUNDER_BALL_BURST = 1093;
  static constexpr auto EOBJ_THUNDER_GRAUND = 5912535;
  static constexpr auto STATUS_INFINITY_STACK_REGEN = 1743;
  static constexpr auto STATUS_INFINITY_ATTACK_DAMAGE_UP = 1744;
  static constexpr auto STATUS_THUNDER_MAGIC_DOT = 1745;
  static constexpr auto BNPC_BASE_ENERGY_BALL_THUNDER = 4651;
  static constexpr auto BNPC_BASE_ENERGY_BALL_BLACK = 4652;
  static constexpr auto LOCKON_BY_ENERGY_BALL_THUNDER = 1;
  static constexpr auto POP_RANGE_ENERGY_BALL_BLACK_01 = 5912707;
  static constexpr auto POP_RANGE_ENERGY_BALL_BLACK_02 = 5912710;
  static constexpr auto POP_RANGE_ENERGY_BALL_BLACK_03 = 5912712;
  static constexpr auto POP_RANGE_ENERGY_BALL_BLACK_04 = 5912713;
  static constexpr auto POP_RANGE_ENERGY_BALL_THUNDER_01 = 5912727;
  static constexpr auto POP_RANGE_ENERGY_BALL_THUNDER_02 = 5912728;
  static constexpr auto POP_RANGE_ENERGY_BALL_THUNDER_03 = 5912729;
  static constexpr auto POP_RANGE_ENERGY_BALL_THUNDER_04 = 5912730;
  static constexpr auto POP_RANGE_ENERGY_BALL_THUNDER_05 = 5912731;
  static constexpr auto POP_RANGE_ENERGY_BALL_THUNDER_06 = 5912732;
  static constexpr auto LOC_POP_0 = 5919784;
  static constexpr auto LOC_POP_1 = 5919785;
  static constexpr auto LOC_ACTOR_0 = 1014543;
  static constexpr auto LOC_ACTOR_1 = 1014541;
  static constexpr auto LOC_ACTOR_2 = 1014542;
  static constexpr auto LOC_ACTOR_3 = 1014013;
  static constexpr auto LOC_ACTOR_4 = 1014014;
  static constexpr auto POP_RANGE_RESQUE_01 = 5927592;
  static constexpr auto POP_RANGE_RESQUE_02 = 5927593;
  static constexpr auto LOC_BGM_1 = 91;
  static constexpr auto POP_RANGE_ENERGY_BALL_BLACK_05 = 5959843;
  static constexpr auto POP_RANGE_ENERGY_BALL_BLACK_06 = 5959844;

public:
  AppetiteforDestruction() : Sapphire::ScriptAPI::QuestBattleScript( 132 )
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

EXPOSE_SCRIPT( AppetiteforDestruction );