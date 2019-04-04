#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class FiveEasyPieces : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_POP_BOSS = 4268988;
  static constexpr auto INIT_POP_1ST_A_01 = 4268991;
  static constexpr auto INIT_POP_1ST_B_01 = 4268992;
  static constexpr auto INIT_POP_1ST_C_01 = 4268993;
  static constexpr auto INIT_POP_1ST_D_01 = 4268994;
  static constexpr auto INIT_POP_2ND_ENERGIE_01 = 4269009;
  static constexpr auto INIT_P_POP_FOR_BUFF_ACTION = 4307688;
  static constexpr auto POP_RANGE_ENEMY_MOVE_01 = 4269001;
  static constexpr auto LOGMESSAGE_QIB_01 = 3203;
  static constexpr auto LOGMESSAGE_QIB_02 = 3213;
  static constexpr auto DEF_ACTION_ENERGY_SUMMON = 1094;
  static constexpr auto DEF_ACTION_CHACKRA = 1310;
  static constexpr auto CUT_START_NCUT = 340;
  static constexpr auto CUT_END_NCUT = 341;
  static constexpr auto JOB_STORY_MES = 3626;

public:
  FiveEasyPieces() : Sapphire::ScriptAPI::QuestBattleScript( 71 )
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

EXPOSE_SCRIPT( FiveEasyPieces );