#include <ScriptObject.h>
#include <Territory/InstanceContent.h>
#include <Actor/EventObject.h>

using namespace Sapphire;

class TheVault : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheVault() : Sapphire::ScriptAPI::InstanceContentScript( 34 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    Entity::EventObjectPtr pEObj;

    pEObj = instance.addEObj( "Entrance", 2000182, 5578486, 5578515, 5, { -5.010592f, -300.000000f, 86.198753f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    pEObj->addCollisionBox( { -5.010592, -298.000000, 83.198753 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -5.000790, -298.000000, 89.198753 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -2.010592, -298.000000, 86.202644 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -8.010592, -298.000000, 86.209732 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -7.110592, -298.000000, 84.098755 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -2.910592, -298.000000, 88.298752 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -2.910592, -298.000000, 84.098755 }, 0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -7.110592, -298.000000, 88.298752 }, 0.785398, 1.400000, 4.000000, 0.250000 );

    pEObj = instance.addEObj( "Shortcut", 2000700, 0, 5578521, 4, { 11.135890f, -300.000000f, 78.862717f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "Exit", 2000139, 0, 5578561, 4, { 0.136796f, 299.977112f, -9.654591f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_9", 2005087, 5474300, 5579442, 4, { 37.735470f, -300.007690f, 30.228149f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { 37.735786, -293.372772, 30.227831 }, 0.000048, 6.545619, 7.298408, 0.354825 );

    pEObj = instance.addEObj( "unknown_10", 2005088, 5499954, 5579463, 4, { 51.884090f, -300.000000f, -35.577080f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 51.884090, -297.804291, -35.577080 }, -0.000000, 1.716209, 2.433349, 0.049223 );

    pEObj = instance.addEObj( "unknown_11", 2005089, 5474303, 5579464, 4, { 44.255379f, -300.000000f, -31.015051f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 44.255379, -293.309967, -31.015053 }, -0.000000, 6.600001, 7.359044, 0.357773 );

    pEObj = instance.addEObj( "unknown_12", 2005090, 5474308, 5579478, 4, { -36.242680f, -300.000000f, -29.871010f }, 1.000000f, -0.000345f, 0 ); 
    pEObj->addCollisionBox( { -36.242680, -293.309967, -29.871012 }, -0.000345, 6.600001, 7.359044, 0.357773 );

    pEObj = instance.addEObj( "unknown_13", 2005091, 5474306, 5579537, 4, { -37.591751f, -300.000000f, -69.819733f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -37.591751, -293.309967, -69.819733 }, -0.000000, 6.600001, 7.359044, 0.357773 );

    pEObj = instance.addEObj( "unknown_14", 2005092, 5499959, 5579540, 4, { -33.701191f, -300.000000f, -79.843872f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -33.701191, -297.804291, -79.843872 }, -0.000000, 1.716209, 2.433349, 0.049223 );

    pEObj = instance.addEObj( "unknown_15", 2005093, 5499966, 5579647, 4, { 6.953651f, -281.975708f, -150.744995f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 6.953650, -279.779999, -150.744995 }, -0.000000, 1.716209, 2.433349, 0.049223 );

    pEObj = instance.addEObj( "unknown_16", 2005094, 5476161, 5580240, 4, { 101.518402f, -263.140503f, -12.115350f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_17", 2005095, 5476162, 5580241, 4, { 101.390800f, -263.204315f, 11.842000f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_18", 2005096, 5474532, 5580265, 4, { 99.222763f, -264.000000f, -0.362554f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 99.222763, -261.000000, -3.062554 }, -0.000000, 5.000000, 6.000000, 1.800000 );

    pEObj = instance.addEObj( "unknown_19", 2005097, 5499987, 5580413, 4, { 22.634041f, 0.000000f, 71.960167f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 22.634041, 2.195720, 71.490746 }, -0.000000, 1.716209, 2.433349, 0.010000 );

    pEObj = instance.addEObj( "unknown_20", 2005098, 5499980, 5580417, 4, { -17.585621f, 0.000000f, 72.136276f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -17.585621, 2.195720, 72.136276 }, -0.000000, 1.716209, 2.433349, 0.049223 );

    pEObj = instance.addEObj( "unknown_21", 2005099, 5444302, 5580677, 4, { -92.607063f, -0.015320f, 0.076233f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { -92.606789, 2.959833, -2.601663 }, 0.000048, 4.958802, 5.950562, 1.785169 );

    pEObj = instance.addEObj( "unknown_22", 2005100, 5499663, 5580709, 4, { -52.663239f, 291.000000f, 42.623951f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_23", 2005101, 5499660, 5580710, 4, { -67.359016f, 291.000000f, 42.656231f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_24", 2005102, 5499645, 5580711, 4, { -66.869476f, 291.000000f, 55.587841f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_25", 2005103, 5499653, 5580712, 4, { -53.398609f, 291.000000f, 55.570320f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_26", 2005104, 5499600, 5580718, 4, { -46.140011f, 291.000000f, 48.667049f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -46.139957, 295.332245, 48.863102 }, -0.000000, 3.784089, 4.766242, 0.359074 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_2", 2002872, 5581166, 5581161, 4, { -18.416611f, -292.000000f, -99.614120f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -18.416611, -289.500000, -99.614120 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "unknown_7", 2002735, 0, 5581162, 4, { -20.099001f, -292.000000f, -98.859291f }, 0.700000f, -1.570796f, 0 ); 

    pEObj = instance.addEObj( "sgvf_w_lvd_b0250_1", 2005106, 5581173, 5581182, 4, { -0.494135f, -292.000000f, -117.713799f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -0.494135, -289.500000, -117.713799 }, -0.000000, 15.000000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "unknown_8", 2002735, 0, 5583052, 4, { 18.757099f, 0.000000f, 72.079903f }, 1.000000f, -1.570451f, 0 ); 

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_3", 2002872, 5583050, 5583053, 4, { 17.161560f, 0.000000f, 73.880867f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 17.161560, 2.500000, 73.880867 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118", 2002872, 5588600, 5588601, 4, { 0.359463f, 300.000000f, 26.171600f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 0.359463, 302.500000, 26.171600 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "unknown_0", 2002735, 0, 5588602, 4, { 0.428600f, 300.000000f, 24.562250f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_1", 2005580, 5873754, 5873755, 4, { 0.360928f, 300.000000f, -15.306860f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 0.360928, 302.500000, -15.306860 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "unknown_1", 2006743, 5474300, 6147777, 4, { 39.139400f, -300.007690f, 29.587160f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { 39.139717, -293.372772, 29.586842 }, 0.000048, 6.545619, 7.298408, 0.354825 );

    pEObj = instance.addEObj( "unknown_2", 2006744, 5474303, 6147778, 4, { 43.961182f, -299.855103f, -30.197689f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { 43.961498, -293.220184, -30.198008 }, 0.000048, 6.545619, 7.298408, 0.354825 );

    pEObj = instance.addEObj( "unknown_6", 2006748, 6143048, 6147779, 4, { 52.795311f, -299.984589f, -36.063671f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 52.795311, -297.788879, -36.063671 }, -0.000000, 1.716209, 2.433349, 0.049223 );

    pEObj = instance.addEObj( "unknown_3", 2006745, 6143050, 6147780, 4, { -34.927921f, -300.007690f, -80.460876f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { -34.927818, -297.830048, -80.460983 }, 0.000048, 1.702068, 2.413299, 0.048818 );

    pEObj = instance.addEObj( "unknown_4", 2006746, 6147782, 6147783, 4, { -38.559631f, -300.007690f, -72.068359f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { -38.559315, -293.372772, -72.068680 }, 0.000048, 6.545619, 7.298408, 0.354825 );

    pEObj = instance.addEObj( "unknown_5", 2006747, 6147781, 6147784, 4, { -38.986820f, -300.007690f, -30.014530f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { -38.986504, -293.372772, -30.014849 }, 0.000048, 6.545619, 7.298408, 0.354825 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0250", 2006749, 6147791, 6147792, 4, { 0.604760f, -291.999908f, -117.413803f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 0.604760, -289.499908, -117.413803 }, -0.000000, 15.000000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "Bonds", 2006752, 0, 6153827, 4, { -52.262211f, -300.000793f, -27.878300f }, 0.991760f, 0.000144f, 0 ); 

    pEObj = instance.addEObj( "Bonds_1", 2006752, 0, 6153828, 4, { 56.960300f, -299.984589f, -73.657806f }, 0.991760f, 0.000048f, 0 ); 


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

EXPOSE_SCRIPT( TheVault );