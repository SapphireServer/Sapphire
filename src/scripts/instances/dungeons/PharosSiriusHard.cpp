#include <ScriptObject.h>
#include <Territory/InstanceContent.h>
#include <Actor/EventObject.h>

using namespace Sapphire;

class PharosSiriusHard : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  PharosSiriusHard() : Sapphire::ScriptAPI::InstanceContentScript( 40 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    Entity::EventObjectPtr pEObj;

    pEObj = instance.addEObj( "Shortcut", 2000700, 0, 5963640, 4, { 39.255451f, 188.130096f, -17.964260f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "Entrance", 2000182, 5963633, 5963642, 5, { 39.155338f, 189.990097f, -2.100519f }, 0.991760f, 0.000048f, 0 ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    pEObj->addCollisionBox( { 39.155575, 191.973480, -5.075895 }, 0.000048, 1.289288, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { 39.165012, 191.973755, 0.874667 }, 0.000048, 1.289288, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { 42.130714, 191.973480, -2.096613 }, -1.570403, 1.289288, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { 36.180153, 191.973755, -2.089871 }, -1.570403, 1.289288, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { 37.072838, 191.973618, -4.183411 }, -0.785350, 1.388464, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { 41.238029, 191.973618, -0.017817 }, -0.785350, 1.388464, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { 41.238232, 191.973419, -4.183211 }, 0.785446, 1.388464, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { 37.072636, 191.973816, -0.018017 }, 0.785446, 1.388464, 3.967041, 0.247940 );

    pEObj = instance.addEObj( "Exit", 2000139, 0, 5963644, 4, { -95.418854f, -5.446677f, -305.998199f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118", 2002872, 5963936, 5963937, 4, { -1.480164f, 93.003777f, -23.788879f }, 0.991760f, 0.000048f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -1.480045, 95.483177, -23.788998 }, 0.000048, 7.438202, 3.967041, 0.743820 );

    pEObj = instance.addEObj( "unknown_0", 2002735, 0, 5963938, 4, { -0.228943f, 93.016541f, -22.052860f }, 0.869751f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_1", 2002872, 5963943, 5963940, 4, { 21.051910f, 90.039482f, -0.641622f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 21.051910, 92.539482, -0.641622 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_2", 2002872, 5963945, 5963946, 4, { 20.515039f, 30.001440f, -55.973820f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 20.515039, 32.501442, -55.973820 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "unknown_2", 2002735, 0, 5963947, 4, { 21.438900f, 30.001369f, -55.832821f }, 0.869751f, -1.570451f, 0 ); 

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_3", 2002872, 5963948, 5963949, 4, { 60.977539f, 30.000811f, -56.096581f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 60.977539, 32.500809, -56.096581 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_4", 2002872, 5963970, 5963971, 4, { -95.386551f, -5.551003f, -272.570099f }, 0.991760f, 0.000048f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -95.386429, -3.071602, -272.570221 }, 0.000048, 7.438202, 3.967041, 0.743820 );

    pEObj = instance.addEObj( "unknown_4", 2002735, 0, 5963972, 4, { -95.423126f, -5.551003f, -271.765991f }, 1.000000f, -0.005750f, 0 ); 

    pEObj = instance.addEObj( "Candlekeepkey", 2006467, 0, 5964169, 4, { 13.504210f, 29.984011f, -54.795170f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_9", 2006465, 5963843, 5964187, 4, { 32.070061f, 72.230629f, -55.058460f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 31.353518, 77.230629, -55.058460 }, -0.000000, 1.000000, 6.759988, 4.836537 );

    pEObj = instance.addEObj( "Lockeddoor", 2006470, 5955784, 5964188, 4, { 15.219990f, 31.371090f, -56.250301f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 15.219990, 38.390800, -56.250301 }, -0.000000, 5.200000, 7.721681, 0.300000 );

    pEObj = instance.addEObj( "unknown_5", 2006461, 5961306, 5964259, 4, { -42.092682f, 170.000000f, 1.321840f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_6", 2006462, 5961309, 5964260, 4, { 0.142279f, 160.000000f, 41.544201f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_8", 2006464, 5964060, 5965715, 4, { 0.116699f, 139.949997f, -18.497431f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 0.116699, 143.113358, -17.538004 }, -0.000000, 5.765694, 4.654292, 1.000000 );

    pEObj = instance.addEObj( "unknown_7", 2006463, 5965424, 5966106, 4, { 1.331733f, 158.160294f, 25.044350f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -0.474504, 160.490280, 24.654303 }, -0.466698, 1.000000, 5.044669, 6.458308 );

    pEObj = instance.addEObj( "unknown_10", 2006466, 5965844, 5966110, 4, { -0.253021f, 39.999969f, -21.544781f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -0.153021, 42.269970, -21.544781 }, -0.000000, 0.190000, 2.400000, 3.300000 );

    pEObj = instance.addEObj( "Port3526", 2006471, 5960472, 5966292, 4, { -16.647579f, 7.686357f, -153.002304f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { -16.647659, 6.003586, -153.002228 }, 0.000048, 2.487948, 2.379860, 0.072691 );

    pEObj = instance.addEObj( "Port3524", 2006472, 5960468, 5966293, 4, { -94.266373f, -0.598898f, -227.302200f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { -94.266457, -2.281669, -227.302124 }, 0.000048, 2.487948, 2.379860, 0.072691 );

    pEObj = instance.addEObj( "sgpl_w_lvd_collison_only", 2002618, 5993225, 5993232, 4, { 0.231439f, 90.039482f, -21.072599f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 0.231439, 90.039482, -21.072599 }, -0.000000, 1.000000, 1.000000, 1.000000 );

    pEObj = instance.addEObj( "unknown_11", 2006528, 5967682, 6034671, 4, { 10.338900f, 10.519330f, -124.110298f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 10.338900, 8.822577, -124.110298 }, -0.000000, 2.508618, 2.399632, 0.142528 );

    pEObj = instance.addEObj( "unknown_1", 2006551, 0, 6045189, 4, { 6.820740f, 90.135010f, -0.717224f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_3", 2006563, 0, 6049589, 4, { 42.160641f, 29.984011f, -60.227360f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_12", 2006564, 5967692, 6050827, 4, { -3.081049f, 5.016401f, -212.859802f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -3.081049, 3.319648, -212.859802 }, -0.000000, 2.508618, 2.399632, 0.142528 );


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

EXPOSE_SCRIPT( PharosSiriusHard );