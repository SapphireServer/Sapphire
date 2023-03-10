#include "ActionResult.h"

#include <Util/Util.h>

#include <Service.h>
#include <Manager/PlayerMgr.h>

#include "Actor/Chara.h"
#include "Actor/Player.h"

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

void ActionResult::applyStatusEffect( uint16_t statusId, uint8_t param )
{
  m_result.Value = static_cast< int16_t >( statusId );
  m_result.Arg2 = param;
  m_result.Type = Common::ActionEffectType::CALC_RESULT_TYPE_SET_STATUS;
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