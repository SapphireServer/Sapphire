#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class TheConsequencesofAnger : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_POP_1_BOSS_TONBELI_01 = 4303542;
  static constexpr auto INIT_P_POP_ARUKA_01 = 4303594;
  static constexpr auto INIT_POP_1_POISON_SLA_01 = 4303610;
  static constexpr auto INIT_POP_1_POISON_SLA_02 = 4303611;
  static constexpr auto INIT_POP_1_POISON_SLA_03 = 4303612;
  static constexpr auto INIT_POP_1_PARAIS_SLA_01 = 4303613;
  static constexpr auto INIT_POP_1_PARAIS_SLA_02 = 4303615;
  static constexpr auto INIT_POP_1_PARAIS_SLA_03 = 4303616;
  static constexpr auto INIT_POP_1_SICK_SLA_01 = 4303619;
  static constexpr auto INIT_POP_2_POISON_SLA_01 = 4303623;
  static constexpr auto INIT_POP_2_POISON_SLA_02 = 4303624;
  static constexpr auto INIT_POP_2_PARAIS_SLA_01 = 4303627;
  static constexpr auto INIT_POP_2_PARAIS_SLA_02 = 4303628;
  static constexpr auto INIT_POP_2_SICK_SLA_01 = 4303630;
  static constexpr auto CUT_START_NCUT = 358;
  static constexpr auto CUT_END_NCUT = 359;
  static constexpr auto JOB_STORY_MES = 3684;

public:
  TheConsequencesofAnger() : Sapphire::ScriptAPI::QuestBattleScript( 84 )
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

EXPOSE_SCRIPT( TheConsequencesofAnger );