#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class DohnMheg : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  DohnMheg() : Sapphire::ScriptAPI::InstanceContentScript( 65 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2007457, 7676213, 4, { -136.809799f, -144.500000f, -248.453598f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b1574", 2007457, 7926931, 4, { -134.172607f, -144.518204f, -258.808289f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_1", 2002735, 0, 4, { -128.526794f, -144.516602f, -224.017807f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "sgvf_w_lvd_b0118", 2007457, 7814831, 4, { -128.500000f, -144.516602f, -224.000000f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_2", 2007457, 7673124, 4, { -12.924500f, 8.194031f, 178.179596f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_3", 2007457, 7841189, 4, { 13.168520f, 8.285583f, 183.856003f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_4", 2007457, 7645074, 4, { 32.181271f, 8.285583f, 175.066696f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_5", 2007457, 7841190, 4, { 44.602051f, 8.194031f, 163.744507f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_6", 2007457, 7673125, 4, { 11.154300f, 8.407715f, 80.796509f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_7", 2007457, 0, 4, { -1.158930f, 4.983621f, -8.448570f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_8", 2007457, 7968332, 4, { -3.545372f, 6.856866f, 11.089310f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_9", 2007457, 7627510, 4, { -50.522709f, 1.419067f, -102.800102f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_10", 2007457, 7683142, 4, { 3.280701f, 11.917240f, -249.774994f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_11", 2007457, 0, 4, { 9.689453f, 21.286320f, -389.852814f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_12", 2007457, 7673272, 4, { -39.658199f, 1.815735f, -97.093201f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_13", 2007457, 7676081, 4, { -172.198105f, -179.003601f, -23.819401f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_14", 2007457, 7676084, 4, { -133.592804f, -167.498306f, -110.215897f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_15", 2007457, 7676086, 4, { -131.273407f, -156.267700f, -174.578598f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Shellcrown", 2009760, 7673457, 4, { -171.862396f, -178.759506f, -6.363098f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_16", 2009761, 0, 4, { 0.000000f, 6.850000f, 30.160000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_17", 2009761, 0, 4, { 0.000000f, 6.850000f, 30.160000f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_18", 2009761, 0, 4, { 0.000000f, 6.850000f, 30.160000f }, 1.000000f, -4.712389f); 
    instance.registerEObj( "unknown_19", 2009761, 0, 4, { 0.000000f, 6.850000f, 30.160000f }, 1.000000f, -1.570796f); 
    instance.registerEObj( "unknown_20", 2009762, 0, 4, { 0.000000f, 6.850000f, 30.160000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_21", 2009762, 0, 4, { 0.000000f, 6.850000f, 30.160000f }, 1.000000f, -4.712389f); 
    instance.registerEObj( "unknown_22", 2009762, 0, 4, { 0.000000f, 6.850000f, 30.160000f }, 1.000000f, -1.570796f); 
    instance.registerEObj( "unknown_23", 2009762, 0, 4, { 0.000000f, 6.850000f, 30.160000f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "unknown_24", 2010262, 0, 4, { 4.057446f, 5.850861f, 21.735170f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_25", 2002735, 0, 4, { 0.000000f, 6.850000f, 50.160000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2007457, 7814797, 4, { 0.000000f, 6.850000f, 50.160000f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2007457, 7814799, 4, { 0.000000f, 6.850000f, 10.160000f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_26", 2002735, 0, 4, { 7.170000f, 23.040001f, -314.603210f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2007457, 7814817, 4, { 7.170000f, 23.040001f, -314.119995f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_4", 2007457, 7814819, 4, { 7.170000f, 23.040001f, -364.119995f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "Entrance", 2000182, 7814767, 5, { -5.557194f, 15.920810f, 128.573898f }, 1.000000f, 0.000000f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { 6.232459f, 15.942540f, 129.594101f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Exit", 2000139, 0, 4, { -128.478104f, -144.500000f, -260.000000f }, 1.000000f, 0.000000f); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( DohnMheg );