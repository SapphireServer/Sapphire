#include <ScriptObject.h>
#include <Territory/QuestBattle.h>

using namespace Sapphire;

class IntoaCopperHell : public Sapphire::ScriptAPI::QuestBattleScript
{
private:
  static constexpr auto INIT_POP_A = 4094987;
  static constexpr auto INIT_POP_B = 4094990;
  static constexpr auto INIT_POP_C = 4094992;
  static constexpr auto CUT_SCENE_01 = 76;
  static constexpr auto CUT_SCENE_02 = 77;
  static constexpr auto CUT_SCENE_03 = 78;
  static constexpr auto LOC_ACTOR0 = 1005138;
  static constexpr auto LOC_ACTOR1 = 1004748;
  static constexpr auto LOC_ACTOR2 = 1004749;
  static constexpr auto LOC_ACTOR3 = 1005117;
  static constexpr auto LOC_ACTOR4 = 1005119;
  static constexpr auto LOC_ACTOR5 = 1005120;
  static constexpr auto LOC_ACTOR8 = 1004653;
  static constexpr auto LOC_ACTOR9 = 1004654;
  static constexpr auto LOC_POS_ACTOR0 = 4176169;
  static constexpr auto LOC_POS_ACTOR1 = 4176170;
  static constexpr auto LOC_POS_ACTOR2 = 4176171;
  static constexpr auto LOC_FACE0 = 604;
  static constexpr auto LOC_FACE1 = 617;
  static constexpr auto LOC_FACE2 = 620;
  static constexpr auto LOC_FACE3 = 605;
  static constexpr auto LOC_FACE4 = 611;

public:
  IntoaCopperHell() : Sapphire::ScriptAPI::QuestBattleScript( 44 )
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

EXPOSE_SCRIPT( IntoaCopperHell );