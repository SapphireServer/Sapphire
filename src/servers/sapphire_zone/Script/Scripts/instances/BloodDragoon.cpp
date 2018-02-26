#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class BloodDragoon : public InstanceContentScript
{
public:
   BloodDragoon() : InstanceContentScript( 5021 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Unknown0", 2007896, 6803926, 4, { 3.704567f, -0.506593f, 225.007507f }, 1.000000f );
      instance->registerEObj( "Unknown1", 2002872, 6805825, 4, { 4.867329f, -0.098875f, 275.309509f }, 1.000000f );
      instance->registerEObj( "Unknown2", 2002735, 0, 4, { 4.932000f, -0.320500f, 274.559509f }, 1.000000f );
      instance->registerEObj( "Unknown3", 2007899, 6802026, 4, { -28.138130f, -45.000000f, -32.892731f }, 1.000000f );
      instance->registerEObj( "Unknown4", 2002872, 6806775, 4, { -28.390051f, -45.148991f, 8.165403f }, 1.000000f );
      instance->registerEObj( "Unknown5", 2002735, 0, 4, { -28.551781f, -45.222500f, 5.617400f }, 1.000000f );
      instance->registerEObj( "Unknown6", 2007903, 6773193, 4, { -18.557831f, -44.964081f, -0.932714f }, 1.000000f );
      instance->registerEObj( "Unknown7", 2007904, 6773192, 4, { -30.723289f, -45.025860f, 1.953206f }, 1.000000f );
      instance->registerEObj( "Unknown8", 2007905, 6773194, 4, { -42.383171f, -44.962471f, -5.125507f }, 1.000000f );
      instance->registerEObj( "Unknown9", 2008196, 0, 4, { -37.125240f, -45.059940f, -9.414856f }, 0.991760f );
      instance->registerEObj( "Unknown10", 2008310, 6879064, 4, { -23.194941f, -45.000000f, -3.016589f }, 1.000000f );
      instance->registerEObj( "Unknown11", 2007457, 7008362, 4, { -28.500000f, -45.000000f, -14.000000f }, 1.000000f );
      instance->registerEObj( "Unknown12", 2002872, 6806776, 4, { 24.174879f, -167.392899f, -453.406586f }, 1.000000f );
      instance->registerEObj( "Unknown13", 2002735, 0, 4, { 24.419100f, -167.350601f, -455.580109f }, 1.000000f );
      instance->registerEObj( "Unknown14", 2007894, 6525794, 4, { -36.023540f, 4.305134f, 406.807404f }, 1.000000f );
      instance->registerEObj( "Unknown15", 2007895, 6525806, 4, { 4.331786f, 1.464790f, 289.456207f }, 1.000000f );
      instance->registerEObj( "Unknown16", 2007897, 6540078, 4, { -49.525101f, -45.174839f, 117.206200f }, 1.000000f );
      instance->registerEObj( "Unknown17", 2007898, 6540093, 4, { -14.321400f, -42.200001f, 42.272179f }, 1.000000f );
      instance->registerEObj( "Unknown18", 2007900, 6525664, 4, { -19.668949f, -188.037003f, -235.950302f }, 0.991760f );
      instance->registerEObj( "Unknown19", 2007901, 6525665, 4, { 25.192631f, -172.808502f, -362.417114f }, 0.991760f );
      instance->registerEObj( "Unknown20", 2007902, 6525180, 4, { 23.936859f, -172.125198f, -405.882996f }, 1.000000f );
      instance->registerEObj( "Entrance", 2000182, 6797774, 5, { -23.838560f, 8.289917f, 482.742615f }, 1.000000f );
      instance->registerEObj( "Shortcut", 2000700, 0, 4, { -20.252930f, 8.134582f, 489.817200f }, 1.000000f );
      instance->registerEObj( "Exit", 2000139, 0, 4, { 23.942671f, -167.617996f, -486.860809f }, 0.991760f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};