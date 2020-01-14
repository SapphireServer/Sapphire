#include "EffectResult.h"

#include <Util/Util.h>

#include "Actor/Chara.h"

using namespace Sapphire;
using namespace Sapphire::World::Action;


EffectResult::EffectResult( Entity::CharaPtr target, Entity::CharaPtr source, uint64_t runAfter ) :
  m_target( std::move( target ) ),
  m_source( std::move( source ) ),
  m_delayMs( runAfter ),
  m_type( Common::ActionEffectType::Nothing ),
  m_value( 0 ),
  m_statusDuration( 0 ),
  m_param0( 0 ),
  m_param1( 0 ),
  m_param2( 0 ),
  m_flag( Common::ActionEffectResultFlag::None ),
  m_pPreBuiltStatusEffect( nullptr )
{

}

Entity::CharaPtr EffectResult::getSource() const
{
  return m_source;
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

void EffectResult::applyStatusEffect( uint16_t statusId, uint32_t duration, uint8_t param )
{
  m_value = statusId;
  m_statusDuration = duration;
  m_param2 = param;

  m_type = Common::ActionEffectType::ApplyStatusEffect;
}

void EffectResult::applyStatusEffect( StatusEffect::StatusEffectPtr pStatusEffect )
{
  m_value = pStatusEffect->getId();
  m_param2 = pStatusEffect->getParam();
  m_pPreBuiltStatusEffect = std::move( pStatusEffect );

  m_type = Common::ActionEffectType::ApplyStatusEffect;
}

void EffectResult::statusNoEffect( uint16_t statusId )
{
  m_value = statusId;

  m_type = Common::ActionEffectType::StatusNoEffect;
}

Common::EffectEntry EffectResult::buildEffectEntry() const
{
  Common::EffectEntry entry{};

  // todo: that retarded shit so > u16 max numbers work
  entry.value = getValue();
  entry.param0 = m_param0;
  entry.param1 = m_param1;
  entry.effectType = m_type;
  entry.param2 = m_param2;
  entry.flags = static_cast< uint8_t >( m_flag );

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

    case Common::ActionEffectType::ApplyStatusEffect:
    {
      uint64_t lastTickOverride = 0;
      //remove same effect from the same source (refreshing old buff)
      for( auto const& entry : m_target->getStatusEffectMap() )
      {
        auto statusEffect = entry.second;
        if( statusEffect->getId() == m_value && statusEffect->getSrcActorId() == m_source->getId() )
        {
          lastTickOverride = statusEffect->getLastTickMs();
          // refreshing does not show "-status" flying text, and we don't send status list now because we are adding a new one
          m_target->removeStatusEffect( entry.first, false, false ); 
          break;
        }
      }

      if( m_pPreBuiltStatusEffect )
      {
        m_pPreBuiltStatusEffect->setLastTick( lastTickOverride );
        m_target->addStatusEffect( m_pPreBuiltStatusEffect );
      }
      else
        m_target->addStatusEffectById( m_value, m_statusDuration, *m_source, m_param2, lastTickOverride );

      break;
    }

    default:
      break;
  }
}