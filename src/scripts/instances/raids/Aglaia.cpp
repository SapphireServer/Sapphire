#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class Aglaia : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  Aglaia() : Sapphire::ScriptAPI::InstanceContentScript( 30115 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2002735, 0, 4, { 0.000000f, 30.000000f, 765.593384f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118", 2002872, 9085155, 4, { 0.000000f, 30.049999f, 765.500000f }, 1.000000f, -0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_1", 2002735, 0, 4, { 160.856995f, 30.000000f, 386.000000f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2002872, 9088012, 4, { 160.856995f, 30.000000f, 386.275513f }, 0.991760f, 0.000048f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2002872, 9085158, 4, { -750.000000f, -932.000000f, -720.084717f }, 1.000000f, -0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_2", 2002735, 0, 4, { -750.000000f, -932.000000f, -719.987610f }, 0.991760f, -0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2002872, 9085159, 4, { -750.000000f, -932.000000f, -779.768799f }, 1.000000f, -0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_4", 2002872, 9088515, 4, { -677.250000f, -950.000000f, -581.250000f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_3", 2002735, 0, 4, { -677.250000f, -950.000000f, -581.250000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_5", 2002872, 9088518, 4, { -677.250000f, -950.000000f, -631.250000f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_6", 2002872, 9272091, 4, { -750.000000f, -938.000000f, -902.000000f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_4", 2002735, 0, 4, { -750.299988f, -938.000000f, -902.000000f }, 1.250000f, -0.000000f); 
    instance.registerEObj( "Flamewreathedportal", 2012826, 0, 4, { -15.313060f, 475.059296f, 255.118805f }, 1.000000f, 0.209440f); 
    instance.registerEObj( "Pedestalofpassage", 2012820, 0, 4, { 102.971001f, 21.299999f, 874.971008f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Pedestalofpassage_1", 2012821, 0, 4, { 70.664551f, 21.299999f, 549.034790f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "Pedestalofpassage_2", 2012822, 0, 4, { 167.873093f, 29.299999f, 397.126709f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Pedestalofpassage_3", 2012823, 0, 4, { -680.506592f, -950.700012f, -573.266174f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "Pedestalofpassage_4", 2012824, 0, 4, { -746.761292f, -934.700012f, -704.005493f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "Pedestalofpassage_5", 2012825, 0, 4, { -757.015320f, -942.700012f, -868.009521f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0286", 2007457, 9085557, 4, { 108.948196f, 22.000031f, 881.947815f }, 1.000000f, -1.570451f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { 750.000000f, -932.000000f, -775.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_7", 2007457, 9085609, 4, { 74.000000f, 22.000000f, 541.400024f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_5", 2002735, 0, 4, { 74.000000f, 22.000000f, 541.400024f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_8", 2007457, 9090401, 4, { 91.918091f, 22.000000f, 498.081909f }, 1.000000f, 0.785398f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( Aglaia );