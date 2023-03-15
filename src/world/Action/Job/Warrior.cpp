#include "Warrior.h"

#include <Action/CommonAction.h>
#include <Action/Action.h>
#include <Actor/Player.h>

using namespace Sapphire;
using namespace Sapphire::World::Action;

void Warrior::onAction( Entity::Player& player, Action& action )
{
  switch( action.getId() )
  {
    case Maim:
    case StormsEye:
    case StormsPath:
    case SkullSunder:
    case ButchersBlock:
    {
      if( action.isComboAction() && !action.isCorrectCombo() )
        break;

      if( player.hasStatusEffect( Defiance ) )
        handleWrath( player, action );
      break;
    }
  }
}

void Warrior::handleWrath( Entity::Player& player, Action& action )
{
  auto effectToApply = Wrath;
  auto parry = 2;
  auto asChara = player.getAsChara();

  if( player.hasStatusEffect( Wrath ) )
  {
    player.replaceSingleStatusEffectById( Wrath );
    effectToApply = WrathII;
    parry += 2;
  }
  else if( player.hasStatusEffect( WrathII ) )
  {
    player.replaceSingleStatusEffectById( WrathII );
    effectToApply = WrathIII;
    parry += 2;
  }
  else if( player.hasStatusEffect( WrathIII ) )
  {
    player.replaceSingleStatusEffectById( WrathIII );
    effectToApply = WrathIV;
    parry += 2;
  }
  else if( player.hasStatusEffect( WrathIV ) )
  {
    player.replaceSingleStatusEffectById( WrathIV );
    effectToApply = Infuriated;
    parry += 2;
  }

  if( !player.hasStatusEffect( Infuriated ) )
  {
    action.getActionResultBuilder()->applyStatusEffectSelf( effectToApply, 30000, 0, { StatusModifier{ Common::ParamModifier::ParryPercent, parry } }, 0, false );
  }
}