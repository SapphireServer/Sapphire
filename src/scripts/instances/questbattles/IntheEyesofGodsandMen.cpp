#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class IntheEyesofGodsandMen : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_ENPC_01 = 4261248;
  static constexpr auto INIT_P_POP_PASCALERET = 4261257;
  static constexpr auto INIT_POP_1_EXC_01 = 4261259;
  static constexpr auto INIT_POP_ALDLEC = 4261262;
  static constexpr auto INIT_POP_1_CNJ_01 = 4261275;
  static constexpr auto INIT_POP_1_ARC_01 = 4261276;
  static constexpr auto INIT_POP_1_PGL_01 = 4261278;
  static constexpr auto INIT_P_POP_OLSHIFAN = 4261300;
  static constexpr auto INIT_POP_2_PGL_01 = 4261302;
  static constexpr auto INIT_POP_2_LNC_01 = 4261303;
  static constexpr auto INIT_POP_3_DRAGON_01 = 4261305;
  static constexpr auto EVENT_ACTION_01 = 22;
  static constexpr auto INIT_EO_POP_01 = 4285063;
  static constexpr auto LOG_EVENT_QIB_GAIUSB803_01 = 3206;
  static constexpr auto LOG_EVENT_QIB_GAIUSB803_02 = 3208;
  static constexpr auto LOG_EVENT_QIB_GAIUSB803_03 = 3209;
  static constexpr auto YELL_QIB_GIEIM_01 = 1030;
  static constexpr auto YELL_QIB_PASCALERET_02 = 1031;
  static constexpr auto YELL_QIB_GIEIM_03 = 1032;
  static constexpr auto YELL_QIB_ALDLEC_04 = 1033;
  static constexpr auto YELL_QIB_OLSHIFAN_05 = 1034;
  static constexpr auto YELL_QIB_OLSHIFAN_06 = 1371;
  static constexpr auto INIT_POP_3_EXC_01 = 4287236;
  static constexpr auto INIT_POP_3_CNJ_01 = 4287237;
  static constexpr auto POP_RANGE_ALDLEC_01 = 4321748;
  static constexpr auto POP_RANGE_PASCALERET_01 = 4321746;
  static constexpr auto POP_RANGE_OLSHIFAN_01 = 4287139;
  static constexpr auto POP_RANGE_OLSHIFAN_02 = 4321747;
  static constexpr auto POP_RANGE_DRAGON_02 = 4287173;
  static constexpr auto BGM_OLSHIFAN_AFTER_POP = 36;
  static constexpr auto LOC_ACTOR0 = 1007675;
  static constexpr auto LOC_ACTOR1 = 1006902;
  static constexpr auto LOC_ACTOR2 = 1007681;
  static constexpr auto LOC_ACTOR3 = 1007665;
  static constexpr auto LOC_ACTOR4 = 1007666;
  static constexpr auto LOC_ACTOR5 = 1006905;
  static constexpr auto LOC_ACTOR6 = 1006906;
  static constexpr auto LOC_ACTOR7 = 1007699;
  static constexpr auto LOC_POS_ACTOR0 = 4323475;
  static constexpr auto LOC_POS_ACTOR1 = 4323476;
  static constexpr auto LOC_POS_ACTOR2 = 4323477;
  static constexpr auto LOC_POS_ACTOR3 = 4323478;
  static constexpr auto LOC_ACTION1 = 979;
  static constexpr auto LOC_BGM1 = 114;

public:
  IntheEyesofGodsandMen() : Sapphire::ScriptAPI::QuestBattleScript( 60 )
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

EXPOSE_SCRIPT( IntheEyesofGodsandMen );