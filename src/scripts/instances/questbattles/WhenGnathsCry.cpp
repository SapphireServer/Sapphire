#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class WhenGnathsCry : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto BNPC_SENSEI = 5886224;
  static constexpr auto BNPC_SANSON = 5886229;
  static constexpr auto BNPC_GUYDELOT = 5886230;
  static constexpr auto BNPC_DIR_DUMMY = 5923655;
  static constexpr auto BNPC_GOAL_01 = 5923387;
  static constexpr auto BNPC_GOAL_02 = 5923388;
  static constexpr auto BNPC_GOAL_03 = 5923390;
  static constexpr auto BNPC_GOAL_04 = 5923537;
  static constexpr auto BNPC_GOAL_05 = 5886232;
  static constexpr auto BNPC_P1_CNJ_01 = 5886225;
  static constexpr auto BNPC_P1_LNC_01 = 5886227;
  static constexpr auto BNPC_P1_MCH_01 = 5886228;
  static constexpr auto BNPC_P2_LNC_01 = 5886234;
  static constexpr auto BNPC_P2_LNC_02 = 5886235;
  static constexpr auto BNPC_P2_LNC_03 = 5886236;
  static constexpr auto BNPC_P2_LNC_04 = 5924207;
  static constexpr auto EOBJ_RESCUE = 5886231;
  static constexpr auto ACTION_GOAL_TRIGER = 3269;
  static constexpr auto EVENTACTION_RESCUE = 35;
  static constexpr auto BNPC_P1_LNC_02 = 5960883;
  static constexpr auto BNPC_P1_MCH_02 = 5960884;

public:
  WhenGnathsCry() : Sapphire::ScriptAPI::QuestBattleScript( 122 )
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

EXPOSE_SCRIPT( WhenGnathsCry );