#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class SpiritholdBroken : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_POP_01 = 3869528;
  static constexpr auto LOC_POS_ACTOR0 = 3884691;
  static constexpr auto LOC_POS_ACTOR1 = 3884694;
  static constexpr auto LOC_ACTOR0 = 1003064;
  static constexpr auto BNPC_NAME_01 = 750;
  static constexpr auto DEF_ACTION_SAND_BREATH = 445;
  static constexpr auto DEF_BLIND = 15;
  static constexpr auto CUT_SCENE_01 = 69;
  static constexpr auto LOC_TALKSHAPE1 = 8;

public:
  SpiritholdBroken() : Sapphire::ScriptAPI::QuestBattleScript( 15 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.registerEObj( "unknown_0", 2005192, 5760474, 4, { -51.493111f, 0.309087f, 71.436897f }, 1.000000f, -0.000006f ); 

  }

  void onUpdate( QuestBattle& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( SpiritholdBroken );