#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class CuriousGorgeMeetsHisMatch :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  CuriousGorgeMeetsHisMatch() :
    Sapphire::ScriptAPI::InstanceContentScript( 5013 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "Summoningbell", 2000401, 4260827, 4, { 14.143430f, 5.238082f, 13.664930f }, 1.000000f, 0.000000f ); 
    // States -> vf_rtbell_on (id: 10) 
    instance.registerEObj( "Teamboard", 2009097, 4302533, 4, { 15.508660f, 6.051773f, -14.767720f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( InstanceContent& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( CuriousGorgeMeetsHisMatch );