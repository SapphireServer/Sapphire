#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class ComeRainorShrine : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto EOBJ_TEMPLE_W = 6784229;
  static constexpr auto EOBJ_TEMPLE_S = 6784233;
  static constexpr auto EOBJ_TEMPLE_E = 6784235;
  static constexpr auto EOBJ_TEMPLE_N = 6784236;
  static constexpr auto EOBJ_TEMPLE_W_AFTER = 6784694;
  static constexpr auto EOBJ_TEMPLE_S_AFTER = 6784695;
  static constexpr auto EOBJ_TEMPLE_E_AFTER = 6784696;
  static constexpr auto EOBJ_TEMPLE_N_AFTER = 6784697;
  static constexpr auto P_BNPC_KYOKUHOU_01 = 6783228;
  static constexpr auto EVENT_ACTION_01 = 22;
  static constexpr auto BNPC_HOKORA_TOUMEI_W = 6798139;
  static constexpr auto BNPC_HOKORA_TOUMEI_S = 6798360;
  static constexpr auto BNPC_HOKORA_TOUMEI_E = 6798361;
  static constexpr auto BNPC_HOKORA_TOUMEI_N = 6798362;
  static constexpr auto STATUS_ASTROLOGIAN_COMPOSE_STAR = 837;
  static constexpr auto PR_KYOKUHOU_HOKORA_MOVE_W = 6798151;
  static constexpr auto PR_KYOKUHOU_HOKORA_MOVE_S = 6798363;
  static constexpr auto PR_KYOKUHOU_HOKORA_MOVE_E = 6798364;
  static constexpr auto PR_KYOKUHOU_HOKORA_MOVE_N = 6798365;
  static constexpr auto DEF_ACTION_TORRIGER = 3269;
  static constexpr auto DEF_ACTION_TORRIGER_B = 4777;
  static constexpr auto PR_KYOKUHOU_HOKORA_BATTLE_S_01 = 7002389;
  static constexpr auto PR_KYOKUHOU_HOKORA_BATTLE_S_02 = 6798367;
  static constexpr auto PR_KYOKUHOU_HOKORA_BATTLE_E = 6798372;
  static constexpr auto BNPC_S_BHOOT_01 = 6798368;
  static constexpr auto BNPC_S_BHOOT_02 = 6798369;
  static constexpr auto BNPC_S_BHOOT_03 = 6798370;
  static constexpr auto BNPC_E_KURAGE = 6798373;
  static constexpr auto BNPC_E_BHOOT_01 = 6798374;
  static constexpr auto BNPC_E_BHOOT_02 = 6798375;
  static constexpr auto BNPC_E_STREET_GHOST_01 = 6798377;
  static constexpr auto BNPC_E_STREET_GHOST_02 = 6798378;
  static constexpr auto BNPC_E_STREET_GHOST_03 = 6798379;
  static constexpr auto BNPC_E_STREET_GHOST_04 = 6798380;
  static constexpr auto BNPC_E_STREET_GHOST_05 = 6798381;
  static constexpr auto BNPC_E_STREET_GHOST_06 = 6798382;
  static constexpr auto BNPC_E_STREET_GHOST_07 = 6798383;
  static constexpr auto BNPC_E_STREET_GHOST_08 = 6798385;
  static constexpr auto BNPC_E_STREET_GHOST_09 = 6798386;
  static constexpr auto BNPC_E_STREET_GHOST_10 = 6798387;
  static constexpr auto BNPC_E_STREET_GHOST_11 = 6798388;
  static constexpr auto BNPC_E_STREET_GHOST_12 = 6798389;
  static constexpr auto ER_E_HOKORA_AROUND = 6798390;
  static constexpr auto BNPC_STREET_GHOST = 6878;
  static constexpr auto BNPC_N_STREET_GHOST_01 = 6798394;
  static constexpr auto BNPC_N_STREET_GHOST_02 = 6798395;
  static constexpr auto BNPC_N_STREET_GHOST_03 = 6798396;
  static constexpr auto BNPC_N_STREET_GHOST_04 = 6798397;
  static constexpr auto BNPC_N_STREET_GHOST_05 = 6798398;
  static constexpr auto BNPC_N_STREET_GHOST_06 = 6798399;
  static constexpr auto BNPC_N_STREET_GHOST_07 = 6798400;
  static constexpr auto BNPC_N_STREET_GHOST_08 = 6798401;
  static constexpr auto BNPC_N_STREET_GHOST_09 = 6798402;
  static constexpr auto ER_N_HOKORA_AROUND = 6798421;
  static constexpr auto BNPC_N_BOSS = 6798428;

public:
  ComeRainorShrine() : Sapphire::ScriptAPI::QuestBattleScript( 154 )
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

EXPOSE_SCRIPT( ComeRainorShrine );