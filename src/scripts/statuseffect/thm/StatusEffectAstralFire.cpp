#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Action/CommonAction.h>
#include <Action/Action.h>
#include <StatusEffect/StatusEffect.h>

using namespace Sapphire;
using namespace Sapphire::World::Action;
class StatusEffectAstralFire : public Sapphire::ScriptAPI::StatusEffectScript
{
public:
  StatusEffectAstralFire() : Sapphire::ScriptAPI::StatusEffectScript( ActionStatus::AstralFireStatus )
  {
  }  
    
  void onApply( Sapphire::Entity::Chara& actor ) override
  {
    Logger::debug( "Astral fire not yet implemented!" );
  }
};

EXPOSE_SCRIPT( StatusEffectAstralFire );