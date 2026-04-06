#include <ScriptObject.h>
#include <Action/CommonAction.h>
#include <Action/Action.h>
#include <Actor/Player.h>
#include <Action/Job/THM/AstralUmbral.h>


using namespace Sapphire;
using namespace Sapphire::World::Action;

class ActionFire : public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionFire() : Sapphire::ScriptAPI::ActionScript( ActionSkill::Fire )
  {
  }

  static constexpr auto Potency = 180;

  void onBeforeBootstrap( Sapphire::World::Action::Action& action ) override
  {
    auto pPlayer = action.getSourceChara()->getAsPlayer();
    if(pPlayer->getStatusEffectById(ActionStatus::UmbralIceIIIStatus))
    {
      action.setCastTime(action.getCastTime()*THM::AstralUmbralCastTimeReduction);
    }
  }
  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto pPlayer = action.getSourceChara()->getAsPlayer();
    auto pSource = action.getSourceChara();
    auto pTarget = action.getHitChara();
    auto pActionBuilder = action.getActionResultBuilder();
    if( !pActionBuilder )
      return;
    auto dmg = action.calcDamage( Potency );
    pActionBuilder->damage( pSource, pTarget, dmg.first, dmg.second );
    Sapphire::World::Action::THM::applyAstralFire( pSource, pActionBuilder );
  }
};

EXPOSE_SCRIPT( ActionFire );