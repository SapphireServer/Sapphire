#include "TimelineActor.h"

#include "EncounterTimeline.h"

#include <Actor/BNpc.h>

namespace Sapphire::Encounter
{
  void TimelineActor::addPhaseCondition( PhaseConditionPtr pCondition )
  {
    m_phaseConditions.emplace( std::make_pair( pCondition->getId(), pCondition ) );
    m_conditionStates[ pCondition->getId() ] = {};
    m_conditionStates[ pCondition->getId() ].m_enabled = pCondition->isDefaultEnabled();
  }

  // todo: make this sane

  void TimelineActor::update( TerritoryPtr pTeri, TimelinePack& pack, uint64_t time )
  {
    // todo: handle interrupts
    for( const auto& condition : m_phaseConditions )
    {
      const auto& pCondition = condition.second;
      auto& state = m_conditionStates[ pCondition->getId() ];

      // ignore if not enabled, unless overriden to enable
      if( !pCondition->isStateEnabled( state ) )
        continue;

      if( pCondition->completed( state ) )
      {
        if( pCondition->isLoopable() )
        {
          if( pCondition->loopReady( state, time ) )
            pCondition->reset( state );
        }
      }
      else if( pCondition->inProgress( state ) )
      {
        pCondition->update( state, *this, pack, pTeri, time );
      }
      else if( pCondition->isConditionMet( state, pack, pTeri, time ) )
      {
        pCondition->execute( state, *this, pack, pTeri, time );

        if( pack.getStartTime() == 0 )
          pack.setStartTime( state.m_startTime );
      }
    }
  }

  void TimelineActor::resetConditionState( uint32_t conditionId )
  {
    if( auto it = m_phaseConditions.find( conditionId ); it != m_phaseConditions.end() )
    {
      auto& state = m_conditionStates.at( it->first );
      it->second->reset( state );
    }
  }

  void TimelineActor::setConditionStateEnabled( uint32_t conditionId, bool enabled )
  {
    if( auto it = m_conditionStates.find( conditionId ); it != m_conditionStates.end() )
    {
      auto& state = m_conditionStates.at( it->first );
      state.m_enabled = enabled;
    }
  }

  void TimelineActor::resetAllConditionStates()
  {
    for( const auto& condition : m_phaseConditions )
    {
      const auto& pCondition = condition.second;
      auto& state = m_conditionStates.at( condition.first );

      pCondition->reset( state );
    }
  }

  void TimelineActor::spawnAllSubActors( TerritoryPtr pTeri )
  {
    std::vector< std::string > toSpawn;
    for( const auto& subActor : m_subActors )
      if( getSubActor( subActor.first ) == nullptr )
        toSpawn.push_back( subActor.first );

    for( const auto& name : toSpawn )
      spawnSubActor( name, pTeri );
  }


  void TimelineActor::addPlaceholderSubactor( const std::string& name )
  {
    // populate m_subActors with nullptr BNpcs
    // then spawn them all in first timepoint and ref them by name subsequently
    if( getSubActor( name ) == nullptr )
      m_subActors.emplace( std::make_pair( name, nullptr ) );
  }

  Entity::BNpcPtr TimelineActor::getBNpcByRef( const std::string& name, TerritoryPtr pTeri ) const
  {
    if( name == m_name )
      return pTeri->getActiveBNpcByLayoutId( m_layoutId );
    return getSubActor( name );
  }

  void TimelineActor::resetAllSubActors( TerritoryPtr pTeri )
  {
    for( auto& subActor : m_subActors )
    {
      if( subActor.second )
      {
        auto inRange = subActor.second->getInRangeActors();
        for( const auto& pActor : inRange )
        {
          if( auto pPlayer = pActor->getAsPlayer() )
            subActor.second->despawn( pPlayer );
        }
        pTeri->removeActor( subActor.second );
        subActor.second = nullptr;
      }
    }
  }

  Entity::BNpcPtr TimelineActor::spawnSubActor( const std::string& name, TerritoryPtr pTeri )
  {
    // todo: retail straight up respawns sub actors, even bnpc parts (qarn adjudicator body parts respawn each time with new ids)
    auto flags = Entity::BNpcFlag::Invincible | Entity::BNpcFlag::Untargetable |
                 Entity::BNpcFlag::Immobile | Entity::BNpcFlag::AutoAttackDisabled |
                 Entity::BNpcFlag::TurningDisabled;

    auto pActor = getSubActor( name );
    if( pActor == nullptr )
    {
      auto pParent = pTeri->getActiveBNpcByLayoutId( m_layoutId );
      pActor = pTeri->createBNpcFromLayoutId( m_layoutId, 1000, pParent->getBNpcType() );
      m_subActors[ name ] = pActor;

      pActor->setInvincibilityType( Common::InvincibilityIgnoreDamage );
      pActor->setFlag( flags );
      pActor->init();

      pTeri->pushActor( pActor );
    }

    return pActor;
  }

  Entity::BNpcPtr TimelineActor::getSubActor( const std::string& name ) const
  {
    if( auto it = m_subActors.find( name ); it != m_subActors.end() )
      return it->second;
    return nullptr;
  }

  void TimelineActor::resetSubActors( TerritoryPtr pTeri )
  {
    for( auto& subActor : m_subActors )
    {
      if( subActor.second )
      {
        auto pBNpc = subActor.second;
        pTeri->removeActor( pBNpc );
        // todo: despawn?
        subActor.second = nullptr;
      }
    }
  }

};