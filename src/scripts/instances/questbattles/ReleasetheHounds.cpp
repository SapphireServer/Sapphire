#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class ReleasetheHounds : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto BNPC_BOSS_01 = 6866621;
  static constexpr auto P_BNPC_HILDA_01 = 6866710;
  static constexpr auto P_BNPC_ROSTN_01 = 6866702;
  static constexpr auto P_BNPC_SYM_01 = 6866725;
  static constexpr auto P_BNPC_EUDES_01 = 6866789;
  static constexpr auto P_BNPC_GUNMAN_01 = 6866791;
  static constexpr auto P_BNPC_GUNMAN_02 = 6866792;
  static constexpr auto EOBJ_SWORD_01 = 6870137;
  static constexpr auto BNPC_ZAKO_AXE_01 = 6952176;
  static constexpr auto BNPC_ZAKO_AXE_02 = 6952183;
  static constexpr auto BNPC_ZAKO_AXE_03 = 6952185;
  static constexpr auto BNPC_ZAKO_AXE_04 = 6952186;
  static constexpr auto BNPC_ZAKO_AXE_05 = 6952187;
  static constexpr auto BNPC_ZAKO_GUN_01 = 6952192;
  static constexpr auto BNPC_ZAKO_GUN_02 = 6952205;
  static constexpr auto BNPC_ZAKO_GUN_03 = 6952207;
  static constexpr auto BNPC_ZAKO_GUN_04 = 6952210;
  static constexpr auto BNPC_ZAKO_GUN_05 = 6952218;
  static constexpr auto BNPC_ZAKO_GUN_06 = 6952224;
  static constexpr auto BNPC_ZAKO_GUN_07 = 6952228;
  static constexpr auto BNPC_ZAKO_GUN_08 = 6952447;
  static constexpr auto BNPC_COEURL = 6952234;
  static constexpr auto BNPC_CHAIN_BIND = 6952238;
  static constexpr auto PR_COUEURL_MOVE_POS = 6952450;
  static constexpr auto PR_ZAKO_MOVE_POS = 6952466;
  static constexpr auto PR_ESC_MOVE_POS = 6952556;
  static constexpr auto PR_FRIEND_MOVE_POS01 = 6955073;
  static constexpr auto PR_FRIEND_MOVE_POS02 = 6955074;
  static constexpr auto PR_FRIEND_MOVE_POS03 = 6955075;
  static constexpr auto PR_FRIEND_MOVE_POS04 = 6955076;
  static constexpr auto CHANNELING_CHAIN = 31;

public:
  ReleasetheHounds() : Sapphire::ScriptAPI::QuestBattleScript( 172 )
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

EXPOSE_SCRIPT( ReleasetheHounds );