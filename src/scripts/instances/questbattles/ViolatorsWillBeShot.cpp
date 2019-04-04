#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class ViolatorsWillBeShot : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_POP_01 = 3818956;
  static constexpr auto INIT_POP_02 = 3818957;
  static constexpr auto INIT_POP_03 = 3818958;
  static constexpr auto INIT_POP_04 = 3818959;
  static constexpr auto INIT_POP_05 = 3818960;
  static constexpr auto INIT_POP_06 = 3818961;
  static constexpr auto INIT_POP_07 = 3818962;
  static constexpr auto INIT_POP_08 = 3818963;
  static constexpr auto INIT_POP_09 = 3818964;
  static constexpr auto INIT_POP_10 = 3818966;
  static constexpr auto INIT_POP_11 = 3818967;
  static constexpr auto INIT_POP_12 = 3818968;
  static constexpr auto BNPC_001 = 113;
  static constexpr auto ER_RECT_01 = 4246562;
  static constexpr auto INIT_POP_CAMP_EXC01 = 4246567;
  static constexpr auto INIT_POP_CAMP_EXC02 = 4246568;
  static constexpr auto INIT_POP_CAMP_LNC01 = 4246569;
  static constexpr auto INIT_POP_CAMP_EXC03 = 4246638;
  static constexpr auto INIT_POP_CAMP_EXC04 = 4246639;
  static constexpr auto INIT_POP_CAMP_LNC02 = 4246640;
  static constexpr auto DEF_ACTION_WATERA = 1016;
  static constexpr auto INIT_P_POP_MIRAUDONT = 4246724;
  static constexpr auto INIT_POP_ADD_GLA01 = 4246863;
  static constexpr auto INIT_POP_ADD_GLA02 = 4246864;
  static constexpr auto POP_RANGE_MIRAUDONT_MOVE = 4358145;

public:
  ViolatorsWillBeShot() : Sapphire::ScriptAPI::QuestBattleScript( 6 )
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

EXPOSE_SCRIPT( ViolatorsWillBeShot );