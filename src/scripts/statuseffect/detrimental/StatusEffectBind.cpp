#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include "StatusEffect/StatusEffect.h"
#include <Action/CommonAction.h>

#include <Actor/Chara.h>

using namespace Sapphire;
using namespace Sapphire::World::Action;

class StatusEffectBind : public Sapphire::ScriptAPI::StatusEffectScript
{
public:
  StatusEffectBind() : Sapphire::ScriptAPI::StatusEffectScript( Bind )
  {
  }

  void onPlayerHit( Entity::Chara& hitActor, Sapphire::StatusEffect::StatusEffect& effect ) override
  {
    hitActor.removeSingleStatusEffectById( Bind );
  }
};

EXPOSE_SCRIPT( StatusEffectBind );