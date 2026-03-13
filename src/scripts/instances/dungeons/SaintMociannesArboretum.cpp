#include <ScriptObject.h>
#include <Territory/InstanceContent.h>
#include <Actor/EventObject.h>

using namespace Sapphire;

class SaintMociannesArboretum : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  SaintMociannesArboretum() : Sapphire::ScriptAPI::InstanceContentScript( 41 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    Entity::EventObjectPtr pEObj;

    pEObj = instance.addEObj( "Entrance", 2000182, 6034530, 6034529, 5, { 0.231333f, 0.000002f, 140.623901f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    pEObj->addCollisionBox( { 0.231333, 2.000002, 137.623901 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 0.241135, 2.000002, 143.623901 }, -0.000000, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 3.231333, 2.000002, 140.627792 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -2.768667, 2.000002, 140.634872 }, -1.570451, 1.300000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -1.868667, 2.000002, 138.523895 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 2.331333, 2.000002, 142.723907 }, -0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { 2.331333, 2.000002, 138.523895 }, 0.785398, 1.400000, 4.000000, 0.250000 );
    pEObj->addCollisionBox( { -1.868667, 2.000002, 142.723907 }, 0.785398, 1.400000, 4.000000, 0.250000 );

    pEObj = instance.addEObj( "Shortcut", 2000700, 0, 6034569, 4, { 4.219861f, 0.000001f, 131.545197f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_1", 2006520, 6041801, 6034580, 4, { 113.481300f, 2.975464f, 19.363649f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { 113.481300, 2.975464, 19.363649 }, 0.000048, 11.901124, 11.901124, 1.487641 );

    pEObj = instance.addEObj( "unknown_2", 2006521, 6047538, 6034589, 4, { 67.640343f, 0.000000f, -71.112350f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { 67.640343, 3.000000, -65.612350 }, -0.000000, 12.000000, 5.000000, 1.000000 );

    pEObj = instance.addEObj( "unknown_4", 2006522, 5966533, 6034592, 4, { -125.780197f, -12.375120f, -188.891495f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { -125.779877, -7.220139, -190.478561 }, 0.000048, 9.917603, 5.306562, 1.487641 );
    pEObj->addCollisionBox( { -133.775497, -7.219756, -190.478943 }, 0.000048, 1.921986, 5.306562, 1.487641 );
    pEObj->addCollisionBox( { -117.897575, -7.220517, -190.478180 }, 0.000048, 2.035306, 5.306562, 1.487641 );

    pEObj = instance.addEObj( "unknown_5", 2006523, 6037786, 6034595, 4, { -234.627304f, -29.692921f, -182.589401f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { -234.627045, -24.537876, -182.837601 }, 0.000048, 9.917603, 5.306562, 0.098917 );
    pEObj->addCollisionBox( { -242.622665, -24.537493, -182.837982 }, 0.000048, 1.921986, 5.306562, 0.098917 );
    pEObj->addCollisionBox( { -226.744751, -24.538254, -182.837219 }, 0.000048, 2.035306, 5.306562, 0.098917 );

    pEObj = instance.addEObj( "unknown_7", 2006524, 6046538, 6034613, 4, { -102.066101f, -349.342285f, 55.198681f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -101.647392, -346.209137, 55.093605 }, -0.000000, 7.301290, 6.313241, 0.500000 );

    pEObj = instance.addEObj( "unknown_8", 2006526, 6046053, 6034616, 4, { -86.535728f, -356.521301f, -4.785355f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -85.722336, -351.841309, -4.884943 }, -0.510586, 5.603866, 6.476184, 4.506908 );
    pEObj->addCollisionBox( { -91.011955, -350.853882, -6.173292 }, -1.326202, 3.544958, 7.532939, 0.814099 );
    pEObj->addCollisionBox( { -87.830727, -350.853882, -10.096910 }, -0.431498, 3.351527, 7.532939, 0.600359 );
    pEObj->addCollisionBox( { -82.733124, -350.875458, -9.320484 }, 0.849470, 3.720198, 7.554501, 0.662047 );

    pEObj = instance.addEObj( "unknown_9", 2006527, 6046055, 6034617, 4, { -104.847900f, -356.059692f, 4.146202f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -104.034508, -351.379700, 4.046614 }, -0.510586, 5.603866, 6.476184, 4.506908 );
    pEObj->addCollisionBox( { -109.324127, -350.392273, 2.758265 }, -1.326202, 3.544958, 7.532939, 0.814099 );
    pEObj->addCollisionBox( { -106.142899, -350.392273, -1.165354 }, -0.431498, 3.351527, 7.532939, 0.600359 );
    pEObj->addCollisionBox( { -101.045296, -350.413849, -0.388927 }, 0.849470, 3.720198, 7.554501, 0.662047 );

    pEObj = instance.addEObj( "unknown_10", 2006525, 6046572, 6037562, 4, { -47.545761f, -359.815613f, -33.600189f }, 1.000000f, 0.000000f, 0 ); 
    pEObj->addCollisionBox( { -47.261951, -356.682465, -33.600189 }, -0.000000, 7.553684, 6.313241, 1.400000 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_1", 2002872, 6037810, 6037807, 4, { 15.731990f, 3.000000f, -89.860413f }, 0.991760f, 0.000048f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { 15.732109, 5.479401, -89.860535 }, 0.000048, 7.438202, 3.967041, 0.743820 );

    pEObj = instance.addEObj( "unknown_15", 2002735, 0, 6037808, 4, { 18.234501f, 3.097534f, -90.928528f }, 0.991760f, 1.130897f, 0 ); 

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_2", 2006531, 6037814, 6037817, 4, { -17.876730f, 3.000000f, -82.649872f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -17.876730, 5.500000, -82.649872 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118", 2002872, 6038834, 6038839, 4, { -14.984150f, -350.000000f, -10.860330f }, 1.000000f, 0.622420f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -14.984150, -347.500000, -10.860330 }, 0.622420, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "Exit", 2000139, 0, 6038848, 4, { 10.788090f, -350.026703f, 7.522644f }, 0.991760f, 0.609911f, 0 ); 

    pEObj = instance.addEObj( "unknown_0", 2002735, 0, 6038858, 4, { -16.401690f, -350.000000f, -11.633360f }, 1.000000f, -0.981437f, 0 ); 

    pEObj = instance.addEObj( "sgvf_w_lvd_b0118_3", 2002872, 6041100, 6041105, 4, { -245.545395f, -36.853828f, -164.052200f }, 1.000000f, 0.000000f, 0 ); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    pEObj->addCollisionBox( { -245.545395, -34.353828, -164.052200 }, -0.000000, 7.500000, 4.000000, 0.750000 );

    pEObj = instance.addEObj( "unknown_16", 2002735, 0, 6041106, 4, { -245.869705f, -36.958050f, -162.887695f }, 0.991760f, 0.541627f, 0 ); 

    pEObj = instance.addEObj( "unknown_17", 2006532, 6082449, 6041107, 4, { -260.975098f, -44.815800f, -108.476402f }, 0.991760f, 0.000048f, 0 ); 
    pEObj->addCollisionBox( { -260.975098, -44.815800, -108.476402 }, 0.000048, 0.991760, 0.991760, 0.991760 );

    pEObj = instance.addEObj( "unknown_18", 2006566, 0, 6057322, 4, { -263.891296f, -44.889751f, -114.578796f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_6", 2006594, 6068325, 6069838, 4, { -244.373505f, -37.105370f, -163.858002f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_11", 2006596, 6058396, 6069983, 4, { -262.334015f, -39.551819f, -111.790802f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_12", 2006597, 6077036, 6080417, 4, { -248.226898f, -46.000000f, -133.086304f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_13", 2006598, 6077035, 6080419, 4, { -283.791992f, -46.000000f, -122.796700f }, 1.000000f, 0.000000f, 0 ); 

    pEObj = instance.addEObj( "unknown_14", 2006609, 6084794, 6081661, 4, { -242.938904f, -44.861469f, -84.336670f }, 0.991760f, 0.000048f, 0 ); 

    pEObj = instance.addEObj( "unknown_3", 2006586, 0, 6110202, 4, { 85.017906f, -0.020000f, -58.585030f }, 1.000000f, 0.000000f, 0 ); 


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

EXPOSE_SCRIPT( SaintMociannesArboretum );