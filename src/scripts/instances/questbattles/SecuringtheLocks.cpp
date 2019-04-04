#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class SecuringtheLocks : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto BNPC_STEPHANIVIEN_01 = 5901097;
  static constexpr auto BNPC_JOYE_01 = 5901098;
  static constexpr auto BNPC_GROUP_A_BALLISTA_01 = 5901106;
  static constexpr auto BNPC_GROUP_A_HAILLENARTE_SWORD_01 = 5901107;
  static constexpr auto BNPC_GROUP_A_HAILLENARTE_SPEAR_01 = 5901108;
  static constexpr auto BNPC_GROUP_A_HAILLENARTE_SPEAR_02 = 5901109;
  static constexpr auto BNPC_GROUP_A_HAILLENARTE_GUARD_01 = 5901110;
  static constexpr auto BNPC_GROUP_B_BALLISTA_01 = 5901116;
  static constexpr auto BNPC_GROUP_B_HAILLENARTE_SWORD_01 = 5901117;
  static constexpr auto BNPC_GROUP_B_HAILLENARTE_SPEAR_01 = 5901118;
  static constexpr auto BNPC_GROUP_B_HAILLENARTE_SPEAR_02 = 5901119;
  static constexpr auto BNPC_GROUP_B_HAILLENARTE_GUARD_01 = 5901120;
  static constexpr auto BNPC_GROUP_C_BALLISTA_01 = 5901121;
  static constexpr auto BNPC_GROUP_C_HAILLENARTE_SWORD_01 = 5901122;
  static constexpr auto BNPC_GROUP_C_HAILLENARTE_SPEAR_01 = 5901123;
  static constexpr auto BNPC_GROUP_C_HAILLENARTE_SPEAR_02 = 5901124;
  static constexpr auto BNPC_GROUP_C_HAILLENARTE_GUARD_01 = 5901125;
  static constexpr auto BNPC_PACK_A_WYVERN_01 = 5901132;
  static constexpr auto BNPC_PACK_A_THRUSTAEVIS_01 = 5901135;
  static constexpr auto BNPC_PACK_A_THRUSTAEVIS_02 = 5901136;
  static constexpr auto BNPC_PACK_B_WYVERN_01 = 5901137;
  static constexpr auto BNPC_PACK_B_DRAGONFLY_01 = 5901138;
  static constexpr auto BNPC_PACK_B_THRUSTAEVIS_01 = 5901139;
  static constexpr auto BNPC_PACK_C_WYVERN_01 = 5901140;
  static constexpr auto BNPC_PACK_C_DRAGONFLY_01 = 5901141;
  static constexpr auto BNPC_PACK_C_DRAGONFLY_02 = 5901142;
  static constexpr auto BNPC_PACK_D_WYVERN_01 = 5901143;
  static constexpr auto BNPC_PACK_D_WYVERN_02 = 5901144;
  static constexpr auto BNPC_PACK_D_WYVERN_03 = 5901145;
  static constexpr auto BNPC_PACK_D_DRAGONFLY_01 = 5901146;
  static constexpr auto BNPC_PACK_D_DRAGONFLY_02 = 5901147;
  static constexpr auto BNPC_PACK_E_WYVERN_01 = 5901148;
  static constexpr auto BNPC_PACK_E_WYVERN_02 = 5901149;
  static constexpr auto BNPC_PACK_E_DRAGONFLY_01 = 5901150;
  static constexpr auto BNPC_PACK_E_DRAGONFLY_02 = 5901151;
  static constexpr auto BNPC_PACK_F_WYVERN_01 = 5901154;
  static constexpr auto BNPC_PACK_F_THRUSTAEVIS_01 = 5901155;
  static constexpr auto BNPC_PACK_G_WYVERN_01 = 5901159;
  static constexpr auto BNPC_PACK_G_WYVERN_02 = 5901160;
  static constexpr auto BNPC_PACK_G_DRAGONFLY_01 = 5901161;
  static constexpr auto BNPC_PACK_G_DRAGONFLY_02 = 5901162;
  static constexpr auto BNPC_PACK_G_THRUSTAEVIS_01 = 5901163;
  static constexpr auto BNPC_SVARA_01 = 5901165;
  static constexpr auto LOGMESSAGE_A_BALLISTA_HP50 = 3266;
  static constexpr auto LOGMESSAGE_A_BALLISTA_HP25 = 3267;
  static constexpr auto LOGMESSAGE_B_BALLISTA_HP50 = 3264;
  static constexpr auto LOGMESSAGE_B_BALLISTA_HP25 = 3265;
  static constexpr auto LOGMESSAGE_C_BALLISTA_HP50 = 3268;
  static constexpr auto LOGMESSAGE_C_BALLISTA_HP25 = 3269;
  static constexpr auto LOGMESSAGE_A_BALLISTA_BREAK_DOWN = 3263;
  static constexpr auto LOGMESSAGE_B_BALLISTA_BREAK_DOWN = 3262;
  static constexpr auto LOGMESSAGE_C_BALLISTA_BREAK_DOWN = 3273;
  static constexpr auto LOC_MARKER_01 = 5925683;
  static constexpr auto LOC_MARKER_02 = 5925684;
  static constexpr auto LOC_MARKER_03 = 5925690;
  static constexpr auto LOC_MARKER_04 = 5925691;
  static constexpr auto LOC_ACTOR0 = 1014579;
  static constexpr auto LOC_ACTOR1 = 1015124;
  static constexpr auto LOC_ACTOR2 = 1014971;
  static constexpr auto LOC_ACTOR3 = 1014972;
  static constexpr auto LOC_ACTOR4 = 1014973;
  static constexpr auto LOC_BGM0 = 316;

public:
  SecuringtheLocks() : Sapphire::ScriptAPI::QuestBattleScript( 128 )
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

EXPOSE_SCRIPT( SecuringtheLocks );