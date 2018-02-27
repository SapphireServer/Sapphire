#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class AlexanderTheFistoftheFatherSavage : public InstanceContentScript
{
public:
   AlexanderTheFistoftheFatherSavage() : InstanceContentScript( 30025 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Unknown0", 2005032, 0, 4, { -10.154560f, -23.900000f, -171.851105f }, 1.000000f );
      instance->registerEObj( "Unknown1", 2005046, 0, 4, { -13.656920f, -24.002501f, -180.132797f }, 0.991760f );
      instance->registerEObj( "Unknown2", 2005033, 0, 4, { -16.466789f, -24.000000f, -176.308197f }, 1.000000f );
      instance->registerEObj( "Unknown3", 2002735, 0, 4, { 0.000000f, 8.000000f, -39.386002f }, 0.750000f );
      instance->registerEObj( "Unknown4", 2002872, 5787765, 4, { -0.007763f, 8.000001f, -38.723202f }, 1.000000f );
      instance->registerEObj( "Unknown5", 2002872, 5787769, 4, { -0.007763f, 8.000002f, -76.255096f }, 1.000000f );
      instance->registerEObj( "Unknown6", 2005148, 5835158, 4, { -5.000000f, -4.351456f, 18.500000f }, 1.000000f );
      instance->registerEObj( "Unknown7", 2005149, 5835159, 4, { 5.000000f, -4.368736f, 18.500000f }, 1.000000f );
      instance->registerEObj( "Unknown8", 2005150, 5835148, 4, { -4.000000f, -3.485719f, 13.500000f }, 1.000000f );
      instance->registerEObj( "Unknown9", 2005151, 5835149, 4, { 4.000000f, -3.483227f, 13.500000f }, 1.000000f );
      instance->registerEObj( "Unknown10", 2005315, 5835144, 4, { -4.000000f, -2.619212f, 8.500000f }, 1.000000f );
      instance->registerEObj( "Unknown11", 2006035, 5835145, 4, { 4.000000f, -2.621703f, 8.500000f }, 1.000000f );
      instance->registerEObj( "Unknown12", 2006053, 5835143, 4, { -3.000000f, -1.918940f, 4.500000f }, 1.000000f );
      instance->registerEObj( "Unknown13", 2006054, 5835135, 4, { 3.000000f, -1.911465f, 4.500000f }, 1.000000f );
      instance->registerEObj( "Unknown14", 2006055, 5835141, 4, { -3.000000f, -1.231334f, 0.500000f }, 1.000000f );
      instance->registerEObj( "Unknown15", 2006056, 5835136, 4, { 3.000000f, -1.231335f, 0.500000f }, 1.000000f );
      instance->registerEObj( "Unknown16", 2006057, 5835153, 4, { -9.000000f, -3.642947f, 14.500000f }, 1.000000f );
      instance->registerEObj( "Unknown17", 2006058, 5835152, 4, { -9.000000f, -3.309154f, 12.500000f }, 1.000000f );
      instance->registerEObj( "Unknown18", 2006059, 5835151, 4, { 9.000000f, -3.666079f, 14.500000f }, 1.000000f );
      instance->registerEObj( "Unknown19", 2006060, 5835150, 4, { 9.000000f, -3.310075f, 12.500000f }, 1.000000f );
      instance->registerEObj( "Unknown20", 2006093, 5858144, 4, { -0.006211f, 12.000000f, -107.218903f }, 1.000000f );
      instance->registerEObj( "Unknown21", 2002872, 5787778, 4, { 0.000000f, 12.000000f, -107.839302f }, 1.000000f );
      instance->registerEObj( "Exit", 2000139, 0, 4, { 0.035584f, -24.311769f, -187.660599f }, 1.000000f );
      instance->registerEObj( "Unknown22", 2005402, 5815199, 4, { 1.317244f, -23.900000f, -173.937302f }, 1.000000f );
      instance->registerEObj( "Unknown23", 2005401, 5837182, 4, { -0.350596f, -23.900000f, -171.328796f }, 1.000000f );
      instance->registerEObj( "Exit", 2005313, 5908619, 4, { 0.000000f, -23.476339f, -186.888397f }, 1.000000f );
      instance->registerEObj( "Unknown24", 2002735, 0, 4, { 0.000000f, 11.993800f, -108.070297f }, 0.500000f );
      instance->registerEObj( "Entrance", 2000182, 5786793, 5, { -0.057753f, -21.358721f, 88.563942f }, 1.000000f );
      instance->registerEObj( "Shortcut", 2000700, 0, 4, { -1.141299f, -16.781481f, 74.122673f }, 1.000000f );
      instance->registerEObj( "Unknown26", 2005147, 5905927, 4, { -0.186450f, -20.599979f, 84.260910f }, 1.000000f );
      instance->registerEObj( "Entrance", 2000182, 5911084, 5, { -0.057753f, 8.090733f, -31.639650f }, 1.000000f );
      instance->registerEObj( "Unknown28", 2000608, 5911088, 4, { -0.300161f, 5.743856f, -19.072269f }, 1.000000f );
      instance->registerEObj( "Unknown29", 2005147, 5912244, 4, { -0.186450f, 8.755365f, -27.952221f }, 1.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};