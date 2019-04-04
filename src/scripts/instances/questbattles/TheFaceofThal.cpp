#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class TheFaceofThal : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_P_POP_01 = 4000991;
  static constexpr auto INIT_P_POP_02 = 4001010;
  static constexpr auto INIT_P_POP_03 = 4001011;
  static constexpr auto INIT_P_POP_04 = 4001012;
  static constexpr auto INIT_P_POP_05 = 4001013;
  static constexpr auto INIT_POP_01A_01 = 4001017;
  static constexpr auto INIT_POP_01A_02 = 4001018;
  static constexpr auto INIT_POP_01A_03 = 4001019;
  static constexpr auto INIT_POP_01A_04 = 4001020;
  static constexpr auto INIT_POP_01B_01 = 4001025;
  static constexpr auto INIT_POP_01B_02 = 4001026;
  static constexpr auto INIT_POP_01B_03 = 4001073;
  static constexpr auto INIT_POP_01C_01 = 4001028;
  static constexpr auto INIT_POP_01C_02 = 4001029;
  static constexpr auto INIT_POP_02A_01 = 4001081;
  static constexpr auto INIT_POP_02A_02 = 4001082;
  static constexpr auto INIT_POP_02A_03 = 4001083;
  static constexpr auto INIT_POP_02A_04 = 4001084;
  static constexpr auto INIT_POP_02B_01 = 4001089;
  static constexpr auto INIT_POP_02B_02 = 4001091;
  static constexpr auto INIT_POP_02B_03 = 4001229;
  static constexpr auto INIT_POP_02D_01 = 4001094;
  static constexpr auto INIT_POP_02D_02 = 4001095;
  static constexpr auto INIT_POP_03A_01 = 4001104;
  static constexpr auto INIT_POP_03A_02 = 4001105;
  static constexpr auto INIT_POP_03A_03 = 4001106;
  static constexpr auto INIT_POP_03A_04 = 4001107;
  static constexpr auto INIT_POP_03E_01 = 4001113;
  static constexpr auto INIT_POP_03E_02 = 4001116;
  static constexpr auto INIT_POP_03E_03 = 4001118;
  static constexpr auto INIT_POP_03BOSS_01 = 4001144;
  static constexpr auto CUT_SCENE_01 = 36;

public:
  TheFaceofThal() : Sapphire::ScriptAPI::QuestBattleScript( 21 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.registerEObj( "Exit", 2000605, 0, 4, { -715.942383f, 69.420113f, -830.370300f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_0", 2000606, 3861081, 4, { -670.462280f, 63.293751f, -801.510986f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Entrance", 2000604, 4262798, 5, { -677.634888f, 64.116386f, -803.174927f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 

  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheFaceofThal );