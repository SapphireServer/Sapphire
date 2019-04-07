#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/Action.h>

class ActionAbyssalDrain3641 :
  public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionAbyssalDrain3641() :
    Sapphire::ScriptAPI::ActionScript( 3641 )
  {
  }

  void onExecute( Sapphire::Action::Action& action ) override
  {
    for( auto& chara : action.getHitCharas() )
    {
      chara->takeDamage( chara->getMaxHp() * 0.5f );
    }
  }
};

EXPOSE_SCRIPT( ActionAbyssalDrain3641 );