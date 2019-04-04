#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheDrownedCityofSkalla :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheDrownedCityofSkalla() :
    Sapphire::ScriptAPI::InstanceContentScript( 58 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "sgvf_w_lvd_b0118", 2002872, 7068116, 4, { 459.000000f, -14.000000f, 4.000000f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_0", 2002735, 0, 4, { 459.000000f, -14.000000f, 4.000000f }, 1.000000f, -1.570796f ); 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 491.000000f, -14.000000f, 4.000000f }, 1.000000f, 1.570796f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2002872, 7068596, 4, { -245.000000f, -2.000000f, 4.000000f }, 1.000000f, -0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2002872, 7068599, 4, { -194.500000f, -2.000000f, 4.000000f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_1", 2007457, 7072874, 4, { -220.044601f, -2.000000f, 3.151932f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_2", 2009045, 0, 4, { -224.806396f, -2.000000f, 8.647594f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_3", 2002735, 0, 4, { -245.000000f, -2.000000f, 4.000000f }, 1.400000f, 1.570796f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2002872, 7068491, 4, { 95.000000f, 9.000000f, 4.000000f }, 1.000000f, -0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_4", 2002735, 0, 4, { 95.000000f, 9.000000f, 4.000000f }, 1.400000f, -1.570451f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_4", 2002872, 7068496, 4, { 135.000000f, 9.000000f, 4.000000f }, 1.000000f, -0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_5", 2009046, 0, 4, { 111.907600f, 9.000000f, 4.017264f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgbg_g3d4_a0_gmc04", 2007457, 7075163, 4, { -335.663391f, 1.815782f, -38.379379f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgbg_g3d4_a0_gmc04_1", 2007457, 7075164, 4, { -324.520203f, 1.008244f, -28.697809f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_6", 2007457, 7032771, 4, { -380.099701f, 5.500000f, -16.441790f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgbg_g3d4_a0_gmc04_2", 2007457, 7075174, 4, { -298.365204f, 1.706293f, -25.538429f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgbg_g3d4_a0_gmc04_3", 2007457, 7075175, 4, { -290.733002f, 1.250000f, -27.983721f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_7", 2007457, 7065309, 4, { -273.437195f, 1.281705f, 3.216716f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgbg_g3d4_a0_gmc04_4", 2007457, 7132450, 4, { -322.497589f, 1.008244f, -34.442020f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgbg_g3d4_a0_gmc04_5", 2007457, 7132455, 4, { -293.498108f, 1.972912f, -19.170090f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgbg_g3d4_a0_gmc04_6", 2007457, 7132456, 4, { -287.911407f, 1.972912f, -26.723471f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_8", 2007457, 7034067, 4, { -67.254761f, 3.500000f, -34.435638f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_9", 2007457, 7065310, 4, { 68.873291f, 7.500000f, 3.740700f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_10", 2007457, 0, 4, { 133.644806f, 9.000000f, 3.453697f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_11", 2007457, 7029084, 4, { 272.652802f, -12.000000f, 48.014309f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_12", 2007457, 7032009, 4, { 276.325592f, -12.008910f, -34.378601f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_13", 2007457, 7034222, 4, { 433.853088f, -15.937500f, 3.644273f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Entrance", 2000182, 7042417, 5, { -488.282501f, -3.750000f, 2.201033f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { -457.918304f, -3.860892f, 14.784940f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheDrownedCityofSkalla );