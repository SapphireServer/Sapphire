#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class ChoicesandPaths : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto BNPC_BOSS_01 = 6852479;
  static constexpr auto BNPC_ZAKO_PACK1_01 = 6852489;
  static constexpr auto BNPC_ZAKO_PACK1_02 = 6852490;
  static constexpr auto BNPC_ZAKO_PACK1_03 = 6852491;
  static constexpr auto BNPC_ZAKO_PACK1_04 = 6852492;
  static constexpr auto BNPC_ZAKO_PACK1_05 = 6865996;
  static constexpr auto BNPC_ZAKO_PACK1_06 = 6865997;
  static constexpr auto BNPC_ZAKO_PACK1_07 = 6865999;
  static constexpr auto BNPC_ZAKO_PACK2_01 = 6866000;
  static constexpr auto BNPC_ZAKO_PACK2_02 = 6866001;
  static constexpr auto BNPC_ZAKO_PACK2_03 = 6866003;
  static constexpr auto BNPC_ZAKO_PACK2_04 = 6866004;
  static constexpr auto BNPC_ZAKO_PACK2_05 = 6866005;
  static constexpr auto BNPC_ZAKO_PACK2_06 = 6866006;
  static constexpr auto BNPC_ZAKO_PACK2_07 = 6866007;
  static constexpr auto BNPC_ZAKO_PACK2_08 = 6866008;
  static constexpr auto BNPC_ZAKO_PACK2_09 = 6866009;
  static constexpr auto BNPC_ZAKO_PACK3_01 = 6866016;
  static constexpr auto BNPC_ZAKO_PACK3_02 = 6866018;
  static constexpr auto BNPC_ZAKO_PACK3_03 = 6866019;
  static constexpr auto BNPC_ZAKO_PACK3_04 = 6866022;
  static constexpr auto BNPC_ZAKO_PACK3_05 = 6866023;
  static constexpr auto BNPC_ZAKO_PACK3_06 = 6866025;
  static constexpr auto BNPC_ZAKO_PACK3_07 = 6866026;
  static constexpr auto BNPC_ZAKO_PACK3_08 = 6866027;
  static constexpr auto BNPC_ZAKO_PACK3_09 = 6866028;
  static constexpr auto EOBJ_FIRE_DAMAGE_AREA = 6866276;
  static constexpr auto STATUS_PARAM_FIRE_DAMAGE = 2917;
  static constexpr auto ACTION_DARK_FIRE_II = 2175;
  static constexpr auto LOCKON_BOSS_CHARGE = 30;
  static constexpr auto QIB_YELL_01 = 4528;
  static constexpr auto QIB_YELL_02 = 4529;
  static constexpr auto QIB_YELL_03 = 4530;
  static constexpr auto QIB_YELL_04 = 4531;
  static constexpr auto QIB_YELL_05 = 4532;
  static constexpr auto QIB_YELL_06 = 4533;
  static constexpr auto ACTION_HEWERALD_CHARGE = 8305;

public:
  ChoicesandPaths() : Sapphire::ScriptAPI::QuestBattleScript( 152 )
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

EXPOSE_SCRIPT( ChoicesandPaths );