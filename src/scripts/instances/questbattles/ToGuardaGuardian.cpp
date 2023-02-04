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
    instance.addEObj( "Companychest", 2000470, 4255829, 4255831, 4, { 135.732803f, 14.529310f, -87.463547f }, 0.991760f, 0.298639f, 0); 
    instance.addEObj( "MarkoftheMatron", 2004588, 0, 4982370, 4, { -160.591400f, 4.982750f, -18.484079f }, 1.000000f, 0.744750f, 0); 
    instance.addEObj( "???", 2004120, 0, 4722737, 4, { 39.566650f, 0.604051f, -132.158401f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_0", 2004669, 0, 5018769, 4, { 97.591248f, 13.162170f, -213.884995f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_1", 2004671, 0, 5018772, 4, { -91.002548f, 7.048923f, -177.080704f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_2", 2004672, 0, 5018788, 4, { 85.438347f, 8.000000f, -81.518631f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Carline", 2004268, 0, 4745128, 4, { 123.938202f, 14.170800f, -275.821808f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Carline_1", 2004269, 0, 4745129, 4, { -141.249893f, 7.843656f, -190.537598f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_3", 2004640, 0, 5017541, 4, { 171.426498f, 15.671020f, -129.700302f }, 0.991760f, 1.230898f, 0); 
    instance.addEObj( "Archonegg", 2005212, 0, 5713785, 4, { 85.510887f, 0.410295f, -118.681702f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Archonegg_1", 2005213, 0, 5713791, 4, { -13.138060f, 10.529740f, -250.843094f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Archonegg_2", 2005214, 0, 5713803, 4, { -248.470398f, 1.496751f, -199.399902f }, 0.991760f, 0.000048f, 0); 

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