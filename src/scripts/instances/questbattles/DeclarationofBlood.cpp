#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class DeclarationofBlood : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto BNPC_FRAY = 5892100;
  static constexpr auto BNPC_P1_BOSS = 5892101;
  static constexpr auto BNPC_P1_MOB_01 = 5892107;
  static constexpr auto BNPC_P1_MOB_02 = 5892110;
  static constexpr auto BNPC_P1_MOB_03 = 5892111;
  static constexpr auto BNPC_P1_MOB_04 = 5892113;
  static constexpr auto BNPC_P1_MOB_05 = 5892115;
  static constexpr auto BNPC_P2_MOB_01 = 5892116;
  static constexpr auto BNPC_P2_MOB_02 = 5892118;
  static constexpr auto BNPC_P2_MOB_03 = 5892119;
  static constexpr auto BNPC_P2_MOB_04 = 5892121;
  static constexpr auto BNPC_P2_HEALER_01 = 5892108;
  static constexpr auto BNPC_P2_HEALER_02 = 5892109;
  static constexpr auto YELL_MOB_01 = 2674;
  static constexpr auto YELL_MOB_02 = 2675;
  static constexpr auto YELL_MOB_03 = 2676;
  static constexpr auto YELL_MOB_04 = 2677;
  static constexpr auto YELL_HEALER_01 = 2678;
  static constexpr auto YELL_HEALER_02 = 2679;
  static constexpr auto YELL_HEALER_03 = 2680;
  static constexpr auto YELL_ADD_MOB_01 = 2681;
  static constexpr auto YELL_BOSS_01 = 3149;
  static constexpr auto EOBJ_BOX = 5928029;
  static constexpr auto EOBJ_BOX_TARGET = 5928033;
  static constexpr auto EVENTACTION_SEARCH = 7;
  static constexpr auto BNPC_TOUMEI_IMAGAWA_HATE = 5961390;

public:
  DeclarationofBlood() : Sapphire::ScriptAPI::QuestBattleScript( 137 )
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

EXPOSE_SCRIPT( DeclarationofBlood );