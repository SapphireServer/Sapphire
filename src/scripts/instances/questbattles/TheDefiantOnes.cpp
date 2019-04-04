#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class TheDefiantOnes : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto BNPC_LALAI_01 = 5891371;
  static constexpr auto BNPC_01_ZAKO_A_01 = 5891375;
  static constexpr auto BNPC_01_ZAKO_A_02 = 5891376;
  static constexpr auto BNPC_01_ZAKO_A_03 = 5891377;
  static constexpr auto BNPC_02_ZAKO_A_04 = 5891410;
  static constexpr auto BNPC_02_ZAKO_A_05 = 5891412;
  static constexpr auto BNPC_02_ZAKO_B_01 = 5891413;
  static constexpr auto BNPC_03_ZAKO_A_06 = 5891418;
  static constexpr auto BNPC_03_ZAKO_A_07 = 5891419;
  static constexpr auto BNPC_03_ZAKO_B_02 = 5891420;
  static constexpr auto WARP_PC_POINT = 5891455;
  static constexpr auto BNPC_LALAI_02 = 5891456;
  static constexpr auto BNPC_KAZAGGCHAH_01 = 5891457;
  static constexpr auto BNPC_DAZA_01 = 5891458;
  static constexpr auto BNPC_DOZOLMELOC_01 = 5891459;
  static constexpr auto BNPC_ZHAIANELHAH_01 = 5891460;
  static constexpr auto BNPC_GARUMU = 5891463;
  static constexpr auto BNPC_VOIDGATE_01 = 5891473;
  static constexpr auto BNPC_VOIDGATE_02 = 5891474;
  static constexpr auto BNPC_VOIDGATE_03 = 5891475;
  static constexpr auto BNPC_IMP_01 = 5891476;
  static constexpr auto BNPC_IMP_02 = 5891478;
  static constexpr auto BNPC_IMP_03 = 5891479;
  static constexpr auto ER_RECT_01 = 5891381;
  static constexpr auto ER_RECT_02 = 5891414;
  static constexpr auto ER_RECT_03 = 5891421;
  static constexpr auto ER_RECT_04 = 5891424;
  static constexpr auto CUT_SCENE_00 = 938;
  static constexpr auto CUT_SCENE_01 = 939;
  static constexpr auto IMP_POP_INTERVAL_1 = 20;
  static constexpr auto LOGMESSAGE_QIB_01 = 3254;
  static constexpr auto LOGMESSAGE_QIB_02 = 3255;
  static constexpr auto BGM_BOSS_BATTLE = 91;
  static constexpr auto BNPC_STATE_NECKS_OFF = 120;
  static constexpr auto BNPC_THUNDER_BALL = 5901000;
  static constexpr auto DEF_ACTION_SUMMON_THUNDER_BALL = 4802;
  static constexpr auto DEF_ACTION_BLIZZARD_CANON = 4803;
  static constexpr auto EOBJ_ICE_DAMAGE_AREA = 5901009;
  static constexpr auto STATUS_PARAM_BLIZZARD_CANON = 1719;
  static constexpr auto POP_RANGE_COMPANION_TANK_MOVE = 5901029;
  static constexpr auto LOCKON_BY_THUNDER_BALL = 1;
  static constexpr auto ENPC_WALDEVE_01 = 5938152;
  static constexpr auto ENPC_WALDEVE_02 = 5938153;
  static constexpr auto BNPC_STATE_LEFT_NECK_ON = 127;
  static constexpr auto BNPC_STATE_NECKS_ON = 128;

public:
  TheDefiantOnes() : Sapphire::ScriptAPI::QuestBattleScript( 126 )
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

EXPOSE_SCRIPT( TheDefiantOnes );