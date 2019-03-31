#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class BringingDowntheMountain : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_P_POP_1ST_01 = 4127474;
  static constexpr auto INIT_P_POP_1ST_02 = 4127475;
  static constexpr auto INIT_POP_BOSS_01 = 4127476;
  static constexpr auto INIT_POP_1ST_01 = 4127477;
  static constexpr auto INIT_POP_1ST_02 = 4127478;
  static constexpr auto INIT_POP_1ST_03 = 4127479;
  static constexpr auto INIT_POP_1ST_04 = 4127480;
  static constexpr auto INIT_POP_1ST_05 = 4127481;
  static constexpr auto INIT_POP_1ST_06 = 4127482;
  static constexpr auto INIT_POP_2ST_01 = 4127485;
  static constexpr auto INIT_POP_2ST_02 = 4127486;
  static constexpr auto INIT_POP_2ST_03 = 4127487;
  static constexpr auto INIT_POP_2ST_04 = 4127488;
  static constexpr auto INIT_POP_2ST_05 = 4127489;
  static constexpr auto INIT_POP_2ST_06 = 4127490;
  static constexpr auto INIT_POP_3ST_01 = 4127491;
  static constexpr auto INIT_POP_3ST_02 = 4127492;
  static constexpr auto INIT_POP_3ST_03 = 4127493;
  static constexpr auto INIT_POP_3ST_04 = 4127494;
  static constexpr auto INIT_POP_3ST_05 = 4127495;
  static constexpr auto INIT_POP_3ST_06 = 4127496;
  static constexpr auto STATUS_HAELED_DOWN = 172;
  static constexpr auto CUT_SCENE_01 = 41;
  static constexpr auto CUT_SCENE_02 = 42;

public:
  BringingDowntheMountain() : Sapphire::ScriptAPI::QuestBattleScript( 28 )
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

EXPOSE_SCRIPT( BringingDowntheMountain );