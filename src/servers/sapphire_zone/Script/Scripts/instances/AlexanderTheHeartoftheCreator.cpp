#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class AlexanderTheHeartoftheCreator : public InstanceContentScript
{
public:
   AlexanderTheHeartoftheCreator() : InstanceContentScript( 30041 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Openduct", 2007466, 0, 4, { 0.000000f, -79.986076f, 42.000000f }, 1.000000f );
      instance->registerEObj( "Openduct", 2007466, 0, 4, { 10.000000f, -79.986076f, 52.000000f }, 1.000000f );
      instance->registerEObj( "Openduct", 2007466, 0, 4, { 0.000000f, -79.986076f, 62.000000f }, 1.000000f );
      instance->registerEObj( "Openduct", 2007466, 0, 4, { -10.000000f, -79.986076f, 52.000000f }, 1.000000f );
      instance->registerEObj( "Unknown0", 2007457, 6516055, 4, { 0.000000f, -79.986099f, 38.000000f }, 1.000000f );
      instance->registerEObj( "Unknown1", 2007457, 6516054, 4, { 0.000000f, -79.986099f, 38.000000f }, 1.000000f );
      instance->registerEObj( "Unknown2", 2007457, 6516050, 4, { 0.000000f, -79.986099f, 38.000000f }, 1.000000f );
      instance->registerEObj( "Unknown3", 2007457, 6516150, 4, { 0.000000f, -79.986099f, 38.000000f }, 1.000000f );
      instance->registerEObj( "Unknown4", 2007457, 6516057, 4, { 0.000000f, -79.986099f, 38.000000f }, 1.000000f );
      instance->registerEObj( "Unknown5", 2007457, 6516049, 4, { 0.000000f, -79.986099f, 38.000000f }, 1.000000f );
      instance->registerEObj( "Unknown6", 2007457, 6516058, 4, { 0.000000f, -79.986099f, 38.000000f }, 1.000000f );
      instance->registerEObj( "Unknown7", 2007457, 6516056, 4, { 0.000000f, -79.986099f, 38.000000f }, 1.000000f );
      instance->registerEObj( "Unknown8", 2007457, 6433752, 4, { 0.000000f, -79.986076f, 52.000000f }, 1.000000f );
      instance->registerEObj( "Unknown9", 2007457, 6498824, 4, { 0.000000f, -79.986076f, 52.000000f }, 1.000000f );
      instance->registerEObj( "Unknown10", 2007457, 6494083, 4, { -12.120000f, -79.986076f, 45.000000f }, 1.000000f );
      instance->registerEObj( "Unknown11", 2007457, 6494060, 4, { 12.120000f, -79.986076f, 45.000000f }, 1.000000f );
      instance->registerEObj( "Unknown12", 2007457, 6494084, 4, { 0.000000f, -79.986076f, 66.000000f }, 1.000000f );
      instance->registerEObj( "Unknown13", 2007497, 0, 4, { 0.000000f, 0.000000f, 0.000000f }, 1.000000f );
      instance->registerEObj( "Unknown14", 2007457, 6572855, 4, { 0.000000f, -80.000000f, 52.000000f }, 1.000000f );
      instance->registerEObj( "Unknown15", 2007457, 6573190, 4, { 0.000000f, -79.986076f, 52.000000f }, 1.000000f );
      instance->registerEObj( "Unknown16", 2007507, 0, 4, { 0.000000f, -79.986076f, 2.957292f }, 1.000000f );
      instance->registerEObj( "Unknown17", 2007457, 6433738, 4, { 26.696230f, 0.000000f, 11.513790f }, 1.000000f );
      instance->registerEObj( "Unknown18", 2007457, 6433741, 4, { -57.433731f, -40.000000f, -0.807872f }, 1.000000f );
      instance->registerEObj( "Exit", 2000139, 0, 4, { 0.000000f, -79.986076f, 40.000000f }, 1.000000f );
      instance->registerEObj( "Unknown19", 2002872, 6485880, 4, { -58.072899f, -39.959671f, -0.860951f }, 1.000000f );
      instance->registerEObj( "Unknown20", 2002735, 0, 4, { -59.879780f, -40.078049f, 0.248821f }, 0.500000f );
      instance->registerEObj( "Unknown21", 2006981, 6588684, 4, { 0.000000f, -80.000000f, 51.000000f }, 1.000000f );
      instance->registerEObj( "Entrance", 2000182, 6449497, 5, { 5.000000f, 0.060100f, 29.472811f }, 1.000000f );
      instance->registerEObj( "Shortcut", 2000700, 0, 4, { 15.893050f, -0.000000f, 20.165380f }, 1.000000f );
      instance->registerEObj( "Entrance", 2000182, 6449499, 5, { -46.692200f, -40.000000f, -16.064711f }, 2.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};