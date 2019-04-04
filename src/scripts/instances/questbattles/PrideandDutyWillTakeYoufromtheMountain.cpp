#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class PrideandDutyWillTakeYoufromtheMountain : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_P_POP_SOLUKU_01 = 4299987;
  static constexpr auto INIT_POP_1_ADAMANT_01 = 4299990;
  static constexpr auto INIT_POP_1_ADAMANT_02 = 4299991;
  static constexpr auto INIT_POP_1_ADAMANT_03 = 4299992;
  static constexpr auto INIT_POP_2_ADAMANT_01 = 4299995;
  static constexpr auto INIT_POP_2_ADAMANT_02 = 4299997;
  static constexpr auto INIT_POP_2_JLYFISH_01 = 4299999;
  static constexpr auto INIT_POP_2_JLYFISH_02 = 4300001;
  static constexpr auto INIT_POP_2_JLYFISH_03 = 4300006;
  static constexpr auto INIT_POP_2_JLYFISH_04 = 4300007;
  static constexpr auto INIT_P_POP_KYURIOUS_01 = 4300008;
  static constexpr auto INIT_POP_3_ADAMANT_BOSS = 4300009;
  static constexpr auto INIT_POP_3_ADAMANT_01 = 4300010;
  static constexpr auto INIT_POP_3_ADAMANT_02 = 4300011;
  static constexpr auto INIT_POP_3_ADAMANT_03 = 4300012;
  static constexpr auto INIT_POP_3_ADAMANT_04 = 4300013;
  static constexpr auto INIT_POP_4_JLYFISH_01 = 4300014;
  static constexpr auto INIT_POP_4_JLYFISH_02 = 4300015;
  static constexpr auto INIT_POP_4_JLYFISH_03 = 4300016;
  static constexpr auto INIT_POP_4_JLYFISH_04 = 4300017;
  static constexpr auto INIT_POP_4_ELEMENT_01 = 4300018;
  static constexpr auto INIT_POP_4_ADAMANT_01 = 4300121;
  static constexpr auto INIT_POP_4_ADAMANT_02 = 4300122;
  static constexpr auto INIT_POP_4_ADAMANT_03 = 4300123;
  static constexpr auto LOC_ACTOR0 = 1007128;
  static constexpr auto LOC_ACTOR1 = 1002696;
  static constexpr auto LOC_POS_ACTOR0 = 4309208;
  static constexpr auto CUT_START_NCUT = 320;
  static constexpr auto CUT_INSART_NCUT = 321;
  static constexpr auto WARP_01 = 4332431;
  static constexpr auto INIT_P_POP_SOLUKU_02 = 4333234;

public:
  PrideandDutyWillTakeYoufromtheMountain() : Sapphire::ScriptAPI::QuestBattleScript( 66 )
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

EXPOSE_SCRIPT( PrideandDutyWillTakeYoufromtheMountain );