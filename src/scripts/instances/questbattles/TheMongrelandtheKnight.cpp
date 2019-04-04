#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class TheMongrelandtheKnight : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto BNPC_MERISI_1ST_01 = 6869391;
  static constexpr auto BNPC_INQUIS_1ST_01 = 6869410;
  static constexpr auto BNPC_INQUIS_1ST_02 = 6869411;
  static constexpr auto BNPC_TEMPLEADER_1ST_01 = 6869413;
  static constexpr auto BNPC_TEMP_LNC_1ST_01 = 6869414;
  static constexpr auto BNPC_TEMP_ARC_1ST_01 = 6869415;
  static constexpr auto BNPC_TEMP_ARC_1ST_02 = 6869416;
  static constexpr auto BNPC_MERISI_2ND_01 = 6869453;
  static constexpr auto P_BNPC_HILDA_1ST_01 = 6869371;
  static constexpr auto P_BNPC_ROSTN_1ST_01 = 6869382;
  static constexpr auto P_BNPC_STEP_1ST_01 = 6869393;
  static constexpr auto P_BNPC_HILDA_2ND_01 = 6869451;
  static constexpr auto P_BNPC_MOSC_2ND_01 = 6869454;
  static constexpr auto P_BNPC_ROSTN_2ND_01 = 6869484;
  static constexpr auto P_BNPC_STEP_2ND_01 = 6869485;
  static constexpr auto BNPC_MERISI_POS = 7010124;
  static constexpr auto BNPC_TOUMEI_SCAPEGOAT = 7010130;
  static constexpr auto WARP_01 = 6869448;
  static constexpr auto BGM_LAST_JOB = 316;
  static constexpr auto LOC_ACTOR0 = 1011895;
  static constexpr auto LOC_ACTOR1 = 1021318;
  static constexpr auto LOC_ACTOR2 = 1021311;
  static constexpr auto LOC_ACTOR3 = 1014579;
  static constexpr auto LOC_ACTOR4 = 1014580;
  static constexpr auto LOC_LQ_SECONDHALF_01 = 6913459;
  static constexpr auto LOC_LQ_SECONDHALF_ADD_01 = 6955064;
  static constexpr auto LOC_LQ_SECONDHALF_MELISIE_01 = 6956268;
  static constexpr auto BNPC_FIRE_BALL = 6969504;
  static constexpr auto EOBJ_FIRE_FLOOR = 6969506;
  static constexpr auto STATUS_FIRE_FLOOR = 3295;
  static constexpr auto PR_FRIEND_MOVE_POS01 = 6969508;
  static constexpr auto PR_FRIEND_MOVE_POS02 = 6969510;
  static constexpr auto ACT_FIRE_FLOOR = 9387;
  static constexpr auto ACT_FLAME_SUMMON = 9389;
  static constexpr auto ACT_TP_DAMAGE = 9390;
  static constexpr auto ACT_FORM_CHANGE = 9393;
  static constexpr auto BNPCSTATE_SCARED = 7;

public:
  TheMongrelandtheKnight() : Sapphire::ScriptAPI::QuestBattleScript( 173 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.registerEObj( "ClanHuntboard", 2005909, 5863338, 4, { 73.908386f, 24.322830f, 22.067520f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_0", 2000608, 5105673, 4, { 84.499992f, 24.124950f, 22.859011f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_1", 2000608, 5048108, 4, { 97.900009f, 24.465071f, -4.244444f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheMongrelandtheKnight );