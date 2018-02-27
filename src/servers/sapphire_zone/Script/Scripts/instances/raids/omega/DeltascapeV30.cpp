#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class DeltascapeV30 : public InstanceContentScript
{
public:
   DeltascapeV30() : InstanceContentScript( 30051 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Matterrelocationdevice", 2008501, 6913059, 4, { 230.975693f, 231.836197f, -19.028080f }, 0.991760f );
      instance->registerEObj( "Unknown0", 2007457, 6792212, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown1", 2007457, 6847573, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown2", 2007457, 6848219, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown3", 2007457, 6953156, 4, { 250.000000f, 250.995605f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown4", 2007457, 6929138, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown5", 2007457, 6847577, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown6", 2007457, 6853325, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown7", 2007457, 6853774, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown8", 2007457, 6846630, 4, { -15.000000f, 0.000001f, 15.000000f }, 1.000000f );
      instance->registerEObj( "Unknown9", 2007457, 6846632, 4, { -5.000000f, 0.000000f, 15.000000f }, 1.000000f );
      instance->registerEObj( "Unknown10", 2007457, 6846634, 4, { 5.000000f, 0.000000f, 15.000000f }, 1.000000f );
      instance->registerEObj( "Unknown11", 2007457, 6846637, 4, { 15.000000f, 0.000000f, 15.000000f }, 1.000000f );
      instance->registerEObj( "Unknown12", 2007457, 6846642, 4, { -15.000000f, 0.000000f, -15.000000f }, 1.000000f );
      instance->registerEObj( "Unknown13", 2007457, 6846643, 4, { -5.000000f, 0.000000f, -15.000000f }, 1.000000f );
      instance->registerEObj( "Unknown14", 2007457, 6846644, 4, { 5.000000f, 0.000000f, -15.000000f }, 1.000000f );
      instance->registerEObj( "Unknown15", 2007457, 6846645, 4, { 15.000000f, 0.000000f, -15.000000f }, 1.000000f );
      instance->registerEObj( "Entrance", 2000182, 6912959, 5, { 0.000000f, 0.000000f, 15.000000f }, 1.000000f );
      instance->registerEObj( "Exit", 2000139, 0, 4, { 0.000000f, 0.000000f, -10.000000f }, 1.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};