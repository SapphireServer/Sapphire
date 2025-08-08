#include "Bard.h"

#include <Action/CommonAction.h>
#include <Action/Action.h>
#include <Actor/Player.h>
#include <StatusEffect/StatusEffect.h>
#include <stdlib.h>

using namespace Sapphire;
using namespace Sapphire::World::Action;

void Bard::onAction( Entity::Player& player, Action& action )
{
  switch( action.getId() )
  {
    case HeavyShot:
    {
      if( player.getLevel() >= 8 && ( float ) rand() / ( float ) RAND_MAX <= 0.2 )
      {
        auto pActionBuilder = action.getActionResultBuilder();
        if( !pActionBuilder )
          return;

        pActionBuilder->applyStatusEffectSelf( StraightShotReady, 10000, 0, {}, 1025, true );
      }
      break;
    }
  }
}
