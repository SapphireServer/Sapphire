#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class TheBindingCoilofBahamutTurn5 : public InstanceContentScript
{
public:
   TheBindingCoilofBahamutTurn5() : InstanceContentScript( 30006 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Unknown0", 2000623, 4328290, 4, { -7.770457f, 54.493511f, -29.083250f }, 1.000000f );
      instance->registerEObj( "Unknown1", 2000666, 4323972, 4, { -3.001781f, 50.022308f, -7.576328f }, 1.000000f );
      instance->registerEObj( "Unknown2", 2000682, 0, 4, { -0.531223f, 50.025429f, 6.100062f }, 1.000000f );
      instance->registerEObj( "Unknown3", 2001151, 0, 4, { 11.681320f, 50.085152f, -0.915123f }, 1.000000f );
      instance->registerEObj( "Unknown4", 2001150, 0, 4, { 14.631230f, 50.087898f, 1.687731f }, 1.000000f );
      instance->registerEObj( "Unknown5", 2001168, 0, 4, { 17.845060f, 50.181900f, -0.676077f }, 1.000000f );
      instance->registerEObj( "Unknown6", 2002664, 0, 4, { -7.768790f, 50.005032f, -4.092178f }, 1.000000f );
      instance->registerEObj( "Allaganterminal", 2001163, 4328464, 4, { 51.910549f, 48.460838f, 72.757553f }, 1.000000f );
      instance->registerEObj( "Unknown7", 2000631, 4294944, 4, { -26.751080f, 100.099998f, -128.204498f }, 1.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};