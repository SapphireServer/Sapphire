#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheToweratParadigmsBreach : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheToweratParadigmsBreach() : Sapphire::ScriptAPI::InstanceContentScript( 30105 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2002735, 0, 4, { -799.984680f, -790.000000f, -654.059082f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118", 2002872, 8688392, 4, { -799.984680f, -790.000000f, -654.059082f }, 0.991760f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_1", 2007457, 8644203, 4, { -800.000000f, -800.000000f, -724.406311f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_2", 2007457, 8644353, 4, { -800.000000f, -800.000000f, -724.406311f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_3", 2007457, 8644354, 4, { -800.000000f, -800.000000f, -724.406311f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_4", 2007457, 8688320, 4, { -800.000000f, -800.000000f, -724.406311f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgbg_n4r3_a4_col01", 2007457, 8665489, 4, { -718.000000f, 600.000000f, -718.000000f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "sgbg_n4r3_a4_col01_1", 2007457, 8665490, 4, { -718.000000f, 600.000000f, -682.000000f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "sgbg_n4r3_a4_col01_2", 2007457, 8665491, 4, { -682.000000f, 600.000000f, -682.000000f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "unknown_5", 2007457, 8670615, 4, { -684.809692f, 600.000000f, -689.723022f }, 0.991760f, -0.000000f); 
    instance.registerEObj( "unknown_6", 2002735, 0, 4, { 799.685974f, -693.299622f, 694.201416f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2002872, 8697804, 4, { 799.685974f, -693.299622f, 694.201416f }, 1.000000f, -0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgbg_n4r3_a4_col01_3", 2007457, 8710418, 4, { -682.000000f, 600.000000f, -718.000000f }, 1.000000f, -0.000000f); 
    instance.registerEObj( "unknown_7", 2002735, 0, 4, { -800.167786f, -792.904480f, -880.460815f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2007457, 8786363, 4, { -800.595093f, -792.233398f, -878.760681f }, 0.991760f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_8", 2002735, 0, 4, { 845.000000f, -776.262512f, -785.477600f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2002872, 8712365, 4, { 845.000000f, -776.262512f, -785.477600f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0286", 2007457, 8661276, 4, { -750.631470f, -900.000000f, 785.213379f }, 1.000000f, 0.000000f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { -700.038208f, 600.000000f, -719.996887f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Networkaccesspoint", 2011488, 8664942, 4, { -793.903015f, -887.958374f, 709.001892f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Networkaccesspoint_1", 2011489, 8664944, 4, { -851.528625f, -877.999878f, 789.451294f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Networkegresspoint", 2011490, 8664945, 4, { -800.000000f, -802.562500f, -969.000000f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Networkegresspoint_1", 2011491, 8664946, 4, { 845.000000f, -786.500000f, -870.000000f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Controlpanel", 2011492, 8636396, 4, { 799.954224f, -698.481812f, 799.984619f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "unknown_9", 2007457, 8756600, 4, { -798.553711f, -800.000000f, -724.922913f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Controlpanel_1", 2011696, 8801147, 4, { 800.000000f, -698.481812f, 800.000000f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Accesspoint", 2011471, 8659000, 4, { -743.025574f, -900.000000f, 766.589722f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Accesspoint_1", 2011472, 8659107, 4, { -783.500000f, -799.500000f, -843.437500f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Accesspoint_2", 2011473, 8659109, 4, { -821.114075f, -888.680481f, 704.563477f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Accesspoint_3", 2011474, 8659195, 4, { 854.375000f, -779.187500f, -746.406311f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "Accesspoint_4", 2011475, 8659363, 4, { -859.478271f, -876.062500f, 822.157471f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Accesspoint_5", 2011476, 8661919, 4, { 807.650024f, -693.599976f, 726.750000f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "unknown_10", 2002735, 0, 4, { 755.000000f, -800.000000f, -723.691528f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_4", 2007457, 8654431, 4, { 754.855530f, -800.000000f, -721.523315f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_5", 2007457, 8654443, 4, { 775.865479f, -800.000000f, -749.152527f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgbg_n4r3_a3_col01", 2007457, 8692196, 4, { 800.503418f, -699.599976f, 773.494995f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "unknown_11", 2010506, 0, 4, { -851.500000f, -876.000000f, 837.094604f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0250", 2007457, 8654847, 4, { -851.500000f, -876.000000f, 834.968018f }, 1.000000f, 0.000000f); 
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

EXPOSE_SCRIPT( TheToweratParadigmsBreach );