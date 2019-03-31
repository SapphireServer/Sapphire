#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class TheOneThatGotAway : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_POP_BOSS = 3762267;
  static constexpr auto INIT_POP_1_ARC_01 = 3762259;
  static constexpr auto INIT_POP_1_ARC_02 = 3762264;
  static constexpr auto INIT_POP_1_ARC_03 = 4277285;
  static constexpr auto INIT_POP_1_LNC_01 = 3762262;
  static constexpr auto INIT_POP_1_LNC_02 = 3762265;
  static constexpr auto INIT_POP_1_LNC_03 = 4277284;
  static constexpr auto INIT_P_POP_LEIHALIAPOH = 3815984;
  static constexpr auto INIT_P_POP_SILVAIRRE = 3815986;
  static constexpr auto INIT_POP_2_ARC_01 = 4277286;
  static constexpr auto INIT_POP_2_ARC_02 = 4277287;
  static constexpr auto INIT_POP_2_LNC_01 = 4277288;
  static constexpr auto INIT_POP_2_LNC_02 = 4277289;
  static constexpr auto INIT_POP_2_CNJ_01 = 4277290;
  static constexpr auto INIT_POP_2_THM_01 = 4277291;
  static constexpr auto CUT_SCENE_01 = 14;
  static constexpr auto CUT_SCENE_02 = 15;
  static constexpr auto EOBJ_BTL_ARROW_FIRE = 4309876;
  static constexpr auto STATUS_CUSTOM_ARROW_FIRE = 675;
  static constexpr auto DEF_ACTION_SIDEWINDER = 1060;
  static constexpr auto DEF_ACTION_MONSTER_WHISTLE = 983;
  static constexpr auto DEF_PARALYSIS = 17;

public:
  TheOneThatGotAway() : Sapphire::ScriptAPI::QuestBattleScript( 3 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.registerEObj( "Entrance", 2000182, 5021407, 5, { 623.000000f, 23.872311f, 94.505638f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 623.000000f, 23.656260f, 61.956181f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( QuestBattle& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheOneThatGotAway );