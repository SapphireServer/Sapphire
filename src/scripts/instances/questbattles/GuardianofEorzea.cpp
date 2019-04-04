#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class GuardianofEorzea : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_POP_1ST_01 = 4755440;
  static constexpr auto INIT_POP_2ST_01 = 4755441;
  static constexpr auto INIT_ENPC_01 = 4759673;
  static constexpr auto INIT_ENPC_02 = 4759674;
  static constexpr auto INIT_ENPC_03 = 4759676;
  static constexpr auto INIT_ENPC_04 = 4759677;
  static constexpr auto QIB_YELL_01 = 2240;
  static constexpr auto QIB_YELL_02 = 2241;
  static constexpr auto QIB_YELL_03 = 2242;
  static constexpr auto INIT_ENPC_05 = 4759678;
  static constexpr auto INIT_ENPC_06 = 4759679;
  static constexpr auto INIT_ENPC_07 = 4868546;
  static constexpr auto CUT_SCENE_01 = 580;
  static constexpr auto LOC_ACTOR0 = 1009412;
  static constexpr auto LOC_ACTOR1 = 1009413;
  static constexpr auto LOC_ACTOR2 = 1009688;
  static constexpr auto LOC_ACTOR3 = 1009689;
  static constexpr auto LOC_ACTOR4 = 1008176;
  static constexpr auto LOC_ACTOR5 = 1008178;
  static constexpr auto LOC_ACTOR6 = 1009690;
  static constexpr auto LOC_ACTOR7 = 1009691;
  static constexpr auto LOC_POS_ACTOR0 = 4887579;
  static constexpr auto LOC_POS_ACTOR1 = 4887580;
  static constexpr auto ACTION_TIMELINE_FACIAL_COMEON = 608;
  static constexpr auto ACTION_TIMELINE_EVENT_BASE_IDLE4 = 787;

public:
  GuardianofEorzea() : Sapphire::ScriptAPI::QuestBattleScript( 89 )
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

EXPOSE_SCRIPT( GuardianofEorzea );