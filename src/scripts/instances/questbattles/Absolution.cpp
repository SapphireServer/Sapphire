#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class Absolution : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto BNPC_RIELLE = 5892194;
  static constexpr auto BNPC_SIDURGU = 5892195;
  static constexpr auto BNPC_P1_YSTRIDE = 5892196;
  static constexpr auto BNPC_P1_GLA_A_01 = 5892197;
  static constexpr auto BNPC_P1_GLA_A_02 = 5892198;
  static constexpr auto BNPC_P1_GLA_A_03 = 5892199;
  static constexpr auto BNPC_P1_LNC_B_01 = 5892200;
  static constexpr auto BNPC_P1_PGL_A_01 = 5892201;
  static constexpr auto BNPC_P1_PGL_B_01 = 5892202;
  static constexpr auto BNPC_P2_ARC_B_01 = 5892203;
  static constexpr auto BNPC_P2_LNC_B_01 = 5892204;
  static constexpr auto BNPC_P2_PGL_A_01 = 5892205;
  static constexpr auto BNPC_P2_EXC_A_01 = 5892206;
  static constexpr auto BNPC_P3_ARC_A_01 = 5892207;
  static constexpr auto BNPC_P3_ARC_B_01 = 5892208;
  static constexpr auto BNPC_P3_PGL_A_01 = 5892209;
  static constexpr auto BNPC_P3_LNC_B_01 = 5892210;
  static constexpr auto BNPC_P3_GLA_A_01 = 5892211;
  static constexpr auto BNPC_P3_EXC_B_01 = 5892212;
  static constexpr auto BNPC_P4_GLA_READER = 5892213;
  static constexpr auto BNPC_P4_EXC_A_01 = 5892214;
  static constexpr auto BNPC_P4_EXC_B_01 = 5892215;
  static constexpr auto BNPC_P4_EXC_A_02 = 5892216;
  static constexpr auto BNPC_P4_LNC_B_01 = 5892217;
  static constexpr auto BNPC_P4_LNC_B_02 = 5892218;
  static constexpr auto BNPC_P4_ARC_B_01 = 5892219;
  static constexpr auto BNPC_P4_GLA_A_01 = 5892220;
  static constexpr auto BNPC_P4_GLA_B_01 = 5892221;
  static constexpr auto BNPC_P4_PGL_B_01 = 5892222;
  static constexpr auto BNPC_P4_LNC_A_01 = 5892223;
  static constexpr auto BNPC_P4_ARC_A_01 = 5892224;
  static constexpr auto BNPC_P4_ARC_B_02 = 5892225;
  static constexpr auto PR_P4_READER_MOVE = 5934824;
  static constexpr auto YELL_P4_GLA_READER_MOVEEND = 2728;
  static constexpr auto YELL_P4_GLA_READER_LOOP = 3589;
  static constexpr auto YELL_P4_GLA_READER_DEAD = 3342;
  static constexpr auto BGM_LASTHALF = 91;
  static constexpr auto LOC_ACTOR0 = 1014593;
  static constexpr auto LOC_ACTOR1 = 1015435;
  static constexpr auto LOC_ACTOR2 = 1014617;
  static constexpr auto LOC_ACTOR3 = 1015433;
  static constexpr auto LOC_ACTOR4 = 1015434;
  static constexpr auto LOC_MARKER_01 = 5959858;
  static constexpr auto CUT_SCENE_01 = 995;
  static constexpr auto BGM_0 = 317;
  static constexpr auto ACTION_GOAL_TRIGER1 = 3269;
  static constexpr auto ACTION_GOAL_TRIGER2 = 4777;

public:
  Absolution() : Sapphire::ScriptAPI::QuestBattleScript( 139 )
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

EXPOSE_SCRIPT( Absolution );