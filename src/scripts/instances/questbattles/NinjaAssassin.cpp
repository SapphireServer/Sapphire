#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class NinjaAssassin : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto BNPC_OBORO_01 = 5886273;
  static constexpr auto BNPC_P1_YAMININ_01 = 5886266;
  static constexpr auto BNPC_P1_NIN_01 = 5886267;
  static constexpr auto BNPC_P1_NIN_02 = 5886268;
  static constexpr auto BNPC_P2_SUMMON_01 = 5886270;
  static constexpr auto BNPC_P2_SUMMON_02 = 5886272;
  static constexpr auto BNPC_P2_KOUMORI_01 = 5887414;
  static constexpr auto BNPC_P2_KOUMORI_02 = 5887415;
  static constexpr auto PR_P2_MOVE_TARGET_YAMININ_01 = 5891769;
  static constexpr auto EOBJ_MAKIBISHI = 5891770;
  static constexpr auto STATUS_MAKIBISHI_DAMAGE = 1221;
  static constexpr auto DEF_ACTION_MAKIBISHI = 3196;
  static constexpr auto POPTIME_KOUMORI = 30;
  static constexpr auto LCUT_ACTOR0 = 1013849;
  static constexpr auto LCUT_ACTOR1 = 1014669;
  static constexpr auto LCUT_ACTOR2 = 1014670;
  static constexpr auto LCUT_POS_ACTOR0 = 5917728;
  static constexpr auto LCUT_BGM0 = 107;

public:
  NinjaAssassin() : Sapphire::ScriptAPI::QuestBattleScript( 124 )
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

EXPOSE_SCRIPT( NinjaAssassin );