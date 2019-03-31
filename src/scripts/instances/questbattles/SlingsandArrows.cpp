#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class SlingsandArrows : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto ENPC_HINT_01 = 5901612;
  static constexpr auto ENPC_HINT_02 = 5901615;
  static constexpr auto ENPC_FAKE_LUNA_A = 5901619;
  static constexpr auto ENPC_FAKE_LUNA_B = 5901620;
  static constexpr auto ENPC_FAKE_LUNA_C = 5901621;
  static constexpr auto ENPC_TRUE_LUNA = 5901622;
  static constexpr auto EOBJ_HINT_01 = 5901646;
  static constexpr auto EOBJ_HINT_02 = 5901650;
  static constexpr auto EOBJ_FAKE_LUNA_A = 5901653;
  static constexpr auto EOBJ_FAKE_LUNA_B = 5901657;
  static constexpr auto EOBJ_TRUE_LUNA = 5901659;
  static constexpr auto EOBJ_FAKE_LUNA_C = 5901660;
  static constexpr auto P_BNPC_SEBAS_SEARCH_01 = 5901666;
  static constexpr auto BNPC_FAKE_LUNA_A = 5901667;
  static constexpr auto BNPC_FAKE_LUNA_B = 5901686;
  static constexpr auto BNPC_FAKE_LUNA_C = 5901687;
  static constexpr auto P_BNPC_TRUE_LUNA_SEARCH_01 = 5901688;
  static constexpr auto BNPC_WAVE01_BOSS_01 = 5901694;
  static constexpr auto BNPC_WAVE01_MRD_01 = 5901711;
  static constexpr auto BNPC_WAVE01_PGL_01 = 5901712;
  static constexpr auto BNPC_WAVE01_PGL_02 = 5901713;
  static constexpr auto MOVE_BOSS_POINT_01 = 5901717;
  static constexpr auto P_BNPC_LUNA_BOSSBATTLE_01 = 5901722;
  static constexpr auto P_BNPC_SEBAS_BOSSBATTLE_01 = 5901726;
  static constexpr auto PR_POINT_BOSSBATTLE_01 = 5901727;
  static constexpr auto BNPC_WAVE02_CNJ_01 = 5901733;
  static constexpr auto BNPC_WAVE02_PGL_01 = 5901734;
  static constexpr auto BNPC_WAVE02_PGL_02 = 5901735;
  static constexpr auto BNPC_WAVE02_LNC_01 = 5901737;
  static constexpr auto BNPC_WAVE02_LNC_02 = 5901738;
  static constexpr auto BNPC_ADD_CAR_01 = 5901740;
  static constexpr auto P_BNPC_BROENBHAR_01 = 5901799;
  static constexpr auto P_BNPC_VKEBBE_01 = 5901801;
  static constexpr auto EVENT_ACTION_01 = 45;
  static constexpr auto YELL_QIB_HINT_01 = 2684;
  static constexpr auto YELL_QIB_HINT_02 = 2685;
  static constexpr auto YELL_QIB_FAKE_LUNA_A_01 = 2686;
  static constexpr auto YELL_QIB_CARK_SEBAS_01 = 2687;
  static constexpr auto YELL_QIB_W_LUNA_SEBAS_01 = 2689;
  static constexpr auto YELL_QIB_FAKE_LUNA_C_01 = 2690;
  static constexpr auto YELL_QIB_TRUE_LUNA_01 = 2691;
  static constexpr auto MOVE_FAKELUNA_B_POINT_01 = 5904735;
  static constexpr auto BEHAVIOR_SQUAT = 30405;
  static constexpr auto BEHAVIOR_NORMAL = 30064;
  static constexpr auto BEHAVIOR_FRIGHT = 30488;
  static constexpr auto ER_RECT_01 = 5906002;
  static constexpr auto ER_RECT_02 = 5917465;
  static constexpr auto MOVE_BATTLE_END_POINT_01 = 5906882;
  static constexpr auto NCUT_01 = 983;
  static constexpr auto NCUT_02 = 984;
  static constexpr auto EVENT_ACTION_02 = 15;
  static constexpr auto MOVE_FAKELUNA_C_POINT_01 = 5905958;
  static constexpr auto BGM_BATTLE = 39;
  static constexpr auto ACTION_SUMMON = 1307;
  static constexpr auto LOC_ACTOR_REYNER = 1003835;
  static constexpr auto LOC_ACTOR_CARVA = 1010427;
  static constexpr auto LOC_ACTOR_LEVE = 1014684;
  static constexpr auto LOC_ACTOR_QUIMP = 1014685;
  static constexpr auto LOC_LEVEL_CARVA = 5927599;
  static constexpr auto LOC_POINT_LEVE = 5927505;
  static constexpr auto LOC_POINT_END = 5927507;
  static constexpr auto LOC_ACTOR_CELIE = 1014690;
  static constexpr auto LOC_ACTION_BASE_01 = 981;
  static constexpr auto LOC_ACTION_BASE_02 = 936;
  static constexpr auto LOC_ACTOR_PIR_01 = 1015155;
  static constexpr auto LOC_ACTOR_PIR_02 = 1015156;
  static constexpr auto LOC_ACTOR_PIR_03 = 1015157;
  static constexpr auto BEHAVIOR_TALK = 30085;
  static constexpr auto LOC_POINT_2ND_START = 5958830;
  static constexpr auto LOC_LOG_MES_WIND = 5343;
  static constexpr auto BNPC_BASE_CARBUNCLE = 4770;
  static constexpr auto ACTION_TIMELINE_FACIAL_COMEON = 608;
  static constexpr auto ACTION_TIMELINE_EVENT_BASE_BAD_STAND = 827;
  static constexpr auto LOC_ACTOR0 = 1005093;
  static constexpr auto LOC_ACTOR1 = 1005094;
  static constexpr auto ACTION_TIMELINE_EVENT_SIGH = 4229;

public:
  SlingsandArrows() : Sapphire::ScriptAPI::QuestBattleScript( 144 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.registerEObj( "Companychest", 2000470, 4255757, 4, { 90.371834f, 41.346722f, 60.735680f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Huntboard", 2004438, 4887771, 4, { 94.366341f, 40.247021f, 60.480110f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( QuestBattle& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( SlingsandArrows );