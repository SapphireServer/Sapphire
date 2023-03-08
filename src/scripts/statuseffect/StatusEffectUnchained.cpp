#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/CommonAction.h>

using namespace Sapphire;
using namespace Sapphire::World::Action;

class StatusEffectUnchained : public Sapphire::ScriptAPI::StatusEffectScript
{
public:
  StatusEffectUnchained() : Sapphire::ScriptAPI::StatusEffectScript( 92 )
  {
  }

  void onExpire( Entity::Chara& actor ) override
  {
    if( actor.hasStatusEffect( Defiance ) )
      actor.addModifier( Common::ParamModifier::DamageDealtPercent, -25 );
  }
};

EXPOSE_SCRIPT( StatusEffectUnchained );