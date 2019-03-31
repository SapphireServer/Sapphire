#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class DutyandtheBeast : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto BNPC_P1_CURIOUS_01 = 5867394;
  static constexpr auto BNPC_P1_GENSYO_TAMASHII_01 = 5867395;
  static constexpr auto BNPC_P1_GENSYO_TAMASHII_02 = 5867397;
  static constexpr auto BNPC_P1_GENSYO_TAMASHII_03 = 5867398;
  static constexpr auto BNPC_P1_GENSYO_TAMASHII_04 = 5867399;
  static constexpr auto BNPC_P2_GENSYO_TAMASHII_01 = 5867425;
  static constexpr auto BNPC_P2_GENSYO_TAMASHII_02 = 5867426;
  static constexpr auto BNPC_P2_GENSYO_TAMASHII_03 = 5867427;
  static constexpr auto BNPC_P3_GENSYO_TAMASHII_01 = 5867431;
  static constexpr auto BNPC_P3_GENSYO_TAMASHII_02 = 5867432;
  static constexpr auto BNPC_P3_GENSYO_TAMASHII_03 = 5867433;
  static constexpr auto BNPC_P3_GENSYO_IKARI_CHASE_01 = 5867443;
  static constexpr auto BNPC_P3_GENSYO_IKARI_CHASE_02 = 5867442;
  static constexpr auto BNPC_P3_GENSYO_IKARI_CHASE_03 = 5867444;
  static constexpr auto ENPC_P1_BROKEN_01 = 5867445;
  static constexpr auto LOG_MESSAGE_01 = 3608;
  static constexpr auto BGM_BATTLE = 39;
  static constexpr auto LOC_ACTOR1 = 1014672;
  static constexpr auto LOC_ACTOR2 = 1014476;
  static constexpr auto LOC_ACTOR3 = 1014638;
  static constexpr auto LOC_POS1 = 5871798;
  static constexpr auto EVENT_BASE_KNEE_SUFFERING = 936;
  static constexpr auto ACTION_DEPOP_TRIGER = 3269;
  static constexpr auto LOC_ACTOR4 = 1014475;
  static constexpr auto LOC_POS2 = 5911679;
  static constexpr auto EVENT_BASE_GROUND_TIRED = 824;
  static constexpr auto STATUS_PARAM_KNOCK_DOWN = 1414;
  static constexpr auto LOGMESSAGE_RAGE_01 = 3297;

public:
  DutyandtheBeast() : Sapphire::ScriptAPI::QuestBattleScript( 102 )
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

EXPOSE_SCRIPT( DutyandtheBeast );