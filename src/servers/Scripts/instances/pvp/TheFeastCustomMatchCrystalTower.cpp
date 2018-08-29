#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class TheFeastCustomMatchCrystalTower :
  public InstanceContentScript
{
public:
  TheFeastCustomMatchCrystalTower() :
    InstanceContentScript( 40025 )
  {
  }

  void onInit( InstanceContentPtr instance ) override
  {
    instance->registerEObj( "unknown_0", 2008986, 7240684, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f,
                            -0.000000f );
    instance->registerEObj( "unknown_1", 2008987, 7240683, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f,
                            -0.000000f );
    instance->registerEObj( "unknown_2", 2007457, 7164689, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f,
                            -0.000000f );
    instance->registerEObj( "unknown_3", 2007457, 7164690, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f,
                            -0.000000f );
    instance->registerEObj( "unknown_4", 2007457, 7164691, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f,
                            -0.000000f );
    instance->registerEObj( "unknown_5", 2007457, 7164692, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f,
                            -0.000000f );

  }

  void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( InstanceContentPtr instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};