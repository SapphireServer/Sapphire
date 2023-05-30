#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class OnsalHakairDanshigNaadam : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  OnsalHakairDanshigNaadam() : Sapphire::ScriptAPI::InstanceContentScript( 50006 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2007457, 8131163, 4, { -260.000000f, 23.000000f, -70.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_1", 2007457, 8131166, 4, { 190.997101f, 23.000441f, -191.027802f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "unknown_2", 2007457, 8131164, 4, { 69.993042f, 23.000000f, 260.975006f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "Ovoo", 2010927, 0, 4, { -0.015320f, 2.265113f, -0.015320f }, 0.991760f, -0.000000f); 
    instance.registerEObj( "Ovoo_1", 2010928, 0, 4, { 8.264099f, -10.900000f, -72.291718f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "Ovoo_2", 2010929, 0, 4, { 101.699997f, 12.998900f, -34.400021f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "Ovoo_3", 2010930, 0, 4, { 63.560699f, 10.149700f, 67.894203f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "Ovoo_4", 2010931, 0, 4, { -29.339291f, 4.548400f, 60.794102f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "Ovoo_5", 2010932, 0, 4, { -65.539200f, -6.999100f, 7.094101f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "Ovoo_6", 2010933, 0, 4, { -61.465199f, -2.373100f, -92.921700f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "Ovoo_7", 2010934, 0, 4, { 75.386200f, 3.584100f, -108.463898f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "Ovoo_8", 2010935, 0, 4, { 35.320889f, -6.088900f, 116.610298f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "Ovoo_9", 2010936, 0, 4, { -126.483299f, 1.156800f, -35.705898f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "Ovoo_10", 2010937, 0, 4, { -27.939301f, -11.008600f, -158.105804f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "Ovoo_11", 2010938, 0, 4, { 142.410706f, -5.983800f, 38.194199f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "Ovoo_12", 2010939, 0, 4, { -94.000000f, -5.939200f, 88.000000f }, 1.000000f, -0.000000f); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( OnsalHakairDanshigNaadam );