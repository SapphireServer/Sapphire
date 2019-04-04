#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class StainedinScarlet : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto P_BNPC_ARIA = 6798100;
  static constexpr auto BNPC_BOSS = 6798104;
  static constexpr auto BNPC_THA_01 = 6798106;
  static constexpr auto BNPC_THA_02 = 6798107;
  static constexpr auto ENPC_SIRUN = 6798148;
  static constexpr auto LOCKON_SHARE = 62;
  static constexpr auto STATUS_VULNERABILITY = 202;
  static constexpr auto ACTION_DARK_SHARE = 8009;
  static constexpr auto BNPC_TOUMEI_ACTION_01 = 6829291;
  static constexpr auto BNPC_TOUMEI_ACTION_02 = 6829292;
  static constexpr auto BNPC_TOUMEI_ACTION_03 = 6829293;
  static constexpr auto ACTION_FLARE = 1305;
  static constexpr auto STATUS_KNOCKOUT = 625;
  static constexpr auto STATUS_PAIN = 273;
  static constexpr auto P_BNPC_TOUMEI_NOACTION_01 = 6829531;
  static constexpr auto P_BNPC_TOUMEI_NOACTION_02 = 6829532;
  static constexpr auto P_BNPC_TOUMEI_NOACTION_03 = 6829533;
  static constexpr auto P_BNPC_TOUMEI_NOACTION_04 = 6829534;
  static constexpr auto P_BNPC_TOUMEI_NOACTION_05 = 6829535;
  static constexpr auto P_BNPC_TOUMEI_NOACTION_06 = 6829536;
  static constexpr auto P_BNPC_TOUMEI_NOACTION_07 = 6829537;
  static constexpr auto P_BNPC_TOUMEI_NOACTION_08 = 6829538;
  static constexpr auto ACTION_LMBARD_DRAIN = 8018;
  static constexpr auto STATUS_HURT = 1256;
  static constexpr auto BNPC_FIREBALL_01 = 6829601;
  static constexpr auto BNPC_FIREBALL_02 = 6829602;
  static constexpr auto BNPC_FIREBALL_03 = 6829603;
  static constexpr auto BNPC_FIREBALL_04 = 6829604;
  static constexpr auto BNPC_FIREBALL_05 = 6829605;
  static constexpr auto BNPC_FIREBALL_06 = 6829606;
  static constexpr auto BNPC_FIREBALL_07 = 6829607;
  static constexpr auto BNPC_FIREBALL_08 = 6829608;
  static constexpr auto ACTION_LMBARD_SUMMON_FIREBALL = 8020;
  static constexpr auto ACTION_FIREBALL_EXPLODE = 8019;
  static constexpr auto QIB_YELL_01 = 4765;
  static constexpr auto ACTION_REDMAGE_HEAL = 7882;

public:
  StainedinScarlet() : Sapphire::ScriptAPI::QuestBattleScript( 165 )
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

EXPOSE_SCRIPT( StainedinScarlet );