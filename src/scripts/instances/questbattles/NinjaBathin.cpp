#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class NinjaBathin : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto BNPC_P1_GENIN_01 = 5126277;
  static constexpr auto BNPC_P1_GENIN_02 = 5126278;
  static constexpr auto BNPC_P1_GENIN_03 = 5126282;
  static constexpr auto BNPC_P1_GENIN_04 = 5126283;
  static constexpr auto BNPC_P1_GENIN_05 = 5126286;
  static constexpr auto BNPC_P1_GENIN_06 = 5126289;
  static constexpr auto BNPC_P1_GENIN_07 = 5126291;
  static constexpr auto BNPC_P1_KOUMORI_01 = 5126325;
  static constexpr auto BNPC_P1_KOUMORI_02 = 5126327;
  static constexpr auto BNPC_P1_CHUNIN_01 = 5126369;
  static constexpr auto BNPC_P1_CHUNIN_02 = 5126370;
  static constexpr auto BNPC_P1_KARASU_01 = 5126373;
  static constexpr auto BNPC_P2_OBORO_01 = 5126473;
  static constexpr auto BNPC_P2_TSUBAME_01 = 5126474;
  static constexpr auto ER_P2_START_RECT = 5126241;
  static constexpr auto BNPC_P3_CHUNIN_04 = 5126481;
  static constexpr auto BNPC_P3_CHUNIN_05 = 5126482;
  static constexpr auto PR_P3_MOVE_TARGET_KARASU_01 = 5126526;
  static constexpr auto BNPC_P4_CHUNIN_06 = 5127359;
  static constexpr auto BNPC_P4_CHUNIN_07 = 5127360;
  static constexpr auto BNPC_P4_CHUNIN_08 = 5127361;
  static constexpr auto PR_P4_MOVE_TARGET_KARASU_01 = 5127368;
  static constexpr auto YELL_P2_KARASU_01 = 2353;
  static constexpr auto BGM_LASTHALF = 117;
  static constexpr auto EOBJ_MAKIBISHI = 5326559;
  static constexpr auto STATUS_MAKIBISHI_DAMAGE = 1221;
  static constexpr auto DEF_ACTION_MAKIBISHI = 3196;
  static constexpr auto LOC_ENPC_CHUNIN_01 = 1010697;
  static constexpr auto LOC_ENPC_KARASU_01 = 1010560;
  static constexpr auto LOC_ENPC_OBORO_01 = 1010597;
  static constexpr auto LOC_ENPC_TSUBAME_01 = 1010764;
  static constexpr auto LOC_ENPC_GENIN_01 = 1010700;
  static constexpr auto LOC_ENPC_GENIN_02 = 1010701;
  static constexpr auto LOC_MARKER_01 = 5375029;
  static constexpr auto LOC_MARKER_02 = 5372783;
  static constexpr auto LOC_ENPC_GEKKAI_01 = 1010559;
  static constexpr auto LOC_MOTION0 = 1056;
  static constexpr auto LOC_BGM0 = 130;
  static constexpr auto LOC_ENPC_KOUMORI_01 = 1010561;
  static constexpr auto STATUS_STEALTH = 1198;
  static constexpr auto LOC_ENPC_OBORO_02 = 1010713;
  static constexpr auto LOC_ENPC_TSUBAME_02 = 1010598;
  static constexpr auto BNPC_P1_KOUMORI_03 = 5405169;
  static constexpr auto BNPC_P1_GENIN_08 = 5405171;

public:
  NinjaBathin() : Sapphire::ScriptAPI::QuestBattleScript( 98 )
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

EXPOSE_SCRIPT( NinjaBathin );