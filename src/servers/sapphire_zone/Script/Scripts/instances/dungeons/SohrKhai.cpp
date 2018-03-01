#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class SohrKhai : public InstanceContentScript
{
public:
   SohrKhai() : InstanceContentScript( 44 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Unknown0", 2002872, 6258645, 4, { 400.881195f, -19.484011f, -332.214996f }, 1.000000f );
      instance->registerEObj( "Unknown1", 2002735, 0, 4, { 400.118713f, -18.543800f, -338.582886f }, 1.000000f );
      instance->registerEObj( "Unknown2", 2007078, 6220718, 4, { -400.506195f, 0.390429f, 82.229874f }, 1.000000f );
      instance->registerEObj( "Unknown3", 2007079, 6220719, 4, { -400.289886f, 0.381470f, -77.470093f }, 0.991760f );
      instance->registerEObj( "Unknown4", 2007189, 0, 4, { -425.070587f, -0.015320f, 5.569519f }, 0.991760f );
      instance->registerEObj( "Unknown5", 2007084, 6241486, 4, { 377.864990f, 0.390429f, 352.375702f }, 1.000000f );
      instance->registerEObj( "Unknown6", 2007087, 6242639, 4, { 399.851196f, -58.700001f, -128.611893f }, 1.000000f );
      instance->registerEObj( "Unknown7", 2007088, 6242640, 4, { 363.607697f, -38.700001f, -242.258194f }, 1.000000f );
      instance->registerEObj( "Unknown8", 2007089, 6242641, 4, { 400.331604f, -18.700001f, -336.562897f }, 1.000000f );
      instance->registerEObj( "Unknown9", 2007090, 6229304, 4, { 423.391998f, -40.024479f, -205.523697f }, 0.991760f );
      instance->registerEObj( "Unknown10", 2002872, 6258669, 4, { -400.654388f, 9.235634f, -135.696106f }, 1.000000f );
      instance->registerEObj( "Unknown11", 2007082, 6258670, 4, { -400.434387f, 8.000000f, -177.220200f }, 1.000000f );
      instance->registerEObj( "Unknown12", 2002735, 0, 4, { -400.177612f, 8.431900f, -137.820801f }, 1.000000f );
      instance->registerEObj( "Unknown13", 2007083, 6238460, 4, { -401.279297f, 9.299995f, -184.260300f }, 1.000000f );
      instance->registerEObj( "Unknown14", 2002872, 6258680, 4, { 399.753113f, 9.358741f, 161.151505f }, 1.000000f );
      instance->registerEObj( "Unknown15", 2002735, 0, 4, { 400.071198f, 9.620000f, 156.602402f }, 1.000000f );
      instance->registerEObj( "Unknown16", 2007085, 6242340, 4, { 397.968506f, 9.664823f, 157.574600f }, 1.000000f );
      instance->registerEObj( "Unknown17", 2007086, 6241485, 4, { 398.938812f, 24.959961f, 85.423576f }, 1.000000f );
      instance->registerEObj( "Unknown18", 2007158, 6241490, 4, { 407.500000f, 24.959999f, 89.161400f }, 1.000000f );
      instance->registerEObj( "Unknown19", 2007159, 6241491, 4, { 407.500000f, 24.959999f, 99.161400f }, 1.000000f );
      instance->registerEObj( "Unknown20", 2007160, 6241492, 4, { 407.500000f, 24.959999f, 109.161400f }, 1.000000f );
      instance->registerEObj( "Unknown21", 2007161, 6241493, 4, { 407.500000f, 24.959999f, 119.161400f }, 1.000000f );
      instance->registerEObj( "Unknown22", 2007162, 6241489, 4, { 392.500000f, 24.959999f, 89.161400f }, 1.000000f );
      instance->registerEObj( "Unknown23", 2007163, 6241488, 4, { 392.500000f, 24.959999f, 99.161400f }, 1.000000f );
      instance->registerEObj( "Unknown24", 2007164, 6241487, 4, { 392.500000f, 24.959999f, 109.161400f }, 1.000000f );
      instance->registerEObj( "Unknown25", 2007165, 6241484, 4, { 392.500000f, 24.959999f, 119.161400f }, 1.000000f );
      instance->registerEObj( "Entrance", 2000182, 6258660, 5, { -406.742615f, -8.000000f, 164.927795f }, 1.000000f );
      instance->registerEObj( "Shortcut", 2000700, 0, 4, { -393.089386f, -8.000000f, 150.811401f }, 1.000000f );
      instance->registerEObj( "Exit", 2000139, 0, 4, { 399.538910f, -50.000011f, -494.319092f }, 1.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};