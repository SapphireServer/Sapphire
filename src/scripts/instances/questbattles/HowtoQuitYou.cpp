#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class HowtoQuitYou : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_POP_1ST_A_01 = 4272556;
  static constexpr auto INIT_POP_1ST_A_02 = 4272557;
  static constexpr auto INIT_POP_1ST_A_03 = 4272558;
  static constexpr auto INIT_POP_1ST_A_04 = 4272559;
  static constexpr auto INIT_POP_1ST_A_05 = 4272560;
  static constexpr auto INIT_P_POP_01 = 4329195;
  static constexpr auto INIT_P_POP_02 = 4272571;
  static constexpr auto INIT_P_POP_03 = 4272573;
  static constexpr auto INIT_POP_2ND_B_01 = 4272579;
  static constexpr auto INIT_POP_2ND_B_02 = 4272580;
  static constexpr auto INIT_POP_2ND_B_03 = 4272581;
  static constexpr auto INIT_POP_2ND_B_04 = 4272582;
  static constexpr auto INIT_POP_2ND_B_05 = 4272583;
  static constexpr auto INIT_POP_BOSS = 4273307;
  static constexpr auto WARP_01 = 4273310;
  static constexpr auto INIT_POP_3RD_C_01 = 4273323;
  static constexpr auto INIT_POP_3RD_C_02 = 4273324;
  static constexpr auto INIT_POP_3RD_C_03 = 4273327;
  static constexpr auto INIT_POP_3RD_C_04 = 4273328;
  static constexpr auto INIT_POP_3RD_C_05 = 4273331;
  static constexpr auto INIT_POP_3RD_C_06 = 4273332;
  static constexpr auto INIT_POP_3RD_C_07 = 4273334;
  static constexpr auto INIT_POP_3RD_C_08 = 4273335;
  static constexpr auto INIT_POP_3RD_C_09 = 4273336;
  static constexpr auto INIT_POP_3RD_C_10 = 4273338;
  static constexpr auto INIT_POP_3RD_C_11 = 4273341;
  static constexpr auto INIT_POP_3RD_C_12 = 4273343;
  static constexpr auto INIT_POP_3RD_C_13 = 4273344;
  static constexpr auto INIT_POP_4TH_D_01 = 4273694;
  static constexpr auto INIT_POP_4TH_D_02 = 4273695;
  static constexpr auto INIT_POP_4TH_D_03 = 4273696;
  static constexpr auto INIT_POP_4TH_D_04 = 4273697;
  static constexpr auto INIT_POP_4TH_D_05 = 4273700;
  static constexpr auto INIT_POP_4TH_D_06 = 4273701;
  static constexpr auto INIT_POP_4TH_D_07 = 4273702;
  static constexpr auto INIT_POP_4TH_D_08 = 4273704;
  static constexpr auto INIT_POP_4TH_D_09 = 4273705;
  static constexpr auto INIT_POP_4TH_D_10 = 4273706;
  static constexpr auto INIT_POP_4TH_D_11 = 4273708;
  static constexpr auto INIT_POP_4TH_C_01 = 4273709;
  static constexpr auto INIT_POP_4TH_C_02 = 4273710;
  static constexpr auto INIT_POP_4TH_C_03 = 4273713;
  static constexpr auto INIT_POP_4TH_C_04 = 4273714;
  static constexpr auto INIT_POP_4TH_C_05 = 4273715;
  static constexpr auto INIT_POP_4TH_C_06 = 4273716;
  static constexpr auto INIT_POP_4TH_C_07 = 4273727;
  static constexpr auto INIT_POP_4TH_C_08 = 4273729;
  static constexpr auto INIT_POP_4TH_C_09 = 4273732;
  static constexpr auto INIT_POP_4TH_C_10 = 4273733;
  static constexpr auto INIT_POP_4TH_C_11 = 4273735;
  static constexpr auto INIT_POP_4TH_C_12 = 4273738;
  static constexpr auto INIT_POP_4TH_C_13 = 4273740;
  static constexpr auto INIT_POP_4TH_C_14 = 4302586;
  static constexpr auto INIT_POP_4TH_C_15 = 4302587;
  static constexpr auto INIT_POP_4TH_C_16 = 4302589;
  static constexpr auto INIT_POP_4TH_C_17 = 4302590;
  static constexpr auto INIT_ENPC_POP_01 = 4274643;
  static constexpr auto INIT_ENPC_POP_02 = 4274644;
  static constexpr auto LOG_EVENT_QIB_WAR500_BTL_01 = 3204;
  static constexpr auto LOG_EVENT_QIB_WAR500_BTL_02 = 3205;
  static constexpr auto BGM_JOB_SHIREN = 91;
  static constexpr auto LOC_ACTOR0 = 1007128;
  static constexpr auto LOC_ACTOR1 = 1007141;
  static constexpr auto LOC_ACTOR2 = 1007142;
  static constexpr auto LOC_ACTOR3 = 1007143;
  static constexpr auto LOC_POS_ACTOR0 = 4312944;
  static constexpr auto CUT_INSART_NCUT = 323;
  static constexpr auto CUT_END_NCUT = 324;
  static constexpr auto INIT_ENPC_POP_03 = 4322368;
  static constexpr auto INIT_ENPC_POP_04 = 4322688;
  static constexpr auto JOB_STORY_MES = 3606;

public:
  HowtoQuitYou() : Sapphire::ScriptAPI::QuestBattleScript( 67 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.registerEObj( "unknown_0", 2009569, 0, 4, { 763.213318f, 9.000000f, 358.016998f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_1", 2009570, 0, 4, { 748.506775f, 9.000000f, 520.002930f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( HowtoQuitYou );