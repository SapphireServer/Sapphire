#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class TortoiseinTime : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto BNPC_SOROBAN = 7436223;
  static constexpr auto P_BNPC_GENBU = 7436224;
  static constexpr auto BNPC_WATERCYCLONE_01 = 7436225;
  static constexpr auto P_BNPC_TATARU = 7436226;
  static constexpr auto BNPC_WATERCYCLONE_02 = 7436227;
  static constexpr auto BNPC_WATERCYCLONE_03 = 7436228;
  static constexpr auto BNPC_WATERCYCLONE_04 = 7436229;
  static constexpr auto BNPC_WATERCYCLONE_05 = 7436230;
  static constexpr auto BNPC_WATERCYCLONE_06 = 7436231;
  static constexpr auto BNPC_WATERCYCLONE_07 = 7436232;
  static constexpr auto P_BNPC_CARBUNCLE = 7436235;
  static constexpr auto POP_RANGE_MOOTAN_MOVE = 7436236;
  static constexpr auto POP_RANGE_GENBU_BARRIER_MOVE = 7436237;
  static constexpr auto POP_RANGE_SOROBAN_EXECUTE_MOVE = 7436238;
  static constexpr auto POP_RANGE_TATARU_BARRIER_MOVE = 7436239;
  static constexpr auto BNPC_ERUPTION_01 = 7436243;
  static constexpr auto BNPC_ERUPTION_02 = 7436247;
  static constexpr auto BNPC_ERUPTION_03 = 7436248;
  static constexpr auto BNPC_LASER_01 = 7436249;
  static constexpr auto BNPC_LASER_02 = 7436250;
  static constexpr auto BNPC_LASER_03 = 7436251;
  static constexpr auto BNPC_LASER_04 = 7436252;
  static constexpr auto BNPC_SHABON = 7436253;
  static constexpr auto POP_RANGE_LASER_V_01 = 7437734;
  static constexpr auto POP_RANGE_LASER_V_02 = 7437735;
  static constexpr auto POP_RANGE_LASER_V_03 = 7437736;
  static constexpr auto POP_RANGE_LASER_V_04 = 7437737;
  static constexpr auto POP_RANGE_LASER_V_05 = 7437738;
  static constexpr auto POP_RANGE_LASER_V_06 = 7437739;
  static constexpr auto POP_RANGE_LASER_H_01 = 7437740;
  static constexpr auto POP_RANGE_LASER_H_02 = 7437741;
  static constexpr auto POP_RANGE_LASER_H_03 = 7437742;
  static constexpr auto POP_RANGE_LASER_H_04 = 7437743;
  static constexpr auto POP_RANGE_LASER_H_05 = 7437744;
  static constexpr auto POP_RANGE_LASER_H_06 = 7437745;
  static constexpr auto YELL_TATARU_START_01 = 6767;
  static constexpr auto YELL_TATARU_START_02 = 6768;
  static constexpr auto YELL_TATARU_START_03 = 6769;
  static constexpr auto YELL_TATARU_START_04 = 6770;
  static constexpr auto YELL_TATARU_BARRIER_01 = 6771;
  static constexpr auto ACTION_WATER_ERUPTION = 11510;
  static constexpr auto ACTION_TIDAL_WAVE = 11512;
  static constexpr auto ACTION_WATER_CYCLONE_1 = 11514;
  static constexpr auto ACTION_WATER_LASER = 11520;
  static constexpr auto STATUS_PARAM_DAMAGE_DOWN = 3778;
  static constexpr auto STATUS_PARAM_ZUIJU_GENBU = 3766;
  static constexpr auto STATUS_PARAM_ZUIJU_SOROBAN = 3767;
  static constexpr auto ACTION_WATER_CYCLONE_2 = 11554;
  static constexpr auto EOBJ_GENBU_BARRIER = 7447627;
  static constexpr auto ACTION_INV_TIDAL_WAVE = 11513;
  static constexpr auto P_BNPC_HATE = 7450435;
  static constexpr auto STATUS_PARAM_HEAVY = 3808;
  static constexpr auto STATUS_PARAM_SPRINT = 3805;
  static constexpr auto BNPC_BUBBLE_01 = 7494305;
  static constexpr auto BNPC_BUBBLE_02 = 7494312;
  static constexpr auto BNPC_BUBBLE_03 = 7494313;
  static constexpr auto BNPC_BUBBLE_04 = 7494314;
  static constexpr auto YELL_SOROBAN_DYING = 6787;
  static constexpr auto ACTION_SUMMON_BUBBLE = 11710;
  static constexpr auto CHANNELING_WATER = 3;
  static constexpr auto YELL_TATARU_HEAVY = 6789;
  static constexpr auto ACTION_INV_WATER_AE = 11301;
  static constexpr auto BNPCBASE_BUBBLE = 9154;
  static constexpr auto YELL_TATARU_WATER_AE = 6791;
  static constexpr auto STATUS_PARAM_EVENT = 2918;
  static constexpr auto YELL_TATARU_GIMMICK_MISS = 6788;
  static constexpr auto STATUS_KNOCKDOWN = 783;
  static constexpr auto POP_RANGE_TATARU_CHASE = 7509050;
  static constexpr auto YELL_TATARU_AFTER_START_01 = 6792;
  static constexpr auto POP_RANGE_MOOTAN_TURN_MOVE_01 = 7553064;
  static constexpr auto POP_RANGE_MOOTAN_TURN_MOVE_02 = 7553066;
  static constexpr auto POP_RANGE_MOOTAN_TURN_MOVE_03 = 7553067;
  static constexpr auto POP_RANGE_MOOTAN_TURN_MOVE_04 = 7553107;
  static constexpr auto POP_RANGE_MOOTAN_TURN_MOVE_05 = 7553108;
  static constexpr auto POP_RANGE_MOOTAN_TURN_MOVE_06 = 7553136;
  static constexpr auto POP_RANGE_MOOTAN_TURN_MOVE_07 = 7553137;
  static constexpr auto POP_RANGE_TATARU_LOOK_MOVE_01 = 7553076;

public:
  TortoiseinTime() : Sapphire::ScriptAPI::QuestBattleScript( 183 )
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

EXPOSE_SCRIPT( TortoiseinTime );