#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class LanceofDestiny : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_P_POP_01 = 4248895;
  static constexpr auto INIT_POP_BOSS = 4248927;
  static constexpr auto INIT_POP_A_01 = 4248928;
  static constexpr auto INIT_POP_A_02 = 4248929;
  static constexpr auto INIT_POP_A_03 = 4248938;
  static constexpr auto INIT_POP_A_04 = 4248939;
  static constexpr auto INIT_POP_B_01 = 4248948;
  static constexpr auto INIT_POP_C_01 = 4248944;
  static constexpr auto INIT_POP_C_02 = 4248945;
  static constexpr auto LOG_MSG_EVENT_QIB_LNC004_BTL_01 = 3201;
  static constexpr auto LOG_MSG_EVENT_QIB_LNC004_BTL_02 = 3202;
  static constexpr auto DEF_ACTION_BOA_WS_CRITICAL = 335;
  static constexpr auto CUT_SCENE_01 = 21;
  static constexpr auto CUT_SCENE_02 = 319;

public:
  LanceofDestiny() : Sapphire::ScriptAPI::QuestBattleScript( 55 )
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

EXPOSE_SCRIPT( LanceofDestiny );