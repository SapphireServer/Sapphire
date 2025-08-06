#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/CommonAction.h>
#include <Action/Action.h>
#include <StatusEffect/StatusEffect.h>
#include <Math/CalcStats.h>

using namespace Sapphire;
using namespace Sapphire::World::Action;

class ActionUnchained : public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionUnchained() : Sapphire::ScriptAPI::ActionScript( 50 )
  {
  }

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto pPlayer = action.getSourceChara()->getAsPlayer();
    auto pActionBuilder = action.getActionResultBuilder();

    if( !pPlayer || !pActionBuilder )
      return;

    if( auto status = pPlayer->getStatusEffectById( Defiance ); status )
      status->setModifier( Common::ParamModifier::DamageDealtPercent, 0 );

    int32_t aggro = Sapphire::Math::CalcStats::calcStatusAggro( *pPlayer );
    pActionBuilder->applyStatusEffectSelf( Unchained, aggro, 20000, 0 );
  }
};

EXPOSE_SCRIPT( ActionUnchained );