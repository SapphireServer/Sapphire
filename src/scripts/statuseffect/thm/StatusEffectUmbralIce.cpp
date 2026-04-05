#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Action/CommonAction.h>
#include <Action/Action.h>
#include <StatusEffect/StatusEffect.h>

using namespace Sapphire;
using namespace Sapphire::World::Action;
class StatusEffectUmbralIce : public Sapphire::ScriptAPI::StatusEffectScript
{
public:
  StatusEffectUmbralIce() : Sapphire::ScriptAPI::StatusEffectScript( ActionStatus::UmbralIceStatus )
  {
  }  
    
  void onApply( Sapphire::Entity::Chara& actor ) override
  {
    Logger::debug( "Umbral Ice not yet implemented!" );
  }
};

EXPOSE_SCRIPT( StatusEffectUmbralIce );