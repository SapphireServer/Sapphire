#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheBindingCoilofBahamutTurn3 :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheBindingCoilofBahamutTurn3() :
    Sapphire::ScriptAPI::InstanceContentScript( 30004 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2001046, 4204647, 4, { -38.434280f, 0.755630f, 27.186541f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_1", 2001047, 4204649, 4, { -22.930870f, -38.074230f, 51.622608f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_2", 2001048, 4204652, 4, { 17.410521f, -36.911560f, 65.506958f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_3", 2001049, 4204654, 4, { 43.230721f, -36.854370f, 41.278610f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_4", 2001050, 4204661, 4, { 41.756340f, -37.405720f, 11.258040f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_5", 2001051, 4204644, 4, { 18.406361f, -75.101082f, 30.246229f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_6", 2001052, 4204665, 4, { -30.734369f, -111.808601f, 16.055771f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_7", 2001053, 4204660, 4, { 28.263350f, -74.681847f, -39.544411f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_8", 2001054, 4204664, 4, { -8.499553f, -113.039597f, -34.010311f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_9", 2001055, 4204662, 4, { -15.483490f, -112.471001f, -20.925671f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Silentterminal", 2001132, 4322464, 4, { -6.976719f, -112.013496f, 23.202400f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { -16.955231f, -0.864158f, 0.593589f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_10", 2001152, 4238687, 4, { -1.707294f, 0.000000f, 3.048101f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_11", 2001056, 4204669, 4, { -14.240080f, -150.417404f, 1.736771f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_12", 2001057, 4204678, 4, { -29.648090f, -188.419907f, -3.748357f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_13", 2001058, 4204672, 4, { -12.738200f, -187.302002f, 51.141499f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_14", 2001059, 4204697, 4, { 0.332115f, -225.076202f, 50.155842f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_15", 2001060, 4204703, 4, { 52.345329f, -224.740707f, 37.453941f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_16", 2001061, 4204709, 4, { 46.480949f, -262.093811f, 5.845346f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_17", 2001062, 4204723, 4, { 28.585011f, -299.527008f, 19.833670f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_18", 2001063, 4204712, 4, { -15.037280f, -262.281311f, 51.584450f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_19", 2001064, 4204725, 4, { -15.719740f, -300.085785f, -22.829020f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_20", 2001065, 4204720, 4, { -0.428782f, -300.866394f, 22.938450f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_21", 2001066, 4204671, 4, { 9.075709f, -150.864899f, -17.327230f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_22", 2001067, 4204680, 4, { -25.603180f, -188.390701f, -25.489799f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_23", 2001068, 4204687, 4, { 28.229540f, -188.408707f, -2.975939f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_24", 2001069, 4204684, 4, { 37.952412f, -187.292603f, -39.644798f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_25", 2001070, 4204707, 4, { -5.330157f, -225.534607f, -50.912369f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_26", 2001071, 4204688, 4, { 23.554840f, -223.922607f, -46.970329f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_27", 2001072, 4204689, 4, { -44.635330f, -225.534607f, -27.836760f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_28", 2001073, 4204715, 4, { -24.786400f, -262.708405f, -39.642220f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_29", 2001074, 4204716, 4, { -0.141846f, -262.624695f, -63.058170f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Silentterminal_1", 2001140, 4328681, 4, { -8.207968f, -300.679108f, -11.383970f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_30", 2001075, 4204730, 4, { -27.307819f, -347.278900f, 23.850750f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_31", 2001076, 4204722, 4, { -32.117531f, -347.483307f, -18.936440f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_32", 2001077, 4204728, 4, { -0.090805f, -348.068695f, -13.361250f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_33", 2001078, 4204719, 4, { 27.568150f, -347.808289f, 23.699249f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_34", 2001106, 4204738, 4, { -64.801163f, -383.539886f, -16.602329f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_35", 2001107, 4204740, 4, { -34.187149f, -383.967804f, -51.634480f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_36", 2001108, 4204732, 4, { 58.207191f, -383.523010f, -18.762280f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_37", 2001109, 4204735, 4, { 27.461531f, -384.122589f, 40.984268f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_38", 2001110, 4204746, 4, { 22.577141f, -422.501587f, 53.173019f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_39", 2001111, 4204744, 4, { -46.433231f, -422.842804f, 34.744751f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_40", 2001112, 4204747, 4, { 17.206091f, -423.418488f, -16.318670f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Allaganterminal", 2001162, 4317929, 4, { -15.875440f, -423.430511f, 18.778770f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Silentterminal_2", 2002600, 4334493, 4, { -24.909149f, -423.472595f, 41.999378f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Entrance", 2000629, 4294859, 5, { -0.075790f, 0.000000f, 0.310051f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheBindingCoilofBahamutTurn3 );