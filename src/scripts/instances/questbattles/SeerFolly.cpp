#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class SeerFolly : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_P_POP_RAYAO_01 = 4293115;
  static constexpr auto INIT_P_POP_ARUN_01 = 4293116;
  static constexpr auto INIT_POP_1_BOSS_TRANT_01 = 4293124;
  static constexpr auto INIT_POP_1_RPT_01 = 4293129;
  static constexpr auto INIT_POP_1_RPT_02 = 4293131;
  static constexpr auto INIT_POP_1_RPT_03 = 4293132;
  static constexpr auto INIT_POP_1_FLY_01 = 4293133;
  static constexpr auto INIT_POP_1_FLY_02 = 4293134;
  static constexpr auto INIT_POP_1_FLY_03 = 4293135;
  static constexpr auto INIT_POP_1_FLY_04 = 4293136;
  static constexpr auto INIT_POP_2_SLUG_01 = 4293144;
  static constexpr auto INIT_POP_2_SLUG_02 = 4293145;
  static constexpr auto INIT_POP_2_FLY_01 = 4293146;
  static constexpr auto INIT_POP_2_FLY_02 = 4293147;
  static constexpr auto INIT_POP_2_RPT_01 = 4293148;
  static constexpr auto INIT_POP_2_SLUG_03 = 4293149;
  static constexpr auto INIT_POP_3_WATER_ERMNT_01 = 4293151;
  static constexpr auto INIT_POP_3_WATER_ERMNT_02 = 4293152;
  static constexpr auto INIT_POP_3_FLY_01 = 4293153;
  static constexpr auto INIT_POP_3_FLY_02 = 4293154;
  static constexpr auto INIT_POP_3_RPT_01 = 4293155;
  static constexpr auto INIT_POP_3_WATER_ERMNT_03 = 4293156;
  static constexpr auto CUT_END_NCUT = 346;
  static constexpr auto LOC_ACTOR0 = 1007130;
  static constexpr auto LOC_ACTOR1 = 1007131;
  static constexpr auto LOC_POS_ACTOR0 = 4322268;

public:
  SeerFolly() : Sapphire::ScriptAPI::QuestBattleScript( 75 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.registerEObj( "unknown_0", 2005192, 5760474, 4, { -51.493111f, 0.309087f, 71.436897f }, 1.000000f, -0.000006f ); 

  }

  void onUpdate( QuestBattle& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( SeerFolly );