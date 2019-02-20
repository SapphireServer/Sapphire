#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class FourplayerMahjongKuitanEnabled :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  FourplayerMahjongKuitanEnabled() :
    Sapphire::ScriptAPI::InstanceContentScript( 61003 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2007457, 7842765, 4, { 100.083900f, 0.472961f, 99.900757f }, 0.991760f, 0.000048f ); 

  }

  void onUpdate( InstanceContent& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( FourplayerMahjongKuitanEnabled );