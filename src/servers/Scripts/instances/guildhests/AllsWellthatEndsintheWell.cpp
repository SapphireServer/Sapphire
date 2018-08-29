#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class AllsWellthatEndsintheWell :
  public InstanceContentScript
{
public:
  AllsWellthatEndsintheWell() :
    InstanceContentScript( 10007 )
  {
  }

  void onInit( InstanceContentPtr instance ) override
  {
    instance->registerEObj( "Entrance", 2000182, 5021407, 5, { 623.000000f, 23.872311f, 94.505638f }, 1.000000f,
                            0.000000f );
    // States -> vf_lock_on vf_lock_of
    instance->registerEObj( "Exit", 2000139, 0, 4, { 623.000000f, 23.656260f, 61.956181f }, 1.000000f, 0.000000f );

  }

  void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( InstanceContentPtr instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};