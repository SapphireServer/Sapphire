#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class KeepingtheSpiritAlive : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_POP_01 = 4074121;
  static constexpr auto INIT_POP_02 = 4074122;
  static constexpr auto INIT_POP_03 = 4074123;
  static constexpr auto INIT_ENPC_POP_01 = 4074347;
  static constexpr auto BGM_NOMAL = 101;
  static constexpr auto BGM_LVUP = 23;
  static constexpr auto NCUT_20010 = 165;
  static constexpr auto WARP_PC_POINT = 4106159;

public:
  KeepingtheSpiritAlive() : Sapphire::ScriptAPI::QuestBattleScript( 31 )
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

  void onUpdate( QuestBattle& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( QuestBattle& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( KeepingtheSpiritAlive );