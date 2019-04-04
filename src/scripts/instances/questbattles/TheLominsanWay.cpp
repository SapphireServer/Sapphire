#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class TheLominsanWay : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_POP_1_KAI_01 = 4295469;
  static constexpr auto INIT_POP_1_ROC_01 = 4295470;
  static constexpr auto INIT_POP_1_ROC_02 = 4295472;
  static constexpr auto INIT_POP_2_BOM_01 = 4295473;
  static constexpr auto INIT_ENPC_MIL_01 = 4295474;
  static constexpr auto DEF_PARALYSIS = 17;
  static constexpr auto POP_RANGE_ENEMY_MOVE_01 = 4295504;
  static constexpr auto LOGMESSAGE_QIB_01 = 3217;
  static constexpr auto LOGMESSAGE_QIB_02 = 3218;
  static constexpr auto LOGMESSAGE_QIB_03 = 3219;
  static constexpr auto QIB_YELL_01 = 1274;
  static constexpr auto QIB_YELL_02 = 1275;
  static constexpr auto QIB_YELL_03 = 1276;
  static constexpr auto QIB_YELL_04 = 1277;
  static constexpr auto QIB_YELL_05 = 1278;
  static constexpr auto QIB_YELL_06 = 1279;
  static constexpr auto QIB_YELL_07 = 1285;
  static constexpr auto BGM_BATTLE = 37;
  static constexpr auto LOC_ACTOR0 = 1006264;
  static constexpr auto LOC_ACTOR1 = 1005259;
  static constexpr auto LOC_POS_ACTOR0 = 4312558;
  static constexpr auto LOC_BGM1 = 87;

public:
  TheLominsanWay() : Sapphire::ScriptAPI::QuestBattleScript( 59 )
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

EXPOSE_SCRIPT( TheLominsanWay );