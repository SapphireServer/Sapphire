#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class AndMyAxe : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto BNPC_CURIOUSGORGE_01 = 5821944;
  static constexpr auto BNPC_WHEISKAET_01 = 5821948;
  static constexpr auto BNPC_BROKENMOUNTAIN_01 = 5821952;
  static constexpr auto BNPC_EYNZAHR_01 = 5821946;
  static constexpr auto BNPC_1T_SOL_01 = 5821959;
  static constexpr auto BNPC_1T_SOL_02 = 5821960;
  static constexpr auto BNPC_1T_LNC_01 = 5821966;
  static constexpr auto BNPC_1T_LNC_02 = 5821967;
  static constexpr auto BNPC_1T_LNC_03 = 5821973;
  static constexpr auto BNPC_1T_LNC_04 = 5821976;
  static constexpr auto BNPC_1T_FIG_01 = 5821963;
  static constexpr auto BNPC_1T_FIG_02 = 5821964;
  static constexpr auto BNPC_1T_MAG_01 = 5821968;
  static constexpr auto BNPC_1T_MAG_02 = 5821971;
  static constexpr auto BNPC_2T_SOL_01 = 5822009;
  static constexpr auto BNPC_2T_FIG_01 = 5822010;
  static constexpr auto BNPC_2T_LNC_01 = 5822012;
  static constexpr auto BNPC_2T_LNC_02 = 5822013;
  static constexpr auto BNPC_2T_MAG_01 = 5822014;
  static constexpr auto BNPC_3T_KARLBOSS_01 = 5822020;
  static constexpr auto BNPC_3T_INVI_01 = 5822027;
  static constexpr auto BNPC_3T_SAHBOSS_01 = 5822030;
  static constexpr auto BNPC_4T_SOUL_01 = 5822038;
  static constexpr auto BNPC_4T_SOUL_02 = 5822039;
  static constexpr auto BNPC_4T_SOUL_03 = 5822040;
  static constexpr auto BNPC_4T_SOUL_04 = 5822041;
  static constexpr auto BNPC_4T_SOUL_05 = 5822042;
  static constexpr auto BNPC_4T_SOUL_06 = 5822043;
  static constexpr auto BNPC_4T_SOUL_07 = 5822044;
  static constexpr auto BNPC_4T_SOUL_08 = 5822045;
  static constexpr auto WARP_01 = 5827124;
  static constexpr auto BGM_BOSS_BATTLE = 91;
  static constexpr auto LOGMESSAGE_01 = 3204;
  static constexpr auto LOGMESSAGE_02 = 2099;
  static constexpr auto BNPCBASE_GENSHO_SOUL = 4157;
  static constexpr auto BNPCBASE_TOUMEI = 4146;
  static constexpr auto DEF_ACTION_KARA_HASHA = 3058;
  static constexpr auto DEF_ACTION_KARA_CHAKUDAN = 4749;
  static constexpr auto STATUS_MARKING = 420;
  static constexpr auto LOCKON_FOR_MARKING = 8;
  static constexpr auto DEF_ACTION_MARKING = 4002;
  static constexpr auto STATUS_PARAM_MARKING = 1283;
  static constexpr auto STATUS_PARAM_ANTI_MARKING = 1284;
  static constexpr auto BNPCNAME_KARLBOSS = 4154;
  static constexpr auto NCUT_01 = 934;
  static constexpr auto LOC_ACTOR1 = 1014475;
  static constexpr auto LOC_ACTOR2 = 1014476;
  static constexpr auto LOC_ACTOR3 = 1014477;
  static constexpr auto LOC_ACTOR4 = 1014478;
  static constexpr auto LOC_POS1 = 5911693;
  static constexpr auto LOC_ACTION1 = 1071;
  static constexpr auto LOC_BGM1 = 39;
  static constexpr auto BNPC_CURIOUSGORGE_02 = 5957444;
  static constexpr auto BNPC_WHEISKAET_02 = 5957445;
  static constexpr auto BNPC_BROKENMOUNTAIN_02 = 5957447;
  static constexpr auto BNPC_EYNZAHR_02 = 5957446;

public:
  AndMyAxe() : Sapphire::ScriptAPI::QuestBattleScript( 103 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.registerEObj( "Entrance", 2000182, 6228959, 5, { 457.583801f, 5.680784f, 280.512787f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "unknown_0", 2000608, 2807920, 4, { -95.322441f, -25.054260f, 61.518002f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( QuestBattle& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( AndMyAxe );