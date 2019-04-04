#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class OvertheRails : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_P_POP_01 = 4256134;
  static constexpr auto INIT_P_POP_02 = 4256136;
  static constexpr auto INIT_P_POP_03 = 4256137;
  static constexpr auto INIT_P_POP_PET = 4256201;
  static constexpr auto INIT_POP_A_01 = 4256144;
  static constexpr auto INIT_POP_A_02 = 4256145;
  static constexpr auto INIT_POP_A_03 = 4256146;
  static constexpr auto INIT_POP_B_01 = 4256162;
  static constexpr auto INIT_POP_B_02 = 4256163;
  static constexpr auto INIT_POP_B_03 = 4256164;
  static constexpr auto INIT_POP_B_04 = 4256167;
  static constexpr auto INIT_POP_BOSS = 4256168;
  static constexpr auto INIT_POP_B_05 = 4256170;
  static constexpr auto INIT_POP_B_06 = 4256171;
  static constexpr auto INIT_POP_C_01 = 4256182;
  static constexpr auto INIT_POP_C_02 = 4256183;
  static constexpr auto INIT_POP_C_03 = 4256184;
  static constexpr auto INIT_POP_B_07 = 4256187;
  static constexpr auto INIT_POP_B_08 = 4256188;
  static constexpr auto INIT_POP_D_01 = 4256194;
  static constexpr auto INIT_POP_D_02 = 4256195;
  static constexpr auto DEF_ACTION_SUMMON_PET_BNPC = 1307;
  static constexpr auto YELL_QIB_01 = 1170;
  static constexpr auto YELL_QIB_02 = 1171;
  static constexpr auto YELL_QIB_03 = 1172;
  static constexpr auto CUT_START_NCUT = 45;
  static constexpr auto CUT_END_NCUT = 46;
  static constexpr auto PR_MEMBER_MOVE_01 = 4334919;
  static constexpr auto PR_MEMBER_MOVE_02 = 4334920;

public:
  OvertheRails() : Sapphire::ScriptAPI::QuestBattleScript( 51 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.registerEObj( "sgbg_w_qic_004_01a", 2007457, 6904219, 4, { 5.684449f, 16.347240f, 3.782750f }, 1.000000f, 0.000000f ); 
    // States -> cage01_close_01 (id: 8) cage01_open_01 (id: 10) cage01_open_02 (id: 11) 

  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( OvertheRails );