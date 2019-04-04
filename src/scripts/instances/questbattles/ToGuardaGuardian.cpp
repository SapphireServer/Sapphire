#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class ToGuardaGuardian : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_NOTAR_P_POP_1ST_01 = 3854583;
  static constexpr auto INIT_NOTAR_POP_1ST_01 = 3854586;
  static constexpr auto INIT_NOTAR_P_POP_2ST_01 = 3854588;
  static constexpr auto INIT_NOTAR_POP_2ST_01 = 3854584;
  static constexpr auto INIT_NOTAR_POP_2ST_02 = 3854721;
  static constexpr auto INIT_NOTAR_P_POP_3ST_01 = 3854673;
  static constexpr auto INIT_NOTAR_POP_3ST_01 = 3854720;
  static constexpr auto INIT_NOTAR_P_POP_4ST_01 = 3854674;
  static constexpr auto INIT_NOTAR_POP_4ST_01 = 3854719;
  static constexpr auto INIT_NOTAR_POP_4ST_02 = 3854724;
  static constexpr auto INIT_NOTAR_P_POP_5ST_01 = 3854675;
  static constexpr auto INIT_NOTAR_POP_5ST_01 = 3854715;
  static constexpr auto INIT_NOTAR_POP_5ST_02 = 3854723;
  static constexpr auto INIT_P_POP_1ST_01 = 4089300;
  static constexpr auto INIT_P_POP_1ST_02 = 4089305;
  static constexpr auto INIT_POP_1ST_BOSS = 4089289;
  static constexpr auto INIT_POP_1ST_EXC_01_01 = 4089296;
  static constexpr auto INIT_POP_1ST_EXC_01_02 = 4089297;
  static constexpr auto INIT_POP_1ST_EXC_01_03 = 4089298;
  static constexpr auto INIT_POP_1ST_LNC_01_04 = 4089292;
  static constexpr auto INIT_POP_1ST_LNC_01_05 = 4089293;
  static constexpr auto INIT_POP_1ST_LNC_01_06 = 4089294;
  static constexpr auto INIT_P_POP_1ST_03 = 3854581;
  static constexpr auto INIT_P_POP_1ST_04 = 3854582;
  static constexpr auto INIT_POP_1ST_CNJ_02_01 = 3803263;
  static constexpr auto INIT_POP_1ST_CNJ_02_02 = 3803264;
  static constexpr auto INIT_POP_1ST_EXC_02_03 = 4089325;
  static constexpr auto INIT_POP_1ST_EXC_02_04 = 3803269;
  static constexpr auto INIT_POP_1ST_LNC_02_05 = 3803267;
  static constexpr auto INIT_POP_1ST_LNC_02_06 = 3803268;
  static constexpr auto INIT_POP_1ST_MON_03_01 = 4089330;
  static constexpr auto INIT_POP_2ND_01 = 4089338;
  static constexpr auto INIT_POP_2ND_02 = 3854784;
  static constexpr auto INIT_P_POP_2ND_01 = 4018837;
  static constexpr auto INIT_P_POP_2ND_02 = 4018839;
  static constexpr auto WARP_01 = 3803262;
  static constexpr auto ACTION_CURE = 120;
  static constexpr auto ACTION_PRO = 123;
  static constexpr auto DEF_ACTION_MONSTER_SUMMON = 867;
  static constexpr auto DEF_ACTION_DOKUBARI = 619;
  static constexpr auto CUT_SCENE_01 = 58;
  static constexpr auto CUT_SCENE_02 = 59;
  static constexpr auto DEF_POISON = 18;
  static constexpr auto DEF_WEATHER_BOSS = 19;
  static constexpr auto DEF_WEATHER_RETURN = 2;
  static constexpr auto BGM_MASKED_BATTLE = 94;

public:
  ToGuardaGuardian() : Sapphire::ScriptAPI::QuestBattleScript( 12 )
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

EXPOSE_SCRIPT( ToGuardaGuardian );