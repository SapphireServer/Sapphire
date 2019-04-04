#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class TheReasonRoaille : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_POP_ENEMY_ROAILLE = 5068285;
  static constexpr auto INIT_POP_ENEMY_CENTURION = 5068286;
  static constexpr auto INIT_POP_ENEMY_01_03 = 5068287;
  static constexpr auto INIT_POP_ENEMY_01_04 = 5068288;
  static constexpr auto INIT_POP_ENEMY_01_05 = 5068290;
  static constexpr auto INIT_POP_ENEMY_01_06 = 5068291;
  static constexpr auto INIT_POP_ENEMY_01_07 = 5068292;
  static constexpr auto INIT_POP_ENEMY_01_08 = 5068293;
  static constexpr auto INIT_POP_ENEMY_CLAW_01 = 5069486;
  static constexpr auto INIT_POP_ENEMY_CLAW_02 = 5069487;
  static constexpr auto INIT_POP_ENEMY_02_03 = 5069490;
  static constexpr auto INIT_POP_ENEMY_02_04 = 5069491;
  static constexpr auto INIT_POP_ENEMY_02_05 = 5069492;
  static constexpr auto INIT_POP_ENEMY_02_06 = 5069493;
  static constexpr auto INIT_POP_ENEMY_02_07 = 5069494;
  static constexpr auto INIT_POP_ENEMY_02_08 = 5069495;
  static constexpr auto INIT_POP_ENEMY_IRON_GIANT = 5069501;
  static constexpr auto INIT_POP_ENEMY_CONJURER = 5069503;
  static constexpr auto INIT_POP_ENEMY_03_03 = 5069505;
  static constexpr auto INIT_POP_ENEMY_03_04 = 5069506;
  static constexpr auto INIT_POP_ENEMY_03_05 = 5069507;
  static constexpr auto INIT_POP_ENEMY_03_06 = 5069508;
  static constexpr auto INIT_POP_ENEMY_04_01 = 5069512;
  static constexpr auto INIT_POP_ENEMY_04_02 = 5069513;
  static constexpr auto INIT_POP_ENEMY_04_03 = 5069514;
  static constexpr auto INIT_POP_ENEMY_04_04 = 5069515;
  static constexpr auto INIT_POP_ENEMY_MACHINE_01 = 5069521;
  static constexpr auto INIT_POP_ENEMY_MACHINE_02 = 5069522;
  static constexpr auto INIT_POP_ENEMY_MACHINE_03 = 5069523;
  static constexpr auto INIT_POP_ENEMY_05_04 = 5069524;
  static constexpr auto INIT_POP_ENEMY_05_05 = 5069525;
  static constexpr auto INIT_POP_ENEMY_05_06 = 5069526;
  static constexpr auto INIT_POP_ENEMY_05_07 = 5069527;
  static constexpr auto INIT_POP_COMPANION_ILBERD = 5068294;
  static constexpr auto INIT_POP_COMPANION_YUYUHASE = 5068295;
  static constexpr auto INIT_POP_COMPANION_CRYSTAL_BRAVE_LAN = 5068296;
  static constexpr auto INIT_POP_COMPANION_CRYSTAL_BRAVE_ARC = 5068297;
  static constexpr auto INIT_POP_COMPANION_CRYSTAL_BRAVE_CON = 5068298;
  static constexpr auto INIT_POP_COMPANION_FUMETSU_GLA = 5068299;
  static constexpr auto INIT_POP_COMPANION_FUMETSU_PGL = 5068300;
  static constexpr auto INIT_POP_COMPANION_FUMETSU_THA = 5068301;
  static constexpr auto INIT_POP_COMPANION_YUGIRI = 5069516;
  static constexpr auto INIT_POP_COMPANION_DOMA_01 = 5069517;
  static constexpr auto INIT_POP_COMPANION_DOMA_02 = 5069518;
  static constexpr auto QIB_YELL_01 = 2340;
  static constexpr auto QIB_YELL_02 = 2341;
  static constexpr auto QIB_YELL_03 = 2358;
  static constexpr auto QIB_YELL_04 = 2359;
  static constexpr auto QIB_YELL_05 = 2360;
  static constexpr auto QIB_YELL_06 = 2361;
  static constexpr auto LOC_ACTOR0 = 1008191;
  static constexpr auto LOC_ACTOR1 = 1010582;
  static constexpr auto LOC_ACTOR2 = 1010589;
  static constexpr auto LOC_ACTOR3 = 1010590;
  static constexpr auto LOC_ACTOR4 = 1010545;
  static constexpr auto LOC_ACTOR5 = 1010547;
  static constexpr auto LOC_ACTOR6 = 1010591;
  static constexpr auto LOC_ACTOR7 = 1010592;
  static constexpr auto LOC_ACTOR10 = 1008191;
  static constexpr auto LOC_ACTOR11 = 1010546;
  static constexpr auto LOC_ACTOR12 = 1008181;
  static constexpr auto LOC_ACTOR13 = 1010582;
  static constexpr auto LOC_ACTOR14 = 1010593;
  static constexpr auto LOC_ACTOR15 = 1010594;
  static constexpr auto LOC_ACTOR16 = 1010595;
  static constexpr auto LOC_POS_ACTOR0 = 5155969;
  static constexpr auto LOC_POS_ACTOR1 = 5155974;
  static constexpr auto LOC_POS_ACTOR2 = 5155976;
  static constexpr auto ACTION_TIMELINE_EVENT_BASE_STAND_POSE4 = 1055;
  static constexpr auto ACTION_TIMELINE_EVENT_BASE_KNEE_SEACH = 1014;
  static constexpr auto ACTION_TIMELINE_BATTLE_CORPSE = 73;
  static constexpr auto ACTION_TIMELINE_EVENT_BASE_GUARD_STAND = 808;
  static constexpr auto ACTION_TIMELINE_FACIAL_SPEWING = 617;
  static constexpr auto ACTION_TIMELINE_EVENT_BASE_BIND_GROUND_SIT = 979;
  static constexpr auto ACTION_TIMELINE_EVENT_BASE_KNEE_SUFFERING = 936;
  static constexpr auto ACTION_TIMELINE_EVENT_SALUTE_CRY = 1045;
  static constexpr auto LOC_BGM0 = 1;
  static constexpr auto LOC_BGM1 = 84;
  static constexpr auto QIB_CHANNELING = 4;
  static constexpr auto DEF_ACTION_SEISHINHA = 3197;
  static constexpr auto STATUS_PARAM_REGEN = 859;
  static constexpr auto DEF_ACTION_JUBAKU = 3207;
  static constexpr auto EOBJ_JUBAKU = 5346846;
  static constexpr auto STATUS_PARAM_PARALYSIS = 1230;
  static constexpr auto STATUS_DEATH_CLAW = 609;
  static constexpr auto STATUS_PARAM_DEATH_CLAW = 1039;
  static constexpr auto LOC_ACTOR90 = 5357438;
  static constexpr auto LOC_ACTOR91 = 5357450;
  static constexpr auto LOC_ACTOR92 = 5357449;
  static constexpr auto LOC_ACTOR93 = 5357447;
  static constexpr auto LOC_ACTOR94 = 5357446;
  static constexpr auto LOC_BGM2 = 223;
  static constexpr auto DEF_ACTION_IRONCLAW = 3086;

public:
  TheReasonRoaille() : Sapphire::ScriptAPI::QuestBattleScript( 101 )
  { }

  void onInit( QuestBattle& instance ) override
  {

  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheReasonRoaille );