#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class SigmascapeV30Savage : public InstanceContentScript
{
public:
   SigmascapeV30Savage() : InstanceContentScript( 30065 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Entrance", 2000182, 7174192, 5, { -0.028109f, 0.000000f, 12.665810f }, 1.000000f );
      instance->registerEObj( "Exit", 2000139, 0, 4, { 0.000000f, 0.000000f, -15.000000f }, 1.000000f );
      instance->registerEObj( "Unknown1", 2009292, 7185733, 4, { -7.736383f, 3.268075f, -35.776291f }, 1.000000f );
      instance->registerEObj( "Unknown2", 2009293, 7185734, 4, { 10.155860f, 3.268075f, -35.738319f }, 1.000000f );
      instance->registerEObj( "Unknown3", 2009294, 0, 4, { 18.075230f, 0.000000f, -16.894060f }, 1.000000f );
      instance->registerEObj( "Unknown4", 2009295, 0, 4, { 15.384740f, 0.000000f, -8.198026f }, 1.000000f );
      instance->registerEObj( "Unknown5", 2009296, 0, 4, { 17.399639f, 0.000000f, -8.148316f }, 1.000000f );
      instance->registerEObj( "Unknown6", 2009297, 0, 4, { 10.133680f, 0.000000f, -9.799342f }, 1.000000f );
      instance->registerEObj( "Unknown7", 2009298, 0, 4, { 12.524550f, 0.000000f, -0.314495f }, 1.000000f );
      instance->registerEObj( "Unknown8", 2009299, 0, 4, { 4.409851f, -0.015320f, -0.839294f }, 0.991760f );
      instance->registerEObj( "Unknown9", 2009300, 0, 4, { 10.240340f, 0.000000f, 2.827696f }, 1.000000f );
      instance->registerEObj( "Unknown10", 2009301, 0, 4, { 12.606230f, 0.000000f, 7.149309f }, 1.000000f );
      instance->registerEObj( "Unknown11", 2009302, 7178404, 4, { 0.616980f, 0.000000f, 0.677854f }, 1.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};