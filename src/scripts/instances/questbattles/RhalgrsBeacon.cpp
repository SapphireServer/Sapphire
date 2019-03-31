#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class RhalgrsBeacon : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_WARP_POINT_001 = 6797597;
  static constexpr auto LOC_MARKER_001 = 6797770;
  static constexpr auto P_BNPC_ALENVALD = 6797761;
  static constexpr auto P_BNPC_CONRAD = 6797762;
  static constexpr auto P_BNPC_LISE = 6797763;
  static constexpr auto P_BNPC_FRIEND_ARAMIGO_SWD = 6797764;
  static constexpr auto P_BNPC_FRIEND_ARAMIGO_ARC = 6797765;
  static constexpr auto P_BNPC_FRIEND_ANANTA_SWD = 6797766;
  static constexpr auto BNPC_PACK1_OPERATOR = 6865638;
  static constexpr auto BNPC_PACK1_SWD1 = 6865641;
  static constexpr auto BNPC_PACK1_SWD2 = 6865642;
  static constexpr auto BNPC_PACK1_MACHINE1 = 6865639;
  static constexpr auto BNPC_PACK1_MACHINE2 = 6865643;
  static constexpr auto BNPC_PACK2_CANON1 = 6865577;
  static constexpr auto BNPC_PACK2_CANON2 = 6865579;
  static constexpr auto BNPC_PACK2_CANON3 = 6865580;
  static constexpr auto BNPC_PACK2_SWD1 = 6865806;
  static constexpr auto BNPC_PACK2_SWD2 = 6865808;
  static constexpr auto BNPC_PACK2_THM1 = 6865810;
  static constexpr auto BNPC_PACK2_THM2 = 6865809;
  static constexpr auto BNPC_PACK2_MACHINE1 = 6865812;
  static constexpr auto BNPC_PACK2_MACHINE2 = 6865813;
  static constexpr auto BNPC_PACK2_MACHINE3 = 6865814;
  static constexpr auto BNPC_PACK2_CANON1_TOUMEI = 6866595;
  static constexpr auto BNPC_PACK2_CANON2_TOUMEI = 6866597;
  static constexpr auto BNPC_PACK2_CANON3_TOUMEI = 6866599;
  static constexpr auto BNPCBASEID_PACK2_CANON = 6986;
  static constexpr auto PRANGE_ALENVALD_MOVE1 = 6866210;
  static constexpr auto PRANGE_ALENVALD_MOVE2 = 6866237;
  static constexpr auto PRANGE_ALENVALD_MOVE3 = 6869636;
  static constexpr auto PRANGE_LISE_MOVE1 = 6869607;
  static constexpr auto PRANGE_LISE_MOVE2 = 6869621;
  static constexpr auto PRANGE_LISE_MOVE3 = 6869633;
  static constexpr auto PRANGE_CONRAD_MOVE1 = 6869613;
  static constexpr auto PRANGE_CONRAD_MOVE2 = 6869624;
  static constexpr auto PRANGE_CONRAD_MOVE3 = 6869635;
  static constexpr auto PRANGE_ARAMIGO_SWD_MOVE1 = 6869609;
  static constexpr auto PRANGE_ARAMIGO_SWD_MOVE2 = 6869622;
  static constexpr auto PRANGE_ARAMIGO_SWD_MOVE3 = 6869634;
  static constexpr auto PRANGE_ARAMIGO_ARC_MOVE1 = 6869611;
  static constexpr auto PRANGE_ARAMIGO_ARC_MOVE2 = 6869623;
  static constexpr auto PRANGE_ARAMIGO_ARC_MOVE3 = 6869638;
  static constexpr auto PRANGE_ANANTA_SWD_MOVE1 = 6869614;
  static constexpr auto PRANGE_ANANTA_SWD_MOVE2 = 6869625;
  static constexpr auto PRANGE_ANANTA_SWD_MOVE3 = 6869637;
  static constexpr auto EOBJ_BOSS_ROOM_CONTROL = 6869904;
  static constexpr auto BNPC_FORDLA = 6873306;
  static constexpr auto BNPC_JUJIGIRI = 6870178;
  static constexpr auto BNPC_BIT_FAN_01 = 6971372;
  static constexpr auto BNPC_BIT_FAN_02 = 6971370;
  static constexpr auto BNPC_BIT_FAN_03 = 6971371;
  static constexpr auto BNPC_BIT_FAN_04 = 6870173;
  static constexpr auto BNPC_GTAE_TOUMEI1 = 6870454;
  static constexpr auto BNPC_GTAE_TOUMEI2 = 6870455;
  static constexpr auto BNPC_GTAE_TOUMEI3 = 6969748;
  static constexpr auto BNPC_GTAE_TOUMEI4 = 6969749;
  static constexpr auto BNPC_GTAE_TOUMEI5 = 6971375;
  static constexpr auto BNPC_GTAE_TOUMEI6 = 6971376;
  static constexpr auto BNPC_GTAE_TOUMEI7 = 6971377;
  static constexpr auto BNPC_GTAE_TOUMEI8 = 6971378;
  static constexpr auto BNPC_SKULL_CONRAD = 6873176;
  static constexpr auto BNPC_SKULL_ALENVALD = 6873177;
  static constexpr auto BNPC_SKULL_ARAMIGO_SWD = 6873178;
  static constexpr auto BNPC_SKULL_LISE = 6873180;
  static constexpr auto BNPC_SKULL_ANANTA = 6873181;
  static constexpr auto BNPC_SKULL_ARAMIGO_ARC = 6873182;
  static constexpr auto P_BNPC_LISE_SECOND_HALF = 6873185;
  static constexpr auto P_BNPC_CONRAD_SECOND_HALF = 6873186;
  static constexpr auto P_BNPC_ALENVALD_SECOND_HALF = 6873187;
  static constexpr auto P_BNPC_FRIEND_ARAMIGO_SWD_SECOND_HALF = 6873188;
  static constexpr auto P_BNPC_FRIEND_ARAMIGO_ARC_SECOND_HALF = 6873189;
  static constexpr auto P_BNPC_FRIEND_ANANTA_SWD_SECOND_HALF = 6873190;
  static constexpr auto PRANGE_GTAE_01 = 6969732;
  static constexpr auto PRANGE_GTAE_02 = 6969736;
  static constexpr auto PRANGE_GTAE_03 = 6969737;
  static constexpr auto PRANGE_GTAE_04 = 6969738;
  static constexpr auto ACTION_JUJIGIRI = 8371;
  static constexpr auto ACTION_JUJIGIRI_ORDER = 8370;
  static constexpr auto ACTION_GTAE_FORDRA = 8345;
  static constexpr auto ACTION_SUMMON_BIT = 8344;
  static constexpr auto ACTION_GTAE_TOUMEI = 8346;
  static constexpr auto EOBJ_DAMAGE_FLOOR = 6870453;
  static constexpr auto STATUS_PAIN = 2924;
  static constexpr auto STATUS_KNOCKDOWN_ETERNAL = 3000;
  static constexpr auto ERANGE_PACK1 = 6865724;
  static constexpr auto ERANGE_PACK2 = 6865801;
  static constexpr auto ERANGE_PACK1_DESTROYED = 6866125;
  static constexpr auto BGM_BOSS_BATTLE = 406;
  static constexpr auto LOC_ACTOR_01 = 1018509;
  static constexpr auto LOC_ACTOR_02 = 1019082;
  static constexpr auto LOC_ACTOR_03 = 1019537;
  static constexpr auto LOC_ACTOR_04 = 1019098;
  static constexpr auto LOC_ACTOR_05 = 1019545;
  static constexpr auto LOC_IDLE_01 = 34;
  static constexpr auto LOC_ACTION_01 = 1;
  static constexpr auto ACTION_CANON = 8308;
  static constexpr auto BNPC_TOUMEI_JUJIGIRI_MOVE_B01 = 6870077;

public:
  RhalgrsBeacon() : Sapphire::ScriptAPI::QuestBattleScript( 160 )
  { }

  void onInit( QuestBattle& instance ) override
  {

  }

  void onUpdate( QuestBattle& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( RhalgrsBeacon );