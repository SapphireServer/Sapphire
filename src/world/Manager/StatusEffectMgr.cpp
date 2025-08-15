#include "StatusEffectMgr.h"

#include "Actor/Chara.h"
#include "StatusEffect/StatusEffect.h"

#include "Network/Util/PacketUtil.h"
#include <Network/CommonActorControl.h>

#include <Math/CalcStats.h>
#include <Util/Util.h>

using namespace Sapphire;
using namespace Sapphire::World::Manager;


void StatusEffectMgr::damage( Entity::CharaPtr pSource, Entity::CharaPtr pTarget, uint32_t amount )
{
  pTarget->takeDamage( amount );
  int32_t aggro = Sapphire::Math::CalcStats::calcAggro( *pSource, amount, 1.0f );
  pTarget->onActionHostile( pSource, aggro );

  Network::Util::Packet::sendActorControl( pTarget->getInRangePlayerIds( pTarget->isPlayer() ), pTarget->getId(), Network::ActorControl::ActorControlType::HPFloatingText, 0,
                                           Common::CalcResultType::TypeDamageHp, amount );
  Network::Util::Packet::sendHudParam( *pTarget );
}

void StatusEffectMgr::heal( Entity::CharaPtr pSource, Entity::CharaPtr pTarget, uint32_t amount )
{
  pTarget->heal( amount );
  Network::Util::Packet::sendActorControl( pTarget->getInRangePlayerIds( pTarget->isPlayer() ), pTarget->getId(), Network::ActorControl::ActorControlType::HPFloatingText, 0,
                                           Common::CalcResultType::TypeRecoverHp, amount );
  Network::Util::Packet::sendHudParam( *pTarget );

  int32_t aggro = Sapphire::Math::CalcStats::calcAggro( *pSource, amount, 0.5f );
  auto hateList = pTarget->getHateList();

  if( !hateList.empty() )
    aggro = aggro / hateList.size();

  for( auto entry : hateList )
  {
    entry->onActionHostile( pSource, aggro );
  }
}

void StatusEffectMgr::restoreMP( Entity::CharaPtr pTarget, uint32_t amount )
{
  pTarget->restoreMP( amount );
}

void StatusEffectMgr::applyStatusEffect( Entity::CharaPtr pSource, Entity::CharaPtr pTarget, uint32_t id, int32_t duration, uint8_t param,
                        const std::vector< World::Action::StatusModifier >& modifiers, uint32_t flag, bool shouldOverride )
{
  auto pStatus = Sapphire::StatusEffect::make_StatusEffect( id, pSource, pTarget, duration, modifiers, flag, 3000 );
  pStatus->setParam( param );

  applyStatusEffect( pTarget, pStatus, shouldOverride );
}

void StatusEffectMgr::applyStatusEffectSelf( Entity::CharaPtr pSource, uint32_t id, int32_t duration, uint8_t param,
                            const std::vector< World::Action::StatusModifier >& modifiers, uint32_t flag, bool shouldOverride )
{
  auto pStatus = Sapphire::StatusEffect::make_StatusEffect( id, pSource, pSource, duration, modifiers, flag, 3000 );
  pStatus->setParam( param );

  applyStatusEffect( pSource, pStatus, shouldOverride );
}

void StatusEffectMgr::replaceStatusEffect( Entity::CharaPtr pSource, Entity::CharaPtr pTarget, Sapphire::StatusEffect::StatusEffectPtr& pOldStatus, uint32_t id,
                          int32_t duration, uint8_t param, const std::vector< World::Action::StatusModifier >& modifiers, uint32_t flag )
{
  auto pStatus = Sapphire::StatusEffect::make_StatusEffect( id, pSource, pTarget, duration, modifiers, flag, 3000 );
  pStatus->setParam( param );

  replaceStatusEffect( pTarget, pOldStatus, pStatus );
}

void StatusEffectMgr::replaceStatusEffectSelf( Entity::CharaPtr pSource, Sapphire::StatusEffect::StatusEffectPtr& pOldStatus, uint32_t id,
                              int32_t duration, uint8_t param, const std::vector< World::Action::StatusModifier >& modifiers, uint32_t flag )
{
  auto pStatus = Sapphire::StatusEffect::make_StatusEffect( id, pSource, pSource, duration, modifiers, flag, 3000 );
  pStatus->setParam( param );

  replaceStatusEffect( pSource, pOldStatus, pStatus );
}

void StatusEffectMgr::applyStatusEffect( Entity::CharaPtr pTarget, Sapphire::StatusEffect::StatusEffectPtr& pStatus, bool shouldOverride )
{
  uint32_t statusId = pStatus->getId();
  Entity::CharaPtr pSource = pStatus->getSrcActor();

  if( shouldOverride )
  {
    for( auto const& entry : pTarget->getStatusEffectMap() )
    {
      auto statusEffect = entry.second;
      if( statusEffect->getId() == statusId && statusEffect->getSrcActorId() == pStatus->getSrcActorId() )
      {
        statusEffect->refresh( pStatus->getDuration() );
        pStatus->setSlot( statusEffect->getSlot() );

        Network::Util::Packet::sendHudParam( *pTarget );

        auto aggro = Sapphire::Math::CalcStats::calcStatusAggro( *pSource );
        if( pStatus->getFlag() & static_cast< uint8_t >( Common::StatusEffectFlag::BuffCategory ) )
        {
          splitAggroApplication( pSource, pTarget, aggro );
        }
        else if( pStatus->getFlag() & static_cast< uint8_t >( Common::StatusEffectFlag::DebuffCategory ) )
        {
          pTarget->onActionHostile( pSource, aggro );
        }
        return;
      }
    }
  }

  if( !shouldOverride )
    pTarget->addStatusEffectByIdIfNotExist( pStatus );
  else
    pTarget->addStatusEffectById( pStatus );

  Network::Util::Packet::sendHudParam( *pTarget );

  auto aggro = Sapphire::Math::CalcStats::calcStatusAggro( *pSource );
  if( pStatus->getFlag() & static_cast< uint8_t >( Common::StatusEffectFlag::BuffCategory ) )
  {
    splitAggroApplication( pSource, pTarget, aggro );
  }
  else if( pStatus->getFlag() & static_cast< uint8_t >( Common::StatusEffectFlag::DebuffCategory ) )
  {
    pTarget->onActionHostile( pSource, aggro );
  }
}

void StatusEffectMgr::replaceStatusEffect( Entity::CharaPtr pTarget, Sapphire::StatusEffect::StatusEffectPtr& pOldStatus, Sapphire::StatusEffect::StatusEffectPtr& pNewStatus )
{
  Entity::CharaPtr pSource = pNewStatus->getSrcActor();
  pTarget->replaceSingleStatusEffect( pOldStatus->getSlot(), pNewStatus );

  auto aggro = Sapphire::Math::CalcStats::calcStatusAggro( *pSource );
  if( pNewStatus->getFlag() & static_cast< uint8_t >( Common::StatusEffectFlag::BuffCategory ) )
  {
    splitAggroApplication( pSource, pTarget, aggro );
  }
  else if( pNewStatus->getFlag() & static_cast< uint8_t >( Common::StatusEffectFlag::DebuffCategory ) )
  {
    pTarget->onActionHostile( pSource, aggro );
  }
}

void StatusEffectMgr::splitAggroApplication( Entity::CharaPtr pSource, Entity::CharaPtr pTarget, float aggro )
{
  auto hateList = pTarget->getHateList();

  if( !hateList.empty() )
    aggro = aggro / hateList.size();

  for( auto entry : hateList )
  {
    entry->onActionHostile( pSource, aggro );
  }
}