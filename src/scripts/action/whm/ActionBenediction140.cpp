#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/Action.h>
#include <Math/CalcStats.h>

using namespace Sapphire;

class ActionBenediction140 :
  public ScriptAPI::ActionScript
{
public:
  ActionBenediction140() :
    ScriptAPI::ActionScript( 140 )
  {
  }

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto pTarget = action.getHitChara();
    if( pTarget )
    {
      action.getEffectbuilder()->heal( pTarget, pTarget, pTarget->getMaxHp() );
    }
  }
};

EXPOSE_SCRIPT( ActionBenediction140 );