#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class Foxfire : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto P_BNPC_KYOKUHOU_01 = 6796961;
  static constexpr auto P_BNPC_LEVELVA_01 = 6796959;
  static constexpr auto P_BNPC_UDOKU_01 = 6796953;
  static constexpr auto P_BNPC_UDOKU_MINI_01 = 6796952;
  static constexpr auto P_BNPC_UDOKU_MINI_02 = 6796954;
  static constexpr auto BNPC_YOUKO_01 = 6796950;
  static constexpr auto BNPC_ZAKO_WAVE01_01 = 6797047;
  static constexpr auto BNPC_ZAKO_WAVE01_02 = 6797048;
  static constexpr auto BNPC_ZAKO_WAVE01_03 = 6797049;
  static constexpr auto BNPC_ZAKO_WAVE01_04 = 6797053;
  static constexpr auto BNPC_ZAKO_WAVE02_01 = 6938916;
  static constexpr auto BNPC_ZAKO_WAVE02_02 = 6938917;
  static constexpr auto BNPC_ZAKO_WAVE02_03 = 6938918;
  static constexpr auto BNPC_ZAKO_WAVE03_01 = 6938922;
  static constexpr auto BNPC_YOUKO_FUNDO_01 = 6939038;
  static constexpr auto BNPC_YOUKO_FUNDO_02 = 6939039;
  static constexpr auto BNPC_YOUKO_FUNDO_03 = 6949956;
  static constexpr auto BNPC_YOUKO_FUNDO_04 = 6949957;
  static constexpr auto BNPC_BOSSADD1_01 = 6949958;
  static constexpr auto BNPC_BOSSADD1_02 = 6949959;
  static constexpr auto BNPC_BOSSADD1_03 = 6949962;
  static constexpr auto ERANGE_01 = 6797270;
  static constexpr auto ERANGE_02 = 6938832;
  static constexpr auto P_BNPC_CITIZEN_P1_01 = 6938731;
  static constexpr auto P_BNPC_CITIZEN_P1_02 = 6938732;
  static constexpr auto SE_WOMAN_SHOUT = 116;
  static constexpr auto QIB_YELL_01 = 5145;
  static constexpr auto QIB_YELL_02 = 5146;
  static constexpr auto QIB_YELL_03 = 5147;
  static constexpr auto QIB_YELL_04 = 5148;
  static constexpr auto QIB_YELL_05 = 5149;
  static constexpr auto QIB_YELL_06 = 5150;
  static constexpr auto QIB_YELL_07 = 5151;
  static constexpr auto QIB_YELL_08 = 5152;
  static constexpr auto PR_PHASE2_YOUKO_WARP = 6938833;
  static constexpr auto PR_PHASE3_YOUKO_WARP = 6938893;
  static constexpr auto PR_PHASE2_5_KYOKUHOU_MOVE01 = 6938962;
  static constexpr auto PR_DEBUG_BOSSBATTLE = 6950271;
  static constexpr auto PR_PHASE2_5_LEVELVA_MOVE01 = 6938963;
  static constexpr auto PR_LEVELVA_MOVE02 = 6950272;
  static constexpr auto ACTION_SCRIPT_TRIGGER = 3269;
  static constexpr auto ACTION_YOUKO_WARP_START = 9267;
  static constexpr auto ACTION_YOUKO_WARP_END = 9268;
  static constexpr auto ACTION_URAMI_LAZER = 9311;
  static constexpr auto ACTION_JOUKA = 9336;
  static constexpr auto ACTION_FINAL_HEAL = 3595;
  static constexpr auto CHANNELING_FUNDO = 1;
  static constexpr auto CHANNELING_URAMI = 5;
  static constexpr auto STATUS_INVINCIBLE = 325;
  static constexpr auto LOG_MSG_01 = 5382;
  static constexpr auto LOG_MSG_02 = 5383;
  static constexpr auto LOG_MSG_03 = 5384;
  static constexpr auto LOG_MSG_04 = 5385;
  static constexpr auto BNPC_YOUKO_URAMI_01 = 6950669;
  static constexpr auto BNPC_YOUKO_URAMI_02 = 6950670;
  static constexpr auto BNPC_BOSSADD2_01 = 6950759;
  static constexpr auto BNPC_BOSSADD2_02 = 6950762;
  static constexpr auto BNPC_BOSSADD2_03 = 6950763;
  static constexpr auto BNPC_YOUKO_KOKORO = 6951562;
  static constexpr auto STATUS_ASTROLOGIAN_COMPOSE_STAR = 837;
  static constexpr auto P_BNPC_YOUKO = 6951650;
  static constexpr auto BNPCSTATE_SPECIAL_IDLE_1 = 68;

public:
  Foxfire() : Sapphire::ScriptAPI::QuestBattleScript( 156 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.registerEObj( "unknown_0", 2000608, 6538194, 4, { -27.571140f, -3.000000f, 46.619968f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_1", 2000608, 6538193, 4, { -28.307659f, 3.999977f, 61.762589f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "ClanHuntboard", 2008655, 6422886, 4, { -31.520060f, 0.076252f, -43.853790f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgbg_w_qic_004_03a", 2002872, 6799085, 4, { -79.087517f, -3.006042f, 41.336670f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgbg_w_qic_004_03a_1", 2002872, 6799087, 4, { -61.668732f, -3.014119f, 84.855003f }, 0.991760f, -1.567030f ); 
    instance.registerEObj( "unknown_2", 2007457, 6611234, 4, { 137.621094f, 14.816470f, 92.484863f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_3", 2007457, 6538193, 4, { -27.894131f, 3.999977f, 61.384491f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_4", 2007457, 6538194, 4, { -28.259020f, -3.000000f, 46.489510f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( Foxfire );