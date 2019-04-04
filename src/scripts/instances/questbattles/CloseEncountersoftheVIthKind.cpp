#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class CloseEncountersoftheVIthKind : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto CUT_SCENE_N_01 = 895;
  static constexpr auto CUT_SCENE_N_02 = 896;
  static constexpr auto BNPC_COMPANION_ALPHINAUD = 5872315;
  static constexpr auto BNPC_COMPANION_ESTINIEN = 5872316;
  static constexpr auto BNPC_COMPANION_Y_SHTOLA = 5873153;
  static constexpr auto BNPC_ENEMY_BOSS = 5872306;
  static constexpr auto BNPC_ENEMY_ZAKO_KEN = 5872308;
  static constexpr auto BNPC_ENEMY_ZAKO_YARI = 5872309;
  static constexpr auto BNPC_ENEMY_ZAKO_JU = 5872310;
  static constexpr auto BNPC_ENEMY_ZAKO_YUMI = 5872311;
  static constexpr auto BNPC_ENEMY_TRANS_BATTALION_NOLOG_NOHIT_00 = 5872328;
  static constexpr auto BNPC_ENEMY_TRANS_BATTALION_NOLOG_NOHIT_01 = 5872329;
  static constexpr auto BNPC_ENEMY_TRANS_BATTALION_NOLOG_NOHIT_02 = 5872332;
  static constexpr auto BNPC_ENEMY_TRANS_BATTALION_NOLOG_NOHIT_03 = 5872333;
  static constexpr auto BNPC_ENEMY_TRANS_BATTALION_NOLOG_NOHIT_04 = 5872334;
  static constexpr auto BNPC_ENEMY_TRANS_BATTALION_NOLOG_NOHIT_05 = 5872337;
  static constexpr auto BNPC_ENEMY_TRANS_BATTALION_NOLOG_NOHIT_06 = 5872338;
  static constexpr auto BNPC_ENEMY_TRANS_BATTALION_NOLOG_NOHIT_07 = 5872339;
  static constexpr auto BNPC_JUJIGIRI = 5891787;
  static constexpr auto DEF_ACTION_JUJIGIRI = 3924;
  static constexpr auto DEF_ACTION_MAGIC_FIELD = 4006;
  static constexpr auto EOBJ_MAGIC_FIELD = 5891583;
  static constexpr auto STATUSPARAM_MAGIC_DOT = 1698;
  static constexpr auto BNPC_ENEMY_ADD_KEN = 5891587;
  static constexpr auto BNPC_ENEMY_ADD_YARI = 5891588;
  static constexpr auto BNPC_SEIRINSUI_01 = 5891755;
  static constexpr auto BNPC_SEIRINSUI_02 = 5891756;
  static constexpr auto BNPC_SEIRINSUI_03 = 5891757;
  static constexpr auto BNPC_SEIRINSUI_04 = 5891758;
  static constexpr auto BNPC_SEIRINSUI_05 = 5891759;
  static constexpr auto BNPC_SEIRINSUI_06 = 5891760;
  static constexpr auto BNPC_SEIRINSUI_07 = 5891761;
  static constexpr auto BNPC_SEIRINSUI_08 = 5891765;
  static constexpr auto DEF_ACTION_SEIRINSUI_BAKUHATSU = 3922;
  static constexpr auto DEF_ACTION_JUJIGIRI_TOSHIN = 3825;
  static constexpr auto BNPC_SUMMON_CARBUNCLE = 5911934;
  static constexpr auto DEF_ACTION_SUMMON_PET_BNPC = 4786;
  static constexpr auto BNPCBASE_SEIRINSUI = 3948;
  static constexpr auto BNPCBASE_JUJIGIRI = 3933;
  static constexpr auto POP_RANGE_Y_SHTOLA_MOVE_01 = 5936437;
  static constexpr auto LINE_VOICE_ALPHINAUD_007 = 8201091;

public:
  CloseEncountersoftheVIthKind() : Sapphire::ScriptAPI::QuestBattleScript( 110 )
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

EXPOSE_SCRIPT( CloseEncountersoftheVIthKind );