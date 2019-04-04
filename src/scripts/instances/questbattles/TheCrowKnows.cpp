#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class TheCrowKnows : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_POP_OBORO_01 = 5143462;
  static constexpr auto INIT_POP_KARASU_1_01 = 5143463;
  static constexpr auto INIT_POP_CHUNIN_1_01 = 5143464;
  static constexpr auto INIT_POP_CHUNIN_1_02 = 5143473;
  static constexpr auto INIT_POP_CHUNIN_1_03 = 5143474;
  static constexpr auto INIT_POP_RANDOM_POP_2_01 = 5143520;
  static constexpr auto INIT_POP_BAT_2_01 = 5143522;
  static constexpr auto INIT_POP_RANDOM_POP_3_01 = 5143525;
  static constexpr auto INIT_POP_BAT_3_01 = 5143526;
  static constexpr auto INIT_POP_RANDOM_POP_3_02 = 5143529;
  static constexpr auto INIT_POP_BAT_3_02 = 5143530;
  static constexpr auto EOBJ_MAKIBISHI = 5327263;
  static constexpr auto STATUS_MAKIBISHI_DAMAGE = 1221;
  static constexpr auto DEF_ACTION_MAKIBISHI = 3196;
  static constexpr auto LOC_ACTOR0 = 1010598;
  static constexpr auto LOC_ACTOR1 = 1010597;
  static constexpr auto LOC_ACTOR2 = 1010560;
  static constexpr auto LOC_POS_ACTOR0 = 5375031;
  static constexpr auto CUT_SCENE_00 = 691;
  static constexpr auto LOC_MOTION0 = 936;
  static constexpr auto LOC_BGM0 = 114;
  static constexpr auto M_BAT_POP_INTERVAL_1 = 12;
  static constexpr auto M_BAT_POP_INTERVAL_2 = 15;
  static constexpr auto M_BAT_POP_INTERVAL_3 = 15;

public:
  TheCrowKnows() : Sapphire::ScriptAPI::QuestBattleScript( 99 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.registerEObj( "unknown_0", 2009569, 0, 4, { 763.213318f, 9.000000f, 358.016998f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_1", 2009570, 0, 4, { 748.506775f, 9.000000f, 520.002930f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheCrowKnows );