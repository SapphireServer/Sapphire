#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class MasterofMarksmanship : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto BNPC_ROSTNSTHAL_01 = 5895579;
  static constexpr auto BNPC_JOYE_01 = 5895580;
  static constexpr auto BNPC_ROSTNSTHAL_02 = 5895760;
  static constexpr auto BNPC_01_CONDOR_01 = 5895588;
  static constexpr auto BNPC_01_CONDOR_02 = 5895590;
  static constexpr auto BNPC_01_CONDOR_03 = 5895592;
  static constexpr auto BNPC_01_CONDOR_04 = 5895593;
  static constexpr auto BNPC_01_CONDOR_05 = 5895594;
  static constexpr auto BNPC_01_CONDOR_06 = 5895595;
  static constexpr auto BNPC_01_CONDOR_07 = 5895596;
  static constexpr auto BNPC_01_CONDOR_08 = 5895598;
  static constexpr auto BNPC_01_COEURL_01 = 5895601;
  static constexpr auto BNPC_01_COEURL_02 = 5895602;
  static constexpr auto BNPC_01_COEURL_03 = 5895603;
  static constexpr auto BNPC_01_COEURL_04 = 5895604;
  static constexpr auto BNPC_01_COEURL_05 = 5895634;
  static constexpr auto BNPC_01_COEURL_06 = 5895635;
  static constexpr auto BNPC_01_COEURL_07 = 5895636;
  static constexpr auto BNPC_01_RINGTAIL_01 = 5895606;
  static constexpr auto BNPC_01_RINGTAIL_02 = 5895607;
  static constexpr auto BNPC_01_RINGTAIL_03 = 5895608;
  static constexpr auto BNPC_01_RINGTAIL_04 = 5895609;
  static constexpr auto BNPC_01_RINGTAIL_05 = 5895610;
  static constexpr auto BNPC_01_RINGTAIL_06 = 5895612;
  static constexpr auto BNPC_01_RINGTAIL_07 = 5895613;
  static constexpr auto BNPC_01_RINGTAIL_08 = 5895614;
  static constexpr auto BNPC_01_SPRITE_01 = 5895615;
  static constexpr auto BNPC_01_SPRITE_02 = 5895616;
  static constexpr auto BNPC_01_SPRITE_03 = 5895618;
  static constexpr auto BNPC_01_SPRITE_04 = 5895619;
  static constexpr auto BNPC_01_SPRITE_05 = 5895620;
  static constexpr auto BNPC_01_SPRITE_06 = 5895623;
  static constexpr auto BNPC_01_SPRITE_07 = 5895624;
  static constexpr auto BNPC_01_SPRITE_08 = 5895625;
  static constexpr auto BNPC_01_GOLEM_01 = 5895626;
  static constexpr auto BNPC_01_GOLEM_02 = 5895627;
  static constexpr auto BNPC_01_GOLEM_03 = 5895628;
  static constexpr auto BNPC_01_GOLEM_04 = 5895629;
  static constexpr auto BNPC_01_GOLEM_05 = 5895630;
  static constexpr auto BNPC_01_GOLEM_06 = 5895631;
  static constexpr auto BNPC_01_GOLEM_07 = 5895632;
  static constexpr auto BNPC_02_BOMB_01 = 5895642;
  static constexpr auto BNPC_02_BOMB_02 = 5895646;
  static constexpr auto BNPC_02_BOMB_03 = 5895648;
  static constexpr auto BNPC_03_WEASEL_01 = 5895752;
  static constexpr auto BNPC_03_WEASEL_02 = 5895755;
  static constexpr auto BNPC_03_TIGER_01 = 5895753;
  static constexpr auto BNPC_03_TIGER_02 = 5895756;
  static constexpr auto MOVING_POINT_01 = 5895586;
  static constexpr auto MOVING_POINT_02 = 5895757;
  static constexpr auto ER_RECT_01 = 5895759;
  static constexpr auto WARP_PC_POINT_01 = 5895762;
  static constexpr auto MOVING_POINT_JOYE_01 = 5908268;
  static constexpr auto BNPC_TYPE_01_GOLEM = 4287;
  static constexpr auto BNPC_TYPE_02_BOMB = 4291;
  static constexpr auto BNPC_TYPE_03_WEASEL = 4294;
  static constexpr auto BNPC_TYPE_03_TIGER = 4295;
  static constexpr auto ENPC_STEPHANIVIEN_01 = 5899500;
  static constexpr auto ENPC_JOYE_01 = 5899501;
  static constexpr auto BEHAVIOR_ROSTNSTHAL_01 = 30601;
  static constexpr auto BEHAVIOR_JOYE_01 = 30602;
  static constexpr auto BEHAVIOR_JOYE_02 = 30603;
  static constexpr auto BEHAVIOR_JOYE_03 = 30604;
  static constexpr auto BEHAVIOR_JOYE_04 = 30605;
  static constexpr auto QIB_YELL_01 = 2723;
  static constexpr auto QIB_YELL_02 = 2724;
  static constexpr auto QIB_YELL_03 = 2725;
  static constexpr auto QIB_YELL_04 = 2726;
  static constexpr auto ACTION_SCRIPT_TRIGGER = 3269;
  static constexpr auto ACTION_HEART_SHOT = 2875;
  static constexpr auto BGM_BOSS_BATTLE = 39;
  static constexpr auto LOC_MARKER_01 = 5923224;
  static constexpr auto LOC_ACTOR0 = 1014580;
  static constexpr auto LOC_ACTOR1 = 1015124;
  static constexpr auto LOC_ACTOR2 = 1014579;

public:
  MasterofMarksmanship() : Sapphire::ScriptAPI::QuestBattleScript( 127 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.registerEObj( "unknown_0", 2000200, 2489513, 4, { 111.832100f, 24.171450f, -613.209473f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_1", 2000201, 2489537, 4, { 47.863529f, 24.380640f, -739.987976f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_2", 2000202, 2489511, 4, { 127.017097f, 24.144819f, -719.131226f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_3", 2000203, 2489539, 4, { 176.514206f, 24.118999f, -640.707825f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_4", 2000204, 0, 4, { 223.131302f, 22.248779f, -596.149780f }, 0.991760f, 0.000048f ); 

  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( MasterofMarksmanship );