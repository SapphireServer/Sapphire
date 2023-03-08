#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/CommonAction.h>
#include <Action/Action.h>

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
    
    if( !pPlayer->hasStatusEffect( Unchained ) )
      pPlayer->delModifier( Common::ParamModifier::DamageDealtPercent, -25 );

    auto dmg = action.calcDamage( Potency );
    action.getEffectbuilder()->damage( pSource, pTarget, dmg.first, dmg.second );
    action.getEffectbuilder()->heal( pTarget, pSource, dmg.first, Common::ActionHitSeverityType::NormalHeal,
                                     Common::ActionEffectResultFlag::EffectOnSource );

    action.applyStatusEffectSelf( InnerBeast );
    pPlayer->addStatusEffectByIdIfNotExist( InnerBeast, 15000, *pSource, 
                                            { StatusModifier{ Common::ParamModifier::DamageTakenPercent, -20 } } );
    
    if( !pPlayer->hasStatusEffect( Unchained ) )
      pPlayer->addModifier( Common::ParamModifier::DamageDealtPercent, -25 );
  }
};

EXPOSE_SCRIPT( ActionInnerBeast );