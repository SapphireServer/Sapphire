#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Action/CommonAction.h>
#include <Action/Action.h>
#include <Actor/Player.h>


using namespace Sapphire;
using namespace Sapphire::World::Action;

class ActionBlizzard : public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionBlizzard() : Sapphire::ScriptAPI::ActionScript( ActionSkill::Blizzard )
  {
  }
  static constexpr auto Potency = 180;
  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto pPlayer = action.getSourceChara()->getAsPlayer();
    auto pSource = action.getSourceChara();
    auto pTarget = action.getHitChara();
    auto pActionBuilder = action.getActionResultBuilder();
    if( !pActionBuilder )
      return;
    action.calcDamage(Potency);

    auto dmg = action.calcDamage( Potency );
    pActionBuilder->damage( pSource, pTarget, dmg.first, dmg.second );
  }
};

EXPOSE_SCRIPT( ActionBlizzard );