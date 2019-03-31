#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class EveryLittleThingSheDoesIsMagitek : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_P_POP_01 = 4277157;
  static constexpr auto INIT_P_POP_02 = 4277164;
  static constexpr auto INIT_POP_1ST_01 = 4277127;
  static constexpr auto INIT_POP_1ST_02 = 4277134;
  static constexpr auto INIT_POP_1ST_03 = 4277135;
  static constexpr auto INIT_POP_1ST_04 = 4277136;
  static constexpr auto INIT_ENPC_01 = 4277249;
  static constexpr auto INIT_ENPC_02 = 4277250;
  static constexpr auto CUT_SCENE_01 = 256;
  static constexpr auto CUT_SCENE_02 = 257;

public:
  EveryLittleThingSheDoesIsMagitek() : Sapphire::ScriptAPI::QuestBattleScript( 64 )
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

EXPOSE_SCRIPT( EveryLittleThingSheDoesIsMagitek );