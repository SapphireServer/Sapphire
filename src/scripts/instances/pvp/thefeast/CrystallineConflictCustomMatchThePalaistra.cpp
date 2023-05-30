#include <ScriptObject.h>
#include <Territory/InstanceContent.h>

using namespace Sapphire;

class CrystallineConflictCustomMatchThePalaistra : public Sapphire::ScriptAPI::InstanceContentScript
{
public:
  CrystallineConflictCustomMatchThePalaistra() : Sapphire::ScriptAPI::InstanceContentScript( 40033 )
  { }

  void onInit( InstanceContent& instance ) override
  {

  }

  void onUpdate( InstanceContent& instance, uint64_t tickCount ) override
  {

  }

  void onEnterTerritory( InstanceContent& instance, Entity::Player& player, uint32_t eventId, uint16_t param1,
                         uint16_t param2 ) override
  {

  }

};

EXPOSE_SCRIPT( CrystallineConflictCustomMatchThePalaistra );