#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include "StatusEffect/StatusEffect.h"
#include <action/Action.h>
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

  void onPlayerHit( Entity::CharaPtr& attackTarget, Sapphire::StatusEffect::StatusEffect& effect ) override
  {
    attackTarget->removeSingleStatusEffectById( Bind );
  }
};

EXPOSE_SCRIPT( StatusEffectBind );