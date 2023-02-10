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
  m_delayMs( runAfter ),
  m_value( 0 ),
  m_param0( 0 ),
  m_param1( 0 ),
  m_type( Common::ActionEffectType::CALC_RESULT_TYPE_NONE ),
  m_param2( 0 ),
  m_flag( Common::ActionEffectResultFlag::None )
{

}

Entity::CharaPtr EffectResult::getTarget() const
{
  return m_target;
}

uint32_t EffectResult::getValue() const
{
  return m_value;
}

uint64_t EffectResult::getDelay()
{
  return m_delayMs;
}

void EffectResult::damage( uint32_t amount, Common::ActionHitSeverityType severity, Common::ActionEffectResultFlag flag )
{
  m_param0 = static_cast< uint8_t >( severity );
  m_value = amount;
  m_flag = flag;

  m_type = Common::ActionEffectType::CALC_RESULT_TYPE_DAMAGE_HP;
}

void EffectResult::heal( uint32_t amount, Common::ActionHitSeverityType severity, Common::ActionEffectResultFlag flag )
{
  m_param1 = static_cast< uint8_t >( severity );
  m_value = amount;
  m_flag = flag;

  m_type = Common::ActionEffectType::CALC_RESULT_TYPE_RECOVER_HP;
}

void EffectResult::restoreMP( uint32_t amount, Common::ActionEffectResultFlag flag )
{
  m_value = amount;
  m_flag = flag;

  m_type = Common::ActionEffectType::CALC_RESULT_TYPE_RECOVER_MP;
}

void EffectResult::startCombo( uint16_t actionId )
{
  m_value = actionId;
  m_flag = Common::ActionEffectResultFlag::EffectOnSource;

  m_type = Common::ActionEffectType::CALC_RESULT_TYPE_COMBO;
}

void EffectResult::comboSucceed()
{
  // no EffectOnSource flag on this
  m_type = Common::ActionEffectType::CALC_RESULT_TYPE_COMBO_HIT;
}

void EffectResult::applyStatusEffect( uint16_t statusId, uint8_t param )
{
  m_value = statusId;
  m_param2 = param;

  m_type = Common::ActionEffectType::CALC_RESULT_TYPE_SET_STATUS;
}

void EffectResult::mount( uint16_t mountId )
{
  m_value = mountId;
  m_param0 = 1;

  m_type = Common::ActionEffectType::CALC_RESULT_TYPE_MOUNT;
}

Common::CalcResultParam EffectResult::buildEffectEntry() const
{
  Common::CalcResultParam entry{};

  // todo: that retarded shit so > u16 max numbers work
  entry.Value = getValue();
  entry.Arg0 = m_param0;
  entry.Arg1 = m_param1;
  entry.Type = m_type;
  entry.Arg2 = m_param2;
  entry.Flag = static_cast< uint8_t >( m_flag );

  return entry;
}

void EffectResult::execute()
{
  switch( m_type )
  {
    case Common::ActionEffectType::CALC_RESULT_TYPE_DAMAGE_HP:
    {
      m_target->takeDamage( m_value );
      break;
    }

    case Common::ActionEffectType::CALC_RESULT_TYPE_RECOVER_HP:
    {
      m_target->heal( m_value );
      break;
    }

    case Common::ActionEffectType::CALC_RESULT_TYPE_RECOVER_MP:
    {
      m_target->restoreMP( m_value );
      break;
    }

    case Common::ActionEffectType::CALC_RESULT_TYPE_MOUNT:
    {
      auto pPlayer = m_target->getAsPlayer();
      Common::Service< World::Manager::PlayerMgr >::ref().onMountUpdate( *pPlayer, m_value );
      break;
    }

    default:
      break;
  }
}