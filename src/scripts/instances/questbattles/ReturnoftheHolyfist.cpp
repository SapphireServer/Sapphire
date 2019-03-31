#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class ReturnoftheHolyfist : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_P_POP_01 = 4082369;
  static constexpr auto INIT_P_POP_02 = 4082370;
  static constexpr auto INIT_P_POP_03 = 4082371;
  static constexpr auto INIT_POP_BOSS = 4082372;
  static constexpr auto INIT_POP_01A_01 = 4082379;
  static constexpr auto INIT_POP_01B_01 = 4082380;
  static constexpr auto INIT_POP_01C_01 = 4082383;
  static constexpr auto INIT_POP_01C_02 = 4082384;
  static constexpr auto INIT_POP_01C_03 = 4082385;
  static constexpr auto INIT_POP_01D_01 = 4082392;
  static constexpr auto INIT_POP_01D_02 = 4082393;
  static constexpr auto INIT_POP_01D_03 = 4082394;
  static constexpr auto INIT_POP_02C_01 = 4082402;
  static constexpr auto INIT_POP_02C_02 = 4082403;
  static constexpr auto INIT_POP_02D_01 = 4082399;
  static constexpr auto INIT_POP_02D_02 = 4082400;
  static constexpr auto INIT_POP_02E_01 = 4082401;
  static constexpr auto INIT_POP_02F_01 = 4082404;
  static constexpr auto NCUT_30010 = 166;
  static constexpr auto NCUT_30020 = 167;
  static constexpr auto INIT_POP_04A_01 = 4163992;
  static constexpr auto INIT_POP_04B_01 = 4163993;
  static constexpr auto DEF_ACTION_EXC_PBAE = 1003;

public:
  ReturnoftheHolyfist() : Sapphire::ScriptAPI::QuestBattleScript( 34 )
  { }

  void onInit( QuestBattle& instance ) override
  {
    instance.registerEObj( "unknown_0", 2009578, 2091611, 4, { 31.545870f, 7.999978f, -121.025002f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_1", 2009578, 2091610, 4, { 4.407776f, 8.022990f, -105.310699f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_2", 2009578, 2091597, 4, { -184.324402f, 18.000000f, 65.271606f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_3", 2009578, 2091596, 4, { -146.806107f, 14.005000f, 63.857010f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Companychest", 2000470, 4255821, 4, { -149.301498f, 4.552717f, -91.365868f }, 0.991760f, -0.619932f ); 
    instance.registerEObj( "Huntboard", 2004440, 2217635, 4, { -152.330902f, 4.230781f, -92.351143f }, 0.991760f, 0.000048f ); 

  }

  void onUpdate( QuestBattle& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( ReturnoftheHolyfist );