#include <ScriptObject.h>
#include <Action/CommonAction.h>
#include <Action/Action.h>
#include <Actor/Player.h>
#include <Action/Job/THM/AstralUmbral.h>


using namespace Sapphire;
using namespace Sapphire::World::Action;

class ActionThunder : public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionThunder() : Sapphire::ScriptAPI::ActionScript( ActionSkill::Thunder )
  {
  }
  static constexpr auto Potency = 40;
  
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
    pActionBuilder->applyStatusEffect( pTarget, ThunderStatus, 18000, 0, {}, static_cast< uint32_t >( Common::StatusEffectFlag::DebuffCategory ), false, true );
  }
};

EXPOSE_SCRIPT( ActionThunder );