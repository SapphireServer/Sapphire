#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/CommonAction.h>
#include <Action/Action.h>
#include <StatusEffect/StatusEffect.h>

using namespace Sapphire;
using namespace Sapphire::World::Action;

class ActionInnerBeast : public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionInnerBeast() : Sapphire::ScriptAPI::ActionScript( 49 )
  {
  }

  static constexpr auto Potency = 300;

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto pPlayer = action.getSourceChara()->getAsPlayer();
    auto pSource = action.getSourceChara();
    auto pTarget = action.getHitChara();

    if( !pPlayer )
      return;
    
    if( auto status = pPlayer->getStatusEffectById( Defiance ); status )
      status->setModifier( Common::ParamModifier::DamageDealtPercent, 0 );

    auto dmg = action.calcDamage( Potency );
    action.getActionResultBuilder()->damage( pSource, pTarget, dmg.first, dmg.second );
    action.getActionResultBuilder()->heal( pTarget, pSource, dmg.first, Common::CalcResultType::TypeRecoverHp, Common::ActionResultFlag::EffectOnSource );

    action.getActionResultBuilder()->applyStatusEffectSelf( InnerBeast, 15000, 0, { StatusModifier{ Common::ParamModifier::DamageTakenPercent, -20 } } );
    
    if( !pPlayer->hasStatusEffect( Unchained ) )
    {
      if( auto status = pPlayer->getStatusEffectById( Defiance ); status )
        status->setModifier( Common::ParamModifier::DamageDealtPercent, -25 );
    }
  }
};

EXPOSE_SCRIPT( ActionInnerBeast );