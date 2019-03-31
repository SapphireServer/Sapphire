#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class UnderneaththeSultantree : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_POP_BOSS = 4077147;
  static constexpr auto INIT_POP_01_01 = 4077151;
  static constexpr auto INIT_POP_01_02 = 4077152;
  static constexpr auto INIT_POP_02_01 = 4077427;
  static constexpr auto INIT_POP_02_02 = 4077428;
  static constexpr auto INIT_POP_02_03 = 4077429;
  static constexpr auto INIT_POP_02_04 = 4077430;
  static constexpr auto INIT_P_POP_01 = 4077150;
  static constexpr auto CUT_SCENE_01 = 140;
  static constexpr auto HOW_TO_QIB = 79;

public:
  UnderneaththeSultantree() : Sapphire::ScriptAPI::QuestBattleScript( 37 )
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

EXPOSE_SCRIPT( UnderneaththeSultantree );