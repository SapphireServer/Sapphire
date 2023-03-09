#include "ActionResultBuilder.h"
#include "ActionResult.h"

#include <Actor/Player.h>

#include <Network/PacketWrappers/EffectPacket.h>
#include <Network/PacketWrappers/EffectPacket1.h>

#include <Territory/Territory.h>

#include <Util/Util.h>
#include <Util/UtilMath.h>

#include <Logging/Logger.h>
#include <Manager/TerritoryMgr.h>
#include <Manager/MgrUtil.h>
#include <Service.h>

#include <Manager/TaskMgr.h>
#include <Task/ActionIntegrityTask.h>

using namespace Sapphire;
using namespace Sapphire::World::Action;
using namespace Sapphire::World::Manager;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets::Server;

ActionResultBuilder::ActionResultBuilder( Entity::CharaPtr source, uint32_t actionId, uint32_t resultId, uint16_t requestId ) :
  m_sourceChara( std::move( source ) ),
  m_actionId( actionId ),
  m_resultId( resultId ),
  m_requestId( requestId )
{

}

uint64_t ActionResultBuilder::getResultDelayMs()
{
  // todo: actually figure this retarded shit out

  return Common::Util::getTimeMs() + 850;
}

void ActionResultBuilder::addResultToActor( Entity::CharaPtr& chara, ActionResultPtr result )
{
  auto it = m_actorResultsMap.find( chara->getId() );
  if( it == m_actorResultsMap.end() )
  {
    // create a new one
    auto resultList = std::vector< ActionResultPtr >();

    resultList.push_back( std::move( result ) );

    m_actorResultsMap[ chara->getId() ] = resultList;

    return;
  }

  it->second.push_back( std::move( result ) );
}

void ActionResultBuilder::heal( Entity::CharaPtr& effectTarget, Entity::CharaPtr& healingTarget, uint32_t amount, Common::ActionHitSeverityType severity, Common::ActionResultFlag flag )
{
  ActionResultPtr nextResult = make_ActionResult( healingTarget, getResultDelayMs() );
  nextResult->heal( amount, severity, flag );
  addResultToActor( effectTarget, nextResult );
}

void ActionResultBuilder::restoreMP( Entity::CharaPtr& target, Entity::CharaPtr& restoringTarget, uint32_t amount, Common::ActionResultFlag flag )
{
  ActionResultPtr nextResult = make_ActionResult( restoringTarget, getResultDelayMs() ); // restore mp source actor
  nextResult->restoreMP( amount, flag );
  addResultToActor( target, nextResult );
}

void ActionResultBuilder::damage( Entity::CharaPtr& effectTarget, Entity::CharaPtr& damagingTarget, uint32_t amount, Common::ActionHitSeverityType severity, Common::ActionResultFlag flag )
{
  ActionResultPtr nextResult = make_ActionResult( damagingTarget, getResultDelayMs() );
  nextResult->damage( amount, severity, flag );
  addResultToActor( damagingTarget, nextResult );
}

void ActionResultBuilder::startCombo( Entity::CharaPtr& target, uint16_t actionId )
{
  ActionResultPtr nextResult = make_ActionResult( target, 0 );
  nextResult->startCombo( actionId );
  addResultToActor( target, nextResult );
}

void ActionResultBuilder::comboSucceed( Entity::CharaPtr& target )
{
  ActionResultPtr nextResult = make_ActionResult( target, 0 );
  nextResult->comboSucceed();
  addResultToActor( target, nextResult );
}

void ActionResultBuilder::applyStatusEffect( Entity::CharaPtr& target, uint16_t statusId, uint8_t param )
{
  ActionResultPtr nextResult = make_ActionResult( target, 0 );
  nextResult->applyStatusEffect( statusId, param );
  addResultToActor( target, nextResult );
}

void ActionResultBuilder::mount( Entity::CharaPtr& target, uint16_t mountId )
{
  ActionResultPtr nextResult = make_ActionResult( target, getResultDelayMs() );
  nextResult->mount( mountId );
  addResultToActor( target, nextResult );
}

void ActionResultBuilder::sendActionResults( const std::vector< Entity::CharaPtr >& targetList )
{
  Logger::debug( "EffectBuilder result: " );
  Logger::debug( "Targets afflicted: {}", targetList.size() );

  do // we want to send at least one packet even nothing is hit so other players can see
  {
    auto packet = createActionResultPacket( targetList );
    server().queueForPlayers( m_sourceChara->getInRangePlayerIds( true ), packet );
  }
  while( !m_actorResultsMap.empty() );
}

std::shared_ptr< FFXIVPacketBase > ActionResultBuilder::createActionResultPacket( const std::vector< Entity::CharaPtr >& targetList )
{
  auto remainingTargetCount = targetList.size();
  auto& taskMgr = Common::Service< World::Manager::TaskMgr >::ref();
  auto& teriMgr = Common::Service< Sapphire::World::Manager::TerritoryMgr >::ref();
  auto zone = teriMgr.getTerritoryByGuId( m_sourceChara->getTerritoryId() );

  if( remainingTargetCount > 1 ) // use AoeEffect packets
  {
    auto effectPacket = std::make_shared< EffectPacket >( m_sourceChara->getId(), targetList[ 0 ]->getId(), m_actionId );
    effectPacket->setRotation( Common::Util::floatToUInt16Rot( m_sourceChara->getRot() ) );
    effectPacket->setRequestId( m_requestId );
    effectPacket->setResultId( m_resultId );

    uint8_t targetIndex = 0;
    for( auto it = m_actorResultsMap.begin(); it != m_actorResultsMap.end(); )
    {
      // get all effect results for an actor
      auto actorResultList = it->second;

      for( auto& result : actorResultList )
      {
        auto effect = result->getCalcResultParam();

        // if effect result is a source/caster effect
        if( result->getTarget() == m_sourceChara )
          effectPacket->addSourceEffect( effect );
        else
        {
          effectPacket->addTargetEffect( effect, result->getTarget()->getId() );
          taskMgr.queueTask( Sapphire::World::makeActionIntegrityTask( m_resultId, result->getTarget(), 1000 ) );
        }

        zone->addActionResult( std::move( result ) );

      }

      actorResultList.clear();
      it = m_actorResultsMap.erase( it );
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
    effectPacket->setRequestId( m_requestId );
    effectPacket->setResultId( m_resultId );

    for( auto it = m_actorResultsMap.begin(); it != m_actorResultsMap.end(); )
    {
      // get all effect results for an actor
      auto actorResultList = it->second;

      for( auto& result : actorResultList )
      {
        auto effect = result->getCalcResultParam();

        // if effect result is a source/caster effect
        if( result->getTarget() == m_sourceChara )
          effectPacket->addSourceEffect( effect );
        else
        {
          effectPacket->addTargetEffect( effect );
          taskMgr.queueTask( Sapphire::World::makeActionIntegrityTask( m_resultId, result->getTarget(), 1000 ) );
        }

        zone->addActionResult( std::move( result ) );
      }

      actorResultList.clear();
      it = m_actorResultsMap.erase( it );
    }

    m_actorResultsMap.clear();

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
    effectPacket->data().RequestId = m_requestId;
    effectPacket->data().ResultId = m_resultId;

    m_actorResultsMap.clear();

    return effectPacket;
  }
}