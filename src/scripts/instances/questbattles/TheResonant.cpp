#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheResonant :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheResonant() :
    Sapphire::ScriptAPI::InstanceContentScript( 5017 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2007457, 6927333, 4, { 503.255096f, 70.000000f, 589.613708f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Gatewinch", 2008907, 0, 4, { 508.261505f, 71.415131f, 575.156982f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgbg_w_qic_004_04a", 2007457, 7012282, 4, { 702.654602f, 70.000000f, 532.514282f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_1", 2008678, 0, 4, { -139.654007f, 69.993042f, 667.066772f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_2", 2008678, 0, 4, { -187.638397f, 69.993042f, 634.666504f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_3", 2008678, 0, 4, { -73.946472f, 69.993042f, 652.456177f }, 0.991760f, 0.000048f ); 

  }

  void onUpdate( InstanceContent& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheResonant );