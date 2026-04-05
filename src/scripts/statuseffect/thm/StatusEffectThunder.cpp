#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Action/CommonAction.h>
#include <Action/Action.h>
#include <StatusEffect/StatusEffect.h>

using namespace Sapphire;
using namespace Sapphire::World::Action;
class StatusEffectThunder : public Sapphire::ScriptAPI::StatusEffectScript
{
public:
  StatusEffectThunder() : Sapphire::ScriptAPI::StatusEffectScript( ActionStatus::ThunderStatus )
  {
  }  
    
  void onApply( Sapphire::Entity::Chara& actor ) override
  {
    Logger::debug( "Thunder not yet implemented!" );
  }
};

EXPOSE_SCRIPT( StatusEffectThunder );