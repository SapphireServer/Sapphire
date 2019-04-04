#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class ThePowertoProtect : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto P_BNPC_WIDARGELT = 6865351;
  static constexpr auto P_BNPC_DZENTSA = 6865485;
  static constexpr auto P_BNPC_OTCHAKHA = 6865484;
  static constexpr auto P_BNPC_HAMON = 6865486;
  static constexpr auto P_BNPC_CHUCHUTO = 6865489;
  static constexpr auto P_BNPC_RURUKUTA = 6865494;
  static constexpr auto BNPC_BOSS = 6865521;
  static constexpr auto BNPC_HEWERALD = 6865534;
  static constexpr auto BNPC_PACK1_01 = 6865527;
  static constexpr auto BNPC_PACK1_02 = 6865531;
  static constexpr auto BNPC_PACK1_03 = 6865532;
  static constexpr auto BNPC_PACK1_04 = 6865533;
  static constexpr auto BNPC_PACK2_01 = 6872933;
  static constexpr auto BNPC_PACK2_02 = 6872934;
  static constexpr auto BNPC_PACK2_03 = 6872935;
  static constexpr auto BNPC_PACK2_04 = 6872937;
  static constexpr auto BNPC_PACK2_05 = 6872938;
  static constexpr auto BNPC_PACK2_06 = 6872943;
  static constexpr auto BNPC_PACK2_07 = 6872944;
  static constexpr auto BNPC_PACK2_08 = 6872945;
  static constexpr auto BNPC_PACK3_MACHINE_01 = 6873169;
  static constexpr auto BNPC_PACK3_MACHINE_02 = 6873170;
  static constexpr auto BNPC_PACK3_MACHINE_03 = 6873171;
  static constexpr auto BNPC_PACK3_SMALL_01 = 6873202;
  static constexpr auto BNPC_PACK3_SMALL_02 = 6873203;
  static constexpr auto BNPC_PACK3_SMALL_03 = 6873204;
  static constexpr auto BNPC_PACK3_SMALL_04 = 6873205;
  static constexpr auto BNPC_PACK3_SMALL_05 = 6873206;
  static constexpr auto BNPC_PACK3_SMALL_06 = 6873207;
  static constexpr auto BNPC_PACK3_SMALL_07 = 6873208;
  static constexpr auto BNPC_PACK3_SMALL_08 = 6873209;
  static constexpr auto LOCKON_BOSS_CHARGE = 30;
  static constexpr auto EOBJ_FIRE_DAMAGE_AREA = 6873049;
  static constexpr auto STATUS_PARAM_FIRE_DAMAGE = 2956;
  static constexpr auto ACTION_DARK_FIRE_II = 2175;
  static constexpr auto PR_WIDARGELT_MOVE_01 = 6872898;
  static constexpr auto PR_HAMON_MOVE_01 = 6873216;
  static constexpr auto QIB_YELL_01 = 4601;
  static constexpr auto QIB_YELL_02 = 4602;
  static constexpr auto QIB_YELL_03 = 4603;
  static constexpr auto QIB_YELL_04 = 4604;
  static constexpr auto QIB_YELL_05 = 4605;
  static constexpr auto QIB_YELL_06 = 4606;
  static constexpr auto QIB_YELL_07 = 4607;
  static constexpr auto QIB_YELL_08 = 4608;
  static constexpr auto QIB_YELL_09 = 4609;
  static constexpr auto QIB_YELL_10 = 6142;
  static constexpr auto ACTION_HEWERALD_CHARGE = 8305;
  static constexpr auto ACTION_HAMON_HYAKURETSUKEN = 8320;
  static constexpr auto ACTION_WIDARGELT_PBAE_HEAL = 8319;
  static constexpr auto BNPCBASE_BOSS = 7115;
  static constexpr auto ACTION_JAMMER_EXPLODE = 8341;
  static constexpr auto ACTION_SELF_DESTRUCT = 9438;
  static constexpr auto ACTION_FINAL_HEAVEN = 9439;
  static constexpr auto BNPCNAME_THEOBALD_VOICE = 6299;

public:
  ThePowertoProtect() : Sapphire::ScriptAPI::QuestBattleScript( 153 )
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

EXPOSE_SCRIPT( ThePowertoProtect );