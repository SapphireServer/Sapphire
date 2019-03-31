#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class BestServedwithColdSteel : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto P_BNPC_RAUBAHN = 6793472;
  static constexpr auto P_BNPC_ALISAIE = 6793473;
  static constexpr auto P_BNPC_SOUJA_CNJ = 6793474;
  static constexpr auto P_BNPC_FUMETSU_PGL = 6793475;
  static constexpr auto P_BNPC_MNARGO = 6844587;
  static constexpr auto P_BNPC_CONRAD = 6844589;
  static constexpr auto P_BNPC_KAIHOUGUN_SWD = 6844591;
  static constexpr auto P_BNPC_KAIHOUGUN_LNC = 6844592;
  static constexpr auto P_BNPC_KAIHOUGUN_ARC = 6844593;
  static constexpr auto BNPC_GREENWART = 6793476;
  static constexpr auto BNPC_KMACHINE_IRONSPIKE_PTYPE = 6793480;
  static constexpr auto BNPC_EMPIRE_A = 6793483;
  static constexpr auto BNPC_EMPIRE_B = 6793484;
  static constexpr auto BNPC_EMPIRE_C = 6793485;
  static constexpr auto BNPC_EMPIRE_D = 6793486;
  static constexpr auto BNPC_EMPIRE_E = 6843401;
  static constexpr auto BNPC_EMPIRE_G = 6843400;
  static constexpr auto BNPC_TOUMEI_GTAE1 = 6843181;
  static constexpr auto BNPC_TOUMEI_GTAE2 = 6843182;
  static constexpr auto BNPC_TOUMEI_GTAE3 = 6843587;
  static constexpr auto BNPC_TOUMEI_GTAE4 = 6880898;
  static constexpr auto BNPC_TOUMEI_GTAE5 = 6880899;
  static constexpr auto BNPC_TOUMEI_GTAE_PLAYER = 6843630;
  static constexpr auto BNPC_MOVINGBOM = 6844116;
  static constexpr auto BNPC_MANTISMACHINE_01 = 6927847;
  static constexpr auto BNPC_MANTISMACHINE_02 = 6927848;
  static constexpr auto BNPC_MANTISMACHINE_03 = 6927864;
  static constexpr auto BNPC_MANTISMACHINE_04 = 6927865;
  static constexpr auto BNPC_MANTISMACHINE_05 = 6927866;
  static constexpr auto BNPC_MANTISMACHINE_06 = 6927867;
  static constexpr auto BNPC_MANTISMACHINE_07 = 6927871;
  static constexpr auto BNPC_MANTISMACHINE_08 = 6927872;
  static constexpr auto BNPC_MANTISMACHINE_09 = 6927873;
  static constexpr auto BNPC_MANTISMACHINE_10 = 6928393;
  static constexpr auto BNPC_MANTISMACHINE_11 = 6940085;
  static constexpr auto BNPC_MANTISMACHINE_12 = 6940087;
  static constexpr auto BNPC_MANTISMACHINE_13 = 6940089;
  static constexpr auto BNPC_MANTISMACHINE_14 = 6940090;
  static constexpr auto BNPC_MANTISMACHINE_15 = 6940091;
  static constexpr auto BNPC_MANTISMACHINE_16 = 6940092;
  static constexpr auto P_RANGE_MULTIPLE_GTAE1 = 6843358;
  static constexpr auto P_RANGE_MULTIPLE_GTAE2 = 6843359;
  static constexpr auto P_RANGE_MULTIPLE_GTAE3 = 6843581;
  static constexpr auto P_RANGE_MULTIPLE_GTAE4 = 6843582;
  static constexpr auto P_RANGE_MULTIPLE_GTAE5 = 6843583;
  static constexpr auto P_RANGE_MULTIPLE_GTAE6 = 6843585;
  static constexpr auto P_RANGE_MULTIPLE_GTAE7 = 6880872;
  static constexpr auto P_RANGE_MULTIPLE_GTAE8 = 6880870;
  static constexpr auto P_RANGE_MULTIPLE_GTAE9 = 6880887;
  static constexpr auto P_RANGE_MULTIPLE_GTAE10 = 6880888;
  static constexpr auto P_RANGE_MNARGO_MOVE = 6928434;
  static constexpr auto P_RANGE_CONRAD_MOVE = 6928435;
  static constexpr auto P_RANGE_kAIHOUGUN_MOVE_01 = 6928436;
  static constexpr auto P_RANGE_kAIHOUGUN_MOVE_02 = 6928437;
  static constexpr auto P_RANGE_kAIHOUGUN_MOVE_03 = 6928438;
  static constexpr auto PRANGE_GREENWART_MOVE = 6928441;
  static constexpr auto PRANGE_KMACHINE_MOVE = 6928439;
  static constexpr auto PRANGE_EMPIRE_C_MOVE = 6928440;
  static constexpr auto PRANGE_EMPIRE_A_MOVE = 6928443;
  static constexpr auto ACTION_IDLESTATE_TRRIGER = 3269;
  static constexpr auto ACTION_MOVINGBOM = 8119;
  static constexpr auto ACTION_MULTIPLE_GTAE = 8120;
  static constexpr auto ACTION_IMOTAL_FLAME = 8118;
  static constexpr auto ACTION_SELF_DESTRUCT = 9169;
  static constexpr auto BNPC_STATE_EXHAUSTED = 6;
  static constexpr auto BNPC_STATE_NORMAL = 0;
  static constexpr auto BNPC_STATE_SCARED = 123;
  static constexpr auto YELL_RAUBAHN_06 = 4397;
  static constexpr auto YELL_RAUBAHN_07 = 4398;
  static constexpr auto YELL_GREENWART_REACTION = 4399;
  static constexpr auto LINEVOICE_RAUBAHN_06 = 8201320;
  static constexpr auto LINEVOICE_RAUBAHN_07 = 8201321;
  static constexpr auto CHANNELING_MOVINGBOM = 54;
  static constexpr auto BGM_BOSSBATTLE = 165;
  static constexpr auto STATUS_STUN = 2991;
  static constexpr auto LOC_ACTOR_01 = 1018376;
  static constexpr auto LOC_ACTOR_03 = 1018318;
  static constexpr auto LOC_ACTOR_04 = 1019082;
  static constexpr auto LOC_ACTOR_05 = 1019702;
  static constexpr auto LOC_ACTOR_06 = 1019703;
  static constexpr auto LOC_MARKER_01 = 6972307;
  static constexpr auto LOC_IDLE_01 = 34;
  static constexpr auto LOC_ACTION_01 = 1;
  static constexpr auto LOC_FACE_01 = 614;
  static constexpr auto BNPC_TOUMEI_DAMMY_HATE = 7012786;

public:
  BestServedwithColdSteel() : Sapphire::ScriptAPI::QuestBattleScript( 159 )
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

EXPOSE_SCRIPT( BestServedwithColdSteel );