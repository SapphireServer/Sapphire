#include "EffectBuilder.h"
#include "EffectResult.h"

#include <Actor/Player.h>

#include <Network/PacketWrappers/EffectPacket.h>

#include <Territory/Territory.h>

#include <Util/Util.h>
#include <Util/UtilMath.h>

#include <Logging/Logger.h>

using namespace Sapphire;
using namespace Sapphire::World::Action;
using namespace Sapphire::Network::Packets;

EffectBuilder::EffectBuilder( Entity::CharaPtr source, uint32_t actionId, uint16_t sequence ) :
  m_sourceChara( std::move( source ) ),
  m_actionId( actionId ),
  m_sequence( sequence )
{

}

uint64_t EffectBuilder::getResultDelayMs()
{
  // todo: actually figure this retarded shit out

  return Common::Util::getTimeMs() + 850;
}

std::shared_ptr< std::vector< EffectResultPtr > > EffectBuilder::getResultList( Entity::CharaPtr& chara )
{
  auto it = m_resolvedEffects.find( chara->getId() );
  if( it == m_resolvedEffects.end() )
  {
    // create a new one and return it
    auto resultList = std::make_shared< std::vector< EffectResultPtr > >();

    m_resolvedEffects[ chara->getId() ] = resultList;

    return resultList;
  }

  return it->second;
}

void EffectBuilder::healTarget( Entity::CharaPtr& target, uint32_t amount, Common::ActionHitSeverityType severity )
{
  auto resultList = getResultList( target );
  assert( resultList );

  EffectResultPtr nextResult = make_EffectResult( target, getResultDelayMs() );
  nextResult->heal( amount, severity, false );
  resultList->push_back( std::move( nextResult ) );
}

void EffectBuilder::selfHeal( Entity::CharaPtr& target, Entity::CharaPtr& source, uint32_t amount, Common::ActionHitSeverityType severity )
{
  auto resultList = getResultList( target );
  assert( resultList );

  EffectResultPtr nextResult = make_EffectResult( source, getResultDelayMs() ); // heal the source actor
  nextResult->heal( amount, severity, true );
  resultList->push_back( std::move( nextResult ) );
}

void EffectBuilder::restoreMP( Entity::CharaPtr& target, Entity::CharaPtr& source, uint32_t amount )
{
  auto resultList = getResultList( target );
  assert( resultList );

  EffectResultPtr nextResult = make_EffectResult( source, getResultDelayMs() ); // restore mp source actor
  nextResult->restoreMP( amount );
  resultList->push_back( std::move( nextResult ) );
}

void EffectBuilder::damageTarget( Entity::CharaPtr& target, uint32_t amount, Common::ActionHitSeverityType severity )
{
  auto resultList = getResultList( target );
  assert( resultList );

  EffectResultPtr nextResult = make_EffectResult( target, getResultDelayMs() );
  nextResult->damage( amount, severity );
  resultList->push_back( std::move( nextResult ) );
}

void EffectBuilder::startCombo( Entity::CharaPtr& target, uint16_t actionId )
{
  auto resultList = getResultList( target );
  assert( resultList );

  EffectResultPtr nextResult = make_EffectResult( target, 0 );
  nextResult->startCombo( actionId );
  resultList->push_back( std::move( nextResult ) );
}

void EffectBuilder::comboVisualEffect( Entity::CharaPtr& target )
{
  auto resultList = getResultList( target );
  assert( resultList );

  EffectResultPtr nextResult = make_EffectResult( target, 0 );
  nextResult->comboVisualEffect();
  resultList->push_back( std::move( nextResult ) );
}

void EffectBuilder::buildAndSendPackets()
{
  Logger::debug( "EffectBuilder result: " );
  Logger::debug( "Targets afflicted: {}", m_resolvedEffects.size() );

  for( auto it = m_resolvedEffects.begin(); it != m_resolvedEffects.end(); )
  {
    auto resultList = it->second;
    assert( resultList->size() > 0 );
    auto firstResult = resultList->data()[ 0 ];
    Logger::debug( " - id: {}", firstResult->getTarget()->getId() );

    auto seq = m_sourceChara->getCurrentTerritory()->getNextEffectSequence();

    auto effectPacket = std::make_shared< Server::EffectPacket >( m_sourceChara->getId(), firstResult->getTarget()->getId(), m_actionId );
    effectPacket->setRotation( Common::Util::floatToUInt16Rot( m_sourceChara->getRot() ) );
    effectPacket->setSequence( seq, m_sequence );

    for( int i = 0; i < resultList->size(); i++ )
    {
      auto result = resultList->data()[ i ];
      effectPacket->addEffect( result->buildEffectEntry() );
      // add effect to territory
      m_sourceChara->getCurrentTerritory()->addEffectResult( std::move( result ) );
    }

    resultList->clear();

    m_sourceChara->sendToInRangeSet( effectPacket, true );

    it = m_resolvedEffects.erase( it );
  }
}