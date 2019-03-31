#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class SwornUponaLance : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto BNPC_HEUSTIENNE_01 = 5877439;
  static constexpr auto BNPC_P1_GORILLADRAGON_01 = 5877448;
  static constexpr auto BNPC_P1_PUK_01 = 5877449;
  static constexpr auto BNPC_P1_PUK_02 = 5877451;
  static constexpr auto BNPC_P2_GORILLADRAGON_01 = 5877656;
  static constexpr auto BNPC_P2_GORILLADRAGON_02 = 5877657;
  static constexpr auto BNPC_P2_GORILLADRAGON_03 = 5877659;
  static constexpr auto BNPC_P2_PUK_01 = 5877661;
  static constexpr auto BNPC_P2_PUK_02 = 5877662;
  static constexpr auto BNPC_P2_PUK_03 = 5877663;
  static constexpr auto BNPC_P2_PUK_04 = 5877706;
  static constexpr auto BNPC_P3_GORILLADRAGON_01 = 5877762;
  static constexpr auto BNPC_P3_GORILLADRAGON_02 = 5877763;
  static constexpr auto BNPC_P3_PUK_01 = 5877765;
  static constexpr auto BNPC_P3_PUK_02 = 5877766;
  static constexpr auto BNPC_P3_WYVERN_01 = 5877769;
  static constexpr auto NCUT_01 = 936;

public:
  SwornUponaLance() : Sapphire::ScriptAPI::QuestBattleScript( 116 )
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

EXPOSE_SCRIPT( SwornUponaLance );