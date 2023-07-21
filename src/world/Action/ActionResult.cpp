#include "ActionResult.h"

#include <Util/Util.h>

#include <Service.h>
#include <Manager/PlayerMgr.h>

#include "Actor/Chara.h"
#include "Actor/Player.h"
#include "StatusEffect/StatusEffect.h"

using namespace Sapphire;
using namespace Sapphire::World::Action;


ActionResult::ActionResult( Entity::CharaPtr target, uint64_t runAfter ) :
  m_target( std::move( target ) ),
  m_delayMs( runAfter )
{
  m_result.Arg0 = 0;
  m_result.Arg1 = 0;
  m_result.Arg2 = 0;
  m_result.Value = 0;
  m_result.Flag = static_cast< uint8_t >( Common::ActionResultFlag::None );
  m_result.Type = Common::ActionEffectType::CALC_RESULT_TYPE_NONE;
}

Entity::CharaPtr ActionResult::getTarget() const
{
  return m_target;
}

uint64_t ActionResult::getDelay()
{
  return m_delayMs;
}

void ActionResult::damage( uint32_t amount, Common::ActionHitSeverityType severity, Common::ActionResultFlag flag )
{
  m_result.Arg0 = static_cast< uint8_t >( severity );
  m_result.Value = static_cast< int16_t >( amount );
  m_result.Flag = static_cast< uint8_t >( flag );
  m_result.Type = Common::ActionEffectType::CALC_RESULT_TYPE_DAMAGE_HP;
}

void ActionResult::heal( uint32_t amount, Common::ActionHitSeverityType severity, Common::ActionResultFlag flag )
{
  m_result.Arg1 = static_cast< uint8_t >( severity );
  m_result.Value = static_cast< int16_t >( amount );
  m_result.Flag = static_cast< uint8_t >( flag );
  m_result.Type = Common::ActionEffectType::CALC_RESULT_TYPE_RECOVER_HP;
}

void ActionResult::restoreMP( uint32_t amount, Common::ActionResultFlag flag )
{
  m_result.Value = static_cast< int16_t >( amount );
  m_result.Flag = static_cast< uint8_t >( flag );
  m_result.Type = Common::ActionEffectType::CALC_RESULT_TYPE_RECOVER_MP;
}

void ActionResult::startCombo( uint16_t actionId )
{
  m_result.Value = static_cast< int16_t >( actionId );
  m_result.Flag = static_cast< uint8_t >( Common::ActionResultFlag::EffectOnSource );
  m_result.Type = Common::ActionEffectType::CALC_RESULT_TYPE_COMBO;
}

void ActionResult::comboSucceed()
{
  // no EffectOnSource flag on this
  m_result.Type = Common::ActionEffectType::CALC_RESULT_TYPE_COMBO_HIT;
}

void ActionResult::applyStatusEffect( uint32_t id, int32_t duration, Entity::Chara& source, uint8_t param, bool shouldOverride )
{
  m_result.Value = static_cast< int16_t >( id );
  m_result.Arg2 = param;
  m_result.Type = Common::ActionEffectType::CALC_RESULT_TYPE_SET_STATUS;

  m_bOverrideStatus = shouldOverride;
  m_pStatus = Sapphire::StatusEffect::make_StatusEffect( id, source.getAsChara(), m_target, duration, 3000 );
  m_pStatus->setParam( param );
}

void ActionResult::applyStatusEffect( uint32_t id, int32_t duration, Entity::Chara& source, uint8_t param,
                                      std::vector< StatusModifier > modifiers, uint32_t flag, bool canApplyMultipleTimes, bool shouldOverride )
{
  m_result.Value = static_cast< int16_t >( id );
  m_result.Arg2 = param;
  m_result.Type = Common::ActionEffectType::CALC_RESULT_TYPE_SET_STATUS;

  m_bOverrideStatus = shouldOverride;
  m_pStatus = Sapphire::StatusEffect::make_StatusEffect( id, source.getAsChara(), m_target, duration, modifiers, flag, 3000, canApplyMultipleTimes );
  m_pStatus->setParam( param );
}

void ActionResult::applyStatusEffectSelf( uint32_t id, int32_t duration, uint8_t param, bool shouldOverride )
{
  m_result.Value = static_cast< int16_t >( id );
  m_result.Arg2 = param;
  m_result.Type = Common::ActionEffectType::CALC_RESULT_TYPE_SET_STATUS_ME;
  m_result.Flag = static_cast< uint8_t >( Common::ActionResultFlag::EffectOnSource );

  m_bOverrideStatus = shouldOverride;
  m_pStatus = Sapphire::StatusEffect::make_StatusEffect( id, m_target, m_target, duration, 3000 );
  m_pStatus->setParam( param );
}

void ActionResult::applyStatusEffectSelf( uint32_t id, int32_t duration, uint8_t param, std::vector< World::Action::StatusModifier > modifiers,
                                          uint32_t flag, bool shouldOverride )
{
  m_result.Value = static_cast< int16_t >( id );
  m_result.Arg2 = param;
  m_result.Type = Common::ActionEffectType::CALC_RESULT_TYPE_SET_STATUS_ME;
  m_result.Flag = static_cast< uint8_t >( Common::ActionResultFlag::EffectOnSource );

  m_bOverrideStatus = shouldOverride;
  m_pStatus = Sapphire::StatusEffect::make_StatusEffect( id, m_target, m_target, duration, modifiers, flag, 3000, false );
  m_pStatus->setParam( param );
}

void ActionResult::mount( uint16_t mountId )
{
  m_result.Value = static_cast< int16_t >( mountId );
  m_result.Arg0 = 1;
  m_result.Type = Common::ActionEffectType::CALC_RESULT_TYPE_MOUNT;
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
    case Common::ActionEffectType::CALC_RESULT_TYPE_DAMAGE_HP:
    {
      m_target->takeDamage( m_result.Value );
      break;
    }

    case Common::ActionEffectType::CALC_RESULT_TYPE_RECOVER_HP:
    {
      m_target->heal( m_result.Value );
      break;
    }

    case Common::ActionEffectType::CALC_RESULT_TYPE_RECOVER_MP:
    {
      m_target->restoreMP( m_result.Value );
      break;
    }

    case Common::ActionEffectType::CALC_RESULT_TYPE_SET_STATUS:
    case Common::ActionEffectType::CALC_RESULT_TYPE_SET_STATUS_ME:
    {
      if( !m_bOverrideStatus )
        m_target->addStatusEffectByIdIfNotExist( m_pStatus );
      else
        m_target->addStatusEffectById( m_pStatus );
      break;
    }

    case Common::ActionEffectType::CALC_RESULT_TYPE_MOUNT:
    {
      auto pPlayer = m_target->getAsPlayer();
      pPlayer->setMount( m_result.Value );
      break;
    }

    default:
      break;
  }
}