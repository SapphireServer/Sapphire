#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class ProofofMight : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_POP_01 = 3818846;
  static constexpr auto CUT_SCENE_01 = 28;
  static constexpr auto CUT_SCENE_02 = 16;
  static constexpr auto DEF_ACTION_LNC_PBAE = 1316;
  static constexpr auto DEF_ACTION_CALL_ZOMBIE_ITEM = 1317;
  static constexpr auto INIT_POP_LNC_01 = 4312452;
  static constexpr auto INIT_POP_LNC_02 = 4312453;
  static constexpr auto INIT_POP_THM_01 = 4312454;
  static constexpr auto INIT_POP_DAMAGE_RANGE = 4312455;
  static constexpr auto STATUS_CUSTOM_DAMAGE_RANGE_DEBUFF = 695;

public:
  ProofofMight() : Sapphire::ScriptAPI::QuestBattleScript( 10 )
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

EXPOSE_SCRIPT( ProofofMight );