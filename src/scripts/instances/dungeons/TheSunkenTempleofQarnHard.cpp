#include <ScriptObject.h>
#include <Territory/InstanceContent.h>
#include <Actor/EventObject.h>

using namespace Sapphire;

class TheSunkenTempleofQarnHard : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheSunkenTempleofQarnHard() : Sapphire::ScriptAPI::InstanceContentScript( 26 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    Entity::EventObjectPtr pEObj;

    pEObj = instance.addEObj( "Entrance", 2000182, 4876828, 4876827, 5, { -201.196701f, 0.682657f, 0.238411f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    pEObj->addCollisionBox( { -201.196701, 2.682657, -2.761590 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -201.186905, 2.682657, 3.238410 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -198.196701, 2.682657, 0.242301 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -204.196701, 2.682657, 0.249387 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -203.296707, 2.682657, -1.861589 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -199.096695, 2.682657, 2.338410 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -199.096695, 2.682657, -1.861589 }, 0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -203.296707, 2.682657, 2.338410 }, 0.785398, 1.400000, 4.000000, 0.250000 );

    pEObj = instance.addEObj( "Shortcut", 2000603, 0, 4876979, 4, { -172.011398f, 12.472960f, 3.615232f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_0", 2004381, 4688136, 4877201, 4, { -62.950489f, -9.042180f, -43.471519f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -62.950489, -2.542179, -43.471519 }, -0.000000, 4.558679, 7.150002, 0.500000 );

    pEObj = instance.addEObj( "Lockeddoor", 2004382, 4686911, 4877203, 4, { -52.102619f, -15.747660f, 0.003015f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -52.102619, -9.247659, 0.003015 }, -0.000000, 4.558679, 7.150002, 0.500000 );

    pEObj = instance.addEObj( "unknown_1", 2004383, 4880940, 4877205, 4, { -32.646118f, -15.322760f, -0.535999f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_2", 2004384, 4688144, 4877206, 4, { -9.445859f, -15.431120f, 0.091173f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { -9.445550, -8.984684, 0.090864 }, 0.000048, 4.482031, 7.091080, 0.495881 );

    pEObj = instance.addEObj( "unknown_3", 2002735, 0, 4877207, 4, { -24.503120f, -51.014042f, -2.151611f }, 0.991760f, 1.469946f, 0 ); 

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118", 2002872, 4877209, 4877210, 4, { -24.127260f, -49.149910f, -1.216785f }, 0.991760f, 0.000048f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -24.127142, -46.670509, -1.216904 }, 0.000048, 7.438202, 3.967041, 0.743820 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_1", 2004385, 4877211, 4877212, 4, { -33.270012f, -49.495350f, -17.436060f }, 0.991760f, 0.000048f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -33.269894, -47.015949, -17.436178 }, 0.000048, 7.438202, 3.967041, 0.743820 );

    pEObj = instance.addEObj( "sgvf_w1d8_b0492", 2004386, 4877345, 4877346, 4, { 47.455811f, -46.541481f, 18.191370f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_wall_off (id: 2) vf_wall_fade (id: 3) vf_wall_on (id: 4) 
    pEObj->addCollisionBox( { 47.755810, -44.930370, 18.544588 }, -0.000000, 7.000000, 4.000000, 0.500000 );

    pEObj = instance.addEObj( "Lockeddoor_1", 2004388, 4688151, 4877360, 4, { 166.535797f, -43.147060f, 0.015993f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { 166.536133, -36.150681, 0.015658 }, 0.000048, 5.454665, 8.126764, 0.495880 );

    pEObj = instance.addEObj( "sgvf_w1d8_b0492_1", 2004402, 4877619, 4877627, 4, { 213.946701f, -42.801571f, -0.015320f }, 0.991760f, 0.000048f, 0 ); 
    // States -> vf_wall_off (id: 2) vf_wall_fade (id: 3) vf_wall_on (id: 4) 
    pEObj->addCollisionBox( { 214.244293, -41.203732, 0.334925 }, 0.000048, 6.942322, 3.967041, 0.495880 );

    pEObj = instance.addEObj( "unknown_5", 2004389, 4688148, 4877632, 4, { 207.414703f, -1.759183f, 0.009065f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 207.414703, 6.240817, 0.259065 }, -0.000000, 5.600000, 8.000000, 0.200000 );

    pEObj = instance.addEObj( "unknown_7", 2004391, 4742442, 4877652, 4, { -44.851521f, -16.474951f, -61.569599f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_8", 2004392, 4742441, 4877654, 4, { -34.082909f, -16.222090f, -39.745499f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_9", 2004403, 4688145, 4877678, 4, { -9.412401f, -14.700150f, -48.979301f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { -9.412092, -8.253714, -48.979610 }, 0.000048, 4.482031, 7.091080, 0.495881 );

    pEObj = instance.addEObj( "unknown_10", 2004393, 4685534, 4877684, 4, { 13.954340f, -16.478741f, -36.432899f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_11", 2004394, 4688137, 4877687, 4, { 8.975560f, -14.432130f, -28.492041f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { 8.975868, -7.985687, -28.492350 }, 0.000048, 4.521117, 7.091088, 0.495880 );

    pEObj = instance.addEObj( "Magickedpedestal", 2004396, 4688166, 4877827, 4, { 53.655460f, -15.371500f, 0.015198f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { 74.482948, -4.463135, 0.015673 }, -1.570403, 5.653034, 3.967041, 0.545468 );

    pEObj = instance.addEObj( "unknown_12", 2004397, 4688139, 4877828, 4, { 70.286049f, -14.700250f, -20.531210f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { 70.286354, -8.253807, -20.531519 }, 0.000048, 4.521117, 7.091088, 0.495880 );

    pEObj = instance.addEObj( "Magickedpedestal_1", 2004398, 4685848, 4877829, 4, { 79.511627f, -15.096250f, -36.674881f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_13", 2004399, 4688140, 4877830, 4, { 70.381950f, -14.689050f, 20.486361f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { 70.382256, -8.242607, 20.486052 }, 0.000048, 4.521117, 7.091088, 0.495880 );

    pEObj = instance.addEObj( "Magickedpedestal_2", 2004400, 4685849, 4877831, 4, { 79.392357f, -14.749610f, 36.721691f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_6", 2002735, 0, 4877952, 4, { 256.782104f, -3.999999f, 0.025025f }, 1.000000f, 1.556998f, 0 ); 

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_2", 2002872, 4877953, 4877954, 4, { 257.319305f, -2.265031f, 0.350891f }, 0.991760f, 0.000048f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 257.319427, 0.214370, 0.350772 }, 0.000048, 7.438202, 3.967041, 0.743820 );

    pEObj = instance.addEObj( "Exit", 2000139, 0, 4878439, 4, { 128.831894f, -3.999020f, -0.076355f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "sgpl_w1d8_b0118_boss_wall", 2002872, 4981816, 4878457, 4, { 97.856079f, -4.013123f, -1.052917f }, 0.991760f, 0.000048f, 0 ); 
    // States -> on (id: 6) off (id: 7) 
    pEObj->addCollisionBox( { 97.647629, -1.770988, 1.171249 }, -1.553296, 7.184145, 3.233777, 0.464033 );
    pEObj->addCollisionBox( { 97.534225, -1.749418, 31.566166 }, -1.588202, 7.406870, 3.233777, 0.480091 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_3", 2004431, 4879695, 4879936, 4, { 218.928802f, -2.699499f, 0.015198f }, 0.991760f, 0.000048f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 218.928925, -0.220098, 0.015079 }, 0.000048, 7.438202, 3.967041, 0.743820 );

    pEObj = instance.addEObj( "unknown_4", 2004576, 4880984, 4979239, 4, { -32.350761f, -15.369120f, 1.208490f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_14", 2004602, 0, 5021338, 4, { 133.195908f, -4.013123f, -0.015320f }, 0.991760f, 1.570451f, 0 ); 

    pEObj = instance.addEObj( "unknown_15", 2004603, 0, 5021359, 4, { 133.195908f, -4.013123f, 12.924380f }, 0.991760f, 1.570451f, 0 ); 

    pEObj = instance.addEObj( "unknown_16", 2004709, 0, 5021365, 4, { 128.074203f, -4.000000f, 18.223900f }, 1.000000f, 0.000488f, 0 ); 

    pEObj = instance.addEObj( "unknown_17", 2004710, 0, 5021367, 4, { 115.087196f, -4.000000f, 18.223900f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_18", 2004711, 0, 5021370, 4, { 102.068398f, -4.000000f, 18.223900f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_19", 2004712, 0, 5021371, 4, { 97.276253f, -4.013123f, 12.893800f }, 0.991760f, -1.570451f, 0 ); 

    pEObj = instance.addEObj( "unknown_20", 2004713, 0, 5021374, 4, { 97.276253f, -4.013123f, -0.045776f }, 0.991760f, -1.570451f, 0 ); 

    pEObj = instance.addEObj( "unknown_21", 2004714, 0, 5021383, 4, { 97.293999f, -4.000000f, -12.961500f }, 1.000000f, -1.570451f, 0 ); 

    pEObj = instance.addEObj( "unknown_22", 2004715, 0, 5021384, 4, { 102.037003f, -4.013123f, -17.868410f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_23", 2004716, 0, 5021385, 4, { 115.069099f, -4.000000f, -17.860500f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_24", 2004717, 0, 5021386, 4, { 128.038498f, -4.013123f, -17.898861f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_25", 2004718, 0, 5021387, 4, { 133.195908f, -4.013123f, -12.954960f }, 0.991760f, 1.570451f, 0 ); 

    pEObj = instance.addEObj( "unknown_26", 2004604, 0, 5021389, 4, { 130.266205f, -4.013123f, 15.518430f }, 0.991760f, 0.785937f, 0 ); 

    pEObj = instance.addEObj( "unknown_27", 2004719, 0, 5021390, 4, { 99.982773f, -4.000000f, 15.879740f }, 1.000000f, -0.785398f, 0 ); 

    pEObj = instance.addEObj( "unknown_28", 2004720, 0, 5021391, 4, { 100.288803f, -4.000000f, -15.013530f }, 1.000000f, -0.785398f, 0 ); 

    pEObj = instance.addEObj( "unknown_29", 2004721, 0, 5021392, 4, { 130.501694f, -4.000000f, -14.939790f }, 1.000000f, 0.785398f, 0 ); 

    pEObj = instance.addEObj( "sgpl_w1d8_b0094_boss_line", 2004772, 4878447, 5034812, 4, { 98.950607f, -4.000012f, -2.245166f }, 1.000000f, 0.000000f, 0 ); 


  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onTalk( InstanceContent& instance, Entity::Player& player, Entity::EventObject& eobj, uint32_t eventId ) override
  {

  }

  void onTalk( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint64_t actorId ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

  void onLeaveTerritory( InstanceContent& instance, Entity::Player& player ) override
  {

  }

};

EXPOSE_SCRIPT( TheSunkenTempleofQarnHard );