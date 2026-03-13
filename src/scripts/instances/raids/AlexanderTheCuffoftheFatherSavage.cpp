#include <ScriptObject.h>
#include <Territory/InstanceContent.h>
#include <Actor/EventObject.h>

using namespace Sapphire;

class AlexanderTheCuffoftheFatherSavage : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  AlexanderTheCuffoftheFatherSavage() : Sapphire::ScriptAPI::InstanceContentScript( 30026 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    Entity::EventObjectPtr pEObj;

    pEObj = instance.addEObj( "Shortcut", 2000700, 0, 5787831, 4, { -19.655809f, 31.065201f, 144.212204f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "Entrance", 2000182, 5787826, 5787836, 5, { -16.006710f, 36.148560f, 161.008804f }, 0.991760f, 0.000048f, 0 ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    pEObj->addCollisionBox( { -16.006472, 38.131939, 158.033432 }, 0.000048, 1.289288, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { -15.997036, 38.132221, 163.983994 }, 0.000048, 1.289288, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { -13.031334, 38.131939, 161.012711 }, -1.570403, 1.289288, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { -18.981895, 38.132225, 161.019455 }, -1.570403, 1.289288, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { -18.089212, 38.132080, 158.925919 }, -0.785350, 1.388464, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { -13.924018, 38.132080, 163.091507 }, -0.785350, 1.388464, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { -13.923819, 38.131882, 158.926117 }, 0.785446, 1.388464, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { -18.089411, 38.132278, 163.091309 }, 0.785446, 1.388464, 3.967041, 0.247940 );

    pEObj = instance.addEObj( "unknown_0", 2005047, 5796486, 5787837, 4, { -16.006710f, 28.995720f, 121.127502f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "Steamspoutingcontraption", 2005048, 5828187, 5787838, 4, { -20.999439f, 28.890051f, 120.379700f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_1", 2005047, 5796475, 5787839, 4, { -15.991690f, 25.994120f, 104.104698f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -15.991690, 25.579119, 104.104698 }, -0.000000, 14.000000, 16.585751, 1.000000 );

    pEObj = instance.addEObj( "unknown_4", 2005428, 5828194, 5787840, 4, { -20.812780f, 25.885040f, 102.729103f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_2", 2005047, 5796479, 5787845, 4, { -0.042969f, -15.876210f, 39.414860f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "Steamspoutingcontraption_1", 2005427, 5828202, 5787846, 4, { -5.000190f, -15.985280f, 39.105530f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_3", 2005047, 5796481, 5787847, 4, { -0.042969f, -22.069151f, 4.294098f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -0.042969, -22.542309, 4.294098 }, -0.000000, 14.000000, 16.520830, 1.000000 );

    pEObj = instance.addEObj( "unknown_5", 2005428, 5828205, 5787848, 4, { -5.111024f, -22.178221f, 3.677231f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_6", 2002735, 0, 5787860, 4, { 0.000000f, -28.000000f, -53.246899f }, 0.750000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118", 2002872, 5787859, 5787861, 4, { -0.137953f, -26.000000f, -52.603008f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -0.137953, -23.500000, -52.603008 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_1", 2002872, 5787862, 5787863, 4, { 0.000000f, -26.000000f, -96.909851f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 0.000000, -23.500000, -96.909851 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "MagitekgobwalkerGVII", 2005126, 0, 5787870, 4, { -23.299919f, -27.250000f, -93.915253f }, 2.500000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "MagitekgobwalkerGVII_1", 2005474, 0, 5787871, 4, { -25.869850f, -27.250000f, -91.505951f }, 2.500000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "MagitekgobwalkerGVII_2", 2005475, 0, 5787872, 4, { -28.364830f, -27.250000f, -89.139442f }, 2.500000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_7", 2006105, 5883005, 5908667, 4, { 0.000000f, -28.000000f, -75.000000f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "Entrance_1", 2000182, 5908672, 5908677, 5, { 0.002526f, -28.000019f, -23.439610f }, 0.991760f, 0.000048f, 0 ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    pEObj->addCollisionBox( { 0.002764, -26.016642, -26.414986 }, 0.000048, 1.289288, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { 0.012200, -26.016356, -20.464424 }, 0.000048, 1.289288, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { 2.977902, -26.016642, -23.435703 }, -1.570403, 1.289288, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { -2.972661, -26.016356, -23.428961 }, -1.570403, 1.289288, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { -2.079976, -26.016499, -25.522501 }, -0.785350, 1.388464, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { 2.085218, -26.016499, -21.356909 }, -0.785350, 1.388464, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { 2.085418, -26.016699, -25.522301 }, 0.785446, 1.388464, 3.967041, 0.247940 );
    pEObj->addCollisionBox( { -2.080176, -26.016298, -21.357107 }, 0.785446, 1.388464, 3.967041, 0.247940 );

    pEObj = instance.addEObj( "MagitekgobwalkerGVII_3", 2005126, 0, 5912255, 4, { -24.477819f, -27.250000f, -93.315643f }, 2.500000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "MagitekgobwalkerGVII_4", 2005474, 0, 5912258, 4, { -27.127260f, -27.250000f, -90.671631f }, 2.500000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "Exit", 2005313, 5908620, 5941367, 4, { 0.000000f, -26.000000f, -110.560898f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "Exit_1", 2000139, 0, 5962679, 4, { 0.000000f, -27.991100f, -115.007500f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgpl_d2a2_ring1wall", 2005047, 5962936, 5962938, 4, { -16.018070f, 27.033091f, 118.517899f }, 1.000000f, 0.000000f, 0 ); 
    // States -> rw01_def (id: 33) rw01_opn (id: 34) rw01_around2opn (id: 35) 
    pEObj->addCollisionBox( { -16.018070, 27.033091, 118.517899 }, -0.000000, 14.000000, 17.000000, 1.000000 );

    pEObj = instance.addEObj( "sgpl_d2a2_ring3wall", 2005047, 5962937, 5962939, 4, { 4.629210f, -8.535899f, 53.038620f }, 1.000000f, 0.000000f, 0 ); 
    // States -> rw03_def (id: 31) rw03_opn (id: 32) rw03_around2opn (id: 33) 
    pEObj->addCollisionBox( { 4.629210, -8.535899, 53.038620 }, -0.000000, 14.000000, 17.000000, 1.000000 );


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

EXPOSE_SCRIPT( AlexanderTheCuffoftheFatherSavage );