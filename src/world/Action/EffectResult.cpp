#include "EffectResult.h"

#include <Util/Util.h>

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
  m_type( Common::ActionEffectType::Nothing ),
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

  m_type = Common::ActionEffectType::Damage;
}

void EffectResult::heal( uint32_t amount, Common::ActionHitSeverityType severity, Common::ActionEffectResultFlag flag )
{
  m_param1 = static_cast< uint8_t >( severity );
  m_value = amount;
  m_flag = flag;

  m_type = Common::ActionEffectType::Heal;
}

void EffectResult::restoreMP( uint32_t amount, Common::ActionEffectResultFlag flag )
{
  m_value = amount;
  m_flag = flag;

  m_type = Common::ActionEffectType::MpGain;
}

void EffectResult::startCombo( uint16_t actionId )
{
  m_value = actionId;
  m_flag = Common::ActionEffectResultFlag::EffectOnSource;

  m_type = Common::ActionEffectType::StartActionCombo;
}

void EffectResult::comboSucceed()
{
  // no EffectOnSource flag on this
  m_type = Common::ActionEffectType::ComboSucceed;
}

void EffectResult::applyStatusEffect( uint16_t statusId, uint8_t param )
{
  m_value = statusId;
  m_param2 = param;

  m_type = Common::ActionEffectType::ApplyStatusEffectTarget;
}

void EffectResult::mount( uint16_t mountId )
{
  m_value = mountId;
  m_param0 = 1;

  m_type = Common::ActionEffectType::Mount;
}

Common::EffectEntry EffectResult::buildEffectEntry() const
{
  Common::EffectEntry entry{};
  entry.effectType = m_type;
  if( m_value > 0x0000FFFF )
  {
    entry.value = static_cast< uint16_t >( m_value & 0x0000FFFF );
    entry.extendedValueHighestByte = static_cast< uint8_t >( m_value >> 16 );
    entry.flags = static_cast< uint8_t >( m_flag ) + static_cast< uint8_t >( Common::ActionEffectResultFlag::ExtendedValue );
  }
  else
  {
    entry.value = static_cast< uint16_t >( m_value );
    entry.flags = static_cast< uint8_t >( m_flag );
  }
  entry.param0 = m_param0;
  entry.param1 = m_param1;
  entry.param2 = m_param2;

  return entry;
}

void EffectResult::execute()
{
  switch( m_type )
  {
    case Common::ActionEffectType::Damage:
    {
      m_target->takeDamage( m_value );
      break;
    }

    case Common::ActionEffectType::Heal:
    {
      m_target->heal( m_value );
      break;
    }

    case Common::ActionEffectType::MpGain:
    {
      m_target->restoreMP( m_value );
      break;
    }

    case Common::ActionEffectType::Mount:
    {
      auto pPlayer = m_target->getAsPlayer();
      pPlayer->mount( m_value );
      break;
    }

    default:
      break;
  }
}