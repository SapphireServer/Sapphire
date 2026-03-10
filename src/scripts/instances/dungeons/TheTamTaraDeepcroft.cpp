#include <ScriptObject.h>
#include <Territory/InstanceContent.h>
#include <Actor/EventObject.h>

using namespace Sapphire;

class TheTamTaraDeepcroft : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheTamTaraDeepcroft() : Sapphire::ScriptAPI::InstanceContentScript( 2 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    Entity::EventObjectPtr pEObj;

    pEObj = instance.addEObj( "Cultistorb", 2000061, 3816929, 1958519, 4, { -8.115554f, 31.427530f, -15.950320f }, 1.000000f, -1.570451f, 0 ); 
    // States -> vf_beam1_on (id: 10) vf_beam1_off (id: 11) all_off (id: 22) 

    pEObj = instance.addEObj( "Cultistorb_1", 2000062, 3817025, 1958523, 4, { -22.784361f, 25.526300f, 20.482220f }, 1.000000f, -0.625840f, 0 ); 
    // States -> vf_beam2_off (id: 5) vf_beam2_on (id: 6) all_off (id: 16) 

    pEObj = instance.addEObj( "Exit", 2000139, 0, 1958526, 4, { -42.771080f, 14.067750f, -17.288521f }, 0.991789f, 0.000144f, 0 ); 

    pEObj = instance.addEObj( "Sealedbarrier", 2000060, 2065984, 1958528, 4, { -103.196800f, 16.825590f, 15.152160f }, 0.950000f, -1.044062f, 0 ); 

    pEObj = instance.addEObj( "Cultistrosary", 2000057, 0, 1958529, 4, { -179.952606f, 14.711600f, -4.996500f }, 0.750000f, -1.570796f, 0 ); 

    pEObj = instance.addEObj( "Cultistorb_2", 2000063, 3817039, 1958530, 4, { -89.733833f, 15.701490f, 13.923830f }, 0.991789f, 0.925052f, 0 ); 
    // States -> vf_beam3_off (id: 6) vf_beam3_on (id: 7) all_off (id: 17) 

    pEObj = instance.addEObj( "Cultistorb_3", 2000067, 3817052, 1958536, 4, { -94.766899f, 15.709600f, 3.820237f }, 1.000000f, 1.227256f, 0 ); 
    // States -> vf_beam3_off (id: 6) vf_beam3_on (id: 7) all_off (id: 17) 

    pEObj = instance.addEObj( "unknown_0", 2000054, 0, 1968438, 4, { -53.345570f, 49.647820f, -146.799103f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_5", 2001741, 3860684, 3689242, 4, { -64.365189f, 15.049010f, -4.720837f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -64.365189, 17.549011, -4.720837 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "unknown_1", 2001085, 0, 3861129, 4, { -68.771881f, 15.144450f, -3.840616f }, 0.539465f, 1.095248f, 0 ); 

    pEObj = instance.addEObj( "Shortcut", 2000700, 0, 4108030, 4, { -57.755428f, 47.653931f, -120.622597f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118", 2001697, 4108043, 4108044, 4, { 13.157160f, 29.280100f, -7.370761f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 13.157160, 31.780100, -7.370761 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_1", 2001698, 4108046, 4108049, 4, { -18.524361f, 23.342850f, 42.375740f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -18.524361, 25.842850, 42.375740 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_2", 2001699, 4108055, 4108060, 4, { 19.811380f, 30.119770f, -20.717630f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 19.811380, 32.619770, -20.717630 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "unknown_2", 2001700, 0, 4108066, 4, { 19.739401f, 30.119801f, -19.838511f }, 1.000000f, 1.409320f, 0 ); 

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_3", 2001701, 4108071, 4108072, 4, { -3.087158f, 23.754129f, 40.895020f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -3.087158, 26.254129, 40.895020 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "unknown_3", 2001702, 0, 4108073, 4, { -3.984208f, 23.754129f, 41.874859f }, 1.000000f, -0.675014f, 0 ); 

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_4", 2001703, 4108078, 4108097, 4, { -95.779678f, 14.524550f, 45.017761f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -95.779678, 17.024551, 45.017761 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "unknown_4", 2001704, 0, 4108099, 4, { -97.035683f, 14.524550f, 44.317101f }, 1.000000f, 0.656244f, 0 ); 

    pEObj = instance.addEObj( "Entrance", 2000182, 4108136, 4108138, 5, { -57.606178f, 49.507038f, -142.170105f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    pEObj->addCollisionBox( { -57.606178, 51.507038, -145.170105 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -57.596375, 51.507038, -139.170105 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -54.606178, 51.507038, -142.166214 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -60.606178, 51.507038, -142.159134 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -59.706177, 51.507038, -144.270111 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -55.506180, 51.507038, -140.070099 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -55.506180, 51.507038, -144.270111 }, 0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -59.706177, 51.507038, -140.070099 }, 0.785398, 1.400000, 4.000000, 0.250000 );


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

EXPOSE_SCRIPT( TheTamTaraDeepcroft );