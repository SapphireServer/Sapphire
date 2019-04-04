#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class PrimalBurdens : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_P_POP_MITRA_01 = 4302956;
  static constexpr auto INIT_POP_1_TRISTAN_01 = 4302960;
  static constexpr auto INIT_POP_1_BELIAS_EGI_01 = 4302979;
  static constexpr auto INIT_POP_FIRE_SPRIT_01 = 4328234;
  static constexpr auto DEF_ACTION_DARK_ABSORB = 1348;
  static constexpr auto DEF_ACTION_MONSTER_SUMMON = 1163;
  static constexpr auto QIB_LOG_MESSAGE_01 = 3227;
  static constexpr auto CUT_START_NCUT = 355;
  static constexpr auto CUT_END_NCUT = 356;
  static constexpr auto QIB_CHANNELING_DARK = 1;
  static constexpr auto JOB_STORY_MES = 3676;

public:
  PrimalBurdens() : Sapphire::ScriptAPI::QuestBattleScript( 82 )
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

EXPOSE_SCRIPT( PrimalBurdens );