#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class AgainsttheShadow : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto BNPC_WIDARGELT = 5886248;
  static constexpr auto BNPC_P1_KEGEMNK_01 = 5886249;
  static constexpr auto BNPC_P1_KEGEMNK_02 = 5886250;
  static constexpr auto BNPC_P1_ENERGY_01 = 5887413;
  static constexpr auto BNPC_P1_ENERGY_02 = 5916107;
  static constexpr auto ACTION_ENERGY_SUMMON = 1094;
  static constexpr auto LOC_POP_0 = 5919819;
  static constexpr auto LOC_POP_1 = 5919820;
  static constexpr auto LOC_ACTOR_0 = 1014543;
  static constexpr auto LOC_ACTOR_1 = 1014540;
  static constexpr auto LOC_ACTOR_2 = 1014541;
  static constexpr auto BGM_BATTLE = 107;
  static constexpr auto LOC_ACTION1 = 1071;
  static constexpr auto LOC_ACTION2 = 173;
  static constexpr auto LOCKON_BY_ENERGY_BALL_THUNDER = 1;

public:
  AgainsttheShadow() : Sapphire::ScriptAPI::QuestBattleScript( 123 )
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

EXPOSE_SCRIPT( AgainsttheShadow );