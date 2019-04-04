#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class FeintandStrike : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_P_POP_1ST_01 = 4102995;
  static constexpr auto INIT_P_POP_1ST_02 = 4102998;
  static constexpr auto INIT_P_POP_1ST_03 = 4103009;
  static constexpr auto INIT_P_POP_1ST_04 = 4103010;
  static constexpr auto INIT_POP_1ST_BOSS = 4102991;
  static constexpr auto INIT_POP_1ST_ARC_01_01 = 4102992;
  static constexpr auto INIT_POP_1ST_ARC_01_02 = 4102993;
  static constexpr auto INIT_POP_1ST_ARC_01_03 = 4102994;
  static constexpr auto INIT_POP_1ST_PGL_01_04 = 4102999;
  static constexpr auto INIT_POP_1ST_PGL_01_05 = 4103000;
  static constexpr auto INIT_POP_1ST_PGL_01_06 = 4103001;
  static constexpr auto INIT_POP_1ST_CNJ_02_01 = 4103170;
  static constexpr auto INIT_POP_1ST_THM_02_02 = 4103171;
  static constexpr auto INIT_POP_1ST_ARC_02_03 = 4103160;
  static constexpr auto INIT_POP_1ST_ARC_02_04 = 4103161;
  static constexpr auto INIT_POP_1ST_PGL_02_05 = 4103168;
  static constexpr auto INIT_POP_1ST_PGL_02_06 = 4103169;
  static constexpr auto INIT_POP_1ST_MON_03_01 = 4103180;
  static constexpr auto INIT_POP_2ND_01 = 4103186;
  static constexpr auto INIT_POP_2ND_02 = 4103187;
  static constexpr auto INIT_P_POP_2ND_01 = 4103188;
  static constexpr auto WARP_01 = 4102986;
  static constexpr auto ACTION_CURE = 120;
  static constexpr auto ACTION_PRO = 123;
  static constexpr auto DEF_ACTION_MONSTER_SUMMON = 867;
  static constexpr auto DEF_ACTION_DOKUBARI = 619;
  static constexpr auto CUT_SCENE_01 = 208;
  static constexpr auto CUT_SCENE_02 = 209;
  static constexpr auto INIT_NOTAR_P_POP_1ST_01 = 4103313;
  static constexpr auto INIT_NOTAR_P_POP_1ST_02 = 4103316;
  static constexpr auto INIT_NOTAR_P_POP_1ST_03 = 4103321;
  static constexpr auto INIT_NOTAR_P_POP_1ST_04 = 4103323;
  static constexpr auto INIT_NOTAR_P_POP_1ST_05 = 4103325;
  static constexpr auto INIT_NOTAR_POP_1ST_01 = 4103314;
  static constexpr auto INIT_NOTAR_POP_1ST_02 = 4103317;
  static constexpr auto INIT_NOTAR_POP_1ST_03 = 4103322;
  static constexpr auto INIT_NOTAR_POP_1ST_04 = 4103324;
  static constexpr auto INIT_NOTAR_POP_1ST_05 = 4103327;
  static constexpr auto DEF_POISON = 18;
  static constexpr auto DEF_WEATHER_BOSS = 19;
  static constexpr auto ACTION_CUREA = 135;
  static constexpr auto DEF_WEATHER_RETURN = 2;
  static constexpr auto BGM_MASKED_BATTLE = 94;

public:
  FeintandStrike() : Sapphire::ScriptAPI::QuestBattleScript( 36 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.registerEObj( "Entrance", 2000182, 6228959, 5, { 457.583801f, 5.680784f, 280.512787f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "unknown_0", 2000608, 2807920, 4, { -95.322441f, -25.054260f, 61.518002f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( FeintandStrike );