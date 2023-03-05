#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/Action.h>
#include <Manager/PlayerMgr.h>
#include <Service.h>

class ActionReturn6 : public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionReturn6() : Sapphire::ScriptAPI::ActionScript( 6 )
  {
  }

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    if( !action.getSourceChara()->isPlayer() )
      return;

    auto pPlayer = action.getSourceChara()->getAsPlayer();

    warpMgr().requestPlayerTeleport( *pPlayer, pPlayer->getHomepoint(), 3 );
  }
};

EXPOSE_SCRIPT( ActionReturn6 );