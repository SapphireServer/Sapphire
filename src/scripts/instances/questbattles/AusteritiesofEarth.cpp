#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class AusteritiesofEarth : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_POP_1_BOSS_TITAN_EGI_01 = 4301700;
  static constexpr auto INIT_POP_1_EARTH_ELE_POP_01 = 4301671;
  static constexpr auto INIT_POP_1_EARTH_ELE_POP_02 = 4301672;
  static constexpr auto INIT_POP_1_EARTH_ELE_POP_03 = 4301673;
  static constexpr auto INIT_POP_2_EARTH_GOLEM_POP_01 = 4301681;
  static constexpr auto INIT_POP_2_EARTH_GOLEM_POP_02 = 4301682;
  static constexpr auto INIT_POP_2_EARTH_GOLEM_POP_03 = 4301686;
  static constexpr auto INIT_POP_2_EARTH_GOLEM_POP_04 = 4321624;
  static constexpr auto INIT_POP_2_EARTH_GOLEM_POP_05 = 4321625;
  static constexpr auto INIT_POP_2_EARTH_GOLEM_POP_06 = 4321626;
  static constexpr auto INIT_POP_2_EARTH_GOLEM_POP_07 = 4321627;
  static constexpr auto INIT_POP_2_EARTH_GOLEM_POP_08 = 4321628;
  static constexpr auto INIT_POP_2_EARTH_GOLEM_POP_09 = 4321629;
  static constexpr auto INIT_POP_3_TRISTAN_01 = 4301698;
  static constexpr auto INIT_POP_3_BOSS_IFRIT_EGI_01 = 4301699;
  static constexpr auto INIT_P_POP_MITRA_01 = 4301637;
  static constexpr auto CUT_START_NCUT = 351;
  static constexpr auto CUT_INSART_NCUT = 352;
  static constexpr auto CUT_END_NCUT = 353;
  static constexpr auto BGM_TRISTAN_BATTLE = 37;
  static constexpr auto EOBJ_DAMAGE_RANGE_EARTH_01 = 4321459;
  static constexpr auto EOBJ_DAMAGE_RANGE_EARTH_02 = 4321585;
  static constexpr auto EOBJ_DAMAGE_RANGE_EARTH_03 = 4321586;
  static constexpr auto EOBJ_DAMAGE_RANGE_EARTH_04 = 4321587;
  static constexpr auto EOBJ_DAMAGE_RANGE_EARTH_05 = 4321588;
  static constexpr auto EOBJ_DAMAGE_RANGE_EARTH_06 = 4321589;
  static constexpr auto EOBJ_DAMAGE_RANGE_EARTH_07 = 4321590;
  static constexpr auto EOBJ_DAMAGE_RANGE_EARTH_08 = 4321591;
  static constexpr auto EOBJ_DAMAGE_RANGE_EARTH_09 = 4321623;
  static constexpr auto STATUS_CUSTOM_EARTH_DOT = 701;
  static constexpr auto DEF_ACTION_EARTH_FURY = 1332;
  static constexpr auto WARP_01 = 4329955;
  static constexpr auto JOB_STORY_MES = 3673;

public:
  AusteritiesofEarth() : Sapphire::ScriptAPI::QuestBattleScript( 80 )
  { }

  void onInit( QuestBattle& instance ) override
  {

  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( AusteritiesofEarth );