#include <ScriptObject.h>
#include <Territory/InstanceContent.h>
#include <Actor/EventObject.h>

using namespace Sapphire;

class TheWanderersPalaceHard : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheWanderersPalaceHard() : Sapphire::ScriptAPI::InstanceContentScript( 30 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    Entity::EventObjectPtr pEObj;

    pEObj = instance.addEObj( "Shortcut", 2000700, 0, 4898007, 4, { 137.285400f, -17.990419f, 454.398407f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "Exit", 2000139, 0, 4898008, 4, { 73.105957f, 9.994568f, -475.590790f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "Entrance", 2000182, 4898005, 4898009, 5, { 130.745697f, -17.983120f, 461.438293f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    pEObj->addCollisionBox( { 130.745697, -15.983120, 458.438293 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 130.755493, -15.983120, 464.438293 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 133.745697, -15.983120, 461.442169 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 127.745697, -15.983120, 461.449280 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 128.645691, -15.983120, 459.338287 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 132.845703, -15.983120, 463.538300 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 132.845703, -15.983120, 459.338287 }, 0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 128.645691, -15.983120, 463.538300 }, 0.785398, 1.400000, 4.000000, 0.250000 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118", 2001811, 4898028, 4898013, 4, { 127.094200f, -12.000000f, 125.826500f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 127.094200, -9.500000, 125.826500 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0094", 2001810, 4898029, 4898014, 4, { 124.986603f, -12.039370f, 125.401100f }, 0.991760f, 0.000048f, 0 ); 
    // States -> vf_line_on (id: 12) vf_line_of (id: 13) 

    pEObj = instance.addEObj( "sgvf_w_lvd_b0250", 2000277, 4898030, 4898031, 4, { 125.461502f, -12.000000f, 89.079697f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 125.461502, -9.500000, 89.079697 }, -0.000000, 15.000000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_1", 2001813, 4898057, 4898038, 4, { 45.925018f, 0.000000f, -212.411499f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 45.925018, 2.500000, -212.411499 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0094_1", 2001812, 4898056, 4898039, 4, { 43.121960f, -0.015320f, -212.616592f }, 0.991760f, 0.000048f, 0 ); 
    // States -> vf_line_on (id: 12) vf_line_of (id: 13) 

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_2", 2000278, 4898058, 4898059, 4, { 43.472900f, -0.106873f, -248.065994f }, 0.991760f, 0.000048f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 43.473019, 2.372528, -248.066116 }, 0.000048, 7.438202, 3.967041, 0.743820 );

    pEObj = instance.addEObj( "sgpl_s1d3_bossline", 2001814, 4898089, 4898087, 4, { 72.890900f, 9.976854f, -400.332489f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgpl_s1d3_bosswall", 2001815, 4898090, 4898088, 4, { 74.753906f, 9.964111f, -400.351013f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { 92.727348, 13.282761, -386.066376 }, -0.495137, 8.925843, 3.967041, 0.743820 );
    pEObj->addCollisionBox( { 57.613647, 13.284472, -385.475586 }, 0.488740, 8.925843, 3.967041, 0.743820 );

    pEObj = instance.addEObj( "unknown_1", 2004551, 5018234, 4949901, 4, { 184.679901f, -14.023070f, 304.066406f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { 184.635544, -11.282625, 304.078247 }, 0.000048, 2.354481, 3.037116, 0.309403 );

    pEObj = instance.addEObj( "unknown_2", 2004552, 5018233, 4949903, 4, { 125.230698f, -14.053590f, 244.800400f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { 125.186340, -11.313145, 244.812241 }, 0.000048, 2.354481, 3.037116, 0.309403 );

    pEObj = instance.addEObj( "unknown_3", 2004553, 5018223, 4949905, 4, { 124.956100f, -14.023070f, 183.581207f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { 124.911743, -11.282625, 183.593048 }, 0.000048, 2.354481, 3.037116, 0.309403 );

    pEObj = instance.addEObj( "unknown_4", 2004554, 5018182, 4949907, 4, { 42.770088f, -0.167908f, -26.822309f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { 42.725731, 2.572537, -26.810469 }, 0.000048, 2.354481, 3.037116, 0.309403 );

    pEObj = instance.addEObj( "unknown_5", 2004555, 5018205, 4949908, 4, { 42.862549f, 0.442505f, -150.225098f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { 42.818192, 3.182950, -150.213257 }, 0.000048, 2.354481, 3.037116, 0.309403 );

    pEObj = instance.addEObj( "Asylumcell", 2004556, 5019054, 4949912, 4, { 71.785713f, -11.783800f, -311.787598f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { 71.786034, -5.263457, -311.787903 }, 0.000048, 5.264233, 7.190996, 0.306765 );

    pEObj = instance.addEObj( "Asylumcell_1", 2004557, 5019055, 4949913, 4, { 71.870552f, -11.659170f, -324.391602f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { 71.870872, -5.138827, -324.391907 }, 0.000048, 5.264233, 7.190996, 0.306765 );

    pEObj = instance.addEObj( "unknown_6", 2004558, 5019051, 4949914, 4, { 94.316040f, -12.008810f, -312.062286f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { 94.316330, -6.058253, -312.161743 }, 0.000048, 2.975281, 5.950562, 0.396704 );

    pEObj = instance.addEObj( "unknown_7", 2004559, 5019004, 4949915, 4, { 161.119995f, -8.011047f, -353.322693f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { 161.120178, -4.232033, -353.322876 }, 0.000048, 1.815021, 4.156917, 0.226209 );

    pEObj = instance.addEObj( "unknown_8", 2004560, 5018224, 4949917, 4, { 73.226128f, 10.390440f, -379.721588f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { 73.181770, 13.130884, -379.709747 }, 0.000048, 2.354481, 3.037116, 0.309403 );

    pEObj = instance.addEObj( "unknown_9", 2004561, 5034792, 4985790, 4, { 120.347900f, -12.000000f, -338.826599f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "Drainagevalve", 2004562, 5022359, 4985791, 4, { 124.002098f, -10.704290f, -341.825287f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_10", 2004564, 5018828, 4985792, 4, { 141.315598f, -11.750000f, -326.359711f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 166.315598, -1.577590, -298.859711 }, -0.000000, 1.000000, 6.172410, 7.500000 );

    pEObj = instance.addEObj( "Nymiandevice", 2004565, 4896865, 4985793, 4, { 156.023407f, -6.851379f, -351.735809f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_0", 2005119, 0, 5582003, 4, { 68.684860f, 6.000000f, -449.635315f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_3", 2005196, 5674432, 5674433, 4, { 72.966209f, 6.000000f, -464.577209f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 72.966209, 8.500000, -464.577209 }, -0.000000, 7.500000, 4.000000, 0.750000 );


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

EXPOSE_SCRIPT( TheWanderersPalaceHard );