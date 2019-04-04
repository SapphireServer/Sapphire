#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class SpearheadingInitiatives : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto BNPC_ENEMY_KNIGHT_GLA_01 = 5877179;
  static constexpr auto BNPC_ENEMY_KNIGHT_GLA_02 = 5881584;
  static constexpr auto BNPC_ENEMY_KNIGHT_GLA_03 = 5881585;
  static constexpr auto BNPC_ENEMY_KNIGHT_GLA_04 = 5881586;
  static constexpr auto BNPC_ENEMY_KNIGHT_LAN_01 = 5881580;
  static constexpr auto BNPC_ENEMY_KNIGHT_LAN_02 = 5881581;
  static constexpr auto BNPC_ENEMY_KNIGHT_LAN_03 = 5881582;
  static constexpr auto BNPC_ENEMY_KNIGHT_LAN_04 = 5881583;
  static constexpr auto BNPC_ENEMY_KNIGHT_LEADER = 5881577;
  static constexpr auto BNPC_ENEMY_KNIGHT_CNJ_01 = 5881640;
  static constexpr auto BNPC_COMPANION_LUNA = 5881587;
  static constexpr auto BNPC_COMPANION_SEBASTIAN = 5881588;
  static constexpr auto BNPC_COMPANION_AVAN = 5881589;
  static constexpr auto BNPC_WAY_STOP_01 = 5881591;
  static constexpr auto BNPC_WAY_STOP_02 = 5881592;
  static constexpr auto BNPC_WAY_STOP_03 = 5881593;
  static constexpr auto BNPC_WAY_STOP_04 = 5881594;
  static constexpr auto BNPC_WAY_STOP_05 = 5882011;
  static constexpr auto BNPC_WAY_STOP_06 = 5882015;
  static constexpr auto BNPC_WAY_STOP_07 = 5882018;
  static constexpr auto BNPC_WAY_STOP_08 = 5882022;
  static constexpr auto BNPC_WAY_STOP_09 = 5882026;
  static constexpr auto BNPC_WAY_STOP_10 = 5882226;
  static constexpr auto BNPC_WAY_STOP_11 = 5883637;
  static constexpr auto BNPC_WAY_STOP_12 = 5883639;
  static constexpr auto BNPC_WAY_STOP_13 = 5883646;
  static constexpr auto BNPC_OGRE_01 = 5881763;
  static constexpr auto BNPC_OGRE_02 = 5881764;
  static constexpr auto BNPC_OGRE_03 = 5883276;
  static constexpr auto BNPC_OGRE_04 = 5883279;
  static constexpr auto BNPC_ABIS_01 = 5883269;
  static constexpr auto BNPC_ABIS_02 = 5883270;
  static constexpr auto ACTION_SCRIPT_TRIGGER_JIBAKU = 4731;
  static constexpr auto ACTION_SCRIPT_TRIGGER = 3269;
  static constexpr auto ACTION_CIRCLE_OF_DOOM = 23;
  static constexpr auto CHANNELING_LUNA_KOUSOKU = 42;
  static constexpr auto YELL_QIB_01 = 2622;
  static constexpr auto YELL_QIB_02 = 2623;
  static constexpr auto YELL_QIB_03 = 2624;
  static constexpr auto YELL_QIB_04 = 2625;
  static constexpr auto YELL_QIB_05 = 2626;
  static constexpr auto YELL_QIB_06 = 2627;
  static constexpr auto YELL_QIB_07 = 2628;
  static constexpr auto YELL_QIB_08 = 2629;
  static constexpr auto YELL_QIB_09 = 2630;
  static constexpr auto YELL_QIB_10 = 2631;
  static constexpr auto YELL_QIB_11 = 2632;
  static constexpr auto YELL_QIB_12 = 2633;
  static constexpr auto YELL_QIB_13 = 2634;
  static constexpr auto POP_RANGE_MONSTER_BATTLE_MOVE_01 = 5881758;
  static constexpr auto POP_RANGE_MONSTER_BATTLE_MOVE_02 = 5883272;
  static constexpr auto POP_RANGE_MONSTER_BATTLE_MOVE_03 = 5883281;
  static constexpr auto EVENT_RANGE_START_NCUT_BEFORE_BOSS = 5883703;
  static constexpr auto BNPC_ENEMY_BOSS = 5883726;
  static constexpr auto BNPC_ENEMY_KNIGHT_BOSS_LAN_01 = 5883752;
  static constexpr auto BNPC_ENEMY_KNIGHT_BOSS_LAN_02 = 5883754;
  static constexpr auto BNPC_ENEMY_KNIGHT_BOSS_LAN_03 = 5883756;
  static constexpr auto BNPC_ENEMY_KNIGHT_BOSS_GLA_01 = 5883758;
  static constexpr auto BNPC_ENEMY_KNIGHT_BOSS_GLA_02 = 5883760;
  static constexpr auto BNPC_ENEMY_KNIGHT_BOSS_CNJ_01 = 5883762;
  static constexpr auto BNPC_COMPANION_BOSS_LUNA = 5883781;
  static constexpr auto BNPC_COMPANION_BOSS_SEBASTIAN = 5883782;
  static constexpr auto BNPC_COMPANION_BOSS_AVAN = 5883783;
  static constexpr auto POP_RANGE_PLAYER_START_FOR_BOSS = 5883784;
  static constexpr auto BGM_BOSS_BATTLE = 91;
  static constexpr auto POP_RANGE_REST_MOVE_01 = 5885177;
  static constexpr auto EOBJ_SHOKAN = 5883708;
  static constexpr auto EVENT_ACTION_01 = 3;
  static constexpr auto BNPC_ENEMY_KNIGHT_BOSS_LEADER = 5885849;
  static constexpr auto NCUT_01 = 986;
  static constexpr auto LOC_ACTOR_JANE = 1014691;
  static constexpr auto LOC_ACTOR_QUIMP = 1014685;
  static constexpr auto LOC_ACTOR_LEVE = 1014684;
  static constexpr auto LOC_ACTOR_KNIGHT_L = 1015071;
  static constexpr auto LOC_ACTOR_KNIGHT_01 = 1015196;
  static constexpr auto LOC_ACTOR_KNIGHT_02 = 1014697;
  static constexpr auto LOC_LEVEL_LEVE = 5933335;
  static constexpr auto LOC_LEVEL_QUIMP = 5933337;
  static constexpr auto LOC_LEVEL_JANE = 5933336;
  static constexpr auto LOC_LEVEL_START = 5935466;
  static constexpr auto MOT_EVENT_LOOK_WEAPON = 1064;
  static constexpr auto LOC_BGM0 = 117;
  static constexpr auto LOC_LEVEL_MOG = 5935584;

public:
  SpearheadingInitiatives() : Sapphire::ScriptAPI::QuestBattleScript( 119 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.registerEObj( "sgbg_w_qic_001_04a", 2006993, 6235274, 4, { -35.822102f, 298.899994f, -205.263199f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_0", 2006952, 0, 4, { -35.712589f, 298.899994f, -204.878006f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 556.049377f, 348.102509f, -752.435730f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Entrance", 2000182, 4600289, 5, { 523.532471f, 348.223389f, -736.685730f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "unknown_1", 2002332, 0, 4, { 533.090881f, 348.691895f, -742.750916f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_2", 2002333, 0, 4, { 539.940430f, 348.836395f, -734.401489f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_3", 2000608, 3967803, 4, { 202.369598f, 257.761108f, 80.435272f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_4", 2000608, 3976993, 4, { 273.634705f, 254.600204f, 106.048500f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_5", 2000608, 3986797, 4, { 205.504898f, 246.188995f, 194.875702f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_6", 2000608, 3986798, 4, { 326.313385f, 239.193497f, 221.138901f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_7", 2000608, 2718481, 4, { 240.552307f, 302.769714f, -199.979996f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_8", 2000608, 4065433, 4, { 204.970001f, 302.119995f, -216.311600f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_9", 2000608, 2814617, 4, { 205.869995f, 302.219086f, -276.681396f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_10", 2000608, 2763112, 4, { -433.000000f, 211.007706f, -216.148605f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_11", 2000608, 4187649, 4, { -453.000000f, 211.000000f, -281.046600f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_12", 2000608, 4187961, 4, { -416.000000f, 210.788193f, -279.813812f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( SpearheadingInitiatives );