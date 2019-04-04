#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class HisForgottenHome : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto P_BNPC_ASAHI = 7189295;
  static constexpr auto P_BNPC_YUGIRI = 7189303;
  static constexpr auto P_BNPC_YUGIRI_AVATAR = 7253964;
  static constexpr auto P_BNPC_YUGIRI_AVATAR_2 = 7283041;
  static constexpr auto P_BNPC_ALISAIE = 7189304;
  static constexpr auto P_BNPC_ISSE = 7189305;
  static constexpr auto P_BNPC_AZAMI = 7189306;
  static constexpr auto BNPC_KOJIN_BOSS = 7189311;
  static constexpr auto BNPC_KOJIN_SAMURAI_01 = 7189312;
  static constexpr auto BNPC_KOJIN_SAMURAI_02 = 7189313;
  static constexpr auto BNPC_KOJIN_SAMURAI_03 = 7189314;
  static constexpr auto BNPC_KOJIN_SAMURAI_04 = 7189315;
  static constexpr auto BNPC_KOJIN_SAMURAI_05 = 7293406;
  static constexpr auto BNPC_KOJIN_SAMURAI_06 = 7293407;
  static constexpr auto BNPC_KOJIN_SAMURAI_07 = 7293408;
  static constexpr auto BNPC_KOJIN_NINJA_01 = 7226515;
  static constexpr auto BNPC_KOJIN_NINJA_02 = 7226527;
  static constexpr auto BNPC_KOJIN_NINJA_03 = 7226528;
  static constexpr auto BNPC_KOJIN_NINJA_04 = 7226534;
  static constexpr auto BNPC_KOJIN_NINJA_05 = 7226538;
  static constexpr auto BNPC_KOJIN_NINJA_06 = 7226539;
  static constexpr auto BNPC_KOJIN_NINJA_07 = 7226540;
  static constexpr auto BNPC_KOJIN_NINJA_08 = 7226541;
  static constexpr auto BNPC_KOJIN_MAGIC_01 = 7226535;
  static constexpr auto BNPC_KOJIN_MAGIC_02 = 7226537;
  static constexpr auto EOBJ_DAMAGE_AREA = 7253968;
  static constexpr auto QIB_YELL_StmBdc106_01 = 6631;
  static constexpr auto QIB_YELL_StmBdc106_02 = 6632;
  static constexpr auto ACTION_WATER_SHARE = 10573;
  static constexpr auto ACTION_BLIND = 3206;
  static constexpr auto ACTION_ICE_FLOOR = 10874;
  static constexpr auto ACTION_TRIGGER = 3269;
  static constexpr auto LOCKON_WATER_SHARE = 62;
  static constexpr auto LOCKON_ICE_FLOOR = 26;
  static constexpr auto STATUS_DOT_DMAGE = 3590;
  static constexpr auto ACTION_JUBAKU = 3207;
  static constexpr auto EOBJ_JUBAKU_AREA = 7335014;
  static constexpr auto STATUS_JUBAKU = 1039;

public:
  HisForgottenHome() : Sapphire::ScriptAPI::QuestBattleScript( 178 )
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

EXPOSE_SCRIPT( HisForgottenHome );