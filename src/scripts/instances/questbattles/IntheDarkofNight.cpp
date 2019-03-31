#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class IntheDarkofNight : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto BNPC_IZORUDE_BOSS = 7808975;
  static constexpr auto BNPC_TOUMEI_ACTION_A01 = 7810191;
  static constexpr auto BNPC_TOUMEI_ACTION_A02 = 7810209;
  static constexpr auto BNPC_TOUMEI_ACTION_B01 = 7810198;
  static constexpr auto BNPC_TOUMEI_ACTION_B02 = 7810200;
  static constexpr auto BNPC_TOUMEI_ACTION_B03 = 7810202;
  static constexpr auto BNPC_TOUMEI_ACTION_B04 = 7810207;
  static constexpr auto P_BNPC_NOCTIS = 7808974;
  static constexpr auto BNPC_TOUMEI_ACTION_C01 = 7821422;
  static constexpr auto BNPC_TOUMEI_ACTION_C02 = 7821430;
  static constexpr auto BNPC_TOUMEI_ACTION_C03 = 7821431;
  static constexpr auto BNPC_TOUMEI_ACTION_C04 = 7821432;
  static constexpr auto BNPC_TOUMEI_ACTION_C05 = 7821433;
  static constexpr auto BNPC_TOUMEI_ACTION_C06 = 7821434;
  static constexpr auto BNPC_TOUMEI_ACTION_D01 = 7821435;
  static constexpr auto BNPC_TOUMEI_ACTION_D02 = 7821436;
  static constexpr auto BNPC_TOUMEI_ACTION_D03 = 7821437;
  static constexpr auto BNPC_TOUMEI_ACTION_D04 = 7821438;
  static constexpr auto BNPC_TOUMEI_ACTION_D05 = 7821439;
  static constexpr auto BNPC_TOUMEI_ACTION_D06 = 7821440;
  static constexpr auto BNPC_TOUMEI_ACTION_E01 = 7840020;
  static constexpr auto BNPC_TOUMEI_ACTION_E02 = 7840030;
  static constexpr auto BNPC_TOUMEI_TARGET = 7840047;
  static constexpr auto BNPC_TOUMEI_TARGETAE_01 = 7846607;
  static constexpr auto BNPC_TOUMEI_TARGETAE_02 = 7846618;
  static constexpr auto ACTION_CLAW_SHARE = 14606;
  static constexpr auto ACTION_SIX_LASER = 14602;
  static constexpr auto ACTION_SIX_LASER_TOUMEI = 14603;
  static constexpr auto ACTION_TOWER_ATTACK = 14608;
  static constexpr auto ACTION_TOWER_ATTACK_TOUMEI_SMALL = 14609;
  static constexpr auto ACTION_TOWER_ATTACK_TOUMEI_WIDE = 14610;
  static constexpr auto ACTION_TOWER_ATTACK_TOUMEI_SMALL_2 = 14981;
  static constexpr auto ACTION_STOMP = 14605;
  static constexpr auto ACTION_TARGETAE_ATTACK = 15082;
  static constexpr auto ACTION_TARGETAE_ATTACK_TOUMEI = 15083;
  static constexpr auto LOCKON_CLAW_SHARE = 93;
  static constexpr auto LOCKON_TARGETAE = 129;

public:
  IntheDarkofNight() : Sapphire::ScriptAPI::QuestBattleScript( 184 )
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

EXPOSE_SCRIPT( IntheDarkofNight );