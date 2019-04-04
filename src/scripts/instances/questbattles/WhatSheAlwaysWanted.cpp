#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class WhatSheAlwaysWanted : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto BNPC_VOIDGATE_01 = 6853042;
  static constexpr auto BNPC_BOSS_01 = 6853043;
  static constexpr auto BNPC_TOUMEI = 6904817;
  static constexpr auto BNPC_VOIDGATE_WAVE1_01 = 6905648;
  static constexpr auto BNPC_VOIDGATE_WAVE1_02 = 6905649;
  static constexpr auto BNPC_VOIDGATE_WAVE1_03 = 6905650;
  static constexpr auto BNPC_WAVE1_TRASH01 = 6905730;
  static constexpr auto BNPC_WAVE1_TRASH02 = 6905732;
  static constexpr auto BNPC_WAVE1_ARK_DEMON = 6905735;
  static constexpr auto BNPC_VOID_LANCE_01 = 6906524;
  static constexpr auto BNPC_VOID_LANCE_02 = 6906525;
  static constexpr auto BNPC_VOID_LANCE_03 = 6906526;
  static constexpr auto BNPC_VOID_LANCE_04 = 6906527;
  static constexpr auto BNPC_VOIDGATE_WAVE2_01 = 6906732;
  static constexpr auto BNPC_VOIDGATE_WAVE2_02 = 6906734;
  static constexpr auto BNPC_VOIDGATE_WAVE2_03 = 6906736;
  static constexpr auto BNPC_WAVE2_TRASH01 = 6906740;
  static constexpr auto BNPC_WAVE2_TRASH02 = 6906741;
  static constexpr auto BNPC_WAVE2_TRASH03 = 6906742;
  static constexpr auto P_BNPC_SYLPHIE = 6853055;
  static constexpr auto P_BNPC_ESUMIYAN = 6853061;
  static constexpr auto P_BNPC_GIRL = 6853071;
  static constexpr auto CHANNELING_HOLD_GATTY = 65;
  static constexpr auto CHANNELING_ABSORB_MAGIC = 1;
  static constexpr auto QIB_YELL_01 = 4930;
  static constexpr auto QIB_YELL_02 = 4931;
  static constexpr auto QIB_YELL_03 = 4932;
  static constexpr auto QIB_YELL_04 = 4933;
  static constexpr auto QIB_YELL_05 = 4934;
  static constexpr auto QIB_YELL_06 = 5243;
  static constexpr auto QIB_YELL_07 = 5244;
  static constexpr auto QIB_YELL_08 = 5245;
  static constexpr auto ACTION_SCRIPT_TRIGGER = 3269;
  static constexpr auto ACTION_SCRIPT_TRIGGER_B = 4777;
  static constexpr auto ACTION_GATTY_EXPLODE = 8995;
  static constexpr auto ACTION_BOSS_LASER = 8996;
  static constexpr auto ACTION_RISE_TO_SKY = 1901;
  static constexpr auto DEF_ACTION_MONSTER_SUMMON = 3439;
  static constexpr auto ACTION_CRIMZON_LANCE_POP = 9038;
  static constexpr auto ACTION_BOSS_LETDOWN = 1899;
  static constexpr auto ACTION_GATTY_GETOVER = 9147;
  static constexpr auto ACTION_ESUMIYAN_LB3 = 8509;
  static constexpr auto PR_BOSS_MOVE_01 = 6904888;
  static constexpr auto PR_ESUMIYAN_MOVE_01 = 6925551;
  static constexpr auto PR_SYLPHIE_MOVE_01 = 6925552;
  static constexpr auto LOGMSG_01 = 5378;
  static constexpr auto LOGMSG_02 = 5379;
  static constexpr auto LOGMSG_03 = 5380;
  static constexpr auto LOGMSG_04 = 5381;
  static constexpr auto STATUS_PARAM_KNOCKDOWN = 3000;
  static constexpr auto STATUS_PARAM_RISE = 535;
  static constexpr auto STATUS_PARAM_BOSS_REGEN = 587;
  static constexpr auto BNPCSTATE_HOLD_GATTY = 166;
  static constexpr auto BNPCSTATE_NORMAL = 0;
  static constexpr auto BNPCBASE_VOIDGATE = 7417;
  static constexpr auto BNPCBASE_VOIDGATE_BIG = 7408;
  static constexpr auto BNPCBASE_ARK_DEMON = 7418;
  static constexpr auto BNPCBASE_HECTEYES = 7419;
  static constexpr auto BGM_BOSS_BATTLE = 406;
  static constexpr auto STATUS_PARAM_GATTY_LIFE_ABSORB = 3196;
  static constexpr auto EOBJ_AURA_01 = 6951909;

public:
  WhatSheAlwaysWanted() : Sapphire::ScriptAPI::QuestBattleScript( 169 )
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

EXPOSE_SCRIPT( WhatSheAlwaysWanted );