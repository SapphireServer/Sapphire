#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class HandsofHealing : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto BNPC_DRGZMB_01 = 5886546;
  static constexpr auto P_BNPC_RAYAO_01 = 5886556;
  static constexpr auto P_BNPC_ARUHN_01 = 5886558;
  static constexpr auto P_BNPC_SERVANT_01 = 5886561;
  static constexpr auto BNPC_SKL_WAVE02_01 = 5887859;
  static constexpr auto BNPC_SKL_WAVE02_02 = 5887860;
  static constexpr auto BNPC_SKL_WAVE02_03 = 5887861;
  static constexpr auto BNPC_SKL_WAVE02_04 = 5911561;
  static constexpr auto BNPC_SKL_WAVE02_05 = 5911562;
  static constexpr auto BNPC_SKL_WAVE01_01 = 5922857;
  static constexpr auto BNPC_SKL_WAVE01_02 = 5922858;
  static constexpr auto BNPC_SKL_WAVE01_03 = 5922859;
  static constexpr auto BNPC_ETHER_01 = 5887863;
  static constexpr auto BNPC_ETHER_02 = 5888386;
  static constexpr auto BNPC_WAVE02_ZMB_01 = 5887930;
  static constexpr auto BNPC_WAVE02_ZMB_02 = 5887931;
  static constexpr auto BNPC_WAVE02_ZMB_03 = 5888028;
  static constexpr auto ENPC_NECROMANCER_01 = 5888162;
  static constexpr auto STATUS_PARAM_DOT_MAGIC = 1740;
  static constexpr auto BNPC_TOUMEI_FOR_ETHER_MAINTAIN_BATTLE_MODE = 5910322;
  static constexpr auto TORIGGER_ACTION_ETHER_HP_CONDITION = 3269;
  static constexpr auto TORIGGER_ACTION_ETHER_HP_CONDITION_B = 4777;
  static constexpr auto LOC_ACTOR_ESCHIVA = 1014683;
  static constexpr auto LOC_ACTOR_RAYAO = 1007130;
  static constexpr auto LOC_ACTOR_ARUN = 1007131;
  static constexpr auto LOC_ACTOR_ARAKA = 1014682;
  static constexpr auto LOC_LEVEL_ARAKA = 5890302;
  static constexpr auto LOC_ACTOR_DRGZMB = 1014702;
  static constexpr auto LOC_FACE1 = 611;
  static constexpr auto LOC_FACE2 = 620;
  static constexpr auto LOC_FACE3 = 617;
  static constexpr auto LOC_FACE4 = 604;
  static constexpr auto BNPC_SKL_WAVE01_04 = 5958827;
  static constexpr auto BNPC_SKL_WAVE01_05 = 5958826;
  static constexpr auto BNPC_SKL_WAVE02_06 = 5958840;
  static constexpr auto BNPC_SKL_WAVE02_07 = 5958841;
  static constexpr auto BNPC_ACTION_SOUL_DOUSE = 4182;
  static constexpr auto STATUS_MALADY = 1867;
  static constexpr auto LOC_BATTLE_BGM_01 = 91;

public:
  HandsofHealing() : Sapphire::ScriptAPI::QuestBattleScript( 134 )
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

EXPOSE_SCRIPT( HandsofHealing );