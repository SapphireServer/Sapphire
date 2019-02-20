#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheRoyalMenagerie :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheRoyalMenagerie() :
    Sapphire::ScriptAPI::InstanceContentScript( 20045 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "Entrance", 2000182, 6842660, 5, { -12.652360f, -380.000000f, 1.417362f }, 1.000000f, 0.000000f ); 
    // States -> vf_lock_on (id: 11) vf_lock_of (id: 12) 
    instance.registerEObj( "Exit", 2000139, 0, 4, { -0.015320f, 620.000000f, -6.698792f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Barrelsoffiresand", 2003127, 0, 4, { -0.108200f, -380.000000f, 0.890151f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "unknown_0", 2007457, 6858507, 4, { -0.819489f, -380.000000f, 1.685981f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_1", 2007457, 6953496, 4, { -1.111895f, -380.000000f, 11.857690f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_2", 2007457, 6797912, 4, { -13.550160f, 620.000000f, -23.367689f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_3", 2007457, 6797914, 4, { -6.156202f, 620.000000f, -24.638531f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_4", 2007457, 6797913, 4, { 14.468520f, 620.000000f, -17.925461f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_5", 2007457, 6797908, 4, { -13.109160f, 620.000000f, -3.235081f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_6", 2007457, 6797907, 4, { 14.608040f, 620.000000f, 0.876270f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_7", 2007457, 6797909, 4, { -13.849610f, 620.000000f, 15.100500f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_8", 2007457, 6797911, 4, { 7.597056f, 620.000000f, 16.291180f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_9", 2007457, 6797910, 4, { 14.168900f, 620.000000f, 15.941650f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_10", 2007457, 6797906, 4, { 6.113630f, 620.000000f, 5.558393f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_11", 2007457, 6925491, 4, { 8.519539f, 620.000000f, 7.842079f }, 1.000000f, 0.000000f ); 

  }

  void onUpdate( InstanceContent& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheRoyalMenagerie );