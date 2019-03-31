#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class ThisLittleSwordofMine : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto BNPC_SHINMAI = 5882353;
  static constexpr auto BNPC_SOLKIZAGIL = 5886099;
  static constexpr auto BNPC_HOLY_SHIELD_1 = 5886100;
  static constexpr auto BNPC_HOLY_SHIELD_2 = 5886101;
  static constexpr auto BNPC_HOLY_SHIELD_3 = 5886102;
  static constexpr auto POP_RANGE_LATE_BATTLE_START = 5882020;
  static constexpr auto BNPC_BATTLE_FIELD_EDGE_01 = 5886124;
  static constexpr auto BNPC_BATTLE_FIELD_EDGE_02 = 5886125;
  static constexpr auto BNPC_BATTLE_FIELD_EDGE_03 = 5886126;
  static constexpr auto BNPC_BATTLE_FIELD_EDGE_04 = 5886127;
  static constexpr auto BNPC_BATTLE_FIELD_EDGE_05 = 5886128;
  static constexpr auto BNPC_BATTLE_FIELD_EDGE_06 = 5886129;
  static constexpr auto BNPC_BATTLE_FIELD_EDGE_07 = 5886130;
  static constexpr auto BNPC_BATTLE_FIELD_EDGE_08 = 5886131;
  static constexpr auto BNPC_FOR_JUMP_01 = 5886132;
  static constexpr auto BNPC_FOR_JUMP_02 = 5886133;
  static constexpr auto BNPC_FOR_JUMP_03 = 5886134;
  static constexpr auto BNPC_FOR_JUMP_04 = 5886135;
  static constexpr auto BGM_BOSS_BATTLE = 91;
  static constexpr auto ACTION_INVINCIBLE = 4745;
  static constexpr auto CHANNELING_INVINCIBLE = 2;
  static constexpr auto STATUS_PARAM_MUTEKI = 1496;
  static constexpr auto STATUS_PARAM_REGEN = 1665;
  static constexpr auto ACTION_BLOODSTAIN = 4747;
  static constexpr auto EOBJ_DAMAGE_FLOOR = 5886223;
  static constexpr auto STATUS_PARAM_DAMAGE_FLOOR = 1666;
  static constexpr auto ENPC_PAPASHAN = 5911812;
  static constexpr auto ENPC_SOLKZAGIL = 5911813;
  static constexpr auto ENPC_JENLINCE = 5911814;
  static constexpr auto ENPC_CONSTAN = 5911815;
  static constexpr auto LCUT_ACTOR0 = 1013868;
  static constexpr auto LCUT_ACTOR1 = 1013837;
  static constexpr auto LCUT_ACTOR2 = 1013838;
  static constexpr auto LCUT_ACTOR3 = 1014472;
  static constexpr auto LCUT_ACTOR4 = 1014471;
  static constexpr auto LCUT_POS_ACTOR0 = 5900389;
  static constexpr auto LCUT_POS_ACTOR1 = 5900390;
  static constexpr auto LCUT_POS_ACTOR2 = 5900392;
  static constexpr auto LCUT_ACTION0 = 936;
  static constexpr auto NCUT_01 = 976;
  static constexpr auto EOBJ_HOLY_SHIELD_1 = 5917573;
  static constexpr auto EOBJ_HOLY_SHIELD_2 = 5917574;
  static constexpr auto EOBJ_HOLY_SHIELD_3 = 5917575;
  static constexpr auto LCUT_SE0 = 94;
  static constexpr auto LCUT_BGM0 = 86;
  static constexpr auto LCUT_BGM1 = 97;
  static constexpr auto LCUT_BGM2 = 91;
  static constexpr auto LCUT_BGM3 = 39;

public:
  ThisLittleSwordofMine() : Sapphire::ScriptAPI::QuestBattleScript( 125 )
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

EXPOSE_SCRIPT( ThisLittleSwordofMine );