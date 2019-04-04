#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class SigmascapeV30 :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  SigmascapeV30() :
    Sapphire::ScriptAPI::InstanceContentScript( 30061 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "Entrance", 2000182, 7174192, 5, { -0.028109f, 0.000000f, 12.665810f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 0.000000f, 0.000000f, -15.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_0", 2009292, 7185733, 4, { -7.736383f, 3.268075f, -35.776291f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_1", 2009293, 7185734, 4, { 10.155860f, 3.268075f, -35.738319f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_2", 2009294, 0, 4, { 18.075230f, 0.000000f, -16.894060f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_3", 2009295, 0, 4, { 15.384740f, 0.000000f, -8.198026f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_4", 2009296, 0, 4, { 17.399639f, 0.000000f, -8.148316f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_5", 2009297, 0, 4, { 10.133680f, 0.000000f, -9.799342f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_6", 2009298, 0, 4, { 12.524550f, 0.000000f, -0.314495f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_7", 2009299, 0, 4, { 4.409851f, -0.015320f, -0.839294f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_8", 2009300, 0, 4, { 10.240340f, 0.000000f, 2.827696f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_9", 2009301, 0, 4, { 12.606230f, 0.000000f, 7.149309f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_10", 2009302, 7178404, 4, { 0.616980f, 0.000000f, 0.677854f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( SigmascapeV30 );