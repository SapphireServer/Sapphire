#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class SweetSorrows : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_POP_1TEAM_DOL_01 = 5047099;
  static constexpr auto INIT_POP_1TEAM_PGL_01 = 5047100;
  static constexpr auto INIT_POP_1TEAM_PGL_02 = 5047101;
  static constexpr auto INIT_POP_2TEAM_DOL_01 = 5047777;
  static constexpr auto INIT_POP_2TEAM_PGL_01 = 5047778;
  static constexpr auto INIT_POP_2TEAM_PGL_02 = 5047779;
  static constexpr auto INIT_POP_3TEAM_BOS_01 = 5047780;
  static constexpr auto INIT_POP_3TEAM_DOL_01 = 5047781;
  static constexpr auto INIT_POP_4TEAM_PGL_01 = 5047783;
  static constexpr auto INIT_POP_4TEAM_BOS_01 = 5047784;
  static constexpr auto INIT_POP_4TEAM_DOL_01 = 5047785;
  static constexpr auto INIT_P_POP_3TEAM_MAS_01 = 5047794;
  static constexpr auto QIB_YELL_01 = 2342;
  static constexpr auto ER_RECT_01 = 5105432;
  static constexpr auto ER_RECT_02 = 5105644;
  static constexpr auto ER_RECT_03 = 5106084;
  static constexpr auto INIT_ENPC_MERCHANT = 5053598;
  static constexpr auto LCUT_ACTOR0 = 1010200;
  static constexpr auto LCUT_ACTOR1 = 1010202;
  static constexpr auto LCUT_ACTOR2 = 1010256;
  static constexpr auto LCUT_ACTOR3 = 1010257;
  static constexpr auto LCUT_ACTOR4 = 1010258;
  static constexpr auto LCUT_ACTOR5 = 1010259;
  static constexpr auto LCUT_ACTOR6 = 1010260;
  static constexpr auto LCUT_ACTOR7 = 1010532;
  static constexpr auto LCUT_ACTOR8 = 1010204;
  static constexpr auto LCUT_POS0 = 5109470;
  static constexpr auto LCUT_POS1 = 5110383;
  static constexpr auto LCUT_POS2 = 5047099;
  static constexpr auto LCUT_POS3 = 5047100;
  static constexpr auto LCUT_POS4 = 5047101;
  static constexpr auto LCUT_POS5 = 5053597;
  static constexpr auto LCUT_POS6 = 5053598;
  static constexpr auto LCUT_ACTION0 = 1014;
  static constexpr auto LCUT_ACTION1 = 808;
  static constexpr auto LCUT_FACE0 = 607;
  static constexpr auto LCUT_BGM1 = 78;
  static constexpr auto LCUT_BGM2 = 86;
  static constexpr auto STATUS_PARM_HIDDEN_FOR_BNPC = 1197;

public:
  SweetSorrows() : Sapphire::ScriptAPI::QuestBattleScript( 94 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.registerEObj( "unknown_0", 2009569, 0, 4, { 763.213318f, 9.000000f, 358.016998f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_1", 2009570, 0, 4, { 748.506775f, 9.000000f, 520.002930f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( SweetSorrows );