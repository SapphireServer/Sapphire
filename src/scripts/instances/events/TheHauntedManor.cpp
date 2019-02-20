#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheHauntedManor :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheHauntedManor() :
    Sapphire::ScriptAPI::InstanceContentScript( 25001 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "Pumpkinchest", 2007385, 0, 4, { 72.176666f, -0.000001f, 8.325592f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Crypticnote", 2007394, 0, 4, { 77.017143f, 0.000000f, 7.811212f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Curiousswitch", 2007406, 0, 4, { 75.432663f, 0.000000f, 9.083635f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Goldbasket", 2007407, 0, 4, { 67.265839f, -0.000000f, 8.740001f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Silverbasket", 2007408, 0, 4, { 69.001480f, 0.000000f, 7.453632f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Bronzebasket", 2007409, 0, 4, { 65.439072f, 0.000000f, 7.248850f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Jackolantern", 2007410, 0, 4, { 61.411270f, 0.000000f, 12.014820f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Smolderingcoal", 2007411, 0, 4, { 58.469200f, -0.000000f, 11.999350f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Truesightsmokebomb", 2007412, 0, 4, { 55.969971f, 0.000000f, 12.118080f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Pumpkincoffer", 2007413, 0, 4, { 53.116581f, -0.015320f, 12.344480f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 15.229340f, -18.678320f, -0.619758f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Obfuscationcharm", 2007414, 0, 4, { 54.995380f, 0.000000f, 9.411625f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Jackinthebox", 2007547, 0, 4, { 69.704788f, 0.000000f, 10.012170f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Suspiciouspumpkin", 2007548, 0, 4, { 67.828171f, 0.000000f, 10.094330f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Suspiciouschest", 2007562, 0, 4, { 3.501173f, -18.779980f, -0.195926f }, 1.000000f, 1.568754f ); 
    instance.registerEObj( "Entrance", 2000182, 6381325, 5, { 73.499107f, -0.000000f, 4.652901f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 

  }

  void onUpdate( InstanceContent& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheHauntedManor );