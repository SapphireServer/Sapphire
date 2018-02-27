#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class TheFractalContinuumHard : public InstanceContentScript
{
public:
   TheFractalContinuumHard() : InstanceContentScript( 60 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Unknown0", 2002735, 0, 4, { -0.015320f, 46.585819f, -330.098389f }, 1.693726f );
      instance->registerEObj( "Unknown1", 2002872, 7178420, 4, { 0.000000f, 46.597000f, -330.000000f }, 1.000000f );
      instance->registerEObj( "Unknown2", 2007457, 7154681, 4, { -336.809601f, -4.091716f, 270.330200f }, 1.000000f );
      instance->registerEObj( "Unknown3", 2007457, 7154670, 4, { -356.951599f, -4.091716f, 262.314697f }, 1.000000f );
      instance->registerEObj( "Unknown4", 2007457, 7154683, 4, { -357.732788f, -4.091716f, 240.942001f }, 1.000000f );
      instance->registerEObj( "Unknown5", 2002872, 7178527, 4, { -322.993408f, -14.000000f, 237.739197f }, 1.000000f );
      instance->registerEObj( "Unknown6", 2002735, 0, 4, { -323.681213f, -13.915580f, 238.152405f }, 0.520000f );
      instance->registerEObj( "Unknown7", 2002872, 7178530, 4, { -363.058411f, -14.000000f, 250.964600f }, 1.000000f );
      instance->registerEObj( "Unknown8", 2009284, 0, 4, { -334.828705f, -13.901060f, 251.636505f }, 0.991760f );
      instance->registerEObj( "Unknown9", 2009285, 0, 4, { -348.204712f, -13.892940f, 243.150803f }, 1.000000f );
      instance->registerEObj( "Unknown10", 2009286, 0, 4, { -341.067108f, -13.892940f, 237.005600f }, 1.000000f );
      instance->registerEObj( "Unknown11", 2002872, 7178955, 4, { -0.015300f, -0.015300f, 318.593109f }, 0.991760f );
      instance->registerEObj( "Unknown12", 2002735, 0, 4, { -0.015320f, -0.015320f, 318.593109f }, 1.388489f );
      instance->registerEObj( "Entrance", 2000182, 7170984, 5, { -168.370193f, 53.116581f, -447.149506f }, 0.991760f );
      instance->registerEObj( "Shortcut", 2000700, 0, 4, { -165.940704f, 53.142620f, -435.801300f }, 1.000000f );
      instance->registerEObj( "Exit", 2000139, 0, 4, { 0.000000f, -0.000000f, 285.000000f }, 1.000000f );
      instance->registerEObj( "Unknown14", 2007457, 7141324, 4, { -0.193053f, 53.508301f, -157.354904f }, 0.991760f );
      instance->registerEObj( "Unknown15", 2007457, 7174264, 4, { 57.117458f, 53.142620f, -213.119202f }, 1.000000f );
      instance->registerEObj( "Unknown16", 2007457, 7170395, 4, { -0.015320f, 46.597000f, -350.082092f }, 0.991760f );
      instance->registerEObj( "Allaganteleporter", 2009278, 0, 4, { 0.002865f, 46.599701f, -377.001007f }, 0.991760f );
      instance->registerEObj( "Unknown17", 2007457, 7141398, 4, { -147.123795f, 53.529110f, -369.004913f }, 0.991760f );
      instance->registerEObj( "Unknown18", 2007457, 7141397, 4, { -82.715157f, 42.516201f, -199.536606f }, 0.991760f );
      instance->registerEObj( "Unknown19", 2007457, 7141396, 4, { 57.117241f, 53.527908f, -213.116699f }, 0.991760f );
      instance->registerEObj( "Tornnavigatorslogpage", 2009412, 0, 4, { -132.524704f, 53.177608f, -407.217499f }, 0.991760f );
      instance->registerEObj( "Unknown20", 2007457, 7141895, 4, { -305.774811f, -0.751164f, 94.720772f }, 1.000000f );
      instance->registerEObj( "Unknown21", 2007457, 7167075, 4, { -291.432098f, -0.015320f, 191.088593f }, 0.991760f );
      instance->registerEObj( "Tornnavigatorslogpage", 2009413, 0, 4, { -202.481003f, 0.052476f, 171.440704f }, 1.000000f );
      instance->registerEObj( "Unknown22", 2007457, 7170446, 4, { 78.733200f, 20.000000f, 245.622299f }, 0.991760f );
      instance->registerEObj( "Unknown23", 2007457, 7170445, 4, { 29.878000f, 12.000000f, 404.197998f }, 1.000000f );
      instance->registerEObj( "Securityterminal", 2009276, 7188820, 4, { 67.426903f, 12.000000f, 331.441711f }, 1.000000f );
      instance->registerEObj( "Securityterminal", 2009277, 7188819, 4, { 0.000000f, 12.000000f, 370.000000f }, 1.000000f );
      instance->registerEObj( "Unknown24", 2007457, 7336140, 4, { 69.068199f, 12.000000f, 332.207001f }, 1.000000f );
      instance->registerEObj( "Unknown25", 2007457, 7336141, 4, { 0.000000f, 12.000000f, 371.396515f }, 1.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};