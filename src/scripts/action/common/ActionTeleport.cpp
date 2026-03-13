#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/Action.h>
#include <Action/CommonAction.h>

using namespace Sapphire;
using namespace Sapphire::World::Action;

class ActionTeleport : public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionTeleport() : Sapphire::ScriptAPI::ActionScript( Teleport )
  {
  }

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto pPlayer = action.getSourceChara()->getAsPlayer();

    if( !pPlayer )
      return;

    auto teleportQuery = pPlayer->getTeleportQuery();

    if( pPlayer->getCurrency( Common::CurrencyType::Gil ) < teleportQuery.cost ||
        teleportQuery.useAetheryteTicket && !pPlayer->removeItem( 7569 ) ||
        teleportQuery.targetAetheryte == 0 )
    {
      action.interrupt();
      return;
    }

    pPlayer->removeCurrency( Common::CurrencyType::Gil, teleportQuery.cost );

    warpMgr().requestPlayerTeleport( *pPlayer, teleportQuery.targetAetheryte, 1 );

    pPlayer->clearTeleportQuery();
  }
};

EXPOSE_SCRIPT( ActionTeleport );