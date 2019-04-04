#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class InNaturesEmbrace : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_POP_BOSS = 3796294;
  static constexpr auto INIT_POP_YODOMI_01 = 4273807;
  static constexpr auto INIT_POP_YODOMI_02 = 4273810;
  static constexpr auto INIT_POP_IMP_01 = 4273820;
  static constexpr auto INIT_POP_IMP_02 = 4273821;
  static constexpr auto INIT_P_POP_SYLPHIE = 3873175;
  static constexpr auto CUT_SCENE_01 = 19;
  static constexpr auto CUT_SCENE_02 = 20;
  static constexpr auto DEF_YODOMI_DORAIN = 1127;
  static constexpr auto QIB_YELL_01 = 1003;
  static constexpr auto QIB_YELL_02 = 1004;

public:
  InNaturesEmbrace() : Sapphire::ScriptAPI::QuestBattleScript( 17 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.registerEObj( "Entrance", 2000182, 5021407, 5, { 623.000000f, 23.872311f, 94.505638f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 623.000000f, 23.656260f, 61.956181f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( InNaturesEmbrace );