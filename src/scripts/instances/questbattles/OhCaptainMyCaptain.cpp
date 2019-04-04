#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class OhCaptainMyCaptain : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_P_POP_01 = 4093947;
  static constexpr auto INIT_POP_01 = 4093955;
  static constexpr auto INIT_POP_02 = 4093957;
  static constexpr auto INIT_POP_03 = 4093961;
  static constexpr auto INIT_POP_04 = 4093962;
  static constexpr auto ACTOR20 = 1002058;
  static constexpr auto LOC_MARKER_01 = 4011232;
  static constexpr auto LOC_MARKER_02 = 4011233;
  static constexpr auto LOC_POS_CAM1 = 4011264;
  static constexpr auto LOC_MARKER_03 = 4011557;
  static constexpr auto LOC_MARKER_04 = 4011562;
  static constexpr auto ACTOR30 = 1004350;
  static constexpr auto LOC_MARKER_05 = 4012536;
  static constexpr auto LOC_MARKER_06 = 4012537;
  static constexpr auto LOC_MARKER_07 = 4012538;
  static constexpr auto LOC_MARKER_08 = 4012539;
  static constexpr auto ACTOR40 = 1001605;
  static constexpr auto LOC_ACTION1 = 961;
  static constexpr auto ACTOR50 = 1006164;
  static constexpr auto ACTOR60 = 1003810;
  static constexpr auto LOC_ACTION2 = 607;
  static constexpr auto LOC_ACTION3 = 617;
  static constexpr auto LOC_ACTION4 = 605;
  static constexpr auto LOC_MARKER_09 = 4096701;
  static constexpr auto LOC_MARKER_10 = 4096704;
  static constexpr auto DEF_ACTION_WS_CRITICAL_LANCER = 477;
  static constexpr auto LOC_ACTION5 = 618;
  static constexpr auto LOC_ACTION6 = 776;

public:
  OhCaptainMyCaptain() : Sapphire::ScriptAPI::QuestBattleScript( 39 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.registerEObj( "Exit", 2000605, 0, 4, { -715.942383f, 69.420113f, -830.370300f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_0", 2000606, 3861081, 4, { -670.462280f, 63.293751f, -801.510986f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Entrance", 2000604, 4262798, 5, { -677.634888f, 64.116386f, -803.174927f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 

  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( OhCaptainMyCaptain );