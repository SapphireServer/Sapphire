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

void ActionResultBuilder::addResultToActor( Entity::CharaPtr& chara, ActionResultPtr result )
{
  auto it = m_actorResultsMap.find( chara );
  if( it == m_actorResultsMap.end() )
  {
    m_actorResultsMap[ chara ].push_back( std::move( result ) );
    return;
  }

  it->second.push_back( std::move( result ) );
}

void ActionResultBuilder::heal( Entity::CharaPtr& effectTarget, Entity::CharaPtr& healingTarget, uint32_t amount, Common::ActionHitSeverityType severity, Common::ActionResultFlag flag )
{
  ActionResultPtr nextResult = make_ActionResult( healingTarget, 0 );
  nextResult->heal( amount, severity, flag );
  addResultToActor( effectTarget, nextResult );
}

void ActionResultBuilder::restoreMP( Entity::CharaPtr& target, Entity::CharaPtr& restoringTarget, uint32_t amount, Common::ActionResultFlag flag )
{
  ActionResultPtr nextResult = make_ActionResult( restoringTarget, 0 ); // restore mp source actor
  nextResult->restoreMP( amount, flag );
  addResultToActor( target, nextResult );
}

void ActionResultBuilder::damage( Entity::CharaPtr& effectTarget, Entity::CharaPtr& damagingTarget, uint32_t amount, Common::ActionHitSeverityType severity, Common::ActionResultFlag flag )
{
  ActionResultPtr nextResult = make_ActionResult( damagingTarget, 0 );
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

void ActionResultBuilder::applyStatusEffect( Entity::CharaPtr& target, uint16_t statusId, uint32_t duration, uint8_t param, bool shouldOverride )
{
  ActionResultPtr nextResult = make_ActionResult( target, 0 );
  nextResult->applyStatusEffect( statusId, duration, *m_sourceChara, param, shouldOverride );
  addResultToActor( target, nextResult );
}

void ActionResultBuilder::applyStatusEffect( Entity::CharaPtr& target, uint16_t statusId, uint32_t duration, uint8_t param,
                                             std::vector< World::Action::StatusModifier > modifiers, uint32_t flag, bool canApplyMultipleTimes, bool shouldOverride )
{
  ActionResultPtr nextResult = make_ActionResult( target, 0 );
  nextResult->applyStatusEffect( statusId, duration, *m_sourceChara, param, modifiers, flag, canApplyMultipleTimes, shouldOverride );
  addResultToActor( target, nextResult );
}

void ActionResultBuilder::applyStatusEffectSelf( uint16_t statusId, uint32_t duration, uint8_t param, bool shouldOverride )
{
  ActionResultPtr nextResult = make_ActionResult( m_sourceChara, 0 );
  nextResult->applyStatusEffectSelf( statusId, duration, param, shouldOverride );
  addResultToActor( m_sourceChara, nextResult );
}

void ActionResultBuilder::applyStatusEffectSelf( uint16_t statusId, uint32_t duration, uint8_t param, std::vector< World::Action::StatusModifier > modifiers,
                                                 uint32_t flag, bool shouldOverride )
{
  ActionResultPtr nextResult = make_ActionResult( m_sourceChara, 0 );
  nextResult->applyStatusEffectSelf( statusId, duration, param, modifiers, flag, shouldOverride );
  addResultToActor( m_sourceChara, nextResult );
}

void ActionResultBuilder::mount( Entity::CharaPtr& target, uint16_t mountId )
{
  ActionResultPtr nextResult = make_ActionResult( target, 0 );
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
  auto targetCount = targetList.size();
  auto& taskMgr = Common::Service< World::Manager::TaskMgr >::ref();
  auto& teriMgr = Common::Service< Sapphire::World::Manager::TerritoryMgr >::ref();
  auto zone = teriMgr.getTerritoryByGuId( m_sourceChara->getTerritoryId() );

  if( targetCount > 1 ) // use AoeEffect packets
  {
    auto actionResult = std::make_shared< EffectPacket >( m_sourceChara->getId(), targetList[ 0 ]->getId(), m_actionId );
    actionResult->setRotation( Common::Util::floatToUInt16Rot( m_sourceChara->getRot() ) );
    actionResult->setRequestId( m_requestId );
    actionResult->setResultId( m_resultId );

    uint8_t targetIndex = 0;
    for( auto it = m_actorResultsMap.begin(); it != m_actorResultsMap.end(); ++it )
    {
      // get all effect results for an actor
      auto actorResultList = it->second;

      if( it->first )
        taskMgr.queueTask( World::makeActionIntegrityTask( m_resultId, it->first, actorResultList, 300 ) );

      for( auto& result : actorResultList )
      {
        auto effect = result->getCalcResultParam();
        if( result->getTarget() == m_sourceChara )
          actionResult->addSourceEffect( effect );
        else
          actionResult->addTargetEffect( effect, result->getTarget()->getId() );
      }
      targetIndex++;

      if( targetIndex == 15 )
        break;
    }

    return actionResult;
  }
  else  // use Effect for single target
  {
    uint32_t mainTargetId = targetList.empty() ? m_sourceChara->getId() : targetList[ 0 ]->getId();
    auto actionResult = std::make_shared< EffectPacket1 >( m_sourceChara->getId(), mainTargetId, m_actionId );
    actionResult->setRotation( Common::Util::floatToUInt16Rot( m_sourceChara->getRot() ) );
    actionResult->setRequestId( m_requestId );
    actionResult->setResultId( m_resultId );

    for( auto it = m_actorResultsMap.begin(); it != m_actorResultsMap.end(); ++it )
    {
      // get all effect results for an actor
      auto actorResultList = it->second;

      if( it->first )
        taskMgr.queueTask( World::makeActionIntegrityTask( m_resultId, it->first, actorResultList, 300 ) );

      for( auto& result : actorResultList )
      {
        auto effect = result->getCalcResultParam();
        if( result->getTarget() == m_sourceChara && result->getCalcResultParam().Type != Common::ActionEffectType::CALC_RESULT_TYPE_SET_STATUS_ME )
          actionResult->addSourceEffect( effect );
        else
          actionResult->addTargetEffect( effect );
      }
    }

    m_actorResultsMap.clear();
    return actionResult;
  }
}