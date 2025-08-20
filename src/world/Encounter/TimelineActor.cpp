#include "TimelineActor.h"

#include "TimelinePack.h"

#include <Actor/BNpc.h>
#include <Action/Action.h>

#include <Manager/PlayerMgr.h>
#include <Service.h>

#include <Territory/Territory.h>

namespace Sapphire
{
  const std::string& TimelineActor::getName() const
  {
    return m_name;
  }

  uint32_t TimelineActor::getLayoutId() const
  {
    return m_layoutId;
  }

  bool TimelineActor::isScheduleActive( const std::string& name ) const
  {
    for( const auto& condition : m_scheduleConditions )
    {
      const auto& pCondition = condition.second;
      const auto& state = m_conditionStates.at( condition.first );
      if( pCondition->inProgress( state ) && pCondition->getScheduleName() == name )
        return true;
    }
    return false;
  }

  void TimelineActor::addPhaseCondition( ScheduleConditionPtr pCondition )
  {
    m_scheduleConditions.emplace( std::make_pair( pCondition->getId(), pCondition ) );
    m_conditionStates[ pCondition->getId() ] = {};
    m_conditionStates[ pCondition->getId() ].m_enabled = pCondition->isDefaultEnabled();
  }

  // todo: make this sane

  void TimelineActor::update(  EncounterPtr pEncounter, TimelinePack& pack, uint64_t time )
  {
    // todo: handle interrupts
    for( const auto& condition : m_scheduleConditions )
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
      // update or execute
      else if( pCondition->isConditionMet( state, pack, pEncounter, time ) )
      {
        if( pCondition->inProgress( state ) )
        {
          pCondition->update( state, *this, pack, pEncounter, time );
        }
        else
        {
          pCondition->execute( state, *this, pack, pEncounter, time );

          if( pack.getStartTime() == 0 )
            pack.setStartTime( state.m_startTime );
        }
      }
    }
  }

  bool TimelineActor::resetConditionState( uint32_t conditionId, bool toDefault )
  {
    if( auto it = m_scheduleConditions.find( conditionId ); it != m_scheduleConditions.end() )
    {
      auto& state = m_conditionStates.at( it->first );
      it->second->reset( state, toDefault );
      return true;
    }
    return false;
  }

  bool TimelineActor::setConditionStateEnabled( uint32_t conditionId, bool enabled )
  {
    if( auto it = m_conditionStates.find( conditionId ); it != m_conditionStates.end() )
    {
      auto& state = m_conditionStates.at( it->first );
      state.m_enabled = enabled;
      return true;
    }
    return false;
  }

  void TimelineActor::resetAllConditionStates()
  {
    for( const auto& condition : m_scheduleConditions )
    {
      const auto& pCondition = condition.second;
      auto& state = m_conditionStates.at( condition.first );

      pCondition->reset( state, true );
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
        // todo: need to reset the ai on interrupt
        auto pAction = subActor.second->getCurrentAction();
        if( pAction )
          pAction->interrupt();

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
                 Entity::BNpcFlag::TurningDisabled | Entity::BNpcFlag::NoDeaggro;

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