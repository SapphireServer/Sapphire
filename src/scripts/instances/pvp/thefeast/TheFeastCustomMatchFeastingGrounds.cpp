#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class TheFeastCustomMatchFeastingGrounds :
  public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  TheFeastCustomMatchFeastingGrounds() :
    Sapphire::ScriptAPI::InstanceContentScript( 40014 )
  { }

  void onInit( InstanceContent& instance ) override
  {
    instance.registerEObj( "unknown_0", 2006819, 6218908, 4, { -89.012909f, 8.477110f, -0.326954f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "unknown_1", 2006818, 6218909, 4, { 95.872437f, 8.468750f, -0.320496f }, 0.991760f, 0.000048f ); 
    instance.registerEObj( "sgpl_w_lvd_collison_only", 2002618, 6220121, 4, { -78.605072f, 0.920299f, 0.000000f }, 1.000000f, 0.000000f ); 
    instance.registerEObj( "sgpl_w_lvd_collison_only_1", 2002618, 6220123, 4, { 79.651703f, 0.811267f, -0.306571f }, 0.991760f, 0.000048f ); 

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( TheFeastCustomMatchFeastingGrounds );