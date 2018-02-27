#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class AlexanderTheEyesoftheCreatorSavage : public InstanceContentScript
{
public:
   AlexanderTheEyesoftheCreatorSavage() : InstanceContentScript( 30043 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Unknown0", 2007457, 6430458, 4, { 8.200209f, -250.000000f, -257.340210f }, 1.000000f );
      instance->registerEObj( "Unknown1", 2007457, 6430459, 4, { 8.200209f, -250.000000f, -242.154495f }, 1.000000f );
      instance->registerEObj( "Unknown2", 2007457, 6430457, 4, { -9.317612f, -250.000000f, -257.340210f }, 1.000000f );
      instance->registerEObj( "Unknown3", 2007457, 6430456, 4, { -9.317612f, -250.000000f, -242.154495f }, 1.000000f );
      instance->registerEObj( "Powergenerator", 2007469, 0, 4, { 13.381770f, -250.000000f, -248.034500f }, 1.000000f );
      instance->registerEObj( "Unknown4", 2007457, 6513582, 4, { 10.437510f, -250.000000f, -260.791412f }, 1.000000f );
      instance->registerEObj( "Unknown5", 2007457, 6513579, 4, { 10.437510f, -250.000000f, -238.786697f }, 1.000000f );
      instance->registerEObj( "Unknown6", 2007457, 6513584, 4, { -11.731350f, -250.000000f, -260.791412f }, 1.000000f );
      instance->registerEObj( "Unknown7", 2007457, 6511025, 4, { -11.731350f, -250.000000f, -238.786697f }, 1.000000f );
      instance->registerEObj( "Unknown8", 2007457, 6516007, 4, { 0.000000f, -249.000000f, -250.000000f }, 1.000000f );
      instance->registerEObj( "Unknown9", 2007457, 6412089, 4, { -124.346802f, -26.965401f, -70.917450f }, 1.000000f );
      instance->registerEObj( "Unknown10", 2007457, 6492511, 4, { -124.346802f, -26.965401f, -70.917503f }, 1.000000f );
      instance->registerEObj( "Ingress", 2007456, 0, 4, { -40.238098f, 116.186600f, 3.921570f }, 0.991760f );
      instance->registerEObj( "Unknown11", 2002735, 0, 4, { -40.738098f, 114.683800f, 6.860600f }, 0.750000f );
      instance->registerEObj( "Unknown12", 2002872, 6480419, 4, { -40.263161f, 114.683800f, 4.312012f }, 1.000000f );
      instance->registerEObj( "Exit", 2000139, 0, 4, { -0.015320f, -246.936798f, -289.430511f }, 0.991760f );
      instance->registerEObj( "Cranialhatch", 2007455, 6401919, 4, { -40.885181f, 114.683899f, 3.853281f }, 1.000000f );
      instance->registerEObj( "Unknown13", 2002872, 6488523, 4, { -41.825008f, 114.671501f, -5.474617f }, 0.991760f );
      instance->registerEObj( "Unknown14", 2007457, 6480499, 4, { 0.029205f, -250.000000f, -269.982300f }, 1.000000f );
      instance->registerEObj( "Unknown15", 2007457, 6422309, 4, { 0.029205f, -249.000000f, -271.779205f }, 1.000000f );
      instance->registerEObj( "Unknown16", 2002587, 0, 4, { -36.774879f, 114.683701f, -18.658051f }, 1.200000f );
      instance->registerEObj( "Unknown17", 2002872, 6502657, 4, { -36.910030f, 114.683701f, -17.920090f }, 1.000000f );
      instance->registerEObj( "Entrance", 2000182, 6449051, 5, { -133.348099f, -24.805401f, -98.991310f }, 1.000000f );
      instance->registerEObj( "Shortcut", 2000700, 0, 4, { -133.531906f, -24.595860f, -91.717850f }, 0.991760f );
      instance->registerEObj( "Entrance", 2000182, 6449334, 5, { -36.523010f, 114.683701f, -20.849701f }, 1.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};