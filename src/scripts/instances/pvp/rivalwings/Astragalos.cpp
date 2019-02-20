#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class Astragalos :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  Astragalos() :
    Sapphire::ScriptAPI::InstanceContentScript( 51001 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2007457, 7033316, 4, { -140.058197f, 45.799999f, -133.960495f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_1", 2007457, 7033315, 4, { -123.008400f, 16.299999f, 103.779503f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_2", 2007457, 7033317, 4, { 105.712799f, 16.299980f, 114.356003f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_3", 2007457, 7033318, 4, { 183.420807f, 45.799980f, -111.239098f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Powergenerator", 2009034, 7032566, 4, { 6.485046f, 46.386410f, -10.055730f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Hangarterminal", 2009035, 7032549, 4, { -258.015198f, 44.361351f, 21.038191f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Hangarterminal_1", 2009062, 7032550, 4, { -262.674988f, 44.773441f, -32.764599f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Hangarterminal_2", 2009063, 7032561, 4, { 276.628510f, 44.544209f, 18.968180f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Hangarterminal_3", 2009064, 7032562, 4, { 258.262787f, 44.210709f, 69.718079f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Ceruleumtank", 2009031, 0, 4, { 8.651855f, 46.280640f, -142.595596f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "Steamcannon", 2009032, 0, 4, { -181.307602f, 47.593700f, -28.846230f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Steamcannon_1", 2009033, 0, 4, { -178.482193f, 47.593700f, 2.992350f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "Steamcannon_2", 2009040, 0, 4, { 186.000504f, 47.578602f, 31.721189f }, 0.991760f, -0.454976f ); 
    instance.registerEObj( "Steamcannon_3", 2009041, 0, 4, { 196.952606f, 47.593700f, 1.659642f }, 1.000000f, -0.455053f ); 

  }

  void onUpdate( InstanceContent& instance, uint32_t currTime ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( Astragalos );