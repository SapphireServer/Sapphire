#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class MyFirstMudra : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_ENPC_01 = 5032993;
  static constexpr auto INIT_ENPC_02 = 5032994;
  static constexpr auto INIT_POP_OBORO_01 = 5032995;
  static constexpr auto INIT_POP_ONIBI_1_01 = 5032996;
  static constexpr auto INIT_POP_ONIBI_1_02 = 5032997;
  static constexpr auto INIT_POP_ONIBI_1_03 = 5032998;
  static constexpr auto INIT_POP_ONIBI_1_04 = 5032999;
  static constexpr auto INIT_POP_ONIBI_1_05 = 5033000;
  static constexpr auto INIT_POP_ONIBI_1_06 = 5033001;
  static constexpr auto INIT_POP_TOAD_01 = 5033011;
  static constexpr auto INIT_POP_ONIBI_2_01 = 5033002;
  static constexpr auto INIT_POP_ONIBI_2_02 = 5033003;
  static constexpr auto INIT_POP_ONIBI_2_03 = 5033004;
  static constexpr auto INIT_POP_ONIBI_2_04 = 5033005;
  static constexpr auto INIT_POP_ONIBI_2_05 = 5033006;
  static constexpr auto INIT_POP_ONIBI_2_06 = 5033007;
  static constexpr auto INIT_POP_ONIBI_3_01 = 5033008;
  static constexpr auto INIT_POP_ONIBI_3_02 = 5033009;
  static constexpr auto INIT_POP_ONIBI_3_03 = 5033010;
  static constexpr auto PC_ACTION_FUUMA = 2265;
  static constexpr auto QIB_YELL_01 = 2346;

public:
  MyFirstMudra() : Sapphire::ScriptAPI::QuestBattleScript( 96 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.registerEObj( "unknown_0", 2009569, 0, 4, { 763.213318f, 9.000000f, 358.016998f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_1", 2009570, 0, 4, { 748.506775f, 9.000000f, 520.002930f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( MyFirstMudra );