#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class AlexanderTheCuffoftheSonSavage :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  AlexanderTheCuffoftheSonSavage() :
    Sapphire::ScriptAPI::InstanceContentScript( 30035 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2005400, 0, 4, { -0.062597f, -7.999998f, -318.102112f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_1", 2004356, 6075850, 4, { 16.000000f, 17.661369f, 68.195396f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Steamspoutingcontraption", 2004357, 6075772, 4, { 21.013269f, 19.288509f, 69.098198f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgpl_d2a2_ring1wall", 2004356, 6183194, 4, { 16.000000f, 17.933451f, 69.738426f }, 1.000000f, 0.000000f ); 
    // States -> rw01_def (id: 33) rw01_opn (id: 34) rw01_around2opn (id: 35) 
    instance.registerEObj( "unknown_2", 2004362, 6075779, 4, { 21.207670f, 12.939710f, 41.993370f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118", 2002872, 6183959, 4, { 0.000000f, -26.000000f, -99.284462f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_3", 2002872, 6185722, 4, { 0.000000f, -25.918800f, -139.159302f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_4", 2002735, 0, 4, { 0.000000f, -26.000000f, -100.169899f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_5", 2002735, 0, 4, { 0.000000f, -20.000000f, -163.887405f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_6", 2002872, 6185721, 4, { 0.000000f, -19.913139f, -203.123398f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2002872, 6183975, 4, { 0.000000f, -20.000000f, -163.001999f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_7", 2002735, 0, 4, { 0.000000f, -14.000000f, -227.250000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_8", 2002872, 6185576, 4, { 0.000000f, -14.000000f, -267.622406f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2002872, 6183981, 4, { 0.000000f, -14.000000f, -226.639999f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_9", 2002735, 0, 4, { 0.000000f, -8.031601f, -286.936798f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2002872, 6183985, 4, { 0.000000f, -8.000000f, -286.051392f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "Exit", 2005313, 6186651, 4, { -0.636187f, -7.999998f, -335.408813f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Exit_1", 2000139, 0, 4, { 0.000000f, -7.921236f, -335.377502f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_10", 2006984, 6210606, 4, { -0.151275f, -14.000000f, -248.039703f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_d2a8_b0882", 2006989, 6234539, 4, { 1.000000f, -20.000000f, -184.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Entrance", 2000182, 6177892, 5, { 16.000000f, 21.783440f, 91.573517f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { 10.387650f, 18.918310f, 75.899696f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Entrance_1", 2000182, 6184206, 5, { 0.000000f, -26.000000f, -65.141693f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( AlexanderTheCuffoftheSonSavage );