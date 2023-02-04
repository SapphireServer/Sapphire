#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheWorldofDarkness : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheWorldofDarkness() : Sapphire::ScriptAPI::InstanceContentScript( 30020 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.addEObj( "sgvf_w_lvd_b0118", 2002872, 5033058, 5033055, 4, { -148.309006f, 25.000000f, 327.505005f }, 1.000000f, -0.785398f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "unknown_0", 2002735, 0, 5033056, 4, { -147.190506f, 34.000000f, 326.593597f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "sgvf_w_lvd_b0118_1", 2002872, 5033059, 5033057, 4, { -116.020401f, 25.000000f, 291.514313f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "unknown_1", 2004749, 5022919, 5033113, 4, { -150.811707f, 33.999840f, 292.778412f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_2", 2004750, 5022920, 5033114, 4, { -143.519608f, 34.000000f, 294.027710f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_3", 2004751, 5022915, 5033115, 4, { -143.096893f, 34.000000f, 301.814209f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_4", 2004752, 5022916, 5033116, 4, { -151.221893f, 34.000000f, 301.291809f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_5", 2004753, 5034307, 5033117, 4, { -153.117905f, 34.000000f, 292.031494f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_6", 2004754, 5034303, 5033118, 4, { -141.245300f, 34.000000f, 291.586212f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_7", 2004755, 5034301, 5033119, 4, { -141.807693f, 34.000000f, 303.198395f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_8", 2004756, 5034306, 5033121, 4, { -151.877304f, 34.000000f, 303.085297f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_9", 2004748, 5033636, 5033125, 4, { -149.922104f, 34.000000f, 293.955414f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_10", 2004774, 5033642, 5035240, 4, { -144.841095f, 34.000000f, 295.275208f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_11", 2004775, 5033641, 5035241, 4, { -144.940308f, 34.000000f, 300.121399f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_12", 2004776, 5033639, 5035242, 4, { -150.097397f, 34.000000f, 299.867798f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "sgvf_l1r3_b0541a", 2005026, 5444436, 5444438, 4, { -147.017593f, 34.000000f, 317.352814f }, 1.000000f, 0.000000f, 0); 
    // States -> boss_pop_off_a (id: 2) boss_pop_on_a (id: 3) boss_pop_on_c (id: 5) 
    instance.addEObj( "sgvf_w_lvd_b0118_2", 2002872, 5033193, 5033170, 4, { 200.082001f, 81.974503f, 211.096603f }, 1.000000f, -0.785398f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "unknown_13", 2002735, 0, 5033172, 4, { 200.000000f, 82.124329f, 208.778595f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "sgvf_w_lvd_b0118_3", 2002872, 5035970, 5033173, 4, { 167.647797f, 81.909058f, 178.824493f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "unknown_14", 2004777, 0, 5035758, 4, { 192.319397f, 82.000000f, 182.835999f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_15", 2004778, 0, 5035759, 4, { 197.039703f, 81.986687f, 184.863007f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_16", 2004779, 0, 5035760, 4, { 204.338196f, 82.000000f, 183.053802f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_17", 2004780, 0, 5035761, 4, { 189.642700f, 82.000000f, 176.451202f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_18", 2005018, 0, 5572609, 4, { 199.442200f, 82.000000f, 183.869598f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_19", 2002587, 0, 5040838, 4, { 0.000000f, 129.250000f, -157.414307f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "sgvf_w_lvd_b0118_4", 2002872, 5040833, 5040850, 4, { -0.855141f, 129.250000f, -164.190598f }, 0.991760f, -0.785362f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "unknown_20", 2002872, 5039743, 5040860, 4, { 0.048592f, 128.906403f, -155.346100f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Openfetter", 2004787, 0, 5040915, 4, { 2.542549f, 129.250000f, -205.570496f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Openfetter_1", 2004789, 0, 5040916, 4, { 3.817404f, 129.250000f, -207.100800f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Magickedfetter", 2004790, 5039668, 5040917, 4, { -17.519341f, 129.250000f, -235.697693f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Magickedfetter_1", 2004791, 5039667, 5040918, 4, { 17.275551f, 129.198105f, -235.656799f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_21", 2004808, 5039717, 5041054, 4, { -10.696810f, -497.601990f, -204.956100f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_22", 2004809, 5039714, 5041055, 4, { 6.635397f, -498.601898f, -210.257507f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_23", 2004810, 5039710, 5041056, 4, { 11.312720f, -498.093597f, -196.581207f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_24", 2004811, 5039721, 5041057, 4, { -9.022294f, -499.107513f, -190.416397f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_25", 2004548, 0, 5721742, 4, { 1.212110f, 129.300003f, -202.733398f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_26", 2002735, 0, 5041152, 4, { -0.000000f, 143.250000f, -314.710114f }, 1.000000f, 0.000048f, 0); 
    instance.addEObj( "sgvf_w_lvd_b0118_5", 2002872, 5041153, 5041154, 4, { -0.147327f, 143.250000f, -328.516998f }, 0.991760f, -0.785362f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "unknown_27", 2004732, 5039981, 5032332, 4, { -0.015320f, 143.236298f, -316.334808f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Exit", 2000139, 0, 5041170, 4, { -299.977112f, 279.987701f, -420.645508f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_28", 2004814, 0, 5041569, 4, { -300.240906f, 280.000000f, -402.510712f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_29", 2004815, 0, 5041570, 4, { -300.687103f, 280.000000f, -398.160706f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_30", 2004620, 0, 5118210, 4, { 0.203211f, 129.250000f, -202.244904f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "sgvf_w_btl_b0528", 2004816, 5041561, 5041566, 4, { -304.280212f, 279.987701f, -415.243805f }, 0.991760f, 0.000048f, 0); 
    // States -> baria_off (id: 3) baria_omen_a (id: 4) baria_omen_b (id: 5) baria_a (id: 6) baria_b (id: 7) baria_c (id: 8) 
    instance.addEObj( "sgvf_w_btl_b0528_1", 2004817, 5041563, 5041567, 4, { -286.856506f, 280.000000f, -392.695404f }, 1.000000f, 0.000000f, 0); 
    // States -> baria_off (id: 3) baria_omen_a (id: 4) baria_omen_b (id: 5) baria_a (id: 6) baria_b (id: 7) baria_c (id: 8) 
    instance.addEObj( "sgvf_w_btl_b0528_2", 2004818, 5041562, 5041568, 4, { -313.290710f, 280.000000f, -392.472412f }, 1.000000f, 0.000000f, 0); 
    // States -> baria_off (id: 3) baria_omen_a (id: 4) baria_omen_b (id: 5) baria_a (id: 6) baria_b (id: 7) baria_c (id: 8) 
    instance.addEObj( "sgvf_w_lvd_b0118_6", 2002872, 5032353, 5032349, 4, { -54.450321f, 16.000000f, 406.409088f }, 1.000000f, -0.785398f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "unknown_31", 2002735, 0, 5032354, 4, { -56.151901f, 16.000000f, 403.855896f }, 1.000000f, -0.785398f, 0); 
    instance.addEObj( "sgvf_w_lvd_b0118_7", 2002872, 5032356, 5032362, 4, { -102.950996f, 16.000000f, 383.202911f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "sgvf_l1r3_b0541b", 2004735, 5437119, 5444426, 4, { -76.985458f, 16.000000f, 382.746613f }, 1.000000f, 0.000000f, 0); 
    // States -> boss_pop2_off_a (id: 2) boss_pop2_on_a (id: 3) 
    instance.addEObj( "unknown_32", 2004736, 0, 5444427, 4, { -74.916229f, 16.000000f, 380.485291f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_33", 2002735, 0, 5035967, 4, { 99.718719f, 63.999989f, 265.143799f }, 1.000000f, -1.570451f, 0); 
    instance.addEObj( "sgvf_w_lvd_b0118_8", 2002872, 5035968, 5035971, 4, { 95.926514f, 63.980949f, 265.796906f }, 0.991760f, -0.785362f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "sgvf_w_lvd_b0118_9", 2002872, 5035969, 5035972, 4, { 167.944199f, 65.533363f, 264.945587f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "Treasurecoffer", 2004745, 0, 5035978, 4, { 130.000000f, 63.999989f, 264.710388f }, 1.000000f, 1.570796f, 0); 
    instance.addEObj( "sgvf_l1r3_b0541b_1", 2004738, 5437120, 5035981, 4, { 130.000000f, 65.431679f, 264.710388f }, 0.991760f, 0.000048f, 0); 
    // States -> boss_pop2_off_a (id: 2) boss_pop2_on_a (id: 3) 
    instance.addEObj( "sgvf_w_lvd_b0556", 2004739, 5037994, 5035987, 4, { 138.468002f, 63.999989f, 275.781311f }, 1.000000f, 0.000000f, 0); 
    // States -> void_off_a (id: 2) void_off_b (id: 3) void_on_a (id: 4) void_omen (id: 5) 
    instance.addEObj( "sgvf_w_lvd_b0556_1", 2004740, 5037996, 5035988, 4, { 129.901001f, 63.999729f, 278.588593f }, 1.000000f, 0.000000f, 0); 
    // States -> void_off_a (id: 2) void_off_b (id: 3) void_on_a (id: 4) void_omen (id: 5) 
    instance.addEObj( "sgvf_w_lvd_b0556_2", 2004741, 5037997, 5035989, 4, { 121.644699f, 63.999729f, 275.762695f }, 1.000000f, 0.000000f, 0); 
    // States -> void_off_a (id: 2) void_off_b (id: 3) void_on_a (id: 4) void_omen (id: 5) 
    instance.addEObj( "sgvf_w_lvd_b0556_3", 2004742, 5037998, 5035991, 4, { 138.356506f, 63.999989f, 250.555603f }, 1.000000f, 0.000000f, 0); 
    // States -> void_off_a (id: 2) void_off_b (id: 3) void_on_a (id: 4) void_omen (id: 5) 
    instance.addEObj( "sgvf_w_lvd_b0556_4", 2004743, 5037999, 5035992, 4, { 129.881393f, 64.000031f, 250.721893f }, 1.000000f, 0.000000f, 0); 
    // States -> void_off_a (id: 2) void_off_b (id: 3) void_on_a (id: 4) void_omen (id: 5) 
    instance.addEObj( "sgvf_w_lvd_b0556_5", 2004744, 5038000, 5035993, 4, { 121.628601f, 63.999989f, 250.572296f }, 1.000000f, 0.000000f, 0); 
    // States -> void_off_a (id: 2) void_off_b (id: 3) void_on_a (id: 4) void_omen (id: 5) 
    instance.addEObj( "sgvf_w_lvd_b0557", 2004746, 5037995, 5035994, 4, { 130.020493f, 63.999748f, 279.027191f }, 1.000000f, 0.000000f, 0); 
    // States -> void_off_a (id: 2) void_off_b (id: 3) void_on_a (id: 4) void_omen (id: 5) 
    instance.addEObj( "sgvf_w_lvd_b0557_1", 2004747, 5038001, 5035995, 4, { 130.056702f, 63.999989f, 249.980301f }, 1.000000f, 0.000000f, 0); 
    // States -> void_off_a (id: 2) void_off_b (id: 3) void_on_a (id: 4) void_omen (id: 5) 
    instance.addEObj( "unknown_34", 2002735, 0, 5038253, 4, { 0.000000f, 94.750053f, 84.669502f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_35", 2004788, 5499560, 5038652, 4, { 0.320374f, 95.231567f, 31.296261f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_36", 2004792, 5038584, 5038657, 4, { -28.578890f, 95.250008f, 39.174721f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_37", 2004793, 5038586, 5038658, 4, { -21.418350f, 95.250008f, 51.649750f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_38", 2004794, 5038587, 5038659, 4, { -33.994980f, 95.250008f, 58.976070f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_39", 2004795, 5038580, 5038660, 4, { -41.014271f, 95.250008f, 46.442242f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_40", 2004796, 5038588, 5038661, 4, { 7.240406f, 95.250008f, -12.319770f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_41", 2004797, 5038590, 5038663, 4, { 7.179711f, 95.250008f, 2.152661f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_42", 2004798, 5038589, 5038664, 4, { -7.245643f, 95.250008f, 2.096094f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_43", 2004799, 5038570, 5038665, 4, { -7.080731f, 95.250008f, -12.155750f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_44", 2004800, 5038591, 5038666, 4, { 41.068710f, 95.250008f, 46.325569f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_45", 2004801, 5038592, 5038667, 4, { 33.762070f, 95.250008f, 58.721840f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_46", 2004802, 5038593, 5038668, 4, { 21.204290f, 95.250008f, 51.578461f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_47", 2004803, 5038571, 5038669, 4, { 28.640770f, 95.250008f, 39.349319f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "sgvf_w_lvd_b0250", 2002872, 5038256, 5040843, 4, { -0.165812f, 94.731613f, 85.317574f }, 0.991760f, -0.785362f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "unknown_48", 2004784, 5489265, 5045718, 4, { 0.294310f, 90.349991f, 22.469700f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_49", 2005042, 5476812, 5573432, 4, { -0.380919f, 99.969032f, 29.779119f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Entrance", 2000182, 5032012, 5032013, 5, { 0.112444f, 1.000004f, 460.032898f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.addEObj( "Wormholegenerator", 2004722, 4985258, 5032035, 4, { -9.284863f, 0.332117f, 436.627411f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Wormholegenerator_1", 2004723, 4985259, 5032036, 4, { -157.081207f, 25.477930f, 382.938385f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Wormholegenerator_2", 2004724, 4985260, 5032037, 4, { 65.994957f, 65.452766f, 265.003998f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Wormholegenerator_3", 2004725, 4985261, 5032038, 4, { 210.040405f, 73.397346f, 264.987091f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Wormholegenerator_4", 2004726, 4985262, 5032042, 4, { 9.958203f, 96.762039f, 104.047096f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Wormholegenerator_5", 2004727, 4985263, 5032043, 4, { -9.978291f, 128.313095f, -121.979301f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Wormholegenerator_6", 2004728, 4985264, 5032044, 4, { 9.998364f, 128.645798f, -274.001892f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_50", 2004729, 5034813, 5032065, 4, { -91.447388f, 32.791962f, 296.223389f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_51", 2004730, 5034821, 5032066, 4, { 143.374405f, 80.799957f, 179.826706f }, 1.000000f, 0.000000f, 0); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheWorldofDarkness );