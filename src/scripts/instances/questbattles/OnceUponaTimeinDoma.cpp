#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class OnceUponaTimeinDoma : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_POP_OBORO_01 = 5045544;
  static constexpr auto INIT_POP_KARASU_1_01 = 5045545;
  static constexpr auto INIT_POP_GENIN_2_01 = 5045560;
  static constexpr auto INIT_POP_GENIN_2_02 = 5045689;
  static constexpr auto INIT_POP_GENIN_2_03 = 5045690;
  static constexpr auto INIT_POP_GENIN_2_04 = 5045693;
  static constexpr auto INIT_POP_GENIN_2_05 = 5045694;
  static constexpr auto INIT_POP_GENIN_2_06 = 5045695;
  static constexpr auto INIT_POP_GENIN_3_01 = 5045698;
  static constexpr auto INIT_POP_GENIN_3_02 = 5045699;
  static constexpr auto INIT_POP_GENIN_3_03 = 5045700;
  static constexpr auto INIT_POP_GENIN_3_04 = 5045702;
  static constexpr auto INIT_POP_GENIN_3_05 = 5045703;
  static constexpr auto INIT_POP_GENIN_3_06 = 5045704;
  static constexpr auto INIT_POP_GENIN_3_07 = 5045706;
  static constexpr auto INIT_POP_GENIN_3_08 = 5045707;
  static constexpr auto INIT_POP_GENIN_3_09 = 5045708;
  static constexpr auto INIT_POP_CHUNIN_4_01 = 5045717;
  static constexpr auto POP_RANGE_DEPOP = 5045776;
  static constexpr auto EOBJ_MAKIBISHI = 5143397;
  static constexpr auto STATUS_MAKIBISHI_DAMAGE = 1221;
  static constexpr auto DEF_ACTION_MAKIBISHI = 3196;
  static constexpr auto LOC_ACTOR0 = 1010597;
  static constexpr auto LOC_ACTOR1 = 1010560;
  static constexpr auto LOC_POS_ACTOR0 = 5375030;
  static constexpr auto LOC_MOTION0 = 1063;
  static constexpr auto LOC_MOTION1 = 617;
  static constexpr auto LOC_MOTION2 = 1059;
  static constexpr auto LOC_BGM0 = 80;
  static constexpr auto LOC_BGM1 = 78;
  static constexpr auto BNPC_SHUKUCHI_TARGET_01 = 5045761;
  static constexpr auto BNPC_SHUKUCHI_TARGET_02 = 5142531;
  static constexpr auto BNPC_SHUKUCHI_TARGET_03 = 5142532;
  static constexpr auto BNPC_SHUKUCHI_TARGET_04 = 5142533;
  static constexpr auto BNPC_SHUKUCHI_TARGET_05 = 5142534;
  static constexpr auto BNPC_SHUKUCHI_TARGET_06 = 5142535;
  static constexpr auto BNPC_SHUKUCHI_TARGET_07 = 5142536;
  static constexpr auto BNPC_SHUKUCHI_TARGET_08 = 5142537;
  static constexpr auto BNPC_SHUKUCHI_TARGET_09 = 5142538;

public:
  OnceUponaTimeinDoma() : Sapphire::ScriptAPI::QuestBattleScript( 97 )
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

EXPOSE_SCRIPT( OnceUponaTimeinDoma );