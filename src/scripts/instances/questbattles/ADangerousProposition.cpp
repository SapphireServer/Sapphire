#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class ADangerousProposition : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_POP_BOSS = 3792898;
  static constexpr auto INIT_POP_01 = 3792905;
  static constexpr auto INIT_POP_02 = 3792907;
  static constexpr auto INIT_POP_03 = 3792908;
  static constexpr auto INIT_POP_04 = 3792909;
  static constexpr auto INIT_POP_05 = 3792911;
  static constexpr auto INIT_POP_06 = 3792912;
  static constexpr auto INIT_POP_07 = 3792913;
  static constexpr auto INIT_POP_08 = 3792914;
  static constexpr auto INIT_POP_09 = 3792916;
  static constexpr auto INIT_POP_10 = 3792917;
  static constexpr auto INIT_POP_11 = 3911020;
  static constexpr auto INIT_P_POP_01 = 4259221;
  static constexpr auto BNPC_001 = 543;
  static constexpr auto LOC_POS_PC_FIRST = 3879338;
  static constexpr auto LOC_ACTOR0 = 1003009;
  static constexpr auto BNPC_NAME_01 = 626;
  static constexpr auto DEF_ACTION_BLIND_POISON = 1089;
  static constexpr auto DEF_BLIND = 15;

public:
  ADangerousProposition() : Sapphire::ScriptAPI::QuestBattleScript( 7 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.registerEObj( "unknown_0", 2005192, 5760474, 4, { -51.493111f, 0.309087f, 71.436897f }, 1.000000f, -0.000006f ); 

  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( ADangerousProposition );