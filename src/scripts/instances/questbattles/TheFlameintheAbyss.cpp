#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class TheFlameintheAbyss : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto BNPC_COMPANION_SIDURGU_01 = 5912555;
  static constexpr auto BNPC_ENEMY_PHASE_1_TANK_MOOGLE_01 = 5912556;
  static constexpr auto BNPC_ENEMY_PHASE_1_HEALER_MOOGLE_01 = 5912557;
  static constexpr auto BNPC_ENEMY_PHASE_2_SNIPER_MOOGLE_01 = 5912558;
  static constexpr auto BNPC_ENEMY_PHASE_2_NUKER_MOOGLE_01 = 5912559;
  static constexpr auto BNPC_ENEMY_PHASE_3_ATTACKER_MOOGLE_01 = 5912560;
  static constexpr auto BNPC_ENEMY_PHASE_3_BUFFER_MOOGLE_01 = 5912561;
  static constexpr auto BNPC_ENEMY_PHASE_3_DEBUFFER_MOOGLE_01 = 5912562;
  static constexpr auto CUT_SCENE_01 = 994;
  static constexpr auto LOC_ACTOR0 = 1014593;
  static constexpr auto LOC_ACTOR1 = 1014607;
  static constexpr auto LOC_ACTOR2 = 1014608;
  static constexpr auto LOC_MARKER_01 = 5959850;
  static constexpr auto LOC_BGM0 = 178;

public:
  TheFlameintheAbyss() : Sapphire::ScriptAPI::QuestBattleScript( 147 )
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

EXPOSE_SCRIPT( TheFlameintheAbyss );