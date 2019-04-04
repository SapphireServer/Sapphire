#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class ForgottenbutNotGone : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_P_POP_ARUKA_01 = 4304120;
  static constexpr auto INIT_POP_1_THM_ZOKU_01 = 4304111;
  static constexpr auto INIT_POP_1_LNC_ZOKU_01 = 4304112;
  static constexpr auto INIT_POP_1_LNC_ZOKU_02 = 4304113;
  static constexpr auto INIT_POP_2_EXC_ZOKU_01 = 4304114;
  static constexpr auto INIT_POP_2_LNC_ZOKU_01 = 4304115;
  static constexpr auto INIT_POP_2_THM_ZOKU_01 = 4304116;
  static constexpr auto INIT_POP_3_LNC_ZOKU_01 = 4304117;
  static constexpr auto INIT_POP_3_EXC_ZOKU_01 = 4304118;
  static constexpr auto INIT_POP_3_GLA_ZOKU_01 = 4304119;
  static constexpr auto POP_EVENT_RANGE_01 = 4304405;
  static constexpr auto POP_EVENT_RANGE_02 = 4304406;
  static constexpr auto POP_EVENT_RANGE_03 = 4304410;
  static constexpr auto EOBJ_BOX = 4305018;
  static constexpr auto EVENT_ACTION_01 = 2;
  static constexpr auto YELL_QIB_01 = 1246;
  static constexpr auto YELL_QIB_02 = 1247;
  static constexpr auto YELL_QIB_03 = 1248;
  static constexpr auto POP_RANGE_ALKAZOLKA_MOVE = 4308993;
  static constexpr auto CUT_END_NCUT = 357;
  static constexpr auto EOBJ_BOX_TARGET = 4322850;

public:
  ForgottenbutNotGone() : Sapphire::ScriptAPI::QuestBattleScript( 83 )
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

EXPOSE_SCRIPT( ForgottenbutNotGone );