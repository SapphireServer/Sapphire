#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class ThatOldFamiliarFeeling : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_P_POP_01 = 3993254;
  static constexpr auto INIT_POP_01A_01 = 3993614;
  static constexpr auto INIT_POP_01A_02 = 3993615;
  static constexpr auto INIT_POP_01A_03 = 3993616;
  static constexpr auto INIT_POP_01A_04 = 3993617;
  static constexpr auto INIT_POP_01A_05 = 3993618;
  static constexpr auto INIT_POP_02A_01 = 3993218;
  static constexpr auto INIT_POP_02A_02 = 3993219;
  static constexpr auto INIT_POP_02A_03 = 3993220;
  static constexpr auto INIT_POP_02A_04 = 3993221;
  static constexpr auto INIT_POP_02A_05 = 3993222;
  static constexpr auto INIT_POP_02B_01 = 3993250;
  static constexpr auto INIT_POP_02B_02 = 3993251;
  static constexpr auto INIT_POP_03A_01 = 3993388;
  static constexpr auto INIT_POP_03A_02 = 3993389;
  static constexpr auto INIT_POP_03A_03 = 3993390;
  static constexpr auto INIT_POP_03A_04 = 3993391;
  static constexpr auto INIT_POP_03A_05 = 3993392;
  static constexpr auto INIT_POP_03C_01 = 3993399;
  static constexpr auto INIT_POP_03C_02 = 3993528;
  static constexpr auto INIT_POP_03C_03 = 3993529;
  static constexpr auto INIT_POP_03C_04 = 3993544;
  static constexpr auto LOC_POS_ACTOR0 = 4009165;
  static constexpr auto LOC_ACTOR0 = 1004301;
  static constexpr auto LOC_FACE0 = 604;
  static constexpr auto LOC_FACE1 = 605;
  static constexpr auto CUT_SCENE_01 = 35;

public:
  ThatOldFamiliarFeeling() : Sapphire::ScriptAPI::QuestBattleScript( 20 )
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

EXPOSE_SCRIPT( ThatOldFamiliarFeeling );