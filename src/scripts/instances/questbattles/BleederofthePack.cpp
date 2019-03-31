#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class BleederofthePack : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_P_POP_1ST_01 = 4126558;
  static constexpr auto INIT_POP_1ST_01 = 4126546;
  static constexpr auto INIT_POP_1ST_02 = 4126547;
  static constexpr auto INIT_POP_1ST_03 = 4126548;
  static constexpr auto INIT_POP_1ST_04 = 4126549;
  static constexpr auto INIT_POP_1ST_05 = 4126550;
  static constexpr auto INIT_POP_1ST_06 = 4126551;
  static constexpr auto INIT_POP_2ST_01 = 4126569;
  static constexpr auto INIT_POP_2ST_02 = 4126570;
  static constexpr auto INIT_POP_2ST_03 = 4126571;
  static constexpr auto INIT_POP_2ST_04 = 4126573;
  static constexpr auto INIT_POP_2ST_05 = 4126574;
  static constexpr auto INIT_POP_2ST_06 = 4126575;
  static constexpr auto INIT_POP_3ST_01 = 4126627;
  static constexpr auto INIT_POP_3ST_02 = 4126628;
  static constexpr auto INIT_POP_3ST_03 = 4126629;
  static constexpr auto INIT_POP_3ST_04 = 4126631;
  static constexpr auto INIT_POP_3ST_05 = 4126632;
  static constexpr auto INIT_POP_3ST_06 = 4126633;
  static constexpr auto INIT_POP_4ST_01 = 4126649;
  static constexpr auto INIT_POP_4ST_02 = 4126655;
  static constexpr auto INIT_POP_4ST_03 = 4126656;
  static constexpr auto INIT_POP_4ST_04 = 4126657;
  static constexpr auto INIT_POP_4ST_05 = 4126658;
  static constexpr auto INIT_POP_5ST_01 = 4126659;
  static constexpr auto P_WARP_01 = 4127467;
  static constexpr auto INIT_ENPC_POP_01 = 4097270;
  static constexpr auto BGM_01 = 37;
  static constexpr auto LOC_ACTOR0 = 1003497;
  static constexpr auto LOC_ACTOR1 = 1002696;
  static constexpr auto LOC_ACTOR2 = 1003498;
  static constexpr auto LOC_ACTOR3 = 1003499;
  static constexpr auto LOC_POS_ACTOR0 = 4097270;
  static constexpr auto LOC_POS_ACTOR1 = 4164696;
  static constexpr auto LOC_POS_ACTOR2 = 4164697;
  static constexpr auto LOC_ACTION1 = 961;
  static constexpr auto LOC_ACTION2 = 824;
  static constexpr auto LOC_ACTION3 = 795;
  static constexpr auto LOC_ACTION4 = 934;

public:
  BleederofthePack() : Sapphire::ScriptAPI::QuestBattleScript( 27 )
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

EXPOSE_SCRIPT( BleederofthePack );