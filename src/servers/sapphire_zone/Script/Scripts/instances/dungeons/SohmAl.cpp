#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class SohmAl : public InstanceContentScript
{
public:
   SohmAl() : InstanceContentScript( 37 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Unknown0", 2002735, 0, 4, { -142.306107f, 11.741690f, 188.300797f }, 1.000000f );
      instance->registerEObj( "Unknown1", 2002872, 5777776, 4, { -146.759598f, 9.382987f, 191.177994f }, 1.000000f );
      instance->registerEObj( "Unknown2", 2002872, 5777778, 4, { -126.024696f, 11.736150f, 144.580200f }, 1.000000f );
      instance->registerEObj( "Unknown3", 2002735, 0, 4, { 165.208603f, 137.478806f, -62.228100f }, 1.000000f );
      instance->registerEObj( "Unknown4", 2002872, 5777792, 4, { 166.178696f, 137.607697f, -62.706631f }, 1.000000f );
      instance->registerEObj( "Unknown5", 2002872, 5777793, 4, { 180.090302f, 138.237793f, -115.812103f }, 1.000000f );
      instance->registerEObj( "Unknown6", 2002735, 0, 4, { -112.464798f, 348.165985f, -368.176514f }, 1.000000f );
      instance->registerEObj( "Unknown7", 2002872, 5777990, 4, { -112.426399f, 348.165985f, -371.392487f }, 1.000000f );
      instance->registerEObj( "Unknown8", 2002872, 5777991, 4, { -89.965149f, 348.204498f, -416.112213f }, 1.000000f );
      instance->registerEObj( "Exit", 2000139, 0, 4, { -92.610641f, 348.164886f, -410.511993f }, 0.991760f );
      instance->registerEObj( "Unknown9", 2005284, 5773453, 4, { -274.538086f, -4.016628f, 191.237701f }, 0.991760f );
      instance->registerEObj( "Unknown10", 2005278, 5772621, 4, { -253.212296f, -2.894600f, 189.267303f }, 1.000000f );
      instance->registerEObj( "Unknown11", 2005285, 5773460, 4, { -196.123306f, 3.106796f, 187.990906f }, 1.000000f );
      instance->registerEObj( "Unknown12", 2005286, 5773461, 4, { -171.931305f, 2.815973f, 206.485794f }, 1.000000f );
      instance->registerEObj( "Unknown13", 2005279, 5772623, 4, { -165.063995f, 4.074061f, 197.945007f }, 1.000000f );
      instance->registerEObj( "Unknown14", 2005280, 5852453, 4, { 335.063385f, 114.335999f, -89.093300f }, 1.000000f );
      instance->registerEObj( "Unknown15", 2005281, 5777403, 4, { 247.495102f, 126.954300f, -30.577419f }, 1.000000f );
      instance->registerEObj( "Unknown16", 2005282, 5773504, 4, { -173.859894f, 324.834686f, -273.653503f }, 1.000000f );
      instance->registerEObj( "Unknown17", 2005283, 5773503, 4, { -191.639694f, 329.656799f, -321.158691f }, 1.000000f );
      instance->registerEObj( "Entrance", 2000182, 5777084, 5, { -267.602997f, -18.376320f, 282.751190f }, 1.000000f );
      instance->registerEObj( "Shortcut", 2000700, 0, 4, { -278.421387f, -17.669189f, 277.700714f }, 1.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};