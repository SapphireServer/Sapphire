#include <ScriptObject.h>
#include <Territory/InstanceContent.h>
#include <Actor/EventObject.h>

using namespace Sapphire;

class AlexanderTheCuffoftheSon : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  AlexanderTheCuffoftheSon() : Sapphire::ScriptAPI::InstanceContentScript( 30031 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    Entity::EventObjectPtr pEObj;

    pEObj = instance.addEObj( "Entrance", 2000182, 6177892, 6177890, 5, { 16.000000f, 21.783440f, 91.573517f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    pEObj->addCollisionBox( { 16.000000, 23.783440, 88.573517 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 16.009802, 23.783440, 94.573517 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 19.000000, 23.783440, 91.577408 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 13.000000, 23.783440, 91.584496 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 13.900000, 23.783440, 89.473518 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 18.100000, 23.783440, 93.673515 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 18.100000, 23.783440, 89.473518 }, 0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 13.900000, 23.783440, 93.673515 }, 0.785398, 1.400000, 4.000000, 0.250000 );

    pEObj = instance.addEObj( "Shortcut", 2000700, 0, 6177891, 4, { 10.387650f, 18.918310f, 75.899696f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_1", 2004356, 6075850, 6183196, 4, { 16.000000f, 17.661369f, 68.195396f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "Steamspoutingcontraption", 2004357, 6075772, 6183197, 4, { 21.013269f, 19.288509f, 69.098198f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgpl_d2a2_ring1wall", 2004356, 6183194, 6183198, 4, { 16.000000f, 17.933451f, 69.738426f }, 1.000000f, 0.000000f, 0 ); 
    // States -> rw01_def (id: 33) rw01_opn (id: 34) rw01_around2opn (id: 35) 
    pEObj->addCollisionBox( { 16.000000, 17.933451, 69.738426 }, -0.000000, 14.000000, 17.000000, 1.000000 );

    pEObj = instance.addEObj( "unknown_2", 2004362, 6075779, 6183199, 4, { 21.207670f, 12.939710f, 41.993370f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 23.807671, 18.139709, 42.993370 }, -0.000000, 2.800000, 20.000000, 3.500000 );

    pEObj = instance.addEObj( "unknown_4", 2002735, 0, 6183911, 4, { 0.000000f, -25.959690f, -100.169899f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118", 2002872, 6183959, 6183912, 4, { 0.000000f, -26.000000f, -99.284462f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 0.000000, -23.500000, -99.284462 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "unknown_3", 2002872, 6185722, 6183961, 4, { 0.000000f, -25.918800f, -139.159302f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 0.000000, -25.918800, -136.159302 }, -0.000000, 20.000000, 10.000000, 10.000000 );

    pEObj = instance.addEObj( "unknown_5", 2002735, 0, 6183972, 4, { 0.000000f, -19.459700f, -163.887405f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_6", 2002872, 6185721, 6183973, 4, { 0.000000f, -19.913139f, -203.123398f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 0.000000, -19.913139, -200.123398 }, -0.000000, 20.000000, 10.000000, 10.000000 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_1", 2002872, 6183975, 6183974, 4, { 0.000000f, -20.000000f, -163.001999f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 0.000000, -17.500000, -163.001999 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "unknown_7", 2002735, 0, 6183978, 4, { 0.000000f, -13.500000f, -227.525406f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_8", 2002872, 6185576, 6183979, 4, { 0.000000f, -14.000000f, -267.622406f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 0.000000, -14.000000, -264.622406 }, -0.000000, 20.000000, 10.000000, 10.000000 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_2", 2002872, 6183981, 6183980, 4, { 0.000000f, -14.000000f, -226.639999f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 0.000000, -11.500000, -226.639999 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "unknown_9", 2002735, 0, 6183983, 4, { 0.000000f, -8.000000f, -286.936798f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_3", 2002872, 6183985, 6183984, 4, { 0.000000f, -8.000000f, -286.051392f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 0.000000, -5.500000, -286.051392 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "Exit_1", 2000139, 0, 6184063, 4, { 0.000000f, -7.921236f, -335.377502f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "Entrance_1", 2000182, 6184206, 6184205, 5, { 0.000000f, -26.000000f, -65.141693f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    pEObj->addCollisionBox( { 0.000000, -24.000000, -68.141693 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 0.009802, -24.000000, -62.141693 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 3.000000, -24.000000, -65.137802 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -3.000000, -24.000000, -65.130714 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -2.100000, -24.000000, -67.241692 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 2.100000, -24.000000, -63.041695 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 2.100000, -24.000000, -67.241692 }, 0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -2.100000, -24.000000, -63.041695 }, 0.785398, 1.400000, 4.000000, 0.250000 );

    pEObj = instance.addEObj( "unknown_10", 2006984, 6210606, 6220709, 4, { -0.151275f, -14.000000f, -248.039703f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_0", 2005400, 0, 6221308, 4, { -0.062597f, -7.999998f, -318.102112f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgvf_d2a8_b0882", 2006989, 6234539, 6234568, 4, { 1.000000f, -20.000000f, -184.000000f }, 1.000000f, 0.000000f, 0 ); 
    // States -> brr_off (id: 2) brr_on2off (id: 3) brr_off2on (id: 5) 

    pEObj = instance.addEObj( "Exit", 2005313, 6186651, 6238484, 4, { -0.636187f, -7.999998f, -335.408813f }, 1.000000f, 0.000000f, 0 ); 


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

EXPOSE_SCRIPT( AlexanderTheCuffoftheSon );