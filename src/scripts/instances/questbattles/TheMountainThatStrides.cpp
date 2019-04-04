#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class TheMountainThatStrides : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_P_POP_1ST_01 = 4125284;
  static constexpr auto INIT_POP_1ST_01 = 4125273;
  static constexpr auto INIT_POP_1ST_02 = 4125274;
  static constexpr auto INIT_POP_1ST_03 = 4125275;
  static constexpr auto INIT_POP_1ST_04 = 4125276;
  static constexpr auto INIT_POP_1ST_05 = 4125277;
  static constexpr auto INIT_POP_1ST_06 = 4125280;
  static constexpr auto INIT_POP_2ST_01 = 4125319;
  static constexpr auto INIT_POP_2ST_02 = 4125320;
  static constexpr auto INIT_POP_2ST_03 = 4125312;
  static constexpr auto INIT_POP_2ST_04 = 4125316;
  static constexpr auto INIT_POP_2ST_05 = 4125321;
  static constexpr auto INIT_POP_2ST_06 = 4125317;
  static constexpr auto INIT_POP_3ST_01 = 4125338;
  static constexpr auto INIT_POP_3ST_02 = 4125340;
  static constexpr auto INIT_POP_3ST_03 = 4125342;
  static constexpr auto INIT_POP_3ST_04 = 4125343;
  static constexpr auto INIT_POP_3ST_05 = 4125345;
  static constexpr auto CUT_SCENE_01 = 38;
  static constexpr auto CUT_SCENE_02 = 39;
  static constexpr auto DEF_PARALYSIS = 17;

public:
  TheMountainThatStrides() : Sapphire::ScriptAPI::QuestBattleScript( 26 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.registerEObj( "Entrance", 2000182, 6228959, 5, { 457.583801f, 5.680784f, 280.512787f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "unknown_0", 2000608, 2807920, 4, { -95.322441f, -25.054260f, 61.518002f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheMountainThatStrides );