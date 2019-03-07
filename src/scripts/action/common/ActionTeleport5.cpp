#include <Script/NativeScriptApi.h>
#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/Action.h>

using namespace Sapphire;

class ActionTeleport5 :
  public Sapphire::ScriptAPI::ActionScript
{
public:
  ActionTeleport5() :
    Sapphire::ScriptAPI::ActionScript( 5 )
  {
  }

  void onExecute( Sapphire::Action::Action& action ) override
  {
    auto player = action.getSourceChara()->getAsPlayer();

    if( !player )
      return;

    auto teleportQuery = player->getTeleportQuery();

    if( player->getCurrency( Common::CurrencyType::Gil ) < teleportQuery.cost ||
        teleportQuery.targetAetheryte == 0 )
    {
      action.interrupt();
      return;
    }

    player->removeCurrency( Common::CurrencyType::Gil, teleportQuery.cost );

    player->setZoningType( Common::ZoneingType::Teleport );
    player->teleport( teleportQuery.targetAetheryte );

    player->clearTeleportQuery();
  }
};

EXPOSE_SCRIPT( ActionTeleport5 );