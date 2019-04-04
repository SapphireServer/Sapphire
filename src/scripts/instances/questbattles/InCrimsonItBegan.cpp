#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class InCrimsonItBegan : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_WARP_POINT_001 = 6842088;
  static constexpr auto CUT_SCENE_01 = 1394;
  static constexpr auto P_BNPC_ALPHINAUD = 6828499;
  static constexpr auto P_BNPC_CARBUNCLE = 6828504;
  static constexpr auto P_BNPC_PIPIN = 6828509;
  static constexpr auto P_BNPC_ALISAIE = 6828511;
  static constexpr auto P_BNPC_KRILE = 6828515;
  static constexpr auto BNPC_EMPIER_PHASE1_THM1 = 6889827;
  static constexpr auto BNPC_EMPIER_PHASE1_THM2 = 6889828;
  static constexpr auto BNPC_EMPIER_PHASE1_EXC1 = 6889829;
  static constexpr auto BNPC_EMPIER_PHASE1_EXC2 = 6889831;
  static constexpr auto BNPC_EMPIER_PHASE1_PGL1 = 6889830;
  static constexpr auto P_BNPC_PHASE1_HOSTAGE1 = 6889837;
  static constexpr auto P_BNPC_PHASE1_HOSTAGE2 = 6889836;
  static constexpr auto P_BNPC_PHASE1_HOSTAGE3 = 6889838;
  static constexpr auto PRANGE_PHASE1_HOSTAGE1 = 6889840;
  static constexpr auto PRANGE_PHASE1_HOSTAGE2 = 6889841;
  static constexpr auto PRANGE_PHASE1_HOSTAGE3 = 6889842;
  static constexpr auto ERANGE_PHASE1 = 6889834;
  static constexpr auto ERANGE_PHASE2 = 6890073;
  static constexpr auto ERANGE_PHASE3 = 6890276;
  static constexpr auto P_BNPC_PHASE2_HOSTAGE1 = 6890159;
  static constexpr auto P_BNPC_PHASE2_HOSTAGE2 = 6890160;
  static constexpr auto P_BNPC_KAIHOUGUN_PHASE2_SWD1 = 6890173;
  static constexpr auto P_BNPC_KAIHOUGUN_PHASE2_EXC1 = 6890181;
  static constexpr auto BNPC_EMPIER_PHASE2_EXC1 = 6890206;
  static constexpr auto BNPC_EMPIER_PHASE2_PGL1 = 6890188;
  static constexpr auto BNPC_EMPIER_PHASE2_THM1 = 6890189;
  static constexpr auto BNPC_EMPIER_PHASE2_THM2 = 6890191;
  static constexpr auto BNPC_EMPIER_PHASE2_MACHINE1 = 6890192;
  static constexpr auto BNPC_EMPIER_PHASE2_MACHINE2 = 6890201;
  static constexpr auto P_BNPC_PHASE3_HOSTAGE1 = 6890300;
  static constexpr auto P_BNPC_PHASE3_HOSTAGE2 = 6890305;
  static constexpr auto P_BNPC_KAIHOUGUN_PHASE3_SWD1 = 6890306;
  static constexpr auto P_BNPC_KAIHOUGUN_PHASE3_EXC1 = 6890307;
  static constexpr auto BNPC_EMPIER_PHASE3_EXC1 = 6890318;
  static constexpr auto BNPC_EMPIER_PHASE3_PGL1 = 6890309;
  static constexpr auto BNPC_WOLFMAN_PHASE3_SAM1 = 6890320;
  static constexpr auto BNPC_WOLFMAN_PHASE3_LNC1 = 6890321;
  static constexpr auto BNPC_WOLFMAN_PHASE3_ARC1 = 6890322;
  static constexpr auto BNPC_WOLFMAN_PHASE3_ARC2 = 6890327;
  static constexpr auto EOBJ_BOSS_ROOM_CONTROL = 6890473;
  static constexpr auto ERANGE_PHASE4 = 6890642;
  static constexpr auto BNPC_SKULL_FORCE_PHASE4_FORDLA = 6828565;
  static constexpr auto BNPC_SKULL_FORCE_PHASE4_THM1 = 6890671;
  static constexpr auto BNPC_SKULL_FORCE_PHASE4_THM2 = 6890672;
  static constexpr auto BNPC_SKULL_FORCE_PHASE4_SWD1 = 6890673;
  static constexpr auto BNPC_SKULL_FORCE_PHASE4_LNC1 = 6890674;
  static constexpr auto BNPC_ZENOS = 6828566;
  static constexpr auto BNPC_STATE_EXHAUSTED = 6;
  static constexpr auto BNPC_STATE_SCARE = 7;
  static constexpr auto BNPC_STATE_ACTIVE = 1;
  static constexpr auto BNPC_STATE_ATTRIBUTE_CHANGE_A1_B1_C0_KEEP = 139;
  static constexpr auto BEHAVIOR_HOSTAGE_PHASE1 = 30936;
  static constexpr auto BEHAVIOR_ALPHINAUD_PHASE1 = 30937;
  static constexpr auto PRANGE_PHASE1_ALPHINAUD1 = 6891799;
  static constexpr auto PRANGE_PHASE2_KAIHOUGUN_EXC = 6892443;
  static constexpr auto PRANGE_PHASE2_KAIHOUGUN_SWD = 6892444;
  static constexpr auto PRANGE_PHASE1_ALISAIE1 = 6892447;
  static constexpr auto BEHAVIOR_PIPIN_PHASE1 = 30938;
  static constexpr auto BEHAVIOR_KRILE_PHASE1 = 30939;
  static constexpr auto YELL_KRILE_01 = 4789;
  static constexpr auto YELL_PIPIN_01 = 4790;
  static constexpr auto YELL_HOSTAGE_04 = 4792;
  static constexpr auto YELL_HOSTAGE_05 = 4793;
  static constexpr auto YELL_HOSTAGE_06 = 4794;
  static constexpr auto YELL_KAIHOUGUN_01 = 4799;
  static constexpr auto YELL_KAIHOUGUN_02 = 4800;
  static constexpr auto YELL_ALPHINAUD_02 = 4801;
  static constexpr auto YELL_WOLFMAN_01 = 4802;
  static constexpr auto YELL_WOLFMAN_02 = 4803;
  static constexpr auto YELL_FORDOLA_03 = 4791;
  static constexpr auto STATUS_KNOCKDOWN_ETERNAL = 3000;
  static constexpr auto STATUS_KNOCKDOWN = 3001;
  static constexpr auto STATUS_STUN = 2991;
  static constexpr auto STATUS_TERROR = 3331;
  static constexpr auto PRANGE_HOSTAGE_DEPOP = 6828473;
  static constexpr auto BNPC_TOUMEI_HOCK_NPCDEAD = 6894431;
  static constexpr auto P_BNPC_PIPIN_SECOND = 6842091;
  static constexpr auto P_BNPC_ALISAIE_SECOND = 6842089;
  static constexpr auto BNPC_FUJINKEN = 6895494;
  static constexpr auto BNPC_RAIJINKEN_01 = 6895495;
  static constexpr auto BNPC_RAIJINKEN_02 = 6940216;
  static constexpr auto BNPC_RAIJINKEN_03 = 6940214;
  static constexpr auto BNPC_RAIJINKEN_04 = 6940227;
  static constexpr auto BNPC_RAIJINKEN_05 = 6940210;
  static constexpr auto BNPC_RAIJINKEN_06 = 6940230;
  static constexpr auto BNPC_RAIJINKEN_07 = 6940212;
  static constexpr auto BNPC_RAIJINKEN_08 = 6940226;
  static constexpr auto BNPC_RAIJINKEN_09 = 6940235;
  static constexpr auto BNPC_RAIJINKEN_10 = 6940237;
  static constexpr auto BNPC_RAIJINKEN_11 = 6940236;
  static constexpr auto BNPC_RAIJINKEN_12 = 6940238;
  static constexpr auto ENPC_ALPINAUD = 6971433;
  static constexpr auto ENPC_KRILE = 6971434;
  static constexpr auto ACTION_RAIDDAMAGE_PHASE1 = 8693;
  static constexpr auto ACTION_HATE_RESETED = 3269;
  static constexpr auto LINEVOICE_FORDOLA_03 = 8201359;
  static constexpr auto LINEVOICE_PIPIN_03 = 8201328;
  static constexpr auto BGM_ZENOS_BATTLE = 207;

public:
  InCrimsonItBegan() : Sapphire::ScriptAPI::QuestBattleScript( 155 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.registerEObj( "ClanHuntboard", 2008654, 0, 4, { 95.105537f, 0.652042f, 22.605730f }, 1.000000f, -1.231116f ); 

  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( InCrimsonItBegan );