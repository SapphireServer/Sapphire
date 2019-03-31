#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class TrialbyWater : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_POP_1_YK_01 = 3875540;
  static constexpr auto INIT_POP_1_YK_02 = 3879109;
  static constexpr auto INIT_POP_1_YK_03 = 3905947;
  static constexpr auto INIT_POP_2_YK_01 = 3905948;
  static constexpr auto INIT_POP_2_YK_02 = 4263917;
  static constexpr auto INIT_POP_2_YK_03 = 4263918;
  static constexpr auto INIT_POP_3_YK_01 = 4263934;
  static constexpr auto INIT_POP_3_YK_02 = 4263935;
  static constexpr auto INIT_POP_3_YK_03 = 4263936;
  static constexpr auto INIT_POP_2_WATER_SPRIT_01 = 4263967;
  static constexpr auto INIT_POP_3_WATER_SPRIT_01 = 4263969;
  static constexpr auto INIT_POP_3_WATER_SPRIT_02 = 4263970;
  static constexpr auto INIT_P_POP_LNC_01 = 3905949;
  static constexpr auto INIT_P_POP_LNC_02 = 4263914;
  static constexpr auto INIT_P_POP_LNC_03 = 4263915;
  static constexpr auto INIT_P_POP_ARC_01 = 3914511;
  static constexpr auto BNPC_NAME_01 = 628;
  static constexpr auto CUT_SCENE_01 = 8;
  static constexpr auto CUT_SCENE_02 = 9;
  static constexpr auto QIB_YELL_01 = 966;
  static constexpr auto QIB_YELL_02 = 967;

public:
  TrialbyWater() : Sapphire::ScriptAPI::QuestBattleScript( 16 )
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

EXPOSE_SCRIPT( TrialbyWater );