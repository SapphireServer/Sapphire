#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class LapisManalis : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  LapisManalis() : Sapphire::ScriptAPI::InstanceContentScript( 89 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "Entrance", 2000182, 9450503, 5, { 47.047859f, 366.000000f, -566.249878f }, 1.000000f, 0.000000f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { 51.895870f, 365.987701f, -577.721802f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Exit", 2000139, 0, 4, { -249.780396f, -173.000000f, 112.119499f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_0", 2013216, 0, 4, { -250.000000f, -173.000000f, 130.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_1", 2002735, 0, 4, { -250.000000f, -173.195694f, 160.535797f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118", 2002872, 9453637, 4, { -250.000000f, -173.195694f, 160.535797f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2002872, 9448695, 4, { 24.000000f, 386.045807f, -723.250000f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_2", 2002735, 0, 4, { 24.000000f, 386.045807f, -723.250000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2002872, 9448703, 4, { 24.000000f, 386.049011f, -764.750000f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2002872, 9462074, 4, { 350.000000f, 34.000000f, -374.000000f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_3", 2002735, 0, 4, { 350.000000f, 34.000000f, -374.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_4", 2002872, 9462082, 4, { 350.000000f, 34.000000f, -414.000000f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "Datedrecords", 2013220, 0, 4, { 404.355713f, 39.688850f, -295.222687f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Fadedrecords", 2013221, 0, 4, { 354.949707f, 36.467621f, -301.062714f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Traineewarningnotice", 2013222, 0, 4, { 352.465515f, 36.478001f, -301.327209f }, 0.991760f, -0.672439f); 
    instance.registerEObj( "Dollmastersmemorandum", 2013295, 0, 4, { 358.298615f, 35.246269f, -347.480713f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Sturdybarrel", 2013232, 0, 4, { 393.717285f, 40.378590f, -273.079712f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Bottomlessbarrel", 2013236, 0, 4, { 338.591187f, 35.001839f, -324.810913f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Dilapidatedbarrel", 2013237, 0, 4, { 356.185303f, 36.431850f, -300.714691f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Holepokedbarrel", 2013238, 0, 4, { 404.956604f, 38.532612f, -293.537811f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Destination", 2013233, 0, 4, { -261.138794f, -165.352798f, 229.112396f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Destination_1", 2013234, 0, 4, { 40.585072f, 366.000000f, -585.400391f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Destination_2", 2013235, 0, 4, { -2.422865f, 374.709595f, -600.981995f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Passagetothevicusmessorum", 2013228, 0, 4, { -20.363230f, 399.510498f, -818.718323f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "ExittoGarlemald", 2013227, 0, 4, { 47.711208f, 367.176910f, -586.741516f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "PassagetoMonsAlbus", 2013229, 0, 4, { 316.917786f, 72.004417f, -111.664902f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "PassagetoFonsManalis", 2013230, 0, 4, { 350.088409f, 34.881290f, -433.933990f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Passagetothevicusmessorum_1", 2013231, 0, 4, { -408.825409f, -117.806297f, 371.981689f }, 1.000000f, 0.000000f); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( LapisManalis );