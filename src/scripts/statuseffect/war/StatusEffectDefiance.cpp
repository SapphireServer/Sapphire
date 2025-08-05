#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/CommonAction.h>

using namespace Sapphire;
using namespace Sapphire::World::Action;

class StatusEffectDefiance : public Sapphire::ScriptAPI::StatusEffectScript
{
public:
  StatusEffectDefiance() : Sapphire::ScriptAPI::StatusEffectScript( 91 )
  {
  }

  void onExpire( Entity::Chara& actor ) override
  {
    actor.removeStatusEffectById( { Unchained, Wrath, WrathII, WrathIII, WrathIV, Infuriated } );
  }
};

EXPOSE_SCRIPT( StatusEffectDefiance );