#include "Encounter.h"

namespace Sapphire
{
  Encounter::Encounter( TerritoryPtr pInstance, std::shared_ptr< Event::Director > pDirector, const std::string& timelineName ) :
    m_pTeri( pInstance ),
    m_pDirector( pDirector ),
    m_timelineName( timelineName ),
    m_status( EncounterStatus::UNINITIALIZED )
  {
  }

  void Encounter::init()
  {
    m_pTimeline = EncounterTimeline::createTimelinePack( m_timelineName );
    m_pTimeline->setEncounter( shared_from_this() );
    m_status = EncounterStatus::IDLE;
    m_startTime = 0;
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
}
