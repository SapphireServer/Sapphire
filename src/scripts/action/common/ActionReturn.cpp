#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/Action.h>
#include <Manager/PlayerMgr.h>
#include <Service.h>
#include <Action/CommonAction.h>

using namespace Sapphire;
using namespace Sapphire::World::Action;

class ActionReturn : public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionReturn() : Sapphire::ScriptAPI::ActionScript( Return )
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

EXPOSE_SCRIPT( ActionReturn );