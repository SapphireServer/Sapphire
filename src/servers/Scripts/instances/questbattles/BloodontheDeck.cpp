#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class BloodontheDeck :
  public InstanceContentScript
{
public:
  BloodontheDeck() :
    InstanceContentScript( 5009 )
  {
  }

  void onInit( InstanceContentPtr instance ) override
  {
    instance->registerEObj( "sgbg_w_qic_004_01a", 2007457, 6904219, 4, { 5.684449f, 16.347240f, 3.782750f }, 1.000000f,
                            0.000000f );
    // States -> cage01_close_01 cage01_open_01 cage01_open_02

  }

  void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( InstanceContentPtr instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};