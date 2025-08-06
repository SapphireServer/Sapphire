#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/CommonAction.h>
#include <Action/Action.h>
#include <StatusEffect/StatusEffect.h>
#include <Math/CalcStats.h>

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
    auto pActionBuilder = action.getActionResultBuilder();

    if( !pPlayer || !pActionBuilder )
      return;
    
    if( auto status = pPlayer->getStatusEffectById( Defiance ); status )
      status->setModifier( Common::ParamModifier::DamageDealtPercent, 0 );

    auto dmg = action.calcDamage( Potency );
    int32_t aggro = Sapphire::Math::CalcStats::calcDamageAggro( *pSource, dmg.first );
    pActionBuilder->damage( pSource, pTarget, dmg.first, aggro, dmg.second );
    pActionBuilder->heal( pTarget, pSource, dmg.first, 0, Common::CalcResultType::TypeRecoverHp, Common::ActionResultFlag::EffectOnSource );

    pActionBuilder->applyStatusEffectSelf( InnerBeast, 0, 15000, 0, { StatusModifier{ Common::ParamModifier::DamageTakenPercent, -20 } } );
    
    if( !pPlayer->hasStatusEffect( Unchained ) )
    {
      if( auto status = pPlayer->getStatusEffectById( Defiance ); status )
        status->setModifier( Common::ParamModifier::DamageDealtPercent, -25 );
    }
  }
};

EXPOSE_SCRIPT( ActionInnerBeast );