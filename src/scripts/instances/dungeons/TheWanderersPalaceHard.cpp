#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheWanderersPalaceHard : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheWanderersPalaceHard() : Sapphire::ScriptAPI::InstanceContentScript( 30 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.addEObj( "sgvf_w_lvd_b0250", 2000277, 4898030, 4898031, 4, { 125.461502f, -12.000000f, 89.079697f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "sgvf_w_lvd_b0094", 2001810, 4898029, 4898014, 4, { 124.986603f, -12.039370f, 125.401100f }, 0.991760f, 0.000048f, 0); 
    // States -> vf_line_on (id: 12) vf_line_of (id: 13) 
    instance.addEObj( "sgvf_w_lvd_b0118", 2001811, 4898028, 4898013, 4, { 127.094200f, -12.000000f, 125.826500f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "sgvf_w_lvd_b0094_1", 2001812, 4898056, 4898039, 4, { 43.121960f, -0.015320f, -212.616592f }, 0.991760f, 0.000048f, 0); 
    // States -> vf_line_on (id: 12) vf_line_of (id: 13) 
    instance.addEObj( "sgvf_w_lvd_b0118_1", 2001813, 4898057, 4898038, 4, { 45.925018f, 0.000000f, -212.411499f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "sgvf_w_lvd_b0118_2", 2000278, 4898058, 4898059, 4, { 43.472900f, -0.106873f, -248.065994f }, 0.991760f, 0.000048f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "sgpl_s1d3_bosswall", 2001815, 4898090, 4898088, 4, { 74.753906f, 9.964111f, -400.351013f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "sgpl_s1d3_bossline", 2001814, 4898089, 4898087, 4, { 72.890900f, 9.976854f, -400.332489f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_0", 2005119, 0, 5582003, 4, { 68.684860f, 6.000000f, -449.635315f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "sgvf_w_lvd_b0118_3", 2005196, 5674432, 5674433, 4, { 72.966209f, 6.000000f, -464.577209f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "Shortcut", 2000700, 0, 4898007, 4, { 137.285400f, -17.990419f, 454.398407f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Exit", 2000139, 0, 4898008, 4, { 73.105957f, 9.994568f, -475.590790f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Entrance", 2000182, 4898005, 4898009, 5, { 130.745697f, -17.983120f, 461.438293f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.addEObj( "unknown_1", 2004551, 5018234, 4949901, 4, { 184.679901f, -14.023070f, 304.066406f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_2", 2004552, 5018233, 4949903, 4, { 125.230698f, -14.053590f, 244.800400f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_3", 2004553, 5018223, 4949905, 4, { 124.956100f, -14.023070f, 183.581207f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_4", 2004554, 5018182, 4949907, 4, { 42.770088f, -0.167908f, -26.822309f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_5", 2004555, 5018205, 4949908, 4, { 42.862549f, 0.442505f, -150.225098f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Asylumcell", 2004556, 5019054, 4949912, 4, { 71.785713f, -11.783800f, -311.787598f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Asylumcell_1", 2004557, 5019055, 4949913, 4, { 71.870552f, -11.659170f, -324.391602f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_6", 2004558, 5019051, 4949914, 4, { 94.316040f, -12.008810f, -312.062286f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_7", 2004559, 5019004, 4949915, 4, { 161.119995f, -8.011047f, -353.322693f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_8", 2004560, 5018224, 4949917, 4, { 73.226128f, 10.390440f, -379.721588f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_9", 2004561, 5034792, 4985790, 4, { 120.347900f, -12.000000f, -338.826599f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Drainagevalve", 2004562, 5022359, 4985791, 4, { 124.002098f, -10.704290f, -341.825287f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_10", 2004564, 5018828, 4985792, 4, { 141.315598f, -11.750000f, -326.359711f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Nymiandevice", 2004565, 4896865, 4985793, 4, { 156.023407f, -6.851379f, -351.735809f }, 0.991760f, 0.000048f, 0); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheWanderersPalaceHard );