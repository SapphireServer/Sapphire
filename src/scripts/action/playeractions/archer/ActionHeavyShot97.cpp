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

  void onCastFinish( Sapphire::Entity::Chara& source, Sapphire::Action::Action& currentAction ) override
  {
    if( auto player = source.getAsPlayer() )
      player->sendDebug( "cast finished" );
  }

  void onCharaHit( Sapphire::Entity::Chara& sourceActor, Sapphire::Entity::Chara& hitActor,
                   Sapphire::Action::Action& currentAction ) override
  {
    currentAction.damageTarget( 150, hitActor );
  }

};

