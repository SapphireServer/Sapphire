#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class TheAery : public InstanceContentScript
{
public:
   TheAery() : InstanceContentScript( 39 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Unknown0", 2002872, 5754325, 4, { 346.791687f, 93.919189f, -178.606903f }, 0.991760f );
      instance->registerEObj( "Unknown1", 2005233, 5754326, 4, { 317.558105f, 93.945251f, -180.372498f }, 1.000000f );
      instance->registerEObj( "Unknown2", 2002735, 0, 4, { 345.215607f, 93.945251f, -178.963303f }, 1.000000f );
      instance->registerEObj( "Unknown3", 2002872, 5795105, 4, { 40.665161f, 59.433842f, 65.873169f }, 0.991760f );
      instance->registerEObj( "Unknown4", 2005234, 5795134, 4, { -14.039410f, 61.140190f, 54.695210f }, 0.991760f );
      instance->registerEObj( "Unknown5", 2002587, 0, 4, { 39.169510f, 59.433949f, 66.247253f }, 1.300000f );
      instance->registerEObj( "Unknown6", 2002872, 5762428, 4, { 37.260880f, 148.068100f, -236.237595f }, 1.000000f );
      instance->registerEObj( "Unknown7", 2002735, 0, 4, { 35.001831f, 148.194504f, -233.032303f }, 1.000000f );
      instance->registerEObj( "Unknown8", 2005542, 0, 4, { 36.301151f, 148.393906f, -242.999893f }, 0.991760f );
      instance->registerEObj( "Unknown9", 2006454, 0, 4, { 32.698120f, 148.397095f, -251.838501f }, 1.000000f );
      instance->registerEObj( "Entrance", 2000182, 5724494, 5, { 136.459106f, 67.985649f, 171.436401f }, 1.000000f );
      instance->registerEObj( "Shortcut", 2000700, 0, 4, { 144.406906f, 67.985611f, 177.100906f }, 1.000000f );
      instance->registerEObj( "Exit", 2000139, 0, 4, { 21.307430f, 148.274002f, -283.827087f }, 1.000000f );
      instance->registerEObj( "Unknown11", 2005222, 5685356, 4, { 267.117188f, 64.682983f, 47.219650f }, 0.991760f );
      instance->registerEObj( "Unknown12", 2005223, 5685357, 4, { 358.511414f, 81.162720f, -120.381798f }, 0.991760f );
      instance->registerEObj( "Unknown13", 2005224, 5821951, 4, { 131.793304f, 5.889650f, -103.881500f }, 1.000000f );
      instance->registerEObj( "Unknown14", 2005225, 5821943, 4, { 50.821239f, 55.531479f, 63.561810f }, 0.991760f );
      instance->registerEObj( "Unknown15", 2005438, 5851315, 4, { -77.756859f, 91.481842f, -15.425310f }, 1.000000f );
      instance->registerEObj( "Unknown16", 2005439, 5851342, 4, { 82.891663f, 108.510201f, -49.804409f }, 1.000000f );
      instance->registerEObj( "Unknown17", 2005540, 5864523, 4, { 33.827099f, 134.430405f, -194.964005f }, 1.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};