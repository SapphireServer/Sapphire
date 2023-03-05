#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/Action.h>

using namespace Sapphire;

class ActionTeleport5 : public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionTeleport5() : Sapphire::ScriptAPI::ActionScript( 5 )
  {
  }

  void onExecute( Sapphire::World::Action::Action& action ) override
  {
    auto pPlayer = action.getSourceChara()->getAsPlayer();

    if( !pPlayer )
      return;

    auto teleportQuery = pPlayer->getTeleportQuery();

    if( pPlayer->getCurrency( Common::CurrencyType::Gil ) < teleportQuery.cost ||
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

EXPOSE_SCRIPT( ActionTeleport5 );