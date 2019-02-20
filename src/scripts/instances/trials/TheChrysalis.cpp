#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheChrysalis :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheChrysalis() :
    Sapphire::ScriptAPI::InstanceContentScript( 20029 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "sgvf_z1e9_b0606", 2005209, 5689928, 4, { -0.866003f, 0.000000f, -29.632271f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Entrance", 2000182, 5649517, 5, { -0.064617f, 0.000000f, 21.704861f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 0.000000f, 0.000000f, -22.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgbg_z1e9_t1_yuka1", 2005160, 5652375, 4, { -1.683807f, -0.002888f, -0.074251f }, 1.000000f, 0.000000f ); 
    // States -> d_def (id: 1) d_def_anim (id: 2) d_01 (id: 3) d_01_anim (id: 4) d_02 (id: 5) d_02_anim (id: 6) d_03 (id: 7) d_03_anim (id: 8) d_04 (id: 9) d_04_anim (id: 10) 
    instance.registerEObj( "unknown_0", 2005158, 0, 4, { 220.000000f, -0.045776f, 0.000000f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_1", 2005159, 0, 4, { 229.899994f, -0.013268f, 9.900000f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_2", 2004550, 0, 4, { 0.068370f, -0.002887f, -0.230858f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_z1e1_b0598", 2005161, 5652362, 4, { 219.837494f, -0.000000f, -20.737341f }, 1.000000f, 0.000000f ); 
    // States -> crack_def (id: 5) crack_01 (id: 6) crack_01_anim (id: 7) crack_02 (id: 8) crack_02_anim (id: 9) crack_03 (id: 10) crack_03_anim (id: 11) crack_04 (id: 12) crack_04_anim (id: 13) 
    instance.registerEObj( "sgvf_z1e1_b0598_1", 2005198, 5675943, 4, { 234.366592f, -0.000818f, -14.481080f }, 1.000000f, 0.000000f ); 
    // States -> crack_def (id: 5) crack_01 (id: 6) crack_01_anim (id: 7) crack_02 (id: 8) crack_02_anim (id: 9) crack_03 (id: 10) crack_03_anim (id: 11) crack_04 (id: 12) crack_04_anim (id: 13) 
    instance.registerEObj( "sgvf_z1e1_b0598_2", 2005199, 5675944, 4, { 238.872803f, -0.002887f, -0.791933f }, 1.000000f, 0.000000f ); 
    // States -> crack_def (id: 5) crack_01 (id: 6) crack_01_anim (id: 7) crack_02 (id: 8) crack_02_anim (id: 9) crack_03 (id: 10) crack_03_anim (id: 11) crack_04 (id: 12) crack_04_anim (id: 13) 
    instance.registerEObj( "sgvf_z1e1_b0598_3", 2005200, 5675945, 4, { 233.135101f, -0.002692f, 13.732260f }, 1.000000f, 0.000000f ); 
    // States -> crack_def (id: 5) crack_01 (id: 6) crack_01_anim (id: 7) crack_02 (id: 8) crack_02_anim (id: 9) crack_03 (id: 10) crack_03_anim (id: 11) crack_04 (id: 12) crack_04_anim (id: 13) 
    instance.registerEObj( "sgvf_z1e1_b0598_4", 2005201, 5675946, 4, { 220.264893f, -0.002887f, 18.895180f }, 1.000000f, 0.000000f ); 
    // States -> crack_def (id: 5) crack_01 (id: 6) crack_01_anim (id: 7) crack_02 (id: 8) crack_02_anim (id: 9) crack_03 (id: 10) crack_03_anim (id: 11) crack_04 (id: 12) crack_04_anim (id: 13) 
    instance.registerEObj( "sgvf_z1e1_b0598_5", 2005202, 5675947, 4, { 206.385605f, -0.002087f, 13.131840f }, 1.000000f, 0.000000f ); 
    // States -> crack_def (id: 5) crack_01 (id: 6) crack_01_anim (id: 7) crack_02 (id: 8) crack_02_anim (id: 9) crack_03 (id: 10) crack_03_anim (id: 11) crack_04 (id: 12) crack_04_anim (id: 13) 
    instance.registerEObj( "sgvf_z1e1_b0598_6", 2005203, 5675948, 4, { 201.101196f, -0.002887f, -0.591635f }, 1.000000f, 0.000000f ); 
    // States -> crack_def (id: 5) crack_01 (id: 6) crack_01_anim (id: 7) crack_02 (id: 8) crack_02_anim (id: 9) crack_03 (id: 10) crack_03_anim (id: 11) crack_04 (id: 12) crack_04_anim (id: 13) 
    instance.registerEObj( "sgvf_z1e1_b0598_7", 2005204, 5675951, 4, { 206.584305f, -0.002887f, -14.412730f }, 1.000000f, 0.000000f ); 
    // States -> crack_def (id: 5) crack_01 (id: 6) crack_01_anim (id: 7) crack_02 (id: 8) crack_02_anim (id: 9) crack_03 (id: 10) crack_03_anim (id: 11) crack_04 (id: 12) crack_04_anim (id: 13) 
    instance.registerEObj( "sgvf_z1e1_b0598_8", 2005205, 5675952, 4, { 227.781204f, -0.002888f, -8.587747f }, 1.000000f, 0.000000f ); 
    // States -> crack_def (id: 5) crack_01 (id: 6) crack_01_anim (id: 7) crack_02 (id: 8) crack_02_anim (id: 9) crack_03 (id: 10) crack_03_anim (id: 11) crack_04 (id: 12) crack_04_anim (id: 13) 
    instance.registerEObj( "sgvf_z1e1_b0598_9", 2005206, 5675953, 4, { 227.676605f, -0.002889f, 8.141966f }, 1.000000f, 0.000000f ); 
    // States -> crack_def (id: 5) crack_01 (id: 6) crack_01_anim (id: 7) crack_02 (id: 8) crack_02_anim (id: 9) crack_03 (id: 10) crack_03_anim (id: 11) crack_04 (id: 12) crack_04_anim (id: 13) 
    instance.registerEObj( "sgvf_z1e1_b0598_10", 2005207, 5675954, 4, { 211.709396f, -0.002890f, 7.657639f }, 1.000000f, 0.000000f ); 
    // States -> crack_def (id: 5) crack_01 (id: 6) crack_01_anim (id: 7) crack_02 (id: 8) crack_02_anim (id: 9) crack_03 (id: 10) crack_03_anim (id: 11) crack_04 (id: 12) crack_04_anim (id: 13) 
    instance.registerEObj( "sgvf_z1e1_b0598_11", 2005208, 5675955, 4, { 211.825500f, -0.001177f, -9.651319f }, 1.000000f, 0.000000f ); 
    // States -> crack_def (id: 5) crack_01 (id: 6) crack_01_anim (id: 7) crack_02 (id: 8) crack_02_anim (id: 9) crack_03 (id: 10) crack_03_anim (id: 11) crack_04 (id: 12) crack_04_anim (id: 13) 

  }

  void onUpdate( InstanceContent& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheChrysalis );