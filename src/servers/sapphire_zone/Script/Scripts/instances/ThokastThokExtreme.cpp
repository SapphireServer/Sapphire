#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class ThokastThokExtreme : public InstanceContentScript
{
public:
   ThokastThokExtreme() : InstanceContentScript( 20032 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Unknown0", 2005385, 5674976, 4, { -1.192890f, 0.000000f, 17.474220f }, 1.000000f );
      instance->registerEObj( "Unknown1", 2005386, 5675419, 4, { -13.222250f, 0.000000f, 12.212180f }, 1.000000f );
      instance->registerEObj( "Unknown2", 2005387, 5675420, 4, { -18.468269f, 0.000000f, 0.628434f }, 1.000000f );
      instance->registerEObj( "Unknown3", 2005388, 5675421, 4, { -13.285940f, 0.000000f, -12.470450f }, 1.000000f );
      instance->registerEObj( "Unknown4", 2005389, 5675422, 4, { 0.342176f, 0.000000f, -18.571230f }, 1.000000f );
      instance->registerEObj( "Unknown5", 2005390, 5675423, 4, { 12.720200f, 0.000000f, -12.658900f }, 1.000000f );
      instance->registerEObj( "Unknown6", 2005391, 5675424, 4, { 17.782970f, 0.000000f, -0.534297f }, 1.000000f );
      instance->registerEObj( "Unknown7", 2005392, 5687664, 4, { 13.452240f, 0.000000f, 12.733450f }, 1.000000f );
      instance->registerEObj( "Unknown8", 2005393, 5797622, 4, { -8.704693f, 0.000000f, 1.700043f }, 1.000000f );
      instance->registerEObj( "Unknown9", 2005394, 5797549, 4, { -1.334651f, 0.000000f, -2.316425f }, 1.000000f );
      instance->registerEObj( "Unknown10", 2005385, 5674976, 4, { 3.622319f, -0.000001f, 15.464100f }, 1.000000f );
      instance->registerEObj( "Unknown11", 2005386, 5675419, 4, { -11.612120f, -0.015320f, 13.595760f }, 0.991760f );
      instance->registerEObj( "Unknown12", 2005387, 5675420, 4, { -17.196960f, -0.015320f, 2.304016f }, 0.991760f );
      instance->registerEObj( "Unknown13", 2005388, 5675421, 4, { -13.697780f, 0.000000f, -10.715490f }, 1.000000f );
      instance->registerEObj( "Unknown14", 2005389, 5675422, 4, { -2.138674f, 0.000000f, -16.784149f }, 1.000000f );
      instance->registerEObj( "Unknown15", 2005390, 5675423, 4, { 12.378810f, 0.000000f, -10.929330f }, 1.000000f );
      instance->registerEObj( "Unknown16", 2005391, 5675424, 4, { 17.679670f, 0.000000f, 1.168503f }, 1.000000f );
      instance->registerEObj( "Unknown17", 2005392, 5687664, 4, { 12.017570f, 0.000000f, 13.670370f }, 1.000000f );
      instance->registerEObj( "Unknown18", 2005393, 5797622, 4, { -10.360960f, -0.015320f, 2.975464f }, 0.991760f );
      instance->registerEObj( "Unknown19", 2005394, 5797549, 4, { -9.475891f, -0.015320f, 4.837097f }, 0.991760f );
      instance->registerEObj( "Entrance", 2000182, 5774826, 5, { -4.440430f, -0.015320f, 14.846980f }, 0.991760f );
      instance->registerEObj( "Exit", 2000139, 0, 4, { -0.068703f, -0.000001f, -13.884950f }, 1.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};