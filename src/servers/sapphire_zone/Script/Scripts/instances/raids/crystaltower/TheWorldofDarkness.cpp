#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Zone/InstanceContent.h>

class TheWorldofDarkness : public InstanceContentScript
{
public:
   TheWorldofDarkness() : InstanceContentScript( 30020 )
   { }

   void onInit( InstanceContentPtr instance ) override
   {
      
      instance->registerEObj( "Unknown0", 2002872, 5033058, 4, { -148.309006f, 25.000000f, 327.505005f }, 1.000000f );
      instance->registerEObj( "Unknown1", 2002735, 0, 4, { -147.190506f, 34.000000f, 326.593597f }, 1.000000f );
      instance->registerEObj( "Unknown2", 2002872, 5033059, 4, { -116.020401f, 25.000000f, 291.514313f }, 1.000000f );
      instance->registerEObj( "Unknown3", 2004749, 5022919, 4, { -150.811707f, 33.999840f, 292.778412f }, 1.000000f );
      instance->registerEObj( "Unknown4", 2004750, 5022920, 4, { -143.519608f, 34.000000f, 294.027710f }, 1.000000f );
      instance->registerEObj( "Unknown5", 2004751, 5022915, 4, { -143.096893f, 34.000000f, 301.814209f }, 1.000000f );
      instance->registerEObj( "Unknown6", 2004752, 5022916, 4, { -151.221893f, 34.000000f, 301.291809f }, 1.000000f );
      instance->registerEObj( "Unknown7", 2004753, 5034307, 4, { -153.117905f, 34.000000f, 292.031494f }, 0.991760f );
      instance->registerEObj( "Unknown8", 2004754, 5034303, 4, { -141.245300f, 34.000000f, 291.586212f }, 1.000000f );
      instance->registerEObj( "Unknown9", 2004755, 5034301, 4, { -141.807693f, 34.000000f, 303.198395f }, 1.000000f );
      instance->registerEObj( "Unknown10", 2004756, 5034306, 4, { -151.877304f, 34.000000f, 303.085297f }, 1.000000f );
      instance->registerEObj( "Unknown11", 2004748, 5033636, 4, { -149.922104f, 34.000000f, 293.955414f }, 1.000000f );
      instance->registerEObj( "Unknown12", 2004774, 5033642, 4, { -144.841095f, 34.000000f, 295.275208f }, 1.000000f );
      instance->registerEObj( "Unknown13", 2004775, 5033641, 4, { -144.940308f, 34.000000f, 300.121399f }, 1.000000f );
      instance->registerEObj( "Unknown14", 2004776, 5033639, 4, { -150.097397f, 34.000000f, 299.867798f }, 1.000000f );
      instance->registerEObj( "Unknown15", 2005026, 5444436, 4, { -147.017593f, 34.000000f, 317.352814f }, 1.000000f );
      instance->registerEObj( "Unknown16", 2002872, 5033193, 4, { 200.082001f, 81.974503f, 211.096603f }, 1.000000f );
      instance->registerEObj( "Unknown17", 2002735, 0, 4, { 200.000000f, 82.124329f, 208.778595f }, 1.000000f );
      instance->registerEObj( "Unknown18", 2002872, 5035970, 4, { 167.647797f, 81.909058f, 178.824493f }, 1.000000f );
      instance->registerEObj( "Unknown19", 2004777, 0, 4, { 192.319397f, 82.000000f, 182.835999f }, 1.000000f );
      instance->registerEObj( "Unknown20", 2004778, 0, 4, { 197.039703f, 81.986687f, 184.863007f }, 0.991760f );
      instance->registerEObj( "Unknown21", 2004779, 0, 4, { 204.338196f, 82.000000f, 183.053802f }, 1.000000f );
      instance->registerEObj( "Unknown22", 2004780, 0, 4, { 189.642700f, 82.000000f, 176.451202f }, 1.000000f );
      instance->registerEObj( "Unknown23", 2005018, 0, 4, { 199.442200f, 82.000000f, 183.869598f }, 1.000000f );
      instance->registerEObj( "Unknown24", 2002587, 0, 4, { 0.000000f, 129.250000f, -157.414307f }, 1.000000f );
      instance->registerEObj( "Unknown25", 2002872, 5040833, 4, { -0.855141f, 129.250000f, -164.190598f }, 0.991760f );
      instance->registerEObj( "Unknown26", 2002872, 5039743, 4, { 0.048592f, 128.906403f, -155.346100f }, 1.000000f );
      instance->registerEObj( "Openfetter", 2004787, 0, 4, { 2.542549f, 129.250000f, -205.570496f }, 1.000000f );
      instance->registerEObj( "Openfetter", 2004789, 0, 4, { 3.817404f, 129.250000f, -207.100800f }, 1.000000f );
      instance->registerEObj( "Magickedfetter", 2004790, 5039668, 4, { -17.519341f, 129.250000f, -235.697693f }, 1.000000f );
      instance->registerEObj( "Magickedfetter", 2004791, 5039667, 4, { 17.275551f, 129.198105f, -235.656799f }, 0.991760f );
      instance->registerEObj( "Unknown27", 2004808, 5039717, 4, { -10.696810f, -497.601990f, -204.956100f }, 1.000000f );
      instance->registerEObj( "Unknown28", 2004809, 5039714, 4, { 6.635397f, -498.601898f, -210.257507f }, 1.000000f );
      instance->registerEObj( "Unknown29", 2004810, 5039710, 4, { 11.312720f, -498.093597f, -196.581207f }, 1.000000f );
      instance->registerEObj( "Unknown30", 2004811, 5039721, 4, { -9.022294f, -499.107513f, -190.416397f }, 1.000000f );
      instance->registerEObj( "Unknown31", 2004548, 0, 4, { 1.212110f, 129.300003f, -202.733398f }, 1.000000f );
      instance->registerEObj( "Unknown32", 2002735, 0, 4, { -0.000000f, 143.250000f, -314.710114f }, 1.000000f );
      instance->registerEObj( "Unknown33", 2002872, 5041153, 4, { -0.147327f, 143.250000f, -328.516998f }, 0.991760f );
      instance->registerEObj( "Unknown34", 2004732, 5039981, 4, { -0.015320f, 143.236298f, -316.334808f }, 0.991760f );
      instance->registerEObj( "Exit", 2000139, 0, 4, { -299.977112f, 279.987701f, -420.645508f }, 0.991760f );
      instance->registerEObj( "Unknown35", 2004814, 0, 4, { -300.240906f, 280.000000f, -402.510712f }, 1.000000f );
      instance->registerEObj( "Unknown36", 2004815, 0, 4, { -300.687103f, 280.000000f, -398.160706f }, 1.000000f );
      instance->registerEObj( "Unknown37", 2004620, 0, 4, { 0.203211f, 129.250000f, -202.244904f }, 1.000000f );
      instance->registerEObj( "Unknown38", 2004816, 5041561, 4, { -304.280212f, 279.987701f, -415.243805f }, 0.991760f );
      instance->registerEObj( "Unknown39", 2004817, 5041563, 4, { -286.856506f, 280.000000f, -392.695404f }, 1.000000f );
      instance->registerEObj( "Unknown40", 2004818, 5041562, 4, { -313.290710f, 280.000000f, -392.472412f }, 1.000000f );
      instance->registerEObj( "Unknown41", 2002872, 5032353, 4, { -54.450321f, 16.000000f, 406.409088f }, 1.000000f );
      instance->registerEObj( "Unknown42", 2002735, 0, 4, { -56.151901f, 16.000000f, 403.855896f }, 1.000000f );
      instance->registerEObj( "Unknown43", 2002872, 5032356, 4, { -102.950996f, 16.000000f, 383.202911f }, 1.000000f );
      instance->registerEObj( "Unknown44", 2004735, 5437119, 4, { -76.985458f, 16.000000f, 382.746613f }, 1.000000f );
      instance->registerEObj( "Unknown45", 2004736, 0, 4, { -74.916229f, 16.000000f, 380.485291f }, 1.000000f );
      instance->registerEObj( "Unknown46", 2002735, 0, 4, { 99.718719f, 63.999989f, 265.143799f }, 1.000000f );
      instance->registerEObj( "Unknown47", 2002872, 5035968, 4, { 95.926514f, 63.980949f, 265.796906f }, 0.991760f );
      instance->registerEObj( "Unknown48", 2002872, 5035969, 4, { 167.944199f, 65.533363f, 264.945587f }, 1.000000f );
      instance->registerEObj( "Treasurecoffer", 2004745, 0, 4, { 130.000000f, 63.999989f, 264.710388f }, 1.000000f );
      instance->registerEObj( "Unknown49", 2004738, 5437120, 4, { 130.000000f, 65.431679f, 264.710388f }, 0.991760f );
      instance->registerEObj( "Unknown50", 2004739, 5037994, 4, { 138.468002f, 63.999989f, 275.781311f }, 1.000000f );
      instance->registerEObj( "Unknown51", 2004740, 5037996, 4, { 129.901001f, 63.999729f, 278.588593f }, 1.000000f );
      instance->registerEObj( "Unknown52", 2004741, 5037997, 4, { 121.644699f, 63.999729f, 275.762695f }, 1.000000f );
      instance->registerEObj( "Unknown53", 2004742, 5037998, 4, { 138.356506f, 63.999989f, 250.555603f }, 1.000000f );
      instance->registerEObj( "Unknown54", 2004743, 5037999, 4, { 129.881393f, 64.000031f, 250.721893f }, 1.000000f );
      instance->registerEObj( "Unknown55", 2004744, 5038000, 4, { 121.628601f, 63.999989f, 250.572296f }, 1.000000f );
      instance->registerEObj( "Unknown56", 2004746, 5037995, 4, { 130.020493f, 63.999748f, 279.027191f }, 1.000000f );
      instance->registerEObj( "Unknown57", 2004747, 5038001, 4, { 130.056702f, 63.999989f, 249.980301f }, 1.000000f );
      instance->registerEObj( "Unknown58", 2002735, 0, 4, { 0.000000f, 94.750053f, 84.669502f }, 0.991760f );
      instance->registerEObj( "Unknown59", 2004788, 5499560, 4, { 0.320374f, 95.231567f, 31.296261f }, 0.991760f );
      instance->registerEObj( "Unknown60", 2004792, 5038584, 4, { -28.578890f, 95.250008f, 39.174721f }, 1.000000f );
      instance->registerEObj( "Unknown61", 2004793, 5038586, 4, { -21.418350f, 95.250008f, 51.649750f }, 1.000000f );
      instance->registerEObj( "Unknown62", 2004794, 5038587, 4, { -33.994980f, 95.250008f, 58.976070f }, 0.991760f );
      instance->registerEObj( "Unknown63", 2004795, 5038580, 4, { -41.014271f, 95.250008f, 46.442242f }, 1.000000f );
      instance->registerEObj( "Unknown64", 2004796, 5038588, 4, { 7.240406f, 95.250008f, -12.319770f }, 1.000000f );
      instance->registerEObj( "Unknown65", 2004797, 5038590, 4, { 7.179711f, 95.250008f, 2.152661f }, 1.000000f );
      instance->registerEObj( "Unknown66", 2004798, 5038589, 4, { -7.245643f, 95.250008f, 2.096094f }, 1.000000f );
      instance->registerEObj( "Unknown67", 2004799, 5038570, 4, { -7.080731f, 95.250008f, -12.155750f }, 1.000000f );
      instance->registerEObj( "Unknown68", 2004800, 5038591, 4, { 41.068710f, 95.250008f, 46.325569f }, 1.000000f );
      instance->registerEObj( "Unknown69", 2004801, 5038592, 4, { 33.762070f, 95.250008f, 58.721840f }, 1.000000f );
      instance->registerEObj( "Unknown70", 2004802, 5038593, 4, { 21.204290f, 95.250008f, 51.578461f }, 1.000000f );
      instance->registerEObj( "Unknown71", 2004803, 5038571, 4, { 28.640770f, 95.250008f, 39.349319f }, 1.000000f );
      instance->registerEObj( "Unknown72", 2002872, 5038256, 4, { -0.165812f, 94.731613f, 85.317574f }, 0.991760f );
      instance->registerEObj( "Unknown73", 2004784, 5489265, 4, { 0.294310f, 90.349991f, 22.469700f }, 0.991760f );
      instance->registerEObj( "Unknown74", 2005042, 5476812, 4, { -0.380919f, 99.969032f, 29.779119f }, 1.000000f );
      instance->registerEObj( "Entrance", 2000182, 5032012, 5, { 0.112444f, 1.000004f, 460.032898f }, 1.000000f );
      instance->registerEObj( "Wormholegenerator", 2004722, 4985258, 4, { -9.284863f, 0.332117f, 436.627411f }, 0.991760f );
      instance->registerEObj( "Wormholegenerator", 2004723, 4985259, 4, { -157.081207f, 25.477930f, 382.938385f }, 0.991760f );
      instance->registerEObj( "Wormholegenerator", 2004724, 4985260, 4, { 65.994957f, 65.452766f, 265.003998f }, 0.991760f );
      instance->registerEObj( "Wormholegenerator", 2004725, 4985261, 4, { 210.040405f, 73.397346f, 264.987091f }, 0.991760f );
      instance->registerEObj( "Wormholegenerator", 2004726, 4985262, 4, { 9.958203f, 96.762039f, 104.047096f }, 0.991760f );
      instance->registerEObj( "Wormholegenerator", 2004727, 4985263, 4, { -9.978291f, 128.313095f, -121.979301f }, 0.991760f );
      instance->registerEObj( "Wormholegenerator", 2004728, 4985264, 4, { 9.998364f, 128.645798f, -274.001892f }, 0.991760f );
      instance->registerEObj( "Unknown76", 2004729, 5034813, 4, { -91.447388f, 32.791962f, 296.223389f }, 0.991760f );
      instance->registerEObj( "Unknown77", 2004730, 5034821, 4, { 143.374405f, 80.799957f, 179.826706f }, 1.000000f );
   }

   void onUpdate( InstanceContentPtr instance, uint32_t currTime ) override
   {

   }

   void onEnterTerritory( Entity::Player &player, uint32_t eventId, uint16_t param1, uint16_t param2 ) override
   {

   }

};