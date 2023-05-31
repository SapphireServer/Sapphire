#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TripleTriadInvitationalParlor : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TripleTriadInvitationalParlor() : Sapphire::ScriptAPI::InstanceContentScript( 26002 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "ExittotheGoldSaucer", 2007526, 0, 4, { 0.000000f, 0.300000f, 17.299999f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "ExittotheGoldSaucer_1", 2007526, 0, 4, { 0.000000f, 0.300000f, -17.299999f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_0", 2007457, 6424686, 4, { 8.500000f, -0.980310f, -10.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_1", 2007457, 6424692, 4, { -8.500000f, -0.980367f, -10.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_2", 2007457, 6493308, 4, { 8.500000f, -0.980310f, 10.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_3", 2007457, 6493307, 4, { -8.500000f, -0.980367f, 10.000000f }, 1.000000f, 0.000000f); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TripleTriadInvitationalParlor );