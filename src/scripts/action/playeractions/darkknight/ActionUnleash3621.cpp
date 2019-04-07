#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/Action.h>

class ActionUnleash3621 :
  public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionUnleash3621() :
    Sapphire::ScriptAPI::ActionScript( 3621 )
  {
  }

  void onExecute( Sapphire::Action::Action& action ) override
  {
    for( auto& chara : action.getHitCharas() )
    {
      chara->takeDamage( chara->getMaxHp() * 0.34f );
    }
  }
};

EXPOSE_SCRIPT( ActionUnleash3621 );