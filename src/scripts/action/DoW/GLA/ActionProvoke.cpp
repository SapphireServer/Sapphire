#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Chara.h>
#include <Action/CommonAction.h>
#include <Action/Action.h>
#include <StatusEffect/StatusEffect.h>
#include <Math/CalcStats.h>
#include <Actor/BNpc.h>
#include <Util/UtilMath.h>

using namespace Sapphire;
using namespace Sapphire::World::Action;

class ActionProvoke : public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionProvoke() : Sapphire::ScriptAPI::ActionScript( Provoke )
  {
  }

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto pSource = action.getSourceChara();
    auto pTarget = action.getHitChara();
    auto pActionBuilder = action.getActionResultBuilder();

    if( !pTarget || !pActionBuilder || pTarget->isFriendly( *pSource ) )
      return;

    pTarget->getAsBNpc()->hateListAdd( pSource, ( pTarget->getAsBNpc()->hateListGetHighestValue() + 1 ) );
  }
};

EXPOSE_SCRIPT( ActionProvoke );