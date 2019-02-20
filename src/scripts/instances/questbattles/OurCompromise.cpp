#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class OurCompromise :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  OurCompromise() :
    Sapphire::ScriptAPI::InstanceContentScript( 5020 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "sgpl_evt_300_jobdark03", 2007457, 6941254, 4, { -613.766602f, 59.266399f, -460.085205f }, 1.000000f, 0.294434f ); 
    // States -> vfx_on (id: 49) vfx_off (id: 50) 

  }

  void onUpdate( InstanceContent& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( OurCompromise );