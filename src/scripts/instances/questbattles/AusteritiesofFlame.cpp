#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class AusteritiesofFlame : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_P_POP_MITRA_01 = 4300437;
  static constexpr auto INIT_POP_1_BOSS_IFRIT_EGI_01 = 4300450;
  static constexpr auto INIT_POP_2_FIRE_ELE_01 = 4300454;
  static constexpr auto INIT_POP_2_FIRE_ELE_02 = 4300455;
  static constexpr auto INIT_POP_2_FIRE_ELE_03 = 4300456;
  static constexpr auto INIT_POP_3_ANCHOR_01 = 4300459;
  static constexpr auto INIT_POP_3_ANCHOR_02 = 4300461;
  static constexpr auto INIT_POP_3_ANCHOR_03 = 4300462;
  static constexpr auto LOGMESSAGE_QIB_01 = 3222;
  static constexpr auto BNPC_BASE_TYPE_SPRIT = 1515;
  static constexpr auto BNPC_BASE_TYPE_BOSS = 1513;
  static constexpr auto CUT_START_NCUT = 350;
  static constexpr auto QIB_CHANNELING_FIRE = 5;

public:
  AusteritiesofFlame() : Sapphire::ScriptAPI::QuestBattleScript( 79 )
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

EXPOSE_SCRIPT( AusteritiesofFlame );