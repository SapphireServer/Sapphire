#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class MatoyasRelict : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  MatoyasRelict() : Sapphire::ScriptAPI::InstanceContentScript( 76 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "sgvf_w_lvd_b0118", 2007457, 8531148, 4, { -180.046997f, -219.949997f, -80.915619f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_0", 2002735, 0, 4, { -180.071701f, -220.000000f, -82.547523f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2007457, 8531388, 4, { -0.015320f, 169.899994f, -109.546997f }, 0.991760f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_1", 2002735, 0, 4, { -0.076355f, 170.500000f, -112.574898f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "unknown_2", 2011335, 0, 4, { 4.959106f, 149.980804f, -164.934799f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "sgbg_d4d1_a2_gmc28", 2007457, 8638316, 4, { 0.000000f, 150.000000f, -168.738495f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2007457, 8532176, 4, { 0.000000f, 0.000000f, 20.750000f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_3", 2002735, 0, 4, { 0.000000f, 0.000000f, 20.750000f }, 0.991760f, -0.000000f); 
    instance.registerEObj( "sgvf_d4d1_b2101", 2007457, 8534733, 4, { -211.779999f, -212.000000f, 35.279289f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_d4d1_b2101_1", 2007457, 8534813, 4, { -180.071701f, -220.019806f, -74.174133f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "unknown_4", 2007457, 8453701, 4, { -179.877899f, -220.000000f, -46.549061f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_5", 2007457, 8443920, 4, { 51.499149f, 234.000000f, -163.042694f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "unknown_6", 2007457, 8443949, 4, { -52.353760f, 201.983597f, -134.172607f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "sgvf_d4d1_b2107b", 2007457, 8534965, 4, { -22.639490f, 198.000000f, -178.860199f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_d4d1_b2107", 2007457, 8534970, 4, { -0.015320f, 169.878693f, -103.593498f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "sgvf_d4d1_b1888", 2007457, 8541347, 4, { -5.169848f, 198.000000f, -164.590897f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_d4d1_b1888_1", 2007457, 8541348, 4, { -20.572170f, 198.000000f, -172.253296f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_d4d1_b1888_2", 2007457, 8541349, 4, { -12.311310f, 198.000000f, -161.658905f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_d4d1_b1888_3", 2007457, 8541350, 4, { -10.833710f, 198.000000f, -179.329605f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_7", 2007457, 8542195, 4, { 180.071701f, -599.486023f, 65.681892f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_8", 2007457, 8542196, 4, { 165.941803f, -599.328613f, -56.717831f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "unknown_9", 2007457, 8542197, 4, { 161.059006f, -598.885986f, -105.119400f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "unknown_10", 2007457, 8441623, 4, { 158.068207f, -592.546021f, -155.999603f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "sgvf_d4d1_b1889", 2007457, 8541358, 4, { 156.908401f, -598.596191f, 99.290413f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "sgvf_d4d1_b1889_1", 2007457, 8541359, 4, { 124.925903f, -598.740723f, 45.852982f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "sgvf_d4d1_b1889_2", 2007457, 8541360, 4, { 164.147995f, -598.956116f, -104.573196f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Intersticeportal", 2011293, 8535678, 4, { -180.000000f, -220.000000f, -150.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_11", 2007457, 0, 4, { -180.010696f, -220.019806f, -146.715607f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Intersticeportal_1", 2011293, 8613013, 4, { -139.740997f, -199.973007f, 134.974594f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_12", 2007457, 0, 4, { -139.740997f, -199.973007f, 134.974594f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "unknown_13", 2007457, 0, 4, { -0.015300f, 150.000000f, -157.033203f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Intersticeportal_2", 2011354, 8535729, 4, { -0.015320f, 149.980804f, -160.021393f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "unknown_14", 2007457, 0, 4, { -43.881989f, 236.000000f, -218.223297f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Intersticeportal_3", 2011354, 8613016, 4, { -43.900269f, 235.980698f, -220.461899f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "unknown_15", 2007457, 0, 4, { 161.862503f, -592.476624f, -146.518600f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "unknown_16", 2009584, 0, 4, { 155.413101f, -598.535217f, 101.182503f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Intersticeportal_4", 2011355, 8535732, 4, { 161.852402f, -592.553589f, -149.889404f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "unknown_17", 2007457, 0, 4, { 160.723907f, -598.301819f, 182.742096f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Intersticeportal_5", 2011355, 8613019, 4, { 160.723907f, -598.301819f, 183.995102f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Entrance", 2007457, 8532637, 5, { 4.989663f, 11.443340f, 131.087097f }, 0.991760f, 0.000048f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { 0.318621f, 11.616820f, 175.153305f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Exit", 2000139, 0, 4, { -0.015320f, -0.015320f, -16.006710f }, 0.991760f, -0.000000f); 
    instance.registerEObj( "Earthyportal", 2011290, 8535639, 4, { 3.790484f, 8.499207f, 62.867828f }, 0.991760f, -0.862215f); 
    instance.registerEObj( "Wateryportal", 2011291, 8535640, 4, { 8.132032f, 8.499605f, 63.954411f }, 0.991760f, -0.709925f); 
    instance.registerEObj( "Fieryportal", 2011292, 8535641, 4, { 12.550680f, 8.499607f, 65.062759f }, 1.000000f, -0.640703f); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( MatoyasRelict );