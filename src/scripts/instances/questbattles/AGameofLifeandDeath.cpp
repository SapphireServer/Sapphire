#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class AGameofLifeandDeath : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto P_BNPC_JACKE = 6959281;
  static constexpr auto P_BNPC_OBORO = 6959282;
  static constexpr auto P_BNPC_YUKI = 6959283;
  static constexpr auto P_BNPC_VKEBBE = 6959341;
  static constexpr auto P_BNPC_PERIMUHAURIMU = 6959342;
  static constexpr auto BNPC_BOSS_ZAKURO = 6954394;
  static constexpr auto BNPC_P1_TRASH_01 = 6959313;
  static constexpr auto BNPC_P1_TRASH_02 = 6959314;
  static constexpr auto BNPC_P1_TRASH_03 = 6959316;
  static constexpr auto BNPC_P1_TRASH_04 = 6959317;
  static constexpr auto BNPC_P1_TRASH_05 = 6959318;
  static constexpr auto BNPC_P1_TRASH_06 = 6959319;
  static constexpr auto BNPC_P1_TRASH_07 = 6959320;
  static constexpr auto BNPC_P1_TRASH_08 = 6969442;
  static constexpr auto BNPC_P1_GUARD_01 = 6959327;
  static constexpr auto BNPC_P1_GUARD_02 = 6959328;
  static constexpr auto BNPC_P1_GUARD_03 = 6959329;
  static constexpr auto QIB_YELL_01 = 5676;
  static constexpr auto QIB_YELL_02 = 5677;
  static constexpr auto QIB_YELL_03 = 5678;
  static constexpr auto QIB_YELL_04 = 5679;
  static constexpr auto QIB_YELL_05 = 5680;
  static constexpr auto QIB_YELL_06 = 5681;
  static constexpr auto QIB_YELL_08 = 5683;
  static constexpr auto QIB_YELL_09 = 4589;
  static constexpr auto ER_VKEBBE_RESCUE = 6969449;
  static constexpr auto BNPCSTATE_NORMAL = 0;
  static constexpr auto BNPCSTATE_BOUND = 118;
  static constexpr auto EOBJ_VKEBBE_BIND = 6969631;
  static constexpr auto EOBJ_PERIMUHAURIMU_BIND = 6969634;
  static constexpr auto EOBJ_MAKIBISHI = 6971206;
  static constexpr auto EVENT_ACTION_01 = 42;
  static constexpr auto BNPC_P2_TRASH_01 = 6971209;
  static constexpr auto BNPC_P2_TRASH_02 = 6971210;
  static constexpr auto BNPC_P2_TRASH_03 = 6971211;
  static constexpr auto BNPC_P2_TRASH_04 = 6971212;
  static constexpr auto BNPC_P2_TRASH_05 = 6971213;
  static constexpr auto BNPC_P2_TRASH_06 = 6971214;
  static constexpr auto BNPC_P2_TRASH_07 = 6971216;
  static constexpr auto BNPC_P2_TRASH_08 = 6971217;
  static constexpr auto BNPC_P2_TRASH_09 = 6971219;
  static constexpr auto BNPC_P2_TRASH_10 = 6971221;
  static constexpr auto BNPC_KARASU = 6971224;
  static constexpr auto ACTION_MAKIBISHI = 8513;
  static constexpr auto STATUS_PARAM_MAKIBISHI_DOT = 3296;
  static constexpr auto PR_KARASU_ESCAPE = 6971517;
  static constexpr auto BNPC_P3_GUARD_01 = 7005448;
  static constexpr auto BNPC_P3_GUARD_02 = 7005449;
  static constexpr auto BNPC_P3_GUARD_03 = 7005450;
  static constexpr auto BNPC_P3_GUARD_04 = 7005730;
  static constexpr auto BNPC_P3_GUARD_05 = 7005731;
  static constexpr auto PR_YUKI_MOVE_FINAL = 7003839;
  static constexpr auto PR_JACKE_MOVE_FINAL = 7004138;
  static constexpr auto PR_VKEBEE_MOVE_FINAL = 7004140;
  static constexpr auto PR_OBORO_MOVE_FINAL = 7004141;
  static constexpr auto EOBJ_BOSS_ROOM_CONTROL = 7005846;
  static constexpr auto BNPC_BOSS_ARC_01 = 7005847;
  static constexpr auto BNPC_BOSS_LNC_01 = 7005848;
  static constexpr auto BNPC_BOSS_LNC_02 = 7005849;
  static constexpr auto BNPC_BOSS_ARC_02 = 7005850;
  static constexpr auto BNPC_BOSS_ARC_03 = 7005851;
  static constexpr auto P_BNPC_JACKE_BOSS = 7005853;
  static constexpr auto P_BNPC_OBORO_BOSS = 7005854;
  static constexpr auto P_BNPC_YUKI_BOSS = 7005855;
  static constexpr auto P_BNPC_VKEBBE_BOSS = 7005856;
  static constexpr auto P_BNPC_PERIMUHAURIMU_BOSS = 7005857;
  static constexpr auto BNPC_BOSS_LNC_HPLOW_01 = 7005916;
  static constexpr auto BNPC_BOSS_LNC_HPLOW_02 = 7005918;
  static constexpr auto BNPC_BOSS_ARC_HPLOW_01 = 7005919;
  static constexpr auto BNPC_BOSS_ARC_HPLOW_02 = 7005917;
  static constexpr auto BNPC_BOSS_KARASU_01 = 7005858;
  static constexpr auto BNPC_BOSS_TOUMEI_01 = 7005868;
  static constexpr auto BNPC_BOSS_TOUMEI_02 = 7005869;
  static constexpr auto BNPC_BOSS_TOUMEI_03 = 7005870;
  static constexpr auto BNPC_BOSS_TOUMEI_04 = 7005871;
  static constexpr auto BNPC_BOSS_TOUMEI_05 = 7005872;
  static constexpr auto BNPC_BOSS_TOUMEI_06 = 7005873;
  static constexpr auto BNPC_BOSS_TOUMEI_07 = 7005874;
  static constexpr auto BNPC_BOSS_TOUMEI_08 = 7005875;
  static constexpr auto BNPC_BOSS_TOUMEI_DAMMY_HATE = 7005878;
  static constexpr auto PR_BOSS_START = 7005852;
  static constexpr auto PR_OBORO_RAITON_AVOID = 7005883;
  static constexpr auto PR_JACKE_RAITON_AVOID = 7005885;
  static constexpr auto PR_YUKI_RAITON_AVOID = 7005886;
  static constexpr auto PR_VKEBEE_RAITON_AVOID = 7005887;
  static constexpr auto PR_PERIMUHAURIMU_RAITON_AVOID = 7005888;
  static constexpr auto ACTION_HISSATSUKEN_30 = 9516;
  static constexpr auto ACTION_HISSATSUKEN_90 = 9515;
  static constexpr auto ACTION_RAITON = 9517;
  static constexpr auto ACTION_TENNOIN = 2259;
  static constexpr auto ACTION_DEPOP_TRRIGER = 3269;
  static constexpr auto ACTION_TOUMEI_RAITON = 9518;
  static constexpr auto LOCKON_RAITION = 21;
  static constexpr auto BGM_BOSS_04 = 39;
  static constexpr auto LOC_ACTOR0 = 1022853;
  static constexpr auto LOC_ACTOR1 = 1023640;
  static constexpr auto LOC_ACTOR2 = 1023641;
  static constexpr auto LOC_MARKER_00 = 6991796;
  static constexpr auto STATUS_PARAM_HIDE = 1197;

public:
  AGameofLifeandDeath() : Sapphire::ScriptAPI::QuestBattleScript( 177 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.registerEObj( "unknown_0", 2008480, 6894787, 4, { 564.783630f, -60.304729f, -136.444901f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_1", 2004541, 0, 4, { 800.087585f, 0.000000f, 44.317749f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( AGameofLifeandDeath );