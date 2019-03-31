#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class DoingIttheBardWay : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_POP_1_BOSS_IKU_01 = 4298952;
  static constexpr auto INIT_POP_1_WLF_01 = 4298953;
  static constexpr auto INIT_POP_1_WLF_02 = 4298954;
  static constexpr auto INIT_POP_2_IKE_LNC_001 = 4298957;
  static constexpr auto INIT_POP_2_IKE_CNJ_001 = 4298958;
  static constexpr auto CUT_START_NCUT = 325;
  static constexpr auto CUT_END_NCUT = 326;
  static constexpr auto JOB_STORY_MES = 3665;

public:
  DoingIttheBardWay() : Sapphire::ScriptAPI::QuestBattleScript( 77 )
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

EXPOSE_SCRIPT( DoingIttheBardWay );