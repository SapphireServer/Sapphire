#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class BloodontheSands : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto BNPC_BOX_01 = 5867998;
  static constexpr auto BNPC_JOYE = 5868001;
  static constexpr auto BNPC_P1_CRAB_01 = 5868003;
  static constexpr auto BNPC_P1_CRAB_02 = 5868005;
  static constexpr auto BNPC_P1_CRAB_03 = 5868006;
  static constexpr auto BNPC_P1_CRAB_04 = 5868007;
  static constexpr auto BNPC_P1_CRAB_05 = 5868008;
  static constexpr auto BNPC_P2_CRAB_01 = 5868009;
  static constexpr auto BNPC_P2_CRAB_02 = 5868010;
  static constexpr auto BNPC_P2_CRAB_03 = 5868011;
  static constexpr auto BNPC_P2_KURAGE_01 = 5868012;
  static constexpr auto BNPC_P2_KURAGE_02 = 5868013;
  static constexpr auto BNPC_P2_KURAGE_03 = 5868014;
  static constexpr auto BNPC_P3_CRAB_01 = 5868015;
  static constexpr auto BNPC_P3_CRAB_02 = 5868018;
  static constexpr auto BNPC_P3_CRAB_03 = 5868019;
  static constexpr auto BNPC_P3_CRAB_04 = 5868020;
  static constexpr auto BNPC_P3_CRAB_05 = 5868022;
  static constexpr auto BNPC_P3_KURAGE_01 = 5868023;
  static constexpr auto BNPC_P3_KURAGE_02 = 5868024;
  static constexpr auto BNPC_P3_KURAGE_03 = 5868025;
  static constexpr auto BNPC_P3_KURAGE_04 = 5868026;
  static constexpr auto BNPC_P4_SUIRYU_01 = 5868028;
  static constexpr auto ENPC_ROSTNSTHAL = 5868079;
  static constexpr auto ENPC_STEPHANIVIEN = 5868080;
  static constexpr auto YELL_JOY_TRANCE_01 = 2663;
  static constexpr auto ACTION_JOY_TRANCE_01 = 4265;
  static constexpr auto LOC_MARKER_01 = 5927544;
  static constexpr auto LOC_ACTOR0 = 1014579;
  static constexpr auto LOC_ACTOR1 = 1014580;
  static constexpr auto LOC_ACTOR2 = 1015124;
  static constexpr auto LOC_BGM0 = 96;

public:
  BloodontheSands() : Sapphire::ScriptAPI::QuestBattleScript( 117 )
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

EXPOSE_SCRIPT( BloodontheSands );