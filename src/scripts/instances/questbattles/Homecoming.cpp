#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class Homecoming : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_POP_01 = 3777844;
  static constexpr auto LOC_POS_FIRST = 3867063;
  static constexpr auto INIT_POP_02 = 3906824;
  static constexpr auto INIT_POP_03 = 3906825;
  static constexpr auto BNPC_001 = 539;
  static constexpr auto LOC_ACTOR0 = 1000199;

public:
  Homecoming() : Sapphire::ScriptAPI::QuestBattleScript( 4 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.registerEObj( "unknown_0", 2005192, 5760474, 4, { -51.493111f, 0.309087f, 71.436897f }, 1.000000f, -0.000006f ); 

  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( Homecoming );