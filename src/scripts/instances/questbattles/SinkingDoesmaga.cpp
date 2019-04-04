#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class SinkingDoesmaga : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_P_POP_01 = 4256368;
  static constexpr auto INIT_P_POP_PET = 4256369;
  static constexpr auto INIT_POP_A_01 = 4256381;
  static constexpr auto INIT_POP_A_02 = 4256382;
  static constexpr auto INIT_POP_B_01 = 4256383;
  static constexpr auto INIT_POP_BOSS_B = 4256387;
  static constexpr auto INIT_POP_C_01 = 4256530;
  static constexpr auto INIT_POP_C_02 = 4256531;
  static constexpr auto INIT_POP_BOSS_C = 4256540;
  static constexpr auto INIT_POP_D_01 = 4256706;
  static constexpr auto INIT_POP_C_03 = 4256707;
  static constexpr auto INIT_POP_C_04 = 4256708;
  static constexpr auto INIT_POP_A_03 = 4256711;
  static constexpr auto INIT_POP_A_04 = 4256712;
  static constexpr auto INIT_POP_BOSS_A = 4256716;
  static constexpr auto INIT_POP_D_02 = 4256717;
  static constexpr auto INIT_POP_A_05 = 4256718;
  static constexpr auto INIT_POP_E_03 = 4256719;
  static constexpr auto INIT_ENPC_POP_01 = 4262403;
  static constexpr auto INIT_ENPC_POP_02 = 4262405;
  static constexpr auto INIT_ENPC_POP_03 = 4262408;
  static constexpr auto INIT_ENPC_POP_04 = 4262411;
  static constexpr auto INIT_WARP_POINT = 4263463;
  static constexpr auto INIT_MAMONJIN = 4263912;
  static constexpr auto LOC_ACTOR0 = 1005198;
  static constexpr auto LOC_ACTOR1 = 1005190;
  static constexpr auto LOC_POS_ACTOR0 = 4289721;
  static constexpr auto LOC_POS_ACTOR1 = 4289778;
  static constexpr auto DEF_ACTION_SUMMON_PET_BNPC = 1307;
  static constexpr auto STATUS_CUSTOM_BUFF_MAMONJIN = 688;
  static constexpr auto BGM_BOSSBATTLE = 113;
  static constexpr auto POS_MAMONJIN_POP = 4317127;
  static constexpr auto POS_MEMBER_MOVE_01 = 4335442;
  static constexpr auto LOGMESSAGE_QIB01 = 3225;
  static constexpr auto CUT_START_NCUT = 48;
  static constexpr auto CUT_END_NCUT = 49;
  static constexpr auto LOC_ACTOR2 = 1005365;
  static constexpr auto LOC_ACTOR3 = 1005366;
  static constexpr auto LOC_ACTOR4 = 1005367;
  static constexpr auto LOC_ACTION1 = 827;
  static constexpr auto LOC_FACE0 = 604;
  static constexpr auto LOC_FACE1 = 617;
  static constexpr auto LOC_FACE2 = 611;

public:
  SinkingDoesmaga() : Sapphire::ScriptAPI::QuestBattleScript( 53 )
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

EXPOSE_SCRIPT( SinkingDoesmaga );