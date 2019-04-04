#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class IntotheDragonsMaw : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_POP_1_ESTINIAN_01 = 4287051;
  static constexpr auto INIT_POP_2_DRGON_HEART_01 = 4287059;
  static constexpr auto INIT_POP_3_DRAGON_POWER_02 = 4287079;
  static constexpr auto INIT_POP_3_DRAGON_POWER_03 = 4287082;
  static constexpr auto INIT_POP_3_DRAGON_POWER_04 = 4287083;
  static constexpr auto INIT_POP_3_DRAGON_POWER_05 = 4287085;
  static constexpr auto INIT_POP_3_DRAGON_POWER_06 = 4287086;
  static constexpr auto INIT_POP_3_DRAGON_POWER_07 = 4287087;
  static constexpr auto INIT_ENPC_POP_ALBERIC = 4287046;
  static constexpr auto LOG_EVENT_QIB_JOBDRG500_01 = 3207;
  static constexpr auto LOG_EVENT_QIB_JOBDRG500_02 = 3220;
  static constexpr auto LOG_EVENT_QIB_JOBDRG500_03 = 3213;
  static constexpr auto LOG_EVENT_QIB_JOBDRG500_04 = 3221;
  static constexpr auto STATUS_CUSTOM_DRAGON_EYE_POWER = 698;
  static constexpr auto DEF_ACTION_DRAGON_BLESS = 1063;
  static constexpr auto DEF_ACTION_DRAGON_DIVE = 1064;
  static constexpr auto EOBJ_DAMAGE_RANGE_FIRE = 4313761;
  static constexpr auto STATUS_CUSTOM_DAMAGE_RANGE_FIRE = 677;
  static constexpr auto CUT_START_NCUT = 336;
  static constexpr auto CUT_END_NCUT = 337;
  static constexpr auto JOB_STORY_MES = 3636;

public:
  IntotheDragonsMaw() : Sapphire::ScriptAPI::QuestBattleScript( 72 )
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

EXPOSE_SCRIPT( IntotheDragonsMaw );