#include <ScriptObject.h>
#include <Territory/InstanceContent.h>
#include <Actor/EventObject.h>

using namespace Sapphire;

class TheGreatGubalLibrary : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheGreatGubalLibrary() : Sapphire::ScriptAPI::InstanceContentScript( 31 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    Entity::EventObjectPtr pEObj;

    pEObj = instance.addEObj( "Entrance", 2000182, 5330520, 5330524, 5, { -387.057098f, -0.015320f, 4.592957f }, 0.991760f, 0.000048f, 0 ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    pEObj->addCollisionBox( { -387.056854, 1.968058, 1.617581 }, 0.000048, 1.289288, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { -387.047424, 1.968343, 7.568143 }, 0.000048, 1.289288, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { -384.081726, 1.968058, 4.596863 }, -1.570403, 1.289288, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { -390.032288, 1.968344, 4.603605 }, -1.570403, 1.289288, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { -389.139587, 1.968201, 2.510065 }, -0.785350, 1.388464, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { -384.974396, 1.968201, 6.675658 }, -0.785350, 1.388464, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { -384.974213, 1.968001, 2.510265 }, 0.785446, 1.388464, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { -389.139801, 1.968400, 6.675459 }, 0.785446, 1.388464, 3.967041, 0.247940 );

    pEObj = instance.addEObj( "Shortcut", 2000700, 0, 5330539, 4, { -381.085205f, -0.015320f, 6.094601f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "Exit", 2000139, 0, 5330557, 4, { 393.716492f, -39.017399f, -59.556030f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_4", 2004942, 5033535, 5336596, 4, { -316.612915f, -0.015320f, 0.045776f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { -316.612793, 2.464081, 0.045658 }, 0.000048, 1.983521, 2.479401, 0.185955 );

    pEObj = instance.addEObj( "unknown_5", 2004949, 5033537, 5336618, 4, { -173.408096f, 12.000000f, -33.362572f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { -173.407974, 14.479401, -33.362690 }, 0.000048, 1.983521, 2.479401, 0.371910 );

    pEObj = instance.addEObj( "unknown_6", 2004956, 5033536, 5336624, 4, { -48.355900f, -0.015320f, 0.747620f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { -48.355782, 2.464081, 0.747501 }, 0.000048, 1.983521, 2.479401, 0.185955 );

    pEObj = instance.addEObj( "unknown_7", 2004957, 5033538, 5336626, 4, { 43.900150f, -0.015320f, -1.083435f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { 43.900269, 2.464081, -1.083554 }, 0.000048, 1.983521, 2.479401, 0.371910 );

    pEObj = instance.addEObj( "unknown_8", 2004958, 5004619, 5336708, 4, { 82.139282f, -8.011047f, 69.748901f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { 82.139565, -2.060485, 69.748619 }, 0.000048, 4.958802, 5.950562, 1.438053 );

    pEObj = instance.addEObj( "unknown_9", 2004959, 5004620, 5336710, 4, { 117.387604f, -9.018127f, 69.291138f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { 117.387886, -3.067565, 69.290855 }, 0.000048, 4.958802, 5.950562, 1.438053 );

    pEObj = instance.addEObj( "sgbg_d2d3_a0_gmc04", 2004960, 5336977, 5336711, 4, { 138.888000f, -9.018127f, 87.533859f }, 0.991760f, 0.000048f, 0 ); 
    // States -> book_def (id: 3) book_off (id: 4) book_off_anim (id: 5) 

    pEObj = instance.addEObj( "unknown_10", 2004962, 5033543, 5336712, 4, { 156.328598f, -9.018127f, 95.628304f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { 156.328720, -6.538727, 95.628181 }, 0.000048, 1.983521, 2.479401, 0.371910 );

    pEObj = instance.addEObj( "unknown_11", 2004963, 5004621, 5336714, 4, { 176.257004f, -8.011047f, -9.414856f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { 176.257294, -2.060485, -9.415141 }, 0.000048, 4.958802, 5.950562, 1.438053 );

    pEObj = instance.addEObj( "unknown_12", 2004964, 5773506, 5336727, 4, { 297.779785f, -24.002501f, -43.308731f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { 297.780060, -18.288969, -43.309006 }, 0.000048, 5.950562, 6.611736, 0.123970 );

    pEObj = instance.addEObj( "unknown_13", 2004965, 5004586, 5336730, 4, { 325.666107f, -39.017399f, -59.098209f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { 325.666534, -30.091557, -59.098637 }, 0.000048, 7.934083, 8.925843, 2.475434 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_1", 2002872, 5419606, 5419608, 4, { -22.327221f, 0.000000f, -0.318492f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -22.327221, 2.500000, -0.318492 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_2", 2005019, 5419607, 5419609, 4, { 22.309731f, 0.000000f, -0.124082f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 22.309731, 2.500000, -0.124082 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "unknown_1", 2002735, 0, 5419610, 4, { -20.486000f, 0.000000f, 0.109200f }, 1.000000f, -1.570451f, 0 ); 

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_3", 2002872, 5419612, 5419617, 4, { 178.337997f, -8.000000f, 53.739559f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 178.337997, -5.500000, 53.739559 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_4", 2005020, 5419614, 5419618, 4, { 179.630203f, -8.000000f, 0.354116f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 179.630203, -5.500000, 0.354116 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "unknown_3", 2002735, 0, 5419619, 4, { 177.873505f, -8.000000f, 52.121300f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_0", 2002735, 0, 5419621, 4, { 353.541412f, -39.250000f, -59.553089f }, 1.000000f, -1.570451f, 0 ); 

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118", 2002872, 5419624, 5419623, 4, { 350.673187f, -39.000000f, -60.588070f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 350.673187, -36.500000, -60.588070 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "unknown_2", 2005316, 5774736, 5795143, 4, { -11.221270f, 0.000000f, -6.534676f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgpl_d2d3_dbook01", 2005328, 5815254, 5815257, 4, { -10.516900f, 0.000000f, -1.875240f }, 1.000000f, 0.000000f, 0 ); 
    // States -> step_all_off (id: 15) step1_all_on (id: 16) step1_side_off (id: 17) step2_all_on (id: 18) step2_side_off (id: 19) step3_all_on (id: 20) step3_side_off (id: 21) 
    pEObj->addCollisionBox( { -0.516900, 9.000000, -10.912252 }, -0.000000, 4.500000, 10.000000, 2.949977 );
    pEObj->addCollisionBox( { -17.614723, 9.000000, -10.887577 }, -0.000000, 4.500000, 10.000000, 2.974651 );
    pEObj->addCollisionBox( { -0.516900, 9.000000, -4.899914 }, -0.000000, 4.500000, 10.000000, 2.986989 );
    pEObj->addCollisionBox( { -9.091494, 9.000000, -4.887577 }, -0.000000, 4.000000, 10.000000, 2.974652 );
    pEObj->addCollisionBox( { -17.659306, 9.000000, -4.887577 }, -0.000000, 4.500000, 10.000000, 2.974652 );
    pEObj->addCollisionBox( { -0.516900, 9.000000, 1.124760 }, -0.000000, 4.500000, 10.000000, 2.986989 );
    pEObj->addCollisionBox( { -9.065280, 9.000000, 1.112423 }, -0.000000, 4.000000, 16.942579, 2.974652 );
    pEObj->addCollisionBox( { -17.630268, 9.000000, 1.115639 }, -0.000000, 4.500000, 10.000000, 2.975967 );
    pEObj->addCollisionBox( { -9.076046, 9.000000, -10.887577 }, -0.000000, 4.000000, 10.000000, 2.974652 );

    pEObj = instance.addEObj( "sgbg_d2d3_a0_gmc17", 2005354, 5852274, 5852275, 4, { 177.539993f, -7.995000f, 32.977421f }, 1.000000f, 0.000000f, 0 ); 
    // States -> bk03_def (id: 5) bk03_on (id: 6) bk03_on_anim (id: 8) bk03_brt (id: 11) bk03_brt_anim (id: 12) bk03_brt_ofanim (id: 14) bk03_dead (id: 15) bk03_dead_anim (id: 16) 

    pEObj = instance.addEObj( "OnGarleanHierarchyVolume1", 2005891, 0, 5896149, 4, { -199.611694f, 6.900000f, -56.354649f }, 1.000000f, -0.298927f, 0 ); 

    pEObj = instance.addEObj( "OnGarleanHierarchyVolume2", 2005892, 0, 5896150, 4, { -72.116417f, 0.900000f, -9.577726f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "Essences&Permutations", 2005893, 0, 5896152, 4, { 54.309052f, -8.099999f, 62.262531f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "OvertheHorizon", 2005894, 0, 5896153, 4, { 113.656601f, -8.153534f, 83.276863f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "Leatherbounddiary", 2005895, 0, 5896154, 4, { 253.342499f, -24.000000f, -16.578369f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "Leatherbounddiary_1", 2005896, 0, 5896167, 4, { 252.532898f, -40.000000f, -78.517921f }, 1.000000f, 0.000000f, 0 ); 


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

EXPOSE_SCRIPT( TheGreatGubalLibrary );