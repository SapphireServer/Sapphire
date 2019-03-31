#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class DivineIntervention : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto BNPC_COMPANION_ALPHINAUD = 5853419;
  static constexpr auto BNPC_ENEMY_GRINNAUX = 5853420;
  static constexpr auto BNPC_ENEMY_PAULECRAIN = 5853421;
  static constexpr auto BNPC_VFX_CHAIN_01 = 5853427;
  static constexpr auto BNPC_VFX_ELECTRON_01 = 5853422;
  static constexpr auto BNPC_VFX_ELECTRON_02 = 5853423;
  static constexpr auto BNPC_VFX_ELECTRON_03 = 5853424;
  static constexpr auto BNPC_VFX_ELECTRON_04 = 5853425;
  static constexpr auto BNPC_TOUMEI_PLAYER = 5853426;
  static constexpr auto BNPC_VFX_ELECTRON_06 = 5927949;
  static constexpr auto BNPC_VFX_ELECTRON_07 = 5927950;
  static constexpr auto BNPC_VFX_ELECTRON_08 = 5927951;
  static constexpr auto BNPC_VFX_ELECTRON_09 = 5927952;
  static constexpr auto INIT_ENPC_TATARU = 5853510;
  static constexpr auto QIB_YELL_01 = 2582;
  static constexpr auto CUT_SCENE_N_01 = 796;
  static constexpr auto STATUS_FETTERS = 667;
  static constexpr auto STATUS_PARAM_FETTERS = 1433;
  static constexpr auto CHANNELING_CHAIN = 10;
  static constexpr auto DEF_ACTION_CHAIN_GANG = 3991;
  static constexpr auto DEF_ACTION_LIGHTENING = 3992;
  static constexpr auto LOC_POS_ACTOR0 = 5908213;
  static constexpr auto LOC_POS_ACTOR1 = 5908214;
  static constexpr auto LOC_POS_ACTOR2 = 5908215;
  static constexpr auto LOC_POS_ACTOR3 = 5908216;
  static constexpr auto LOC_POS_ACTOR4 = 5908217;
  static constexpr auto LOC_POS_ACTOR5 = 5908218;
  static constexpr auto LOC_POS_ACTOR6 = 5908219;
  static constexpr auto LOC_ACTOR0 = 1008181;
  static constexpr auto LOC_ACTOR1 = 1012189;
  static constexpr auto LOC_ACTOR2 = 1012465;
  static constexpr auto LOC_ACTOR3 = 1012466;
  static constexpr auto LOC_ACTOR4 = 1012467;
  static constexpr auto LOC_ACTOR5 = 1012468;
  static constexpr auto LOC_ACTOR6 = 1012469;
  static constexpr auto ACTION_TIMELIN_EVENT_BASE_KNEE_SUFFERING = 936;
  static constexpr auto ACTION_TIMELIN_EVENT_BASE_FRIGHTENED3 = 4215;
  static constexpr auto ACTION_TIMELIN_EVENT_BASE_CHAIR_SIT = 788;
  static constexpr auto LOC_POS_CAM0 = 5908250;
  static constexpr auto BNPCBASE_CHAIN = 4140;
  static constexpr auto BNPCBASE_ELECTRON = 3780;

public:
  DivineIntervention() : Sapphire::ScriptAPI::QuestBattleScript( 105 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.registerEObj( "unknown_0", 2006981, 5656867, 4, { 0.000000f, 0.000000f, -15.851080f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( QuestBattle& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( DivineIntervention );