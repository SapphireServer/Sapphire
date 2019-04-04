#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class MasterandStudent : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto BNPC_GEKKAI = 5032404;
  static constexpr auto BNPC_GEKKAI_BUNSHIN_01 = 5112962;
  static constexpr auto BNPC_GEKKAI_BUNSHIN_02 = 5112979;
  static constexpr auto BNPC_GEKKAI_BUNSHIN_03 = 5112980;
  static constexpr auto BNPC_ZAKO_01 = 5112969;
  static constexpr auto BNPC_ZAKO_02 = 5112977;
  static constexpr auto BNPC_OBORO = 5112967;
  static constexpr auto BNPC_TSUBAME = 5112968;
  static constexpr auto BNPC_TOUMEI_RAITON_FOR_PLAYER_01 = 5112965;
  static constexpr auto BNPC_TOUMEI_RAITON_FOR_PLAYER_02 = 5114065;
  static constexpr auto BNPC_TOUMEI_RAITON_FOR_PLAYER_03 = 5114066;
  static constexpr auto BNPC_TOUMEI_RAITON_FOR_FIXED_POINT = 5112964;
  static constexpr auto BNPC_RAITON_TARGET_01 = 5113180;
  static constexpr auto BNPC_RAITON_TARGET_02 = 5113181;
  static constexpr auto BNPC_RAITON_TARGET_03 = 5113182;
  static constexpr auto BNPC_RAITON_TARGET_04 = 5113183;
  static constexpr auto BNPC_RAITON_TARGET_05 = 5113184;
  static constexpr auto BNPC_RAITON_TARGET_06 = 5113185;
  static constexpr auto BNPC_RAITON_TARGET_07 = 5113186;
  static constexpr auto BNPC_RAITON_TARGET_08 = 5118217;
  static constexpr auto BNPC_RAITON_TARGET_09 = 5118218;
  static constexpr auto BNPC_RAITON_TARGET_10 = 5118221;
  static constexpr auto DEF_ACTION_RAITON_GT = 3203;
  static constexpr auto DEF_ACTION_BUNSHIN = 3206;
  static constexpr auto STATUS_FIRE_DOT = 267;
  static constexpr auto DEF_ACTION_KATON_GT = 3205;
  static constexpr auto QIB_YELL_01 = 2347;
  static constexpr auto QIB_YELL_02 = 2348;
  static constexpr auto QIB_YELL_03 = 2349;
  static constexpr auto QIB_YELL_04 = 2350;
  static constexpr auto CUT_SCENE_00 = 692;
  static constexpr auto CUT_SCENE_01 = 693;
  static constexpr auto BNPC_SHUKUCHI_TARGET = 5420138;

public:
  MasterandStudent() : Sapphire::ScriptAPI::QuestBattleScript( 100 )
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

EXPOSE_SCRIPT( MasterandStudent );