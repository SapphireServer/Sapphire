#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheFellCourtofTroia : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheFellCourtofTroia() : Sapphire::ScriptAPI::InstanceContentScript( 88 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "Exit", 2000139, 0, 4, { -35.014530f, 385.000214f, -313.771210f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "Entrance", 2007457, 9305359, 5, { -31.431810f, -718.000000f, 129.892197f }, 1.000000f, 0.000000f); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Shortcut", 2000700, 0, 4, { -24.598009f, -718.000000f, 129.682800f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_0", 2002735, 0, 4, { 167.986603f, -700.007629f, 110.246300f }, 0.991760f, 0.000048f); 
    instance.registerEObj( "sgvf_w_lvd_b0118", 2002872, 9315932, 4, { 168.000000f, -700.000305f, 110.250000f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_1", 2002872, 9315948, 4, { 189.399994f, -700.000000f, 90.007004f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_1", 2002735, 0, 4, { 0.000000f, -698.000000f, -127.629997f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_2", 2002872, 9315956, 4, { 0.000000f, -698.000000f, -126.040001f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "sgvf_w_lvd_b0118_3", 2002872, 9315959, 4, { 0.000000f, -698.000000f, -170.509995f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_2", 2002735, 0, 4, { -35.785870f, 386.299896f, -247.542404f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "sgvf_w_lvd_b0118_4", 2002872, 9321137, 4, { -35.785870f, 386.299896f, -247.542404f }, 1.000000f, 0.000000f); 
    // States -> vf_bextwall_on (id: 3) vf_bextwall_of (id: 4) 
    instance.registerEObj( "unknown_3", 2013027, 0, 4, { -23.486071f, -698.000000f, -152.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_4", 2013028, 0, 4, { -23.292290f, -698.000000f, -155.000000f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "unknown_5", 2013026, 0, 4, { 0.000000f, -698.000000f, -145.000000f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Destination", 2013042, 0, 4, { 38.097801f, 348.049591f, 4.406200f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "unknown_6", 2013043, 0, 4, { -1.550820f, -698.010376f, -150.857803f }, 0.827808f, -1.519346f); 
    instance.registerEObj( "PassagetoTroiaKeep", 2013115, 0, 4, { 14.251640f, 351.304688f, 14.396480f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "PassagetoZerosdomain", 2013044, 0, 4, { 15.548890f, 360.385712f, -114.580002f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "Passagetothehydromanticterraces", 2013114, 0, 4, { 0.029306f, -692.640320f, -232.408295f }, 0.991760f, 0.000000f); 
    instance.registerEObj( "PassagetocarcereIV", 2013113, 0, 4, { -280.056885f, -716.735718f, 133.986603f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "PassagetoTroiaKeep_1", 2013112, 0, 4, { 259.931793f, -706.408020f, 90.013252f }, 1.000000f, 0.000000f); 
    instance.registerEObj( "PassagetoWeaversWarding", 2013040, 0, 4, { -49.492378f, -716.662598f, 130.708893f }, 1.000000f, 0.000000f); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheFellCourtofTroia );