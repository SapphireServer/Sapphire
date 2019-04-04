#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class SigmascapeV20 :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  SigmascapeV20() :
    Sapphire::ScriptAPI::InstanceContentScript( 30060 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2007457, 7244294, 4, { -6.511937f, 0.003125f, -4.958800f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_1", 2007457, 7181375, 4, { 12.476670f, -0.015002f, 6.948618f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_2", 2007457, 7181377, 4, { 12.570220f, -0.015320f, -9.693607f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_3", 2007457, 7329867, 4, { -4.318359f, -0.015320f, 5.722107f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_4", 2007457, 7187344, 4, { -1.960858f, 0.001128f, 0.319698f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_5", 2007457, 7174526, 4, { -6.872698f, 0.004465f, 1.843464f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_6", 2007457, 7174523, 4, { 11.220570f, 0.054783f, -1.564175f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_7", 2007457, 7174518, 4, { 8.520967f, 0.009985f, -8.679861f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_8", 2007457, 7174519, 4, { 9.028366f, 0.055644f, 3.513119f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_9", 2007457, 7180548, 4, { 2.311234f, 0.003611f, 3.656348f }, 1.000000f, -0.000000f ); 
    instance.registerEObj( "unknown_10", 2007457, 7244420, 4, { 2.385169f, 0.003358f, 3.242888f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_11", 2007457, 7181938, 4, { 15.676980f, 0.010429f, -11.942520f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_12", 2007457, 7181940, 4, { 16.526520f, 0.010429f, 11.441620f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_13", 2007457, 7181939, 4, { -16.083740f, 0.010429f, 11.147680f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_14", 2007457, 7181937, 4, { -16.250851f, -0.015320f, -11.795230f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Entrance", 2000182, 7179724, 5, { -1.443299f, 0.007087f, 6.836350f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 0.000000f, 0.000000f, -11.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_15", 2007457, 7171885, 4, { 4.955309f, 0.000000f, -52.142441f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( SigmascapeV20 );