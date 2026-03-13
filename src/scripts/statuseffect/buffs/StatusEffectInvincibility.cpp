#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include "StatusEffect/StatusEffect.h"

#include <Action/CommonAction.h>
#include <Actor/Chara.h>

#include "Common.h"

using namespace Sapphire;
using namespace Sapphire::World::Action;

class StatusEffectInvincibility : public Sapphire::ScriptAPI::StatusEffectScript
{
public:
  StatusEffectInvincibility() : Sapphire::ScriptAPI::StatusEffectScript( 325 )
  {
  }

  void onApply( Entity::Chara& actor ) override
  {
    actor.setInvincibilityType( Common::InvincibilityIgnoreDamage );
  }

  void onExpire( Entity::Chara& actor ) override
  {
    actor.setInvincibilityType( Common::InvincibilityNone );
  }
};

EXPOSE_SCRIPT( StatusEffectInvincibility );