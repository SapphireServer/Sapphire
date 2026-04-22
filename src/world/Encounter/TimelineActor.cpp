#include "TimelineActor.h"

#include "TimelinePack.h"

#include "Phase.h"
#include "Trigger.h"
#include "TriggerCondition.h"

#include <Actor/BNpc.h>
#include <Action/Action.h>

#include <Manager/PlayerMgr.h>
#include <Service.h>

#include <Territory/Territory.h>

namespace Sapphire
{
  void TimelineActor::addPhase( PhasePtr pPhase )
  {
    if( m_phases.find( pPhase->getId() ) != m_phases.end() )
      throw std::runtime_error( "TimelineActor::addPhase duplicate Phase by ID " + std::to_string( pPhase->getId() ) );

    m_phases.emplace( pPhase->getId(), pPhase );
  }

  const std::string& TimelineActor::getName() const
  {
    return m_name;
  }

  uint32_t TimelineActor::getLayoutId() const
  {
    return m_layoutId;
  }

  bool TimelineActor::isPhaseActive( uint32_t phaseId ) const
  {
    if( m_pPhase )
      return m_pPhase->getId() == phaseId;
    return false;
  }

  PhasePtr TimelineActor::getPhaseById( uint32_t phaseId )
  {
    if( auto it = m_phases.find( phaseId ); it != m_phases.end() )
      return it->second;

    return nullptr;
  }

  uint64_t TimelineActor::getPhaseElapsed() const
  {
    auto startTime = m_state.m_phaseState.m_startTime;
    if( startTime == 0 )
      startTime = Common::Util::getTimeMs();

    auto elapsed = Common::Util::getTimeMs() - startTime;

    return elapsed;
  }

  void TimelineActor::update(  EncounterPtr pEncounter, TimelinePack& pack, uint64_t time )
  {
    // todo: handle interrupts

    // set the initial phase according to timeline
    if( !m_pPhase )
    {
      auto& pPhase = m_phases.at( m_initialPhaseId );

      transitionPhase( pEncounter, pack, time, m_phases.at( m_initialPhaseId ) );
    }

    // update phase and schedules
    m_pPhase->update( *this, pack, m_state.m_phaseState, pEncounter, time );

    // fire any enabled triggers
    const auto& triggers = m_pPhase->getTriggers();
    for( const auto& [ id, trigger ] : triggers )
    {
      if( trigger.isEnabled( m_state.m_phaseState ) && trigger.isConditionMet( *this, pack, m_state.m_phaseState, pEncounter, time ) )
      {
        // trigger.execute may change the current phase, or fire a single timepoint
        trigger.execute( *this, pack, m_state.m_phaseState, pEncounter, time );
        break;
      }
    }
  }

  void TimelineActor::transitionPhase( EncounterPtr pEncounter, TimelinePack& pack, uint64_t time, PhasePtr pPhase )
  {
    // clean up if we already have a phase active
    if( m_pPhase )
      m_pPhase->onExit( *this, pack, m_state.m_phaseState, pEncounter, time );

    // set the new phase ptr
    m_pPhase = pPhase;

    // set the new phase id
    m_state.m_phaseId = pPhase->getId();

    // reset start time
    m_state.m_phaseState.m_startTime = 0;
    m_state.m_phaseState.m_scheduleInfo.clear();

    // reset triggers
    m_state.m_phaseState.m_triggerStates.clear();
    // enable/disable triggers according to default value in timeline
    for( const auto& [ id, trigger ] : pPhase->getTriggers() )
      m_state.m_phaseState.m_triggerStates.emplace( id, trigger.getDefaultEnabled() );

    // run setup for new phase
    m_pPhase->onEnter( *this, pack, m_state.m_phaseState, pEncounter, time );
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
        // todo: need to reset the ai on interrupt
        auto pAction = subActor.second->getCurrentAction();
        if( pAction )
          pAction->interrupt();

        pTeri->removeActor( subActor.second );
        subActor.second = nullptr;
      }
    }
  }

  void TimelineActor::setTriggerEnabled( uint32_t phaseId, uint32_t triggerId, bool enabled )
  {
    // only fire if current phase is phaseId
    if( m_pPhase->getId() == phaseId )
    {
      auto& trigger = m_pPhase->getTriggers().at( triggerId );
      trigger.setEnabled( m_state.m_phaseState, enabled );
    }
  }

  Entity::BNpcPtr TimelineActor::spawnSubActor( const std::string& name, TerritoryPtr pTeri )
  {
    // todo: retail straight up respawns sub actors, even bnpc parts (qarn adjudicator body parts respawn each time with new ids)
    auto flags = Entity::BNpcFlag::Invincible | Entity::BNpcFlag::Untargetable |
                 Entity::BNpcFlag::Immobile | Entity::BNpcFlag::AutoAttackDisabled |
                 Entity::BNpcFlag::TurningDisabled | Entity::BNpcFlag::NoDeaggro |
                 Entity::BNpcFlag::Invisible;

    auto pActor = getSubActor( name );
    if( pActor == nullptr )
    {
      auto pParent = pTeri->getActiveBNpcByLayoutId( m_layoutId );
      Common::BNpcType type = pParent ? pParent->getBNpcType() : Common::BNpcType::Enemy;
      
      pActor = pTeri->createBNpcFromLayoutIdNoPush( m_layoutId, 1000, type );
      m_subActors[ name ] = pActor;

      pActor->setInvincibilityType( Common::InvincibilityIgnoreDamage );
      pActor->setFlag( flags );
      pActor->init();

      pTeri->pushActor( pActor );

      auto& playerMgr = Common::Service< World::Manager::PlayerMgr >::ref();
      for( const auto& player : pTeri->getPlayers() )
      {
        playerMgr.sendDebug( *player.second, fmt::format( "Spawned subactor {}", name ) );
      }
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
        auto& pBNpc = subActor.second;
        pTeri->removeActor( pBNpc );
        subActor.second = nullptr;
      }
    }
  }

};