#include "Encounter.h"

#include "TimelinePack.h"

namespace Sapphire
{
  Encounter::Encounter( TerritoryPtr pInstance, std::shared_ptr< Event::Director > pDirector,
                        const std::string& timelineName ) :
    m_pTeri( pInstance ),
    m_pDirector( pDirector ),
    m_status( EncounterStatus::UNINITIALIZED )
  {
    m_setup.timelineName = timelineName;
  }

  void Encounter::init()
  {
    m_pTimeline = TimelinePack::createTimelinePack( m_setup.timelineName );
    m_pTimeline->setEncounter( shared_from_this() );
    m_status = EncounterStatus::IDLE;
    m_startTime = 0;

    for( const auto& actor : m_setup.actorSetupList )
    {
      auto entry = m_pTeri->createBNpcFromLayoutId( actor.layoutId, actor.hp, actor.type );
      entry->init();
      addBNpc( entry );
    }
  }

  void Encounter::start()
  {
    m_status = EncounterStatus::ACTIVE;
  }

  void Encounter::update( uint64_t currTime )
  {
    m_pTimeline->update( currTime );
  }

  void Encounter::reset()
  {
    removeBNpcs();
    m_pTimeline->reset( shared_from_this() );
    init();
  }

  void Encounter::removeBNpcs()
  {
    for( auto it = m_bnpcs.begin(); it != m_bnpcs.end(); )
    {
      m_pTeri->removeActor( it->second );
      it = m_bnpcs.erase( it );
    }
  }

  void Encounter::setStartTime( uint64_t startTime )
  {
    m_startTime = startTime;
  }

  EncounterStatus Encounter::getStatus() const
  {
    return m_status;
  }

  void Encounter::setStatus( EncounterStatus status )
  {
    m_status = status;
  }

  void Encounter::addBNpc( Entity::BNpcPtr pBNpc )
  {
    m_bnpcs[ pBNpc->getLayoutId() ] = pBNpc;
  }

  Entity::BNpcPtr Encounter::getBNpc( uint32_t layoutId ) const
  {
    auto bnpc = m_bnpcs.find( layoutId );
    if( bnpc != std::end( m_bnpcs ) )
      return bnpc->second;

    return nullptr;
  }

  void Encounter::removeBNpc( uint32_t layoutId )
  {
    m_bnpcs.erase( layoutId );
  }

  TerritoryPtr Encounter::getTeriPtr()
  {
    return m_pTeri;
  }

  Event::DirectorPtr Encounter::getDirector()
  {
    return m_pDirector;
  }

  void Encounter::setInitialActorSetup( const std::vector< EncounterActor >& actorSetupList )
  {
    m_setup.actorSetupList = actorSetupList;
  }

  EncounterSetup& Encounter::getSetup()
  {
    return m_setup;
  }
}
