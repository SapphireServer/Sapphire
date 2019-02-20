#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class BloodontheDeck :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  BloodontheDeck() :
    Sapphire::ScriptAPI::InstanceContentScript( 5009 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "sgbg_w_qic_004_01a", 2007457, 6904219, 4, { 5.684449f, 16.347240f, 3.782750f }, 1.000000f, 0.000000f ); 
    // States -> cage01_close_01 (id: 8) cage01_open_01 (id: 10) cage01_open_02 (id: 11) 

  }

  void onUpdate( InstanceContent& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( BloodontheDeck );