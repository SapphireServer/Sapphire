#include <Exd/ExdDataGenerated.h>
#include <Util/Util.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <Logging/Logger.h>

#include <algorithm>

#include "Actor/Chara.h"
#include "Actor/Actor.h"

#include "Script/ScriptMgr.h"

#include "Math/CalcStats.h"

#include "StatusEffect.h"
#include "Framework.h"

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;

Sapphire::StatusEffect::StatusEffect::StatusEffect( uint32_t id, Entity::CharaPtr sourceActor, Entity::CharaPtr targetActor,
                                                    uint32_t duration, uint32_t tickRate, FrameworkPtr pFw ) :
  m_id( id ),
  m_sourceActor( sourceActor ),
  m_targetActor( targetActor ),
  m_duration( duration ),
  m_startTime( 0 ),
  m_tickRate( tickRate ),
  m_lastTick( 0 ),
  m_pFw( pFw ),
  m_cachedHotOrDotValue( 0 ),
  m_cachedSourceCrit( 0 ),
  m_cachedSourceCritBonus( 0 )
{
  auto pExdData = m_pFw->get< Data::ExdDataGenerated >();
  auto entry = pExdData->get< Sapphire::Data::Status >( id );
  m_name = entry->name;

  std::replace( m_name.begin(), m_name.end(), ' ', '_' );
  std::replace( m_name.begin(), m_name.end(), ':', '_' );
  std::replace( m_name.begin(), m_name.end(), '&', '_' );
  std::replace( m_name.begin(), m_name.end(), '+', 'p' );
  Util::eraseAll( m_name, '\'' );
  Util::eraseAll( m_name, '&' );
  Util::eraseAll( m_name, '-' );
  Util::eraseAll( m_name, '(' );
  Util::eraseAll( m_name, ')' );

  if( Sapphire::World::Action::ActionLut::validStatusEffectExists( id ) )
    m_effectEntry = Sapphire::World::Action::ActionLut::getStatusEffectEntry( id );
  else
    m_effectEntry.effectType = Sapphire::World::Action::EffectTypeInvalid;
}


Sapphire::StatusEffect::StatusEffect::~StatusEffect()
{
}

void Sapphire::StatusEffect::StatusEffect::registerTickEffect( uint8_t type, uint32_t param )
{
  m_currTickEffect = std::make_pair( type, param );
}

std::pair< uint8_t, uint32_t > Sapphire::StatusEffect::StatusEffect::getTickEffect()
{
  auto thisTick = m_currTickEffect;
  if( m_effectEntry.effectType == Sapphire::World::Action::EffectTypeDot )
  {
    auto value = m_cachedHotOrDotValue;
    if( m_cachedSourceCrit > Sapphire::Math::CalcStats::range100( Sapphire::Math::CalcStats::rng ) )
    {
      value *= m_cachedSourceCritBonus;
    }
    value *= 1.0f + ( ( Sapphire::Math::CalcStats::range100( Sapphire::Math::CalcStats::rng ) - 50.0f ) / 1000.0f );
    m_currTickEffect = std::make_pair( 1, value );
  }
  else if( m_effectEntry.effectType == Sapphire::World::Action::EffectTypeHot )
  {
    auto value = m_cachedHotOrDotValue;
    if( m_cachedSourceCrit > Sapphire::Math::CalcStats::range100( Sapphire::Math::CalcStats::rng ) )
    {
      value *= m_cachedSourceCritBonus;
    }
    value *= 1.0f + ( ( Sapphire::Math::CalcStats::range100( Sapphire::Math::CalcStats::rng ) - 50.0f ) / 1000.0f );
    m_currTickEffect = std::make_pair( 2, value );
  }
  else
  {
    m_currTickEffect = std::make_pair( 0, 0 );
  }
  return thisTick;
}

void Sapphire::StatusEffect::StatusEffect::onTick()
{
  auto pScriptMgr = m_pFw->get< Scripting::ScriptMgr >();
  m_lastTick = Util::getTimeMs();
  pScriptMgr->onStatusTick( m_targetActor, *this );
}

uint32_t Sapphire::StatusEffect::StatusEffect::getSrcActorId() const
{
  return m_sourceActor->getId();
}

uint32_t Sapphire::StatusEffect::StatusEffect::getTargetActorId() const
{
  return m_targetActor->getId();
}

uint16_t Sapphire::StatusEffect::StatusEffect::getParam() const
{
  return m_param;
}

void Sapphire::StatusEffect::StatusEffect::applyStatus()
{
  m_startTime = Util::getTimeMs();
  auto pScriptMgr = m_pFw->get< Scripting::ScriptMgr >();

  if( m_effectEntry.effectType == Sapphire::World::Action::EffectTypeDot )
  {
    auto wepDmg = Sapphire::Math::CalcStats::getWeaponDamage( *m_sourceActor );
    auto damage = Sapphire::Math::CalcStats::calcDamageBaseOnPotency( *m_sourceActor, m_effectEntry.effectValue2, wepDmg );
    m_cachedHotOrDotValue = Sapphire::Math::CalcStats::applyDamageReceiveMultiplier( *m_targetActor, damage,
      m_effectEntry.effectValue1 == 1 ? -1 : ( m_effectEntry.effectValue1 == 2 ? 5 : -128 ) );
  }
  else if( m_effectEntry.effectType == Sapphire::World::Action::EffectTypeHot )
  {
    auto wepDmg = Sapphire::Math::CalcStats::getWeaponDamage( *m_sourceActor );
    auto heal = Sapphire::Math::CalcStats::calcHealBaseOnPotency( *m_sourceActor, m_effectEntry.effectValue2, wepDmg );
    m_cachedHotOrDotValue = Sapphire::Math::CalcStats::applyHealingReceiveMultiplier( *m_targetActor, heal, m_effectEntry.effectValue1 );
  }
  m_cachedSourceCrit = Sapphire::Math::CalcStats::criticalHitProbability( *m_sourceActor );
  m_cachedSourceCritBonus = Sapphire::Math::CalcStats::criticalHitBonus( *m_sourceActor );

  pScriptMgr->onStatusReceive( m_targetActor, m_id );
}

void Sapphire::StatusEffect::StatusEffect::removeStatus()
{
  auto pScriptMgr = m_pFw->get< Scripting::ScriptMgr >();
  pScriptMgr->onStatusTimeOut( m_targetActor, m_id );
}

uint32_t Sapphire::StatusEffect::StatusEffect::getId() const
{
  return m_id;
}

uint32_t Sapphire::StatusEffect::StatusEffect::getDuration() const
{
  return m_duration;
}

uint32_t Sapphire::StatusEffect::StatusEffect::getTickRate() const
{
  return m_tickRate;
}

uint64_t Sapphire::StatusEffect::StatusEffect::getLastTickMs() const
{
  return m_lastTick;
}

uint64_t Sapphire::StatusEffect::StatusEffect::getStartTimeMs() const
{
  return m_startTime;
}

void Sapphire::StatusEffect::StatusEffect::setLastTick( uint64_t lastTick )
{
  m_lastTick = lastTick;
}

void Sapphire::StatusEffect::StatusEffect::setParam( uint16_t param )
{
  m_param = param;
}

const std::string& Sapphire::StatusEffect::StatusEffect::getName() const
{
  return m_name;
}

const Sapphire::World::Action::StatusEffectEntry& Sapphire::StatusEffect::StatusEffect::getEffectEntry() const
{
  return m_effectEntry;
}
