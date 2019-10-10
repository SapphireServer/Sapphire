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

EffectResultPtr EffectBuilder::getResult( Entity::CharaPtr& chara )
{
  auto it = m_resolvedEffects.find( chara->getId() );
  if( it == m_resolvedEffects.end() )
  {
    // create a new one and return it
    // todo: this feels kinda dirty but makes for easy work
    auto result = make_EffectResult( chara, getResultDelayMs() );

    m_resolvedEffects[ chara->getId() ] = result;

    return result;
  }

  return it->second;
}

void EffectBuilder::healTarget( Entity::CharaPtr& target, uint32_t amount, Common::ActionHitSeverityType severity )
{
  auto result = getResult( target );
  assert( result );

  result->heal( amount, severity );
}

void EffectBuilder::damageTarget( Entity::CharaPtr& target, uint32_t amount, Common::ActionHitSeverityType severity )
{
  auto result = getResult( target );
  assert( result );

  result->damage( amount, severity );
}

void EffectBuilder::buildAndSendPackets()
{
  Logger::debug( "EffectBuilder result: " );
  Logger::debug( "Targets afflicted: {}", m_resolvedEffects.size() );

  for( auto it = m_resolvedEffects.begin(); it != m_resolvedEffects.end(); )
  {
    auto result = it->second;
    Logger::debug( " - id: {}", result->getTarget()->getId() );

    auto seq = m_sourceChara->getCurrentTerritory()->getNextEffectSequence();

    auto effectPacket = std::make_shared< Server::EffectPacket >( m_sourceChara->getId(), result->getTarget()->getId(), m_actionId );
    effectPacket->setRotation( Common::Util::floatToUInt16Rot( m_sourceChara->getRot() ) );
    effectPacket->setSequence( seq, m_sequence );

    effectPacket->addEffect( result->buildEffectEntry() );

    m_sourceChara->sendToInRangeSet( effectPacket, true );

    // add effect to territory
    m_sourceChara->getCurrentTerritory()->addEffectResult( std::move( result ) );

    it = m_resolvedEffects.erase( it );
  }
}