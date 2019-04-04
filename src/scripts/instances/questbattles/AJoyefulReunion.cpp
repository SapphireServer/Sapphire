#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class AJoyefulReunion : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto BNPC_CELESTAUX = 5873785;
  static constexpr auto BNPC_HAILLENARTE_01 = 5873786;
  static constexpr auto BNPC_HAILLENARTE_02 = 5873787;
  static constexpr auto BNPC_HAILLENARTE_03 = 5873788;
  static constexpr auto BNPC_HAILLENARTE_04 = 5873789;
  static constexpr auto BNPC_P1_ABIS_01 = 5873790;
  static constexpr auto BNPC_P1_ABIS_02 = 5873791;
  static constexpr auto BNPC_P1_ABIS_03 = 5873792;
  static constexpr auto BNPC_P1_ABIS_04 = 5873793;
  static constexpr auto BNPC_P1_ABIS_05 = 5873795;
  static constexpr auto BNPC_P1_RINGDRAGON_01 = 5873802;
  static constexpr auto BNPC_P1_DRAKE_01 = 5873794;
  static constexpr auto BNPC_P1_DRAKE_02 = 5873798;
  static constexpr auto BNPC_P1_DRAKE_03 = 5873799;
  static constexpr auto ENPC_ROSTNSTHAL = 5873783;
  static constexpr auto ENPC_BAURENDOUIN = 5873784;
  static constexpr auto YELL_CELESTAUX_DEAD = 2654;
  static constexpr auto YELL_HAILLENARTE_01_DEAD = 2655;
  static constexpr auto YELL_HAILLENARTE_02_DEAD = 2656;
  static constexpr auto YELL_HAILLENARTE_03_DEAD = 2657;
  static constexpr auto YELL_HAILLENARTE_04_DEAD = 2658;
  static constexpr auto LOC_MARKER_01 = 5934854;
  static constexpr auto LOC_ACTOR0 = 1014580;
  static constexpr auto LOC_ACTOR1 = 1015073;
  static constexpr auto CUT_SCENE_01 = 974;
  static constexpr auto LOC_BGM0 = 39;

public:
  AJoyefulReunion() : Sapphire::ScriptAPI::QuestBattleScript( 118 )
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

EXPOSE_SCRIPT( AJoyefulReunion );