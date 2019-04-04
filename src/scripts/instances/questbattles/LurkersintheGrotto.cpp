#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class LurkersintheGrotto : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_POP_BOSS = 4083604;
  static constexpr auto INIT_POP_01_01 = 4083606;
  static constexpr auto INIT_POP_01_02 = 4083607;
  static constexpr auto INIT_POP_02_01 = 4083608;
  static constexpr auto INIT_POP_02_02 = 4083609;
  static constexpr auto INIT_POP_02_03 = 4083610;
  static constexpr auto INIT_POP_02_04 = 4083611;
  static constexpr auto INIT_P_POP_01 = 4083622;
  static constexpr auto CUT_SCENE_01 = 133;
  static constexpr auto HOW_TO_QIB = 79;

public:
  LurkersintheGrotto() : Sapphire::ScriptAPI::QuestBattleScript( 35 )
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

EXPOSE_SCRIPT( LurkersintheGrotto );