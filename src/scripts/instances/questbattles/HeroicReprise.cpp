#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class HeroicReprise : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto BNPC_FRAY = 5891995;
  static constexpr auto BNPC_RESCUE_01 = 5891996;
  static constexpr auto BNPC_RESCUE_02 = 5891997;
  static constexpr auto BNPC_RESCUE_03 = 5891999;
  static constexpr auto BNPC_DIR_DUMMY_01 = 5927524;
  static constexpr auto BNPC_DIR_DUMMY_02 = 5927525;
  static constexpr auto BNPC_DIR_DUMMY_03 = 5927526;
  static constexpr auto BNPC_P1_LNC_01 = 5892007;
  static constexpr auto BNPC_P1_LNC_02 = 5892008;
  static constexpr auto BNPC_P1_LNC_03 = 5892011;
  static constexpr auto BNPC_P1_LNC_04 = 5892012;
  static constexpr auto BNPC_P1_LNC_05 = 5892013;
  static constexpr auto BNPC_P1_LNC_06 = 5892014;
  static constexpr auto BNPC_P1_THM_01 = 5892010;
  static constexpr auto BNPC_P1_THM_02 = 5892015;
  static constexpr auto BNPC_P2_LNC_01 = 5892058;
  static constexpr auto BNPC_P2_LNC_02 = 5892059;
  static constexpr auto BNPC_P2_LNC_03 = 5892062;
  static constexpr auto BNPC_P2_LNC_04 = 5892065;
  static constexpr auto BNPC_P2_THM_01 = 5892063;
  static constexpr auto BNPC_P2_THM_02 = 5892066;
  static constexpr auto BNPC_P2_DRAKE_01 = 5892060;
  static constexpr auto BNPC_P2_DRAKE_02 = 5892064;
  static constexpr auto BNPC_P2_DRAKE_03 = 5892067;
  static constexpr auto BNPC_P3_DRAKE_01 = 5892079;
  static constexpr auto BNPC_P3_DRAKE_02 = 5892080;
  static constexpr auto BNPC_P3_PGL_01 = 5892085;
  static constexpr auto BNPC_P2_GOAL_01 = 5892087;
  static constexpr auto BNPC_P2_GOAL_01_02 = 5927597;
  static constexpr auto BNPC_P2_GOAL_01_03 = 5927598;
  static constexpr auto BNPC_P3_GOAL = 5892088;
  static constexpr auto EOBJ_RESCUE = 5892004;
  static constexpr auto ACTION_GOAL_TRIGER = 3269;
  static constexpr auto ACTION_YELL_TRIGER = 4777;
  static constexpr auto EVENTACTION_RESCUE = 39;
  static constexpr auto YELL_RESCUE_01 = 2669;
  static constexpr auto YELL_RESCUE_02 = 2670;
  static constexpr auto YELL_RESCUE_03 = 2673;
  static constexpr auto YELL_RESCUE_04 = 3065;
  static constexpr auto YELL_AMALJA_01 = 2671;
  static constexpr auto YELL_AMALJA_02 = 2672;

public:
  HeroicReprise() : Sapphire::ScriptAPI::QuestBattleScript( 136 )
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

EXPOSE_SCRIPT( HeroicReprise );