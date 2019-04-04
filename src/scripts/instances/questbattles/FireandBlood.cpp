#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class FireandBlood : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto CUT_SCENE_N_01 = 854;
  static constexpr auto CUT_SCENE_N_02 = 855;
  static constexpr auto INIT_POP_BNPC_COMPANION_ALPHINAUD = 5866564;
  static constexpr auto INIT_POP_BNPC_COMPANION_HILDA = 5866565;
  static constexpr auto INIT_POP_BNPC_ENEMY_P1_CHARIBERT = 5866560;
  static constexpr auto INIT_POP_BNPC_ENEMY_P1_ZAKO_GEN = 5866561;
  static constexpr auto INIT_POP_BNPC_ENEMY_P1_ZAKO_JU1 = 5866562;
  static constexpr auto INIT_POP_BNPC_ENEMY_P1_ZAKO_JU2 = 5877278;
  static constexpr auto INIT_POP_BNPC_ENEMY_GIMMIC_VFX_FIREBALL = 5866580;
  static constexpr auto SECOND_POP_BNPC_ENEMY_P2_A_ZAKO_JU = 5875773;
  static constexpr auto SECOND_POP_BNPC_ENEMY_P2_B_ZAKO_YARI = 5866571;
  static constexpr auto SECOND_POP_BNPC_ENEMY_P2_B_ZAKO_KEN = 5866572;
  static constexpr auto SECOND_POP_BNPC_ENEMY_P2_C_ZAKO_YARI = 5866568;
  static constexpr auto SECOND_POP_BNPC_ENEMY_P2_C_ZAKO_KEN = 5866569;
  static constexpr auto THIRD_POP_BNPC_COMPANION_HAURCHEFANT = 5866579;
  static constexpr auto THIRD_POP_BNPC_ENEMY_P3_D_ZAKO_JU = 5866577;
  static constexpr auto THIRD_POP_BNPC_ENEMY_P3_D_ZAKO_GEN = 5866578;
  static constexpr auto EOBJ_DAMAGE_AREA = 5898500;
  static constexpr auto STATUS_PARAM_FIRE_DAMAGE = 1700;
  static constexpr auto ACTION_DARK_FIREGA = 3791;
  static constexpr auto ACTION_FIRERA = 2175;
  static constexpr auto STATUS_FIRE_DOT = 267;
  static constexpr auto DEF_ACTION_SUMMON_PET_BNPC = 4785;
  static constexpr auto BNPC_COMPANION_PET_CARBUNCLE_RED = 5898576;
  static constexpr auto LOCKON_FIRE = 25;
  static constexpr auto QIB_YELL_01 = 2659;
  static constexpr auto QIB_YELL_02 = 2660;
  static constexpr auto QIB_YELL_03 = 2661;
  static constexpr auto QIB_YELL_04 = 2662;

public:
  FireandBlood() : Sapphire::ScriptAPI::QuestBattleScript( 109 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.registerEObj( "ClanHuntboard", 2005909, 5863338, 4, { 73.908386f, 24.322830f, 22.067520f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_0", 2000608, 5105673, 4, { 84.499992f, 24.124950f, 22.859011f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_1", 2000608, 5048108, 4, { 97.900009f, 24.465071f, -4.244444f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( FireandBlood );