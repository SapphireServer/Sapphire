#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class JustDeserts : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_POP_01 = 4082418;
  static constexpr auto BNPC_NAME_01 = 750;
  static constexpr auto DEF_ACTION_SAND_BREATH = 445;
  static constexpr auto LOC_ACTOR1 = 1003064;
  static constexpr auto LOC_POS_ACTOR0 = 4126749;
  static constexpr auto LOC_POS_ACTOR1 = 4126755;
  static constexpr auto DEF_BLIND = 15;
  static constexpr auto CUT_SCENE_01 = 203;
  static constexpr auto LOC_TALKSHAPE1 = 8;

public:
  JustDeserts() : Sapphire::ScriptAPI::QuestBattleScript( 29 )
  { }

  void onInit( QuestBattle& instance ) override
  {

  }

  void onUpdate( QuestBattle& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( JustDeserts );