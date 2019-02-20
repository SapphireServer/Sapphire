#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class AirForceOne :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  AirForceOne() :
    Sapphire::ScriptAPI::InstanceContentScript( 62002 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2009676, 0, 4, { -4.593018f, -8.655450f, 3.738403f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_1", 2009677, 0, 4, { -4.318359f, -8.655450f, 5.050659f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_2", 2009678, 0, 4, { -3.891113f, -8.655450f, 6.485046f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_3", 2009679, 0, 4, { -4.837158f, -8.655450f, 2.639771f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_4", 2009695, 0, 4, { -6.729248f, -8.655450f, -1.693787f }, 0.991760f, 0.000048f ); 

  }

  void onUpdate( InstanceContent& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( AirForceOne );