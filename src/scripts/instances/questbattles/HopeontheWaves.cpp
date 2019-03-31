#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class HopeontheWaves : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto WARP_01 = 7186209;
  static constexpr auto NCUT_01 = 1676;
  static constexpr auto NCUT_02 = 1677;
  static constexpr auto P_BNPC_PIRATE_01 = 7288485;
  static constexpr auto P_BNPC_PIRATE_02 = 7288494;
  static constexpr auto P_BNPC_PIRATE_03 = 7288495;
  static constexpr auto P_BNPC_PIRATE_04 = 7288497;
  static constexpr auto P_BNPC_PIRATE_05 = 7288498;
  static constexpr auto P_BNPC_ALPHINAUD = 7288500;
  static constexpr auto P_BNPC_CARBUNCLE_WHITE = 7288502;
  static constexpr auto P_BNPC_YUGIRI = 7288507;
  static constexpr auto P_BNPC_TANSUI = 7288519;
  static constexpr auto BNPC_ENEMY_EMPIRE_SPEAR_01 = 7288522;
  static constexpr auto BNPC_ENEMY_EMPIRE_SPEAR_02 = 7288525;
  static constexpr auto BNPC_ENEMY_EMPIRE_SPEAR_03 = 7288526;
  static constexpr auto BNPC_ENEMY_EMPIRE_SPEAR_04 = 7288527;
  static constexpr auto BNPC_ENEMY_EMPIRE_SPEAR_05 = 7288528;
  static constexpr auto BNPC_ENEMY_EMPIRE_CONJ_01 = 7288529;
  static constexpr auto BNPC_ENEMY_EMPIRE_CONJ_02 = 7288530;
  static constexpr auto BNPC_ENEMY_EMPIRE_CONJ_03 = 7288531;
  static constexpr auto BNPC_ENEMY_EMPIRE_CONJ_04 = 7288532;
  static constexpr auto BNPC_ENEMY_EMPIRE_SWORD_01 = 7288533;
  static constexpr auto BNPC_ENEMY_EMPIRE_SWORD_02 = 7288534;
  static constexpr auto BNPC_KMACHINE_IRONSPIKE = 7288535;
  static constexpr auto PR_TANSUI_MOVE_POS = 7288548;
  static constexpr auto PR_PIRATE_MOVE_POS = 7292066;
  static constexpr auto PR_PIRATE_MOVE_POS2 = 7315871;
  static constexpr auto EOBJ_SHARED_CONTROL = 7295786;
  static constexpr auto EVENT_RANGE_NEXT_CUT = 7291574;
  static constexpr auto P_BNPC_ALPHINAUD_2 = 7292138;
  static constexpr auto P_BNPC_CARBUNCLE_WHITE_2 = 7292140;
  static constexpr auto P_BNPC_YUGIRI_2 = 7292141;
  static constexpr auto P_BNPC_TANSUI_2 = 7292143;
  static constexpr auto P_BNPC_YUGIRI_AVATAR01 = 7307562;
  static constexpr auto P_BNPC_YUGIRI_AVATAR02 = 7307565;
  static constexpr auto BNPC_ENEMY_EMPIRE_LEADER = 7292111;
  static constexpr auto BNPC_ENEMY_EMPIRE_SPEAR_06 = 7292072;
  static constexpr auto BNPC_ENEMY_EMPIRE_SPEAR_07 = 7292100;
  static constexpr auto BNPC_ENEMY_EMPIRE_CONJ_05 = 7292073;
  static constexpr auto BNPC_ENEMY_EMPIRE_CONJ_06 = 7292101;
  static constexpr auto BNPC_ENEMY_EMPIRE_SWORD_03 = 7292079;
  static constexpr auto BNPC_ENEMY_EMPIRE_SWORD_04 = 7292102;
  static constexpr auto BNPC_KMACHINE_IRONSPIKE_01 = 7292118;
  static constexpr auto BNPC_KMACHINE_IRONSPIKE_02 = 7292121;
  static constexpr auto BNPC_KMACHINE_IRONSPIKE_03 = 7292124;
  static constexpr auto BNPC_KMACHINE_IRONSPIKE_04 = 7292125;
  static constexpr auto BNPC_MACHINE_WHEELED = 7292132;
  static constexpr auto BNPC_TOUMEI_ACTION_LB = 7292152;
  static constexpr auto BNPC_TOUMEI_ACTION_DIST = 7292160;
  static constexpr auto BNPC_MACHINE_BIT_01 = 7292516;
  static constexpr auto BNPC_MACHINE_BIT_02 = 7292517;
  static constexpr auto BNPC_MACHINE_BIT_03 = 7292518;
  static constexpr auto BNPC_MACHINE_BIT_04 = 7292519;
  static constexpr auto BNPC_MACHINE_BIT_BOM_01 = 7292524;
  static constexpr auto BNPC_MACHINE_BIT_BOM_02 = 7292524;
  static constexpr auto BNPC_MACHINE_BIT_BOM_03 = 7292524;
  static constexpr auto BNPC_MACHINE_BIT_BOM_04 = 7292524;
  static constexpr auto BNPC_MACHINE_BIT_BOM_05 = 7292524;
  static constexpr auto BNPC_MACHINE_BIT_BOM_06 = 7292524;
  static constexpr auto BNPC_TOUMEI_POS01 = 7292520;
  static constexpr auto BNPC_TOUMEI_POS02 = 7292521;
  static constexpr auto BNPC_TOUMEI_POS03 = 7292136;
  static constexpr auto P_BNPC_GOSETSU = 7309542;
  static constexpr auto P_BNPC_YOTSUYU = 7309544;
  static constexpr auto PR_MACHINE_BIT_BOM_POS01 = 7292522;
  static constexpr auto ACTION_DIST_MISSILE = 10816;
  static constexpr auto ACTION_TOUMEI_DIST_MISSILE = 10893;
  static constexpr auto ACTION_KMACHINE_SUICIDE = 10928;
  static constexpr auto ACTION_SLOW_AREA = 10892;
  static constexpr auto ACTION_BLIND = 3206;
  static constexpr auto ACTION_LB = 10894;
  static constexpr auto ACTION_SUMMON = 9158;
  static constexpr auto LOCKON_DIST = 17;
  static constexpr auto BNPCBASE_KMACHINE_IRONSPIKE_01 = 8468;
  static constexpr auto BNPCBASE_KMACHINE_IRONSPIKE_02 = 8468;
  static constexpr auto BNPCBASE_KMACHINE_IRONSPIKE_03 = 8468;
  static constexpr auto BNPCBASE_KMACHINE_IRONSPIKE_04 = 8468;
  static constexpr auto BNPCBASE_MACHINE_WHEELED = 8469;
  static constexpr auto EOBJ_SLOW_AREA = 7292514;
  static constexpr auto EOBJ_WALL_CONTROL = 7307561;
  static constexpr auto EOBJ_GOSETSU_KATANA = 7315865;
  static constexpr auto STATUS_SLOW_TIME = 3620;
  static constexpr auto QIB_YELL_StmBdc103_01 = 6733;
  static constexpr auto QIB_YELL_StmBdc103_02 = 3089;
  static constexpr auto QIB_YELL_StmBdc103_03 = 6736;
  static constexpr auto LOC_BGM1 = 107;
  static constexpr auto LOGMESSAGE_LB_COUNT_01 = 9201;
  static constexpr auto LOGMESSAGE_LB_COUNT_02 = 9202;
  static constexpr auto LOGMESSAGE_LB_COUNT_03 = 9203;
  static constexpr auto LOGMESSAGE_LB_COUNT_04 = 9204;
  static constexpr auto LOGMESSAGE_LB_COUNT_05 = 9205;
  static constexpr auto LINEVOICE_ALPHINAUD_01 = 8201086;

public:
  HopeontheWaves() : Sapphire::ScriptAPI::QuestBattleScript( 181 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.registerEObj( "unknown_0", 2008480, 6894787, 4, { 564.783630f, -60.304729f, -136.444901f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_1", 2004541, 0, 4, { 800.087585f, 0.000000f, 44.317749f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( QuestBattle& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( HopeontheWaves );