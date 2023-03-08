#include "EffectResult.h"

#include <Util/Util.h>

#include <Service.h>
#include <Manager/PlayerMgr.h>

#include "Actor/Chara.h"
#include "Actor/Player.h"

using namespace Sapphire;
using namespace Sapphire::World::Action;


EffectResult::EffectResult( Entity::CharaPtr target, uint64_t runAfter ) :
  m_target( std::move( target ) ),
  m_delayMs( runAfter )
{
  m_result.Arg0 = 0;
  m_result.Arg1 = 0;
  m_result.Arg2 = 0;
  m_result.Value = 0;
  m_result.Flag = static_cast< uint8_t >( Common::ActionEffectResultFlag::None );
  m_result.Type = Common::ActionEffectType::CALC_RESULT_TYPE_NONE;
}

Entity::CharaPtr EffectResult::getTarget() const
{
  return m_target;
}

uint64_t EffectResult::getDelay()
{
  return m_delayMs;
}

void EffectResult::damage( uint32_t amount, Common::ActionHitSeverityType severity, Common::ActionEffectResultFlag flag )
{
  m_result.Arg0 = static_cast< uint8_t >( severity );
  m_result.Value = static_cast< int16_t >( amount );
  m_result.Flag = static_cast< uint8_t >( flag );
  m_result.Type = Common::ActionEffectType::CALC_RESULT_TYPE_DAMAGE_HP;
}

void EffectResult::heal( uint32_t amount, Common::ActionHitSeverityType severity, Common::ActionEffectResultFlag flag )
{
  m_result.Arg1 = static_cast< uint8_t >( severity );
  m_result.Value = static_cast< int16_t >( amount );
  m_result.Flag = static_cast< uint8_t >( flag );
  m_result.Type = Common::ActionEffectType::CALC_RESULT_TYPE_RECOVER_HP;
}

void EffectResult::restoreMP( uint32_t amount, Common::ActionEffectResultFlag flag )
{
  m_result.Value = static_cast< int16_t >( amount );
  m_result.Flag = static_cast< uint8_t >( flag );
  m_result.Type = Common::ActionEffectType::CALC_RESULT_TYPE_RECOVER_MP;
}

void EffectResult::startCombo( uint16_t actionId )
{
  m_result.Value = static_cast< int16_t >( actionId );
  m_result.Flag = static_cast< uint8_t >( Common::ActionEffectResultFlag::EffectOnSource );
  m_result.Type = Common::ActionEffectType::CALC_RESULT_TYPE_COMBO;
}

void EffectResult::comboSucceed()
{
  // no EffectOnSource flag on this
  m_result.Type = Common::ActionEffectType::CALC_RESULT_TYPE_COMBO_HIT;
}

void EffectResult::applyStatusEffect( uint16_t statusId, uint8_t param, bool forSelf )
{
  m_result.Value = static_cast< int16_t >( statusId );
  m_result.Arg2 = param;
  if( forSelf )
    m_result.Flag = static_cast< uint8_t >( Common::ActionEffectResultFlag::EffectOnSource );
  m_result.Type = forSelf ? Common::ActionEffectType::CALC_RESULT_TYPE_SET_STATUS_ME : Common::ActionEffectType::CALC_RESULT_TYPE_SET_STATUS;
}

void EffectResult::mount( uint16_t mountId )
{
  m_result.Value = static_cast< int16_t >( mountId );
  m_result.Arg0 = 1;
  m_result.Type = Common::ActionEffectType::CALC_RESULT_TYPE_MOUNT;
}

const Common::CalcResultParam& EffectResult::getCalcResultParam() const
{
  return m_result;
}

void EffectResult::execute()
{
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