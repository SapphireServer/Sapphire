#include "EffectBuilder.h"
#include "EffectResult.h"

#include <Actor/Player.h>

#include <Network/PacketWrappers/EffectPacket.h>
#include <Network/PacketWrappers/EffectPacket1.h>

#include <Territory/Territory.h>

#include <Util/Util.h>
#include <Util/UtilMath.h>

#include <Logging/Logger.h>

using namespace Sapphire;
using namespace Sapphire::World::Action;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets::Server;

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

void EffectBuilder::moveToResultList( Entity::CharaPtr& chara, EffectResultPtr result )
{
  auto it = m_resolvedEffects.find( chara->getId() );
  if( it == m_resolvedEffects.end() )
  {
    // create a new one
    auto resultList = std::make_shared< std::vector< EffectResultPtr > >();

    m_resolvedEffects[ chara->getId() ] = resultList;

    resultList->push_back( std::move( result ) );

    return;
  }

  it->second->push_back( std::move( result ) );
}

void EffectBuilder::heal( Entity::CharaPtr& effectTarget, Entity::CharaPtr& healingTarget, uint32_t amount, Common::ActionHitSeverityType severity, Common::ActionEffectResultFlag flag )
{
  EffectResultPtr nextResult = make_EffectResult( healingTarget, getResultDelayMs() );
  nextResult->heal( amount, severity, flag );
  moveToResultList( effectTarget, nextResult );
}

void EffectBuilder::restoreMP( Entity::CharaPtr& target, Entity::CharaPtr& restoringTarget, uint32_t amount, Common::ActionEffectResultFlag flag )
{
  EffectResultPtr nextResult = make_EffectResult( restoringTarget, getResultDelayMs() ); // restore mp source actor
  nextResult->restoreMP( amount, flag );
  moveToResultList( target, nextResult );
}

void EffectBuilder::damage( Entity::CharaPtr& effectTarget, Entity::CharaPtr& damagingTarget, uint32_t amount, Common::ActionHitSeverityType severity, Common::ActionEffectResultFlag flag )
{
  EffectResultPtr nextResult = make_EffectResult( damagingTarget, getResultDelayMs() );
  nextResult->damage( amount, severity, flag );
  moveToResultList( effectTarget, nextResult );
}

void EffectBuilder::startCombo( Entity::CharaPtr& target, uint16_t actionId )
{
  EffectResultPtr nextResult = make_EffectResult( target, 0 );
  nextResult->startCombo( actionId );
  moveToResultList( target, nextResult );
}

void EffectBuilder::comboSucceed( Entity::CharaPtr& target )
{
  EffectResultPtr nextResult = make_EffectResult( target, 0 );
  nextResult->comboSucceed();
  moveToResultList( target, nextResult );
}

void EffectBuilder::applyStatusEffect( Entity::CharaPtr& target, uint16_t statusId, uint8_t param )
{
  EffectResultPtr nextResult = make_EffectResult( target, 0 );
  nextResult->applyStatusEffect( statusId, param );
  moveToResultList( target, nextResult );
}

void EffectBuilder::mount( Entity::CharaPtr& target, uint16_t mountId )
{
  EffectResultPtr nextResult = make_EffectResult( target, getResultDelayMs() );
  nextResult->mount( mountId );
  moveToResultList( target, nextResult );
}

void EffectBuilder::buildAndSendPackets()
{
  auto targetCount = m_resolvedEffects.size();
  Logger::debug( "EffectBuilder result: " );
  Logger::debug( "Targets afflicted: {}", targetCount );

  auto globalSequence = m_sourceChara->getCurrentTerritory()->getNextEffectSequence();

  do // we want to send at least one packet even nothing is hit so other players can see
  {
    auto packet = buildNextEffectPacket( globalSequence );
    m_sourceChara->sendToInRangeSet( packet, true );
  }
  while( !m_resolvedEffects.empty() );
}

std::shared_ptr< FFXIVPacketBase > EffectBuilder::buildNextEffectPacket( uint32_t globalSequence )
{
  auto remainingTargetCount = m_resolvedEffects.size();

  if( remainingTargetCount > 1 ) // use AoeEffect packets
  {
    auto effectResult = makeZonePacket< FFXIVIpcActionResult >( m_sourceChara->getId() );
    Common::CalcResultParam* pEntry;
    uint64_t* pEffectTargetId;
    
    effectResult->data().ActionKey = m_actionId;
    effectResult->data().ActionKind = 1;
    effectResult->data().Action = static_cast< uint16_t >( m_actionId );
    effectResult->data().MainTarget = m_sourceChara->getId();
    effectResult->data().DirTarget = Common::Util::floatToUInt16Rot( m_sourceChara->getRot() );
    effectResult->data().Flag = Common::ActionEffectDisplayType::ShowActionName;
    effectResult->data().TargetCount = static_cast< uint8_t >( remainingTargetCount );
    effectResult->data().RequestId = m_sequence;
    effectResult->data().ResultId = globalSequence;

    uint8_t targetIndex = 0;
    for( auto it = m_resolvedEffects.begin(); it != m_resolvedEffects.end(); )
    {
      auto resultList = it->second;
      assert( !resultList->empty() );
      auto firstResult = resultList->data()[ 0 ];
      pEffectTargetId[ targetIndex ] = firstResult->getTarget()->getId();
      Logger::debug( " - id: {}", pEffectTargetId[ targetIndex ] );

      for( auto i = 0; i < resultList->size(); i++ )
      {
        auto result = resultList->data()[ i ];
        pEntry[ targetIndex * 8 + i ] = result->buildEffectEntry();
        m_sourceChara->getCurrentTerritory()->addEffectResult( std::move( result ) );
      }
      resultList->clear();

      it = m_resolvedEffects.erase( it );

      targetIndex++;

      if( targetIndex == 15 )
        break;
    }

    return effectResult;
  }
  else if ( remainingTargetCount == 1 ) // use Effect for single target
  {
    auto resultList = m_resolvedEffects.begin()->second;
    assert( !resultList->empty() );
    auto firstResult = resultList->data()[ 0 ];
    Logger::debug( " - id: {}", firstResult->getTarget()->getId() );

    auto seq = m_sourceChara->getCurrentTerritory()->getNextEffectSequence();

    auto effectPacket = std::make_shared< EffectPacket1 >( m_sourceChara->getId(), firstResult->getTarget()->getId(), m_actionId );
    effectPacket->setRotation( Common::Util::floatToUInt16Rot( m_sourceChara->getRot() ) );
    effectPacket->setSequence( seq, m_sequence );

    for( int i = 0; i < resultList->size(); i++ )
    {
      auto result = resultList->data()[ i ];
      effectPacket->addTargetEffect( result->buildEffectEntry() );
      m_sourceChara->getCurrentTerritory()->addEffectResult( std::move( result ) );
    }

    resultList->clear();

    m_resolvedEffects.clear();

    return effectPacket;
  }
  else // nothing is hit, this only happens when using aoe and AoeEffect8 is used on retail
  {
    auto effectPacket = makeZonePacket< FFXIVIpcActionResult1 >( m_sourceChara->getId() );

    effectPacket->data().ActionKey = m_actionId;
    effectPacket->data().Action = static_cast< uint16_t >( m_actionId );
    effectPacket->data().Target = m_sourceChara->getId();
    effectPacket->data().MainTarget = static_cast< uint64_t >( m_sourceChara->getId() );
    effectPacket->data().DirTarget = Common::Util::floatToUInt16Rot( m_sourceChara->getRot() );
    effectPacket->data().Flag = Common::ActionEffectDisplayType::HideActionName;
    effectPacket->data().RequestId = m_sequence;
    effectPacket->data().ResultId = globalSequence;

    return effectPacket;
  }
}