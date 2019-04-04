#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class FacingYourDemons : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_POP_01 = 4031416;
  static constexpr auto INIT_POP_02 = 4031423;
  static constexpr auto INIT_POP_03 = 4031424;
  static constexpr auto INIT_POP_04 = 4031425;
  static constexpr auto INIT_P_POP_01 = 4031419;
  static constexpr auto INIT_P_POP_02 = 4031420;
  static constexpr auto INIT_P_POP_03 = 4031421;
  static constexpr auto INIT_P_POP_04 = 4031422;
  static constexpr auto INIT_P_POP_05 = 4143519;
  static constexpr auto INIT_P_POP_06 = 4143524;
  static constexpr auto CUT_CLSTHM30010 = 168;
  static constexpr auto CUT_CLSTHM30020 = 169;
  static constexpr auto DEF_ACTION_MONSTER_SUMMON = 867;
  static constexpr auto DEF_ACTION_SUCCUBUS_SILENCE = 869;
  static constexpr auto PR_FIXED_POS_01 = 4208386;
  static constexpr auto PR_FIXED_POS_02 = 4208387;
  static constexpr auto PR_FIXED_POS_03 = 4208388;

public:
  FacingYourDemons() : Sapphire::ScriptAPI::QuestBattleScript( 43 )
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

EXPOSE_SCRIPT( FacingYourDemons );