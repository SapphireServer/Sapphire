#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class NouveauRiche : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_POP_1_LNC_01 = 4293092;
  static constexpr auto INIT_POP_1_LNC_02 = 4293093;
  static constexpr auto INIT_POP_1_LNC_03 = 4293095;
  static constexpr auto INIT_POP_1_KIK_01 = 4293096;
  static constexpr auto INIT_P_POP_1_RED_LEADER = 4293097;
  static constexpr auto INIT_P_POP_1_RED_LNC = 4293098;
  static constexpr auto INIT_POP_2_EXC_LEADER_01 = 4293099;
  static constexpr auto INIT_POP_2_LNC_01 = 4293109;
  static constexpr auto INIT_POP_2_THM_01 = 4293110;
  static constexpr auto INIT_POP_2_ARC_01 = 4293111;
  static constexpr auto INIT_P_POP_2_ARC_01 = 4293125;
  static constexpr auto INIT_P_POP_2_ARC_02 = 4293126;
  static constexpr auto INIT_P_POP_2_ARC_03 = 4293127;
  static constexpr auto POP_RANGE_DEPOP = 4295055;
  static constexpr auto LOC_ACTOR1 = 1008111;
  static constexpr auto LOC_ACTOR2 = 1007656;
  static constexpr auto LOC_ACTOR3 = 1007658;
  static constexpr auto LOC_ACTOR4 = 1007659;
  static constexpr auto LOC_ACTOR5 = 1007655;
  static constexpr auto LOC_ACTOR6 = 1007657;
  static constexpr auto LOC_POS_ACTOR0 = 4310117;
  static constexpr auto LOC_POS_ACTOR1 = 4310122;
  static constexpr auto LOC_POS_ACTOR2 = 4310125;
  static constexpr auto LOC_POS_ACTOR3 = 4310127;
  static constexpr auto LOC_ACTION1 = 961;
  static constexpr auto BGM_BATTLE = 39;
  static constexpr auto LOC_BGM1 = 117;

public:
  NouveauRiche() : Sapphire::ScriptAPI::QuestBattleScript( 13 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.registerEObj( "Entrance", 2000182, 5021407, 5, { 623.000000f, 23.872311f, 94.505638f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 623.000000f, 23.656260f, 61.956181f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( NouveauRiche );