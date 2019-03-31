#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class FortuneFavorstheBole : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto BNPC_PACK_A_LNC_01 = 5898639;
  static constexpr auto BNPC_PACK_A_ARC_01 = 5898640;
  static constexpr auto BNPC_PACK_A_ARC_02 = 5898644;
  static constexpr auto BNPC_PACK_B_LNC_01 = 5898690;
  static constexpr auto BNPC_PACK_B_ARC_01 = 5898691;
  static constexpr auto BNPC_PACK_B_ARC_02 = 5898692;
  static constexpr auto BNPC_PACK_B_CNJ_01 = 5898693;
  static constexpr auto BNPC_STAR_A_BAT_01 = 5898699;
  static constexpr auto BNPC_STAR_A_BAT_02 = 5898704;
  static constexpr auto BNPC_STAR_A_BAT_03 = 5898705;
  static constexpr auto BNPC_STAR_B_WISP_01 = 5898706;
  static constexpr auto BNPC_STAR_B_WISP_02 = 5898707;
  static constexpr auto BNPC_STAR_B_YAMANE_01 = 5898708;
  static constexpr auto BNPC_PACK_C_LNC_01 = 5898710;
  static constexpr auto BNPC_PACK_C_ARC_01 = 5898711;
  static constexpr auto BNPC_PACK_C_THM_01 = 5898712;
  static constexpr auto BNPC_PACK_C_CNJ_01 = 5898713;
  static constexpr auto BNPC_STAR_C_TREANT_01 = 5898717;
  static constexpr auto BNPC_STAR_C_BAT_01 = 5898718;
  static constexpr auto BNPC_STAR_C_BAT_02 = 5898719;
  static constexpr auto BNPC_PACK_D_ACN_BOSS_01 = 5898722;
  static constexpr auto BNPC_PACK_D_ARC_01 = 5898724;
  static constexpr auto BNPC_PACK_D_ARC_02 = 5898725;
  static constexpr auto BNPC_ADD_DEEP_EYE_01 = 5898739;
  static constexpr auto BNPC_ADD_GOLEM_01 = 5898740;
  static constexpr auto P_BNPC_SEBAS_01 = 5898750;
  static constexpr auto P_BNPC_LNC_01 = 5898751;
  static constexpr auto P_BNPC_LUNA_01 = 5898752;
  static constexpr auto EOBJ_TAROT_FIRE_01 = 5898834;
  static constexpr auto EOBJ_TAROT_WATER_01 = 5898836;
  static constexpr auto EOBJ_TAROT_WIND_01 = 5898837;
  static constexpr auto EOBJ_TAROT_EARTH_01 = 5898840;
  static constexpr auto EOBJ_TAROT_LIGHTNING_01 = 5898841;
  static constexpr auto EOBJ_TAROT_ICE_01 = 5898842;
  static constexpr auto EVENT_ACTION_01 = 22;
  static constexpr auto LOG_MESSAGE_ACCESE_FIRE_01 = 3256;
  static constexpr auto LOG_MESSAGE_ACCESE_WATER_01 = 3257;
  static constexpr auto LOG_MESSAGE_ACCESE_WIND_01 = 3258;
  static constexpr auto LOG_MESSAGE_ACCESE_EARTH_01 = 3259;
  static constexpr auto LOG_MESSAGE_ACCESE_LIGHTNING_01 = 3260;
  static constexpr auto LOG_MESSAGE_ACCESE_ICE_01 = 3261;
  static constexpr auto STATUS_PARAM_STAR_POWER = 1747;
  static constexpr auto NCUT_01 = 980;
  static constexpr auto STATUS_PLAY_TAROT_FIRE_01 = 829;
  static constexpr auto STATUS_PLAY_TAROT_WATER_01 = 833;
  static constexpr auto STATUS_PLAY_TAROT_WIND_01 = 831;
  static constexpr auto STATUS_PLAY_TAROT_EARTH_01 = 830;
  static constexpr auto STATUS_PLAY_TAROT_LIGHTNING_01 = 834;
  static constexpr auto STATUS_PLAY_TAROT_ICE_01 = 832;
  static constexpr auto YELL_QIB_FIRE_LNC_01 = 2664;
  static constexpr auto YELL_QIB_EARTH_SEBAS_01 = 2665;
  static constexpr auto YELL_QIB_WIND_LNC_01 = 2666;
  static constexpr auto YELL_QIB_ICE_SEBAS_01 = 2667;
  static constexpr auto YELL_QIB_LIGHTNING_LNC_01 = 2668;
  static constexpr auto YELL_QIB_LEVEVA_01 = 2783;
  static constexpr auto YELL_QIB_YATO_01 = 2784;
  static constexpr auto ENPC_OLD_AST_01 = 5900085;
  static constexpr auto PR_LEVEVA_MOVE_01 = 5913204;
  static constexpr auto BEHAVIOR_LEVEVA_01 = 30617;
  static constexpr auto BGM_START = 113;
  static constexpr auto P_BNPC_TOUMEI_FOLLOW_PLAYER = 5914841;
  static constexpr auto EVENT_RANGE_PACK_B_SENSE = 5915107;
  static constexpr auto EVENT_RANGE_PACK_C_SENSE = 5915618;
  static constexpr auto EVENT_RANGE_PACK_D_SENSE = 5915672;
  static constexpr auto BNPCBASE_BAT = 4297;
  static constexpr auto BNPCBASE_WISP = 4298;
  static constexpr auto BNPCBASE_YAMANE = 4299;
  static constexpr auto BNPCBASE_TRENT = 4300;
  static constexpr auto BNPCBASE_DEEP_EYES = 4309;
  static constexpr auto BNPCBASE_GOLEM = 4310;
  static constexpr auto ACTION_SUMMON_MONSTER = 4779;
  static constexpr auto LOC_ACTOR_MACE = 1014686;
  static constexpr auto LOC_ACTOR_LEVE = 1015607;
  static constexpr auto LOC_ACTOR_QUIMP = 1014685;
  static constexpr auto LOC_ACTOR_GUARD = 1014688;
  static constexpr auto LOC_ACTOR_CELIE = 1014687;
  static constexpr auto LOC_ACTION_BASE_01 = 936;
  static constexpr auto LOC_LOG_MES_EARTH = 5340;
  static constexpr auto LOC_ACTION0 = 979;
  static constexpr auto LOC_BGM0 = 211;

public:
  FortuneFavorstheBole() : Sapphire::ScriptAPI::QuestBattleScript( 143 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.registerEObj( "Entrance", 2000182, 5021407, 5, { 623.000000f, 23.872311f, 94.505638f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 623.000000f, 23.656260f, 61.956181f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( QuestBattle& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( FortuneFavorstheBole );