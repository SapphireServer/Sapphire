#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class TheThreatofPerplexity : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_P_POP_FRIEND = 4031433;
  static constexpr auto INIT_POP_BOSS = 4031432;
  static constexpr auto INIT_POP_ENEMY_A_01 = 4031434;
  static constexpr auto INIT_POP_ENEMY_A_02 = 4031747;
  static constexpr auto DEF_ACTION_BLLIZARA = 146;

public:
  TheThreatofPerplexity() : Sapphire::ScriptAPI::QuestBattleScript( 41 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.registerEObj( "Exit", 2000605, 0, 4, { -715.942383f, 69.420113f, -830.370300f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_0", 2000606, 3861081, 4, { -670.462280f, 63.293751f, -801.510986f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Entrance", 2000604, 4262798, 5, { -677.634888f, 64.116386f, -803.174927f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 

  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheThreatofPerplexity );