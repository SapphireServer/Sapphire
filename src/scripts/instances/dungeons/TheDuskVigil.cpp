#include <ScriptObject.h>
#include <Territory/InstanceContent.h>
#include <Actor/EventObject.h>

using namespace Sapphire;

class TheDuskVigil : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheDuskVigil() : Sapphire::ScriptAPI::InstanceContentScript( 36 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    Entity::EventObjectPtr pEObj;

    pEObj = instance.addEObj( "Tornjournalpage", 2005180, 0, 5653571, 4, { 66.788696f, -3.996225f, -52.994629f }, 0.991760f, 1.343069f, 0 ); 

    pEObj = instance.addEObj( "Tornjournalpage_1", 2005181, 0, 5653572, 4, { 96.351990f, -8.050000f, -30.383080f }, 1.000000f, 1.112220f, 0 ); 

    pEObj = instance.addEObj( "Tornjournalpage_2", 2005182, 0, 5653573, 4, { 151.468704f, -7.345456f, -48.435421f }, 1.000000f, -0.025044f, 0 ); 

    pEObj = instance.addEObj( "Tornjournalpage_3", 2005183, 0, 5653574, 4, { 170.853394f, -7.671008f, -20.209290f }, 1.000000f, 0.034435f, 0 ); 

    pEObj = instance.addEObj( "Tornjournalpage_4", 2005184, 0, 5653575, 4, { 208.382401f, -8.050000f, -58.810051f }, 0.991760f, 0.103443f, 0 ); 

    pEObj = instance.addEObj( "Shortcut", 2000700, 0, 5653683, 4, { -119.582703f, -47.846481f, 223.251007f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "Exit", 2000139, 0, 5653684, 4, { -69.846916f, 32.000000f, -403.795990f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "Entrance", 2000182, 5653670, 5653685, 5, { -135.662598f, -48.859058f, 229.988297f }, 0.991760f, 0.000048f, 0 ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    pEObj->addCollisionBox( { -135.662354, -46.875679, 227.012924 }, 0.000048, 1.289288, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { -135.652924, -46.875397, 232.963486 }, 0.000048, 1.289288, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { -132.687225, -46.875679, 229.992203 }, -1.570403, 1.289288, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { -138.637787, -46.875393, 229.998947 }, -1.570403, 1.289288, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { -137.745102, -46.875538, 227.905411 }, -0.785350, 1.388464, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { -133.579910, -46.875538, 232.070999 }, -0.785350, 1.388464, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { -133.579712, -46.875736, 227.905609 }, 0.785446, 1.388464, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { -137.745300, -46.875340, 232.070801 }, 0.785446, 1.388464, 3.967041, 0.247940 );

    pEObj = instance.addEObj( "unknown_5", 2005169, 5674328, 5653784, 4, { -66.894547f, -5.577260f, 129.660202f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_6", 2005170, 5674333, 5653787, 4, { -28.173691f, -5.988469f, 165.738907f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -40.645840, -1.988469, 158.393356 }, 0.501682, 1.000000, 8.000000, 6.942111 );
    pEObj->addCollisionBox( { -42.743942, -1.988469, 167.486542 }, -0.292034, 1.000000, 8.000000, 3.982156 );
    pEObj->addCollisionBox( { -41.648441, -1.988469, 172.970688 }, 0.018514, 1.000000, 8.000000, 2.136745 );

    pEObj = instance.addEObj( "unknown_7", 2005171, 5674334, 5653806, 4, { 32.157242f, -8.242720f, 98.301018f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { 26.281265, -6.258272, 111.770813 }, 0.089911, 16.768307, 5.950562, 0.871689 );

    pEObj = instance.addEObj( "Coldsteellever", 2005172, 0, 5653807, 4, { 9.864166f, -0.650611f, 48.260380f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "Damagedwinch", 2005173, 5660757, 5653808, 4, { -3.958177f, 1.907400f, 32.349579f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_8", 2005174, 5584415, 5653809, 4, { -0.076084f, -0.115606f, 34.058880f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -0.076084, 5.878464, 34.197163 }, -0.000000, 4.458357, 6.593477, 0.222935 );

    pEObj = instance.addEObj( "Barracksdoor", 2005177, 5584421, 5658825, 4, { 158.730606f, -8.011047f, -24.266649f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { 158.730881, -2.054325, -24.043789 }, 0.000048, 4.363746, 6.552383, 0.223146 );

    pEObj = instance.addEObj( "Lordcommandersseat", 2005178, 5584424, 5658827, 4, { 192.164307f, -8.050052f, -70.690117f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { 192.164581, -2.093329, -70.467255 }, 0.000048, 4.363746, 6.552383, 0.223146 );

    pEObj = instance.addEObj( "unknown_10", 2005179, 5584425, 5658830, 4, { 191.948196f, -8.000000f, -159.505096f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 191.948196, -1.993799, -159.280090 }, -0.000000, 4.400000, 6.606821, 0.225000 );

    pEObj = instance.addEObj( "unknown_11", 2005185, 5584476, 5658834, 4, { 96.173714f, 24.000000f, -222.821701f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 96.173714, 30.000000, -222.245819 }, -0.000000, 6.000000, 6.000000, 0.500000 );
    pEObj->addCollisionBox( { 96.173714, 26.000000, -220.581055 }, -0.000000, 6.000000, 2.000000, 1.250000 );
    pEObj->addCollisionBox( { 102.528946, 26.000000, -221.174973 }, -0.517995, 1.250000, 2.000000, 1.432575 );
    pEObj->addCollisionBox( { 90.003777, 26.000000, -221.166351 }, 0.588395, 1.250000, 2.000000, 1.432575 );
    pEObj->addCollisionBox( { 88.406006, 26.000000, -222.599899 }, 0.895483, 1.377504, 2.000000, 1.385448 );
    pEObj->addCollisionBox( { 104.190941, 26.000000, -222.442017 }, -0.777176, 1.252031, 2.000000, 1.432575 );

    pEObj = instance.addEObj( "unknown_12", 2005186, 5584485, 5658835, 4, { 21.875490f, 28.000000f, -217.942505f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 21.875490, 34.000000, -217.366623 }, -0.000000, 6.000000, 6.000000, 0.500000 );
    pEObj->addCollisionBox( { 21.875490, 30.000000, -215.701859 }, -0.000000, 6.000000, 2.000000, 1.250000 );
    pEObj->addCollisionBox( { 28.230721, 30.000000, -216.295776 }, -0.517995, 1.250000, 2.000000, 1.432575 );
    pEObj->addCollisionBox( { 15.705553, 30.000000, -216.287155 }, 0.588395, 1.250000, 2.000000, 1.432575 );
    pEObj->addCollisionBox( { 14.107782, 30.000000, -217.720703 }, 0.895483, 1.377504, 2.000000, 1.385448 );
    pEObj->addCollisionBox( { 29.892717, 30.000000, -217.562820 }, -0.777176, 1.252031, 2.000000, 1.432575 );

    pEObj = instance.addEObj( "unknown_13", 2005187, 5584486, 5658836, 4, { -35.156700f, 32.000000f, -286.161285f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -35.156700, 38.000000, -285.585388 }, -0.000000, 6.000000, 6.000000, 0.500000 );
    pEObj->addCollisionBox( { -35.156700, 34.000000, -283.920624 }, -0.000000, 6.000000, 2.000000, 1.250000 );
    pEObj->addCollisionBox( { -28.801470, 34.000000, -284.514557 }, -0.517995, 1.250000, 2.000000, 1.432575 );
    pEObj->addCollisionBox( { -41.326637, 34.000000, -284.505951 }, 0.588395, 1.250000, 2.000000, 1.432575 );
    pEObj->addCollisionBox( { -42.924408, 34.000000, -285.939484 }, 0.895483, 1.377504, 2.000000, 1.385448 );
    pEObj->addCollisionBox( { -27.139473, 34.000000, -285.781586 }, -0.777176, 1.252031, 2.000000, 1.432575 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118", 2002872, 5658893, 5658895, 4, { -0.378468f, -0.000006f, 19.173130f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -0.378468, 2.499994, 19.173130 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "unknown_0", 2002735, 0, 5658896, 4, { -0.473083f, -0.015320f, 21.194759f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_1", 2005189, 5658883, 5658897, 4, { 0.051215f, 0.000000f, -19.347589f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 0.051215, 2.500000, -19.347589 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_3", 2005190, 5670071, 5670053, 4, { 192.629501f, -8.000000f, -145.825104f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 192.629501, -5.500000, -145.825104 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "unknown_1", 2002735, 0, 5670054, 4, { 191.935699f, -8.000000f, -97.548279f }, 1.143130f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_2", 2002872, 5670058, 5670061, 4, { 191.873398f, -8.000000f, -94.706589f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 191.873398, -5.500000, -94.706589 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "unknown_3", 2002735, 0, 5670083, 4, { -69.815361f, 32.171459f, -368.314209f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_4", 2002872, 5670105, 5670104, 4, { -69.864067f, 32.000050f, -370.484314f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -69.864067, 34.500050, -370.484314 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "unknown_2", 2005319, 0, 5797171, 4, { 191.294998f, -8.000000f, -126.640503f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgvf_r2d1_b0622", 2005320, 5800343, 5801710, 4, { 179.680298f, 16.000111f, -261.236206f }, 1.000000f, 0.000000f, 0 ); 
    // States -> snow_def_01 (id: 3) snow_start_01 (id: 4) snow_start_02 (id: 5) 

    pEObj = instance.addEObj( "sgvf_r2d1_b0622_1", 2005321, 5800818, 5801711, 4, { 127.707603f, 20.323111f, -262.321411f }, 1.000000f, 0.000000f, 0 ); 
    // States -> snow_def_01 (id: 3) snow_start_01 (id: 4) snow_start_02 (id: 5) 

    pEObj = instance.addEObj( "sgvf_r2d1_b0622_2", 2005322, 5800840, 5801715, 4, { 5.201134f, 28.557409f, -289.850006f }, 1.000000f, 0.000000f, 0 ); 
    // States -> snow_def_01 (id: 3) snow_start_01 (id: 4) snow_start_02 (id: 5) 

    pEObj = instance.addEObj( "sgvf_r2d1_b0622_3", 2005323, 5800842, 5801725, 4, { -21.532181f, 32.000061f, -289.092407f }, 1.000000f, 0.000000f, 0 ); 
    // States -> snow_def_01 (id: 3) snow_start_01 (id: 4) snow_start_02 (id: 5) 

    pEObj = instance.addEObj( "unknown_14", 2005353, 5584312, 5821638, 4, { -73.144119f, 32.000000f, -405.536011f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "Chapeldoor", 2005357, 5584428, 5829566, 4, { -69.550163f, 31.950060f, -291.505493f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -69.550163, 37.956261, -291.280487 }, -0.000000, 4.400000, 6.606821, 0.225000 );

    pEObj = instance.addEObj( "unknown_4", 2005395, 0, 5837149, 4, { -72.186203f, 32.000000f, -389.922302f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_9", 2006185, 5912762, 5913191, 4, { -131.761703f, -48.569462f, 225.451996f }, 0.991760f, 0.000048f, 0 ); 


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

EXPOSE_SCRIPT( TheDuskVigil );