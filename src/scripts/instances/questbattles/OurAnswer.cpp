#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class OurAnswer : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto BNPC_COMPANION_CNJ_01 = 5911851;
  static constexpr auto BNPC_COMPANION_DRILLEMONT_01 = 5911852;
  static constexpr auto BNPC_COMPANION_BUKA_01 = 5911853;
  static constexpr auto BNPC_ENEMY_FRAY_01 = 5911855;
  static constexpr auto BNPC_ENEMY_PHASE_1_DARK_SPRITE_01 = 5911861;
  static constexpr auto BNPC_ENEMY_PHASE_1_DARK_SPRITE_02 = 5911862;
  static constexpr auto BNPC_ENEMY_PHASE_2_DARK_SPRITE_01 = 5911864;
  static constexpr auto BNPC_ENEMY_PHASE_2_DARK_SPRITE_02 = 5911865;
  static constexpr auto BNPC_ENEMY_PHASE_3_DARK_SPRITE_01 = 5911866;
  static constexpr auto BNPC_ENEMY_PHASE_3_DARK_SPRITE_02 = 5911867;
  static constexpr auto BNPC_ENEMY_PHASE_3_DARK_SPRITE_03 = 5911868;
  static constexpr auto BNPC_ENEMY_PHASE_3_DARK_SPRITE_04 = 5911869;
  static constexpr auto BNPC_ENEMY_FRAY_THOUGHTS_BODY_01 = 5911870;
  static constexpr auto POPTHOUGHTS_BODY_POINT_01 = 5911872;
  static constexpr auto POPTHOUGHTS_BODY_POINT_02 = 5911873;
  static constexpr auto POPTHOUGHTS_BODY_POINT_03 = 5911874;
  static constexpr auto POPTHOUGHTS_BODY_POINT_04 = 5911875;
  static constexpr auto POPTHOUGHTS_BODY_POINT_05 = 5911876;
  static constexpr auto POPTHOUGHTS_BODY_POINT_06 = 5911877;
  static constexpr auto POPTHOUGHTS_BODY_POINT_07 = 5911878;
  static constexpr auto POPTHOUGHTS_BODY_POINT_08 = 5911916;
  static constexpr auto BNPC_ENEMY_DARK_BALL_01 = 5911885;
  static constexpr auto LOGMESSAGE_POP_THOUGHTS_BODY = 3272;
  static constexpr auto CUT_SCENE_01 = 992;
  static constexpr auto CUT_SCENE_02 = 993;
  static constexpr auto BNPC_TOUMEI_ACTION_SELECTED_01 = 5919543;
  static constexpr auto BNPC_TOUMEI_ACTION_SELECTED_02 = 5919547;
  static constexpr auto BNPC_TOUMEI_ACTION_SELECTED_03 = 5919550;
  static constexpr auto BNPC_TOUMEI_ACTION_SELECTED_04 = 5919553;
  static constexpr auto BNPC_TOUMEI_ACTION_SELECTED_05 = 5919554;
  static constexpr auto BNPC_TOUMEI_ACTION_SELECTED_06 = 5919555;
  static constexpr auto BNPC_TOUMEI_ACTION_SELECTED_07 = 5919556;
  static constexpr auto ACTION_GRAVITY_FORCE = 4837;
  static constexpr auto BNPC_TOUMEI_FOLLOW_PLAYER = 5919749;
  static constexpr auto STATUS_KNOCKDOWN = 625;
  static constexpr auto ACTION_DARK_FIREGA = 3791;
  static constexpr auto STATUS_PARAM_FIRE_DAMAGE = 1753;
  static constexpr auto EOBJ_DAMAGE_AREA = 5920750;
  static constexpr auto ACTION_SCRIPT_TRIGGER = 3269;

public:
  OurAnswer() : Sapphire::ScriptAPI::QuestBattleScript( 146 )
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

  void onUpdate( QuestBattle& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( OurAnswer );