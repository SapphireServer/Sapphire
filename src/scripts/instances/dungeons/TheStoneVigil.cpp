#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheStoneVigil : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheStoneVigil() : Sapphire::ScriptAPI::InstanceContentScript( 11 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.addEObj( "unknown_0", 2000611, 0, 4284710, 4, { 0.015198f, 0.350891f, -246.784195f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Entrance", 2001869, 4239670, 4239683, 5, { -0.000510f, 3.949623f, 307.392395f }, 2.000000f, 0.000000f, 0); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.addEObj( "unknown_1", 2001870, 0, 4239705, 4, { 0.015198f, 3.949618f, 317.179199f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Exit", 2001871, 4239710, 4239714, 4, { 0.004404f, 0.076945f, -268.716095f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_htras1_on (id: 2) vf_htras1_of (id: 3) 
    instance.addEObj( "sgvf_w_lvd_b0094", 2001872, 4239719, 4239717, 4, { -0.106873f, 3.860474f, 136.491898f }, 0.991760f, 0.000048f, 0); 
    // States -> vf_line_on (id: 12) vf_line_of (id: 13) 
    instance.addEObj( "sgvf_w_lvd_b0118_r1d1", 2001873, 4239720, 4239721, 4, { -0.625671f, 3.829956f, 136.461395f }, 0.991760f, 0.000048f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "sgvf_w_lvd_b0094_1", 2001874, 4239769, 4239778, 4, { 20.620710f, 3.949919f, -80.003052f }, 0.991760f, 0.000048f, 0); 
    // States -> vf_line_on (id: 12) vf_line_of (id: 13) 
    instance.addEObj( "sgvf_w_lvd_b0118", 2001875, 4239782, 4239792, 4, { 20.559681f, 3.949919f, -80.277771f }, 0.991760f, 0.000048f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "sgvf_w_lvd_b0094_2", 2001876, 4239833, 4239836, 4, { -0.197872f, 4.844441f, -223.182404f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_line_on (id: 12) vf_line_of (id: 13) 
    instance.addEObj( "sgvf_w_lvd_b0118_r1d1_1", 2001877, 4239838, 4239846, 4, { 0.816688f, 4.854907f, -223.199707f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "Shortcut", 2000700, 0, 4240026, 4, { 3.484173f, 4.000121f, 298.130005f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "sgbg_r1d1_t1_fwal1", 2001878, 4239736, 4240037, 4, { 0.228821f, 3.982544f, 95.231567f }, 0.991760f, 0.000048f, 0); 
    // States -> fire_on (id: 4) fire_of (id: 5) 
    instance.addEObj( "sgbg_r1d1_t1_fwal1_1", 2001879, 4239917, 4240042, 4, { -0.137390f, -0.076355f, -90.104553f }, 0.991760f, 0.000048f, 0); 
    // States -> fire_on (id: 4) fire_of (id: 5) 
    instance.addEObj( "Strongroomgate", 2001880, 4172415, 4240048, 4, { -0.022534f, 4.052033f, -215.388901f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "sgvf_r1d1_b0172", 2001881, 4240140, 4240146, 4, { 24.443140f, -0.000003f, -16.325529f }, 1.000000f, 0.000000f, 0); 
    // States -> snow_of (id: 2) snow_on (id: 3) 
    instance.addEObj( "sgvf_r1d1_b0172_1", 2001882, 4240143, 4240147, 4, { 24.207170f, -0.386616f, -119.586502f }, 1.000000f, 0.000000f, 0); 
    // States -> snow_of (id: 2) snow_on (id: 3) 
    instance.addEObj( "sgvf_r1d1_b0172_2", 2001883, 4240145, 4240148, 4, { 24.277100f, -0.015320f, -168.047699f }, 0.991760f, 0.000048f, 0); 
    // States -> snow_of (id: 2) snow_on (id: 3) 
    instance.addEObj( "Bertha", 2001884, 0, 4240186, 4, { 56.748291f, 4.989685f, -86.472900f }, 0.991760f, 1.040362f, 0); 
    instance.addEObj( "Bertha_1", 2001885, 0, 4240187, 4, { 58.899940f, 4.989685f, -79.857857f }, 0.991760f, 1.535637f, 0); 
    instance.addEObj( "Bertha_2", 2001886, 0, 4240188, 4, { 56.935600f, 5.003687f, -73.150261f }, 0.991760f, 1.076136f, 0); 
    instance.addEObj( "sgpl_w_lvd_collison_only", 2002618, 4334349, 4334436, 4, { -0.221096f, 4.007471f, 137.674500f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "sgpl_w_lvd_collison_only_1", 2002618, 4334437, 4334438, 4, { 0.000000f, 5.259686f, -221.867004f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "sgpl_w_lvd_collison_only_2", 2002618, 4334925, 4334931, 4, { -0.016311f, 0.434590f, -224.636993f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "sgpl_w_lvd_collison_only_3", 2002618, 4334973, 4334974, 4, { 0.117383f, 0.135054f, -224.822800f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_2", 2002481, 0, 4321730, 4, { -7.818000f, 9.492000f, -285.652008f }, 1.000000f, -0.783094f, 0); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheStoneVigil );