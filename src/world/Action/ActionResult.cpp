#include "ActionResult.h"

#include <Util/Util.h>
#include <Math/CalcStats.h>

#include <Service.h>
#include <Manager/PlayerMgr.h>

#include "Actor/Chara.h"
#include "Actor/Player.h"
#include "StatusEffect/StatusEffect.h"

#include "Network/Util/PacketUtil.h"

#include "Script/ScriptMgr.h"

using namespace Sapphire;
using namespace Sapphire::Common;
using namespace Sapphire::World::Action;


ActionResult::ActionResult( Entity::CharaPtr source, Entity::CharaPtr target ) :
  m_target( std::move( target ) ), m_source( std::move( source ) )
{
  m_result.Arg0 = 0;
  m_result.Arg1 = 0;
  m_result.Arg2 = 0;
  m_result.Value = 0;
  m_result.Flag = static_cast< uint8_t >( ActionResultFlag::None );
  m_result.Type = CalcResultType::TypeNone;

  m_aggroModifier = 1;
}

Entity::CharaPtr ActionResult::getTarget() const
{
  return m_target;
}

void ActionResult::damage( uint32_t amount, CalcResultType hitType, uint8_t hitEffect, ActionResultFlag flag, float aggroModifier )
{
  m_result.Arg0 = hitEffect;
  m_result.Value = static_cast< int16_t >( amount );
  m_result.Flag = static_cast< uint8_t >( flag );
  m_result.Type = hitType;
  m_aggroModifier = aggroModifier;
}

void ActionResult::heal( uint32_t amount, CalcResultType hitType, uint8_t hitEffect, ActionResultFlag flag, float aggroModifier )
{
  m_result.Arg0 = hitEffect;
  m_result.Value = static_cast< int16_t >( amount );
  m_result.Flag = static_cast< uint8_t >( flag );
  m_result.Type = hitType;
  m_aggroModifier = aggroModifier;
}

void ActionResult::restoreMP( uint32_t amount, ActionResultFlag flag )
{
  m_result.Value = static_cast< int16_t >( amount );
  m_result.Flag = static_cast< uint8_t >( flag );
  m_result.Type = CalcResultType::TypeRecoverMp;
}

void ActionResult::startCombo( uint16_t actionId )
{
  m_result.Value = static_cast< int16_t >( actionId );
  m_result.Flag = static_cast< uint8_t >( ActionResultFlag::EffectOnSource );
  m_result.Type = CalcResultType::TypeCombo;
}

void ActionResult::comboSucceed()
{
  // no EffectOnSource flag on this
  m_result.Type = CalcResultType::TypeComboHit;
}

void ActionResult::applyStatusEffect( uint32_t id, int32_t duration, Entity::Chara& source, uint8_t param, bool applyAggro, bool shouldOverride )
{
  m_result.Value = static_cast< int16_t >( id );
  m_result.Arg2 = param;
  m_result.Type = CalcResultType::TypeSetStatus;

  m_bShouldOverride = shouldOverride;
  m_pStatus = Sapphire::StatusEffect::make_StatusEffect( id, source.getAsChara(), m_target, duration, 3000 );
  m_pStatus->setParam( param );

  m_applyStatusAggro = applyAggro;
}

void ActionResult::applyStatusEffect( uint32_t id, int32_t duration, Entity::Chara& source, uint8_t param, const std::vector< StatusModifier >& modifiers,
                                      uint32_t flag, bool statusToSource, bool applyAggro, bool shouldOverride, const World::Action::GroundAOE& groundAOE )
{
  m_result.Value = static_cast< int16_t >( id );
  m_result.Arg2 = param;
  m_result.Type = statusToSource ? CalcResultType::TypeSetStatusMe : CalcResultType::TypeSetStatus;
  if( statusToSource )
    m_result.Flag = static_cast< uint8_t >( ActionResultFlag::EffectOnSource );

  m_bShouldOverride = shouldOverride;
  m_pStatus = Sapphire::StatusEffect::make_StatusEffect( id, source.getAsChara(), m_target, duration, modifiers, groundAOE, flag, 3000 );
  m_pStatus->setParam( param );

  m_applyStatusAggro = applyAggro;
}

void ActionResult::applyStatusEffectSelf( uint32_t id, int32_t duration, uint8_t param, bool applyAggro, bool shouldOverride )
{
  m_result.Value = static_cast< int16_t >( id );
  m_result.Arg2 = param;
  m_result.Type = CalcResultType::TypeSetStatusMe;
  m_result.Flag = static_cast< uint8_t >( ActionResultFlag::EffectOnSource );

  m_bShouldOverride = shouldOverride;
  m_pStatus = Sapphire::StatusEffect::make_StatusEffect( id, m_target, m_target, duration, 3000 );
  m_pStatus->setParam( param );

  m_applyStatusAggro = applyAggro;
}

void ActionResult::applyStatusEffectSelf( uint32_t id, int32_t duration, uint8_t param, const std::vector< World::Action::StatusModifier >& modifiers,
                                          uint32_t flag, bool applyAggro, bool shouldOverride, const World::Action::GroundAOE& groundAOE )
{
  m_result.Value = static_cast< int16_t >( id );
  m_result.Arg2 = param;
  m_result.Type = CalcResultType::TypeSetStatusMe;
  m_result.Flag = static_cast< uint8_t >( Common::ActionResultFlag::EffectOnSource );

  m_bShouldOverride = shouldOverride;
  m_pStatus = Sapphire::StatusEffect::make_StatusEffect( id, m_target, m_target, duration, modifiers, groundAOE, flag, 3000 );
  m_pStatus->setParam( param );

  m_applyStatusAggro = applyAggro;
}

void ActionResult::replaceStatusEffect( Sapphire::StatusEffect::StatusEffectPtr& pOldStatus, uint32_t id, int32_t duration, Entity::Chara& source, uint8_t param,
                                        const std::vector< StatusModifier >& modifiers, uint32_t flag, bool statusToSource, bool applyAggro, const World::Action::GroundAOE& groundAOE )
{
  applyStatusEffect( id, duration, source, param, modifiers, flag, statusToSource, applyAggro, false, groundAOE );
  m_pOldStatus = std::move( pOldStatus );
  m_pStatus->setSlot( m_pOldStatus->getSlot() );
}

void ActionResult::replaceStatusEffectSelf( Sapphire::StatusEffect::StatusEffectPtr& pOldStatus, uint32_t id, int32_t duration, uint8_t param,
                                            const std::vector< World::Action::StatusModifier >& modifiers, uint32_t flag, bool applyAggro, const World::Action::GroundAOE& groundAOE )
{
  applyStatusEffectSelf( id, duration, param, modifiers, flag, applyAggro, false, groundAOE );
  m_pOldStatus = std::move( pOldStatus );
  m_pStatus->setSlot( m_pOldStatus->getSlot() );
}

void ActionResult::mount( uint16_t mountId )
{
  m_result.Value = static_cast< int16_t >( mountId );
  m_result.Arg0 = 1;
  m_result.Type = CalcResultType::TypeMount;
}

const Common::CalcResultParam& ActionResult::getCalcResultParam() const
{
  return m_result;
}

const Sapphire::StatusEffect::StatusEffectPtr ActionResult::getStatusEffect() const
{
  return m_pStatus;
}

void ActionResult::execute()
{
  if( !m_target )
    return;

  switch( m_result.Type )
  {
    case CalcResultType::TypeDamageHp:
    case CalcResultType::TypeCriticalDamageHp:
    {
      auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();
      auto statusEffects( m_target->getStatusEffectMap() );
      for( auto& status : statusEffects )
      {
        scriptMgr.onPlayerHit( m_target, *status.second );
      }

      m_target->takeDamage( m_result.Value, false );
      int32_t aggro = Sapphire::Math::CalcStats::calcAggro( *m_source, m_result.Value, m_aggroModifier );
      m_target->onActionHostile( m_source, aggro );
      break;
    }

    case CalcResultType::TypeRecoverHp:
    case CalcResultType::TypeCriticalRecoverHp:
    {
      m_target->heal( m_result.Value, false );

      if( m_aggroModifier != 0 )
      {
        int32_t aggro = Sapphire::Math::CalcStats::calcAggro( *m_source, m_result.Value, m_aggroModifier );
        splitAggroApplication( aggro );
      }
      break;
    }

    case CalcResultType::TypeRecoverMp:
    {
      m_target->restoreMP( m_result.Value );
      break;
    }

    case CalcResultType::TypeSetStatus:
    case CalcResultType::TypeSetStatusMe:
    {
      if( m_bShouldOverride )
      {
        for( auto const& entry : m_target->getStatusEffectMap() )
        {
          auto statusEffect = entry.second;
          if( statusEffect->getId() == m_result.Value && statusEffect->getSrcActorId() == m_pStatus->getSrcActorId() )
          {
            statusEffect->refresh( m_pStatus->getDuration() );
            m_pStatus->setSlot( statusEffect->getSlot() );

            Network::Util::Packet::sendHudParam( *m_target );

            if( m_applyStatusAggro )
            {
              auto aggro = Sapphire::Math::CalcStats::calcStatusAggro( *m_source );
              if( m_pStatus->getFlag() & static_cast< uint8_t >( StatusEffectFlag::BuffCategory ) )
              {
                splitAggroApplication( aggro );
              }
              else if( m_pStatus->getFlag() & static_cast< uint8_t >( StatusEffectFlag::DebuffCategory ) )
              {
                m_target->onActionHostile( m_source, aggro );
              }
            }
            return;
          }
        }
      }

      if( m_pOldStatus )
        m_target->replaceSingleStatusEffect( m_pOldStatus->getSlot(), m_pStatus );
      else if( !m_bShouldOverride )
        m_target->addStatusEffectByIdIfNotExist( m_pStatus );
      else
        m_target->addStatusEffectById( m_pStatus );

      if( m_applyStatusAggro )
      {
        auto aggro = Sapphire::Math::CalcStats::calcStatusAggro( *m_source );
        if( m_pStatus->getFlag() & static_cast< uint8_t >( StatusEffectFlag::BuffCategory ) )
        {
          splitAggroApplication( aggro );
        }
        else if( m_pStatus->getFlag() & static_cast< uint8_t >( StatusEffectFlag::DebuffCategory ) )
        {
          m_target->onActionHostile( m_source, aggro );
        }
      }
      break;
    }

    case CalcResultType::TypeMount:
    {
      auto pPlayer = m_target->getAsPlayer();
      pPlayer->setMount( m_result.Value );
      break;
    }

    default:
      break;
  }
}

void ActionResult::splitAggroApplication( float aggro )
{
  auto hateList = m_target->getHateList();
  aggro = aggro / hateList.size();
  for( auto entry : hateList )
  {
    if( entry && entry->isAlive() )
    {
      entry->onActionHostile( m_source, aggro );
    }
  }
}
