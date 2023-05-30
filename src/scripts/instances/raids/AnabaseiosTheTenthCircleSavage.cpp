#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class AnabaseiosTheTenthCircleSavage : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  AnabaseiosTheTenthCircleSavage() : Sapphire::ScriptAPI::InstanceContentScript( 30129 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "Entrance", 2007457, 9794467, 5, { 100.000000f, 0.000000f, 110.000000f }, 1.000000f, 0.000000f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 100.000000f, 0.000000f, 88.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Entrance", 2013340, 0, 4, { 99.992310f, -0.015320f, 92.647461f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "PassagetotheAitiascope", 2013342, 0, 4, { 100.033096f, 1.151500f, 114.283897f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Entrance_1", 2011709, 0, 4, { 100.012001f, 0.000000f, 87.795959f }, 1.000000f, 0.000000f); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( AnabaseiosTheTenthCircleSavage );