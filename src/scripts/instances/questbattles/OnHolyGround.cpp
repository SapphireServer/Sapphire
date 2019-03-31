#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class OnHolyGround : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_P_POP_01 = 4004498;
  static constexpr auto INIT_POP_01 = 4004494;
  static constexpr auto INIT_POP_02 = 4004495;
  static constexpr auto INIT_POP_BOSS = 4004491;
  static constexpr auto LOC_POS_ACTOR0 = 4011257;
  static constexpr auto LOC_POS_ACTOR1 = 4011258;
  static constexpr auto LOC_POS_ACTOR2 = 4011259;
  static constexpr auto LOC_ACTOR0 = 1004301;
  static constexpr auto LOC_ACTOR1 = 1004306;
  static constexpr auto LOC_FACE0 = 604;
  static constexpr auto LOC_FACE1 = 605;
  static constexpr auto LOC_FACE2 = 617;
  static constexpr auto BNPC_NAME_01 = 690;
  static constexpr auto INIT_ENPC_POP_01 = 4065824;

public:
  OnHolyGround() : Sapphire::ScriptAPI::QuestBattleScript( 22 )
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

EXPOSE_SCRIPT( OnHolyGround );