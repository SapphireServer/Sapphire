#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/Action.h>
#include <Math/CalcStats.h>

using namespace Sapphire;

class ActionProvoke7533 :
  public ScriptAPI::ActionScript
{
public:
  ActionProvoke7533() :
    ScriptAPI::ActionScript( 7533 )
  {
  }

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto chara = action.getHitChara();
    if( chara )
    {
      chara->onActionHostile( action.getSourceChara() );
      action.getEffectbuilder()->provoke( chara );
    }
  }
};

EXPOSE_SCRIPT( ActionProvoke7533 );