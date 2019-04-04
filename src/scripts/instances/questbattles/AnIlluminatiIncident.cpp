#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class AnIlluminatiIncident : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto BNPC_COMPANION_BRAYFLOX = 5886492;
  static constexpr auto BNPC_COMPANION_ALPHINAUD = 5886496;
  static constexpr auto BNPC_COMPANION_YSHTOLA = 5886497;
  static constexpr auto BNPC_ENEMY_LEADER_GOBLIN_01 = 5886499;
  static constexpr auto BNPC_ENEMY_FIGHTER_GOBLIN_02 = 5886500;
  static constexpr auto BNPC_ENEMY_FIGHTER_GOBLIN_03 = 5886501;
  static constexpr auto BNPC_ENEMY_SNIPER_GOBLIN_04 = 5886502;
  static constexpr auto BNPC_SUMMON_CARBUNCLE = 5886508;
  static constexpr auto BNPC_OBJ_SMALL_BOMB_01 = 5886511;
  static constexpr auto BNPC_OBJ_SMALL_BOMB_02 = 5886512;
  static constexpr auto BNPC_OBJ_SMALL_BOMB_03 = 5886513;
  static constexpr auto BNPC_OBJ_SMALL_BOMB_04 = 5886514;
  static constexpr auto BNPC_OBJ_SMALL_BOMB_05 = 5886515;
  static constexpr auto BNPC_OBJ_SMALL_BOMB_06 = 5886516;
  static constexpr auto BNPC_OBJ_SMALL_BOMB_07 = 5886517;
  static constexpr auto BNPC_OBJ_SMALL_BOMB_08 = 5886518;
  static constexpr auto BNPC_OBJ_SMALL_BOMB_09 = 5886519;
  static constexpr auto BNPC_OBJ_SMALL_BOMB_10 = 5886520;
  static constexpr auto BNPC_OBJ_SMALL_BOMB_11 = 5886521;
  static constexpr auto BNPC_ENEMY_FIGHTER_GOBLIN_05 = 5886545;
  static constexpr auto BNPC_ENEMY_FIGHTER_GOBLIN_06 = 5886547;
  static constexpr auto BNPC_ENEMY_SNIPER_GOBLIN_07 = 5886548;
  static constexpr auto BNPC_ENEMY_SNIPER_GOBLIN_08 = 5886549;
  static constexpr auto BNPC_ENEMY_FIGHTER_GOBLIN_09 = 5886550;
  static constexpr auto BNPC_ENEMY_GLIDER_GOBLIN_10 = 5886551;
  static constexpr auto BNPC_ENEMY_GLIDER_GOBLIN_11 = 5886552;
  static constexpr auto BNPC_ENEMY_FIGHTER_GOBLIN_12 = 5886563;
  static constexpr auto BNPC_ENEMY_SNIPER_GOBLIN_13 = 5886564;
  static constexpr auto BNPC_ENEMY_FIGHTER_GOBLIN_14 = 5886565;
  static constexpr auto BNPC_ENEMY_SNIPER_GOBLIN_15 = 5886566;
  static constexpr auto BNPC_ENEMY_FIGHTER_GOBLIN_16 = 5886568;
  static constexpr auto BNPC_ENEMY_SNIPER_GOBLIN_17 = 5886569;
  static constexpr auto BNPC_ENEMY_GLIDER_GOBLIN_18 = 5886570;
  static constexpr auto BNPC_ENEMY_MACHINE_GOBLIN_19 = 5886571;
  static constexpr auto BNPC_OBJ_BIG_BOMB_01 = 5886573;
  static constexpr auto BNPC_OBJ_BIG_BOMB_02 = 5886578;
  static constexpr auto BNPC_OBJ_BIG_BOMB_03 = 5886582;
  static constexpr auto BNPC_OBJ_BIG_BOMB_04 = 5886583;
  static constexpr auto BNPC_OBJ_BIG_BOMB_05 = 5886585;
  static constexpr auto BNPC_OBJ_BIG_BOMB_06 = 5886587;
  static constexpr auto NPC_YELL_YSHTOLA_01 = 2637;
  static constexpr auto NPC_YELL_YSHTOLA_02 = 2638;
  static constexpr auto NPC_YELL_YSHTOLA_03 = 2639;
  static constexpr auto NPC_YELL_YSHTOLA_04 = 2781;
  static constexpr auto NPC_YELL_YSHTOLA_05 = 2782;
  static constexpr auto ACTION_BOMB_DISPERSAL = 1933;
  static constexpr auto ACTION_YSHTOLA_SPIRITUAL_RAY = 4023;
  static constexpr auto STATUS_PARAM_DEBUFF_YSHTOLA_SPIRITUAL_RAY = 1702;
  static constexpr auto DEF_ACTION_SUMMON_PET_BNPC = 4785;
  static constexpr auto LOC_POS_ACTOR0 = 5919735;
  static constexpr auto LOC_POS_ACTOR1 = 5919743;
  static constexpr auto LOC_POS_ACTOR2 = 5919747;
  static constexpr auto LOC_POS_ACTOR100 = 5919760;
  static constexpr auto LOC_ACTOR0 = 1011887;
  static constexpr auto LOC_ACTOR1 = 1011889;
  static constexpr auto LOC_ACTOR2 = 1012487;
  static constexpr auto LOC_ACTOR3 = 1012488;
  static constexpr auto LOC_ACTOR4 = 1012489;
  static constexpr auto LOC_ACTOR5 = 1012490;
  static constexpr auto LOC_ACTOR6 = 1012491;
  static constexpr auto ACTION_TIMELINE_EVENT_TALK_DEMIHUMAN = 949;
  static constexpr auto ACTION_TIMELINE_EVENT_SIGH = 4229;
  static constexpr auto ACTION_TIMELINE_EMOTE_GROUND_LOOP = 654;
  static constexpr auto LOC_BGM0 = 113;
  static constexpr auto LOC_POS_CAM0 = 5922528;
  static constexpr auto LINE_VOICE_YSHTOLA_002 = 8201093;
  static constexpr auto LINE_VOICE_YSHTOLA_006 = 8201097;
  static constexpr auto LINE_VOICE_YSHTOLA_005 = 8201096;
  static constexpr auto NPC_YELL_YSHTOLA_VOICE_002 = 3485;
  static constexpr auto NPC_YELL_YSHTOLA_VOICE_006 = 3489;
  static constexpr auto NPC_YELL_YSHTOLA_VOICE_005 = 3488;

public:
  AnIlluminatiIncident() : Sapphire::ScriptAPI::QuestBattleScript( 112 )
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

EXPOSE_SCRIPT( AnIlluminatiIncident );