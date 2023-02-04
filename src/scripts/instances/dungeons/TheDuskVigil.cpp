#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheDuskVigil : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheDuskVigil() : Sapphire::ScriptAPI::InstanceContentScript( 36 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.addEObj( "sgvf_w_lvd_b0118", 2002872, 5658893, 5658895, 4, { -0.378468f, -0.000006f, 19.173130f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "unknown_0", 2002735, 0, 5658896, 4, { -0.473083f, -0.015320f, 21.194759f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "sgvf_w_lvd_b0118_1", 2005189, 5658883, 5658897, 4, { 0.051215f, 0.000000f, -19.347589f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "unknown_1", 2002735, 0, 5670054, 4, { 191.935699f, -8.000000f, -97.548279f }, 1.143130f, 0.000000f, 0); 
    instance.addEObj( "sgvf_w_lvd_b0118_2", 2002872, 5670058, 5670061, 4, { 191.873398f, -8.000000f, -94.706589f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "sgvf_w_lvd_b0118_3", 2005190, 5670071, 5670053, 4, { 192.629501f, -8.000000f, -145.825104f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "unknown_2", 2005319, 0, 5797171, 4, { 191.294998f, -8.000000f, -126.640503f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_3", 2002735, 0, 5670083, 4, { -69.815361f, 32.171459f, -368.314209f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "sgvf_w_lvd_b0118_4", 2002872, 5670105, 5670104, 4, { -69.864067f, 32.000050f, -370.484314f }, 1.000000f, 0.000000f, 0); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.addEObj( "unknown_4", 2005395, 0, 5837149, 4, { -72.186203f, 32.000000f, -389.922302f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Shortcut", 2000700, 0, 5653683, 4, { -119.582703f, -47.846481f, 223.251007f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Exit", 2000139, 0, 5653684, 4, { -69.846916f, 32.000000f, -403.795990f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Entrance", 2000182, 5653670, 5653685, 5, { -135.662598f, -48.859058f, 229.988297f }, 0.991760f, 0.000048f, 0); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.addEObj( "unknown_5", 2005169, 5674328, 5653784, 4, { -66.894547f, -5.577260f, 129.660202f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_6", 2005170, 5674333, 5653787, 4, { -28.173691f, -5.988469f, 165.738907f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_7", 2005171, 5674334, 5653806, 4, { 32.157242f, -8.242720f, 98.301018f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Coldsteellever", 2005172, 0, 5653807, 4, { 9.864166f, -0.650611f, 48.260380f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Damagedwinch", 2005173, 5660757, 5653808, 4, { -3.958177f, 1.907400f, 32.349579f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_8", 2005174, 5584415, 5653809, 4, { -0.076084f, -0.115606f, 34.058880f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_9", 2006185, 5912762, 5913191, 4, { -131.761703f, -48.569462f, 225.451996f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Tornjournalpage", 2005180, 0, 5653571, 4, { 66.788696f, -3.996225f, -52.994629f }, 0.991760f, 1.343069f, 0); 
    instance.addEObj( "Tornjournalpage_1", 2005181, 0, 5653572, 4, { 96.351990f, -8.050000f, -30.383080f }, 1.000000f, 1.112220f, 0); 
    instance.addEObj( "Tornjournalpage_2", 2005182, 0, 5653573, 4, { 151.468704f, -7.345456f, -48.435421f }, 1.000000f, -0.025044f, 0); 
    instance.addEObj( "Tornjournalpage_3", 2005183, 0, 5653574, 4, { 170.853394f, -7.671008f, -20.209290f }, 1.000000f, 0.034435f, 0); 
    instance.addEObj( "Tornjournalpage_4", 2005184, 0, 5653575, 4, { 208.382401f, -8.050000f, -58.810051f }, 0.991760f, 0.103443f, 0); 
    instance.addEObj( "Barracksdoor", 2005177, 5584421, 5658825, 4, { 158.730606f, -8.011047f, -24.266649f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "Lordcommandersseat", 2005178, 5584424, 5658827, 4, { 192.164307f, -8.050052f, -70.690117f }, 0.991760f, 0.000048f, 0); 
    instance.addEObj( "unknown_10", 2005179, 5584425, 5658830, 4, { 191.948196f, -8.000000f, -159.505096f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_11", 2005185, 5584476, 5658834, 4, { 96.173714f, 24.000000f, -222.821701f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_12", 2005186, 5584485, 5658835, 4, { 21.875490f, 28.000000f, -217.942505f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "unknown_13", 2005187, 5584486, 5658836, 4, { -35.156700f, 32.000000f, -286.161285f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "sgvf_r2d1_b0622", 2005320, 5800343, 5801710, 4, { 179.680298f, 16.000111f, -261.236206f }, 1.000000f, 0.000000f, 0); 
    // States -> snow_def_01 (id: 3) snow_start_01 (id: 4) snow_start_02 (id: 5) 
    instance.addEObj( "sgvf_r2d1_b0622_1", 2005321, 5800818, 5801711, 4, { 127.707603f, 20.323111f, -262.321411f }, 1.000000f, 0.000000f, 0); 
    // States -> snow_def_01 (id: 3) snow_start_01 (id: 4) snow_start_02 (id: 5) 
    instance.addEObj( "sgvf_r2d1_b0622_2", 2005322, 5800840, 5801715, 4, { 5.201134f, 28.557409f, -289.850006f }, 1.000000f, 0.000000f, 0); 
    // States -> snow_def_01 (id: 3) snow_start_01 (id: 4) snow_start_02 (id: 5) 
    instance.addEObj( "sgvf_r2d1_b0622_3", 2005323, 5800842, 5801725, 4, { -21.532181f, 32.000061f, -289.092407f }, 1.000000f, 0.000000f, 0); 
    // States -> snow_def_01 (id: 3) snow_start_01 (id: 4) snow_start_02 (id: 5) 
    instance.addEObj( "unknown_14", 2005353, 5584312, 5821638, 4, { -73.144119f, 32.000000f, -405.536011f }, 1.000000f, 0.000000f, 0); 
    instance.addEObj( "Chapeldoor", 2005357, 5584428, 5829566, 4, { -69.550163f, 31.950060f, -291.505493f }, 1.000000f, 0.000000f, 0); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheDuskVigil );