#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class OneAutumnsSecret : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto P_BNPC_COMPANION_SANSON = 6873346;
  static constexpr auto P_BNPC_COMPANION_GUYDELOT = 6873347;
  static constexpr auto BNPC_ENEMY_NOURVAL = 6873349;
  static constexpr auto BNPC_ENEMY_BUKA_SPEAR_01_01 = 6873351;
  static constexpr auto BNPC_ENEMY_BUKA_BOW_01_01 = 6873352;
  static constexpr auto BNPC_ENEMY_BUKA_SPEAR_02_01 = 6873353;
  static constexpr auto BNPC_ENEMY_BUKA_SPEAR_02_02 = 6894649;
  static constexpr auto BNPC_ENEMY_BUKA_BOW_02_01 = 6894652;
  static constexpr auto BNPC_ENEMY_BUKA_BOW_02_02 = 6894665;
  static constexpr auto BNPC_ENEMY_BUKA_SPEAR_03_01 = 6894671;
  static constexpr auto BNPC_ENEMY_BUKA_SPEAR_03_02 = 6894673;
  static constexpr auto BNPC_ENEMY_BUKA_SPEAR_03_03 = 6894677;
  static constexpr auto BNPC_ENEMY_BUKA_BOW_03_01 = 6894682;
  static constexpr auto BNPC_ENEMY_BUKA_BOW_03_02 = 6894687;
  static constexpr auto BNPC_ENEMY_BUKA_BOW_03_03 = 6894689;
  static constexpr auto BNPC_ENEMY_BUKA_BOW_03_04 = 6894691;
  static constexpr auto PR_MOVE_NOURVAL = 6894697;
  static constexpr auto PR_MOVE_GUYDELOT_START = 6895519;
  static constexpr auto PR_MOVE_SANSON_START = 6895526;
  static constexpr auto YELL_QIB_NOURVAL_START = 4845;
  static constexpr auto YELL_QIB_BUKA_START = 4846;
  static constexpr auto DEF_ACTION_EARTH_WAVE = 8735;
  static constexpr auto DEF_ACTION_EARTH_WAVE_TOUMEI_END = 8734;
  static constexpr auto BNPC_TOUMEI_ACTION_NOURVAL = 6901397;
  static constexpr auto BNPC_TOUMEI_SCAPEGOAT = 6906140;
  static constexpr auto BEHAVIOR_ACTION_01 = 30073;
  static constexpr auto BEHAVIOR_ACTION_02 = 30082;
  static constexpr auto BEHAVIOR_ACTION_03 = 30940;
  static constexpr auto BEHAVIOR_ACTION_04 = 30943;
  static constexpr auto BEHAVIOR_ACTION_05 = 30944;
  static constexpr auto BGM_NO_MUSIC = 1;
  static constexpr auto BGM_JOB_SHIREN = 91;

public:
  OneAutumnsSecret() : Sapphire::ScriptAPI::QuestBattleScript( 174 )
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

EXPOSE_SCRIPT( OneAutumnsSecret );