#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class IntoaCopperHell : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_POP_A = 4094987;
  static constexpr auto INIT_POP_B = 4094990;
  static constexpr auto INIT_POP_C = 4094992;
  static constexpr auto CUT_SCENE_01 = 76;
  static constexpr auto CUT_SCENE_02 = 77;
  static constexpr auto CUT_SCENE_03 = 78;
  static constexpr auto LOC_ACTOR0 = 1005138;
  static constexpr auto LOC_ACTOR1 = 1004748;
  static constexpr auto LOC_ACTOR2 = 1004749;
  static constexpr auto LOC_ACTOR3 = 1005117;
  static constexpr auto LOC_ACTOR4 = 1005119;
  static constexpr auto LOC_ACTOR5 = 1005120;
  static constexpr auto LOC_ACTOR8 = 1004653;
  static constexpr auto LOC_ACTOR9 = 1004654;
  static constexpr auto LOC_POS_ACTOR0 = 4176169;
  static constexpr auto LOC_POS_ACTOR1 = 4176170;
  static constexpr auto LOC_POS_ACTOR2 = 4176171;
  static constexpr auto LOC_FACE0 = 604;
  static constexpr auto LOC_FACE1 = 617;
  static constexpr auto LOC_FACE2 = 620;
  static constexpr auto LOC_FACE3 = 605;
  static constexpr auto LOC_FACE4 = 611;

public:
  IntoaCopperHell() : Sapphire::ScriptAPI::QuestBattleScript( 44 )
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

EXPOSE_SCRIPT( IntoaCopperHell );