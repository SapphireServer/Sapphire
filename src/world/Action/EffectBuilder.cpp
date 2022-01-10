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

void EffectBuilder::addResultToActor( Entity::CharaPtr& chara, EffectResultPtr result )
{
  auto it = m_actorEffectsMap.find( chara->getId() );
  if( it == m_actorEffectsMap.end() )
  {
    // create a new one
    auto resultList = std::vector< EffectResultPtr >();

    resultList.push_back( std::move( result ) );

    m_actorEffectsMap[ chara->getId() ] = resultList;

    return;
  }

  it->second.push_back( std::move( result ) );
}

void EffectBuilder::heal( Entity::CharaPtr& effectTarget, Entity::CharaPtr& healingTarget, uint32_t amount, Common::ActionHitSeverityType severity, Common::ActionEffectResultFlag flag )
{
  EffectResultPtr nextResult = make_EffectResult( healingTarget, getResultDelayMs() );
  nextResult->heal( amount, severity, flag );
  addResultToActor( effectTarget, nextResult );
}

void EffectBuilder::restoreMP( Entity::CharaPtr& target, Entity::CharaPtr& restoringTarget, uint32_t amount, Common::ActionEffectResultFlag flag )
{
  EffectResultPtr nextResult = make_EffectResult( restoringTarget, getResultDelayMs() ); // restore mp source actor
  nextResult->restoreMP( amount, flag );
  addResultToActor( target, nextResult );
}

void EffectBuilder::damage( Entity::CharaPtr& effectTarget, Entity::CharaPtr& damagingTarget, uint32_t amount, Common::ActionHitSeverityType severity, Common::ActionEffectResultFlag flag )
{
  EffectResultPtr nextResult = make_EffectResult( damagingTarget, getResultDelayMs() );
  nextResult->damage( amount, severity, flag );
  addResultToActor( damagingTarget, nextResult );
}

void EffectBuilder::startCombo( Entity::CharaPtr& target, uint16_t actionId )
{
  EffectResultPtr nextResult = make_EffectResult( target, 0 );
  nextResult->startCombo( actionId );
  addResultToActor( target, nextResult );
}

void EffectBuilder::comboSucceed( Entity::CharaPtr& target )
{
  EffectResultPtr nextResult = make_EffectResult( target, 0 );
  nextResult->comboSucceed();
  addResultToActor( target, nextResult );
}

void EffectBuilder::applyStatusEffect( Entity::CharaPtr& target, uint16_t statusId, uint8_t param )
{
  EffectResultPtr nextResult = make_EffectResult( target, 0 );
  nextResult->applyStatusEffect( statusId, param );
  addResultToActor( target, nextResult );
}

void EffectBuilder::mount( Entity::CharaPtr& target, uint16_t mountId )
{
  EffectResultPtr nextResult = make_EffectResult( target, getResultDelayMs() );
  nextResult->mount( mountId );
  addResultToActor( target, nextResult );
}

void EffectBuilder::buildAndSendPackets( const std::vector< Entity::CharaPtr >& targetList )
{
  Logger::debug( "EffectBuilder result: " );
  Logger::debug( "Targets afflicted: {}", targetList.size() );

  do // we want to send at least one packet even nothing is hit so other players can see
  {
    auto packet = buildNextEffectPacket( targetList );
    m_sourceChara->sendToInRangeSet( packet, true );
  }
  while( !m_actorEffectsMap.empty() );
}

std::shared_ptr< FFXIVPacketBase > EffectBuilder::buildNextEffectPacket( const std::vector< Entity::CharaPtr >& targetList )
{
  auto remainingTargetCount = targetList.size();
  auto globalSequence = m_sourceChara->getCurrentTerritory()->getNextEffectSequence();

  if( remainingTargetCount > 1 ) // use AoeEffect packets
  {
    auto effectPacket = std::make_shared< EffectPacket >( m_sourceChara->getId(), m_actionId );
    effectPacket->setRotation( Common::Util::floatToUInt16Rot( m_sourceChara->getRot() ) );
    effectPacket->setSequence( globalSequence, m_sequence );
    effectPacket->setTargetActor( targetList[ 0 ]->getId() );

    uint8_t targetIndex = 0;
    for( auto it = m_actorEffectsMap.begin(); it != m_actorEffectsMap.end(); )
    {
      // get all effect results for an actor
      auto actorResultList = it->second;

      for( auto i = 0; i < actorResultList.size(); ++i )
      {
        auto result = actorResultList.data()[ i ];
        auto effect = result->buildEffectEntry();

        // if effect result is a source/caster effect
        if( result->getTarget() == m_sourceChara )
        {
          effectPacket->addSourceEffect( effect );
        }
        else
        {
          effectPacket->addTargetEffect( effect, result->getTarget()->getId() );
        }
        
        m_sourceChara->getCurrentTerritory()->addEffectResult( std::move( result ) );
      }

      actorResultList.clear();
      it = m_actorEffectsMap.erase( it );
      targetIndex++;

      if( targetIndex == 15 )
        break;
    }

    return effectPacket;
  }
  else if( remainingTargetCount == 1 ) // use Effect for single target
  {
    Logger::debug( " - id: {}", targetList[0]->getId() );
    Logger::debug( "------------------------------------------" );

    auto effectPacket = std::make_shared< EffectPacket1 >( m_sourceChara->getId(), targetList[ 0 ]->getId(), m_actionId );
    effectPacket->setRotation( Common::Util::floatToUInt16Rot( m_sourceChara->getRot() ) );
    effectPacket->setSequence( globalSequence, m_sequence );

    for( auto it = m_actorEffectsMap.begin(); it != m_actorEffectsMap.end(); )
    {
      // get all effect results for an actor
      auto actorResultList = it->second;

      for( auto i = 0; i < actorResultList.size(); ++i )
      {
        auto result = actorResultList.data()[ i ];
        auto effect = result->buildEffectEntry();

        // if effect result is a source/caster effect
        if( result->getTarget() == m_sourceChara )
        {
          effectPacket->addSourceEffect( effect );
        }
        else
        {
          effectPacket->addTargetEffect( effect );
        }
        
        m_sourceChara->getCurrentTerritory()->addEffectResult( std::move( result ) );
      }

      actorResultList.clear();
      it = m_actorEffectsMap.erase( it );
    }

    m_actorEffectsMap.clear();

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

    m_actorEffectsMap.clear();

    return effectPacket;
  }
}