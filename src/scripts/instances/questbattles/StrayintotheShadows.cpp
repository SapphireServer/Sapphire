#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class StrayintotheShadows : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_POP_1ST_EXC_01 = 5032415;
  static constexpr auto INIT_POP_1ST_EXC_02 = 5032416;
  static constexpr auto INIT_POP_1ST_EXC_03 = 5032417;
  static constexpr auto INIT_POP_1ST_EXC_04 = 5032418;
  static constexpr auto INIT_POP_2ST_ARC_01 = 5032445;
  static constexpr auto INIT_POP_2ST_ARC_02 = 5032446;
  static constexpr auto INIT_POP_2ST_EXC_01 = 5032447;
  static constexpr auto BNPC_VK_BAIT_1 = 5032448;
  static constexpr auto INIT_POP_3ST_EXC_02 = 5032449;
  static constexpr auto INIT_POP_3ST_EXC_03 = 5032453;
  static constexpr auto INIT_POP_3ST_EXC_04 = 5032454;
  static constexpr auto INIT_POP_3ST_EXC_05 = 5032455;
  static constexpr auto INIT_POP_3ST_EXC_06 = 5032456;
  static constexpr auto INIT_POP_3ST_ARC_01 = 5032457;
  static constexpr auto BNPC_VK_BAIT_2 = 5032458;
  static constexpr auto INIT_POP_3ST_ARC_03 = 5032459;
  static constexpr auto INIT_POP_3ST_ARC_04 = 5032460;
  static constexpr auto INIT_POP_3ST_ARC_05 = 5032461;
  static constexpr auto INIT_POP_3ST_ARC_06 = 5032462;
  static constexpr auto INIT_POP_3ST_ARC_07 = 5032463;
  static constexpr auto INIT_POP_3ST_ARC_08 = 5032464;
  static constexpr auto INIT_P_POP_VAK_01 = 5032444;
  static constexpr auto INIT_ENPC_VAK_01 = 5032411;
  static constexpr auto INIT_ENPC_MAR_01 = 5032420;
  static constexpr auto INIT_ENPC_MAR_02 = 5032855;
  static constexpr auto INIT_ENPC_YEL_01 = 5032422;
  static constexpr auto INIT_POP_EOBJ_01 = 5032470;
  static constexpr auto EVENT_ACTION_01 = 32;
  static constexpr auto EVENT_ACTION_02 = 45;
  static constexpr auto ER_RECT_01 = 5038527;
  static constexpr auto BGM_LASTHALF = 39;
  static constexpr auto POP_RANGE_VAK_DEPOP = 5045483;
  static constexpr auto QIB_YELL_01 = 2319;
  static constexpr auto QIB_YELL_02 = 2378;
  static constexpr auto QIB_YELL_03 = 2379;
  static constexpr auto LCUT_ACTOR0 = 1010214;
  static constexpr auto LCUT_ACTOR1 = 1010215;
  static constexpr auto LCUT_ACTOR2 = 1010216;
  static constexpr auto LCUT_ACTOR3 = 1010217;
  static constexpr auto LCUT_POS0 = 5032420;
  static constexpr auto LCUT_POS1 = 5323061;
  static constexpr auto LCUT_POS2 = 5323062;
  static constexpr auto LCUT_POS3 = 5323066;
  static constexpr auto LCUT_FACE0 = 608;
  static constexpr auto INIT_POP_EOBJ_02 = 5323044;
  static constexpr auto STATUS_STEALTH = 1198;
  static constexpr auto WARP_01 = 5032443;

public:
  StrayintotheShadows() : Sapphire::ScriptAPI::QuestBattleScript( 90 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.registerEObj( "Companychest", 2000470, 4255817, 4, { -199.998505f, 17.071720f, 58.787498f }, 1.000000f, -0.402012f ); 

  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( StrayintotheShadows );