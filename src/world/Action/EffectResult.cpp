#include "EffectResult.h"

#include <Util/Util.h>

#include "Actor/Chara.h"

using namespace Sapphire;
using namespace Sapphire::World::Action;


EffectResult::EffectResult( Entity::CharaPtr target, uint64_t runAfter ) :
  m_target( std::move( target ) ),
  m_delayMs( runAfter ),
  m_value( 0 ),
  m_severity( Common::ActionHitSeverityType::NormalDamage ),
  m_type( Common::ActionEffectType::Nothing ),
  m_param( 0 )
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

void EffectResult::setParam( uint8_t param )
{
  m_param = param;
}

void EffectResult::damage( uint32_t amount, Common::ActionHitSeverityType severity )
{
  m_severity = severity;
  m_value = amount;

  m_type = Common::ActionEffectType::Damage;
}

void EffectResult::heal( uint32_t amount, Sapphire::Common::ActionHitSeverityType severity )
{
  m_severity = severity;
  m_value = amount;

  m_type = Common::ActionEffectType::Heal;
}

Common::EffectEntry EffectResult::buildEffectEntry() const
{
  Common::EffectEntry entry{};

  // todo: that retarded shit so > u16 max numbers work
  entry.value = getValue();
  entry.hitSeverity = m_severity;
  entry.effectType = m_type;
  entry.param = m_param;

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

    default:
      break;
  }
}