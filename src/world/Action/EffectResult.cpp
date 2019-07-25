#include "EffectResult.h"

#include <Util/Util.h>

using namespace Sapphire;
using namespace Sapphire::World::Action;


EffectResult::EffectResult( Entity::CharaPtr target, uint32_t runAfter ) :
  m_target( std::move( target ) ),
  m_runAfter( runAfter ),
  m_value( 0 ),
  m_severity( Common::ActionHitSeverityType::NormalDamage )
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


  return entry;
}