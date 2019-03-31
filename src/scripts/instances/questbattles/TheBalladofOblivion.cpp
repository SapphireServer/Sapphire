#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class TheBalladofOblivion : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto BNPC_COMPANION_SANSON_01 = 5908646;
  static constexpr auto BNPC_COMPANION_GUYDELOT_01 = 5908647;
  static constexpr auto BNPC_COMPANION_MOGTA_01 = 5908650;
  static constexpr auto BNPC_ENEMY_SIREN_01 = 5908651;
  static constexpr auto CUT_SCENE_01 = 964;
  static constexpr auto POP_RANGE_CHARGE_01 = 5933330;
  static constexpr auto POP_RANGE_CHARGE_02 = 5933331;
  static constexpr auto POP_RANGE_CHARGE_03 = 5933333;
  static constexpr auto POP_RANGE_CHARGE_04 = 5933334;
  static constexpr auto POP_RANGE_CHARGE_05 = 5934802;
  static constexpr auto POP_RANGE_CHARGE_06 = 5934805;
  static constexpr auto POP_RANGE_CHARGE_07 = 5934806;
  static constexpr auto POP_RANGE_CHARGE_08 = 5934812;
  static constexpr auto BNPC_ENEMY_SIREN_CHARGE = 5933359;
  static constexpr auto ACTION_SIREN_WARP_START = 1537;
  static constexpr auto ACTION_SIREN_WARP_END = 1538;
  static constexpr auto ACTION_SIREN_CHARGE = 4988;
  static constexpr auto POP_RANGE_DOUGHNUT = 5934847;
  static constexpr auto LCUT_ACTOR0 = 1014547;
  static constexpr auto LCUT_ACTOR1 = 1014546;
  static constexpr auto LCUT_ACTOR2 = 1014549;
  static constexpr auto LCUT_POS0 = 5935823;
  static constexpr auto LCUT_POS1 = 5935824;
  static constexpr auto BNPC_TOUMEI_PLAYER = 5963051;

public:
  TheBalladofOblivion() : Sapphire::ScriptAPI::QuestBattleScript( 133 )
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

EXPOSE_SCRIPT( TheBalladofOblivion );