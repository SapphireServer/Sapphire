#include <Exd/ExdDataGenerated.h>
#include <Util/Util.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <Logging/Logger.h>

#include <algorithm>
#include <Service.h>

#include "Actor/Player.h"
#include "Actor/Chara.h"
#include "Actor/Actor.h"

#include "Action/Action.h"

#include "Script/ScriptMgr.h"

#include "Math/CalcStats.h"

#include "StatusEffect.h"

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;

Sapphire::StatusEffect::StatusEffect::StatusEffect( uint32_t id, Entity::CharaPtr sourceActor, Entity::CharaPtr targetActor,
                                                    uint32_t duration, uint32_t tickRate ) :
  m_id( id ),
  m_sourceActor( sourceActor ),
  m_targetActor( targetActor ),
  m_duration( duration ),
  m_startTime( 0 ),
  m_tickRate( tickRate ),
  m_lastTick( 0 ),
  m_value( 0 ),
  m_cachedSourceCrit( 0 ),
  m_cachedSourceCritBonus( 0 ),
  m_markToRemove( false )
{
  auto& exdData = Common::Service< Data::ExdDataGenerated >::ref();
  auto entry = exdData.get< Sapphire::Data::Status >( id );
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
    m_effectEntry.effectType = static_cast< uint32_t >( Common::StatusEffectType::Invalid );
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
  switch( static_cast< Common::StatusEffectType >( m_effectEntry.effectType ) )
  {
    case Common::StatusEffectType::Dot:
    {
      auto value = m_value;
      if( m_cachedSourceCrit > Sapphire::Math::CalcStats::getRandomNumber0To99() )
      {
        value *= m_cachedSourceCritBonus;
      }
      value *= 1.0f + ( ( Sapphire::Math::CalcStats::getRandomNumber0To99() - 50.0f ) / 1000.0f );
      m_currTickEffect = std::make_pair( 1, value );
      break;
    }

    case Common::StatusEffectType::Hot:
    {
      auto value = m_value;
      if( m_cachedSourceCrit > Sapphire::Math::CalcStats::getRandomNumber0To99() )
      {
        value *= m_cachedSourceCritBonus;
      }
      value *= 1.0f + ( ( Sapphire::Math::CalcStats::getRandomNumber0To99() - 50.0f ) / 1000.0f );
      m_currTickEffect = std::make_pair( 2, value );
      break;
    }

    default:
    {
      m_currTickEffect = std::make_pair( 0, 0 );
      break;
    }
  }

  return m_currTickEffect;
}

void Sapphire::StatusEffect::StatusEffect::onTick()
{
  m_lastTick = Util::getTimeMs();

  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();
  scriptMgr.onStatusTick( m_targetActor, *this );

  auto statusEffectType = static_cast< Common::StatusEffectType >( m_effectEntry.effectType );
  if( statusEffectType == Common::StatusEffectType::MPRestore )
  {
    m_targetActor->restoreMP( m_effectEntry.effectValue1 * 10 );
  }
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
  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();
  scriptMgr.onStatusReceive( m_targetActor, m_id );

  switch( static_cast< Common::StatusEffectType >( m_effectEntry.effectType ) )
  {
    case Common::StatusEffectType::Dot:
    {
      auto wepDmg = Sapphire::Math::CalcStats::getWeaponDamage( m_sourceActor );
      auto damage = Sapphire::Math::CalcStats::calcDamageBaseOnPotency( *m_sourceActor, m_effectEntry.effectValue2, wepDmg );

      for( auto const& entry : m_sourceActor->getStatusEffectMap() )
      {
        auto status = entry.second;
        auto effectEntry = status->getEffectEntry();
        if( static_cast< Common::StatusEffectType >( effectEntry.effectType ) != Common::StatusEffectType::DamageMultiplier )
          continue;
        if( effectEntry.effectValue1 & m_effectEntry.effectValue1 )
        {
          damage *= 1.0f + ( effectEntry.effectValue2 / 100.0f );
        }
      }

      m_value = Sapphire::Math::CalcStats::applyDamageReceiveMultiplier( *m_targetActor, damage,
        m_effectEntry.effectValue1 == static_cast< int32_t >( Common::ActionTypeFilter::Physical ) ? Common::AttackType::Physical :
        ( m_effectEntry.effectValue1 == static_cast< int32_t >( Common::ActionTypeFilter::Magical ) ? Common::AttackType::Magical : Common::AttackType::Unknown_0 ) );
      m_cachedSourceCrit = Sapphire::Math::CalcStats::criticalHitProbability( *m_sourceActor, Common::CritDHBonusFilter::Damage );
      m_cachedSourceCritBonus = Sapphire::Math::CalcStats::criticalHitBonus( *m_sourceActor );
      break;
    }

    case Common::StatusEffectType::Hot:
    {
      auto wepDmg = Sapphire::Math::CalcStats::getWeaponDamage( m_sourceActor );
      auto heal = Sapphire::Math::CalcStats::calcHealBaseOnPotency( *m_sourceActor, m_effectEntry.effectValue2, wepDmg );

      if( m_effectEntry.effectValue1 == 0 ) // this value is always 0 atm, if statement here just in case there is a hot that isn't a "cast"
      {
        for( auto const& entry : m_sourceActor->getStatusEffectMap() )
        {
          auto status = entry.second;
          auto effectEntry = status->getEffectEntry();
          if( static_cast< Common::StatusEffectType >( effectEntry.effectType ) != Common::StatusEffectType::HealCastMultiplier )
            continue;
          heal *= 1.0f + ( effectEntry.effectValue2 / 100.0f );
        }
      }
      m_value = Sapphire::Math::CalcStats::applyHealingReceiveMultiplier( *m_targetActor, heal );
      m_cachedSourceCrit = Sapphire::Math::CalcStats::criticalHitProbability( *m_sourceActor, Common::CritDHBonusFilter::Heal );
      m_cachedSourceCritBonus = Sapphire::Math::CalcStats::criticalHitBonus( *m_sourceActor );
      break;
    }

    case Common::StatusEffectType::Haste:
    {
      auto pPlayer = m_targetActor->getAsPlayer();
      if( pPlayer )
        pPlayer->sendStats();
      break;
    }
  }
}

void Sapphire::StatusEffect::StatusEffect::removeStatus()
{
  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();
  scriptMgr.onStatusTimeOut( m_targetActor, m_id );

  switch( static_cast< Common::StatusEffectType >( m_effectEntry.effectType ) )
  {
    case Common::StatusEffectType::Haste:
    {
      auto pPlayer = m_targetActor->getAsPlayer();
      if( pPlayer )
        pPlayer->sendStats();
      break;
    }
  }

  // lol just hack it and hardcode this shit
  if( m_markToRemove && m_id == 1178 )
  {
    if( auto drk = m_sourceActor->getAsPlayer() )
    {
      if( drk->getClass() == Common::ClassJob::Darkknight )
      {
        drk->gaugeDrkSetDarkArts( true );
      }
    }
  }
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

void Sapphire::StatusEffect::StatusEffect::replaceEffectEntry( Sapphire::World::Action::StatusEffectEntry entryOverride )
{
  m_effectEntry = entryOverride;
}

void Sapphire::StatusEffect::StatusEffect::onBeforeActionStart( Sapphire::World::Action::ActionPtr action )
{
  // todo: add script function for this if needed
  //auto pScriptMgr = m_pFw->get< Scripting::ScriptMgr >();
  //pScriptMgr->onBeforeActionStart( m_targetActor, *this );

  switch( static_cast< Common::StatusEffectType >( m_effectEntry.effectType ) )
  {
    case Common::StatusEffectType::InstantCast:
    {
      if( !action->hasCastTime() )
        return;
      // value1: remaining uses
      // value2-4: affected action ids, or all actions if value2 is 0
      if( m_effectEntry.effectValue2 != 0 )
      {
        if( action->getId() != m_effectEntry.effectValue2 &&
            action->getId() != m_effectEntry.effectValue3 &&
            action->getId() != m_effectEntry.effectValue4 )
          return;
      }
      if( m_effectEntry.effectValue1 > 0 )
      {
        m_effectEntry.effectValue1--;
        if( m_effectEntry.effectValue1 == 0 )
        {
          markToRemove();
        }
        action->setCastTime( 0 );
      }
      break;
    }
  }
}

bool Sapphire::StatusEffect::StatusEffect::isMarkedToRemove()
{
  return m_markToRemove;
}

void Sapphire::StatusEffect::StatusEffect::markToRemove()
{
  m_markToRemove = true;
}

void Sapphire::StatusEffect::StatusEffect::refresh()
{
  m_value = 0;
  m_cachedSourceCritBonus = 0;
  m_cachedSourceCrit = 0;
  applyStatus();
}

void Sapphire::StatusEffect::StatusEffect::refresh( Sapphire::World::Action::StatusEffectEntry newEntry )
{
  m_effectEntry = newEntry;
  refresh();
}