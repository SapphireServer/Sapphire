#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheDuskVigil :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheDuskVigil() :
    Sapphire::ScriptAPI::InstanceContentScript( 36 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "sgvf_w_lvd_b0118", 2002872, 5658893, 4, { -0.378468f, -0.000006f, 19.173130f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_0", 2002735, 0, 4, { -0.473083f, -0.015320f, 21.194759f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2005189, 5658883, 4, { 0.051215f, 0.000000f, -19.347589f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_1", 2002735, 0, 4, { 191.935699f, -8.000000f, -97.548279f }, 1.143130f, 0.000000f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2002872, 5670058, 4, { 191.873398f, -8.000000f, -94.706589f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2005190, 5670071, 4, { 192.629501f, -8.000000f, -145.825104f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_2", 2005319, 0, 4, { 191.294998f, -8.000000f, -126.640503f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_3", 2002735, 0, 4, { -69.815361f, 32.171459f, -368.314209f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgvf_w_lvd_b0118_4", 2002872, 5670105, 4, { -69.864067f, 32.000050f, -370.484314f }, 1.000000f, 0.000000f ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_4", 2005395, 0, 4, { -72.186203f, 32.000000f, -389.922302f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { -119.582703f, -47.846481f, 223.251007f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Exit", 2000139, 0, 4, { -69.846916f, 32.000000f, -403.795990f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Entrance", 2000182, 5653670, 5, { -135.662598f, -48.859058f, 229.988297f }, 0.991760f, 0.000048f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "unknown_5", 2005169, 5674328, 4, { -66.894547f, -5.577260f, 129.660202f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_6", 2005170, 5674333, 4, { -28.173691f, -5.988469f, 165.738907f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_7", 2005171, 5674334, 4, { 32.157242f, -8.242720f, 98.301018f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Coldsteellever", 2005172, 0, 4, { 9.864166f, -0.650611f, 48.260380f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Damagedwinch", 2005173, 5660757, 4, { -3.958177f, 1.907400f, 32.349579f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_8", 2005174, 5584415, 4, { -0.076084f, -0.115606f, 34.058880f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_9", 2006185, 5912762, 4, { -131.761703f, -48.569462f, 225.451996f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Tornjournalpage", 2005180, 0, 4, { 66.788696f, -3.996225f, -52.994629f }, 0.991760f, 1.343069f ); 
    instance.registerEObj( "Tornjournalpage_1", 2005181, 0, 4, { 96.351990f, -8.050000f, -30.383080f }, 1.000000f, 1.112220f ); 
    instance.registerEObj( "Tornjournalpage_2", 2005182, 0, 4, { 151.468704f, -7.345456f, -48.435421f }, 1.000000f, -0.025044f ); 
    instance.registerEObj( "Tornjournalpage_3", 2005183, 0, 4, { 170.853394f, -7.671008f, -20.209290f }, 1.000000f, 0.034435f ); 
    instance.registerEObj( "Tornjournalpage_4", 2005184, 0, 4, { 208.382401f, -8.050000f, -58.810051f }, 0.991760f, 0.103443f ); 
    instance.registerEObj( "Barracksdoor", 2005177, 5584421, 4, { 158.730606f, -8.011047f, -24.266649f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Lordcommandersseat", 2005178, 5584424, 4, { 192.164307f, -8.050052f, -70.690117f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_10", 2005179, 5584425, 4, { 191.948196f, -8.000000f, -159.505096f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_11", 2005185, 5584476, 4, { 96.173714f, 24.000000f, -222.821701f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_12", 2005186, 5584485, 4, { 21.875490f, 28.000000f, -217.942505f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_13", 2005187, 5584486, 4, { -35.156700f, 32.000000f, -286.161285f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgvf_r2d1_b0622", 2005320, 5800343, 4, { 179.680298f, 16.000111f, -261.236206f }, 1.000000f, 0.000000f ); 
    // States -> snow_def_01 (id: 3) snow_start_01 (id: 4) snow_start_02 (id: 5) 
    instance.registerEObj( "sgvf_r2d1_b0622_1", 2005321, 5800818, 4, { 127.707603f, 20.323111f, -262.321411f }, 1.000000f, 0.000000f ); 
    // States -> snow_def_01 (id: 3) snow_start_01 (id: 4) snow_start_02 (id: 5) 
    instance.registerEObj( "sgvf_r2d1_b0622_2", 2005322, 5800840, 4, { 5.201134f, 28.557409f, -289.850006f }, 1.000000f, 0.000000f ); 
    // States -> snow_def_01 (id: 3) snow_start_01 (id: 4) snow_start_02 (id: 5) 
    instance.registerEObj( "sgvf_r2d1_b0622_3", 2005323, 5800842, 4, { -21.532181f, 32.000061f, -289.092407f }, 1.000000f, 0.000000f ); 
    // States -> snow_def_01 (id: 3) snow_start_01 (id: 4) snow_start_02 (id: 5) 
    instance.registerEObj( "unknown_14", 2005353, 5584312, 4, { -73.144119f, 32.000000f, -405.536011f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Chapeldoor", 2005357, 5584428, 4, { -69.550163f, 31.950060f, -291.505493f }, 1.000000f, 0.000000f ); 

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