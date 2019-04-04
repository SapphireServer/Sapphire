#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class ReturntotheRift : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto NCUT_01 = 1741;
  static constexpr auto EOBJ_FLOOR_7 = 7247427;
  static constexpr auto EOBJ_FLOOR_8 = 7247428;
  static constexpr auto EOBJ_WARP = 7257027;
  static constexpr auto EOBJ_W1_BARRIER_01 = 7288224;
  static constexpr auto P_BNPC_ALPHA = 7253907;
  static constexpr auto EVENT_RANGE_ENTRY_MID_FLOOR = 7253926;
  static constexpr auto EVENT_RANGE_ENTRY_BOSS_FLOOR = 7253927;
  static constexpr auto P_BNPC_NERO = 7257028;
  static constexpr auto P_BNPC_CID = 7257029;
  static constexpr auto P_BNPC_MIDGARDSORMR = 7257030;
  static constexpr auto P_BNPC_ARMORED_NERO = 7257031;
  static constexpr auto BNPC_W1_LEVELCHECKER_01 = 7288204;
  static constexpr auto BNPC_W1_MAGNAROADER_01 = 7288206;
  static constexpr auto BNPC_W1_MAGNAROADER_02 = 7288207;
  static constexpr auto BNPC_W2_MAGNAROADER_01 = 7288536;
  static constexpr auto BNPC_W2_MAGNAROADER_02 = 7288537;
  static constexpr auto BNPC_W2_MAGNAROADER_03 = 7288538;
  static constexpr auto BNPC_W2_FACE_01 = 7288539;
  static constexpr auto BNPC_W2_FACE_02 = 7288540;
  static constexpr auto BNPC_W2_FACE_03 = 7288541;
  static constexpr auto BNPC_W2_LEVELCHECKER_01 = 7288542;
  static constexpr auto BNPC_W2_LEVELCHECKER_02 = 7288543;
  static constexpr auto BNPC_W2_LEVELCHECKER_03 = 7288544;
  static constexpr auto BNPC_W2_LEVELCHECKER_04 = 7288545;
  static constexpr auto BNPC_W2_LEVELCHECKER_05 = 7288546;
  static constexpr auto BNPC_W2_LEVELCHECKER_06 = 7288547;
  static constexpr auto BNPC_W3_MAGNAROADER_01 = 7288549;
  static constexpr auto BNPC_W3_MAGNAROADER_02 = 7288550;
  static constexpr auto BNPC_W3_MAGNAROADER_03 = 7288551;
  static constexpr auto BNPC_W3_FACE_01 = 7288552;
  static constexpr auto BNPC_W3_FACE_02 = 7288553;
  static constexpr auto BNPC_W3_FACE_03 = 7288554;
  static constexpr auto BNPC_W3_MAGNAROADER_04 = 7288555;
  static constexpr auto BNPC_W3_MAGNAROADER_05 = 7288556;
  static constexpr auto BNPC_W3_MAGNAROADER_06 = 7288557;
  static constexpr auto BNPC_W3_FACE_04 = 7288558;
  static constexpr auto BNPC_W3_FACE_05 = 7288559;
  static constexpr auto BNPC_W3_FACE_06 = 7288560;
  static constexpr auto BNPC_W4_LEVELCHECKER_01 = 7288561;
  static constexpr auto BNPC_W4_LEVELCHECKER_02 = 7288562;
  static constexpr auto BNPC_W4_LEVELCHECKER_03 = 7288563;
  static constexpr auto BNPC_W4_LEVELCHECKER_04 = 7288564;
  static constexpr auto BNPC_W4_LEVELCHECKER_05 = 7288565;
  static constexpr auto BNPC_W4_LEVELCHECKER_06 = 7288566;
  static constexpr auto BNPC_W4_LEVELCHECKER_07 = 7288567;
  static constexpr auto BNPC_W4_LEVELCHECKER_08 = 7288568;
  static constexpr auto BNPC_W4_LEVELCHECKER_09 = 7288569;
  static constexpr auto BNPC_W4_LEVELCHECKER_10 = 7288570;
  static constexpr auto BNPC_BOSS_DADALUMA_01 = 7288571;
  static constexpr auto BNPC_BOSS_AURA_01 = 7288572;
  static constexpr auto BNPC_BOSS_AURA_02 = 7288573;
  static constexpr auto BNPC_BOSS_AURA_03 = 7288574;
  static constexpr auto BNPC_BOSS_AURA_04 = 7288575;
  static constexpr auto POP_RANGE_CID_RETURN = 7257032;
  static constexpr auto POP_RANGE_P01_MOVE_CID_01 = 7284129;
  static constexpr auto POP_RANGE_P01_MOVE_ALPHA_01 = 7284130;
  static constexpr auto POP_RANGE_P01_MOVE_NERO_01 = 7284131;
  static constexpr auto POP_RANGE_P01_MOVE_MIDGARDSORMR_01 = 7284132;
  static constexpr auto EOBJ_CUBE_W1_MAGNAROADER_01 = 7288194;
  static constexpr auto EOBJ_CUBE_W1_MAGNAROADER_02 = 7288195;
  static constexpr auto POP_RANGE_P01_MOVE_BARRIER_RELEASE_01 = 7288199;
  static constexpr auto EOBJ_BARRIER_RELEASE = 7288201;
  static constexpr auto POP_RANGE_P01_MOVE_ALPHA_TRAP_01 = 7288203;
  static constexpr auto EVENT_RANGE_W1_START = 7291771;
  static constexpr auto YELL_NERO_W1_START = 6700;
  static constexpr auto SHARED_GROUP_W1_BARRIER_01 = 7288225;
  static constexpr auto BEHAVIOR_TOOL_OPERATION = 31282;
  static constexpr auto BEHAVIOR_WARP_OPERATION = 31283;
  static constexpr auto BNPC_GIMMICK_01 = 7292508;
  static constexpr auto BEHAVIOR_ALPHA_CAPTURE = 31284;
  static constexpr auto BNPCBASE_LEVEL_CHECKER_A = 8611;
  static constexpr auto BNPCBASE_LEVEL_CHECKER_B = 8612;
  static constexpr auto BEHAVIOR_TOOL_END = 31285;
  static constexpr auto POP_RANGE_P03_MOVE_CID_WARP_01 = 7292535;
  static constexpr auto POP_RANGE_P03_MOVE_NERO_WARP_01 = 7292536;
  static constexpr auto POP_RANGE_P03_MOVE_ALPHA_WARP_01 = 7292537;
  static constexpr auto POP_RANGE_P03_MOVE_MIDGARDSORMR_WARP_01 = 7292538;
  static constexpr auto BEHAVIOR_FADE_OUT = 31286;
  static constexpr auto BEHAVIOR_FADE_IN = 31287;
  static constexpr auto EVENT_ACTION_01 = 24;
  static constexpr auto POP_RANGE_P04_WARP_OUT_01 = 7292539;
  static constexpr auto POP_RANGE_P04_ALPHA_WARP_OUT_01 = 7297659;
  static constexpr auto POP_RANGE_P04_MIDGARDSORMR_WARP_OUT_01 = 7297661;
  static constexpr auto POP_RANGE_P04_NERO_WARP_OUT_01 = 7297662;
  static constexpr auto POP_RANGE_P04_CID_WARP_OUT_01 = 7297664;
  static constexpr auto EVENT_RANGE_AFTER_WARP_START = 7297670;
  static constexpr auto EVENT_RANGE_W2_START = 7297678;
  static constexpr auto POP_RANGE_P04_MOVE_MIDGARDSORMR_01 = 7297707;
  static constexpr auto POP_RANGE_P04_MOVE_ALPHA_01 = 7297710;
  static constexpr auto POP_RANGE_P06_MOVE_ALPHA_01 = 7297713;
  static constexpr auto POP_RANGE_P04_MOVE_NERO_01 = 7297731;
  static constexpr auto POP_RANGE_P04_MOVE_CID_01 = 7297732;
  static constexpr auto BEHAVIOR_W2_BARRIER_START = 31289;
  static constexpr auto BEHAVIOR_W2_BARRIER_END = 31290;
  static constexpr auto EOBJ_CUBE_W2_MAGNAROADER_01 = 7298352;
  static constexpr auto EOBJ_CUBE_W2_MAGNAROADER_02 = 7298354;
  static constexpr auto EOBJ_CUBE_W2_MAGNAROADER_03 = 7298355;
  static constexpr auto EOBJ_CUBE_W2_FACE_01 = 7298356;
  static constexpr auto EOBJ_CUBE_W2_FACE_02 = 7298357;
  static constexpr auto EOBJ_CUBE_W2_FACE_03 = 7298358;
  static constexpr auto EOBJ_CUBE_W3_MAGNAROADER_01 = 7298359;
  static constexpr auto EOBJ_CUBE_W3_MAGNAROADER_02 = 7298360;
  static constexpr auto EOBJ_CUBE_W3_MAGNAROADER_03 = 7298361;
  static constexpr auto EOBJ_CUBE_W3_MAGNAROADER_04 = 7298362;
  static constexpr auto EOBJ_CUBE_W3_MAGNAROADER_05 = 7298363;
  static constexpr auto EOBJ_CUBE_W3_MAGNAROADER_06 = 7298364;
  static constexpr auto EOBJ_CUBE_W3_FACE_01 = 7298365;
  static constexpr auto EOBJ_CUBE_W3_FACE_02 = 7298366;
  static constexpr auto EOBJ_CUBE_W3_FACE_03 = 7298367;
  static constexpr auto EOBJ_CUBE_W3_FACE_04 = 7298368;
  static constexpr auto EOBJ_CUBE_W3_FACE_05 = 7298369;
  static constexpr auto EOBJ_CUBE_W3_FACE_06 = 7298370;
  static constexpr auto BEHAVIOR_W2_BARRIER_BREAK = 31291;
  static constexpr auto BEHAVIOR_CID_PANIC = 31294;
  static constexpr auto ACTION_DISPEL_CARD = 10877;
  static constexpr auto EOBJ_CUBE_W4_MAGNAROADER_01 = 7309473;
  static constexpr auto EOBJ_CUBE_W4_MAGNAROADER_02 = 7309474;
  static constexpr auto EOBJ_CUBE_W4_FACE_01 = 7309475;
  static constexpr auto EOBJ_CUBE_W4_FACE_02 = 7309476;
  static constexpr auto BNPC_W4_MAGNAROADER_01 = 7309480;
  static constexpr auto BNPC_W4_MAGNAROADER_02 = 7309481;
  static constexpr auto BNPC_W4_FACE_01 = 7309482;
  static constexpr auto BNPC_W4_FACE_02 = 7309483;
  static constexpr auto BEHAVIOR_W4_BARRIER_START = 31293;
  static constexpr auto BEHAVIOR_W4_BARRIER_BREAK = 31295;
  static constexpr auto POP_RANGE_P08_MOVE_ALPHA_01 = 7307407;
  static constexpr auto POP_RANGE_P08_MOVE_CID_01 = 7307408;
  static constexpr auto POP_RANGE_P08_MOVE_NERO_01 = 7307409;
  static constexpr auto POP_RANGE_P08_MOVE_MIDGARDSORMR_01 = 7307410;
  static constexpr auto BGM_EMPIRE_BATTLE = 151;
  static constexpr auto POP_RANGE_P09_MOVE_CID_01 = 7309664;
  static constexpr auto POP_RANGE_P09_MOVE_NERO_01 = 7309665;
  static constexpr auto POP_RANGE_P09_MOVE_ALPHA_01 = 7309666;
  static constexpr auto POP_RANGE_P09_MOVE_MIDGARDSORMR_01 = 7309667;
  static constexpr auto YELL_ALPHA_CHIRPING_01 = 6730;
  static constexpr auto EOBJ_TRAP = 7309742;
  static constexpr auto BEHAVIOR_ALPHA_RELEASE = 31305;
  static constexpr auto EOBJ_CUBE_BOSS_DADALUMA = 7285324;
  static constexpr auto LINEVOICE_NERO_0 = 8201044;
  static constexpr auto ACTION_BOOST_SCREW = 10941;
  static constexpr auto ACTION_BOOST_SWINGDOWN = 10942;
  static constexpr auto LOGMESSAGE_CARD = 2916;

public:
  ReturntotheRift() : Sapphire::ScriptAPI::QuestBattleScript( 180 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.registerEObj( "unknown_0", 2007457, 7233046, 4, { 117.389702f, -91.250000f, 286.907013f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "unknown_1", 2007457, 7233051, 4, { 50.875999f, -82.750008f, 230.007004f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "Exit", 2000046, 0, 4, { -74.926453f, -71.750000f, 159.849503f }, 0.991760f, 0.000048f ); 

  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( ReturntotheRift );