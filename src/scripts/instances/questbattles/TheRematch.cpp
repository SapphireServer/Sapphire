#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class TheRematch : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_P_POP_01 = 4011016;
  static constexpr auto INIT_P_POP_02 = 4011017;
  static constexpr auto INIT_P_POP_03 = 4011018;
  static constexpr auto INIT_POP_01_01 = 4011007;
  static constexpr auto INIT_POP_01_02 = 4011008;
  static constexpr auto INIT_POP_02_01 = 4011009;
  static constexpr auto INIT_POP_02_02 = 4011010;
  static constexpr auto INIT_POP_03_01 = 4011011;
  static constexpr auto INIT_POP_03_02 = 4011012;
  static constexpr auto ER_RECT_01 = 4011013;
  static constexpr auto INIT_POP_04_01 = 4011014;
  static constexpr auto INIT_POP_04_02 = 4011015;
  static constexpr auto INIT_POP_VS_MIRA_01 = 4011021;
  static constexpr auto INIT_POP_VS_MIRA_02 = 4011022;
  static constexpr auto INIT_POP_VS_GIL_A_01 = 4011027;
  static constexpr auto INIT_POP_VS_GIL_A_02 = 4011028;
  static constexpr auto INIT_POP_VS_GIL_B_01 = 4011029;
  static constexpr auto INIT_POP_VS_GIL_B_02 = 4011030;
  static constexpr auto INIT_P_POP_ALDIS = 4011120;
  static constexpr auto INIT_POP_NOTAR_GIL_02 = 4011234;
  static constexpr auto INIT_POP_NOTAR_GIL_03 = 4011237;
  static constexpr auto INIT_POP_NOTAR_GIL_04 = 4011241;
  static constexpr auto INIT_POP_NOTAR_GIL_05 = 4011244;
  static constexpr auto INIT_POP_NOTAR_GIL_06 = 4011246;
  static constexpr auto INIT_POP_NOTAR_GIL_07 = 4011249;
  static constexpr auto INIT_POP_NOTAR_GIL_08 = 4011260;
  static constexpr auto INIT_POP_NOTAR_GIL_09 = 4011262;
  static constexpr auto INIT_POP_NOTAR_GIL_10 = 4011266;
  static constexpr auto INIT_POP_NOTAR_GIL_11 = 4011267;
  static constexpr auto INIT_POP_REHWOLD = 4011122;
  static constexpr auto INIT_POP_NOTAR_ENE_02 = 4011235;
  static constexpr auto INIT_POP_NOTAR_ENE_03 = 4011236;
  static constexpr auto INIT_POP_NOTAR_ENE_04 = 4011242;
  static constexpr auto INIT_POP_NOTAR_ENE_05 = 4011243;
  static constexpr auto INIT_POP_NOTAR_ENE_06 = 4011247;
  static constexpr auto INIT_POP_NOTAR_ENE_07 = 4011248;
  static constexpr auto INIT_POP_NOTAR_ENE_08 = 4011261;
  static constexpr auto INIT_POP_NOTAR_ENE_09 = 4011263;
  static constexpr auto INIT_POP_NOTAR_ENE_10 = 4011265;
  static constexpr auto INIT_POP_NOTAR_ENE_11 = 4011268;
  static constexpr auto INIT_POP_LAST_ENE_01 = 4011419;
  static constexpr auto INIT_POP_LAST_ENE_02 = 4011422;
  static constexpr auto INIT_POP_LAST_ENE_03 = 4011426;
  static constexpr auto INIT_POP_LAST_OGRE = 4011434;
  static constexpr auto INIT_POP_LAST_BOSS = 4011442;
  static constexpr auto DEF_ACTION_MONSTER_SUMMON = 867;
  static constexpr auto CUT_SCENE_01 = 43;
  static constexpr auto CUT_SCENE_02 = 162;

public:
  TheRematch() : Sapphire::ScriptAPI::QuestBattleScript( 23 )
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

EXPOSE_SCRIPT( TheRematch );