#include "Warrior.h"

#include <Action/CommonAction.h>
#include <Action/Action.h>
#include <Actor/Player.h>
#include <StatusEffect/StatusEffect.h>

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
  Sapphire::StatusEffect::StatusEffectPtr oldStatus = nullptr;
  auto effectToApply = Wrath;
  auto parry = 2;
  auto asChara = player.getAsChara();

  auto pActionBuilder = action.getActionResultBuilder();
    
  if( !pActionBuilder )
    return;

  auto statusMap = player.getStatusEffectMap();

  for( const auto& effectIt : statusMap )
  {
    if( effectIt.second->getId() == Wrath )
    {
      oldStatus = effectIt.second;
      effectToApply = WrathII;
      parry = 4;
      break;
    }
    else if( effectIt.second->getId() == WrathII )
    {
      oldStatus = effectIt.second;
      effectToApply = WrathIII;
      parry = 6;      
      break;
    }
    else if( effectIt.second->getId() == WrathIII )
    {
      oldStatus = effectIt.second;
      effectToApply = WrathIV;
      parry = 8;      
      break;
    }
    else if( effectIt.second->getId() == WrathIV )
    {
      oldStatus = effectIt.second;
      effectToApply = Infuriated;
      parry = 10;     
      break;
    }
  }

  if( !player.hasStatusEffect( Infuriated ) )
  {
    if( oldStatus )
      pActionBuilder->replaceStatusEffectSelf( oldStatus, effectToApply, 30000, 0, { StatusModifier{ Common::ParamModifier::ParryPercent, parry } } );
    else
      pActionBuilder->applyStatusEffectSelf( effectToApply, 30000, 0, { StatusModifier{ Common::ParamModifier::ParryPercent, parry } } );
  }
}