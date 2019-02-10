#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/Action.h>

class ActionHeavyShot97 :
  public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionHeavyShot97() :
    Sapphire::ScriptAPI::ActionScript( 97 )
  {
  }

  void onCastFinish( Sapphire::Action::Action& currentAction ) override
  {
    auto source = currentAction.getSourceChara();
    if( auto player = source->getAsPlayer() )
      player->sendDebug( "cast finished" );
  }

  void onCharaHit( Sapphire::Action::Action& currentAction, Sapphire::Entity::Chara& hitActor ) override
  {
    currentAction.damageTarget( 150, hitActor );
  }

};

