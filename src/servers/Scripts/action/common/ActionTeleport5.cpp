#include <ScriptObject.h>
#include <Actor/Player.h>
#include <Action/Action.h>

class ActionTeleport5 : public ActionScript
{
public:
   ActionTeleport5() : ActionScript( 5 )
   {}

   void onCastStart( Entity::Chara& caster, Entity::Chara& target, Action::Action& action ) override
   {
      auto player = caster.getAsPlayer();
      if( !player )
         return;

      if( player->getTeleportDestination() == 0 )
         action.setInterrupted();
   }

   void onCastFinish( Entity::Chara& caster, Entity::Chara& target, Action::Action& action ) override
   {
      auto player = caster.getAsPlayer();
      if( !player )
         return;

      auto cost = player->getTeleportCost( player->getTeleportDestination() );

      if( player->getCurrency( Common::CurrencyType::Gil ) < cost )
      {
         action.setInterrupted();
         return;
      }

      player->removeCurrency( Common::CurrencyType::Gil, cost );

      player->setZoningType( Common::ZoneingType::Teleport );
      player->teleport( player->getTeleportDestination() );
   }
};