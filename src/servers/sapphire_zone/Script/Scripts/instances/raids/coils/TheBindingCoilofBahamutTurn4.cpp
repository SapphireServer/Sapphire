#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class TheBindingCoilofBahamutTurn4 : public InstanceContentScript
{
public:
   TheBindingCoilofBahamutTurn4() : InstanceContentScript( 30005 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Silentterminal", 2000633, 4974723, 4, { -16.904461f, 1.700597f, 17.125530f }, 1.000000f );
      instance->registerEObj( "Silentterminal", 2000634, 4974724, 4, { 17.103741f, 1.662121f, 16.896111f }, 1.000000f );
      instance->registerEObj( "Unknown0", 2001153, 4254608, 4, { 7.917505f, 0.058137f, -7.647632f }, 1.000000f );
      instance->registerEObj( "Unknown1", 2001153, 4254609, 4, { 8.217505f, 0.058137f, -6.747632f }, 1.000000f );
      instance->registerEObj( "Unknown2", 2001153, 4254607, 4, { 8.517506f, 0.000000f, -5.847631f }, 1.000000f );
      instance->registerEObj( "Unknown3", 2001153, 4254606, 4, { 8.817506f, 0.000000f, -4.947631f }, 1.000000f );
      instance->registerEObj( "Unknown4", 2001155, 4974722, 4, { -16.599979f, 0.058137f, -16.803070f }, 1.000000f );
      instance->registerEObj( "Unknown5", 2001155, 4974721, 4, { 16.776859f, 0.058137f, -16.643490f }, 1.000000f );
      instance->registerEObj( "Unknown6", 2001764, 3961628, 4, { -0.983059f, 0.058134f, 3.319265f }, 1.000000f );
      instance->registerEObj( "Unknown7", 2001764, 4974712, 4, { -2.906071f, 0.058134f, 2.796373f }, 1.000000f );
      instance->registerEObj( "Unknown8", 2001764, 3962580, 4, { -4.811448f, 0.000001f, 9.066607f }, 0.991760f );
      instance->registerEObj( "Unknown9", 2001764, 4330325, 4, { 2.346304f, 0.058136f, 5.385328f }, 1.000000f );
      instance->registerEObj( "Unknown10", 2001764, 4330326, 4, { 4.663461f, 0.058136f, 4.726402f }, 1.000000f );
      instance->registerEObj( "Unknown11", 2000630, 4294847, 4, { -12.531030f, 0.000001f, 12.592170f }, 1.000000f );
      instance->registerEObj( "Unknown12", 2000615, 4374568, 4, { -15.534740f, 0.058137f, -15.601170f }, 1.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};