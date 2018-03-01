#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class TheBindingCoilofBahamutTurn1 : public InstanceContentScript
{
public:
   TheBindingCoilofBahamutTurn1() : InstanceContentScript( 30002 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Unknown0", 2000620, 4293369, 4, { -1.810616f, 13.164380f, 57.682442f }, 1.000000f );
      instance->registerEObj( "Unknown1", 2000619, 4293368, 4, { -3.276026f, 13.164380f, 57.488449f }, 1.000000f );
      instance->registerEObj( "Unknown2", 2000680, 0, 4, { 0.000000f, 5.245687f, 4.314113f }, 1.000000f );
      instance->registerEObj( "Unknown3", 2000620, 4293633, 4, { 8.673634f, 4.398203f, -361.720886f }, 1.000000f );
      instance->registerEObj( "Unknown4", 2000619, 4293632, 4, { 7.539745f, 4.948945f, -366.654388f }, 0.991760f );
      instance->registerEObj( "Unknown5", 2001137, 0, 4, { -8.048342f, 1.700000f, -412.088593f }, 1.000000f );
      instance->registerEObj( "Unknown6", 2001696, 0, 4, { -23.791620f, 1.300000f, -414.239990f }, 1.000000f );
      instance->registerEObj( "Shortcut", 2000700, 0, 4, { -45.330261f, 25.136589f, 134.093399f }, 1.000000f );
      instance->registerEObj( "Unknown7", 2000486, 4374535, 4, { -5.435945f, 12.209330f, 0.953091f }, 0.991760f );
      instance->registerEObj( "Unknown8", 2000746, 4312523, 4, { 57.321320f, 2.000001f, -254.168396f }, 1.000000f );
      instance->registerEObj( "Unknown9", 2000746, 4312527, 4, { 36.303661f, 2.815034f, -341.235992f }, 1.000000f );
      instance->registerEObj( "Allaganterminal", 2001154, 4083745, 4, { -38.633110f, 0.899952f, -414.162201f }, 1.000000f );
      instance->registerEObj( "Unknown10", 2001167, 4329693, 4, { -50.832001f, 59.871399f, -332.417511f }, 1.000000f );
      instance->registerEObj( "Unknown11", 2002712, 4374479, 4, { 52.174641f, 2.740428f, -248.752899f }, 0.991760f );
      instance->registerEObj( "Unknown12", 2002712, 4374482, 4, { 44.598309f, 1.549361f, -340.584991f }, 1.000000f );
      instance->registerEObj( "Unknown13", 2001152, 4374713, 4, { -4.591531f, 4.500000f, -379.052795f }, 1.000000f );
      instance->registerEObj( "Unknown14", 2001152, 4374714, 4, { -47.199150f, 4.900000f, -430.581299f }, 0.991760f );
      instance->registerEObj( "Unknown15", 2001152, 4374715, 4, { -12.391370f, -0.160584f, -378.187805f }, 0.991760f );
      instance->registerEObj( "Unknown16", 2001152, 4374749, 4, { -12.091370f, -0.160584f, -376.087799f }, 0.991760f );
      instance->registerEObj( "Unknown17", 2000681, 4312291, 4, { 0.534759f, 4.500000f, -374.000000f }, 1.000000f );
      instance->registerEObj( "Unknown18", 2000681, 4312292, 4, { -7.437989f, 0.900002f, -387.547607f }, 1.000000f );
      instance->registerEObj( "Unknown19", 2000681, 4312293, 4, { -23.117430f, 0.472961f, -387.472412f }, 0.991760f );
      instance->registerEObj( "Unknown20", 2000681, 4312297, 4, { -46.428509f, 0.500000f, -400.448212f }, 1.000000f );
      instance->registerEObj( "Unknown21", 2000681, 4312296, 4, { -30.738091f, 0.099998f, -400.874908f }, 1.000000f );
      instance->registerEObj( "Unknown22", 2000681, 4312295, 4, { -14.994600f, -0.299999f, -400.505615f }, 1.000000f );
      instance->registerEObj( "Unknown23", 2000681, 4312294, 4, { 0.589670f, -0.700001f, -400.720093f }, 1.000000f );
      instance->registerEObj( "Unknown24", 2000681, 4312298, 4, { -7.442382f, 1.700001f, -414.361389f }, 1.000000f );
      instance->registerEObj( "Unknown25", 2000681, 4312299, 4, { -22.934330f, 1.296936f, -414.053589f }, 0.991760f );
      instance->registerEObj( "Unknown26", 2000681, 4312300, 4, { -38.631561f, 0.900004f, -414.153595f }, 1.000000f );
      instance->registerEObj( "Unknown27", 2000681, 4312303, 4, { -49.847839f, 4.899996f, -429.440002f }, 1.000000f );
      instance->registerEObj( "Unknown28", 2000681, 4312302, 4, { -30.867050f, 2.500000f, -428.009308f }, 1.000000f );
      instance->registerEObj( "Unknown29", 2000681, 4312301, 4, { -15.123560f, 2.100006f, -427.852295f }, 1.000000f );
      instance->registerEObj( "Unknown30", 2000627, 4293311, 4, { -57.085258f, 25.136589f, 146.983200f }, 1.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};