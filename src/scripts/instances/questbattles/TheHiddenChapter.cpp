#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class TheHiddenChapter : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_POP_01 = 4035753;
  static constexpr auto INIT_POP_02 = 4035757;
  static constexpr auto INIT_POP_03 = 4035758;
  static constexpr auto INIT_POP_04 = 4035762;
  static constexpr auto INIT_POP_05 = 4035763;
  static constexpr auto INIT_POP_06 = 4035764;
  static constexpr auto INIT_POP_07 = 4035765;
  static constexpr auto INIT_POP_08 = 4036114;
  static constexpr auto INIT_POP_09 = 4036608;
  static constexpr auto INIT_POP_10 = 4036610;
  static constexpr auto INIT_POP_11 = 4036611;
  static constexpr auto INIT_POP_12 = 4036612;
  static constexpr auto INIT_POP_13 = 4036621;
  static constexpr auto LOC_ACTOR1 = 1001708;
  static constexpr auto LOC_ACTOR2 = 1001709;
  static constexpr auto LOC_ACTOR3 = 1001710;
  static constexpr auto LOC_ACTOR4 = 1001711;
  static constexpr auto LOC_ACTOR5 = 1001712;
  static constexpr auto LOC_POS_ACTOR1 = 4101648;
  static constexpr auto LOC_POS_ACTOR2 = 4101651;
  static constexpr auto LOC_ACTION1 = 787;
  static constexpr auto LOC_ACTION2_0 = 791;
  static constexpr auto LOC_ACTION2_1 = 794;
  static constexpr auto LOC_ACTION2_2 = 795;
  static constexpr auto DEF_ACTION_THUNDER_STRIKE = 325;

public:
  TheHiddenChapter() : Sapphire::ScriptAPI::QuestBattleScript( 42 )
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

EXPOSE_SCRIPT( TheHiddenChapter );