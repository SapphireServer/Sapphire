#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class ToCatchaPoacher : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_POP_1_ARC_01 = 3818973;
  static constexpr auto INIT_POP_1_LNC_01 = 3818974;
  static constexpr auto INIT_POP_1_LNC_02 = 3818975;
  static constexpr auto INIT_POP_2_LNC_01 = 4259098;
  static constexpr auto INIT_POP_2_LNC_02 = 4259100;
  static constexpr auto INIT_POP_2_CNJ_01 = 4259102;
  static constexpr auto INIT_POP_2_ARC_01 = 3818976;
  static constexpr auto INIT_POP_2_ARC_02 = 3818977;
  static constexpr auto INIT_POP_3_LNC_01 = 3914483;
  static constexpr auto INIT_POP_3_LNC_02 = 3914484;
  static constexpr auto INIT_POP_3_BOSS = 4259104;
  static constexpr auto INIT_POP_3_CNJ_01 = 4259105;
  static constexpr auto INIT_P_POP_1 = 4259091;
  static constexpr auto BNPC_NAME_01 = 139;
  static constexpr auto BNPC_NAME_02 = 140;
  static constexpr auto CUT_SCENE_01 = 11;
  static constexpr auto CUT_SCENE_02 = 12;
  static constexpr auto DEF_QUICK_KNOCK = 106;

public:
  ToCatchaPoacher() : Sapphire::ScriptAPI::QuestBattleScript( 5 )
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

EXPOSE_SCRIPT( ToCatchaPoacher );