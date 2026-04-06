#include "AstralUmbral.h"

#include <Action/CommonAction.h>
#include <Action/ActionResultBuilder.h>
#include <Actor/Chara.h>
#include <StatusEffect/StatusEffect.h>

using namespace Sapphire;
using namespace Sapphire::World::Action;

static constexpr uint32_t AstralFireDuration = 12000;
static constexpr uint32_t UmbralIceDuration  = 12000;
static constexpr uint32_t Flags = static_cast< uint32_t >( Common::StatusEffectFlag::BuffCategory );

static constexpr uint8_t MagickAndMendLevel = 20;
static constexpr uint8_t MagickAndMend2Level = 40;

Sapphire::StatusEffect::StatusEffectPtr THM::getAstralFire( Entity::CharaPtr& pSource )
{
  if( auto pStatus = pSource->getStatusEffectById( ActionStatus::AstralFireStatus ) )
  {
    return pStatus;
  }
  if( auto pStatus = pSource->getStatusEffectById( ActionStatus::AstralFireIIStatus ) )
  {
    return pStatus;
  }
  return pSource->getStatusEffectById( ActionStatus::AstralFireIIIStatus );
}
Sapphire::StatusEffect::StatusEffectPtr THM::getUmbralIce( Entity::CharaPtr& pSource )
{
  if( auto pStatus = pSource->getStatusEffectById( ActionStatus::UmbralIceStatus ) )
  {
    return pStatus;
  }
  if( auto pStatus = pSource->getStatusEffectById( ActionStatus::UmbralIceIIStatus ) )
  {
    return pStatus;
  }
  return pSource->getStatusEffectById( ActionStatus::UmbralIceIIIStatus );
}

void THM::applyAstralFire( Entity::CharaPtr& pSource, ActionResultBuilderPtr& pBuilder )
{
  auto pStatus = getAstralFire( pSource );
  if( auto pUmbral = getUmbralIce( pSource ) )
  {
    pSource->removeSingleStatusEffectById( pUmbral->getId() );
  }
  else
  {
    if( !pStatus )
    {
      pBuilder->applyStatusEffectSelf( ActionStatus::AstralFireStatus, AstralFireDuration, 0, {}, Flags, true );
    }
    else
    {
      const auto level = pSource->getLevel();
      const auto currentStatus = pStatus->getId();

      ActionStatus newStatus = ActionStatus::AstralFireStatus;
      if( currentStatus == ActionStatus::AstralFireStatus )
      {
        newStatus = ( level >= MagickAndMendLevel ) ? ActionStatus::AstralFireIIStatus : ActionStatus::AstralFireStatus;
      }
      else if( currentStatus == ActionStatus::AstralFireIIStatus || currentStatus == ActionStatus::AstralFireIIIStatus )
      {
        if( level >= MagickAndMend2Level )
        {
          newStatus = ActionStatus::AstralFireIIIStatus;
        }
        else if( level >= MagickAndMendLevel )
        {
          newStatus = ActionStatus::AstralFireIIStatus;
        }
      }

      pBuilder->replaceStatusEffectSelf( pStatus, newStatus, AstralFireDuration, 0, {}, Flags );
    }
  }
}

void THM::applyUmbralIce( Entity::CharaPtr& pSource, ActionResultBuilderPtr& pBuilder )
{
  auto pStatus = getUmbralIce( pSource );
  if( auto pAstral = getAstralFire( pSource ) )
  {
    pSource->removeSingleStatusEffectById( pAstral->getId() );
  }
  else
  {
    if( !pStatus )
    {
      pBuilder->applyStatusEffectSelf( ActionStatus::UmbralIceStatus, UmbralIceDuration, 0, {}, Flags, true );
    }
    else
    {
      const auto level = pSource->getLevel();
      const auto currentStatus = pStatus->getId();

      ActionStatus newStatus = ActionStatus::UmbralIceStatus;
      if( currentStatus == ActionStatus::UmbralIceStatus )
      {
        newStatus = ( level >= MagickAndMendLevel ) ? ActionStatus::UmbralIceIIStatus : ActionStatus::UmbralIceStatus;
      }
      else if( currentStatus == ActionStatus::UmbralIceIIStatus || currentStatus == ActionStatus::UmbralIceIIIStatus )
      {
        if( level >= MagickAndMend2Level )
        {
          newStatus = ActionStatus::UmbralIceIIIStatus;
        }
        else if( level >= MagickAndMendLevel )
        {
          newStatus = ActionStatus::UmbralIceIIStatus;
        }
      }

      pBuilder->replaceStatusEffectSelf( pStatus, newStatus, UmbralIceDuration, 0, {}, Flags );
    }
  }
}

void THM::setAstralFire( Entity::CharaPtr& pSource, ActionResultBuilderPtr& pBuilder, uint8_t tier )
{
  auto pStatus = getAstralFire( pSource );
  if( !pStatus )
  {
    pStatus = getUmbralIce( pSource );
  }
  const auto level = pSource->getLevel();
  const uint8_t highestTier = ( level >= MagickAndMend2Level ) ? 3 : ( ( level >= MagickAndMendLevel ) ? 2 : 1 );
  const uint8_t clampedTier = ( tier > highestTier ) ? highestTier : tier;

  ActionStatus newStatus = ActionStatus::AstralFireStatus;
  switch( clampedTier )
  {
    case 1:
      newStatus = ActionStatus::AstralFireStatus;
      break;
    case 2:
      newStatus = ActionStatus::AstralFireIIStatus;
      break;
    case 3:
      newStatus = ActionStatus::AstralFireIIIStatus;
      break;
    default:
      newStatus = ActionStatus::AstralFireStatus;
      break;
  }
  if( pStatus )
  {
    pBuilder->replaceStatusEffectSelf( pStatus, newStatus, AstralFireDuration, 0, {}, Flags );
  }
  else
  {
    pBuilder->applyStatusEffectSelf( newStatus, AstralFireDuration, 0, {}, Flags, true );
  }
}

void THM::setUmbralIce( Entity::CharaPtr& pSource, ActionResultBuilderPtr& pBuilder, uint8_t tier )
{
  auto pStatus = getUmbralIce( pSource );
  if( !pStatus )
  {
    pStatus = getAstralFire( pSource );
  }
  const auto level = pSource->getLevel();
  const uint8_t highestTier = ( level >= MagickAndMend2Level ) ? 3 : ( ( level >= MagickAndMendLevel ) ? 2 : 1 );
  const uint8_t clampedTier = ( tier > highestTier ) ? highestTier : tier;

  ActionStatus newStatus = ActionStatus::UmbralIceStatus;
  switch( clampedTier )
  {
    case 1:
      newStatus = ActionStatus::UmbralIceStatus;
      break;
    case 2:
      newStatus = ActionStatus::UmbralIceIIStatus;
      break;
    case 3:
      newStatus = ActionStatus::UmbralIceIIIStatus;
      break;
    default:
      newStatus = ActionStatus::UmbralIceStatus;
      break;
  }
  if( pStatus )
  {
    pBuilder->replaceStatusEffectSelf( pStatus, newStatus, UmbralIceDuration, 0, {}, Flags );
  }
  else
  {
    pBuilder->applyStatusEffectSelf( newStatus, UmbralIceDuration, 0, {}, Flags, true );
  }
}

