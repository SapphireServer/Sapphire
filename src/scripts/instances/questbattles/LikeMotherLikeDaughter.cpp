#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class LikeMotherLikeDaughter : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_POP_PRIN_1_01 = 4249083;
  static constexpr auto INIT_POP_PRIN_1_02 = 4249087;
  static constexpr auto INIT_POP_PRIN_1_03 = 4249088;
  static constexpr auto INIT_POP_YODOMI = 4250414;
  static constexpr auto INIT_P_POP_WULFIUE = 4249072;
  static constexpr auto INIT_P_POP_NOLANEL = 4249073;
  static constexpr auto INIT_P_POP_JOACIN = 4249074;
  static constexpr auto INIT_POP_TREE_2_01 = 4249097;
  static constexpr auto INIT_POP_TREE_2_02 = 4249098;
  static constexpr auto INIT_POP_YAMANE_2_01 = 4249106;
  static constexpr auto INIT_POP_YAMANE_2_02 = 4249107;
  static constexpr auto INIT_POP_EARTH_SPRIT = 4249109;
  static constexpr auto INIT_POP_TREE_3_01 = 4250514;
  static constexpr auto INIT_POP_TREE_3_02 = 4250515;
  static constexpr auto INIT_P_POP_ELEMENTAL_THUNDER = 4249116;
  static constexpr auto INIT_P_POP_ELEMENTAL_WIND = 4249117;
  static constexpr auto INIT_P_POP_ELEMENTAL_WATER = 4249119;
  static constexpr auto INIT_P_POP_PRIN_BOSS = 4249132;
  static constexpr auto INIT_ENPC_POP_01 = 4249177;
  static constexpr auto INIT_ENPC_POP_02 = 4249178;
  static constexpr auto INIT_ENPC_POP_03 = 4249179;
  static constexpr auto INIT_ENPC_POP_04 = 4249180;
  static constexpr auto DEF_WEATHER_BOLT = 10;
  static constexpr auto DEF_WEATHER_FINE = 1;
  static constexpr auto YELL_QIB_WULFIUE_01 = 996;
  static constexpr auto YELL_QIB_NOLANEL_01 = 997;
  static constexpr auto YELL_QIB_JOACIN_01 = 998;

public:
  LikeMotherLikeDaughter() : Sapphire::ScriptAPI::QuestBattleScript( 56 )
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

EXPOSE_SCRIPT( LikeMotherLikeDaughter );