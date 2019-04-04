#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class AusteritiesofWind : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_P_POP_MITRA_01 = 4302425;
  static constexpr auto INIT_POP_1_BOSS_GARUDA_EGI_01 = 4302448;
  static constexpr auto INIT_POP_2_GARUDA_FZR_POP_02 = 4302452;
  static constexpr auto INIT_POP_2_GARUDA_FZR_POP_03 = 4302454;
  static constexpr auto INIT_POP_2_GARUDA_FZR_POP_04 = 4302455;
  static constexpr auto INIT_POP_1_BOSS_GARUDA_EGI_CHILD_A = 4321859;
  static constexpr auto INIT_POP_1_BOSS_GARUDA_EGI_CHILD_B = 4321860;
  static constexpr auto CUT_START_NCUT = 354;
  static constexpr auto DEF_ACTION_GARUDA_AIRIAL_SLASH = 794;
  static constexpr auto JOB_STORY_MES = 3675;

public:
  AusteritiesofWind() : Sapphire::ScriptAPI::QuestBattleScript( 81 )
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

EXPOSE_SCRIPT( AusteritiesofWind );