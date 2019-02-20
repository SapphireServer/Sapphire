#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class ItsProbablyaTrap :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  ItsProbablyaTrap() :
    Sapphire::ScriptAPI::InstanceContentScript( 5005 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2000608, 6538194, 4, { -27.571140f, -3.000000f, 46.619968f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_1", 2000608, 6538193, 4, { -28.307659f, 3.999977f, 61.762589f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "ClanHuntboard", 2008655, 6422886, 4, { -31.520060f, 0.076252f, -43.853790f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgbg_w_qic_004_03a", 2002872, 6799085, 4, { -79.087517f, -3.006042f, 41.336670f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgbg_w_qic_004_03a_1", 2002872, 6799087, 4, { -61.668732f, -3.014119f, 84.855003f }, 0.991760f, -1.567030f ); 
    instance.registerEObj( "unknown_2", 2007457, 6611234, 4, { 137.621094f, 14.816470f, 92.484863f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_3", 2007457, 6538193, 4, { -27.894131f, 3.999977f, 61.384491f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_4", 2007457, 6538194, 4, { -28.259020f, -3.000000f, 46.489510f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( InstanceContent& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( ItsProbablyaTrap );