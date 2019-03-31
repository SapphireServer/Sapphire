#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class ParleyintheSagolii : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_POP_1_BOSS_JENLINCE_01 = 4296937;
  static constexpr auto INIT_POP_1_B_TYPE_GLA_01 = 4296942;
  static constexpr auto INIT_POP_1_B_TYPE_GLA_02 = 4296943;
  static constexpr auto INIT_POP_1_B_TYPE_GLA_03 = 4296944;
  static constexpr auto INIT_POP_1_A_TYPE_GLA_01 = 4296945;
  static constexpr auto CUT_START_NCUT = 330;
  static constexpr auto CUT_END_NCUT = 331;
  static constexpr auto JOB_STORY_MES = 3615;

public:
  ParleyintheSagolii() : Sapphire::ScriptAPI::QuestBattleScript( 68 )
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

EXPOSE_SCRIPT( ParleyintheSagolii );