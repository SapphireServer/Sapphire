#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class ABeaconforBadThings : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto BNPC_WAVE1_01 = 6642829;
  static constexpr auto BNPC_WAVE1_02 = 6643459;
  static constexpr auto BNPC_WAVE1_03 = 6643462;
  static constexpr auto P_BNPC_GIRL = 6648027;
  static constexpr auto P_BNPC_MOTHER = 6648001;
  static constexpr auto P_BNPC_SYLPHIE = 6647996;
  static constexpr auto EOBJ_MIASMA_01 = 6650032;
  static constexpr auto QIB_YELL_GATTY_01 = 4290;
  static constexpr auto BNPC_WAVE2_GATE_01 = 6740811;
  static constexpr auto BNPC_WAVE2_GATE_02 = 6740812;
  static constexpr auto BNPC_WAVE2_GATE_03 = 6740813;
  static constexpr auto BNPC_WAVE2_01 = 6740817;
  static constexpr auto BNPC_WAVE2_02 = 6740818;
  static constexpr auto BNPC_WAVE2_03 = 6740819;
  static constexpr auto DEF_ACTION_MONSTER_SUMMON = 3439;
  static constexpr auto BNPC_WAVE3_GATE_01 = 6740861;
  static constexpr auto BNPC_WAVE3_GATE_02 = 6740862;
  static constexpr auto BNPC_WAVE3_GATE_03 = 6740863;
  static constexpr auto BNPC_WAVE3_01 = 6740865;
  static constexpr auto BNPC_WAVE3_02 = 6740866;
  static constexpr auto BNPC_WAVE3_03 = 6740867;

public:
  ABeaconforBadThings() : Sapphire::ScriptAPI::QuestBattleScript( 151 )
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

EXPOSE_SCRIPT( ABeaconforBadThings );