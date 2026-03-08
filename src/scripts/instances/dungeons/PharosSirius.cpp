#include <ScriptObject.h>
#include <Territory/InstanceContent.h>
#include <Actor/EventObject.h>

using namespace Sapphire;

class PharosSirius : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  PharosSirius() : Sapphire::ScriptAPI::InstanceContentScript( 17 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    Entity::EventObjectPtr pEObj;

    pEObj = instance.addEObj( "Entrance", 2002718, 4378108, 4378109, 5, { 88.730026f, 0.300000f, 69.993042f }, 0.991760f, 0.000048f, 0 ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    pEObj->addCollisionBox( { 88.730263, 2.283378, 67.017670 }, 0.000048, 1.289288, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { 88.739700, 2.283663, 72.968231 }, 0.000048, 1.289288, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { 91.705399, 2.283378, 69.996948 }, -1.570403, 1.289288, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { 85.754837, 2.283664, 70.003693 }, -1.570403, 1.289288, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { 86.647522, 2.283520, 67.910149 }, -0.785350, 1.388464, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { 90.812721, 2.283520, 72.075745 }, -0.785350, 1.388464, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { 90.812920, 2.283321, 67.910347 }, 0.785446, 1.388464, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { 86.647324, 2.283720, 72.075546 }, 0.785446, 1.388464, 3.967041, 0.247940 );

    pEObj = instance.addEObj( "unknown_0", 2002719, 0, 4378112, 4, { 118.749496f, 0.300000f, 70.000000f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "Exit", 2000139, 0, 4378113, 4, { -18.275600f, 193.987900f, 0.000000f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_1", 2002735, 0, 4378114, 4, { 42.000000f, 30.001560f, -31.911860f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgpl_w_lvd_b0118_f1d2", 2002720, 4378115, 4378116, 4, { 41.977539f, 30.001610f, -32.837688f }, 0.991760f, 0.000048f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 41.977650, 32.481022, -32.640942 }, 0.000048, 4.214982, 3.967041, 0.257858 );

    pEObj = instance.addEObj( "unknown_2", 2002723, 4391376, 4378118, 4, { 23.849791f, 29.984011f, -56.015869f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { 23.850124, 36.945881, -56.016201 }, 0.000048, 5.157154, 7.658057, 0.297528 );

    pEObj = instance.addEObj( "unknown_3", 2002735, 0, 4378120, 4, { 21.750000f, 90.008011f, 0.000000f }, 1.000000f, -1.570796f, 0 ); 

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118", 2002721, 4378121, 4378122, 4, { 20.298759f, 90.000008f, 0.000000f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 20.298759, 92.500008, 0.000000 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_1", 2002724, 4378123, 4378124, 4, { -20.870550f, 90.000008f, 0.000000f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -20.870550, 92.500008, 0.000000 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "unknown_4", 2002735, 0, 4378126, 4, { 25.750000f, 194.136505f, 0.000000f }, 1.000000f, -1.570451f, 0 ); 

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_2", 2002722, 4378127, 4378128, 4, { 24.286779f, 194.000000f, 0.000000f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 24.286779, 196.500000, 0.000000 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "Shortcut", 2000700, 0, 4378130, 4, { 76.644943f, 0.300000f, 66.422493f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_5", 2002725, 4392603, 4378143, 4, { -42.923710f, 29.984011f, -56.504211f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_6", 2002726, 4392604, 4378146, 4, { -19.028080f, 36.148560f, -22.110350f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_7", 2002727, 4392605, 4378148, 4, { 17.898800f, 44.388432f, -22.415590f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_8", 2002728, 4392606, 4378150, 4, { 26.840580f, 52.091381f, 10.055660f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_9", 2002729, 4404469, 4378152, 4, { -41.947140f, 29.984011f, 55.924320f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_10", 2002735, 0, 4390582, 4, { 0.000000f, 140.000000f, 21.000000f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_3", 2002744, 4390583, 4390584, 4, { 0.213522f, 139.893402f, 22.075270f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 0.213522, 142.393402, 22.075270 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_4", 2002743, 4390585, 4390586, 4, { -0.033084f, 140.000000f, -20.026180f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -0.033084, 142.500000, -20.026180 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "unknown_11", 2002742, 4390546, 4390592, 4, { -11.093380f, 1.388489f, -23.453131f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { -11.093160, 5.977820, -23.453350 }, 0.000048, 3.413589, 5.048265, 0.311932 );

    pEObj = instance.addEObj( "Aethervalve", 2002730, 4392611, 4391091, 4, { -0.015320f, 119.981598f, -32.913761f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "Aethervalve_1", 2002731, 4392612, 4391096, 4, { -0.076355f, 139.970901f, 42.618408f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_14", 2003032, 0, 4391461, 4, { 42.000000f, 30.000771f, -59.314499f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_15", 2003033, 0, 4391486, 4, { 42.000000f, 30.000771f, -56.244320f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_16", 2003034, 0, 4391487, 4, { 42.000000f, 30.000771f, -51.724258f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_12", 2002787, 4395239, 4393922, 4, { -38.345951f, 60.593510f, 21.011600f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { -38.345730, 65.182838, 21.011381 }, 0.000048, 3.413589, 5.048265, 0.311932 );

    pEObj = instance.addEObj( "unknown_13", 2003436, 4406574, 4579948, 4, { 41.813019f, 29.999941f, -29.969271f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 41.813019, 37.019650, -29.969271 }, -0.000000, 5.200000, 7.721681, 0.300000 );


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

EXPOSE_SCRIPT( PharosSirius );