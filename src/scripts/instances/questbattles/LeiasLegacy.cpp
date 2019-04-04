#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class LeiasLegacy : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_POP_01 = 2319770;
  static constexpr auto INIT_POP_02 = 2319771;
  static constexpr auto INIT_POP_03 = 2319772;
  static constexpr auto INIT_POP_04 = 2319773;
  static constexpr auto INIT_EO_POP_01 = 3867263;
  static constexpr auto LOC_ACTOR0 = 1003008;
  static constexpr auto LOC_ACTOR1 = 1000816;
  static constexpr auto LOC_ACTOR2 = 1003016;
  static constexpr auto LOC_ACTOR3 = 1003017;
  static constexpr auto LOC_ACTOR4 = 1003018;
  static constexpr auto INIT_P_POP_KUPURU_KOPO = 4097283;
  static constexpr auto DEF_ACTION_WS_CRITICAL_LANCER = 477;
  static constexpr auto INIT_EN_POP_01 = 4107577;

public:
  LeiasLegacy() : Sapphire::ScriptAPI::QuestBattleScript( 14 )
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

EXPOSE_SCRIPT( LeiasLegacy );