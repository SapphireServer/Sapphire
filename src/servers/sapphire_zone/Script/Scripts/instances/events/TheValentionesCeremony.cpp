#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class TheValentionesCeremony : public InstanceContentScript
{
public:
   TheValentionesCeremony() : InstanceContentScript( 25002 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Unknown0", 2007457, 7231658, 4, { -3.500000f, -6.000000f, -42.000000f }, 0.991760f );
      instance->registerEObj( "Unknown1", 2007457, 7231654, 4, { 17.466560f, -6.000000f, -45.513531f }, 0.991760f );
      instance->registerEObj( "Unknown2", 2007457, 7231667, 4, { 18.500000f, -6.000000f, -59.500000f }, 0.991760f );
      instance->registerEObj( "Unknown3", 2007457, 7231666, 4, { -9.500000f, -6.000000f, -68.500000f }, 0.991760f );
      instance->registerEObj( "Unknown4", 2007457, 7231668, 4, { -18.500000f, -6.000000f, -59.500000f }, 0.991760f );
      instance->registerEObj( "Unknown5", 2007457, 7231669, 4, { 11.489990f, -6.027344f, -68.528320f }, 0.991760f );
      instance->registerEObj( "Unknown6", 2007457, 7231672, 4, { 15.495000f, -6.027344f, -77.500671f }, 0.991760f );
      instance->registerEObj( "Unknown7", 2007457, 7231671, 4, { -16.500000f, -6.000000f, -71.500000f }, 1.000000f );
      instance->registerEObj( "Unknown8", 2007457, 7231673, 4, { 8.500000f, -8.000000f, -95.199997f }, 1.000000f );
      instance->registerEObj( "Unknown9", 2007457, 7231674, 4, { -6.515625f, -8.011047f, -92.729057f }, 0.991760f );
      instance->registerEObj( "Unknown10", 2007457, 7231677, 4, { -6.500000f, -8.000000f, -89.699997f }, 1.000000f );
      instance->registerEObj( "Unknown11", 2007457, 7231676, 4, { 8.475829f, -8.011047f, -101.701401f }, 0.991760f );
      instance->registerEObj( "Unknown12", 2007457, 7231678, 4, { -18.500000f, -8.000000f, -112.699997f }, 1.000000f );
      instance->registerEObj( "Unknown13", 2007457, 7231679, 4, { 14.500000f, -8.000000f, -111.699997f }, 1.000000f );
      instance->registerEObj( "Unknown14", 2007457, 7231681, 4, { 10.000000f, -8.000000f, -134.699997f }, 0.991760f );
      instance->registerEObj( "Unknown15", 2007457, 7231680, 4, { -15.500000f, -8.000000f, -127.699997f }, 1.000000f );
      instance->registerEObj( "Unknown16", 2007457, 7231683, 4, { -16.500000f, -10.000000f, -160.699997f }, 1.000000f );
      instance->registerEObj( "Unknown17", 2007457, 7231684, 4, { 3.558000f, -10.000000f, -150.699997f }, 1.000000f );
      instance->registerEObj( "Unknown18", 2007457, 7231686, 4, { 6.499207f, -10.025270f, -172.723999f }, 0.991760f );
      instance->registerEObj( "Unknown19", 2007457, 7231687, 4, { -17.471680f, -10.025270f, -170.716904f }, 0.991760f );
      instance->registerEObj( "Unknown20", 2007457, 7231689, 4, { 18.500000f, -10.000000f, -190.199997f }, 1.000000f );
      instance->registerEObj( "Unknown21", 2007457, 7231688, 4, { -3.550100f, -10.000000f, -186.699997f }, 1.000000f );
      instance->registerEObj( "Unknown22", 2007457, 7231690, 4, { -18.500000f, -10.000000f, -190.199997f }, 1.000000f );
      instance->registerEObj( "Unknown23", 2007457, 7231691, 4, { 3.550100f, -10.000000f, -186.699997f }, 1.000000f );
      instance->registerEObj( "Unknown24", 2007457, 7171421, 4, { -0.007954f, -11.881100f, -230.514008f }, 1.000000f );
      instance->registerEObj( "Unknown25", 2007457, 7231843, 4, { 0.006785f, -11.881100f, -253.447296f }, 1.000000f );
      instance->registerEObj( "ValentionesDaycard", 2009385, 7231795, 4, { -5.426984f, -11.917360f, -260.462494f }, 0.991760f );
      instance->registerEObj( "ValentionesDaycard", 2009387, 7231796, 4, { -9.668927f, -11.917360f, -260.401611f }, 0.991760f );
      instance->registerEObj( "ValentionesDaycard", 2009388, 7231797, 4, { -6.021372f, -11.917360f, -253.618393f }, 0.991760f );
      instance->registerEObj( "ValentionesDaycard", 2009389, 7231798, 4, { -10.334230f, -11.917360f, -253.545105f }, 0.991760f );
      instance->registerEObj( "ValentionesDaycard", 2009390, 7231799, 4, { -4.210987f, -11.917360f, -246.692703f }, 0.991760f );
      instance->registerEObj( "ValentionesDaycard", 2009391, 7231800, 4, { -8.330921f, -11.917360f, -246.662094f }, 0.991760f );
      instance->registerEObj( "ValentionesDaycard", 2009392, 7231801, 4, { 5.258507f, -11.917360f, -260.425812f }, 0.991760f );
      instance->registerEObj( "ValentionesDaycard", 2009393, 7231802, 4, { 9.500511f, -11.917360f, -260.425812f }, 0.991760f );
      instance->registerEObj( "ValentionesDaycard", 2009394, 7231803, 4, { 6.041663f, -11.881100f, -253.545105f }, 0.991760f );
      instance->registerEObj( "ValentionesDaycard", 2009395, 7231804, 4, { 10.315010f, -11.881100f, -253.545105f }, 0.991760f );
      instance->registerEObj( "ValentionesDaycard", 2009396, 7231805, 4, { 3.961101f, -11.917360f, -246.662094f }, 0.991760f );
      instance->registerEObj( "ValentionesDaycard", 2009397, 7231806, 4, { 8.203044f, -11.917360f, -246.662094f }, 0.991760f );
      instance->registerEObj( "Entrance", 2000182, 7186874, 5, { -0.017344f, 0.700000f, 15.850460f }, 1.000000f );
      instance->registerEObj( "Exit", 2000139, 0, 4, { 0.151178f, -11.881100f, -262.439209f }, 1.000000f );
      instance->registerEObj( "Unknown27", 2007457, 7167001, 4, { -0.198283f, 0.437501f, 3.359166f }, 1.000000f );
      instance->registerEObj( "Unknown28", 2007457, 7167005, 4, { -10.222270f, -6.000000f, -25.717331f }, 1.000000f );
      instance->registerEObj( "Unknown29", 2007457, 7167002, 4, { 10.259260f, -6.000000f, -25.717331f }, 1.000000f );
      instance->registerEObj( "Unknown30", 2007457, 7154005, 4, { -0.045776f, -11.734250f, -210.009903f }, 0.991760f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};