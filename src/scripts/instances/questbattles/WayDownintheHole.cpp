#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class WayDownintheHole : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_POP_01 = 3872242;
  static constexpr auto ACTOR0 = 1001578;
  static constexpr auto ACTOR1 = 1002947;
  static constexpr auto ACTOR2 = 1002948;
  static constexpr auto ACTOR3 = 1002949;
  static constexpr auto ACTOR4 = 1002950;
  static constexpr auto ACTOR5 = 1002951;
  static constexpr auto ACTOR6 = 1003028;
  static constexpr auto ACTOR7 = 1002952;
  static constexpr auto ACTOR8 = 1002953;
  static constexpr auto ACTOR9 = 1002954;
  static constexpr auto ACTOR10 = 1002956;
  static constexpr auto ACTOR11 = 1002957;
  static constexpr auto ACTOR12 = 1002958;
  static constexpr auto ACTOR13 = 1002959;
  static constexpr auto ACTOR14 = 1001353;
  static constexpr auto LOC_POS_ENPC1 = 3817003;
  static constexpr auto ACTOR15 = 1002990;
  static constexpr auto ACTOR16 = 1002991;
  static constexpr auto LOC_POS_ENPC2 = 3817009;
  static constexpr auto LOC_POS_ENPC3 = 3817004;
  static constexpr auto ACTOR17 = 1002992;
  static constexpr auto ACTOR6_POS = 3817007;
  static constexpr auto BNPC_NAME_01 = 750;
  static constexpr auto DEF_ACTION_SAND_BREATH = 445;
  static constexpr auto DEF_BLIND = 15;
  static constexpr auto CUT_SCENE_01 = 189;
  static constexpr auto LOC_ACTOR0 = 1003064;
  static constexpr auto LOC_POS_ENPC4 = 4163979;
  static constexpr auto LOC_POS_ENPC5 = 4163982;
  static constexpr auto LOC_TALKSHAPE1 = 8;
  static constexpr auto LOC_ACTOR1 = 1002947;

public:
  WayDownintheHole() : Sapphire::ScriptAPI::QuestBattleScript( 18 )
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

EXPOSE_SCRIPT( WayDownintheHole );