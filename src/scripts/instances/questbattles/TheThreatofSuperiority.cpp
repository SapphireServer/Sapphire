#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class TheThreatofSuperiority : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_POP_01 = 4033627;
  static constexpr auto INIT_POP_02 = 4033629;
  static constexpr auto INIT_POP_03 = 4033631;
  static constexpr auto INIT_POP_07 = 4033691;
  static constexpr auto INIT_POP_08 = 4033692;
  static constexpr auto INIT_EO_POP_01 = 4033684;
  static constexpr auto EVENT_ACTION_01 = 16;
  static constexpr auto INIT_P_POP_01 = 4033688;
  static constexpr auto INIT_POP_ENEMY_F01 = 4089803;
  static constexpr auto INIT_POP_ENEMY_F02 = 4089804;
  static constexpr auto INIT_POP_ENEMY_F03 = 4089805;
  static constexpr auto ACTOR20 = 1001713;
  static constexpr auto ACTOR30 = 1002325;
  static constexpr auto ACTOR40 = 1002326;
  static constexpr auto CUT_CLSTHM15010 = 51;
  static constexpr auto INIT_POP_04 = 4169221;
  static constexpr auto INIT_EO_POP_02 = 4185128;
  static constexpr auto LOC_POS_EOBJ1 = 4033684;
  static constexpr auto BGM_BATTLE = 37;

public:
  TheThreatofSuperiority() : Sapphire::ScriptAPI::QuestBattleScript( 40 )
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

EXPOSE_SCRIPT( TheThreatofSuperiority );