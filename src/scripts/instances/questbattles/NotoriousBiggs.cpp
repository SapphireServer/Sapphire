#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class NotoriousBiggs : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_P_POP_01 = 4264062;
  static constexpr auto INIT_P_POP_02 = 4264069;
  static constexpr auto INIT_P_POP_03 = 4264070;
  static constexpr auto INIT_POP_1ST_01 = 4264130;
  static constexpr auto INIT_POP_1ST_02 = 4264135;
  static constexpr auto INIT_POP_1ST_03 = 4264138;
  static constexpr auto INIT_POP_1ST_04 = 4264140;
  static constexpr auto INIT_POP_2ST_01 = 4264377;
  static constexpr auto INIT_POP_2ST_02 = 4264378;
  static constexpr auto INIT_POP_2ST_03 = 4264380;
  static constexpr auto INIT_POP_2ST_04 = 4264381;
  static constexpr auto INIT_POP_2ST_05 = 4264382;
  static constexpr auto INIT_POP_2ST_06 = 4264384;
  static constexpr auto INIT_POP_3ST_01 = 4264403;
  static constexpr auto INIT_POP_3ST_02 = 4264404;
  static constexpr auto INIT_POP_3ST_03 = 4264406;
  static constexpr auto INIT_POP_3ST_04 = 4264407;
  static constexpr auto INIT_POP_3ST_05 = 4264408;
  static constexpr auto INIT_POP_3ST_06 = 4264411;
  static constexpr auto INIT_POP_3ST_07 = 4264412;
  static constexpr auto POP_RANGE_ENEMY_MOVE_01 = 4268836;
  static constexpr auto YELL_QIB_02 = 1530;
  static constexpr auto LOC_ACTOR0 = 1003837;
  static constexpr auto LOC_ACTOR1 = 1007628;
  static constexpr auto LOC_ACTOR2 = 1007001;
  static constexpr auto LOC_ACTOR3 = 1002275;
  static constexpr auto LOC_ACTOR4 = 1003782;
  static constexpr auto LOC_ACTOR5 = 1007622;
  static constexpr auto LOC_ACTOR6 = 1007623;
  static constexpr auto LOC_ACTOR7 = 1007624;
  static constexpr auto LOC_MARKER_01 = 4323173;
  static constexpr auto LOC_MARKER_02 = 4323176;
  static constexpr auto LOC_MARKER_03 = 4323178;
  static constexpr auto LOC_ACTION0 = 34;
  static constexpr auto LOC_ACTION1 = 934;
  static constexpr auto LOC_ACTION2 = 936;
  static constexpr auto LOC_ACTION3 = 1005;
  static constexpr auto LOC_BGM0 = 83;
  static constexpr auto LOC_BGM1 = 113;

public:
  NotoriousBiggs() : Sapphire::ScriptAPI::QuestBattleScript( 62 )
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

EXPOSE_SCRIPT( NotoriousBiggs );