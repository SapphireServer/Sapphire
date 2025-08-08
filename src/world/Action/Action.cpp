#include "Action.h"

#include <Inventory/Item.h>

#include <Exd/ExdData.h>
#include <Util/Util.h>
#include <Util/UtilMath.h>
#include "Script/ScriptMgr.h"

#include <Math/CalcStats.h>

#include "Actor/Player.h"
#include "Actor/BNpc.h"

#include "Territory/Territory.h"

#include "Manager/PlayerMgr.h"
#include "Manager/MgrUtil.h"
#include "Manager/TerritoryMgr.h"
#include "Manager/PartyMgr.h"

#include "Session.h"
#include "Network/GameConnection.h"
#include <Network/CommonActorControl.h>
#include "Network/PacketWrappers/ActorControlPacket.h"
#include "Network/PacketWrappers/ActorControlSelfPacket.h"
#include "Network/PacketWrappers/ActorControlTargetPacket.h"
#include "Network/Util/PacketUtil.h"

#include <Logging/Logger.h>

#include <Util/ActorFilter.h>
#include <Service.h>
#include "WorldServer.h"

#include "StatusEffect/StatusEffect.h"

#include "Job/Warrior.h"
#include "Job/Bard.h"

using namespace Sapphire;
using namespace Sapphire::Common;
using namespace Sapphire::Network;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets;
using namespace Sapphire::Network::Packets::WorldPackets::Server;
using namespace Sapphire::Network::ActorControl;
using namespace Sapphire::World;
using namespace Sapphire::World::Manager;


Action::Action::Action( Entity::CharaPtr caster, uint32_t actionId, uint16_t requestId ) :
  Action( std::move( caster ), actionId, requestId, nullptr )
{
}

Action::Action::Action( Entity::CharaPtr caster, uint32_t actionId, uint16_t requestId,
                        std::shared_ptr< Excel::ExcelStruct< Excel::Action > > actionData ) :
  m_pSource( std::move( caster ) ),
  m_actionData( std::move( actionData ) ),
  m_id( actionId ),
  m_targetId( 0 ),
  m_startTime( 0 ),
  m_interruptType( Common::ActionInterruptType::None ),
  m_requestId( requestId ),
  m_actionKind( Common::ActionKind::ACTION_KIND_NORMAL )
{
}

uint32_t Action::Action::getId() const
{
  return m_id;
}

uint32_t Action::Action::getResultId() const
{
  return m_resultId;
}

std::shared_ptr< Excel::ExcelStruct< Excel::Action > > Action::Action::getActionData() const
{
  return m_actionData;
}

bool Action::Action::init()
{
  if( !m_actionData )
  {
    // need to get actionData
    auto& exdData = Common::Service< Data::ExdData >::ref();

    auto actionData = exdData.getRow< Excel::Action >( m_id );
    if( !actionData )
      throw std::runtime_error( "No actiondata found!" );

    m_actionData = actionData;
  }
  auto teriMgr = Common::Service< Manager::TerritoryMgr >::ref();
  auto zone = teriMgr.getTerritoryByGuId( m_pSource->getTerritoryId() );
  m_resultId = zone->getNextActionResultId();

  m_castTimeMs = static_cast< uint32_t >( m_actionData->data().CastTime * 100 );
  m_recastTimeMs = static_cast< uint32_t >( m_actionData->data().RecastTime * 100 );
  m_cooldownGroup = m_actionData->data().RecastGroup;
  m_range = m_actionData->data().SelectRange;
  m_effectRange = m_actionData->data().EffectRange;
  m_effectWidth = m_actionData->data().EffectWidth;
  m_category = static_cast< Common::ActionCategory >( m_actionData->data().Category );
  m_castType = static_cast< Common::CastType >( m_actionData->data().EffectType );
  m_aspect = static_cast< Common::ActionAspect >( m_actionData->data().AttackType );

  // todo: move this to bitset
  m_canTargetSelf = m_actionData->data().SelectMyself;
  m_canTargetParty = m_actionData->data().SelectParty;
  m_canTargetFriendly = m_actionData->data().SelectAlliance;
  m_canTargetHostile = m_actionData->data().SelectEnemy;
  // todo: this one doesn't look right based on whats in that col, probably has shifted
  m_canTargetDead = m_actionData->data().SelectCorpse;

  // a default range is set by the game for the class/job
  if( m_range == -1 )
  {
    switch( static_cast< Common::ClassJob >( m_actionData->data().UseClassJob ) )
    {
      case Common::ClassJob::Bard:
      case Common::ClassJob::Archer:
      case Common::ClassJob::Machinist:
        m_range = 25;
        break;
      default:
        m_range = 3;
        break;
    }
  }

  m_primaryCostType = static_cast< Common::ActionPrimaryCostType >( m_actionData->data().CostType );
  m_primaryCost = m_actionData->data().CostValue;

  if( !m_actionData->data().SelectGround )
  {
    // override pos to target position
    // todo: this is kinda dirty
    for( auto& actor : m_pSource->getInRangeActors() )
    {
      if( actor->getId() == m_targetId )
      {
        m_pos = actor->getPos();
        break;
      }
    }
  }

  // todo: add missing rows for secondaryCostType/secondaryCostType and rename the current rows to primaryCostX

  if( ActionLut::validEntryExists( static_cast< uint16_t >( getId() ) ) )
  {
    m_lutEntry = ActionLut::getEntry( static_cast< uint16_t >( getId() ) );
  }
  else
  {
    m_lutEntry.curePotency = 0;
    m_lutEntry.restoreMPPercentage = 0;
    m_lutEntry.potency = 0;
    m_lutEntry.comboPotency = 0;
    m_lutEntry.flankPotency = 0;
    m_lutEntry.rearPotency = 0;
    m_lutEntry.frontPotency = 0;
    m_lutEntry.nextCombo.clear();
    m_lutEntry.aggroModifier = 1;
  }

  m_actionResultBuilder = make_ActionResultBuilder( m_pSource, getId(), m_lutEntry.aggroModifier, m_resultId, m_requestId );
  addDefaultActorFilters();

  return true;
}

void Action::Action::setPos( const Common::FFXIVARR_POSITION3& pos )
{
  m_pos = pos;
}

const Common::FFXIVARR_POSITION3& Action::Action::getPos() const
{
  return m_pos;
}

void Action::Action::setTargetId( uint64_t targetId )
{
  m_targetId = targetId;
}

uint64_t Action::Action::getTargetId() const
{
  return m_targetId;
}

bool Action::Action::hasClientsideTarget() const
{
  return m_targetId > 0xFFFFFFFF;
}

bool Action::Action::isInterrupted() const
{
  return m_interruptType != Common::ActionInterruptType::None;
}

Common::ActionInterruptType Action::Action::getInterruptType() const
{
  return m_interruptType;
}

void Action::Action::setInterrupted( Common::ActionInterruptType type )
{
  m_interruptType = type;
}

uint32_t Action::Action::getCastTime() const
{
  return m_castTimeMs;
}

void Action::Action::setCastTime( uint32_t castTime )
{
  m_castTimeMs = castTime;
}

bool Action::Action::hasCastTime() const
{
  return m_castTimeMs > 0;
}

bool Action::Action::isAbility() const
{
  return m_category == ActionCategory::Ability;
}

bool Action::Action::isWeaponskill() const
{
  return m_category == ActionCategory::Weaponskill;
}

Entity::CharaPtr Action::Action::getSourceChara() const
{
  return m_pSource;
}

bool Action::Action::update()
{
  // action has not been started yet
  if( m_startTime == 0 )
    return false;

  if( isInterrupted() )
  {
    interrupt();
    return true;
  }

  if( !hasClientsideTarget() )
  {
    // todo: check if the target is still in range
  }

  auto tickCount = static_cast< time_t >( Common::Util::getTimeMs() );
  auto startTime = static_cast< time_t >( m_startTime );
  uint64_t castTime = m_castTimeMs;

  if( auto player = m_pSource->getAsPlayer() )
  {
    auto lastActionTick = static_cast< time_t >( player->getLastActionTick() );
    uint32_t lastTickMs = 0;
    if( lastActionTick > 0 )
    {
      lastTickMs = static_cast< uint32_t >( std::difftime( tickCount, lastActionTick ) );
      if( lastTickMs > 100 ) //max 100ms
        lastTickMs = 100;
    }

    player->setLastActionTick( tickCount );
    uint64_t delayMs = 100 - lastTickMs;
    castTime = ( m_castTimeMs + delayMs );
    m_castTimeRestMs = static_cast< uint64_t >( m_castTimeMs ) - static_cast< uint64_t >( std::difftime( tickCount, startTime ) );
  }

  if( !hasCastTime() || std::difftime( tickCount, startTime ) > castTime )
  {
    execute();
    return true;
  }

  if( !m_pTarget && m_targetId != 0 )
  {
    // try to search for the target actor
    for( const auto& actor : m_pSource->getInRangeActors( true ) )
    {
      if( actor->getId() == m_targetId )
      {
        m_pTarget = actor->getAsChara();
        break;
      }
    }
  }

  if( m_pTarget && !m_pTarget->isAlive() )
  {
    // interrupt the cast if target died
    setInterrupted( Common::ActionInterruptType::RegularInterrupt );
    interrupt();
    return true;
  }

  return false;
}

void Action::Action::start()
{
  assert( m_pSource );
  m_startTime = Common::Util::getTimeMs();

  auto player = m_pSource->getAsPlayer();

  if( hasCastTime() )
  {
    auto castPacket = makeZonePacket< Server::FFXIVIpcActorCast >( m_pSource->getId() );
    auto& data = castPacket->data();

    data.Action = static_cast< uint16_t >( m_id );
    data.ActionKey = m_id;
    data.ActionKind = m_actionKind;
    data.CastTime = static_cast< float >( m_castTimeMs ) / 1000.f;
    data.Target = static_cast< uint32_t >( m_targetId );

    data.TargetPos[ 0 ] = Common::Util::floatToUInt16( m_pSource->getPos().x );
    data.TargetPos[ 1 ] = Common::Util::floatToUInt16( m_pSource->getPos().y );
    data.TargetPos[ 2 ] = Common::Util::floatToUInt16( m_pSource->getPos().z );
    data.Dir = m_pSource->getRot();

    server().queueForPlayers( m_pSource->getInRangePlayerIds( m_pSource->isPlayer() ), castPacket );

    if( player )
      player->setCondition( PlayerCondition::Casting );
  }
  
  // todo: m_recastTimeMs needs to be adjusted for player sks/sps
  auto actionStartPkt = makeActorControlSelf( m_pSource->getId(), ActorControlType::ActionStart, m_cooldownGroup, getId(), m_recastTimeMs / 10 );

  if( player )
  {
    player->setRecastGroup( m_cooldownGroup, static_cast< float >( m_castTimeMs ) / 1000.f );
    server().queueForPlayer( player->getCharacterId(), actionStartPkt );
  }

  onStart();

  // instantly finish cast if there's no cast time
  if( !hasCastTime() && !isInterrupted() )
    execute();
}

void Action::Action::onStart()
{
  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();
  auto player = m_pSource->getAsPlayer();

  // check the lut too and see if we have something usable, otherwise cancel the cast
  if( !scriptMgr.onStart( *this ) && !ActionLut::validEntryExists( static_cast< uint16_t >( getId() ) ) )
  {
    // script not implemented and insufficient lut data (no potencies)
    interrupt();

    if( player )
    {
      Manager::PlayerMgr::sendUrgent( *player, "Action not implemented, missing script/lut entry for action#{0}", getId() );
      player->setCurrentAction( nullptr );
    }

    return;
  }

}

void Action::Action::interrupt()
{
  assert( m_pSource );
  if( m_interruptType == ActionInterruptType::None )
    m_interruptType = ActionInterruptType::RegularInterrupt;
  // things that aren't players don't care about cooldowns and state flags
  if( m_pSource->isPlayer() )
  {
    auto pPlayer = m_pSource->getAsPlayer();

    // todo: reset cooldown for actual player

    // reset state flag
    //player->unsetStateFlag( PlayerStateFlag::Occupied1 );
    pPlayer->setLastActionTick( 0 );
    pPlayer->removeCondition( PlayerCondition::Casting );
  }

  if( hasCastTime() )
  {
    uint8_t interruptEffect = 0;
    if( m_interruptType == ActionInterruptType::DamageInterrupt )
      interruptEffect = 1;

    // Note: When cast interrupt from taking too much damage, set the last value to 1.
    // This enables the cast interrupt effect.
    auto control = makeActorControl( m_pSource->getId(), ActorControlType::CastInterrupt, 0x219, 1, m_id, interruptEffect );

    server().queueForPlayers( m_pSource->getInRangePlayerIds( true ), control );
  }

  onInterrupt();

}

void Action::Action::onInterrupt()
{
  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();
  scriptMgr.onInterrupt( *this );
}

void Action::Action::execute()
{
  assert( m_pSource );
  // subtract costs first, if somehow the caster stops meeting those requirements cancel the cast
  if( !consumeResources() )
  {
    interrupt();
    return;
  }

  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();

  if( hasCastTime() && m_pSource->isPlayer() )
  {
    auto pPlayer = m_pSource->getAsPlayer();
    pPlayer->setLastActionTick( 0 );
    pPlayer->removeCondition( PlayerCondition::Casting );
  }

  if( isCorrectCombo() )
  {
    auto player = m_pSource->getAsPlayer();
    Manager::PlayerMgr::sendDebug( *player, "action combo success from action#{0}", player->getLastComboActionId() );
  }

  if( !hasClientsideTarget()  )
    buildActionResults();
  else if( auto player = m_pSource->getAsPlayer() )
    scriptMgr.onEObjHit( *player, m_targetId, getId() );

  // set currently casted action as the combo action if it interrupts a combo
  // ignore it otherwise (ogcds, etc.)
  if( isWeaponskill() && !m_actionData->data().ComboContinue )
  {
    // potential combo starter or correct combo from last action, must hit something to progress combo
    if( !m_hitActors.empty() && ( !isComboAction() || isCorrectCombo() ) )
      m_pSource->setLastComboActionId( getId() );
    else // clear last combo action if the combo breaks
      m_pSource->setLastComboActionId( 0 );
  }
}

std::pair< uint32_t, Common::CalcResultType > Action::Action::calcDamage( uint32_t potency )
{
  // todo: what do for npcs?
  auto wepDmg = 1.f;

  if( auto player = m_pSource->getAsPlayer() )
  {
    auto item = player->getEquippedWeapon();
    assert( item );

    auto role = player->getRole();
    if( role == Common::Role::RangedMagical || role == Common::Role::Healer )
      wepDmg = item->getMagicalDmg();
    else
      wepDmg = item->getPhysicalDmg();

    // is auto attack
    if( getId() == 7 || getId() == 8 )
      return Math::CalcStats::calcAutoAttackDamage( *m_pSource->getAsPlayer() );
  }

  return Math::CalcStats::calcActionDamage( *m_pSource, potency, wepDmg );
}

std::pair< uint32_t, Common::CalcResultType > Action::Action::calcHealing( uint32_t potency )
{
  auto wepDmg = 1.f;

  if( auto player = m_pSource->getAsPlayer() )
  {
    auto item = player->getEquippedWeapon();
    assert( item );

    auto role = player->getRole();
    if( role == Common::Role::RangedMagical || role == Common::Role::Healer )
      wepDmg = item->getMagicalDmg();
    else
      wepDmg = item->getPhysicalDmg();
  }

  return Math::CalcStats::calcActionHealing( *m_pSource, potency, wepDmg );
}

void Action::Action::buildActionResults()
{
  snapshotAffectedActors( m_hitActors );

  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();
  auto hasLutEntry = hasValidLutEntry();
  auto hasScript = scriptMgr.onExecute( *this );

  if( !hasScript && !hasLutEntry )
  {
    if( auto player = m_pSource->getAsPlayer() )
      Manager::PlayerMgr::sendUrgent( *player, "missing lut entry for action#{}", getId() );
    return;
  }

  if( !hasScript )
    m_enableGenericHandler = true;

  Network::Util::Packet::sendHudParam( *m_pSource );

  if( !m_enableGenericHandler || !hasLutEntry || m_hitActors.empty() )
  {
    scriptMgr.onAfterBuildEffect( *this );
    // send any effect packet added by script or an empty one just to play animation for other players
    m_actionResultBuilder->sendActionResults( m_hitActors );
    return;
  }

  // no script exists but we have a valid lut entry
  if( auto player = getSourceChara()->getAsPlayer() )
  {
    Manager::PlayerMgr::sendDebug( *player, "Hit target: pot: {} (c: {}, f: {}, r: {}), heal pot: {}, mpp: {}",
                                   m_lutEntry.potency, m_lutEntry.comboPotency, m_lutEntry.flankPotency, m_lutEntry.rearPotency,
                                   m_lutEntry.curePotency, m_lutEntry.restoreMPPercentage );
    Manager::PlayerMgr::sendDebug( *player, "mod: {}", m_lutEntry.aggroModifier );
  }

  // when aoe, these effects are in the target whatever is hit first
  bool shouldRestoreMP = true;
  bool shouldApplyComboSucceedEffect = true;

  for( auto& actor : m_hitActors )
  {
    if( m_lutEntry.potency > 0 )
    {
      auto dmg = calcDamage( isCorrectCombo() ? m_lutEntry.comboPotency : m_lutEntry.potency );
      m_actionResultBuilder->damage( m_pSource, actor, dmg.first, dmg.second );

      if( isCorrectCombo() && shouldApplyComboSucceedEffect )
      {
        m_actionResultBuilder->comboSucceed( m_pSource );
        shouldApplyComboSucceedEffect = false;
      }

      if( !isComboAction() || isCorrectCombo() )
      {
        if( m_lutEntry.curePotency > 0 ) // actions with self heal
        {
          auto heal = calcHealing( m_lutEntry.curePotency );
          m_actionResultBuilder->heal( actor, m_pSource, heal.first, heal.second, Common::ActionResultFlag::EffectOnSource );
        }

        if( m_lutEntry.restoreMPPercentage > 0 && shouldRestoreMP )
        {
          m_actionResultBuilder->restoreMP( actor, m_pSource, m_pSource->getMaxMp() * m_lutEntry.restoreMPPercentage / 100, Common::ActionResultFlag::EffectOnSource );
          shouldRestoreMP = false;
        }

        if( !m_lutEntry.nextCombo.empty() ) // if we have a combo action followup
          m_actionResultBuilder->startCombo( m_pSource, getId() ); // this is on all targets hit
      }
    }
    else if( m_lutEntry.curePotency > 0 )
    {
      auto heal = calcHealing( m_lutEntry.curePotency );
      m_actionResultBuilder->heal( actor, actor, heal.first, heal.second );

      if( m_lutEntry.restoreMPPercentage > 0 && shouldRestoreMP )
      {
        m_actionResultBuilder->restoreMP( actor, m_pSource, m_pSource->getMaxMp() * m_lutEntry.restoreMPPercentage / 100, Common::ActionResultFlag::EffectOnSource );
        shouldRestoreMP = false;
      }
    }
    else if( m_lutEntry.restoreMPPercentage > 0 && shouldRestoreMP )
    {
      m_actionResultBuilder->restoreMP( actor, m_pSource, m_pSource->getMaxMp() * m_lutEntry.restoreMPPercentage / 100, Common::ActionResultFlag::EffectOnSource );
      shouldRestoreMP = false;
    }
  }

  // If we hit an enemy
  if( !m_hitActors.empty() && getHitChara()->isHostile( *m_pSource ) )
  {
    m_pSource->removeStatusEffectByFlag( Common::StatusEffectFlag::RemoveOnSuccessfulHit );
  }

  handleJobAction();
  handleStatusEffects();

  scriptMgr.onAfterBuildEffect( *this );

  m_actionResultBuilder->sendActionResults( m_hitActors );

  // TODO: disabled, reset kills our queued actions
  // at this point we're done with it and no longer need it
  // m_effectBuilder.reset();
}

void Action::Action::applyStatusEffect( bool isSelf, Entity::CharaPtr& target, Entity::CharaPtr& source, World::Action::StatusEntry& status, bool statusToSource )
{
  auto pActionBuilder = getActionResultBuilder();

  if( !pActionBuilder )
    return;

  auto hasSameStatus = false;
  auto hasSameStatusFromSameCaster = false;
  Sapphire::StatusEffect::StatusEffectPtr referenceStatus = nullptr;

  for( auto const& entry : statusToSource ? source->getStatusEffectMap() : target->getStatusEffectMap() )
  {
    auto statusEffect = entry.second;
    if( statusEffect->getId() == status.id )
    {
      hasSameStatus = true;
      
      if( !referenceStatus )
        referenceStatus = statusEffect;
      
      if( statusEffect->getSrcActorId() == source->getId() )
      {
        hasSameStatusFromSameCaster = true;
        referenceStatus = statusEffect;
        break;;
      }
    }
  }

  auto policy = getStatusRefreshPolicy( status.statusRefreshPolicy, isSelf );
  switch( policy )
  {
    case Common::StatusRefreshPolicy::Stack:
    {
      pActionBuilder->applyStatusEffect( target, status.id, status.duration, 0, std::move( status.modifiers ), status.flag, statusToSource, false );
      break;
    }
    case Common::StatusRefreshPolicy::ReplaceOrApply:
    {
      if( (status.flag & static_cast< uint32_t >( Common::StatusEffectFlag::ReplaceSameCaster ) && hasSameStatusFromSameCaster) || hasSameStatus )
        pActionBuilder->replaceStatusEffect( referenceStatus, target, status.id, status.duration, 0, std::move( status.modifiers ), status.flag, statusToSource );
      else
        pActionBuilder->applyStatusEffect( target, status.id, status.duration, 0, std::move( status.modifiers ), status.flag, statusToSource, true );
      break;
    }
    case Common::StatusRefreshPolicy::Extend:
    case Common::StatusRefreshPolicy::ExtendOrApply:
    {
      int64_t remainingDuration = 0;
      if( hasSameStatus )
      {
        remainingDuration = static_cast< int64_t >( referenceStatus->getDuration() ) - ( Common::Util::getTimeMs() - referenceStatus->getStartTimeMs() );
        if( remainingDuration < 0 )
          remainingDuration = 0;
      }

      if( hasSameStatus || policy == Common::StatusRefreshPolicy::ExtendOrApply )
      {
        pActionBuilder->applyStatusEffect( target, status.id, std::min( status.duration + remainingDuration, static_cast< int64_t >( status.maxDuration ) ), 0, std::move( status.modifiers ), status.flag, statusToSource, true );
      }
      break;
    }
    case Common::StatusRefreshPolicy::Reject:
    {
      if( !hasSameStatus )
      {
        pActionBuilder->applyStatusEffect( target, status.id, status.duration, 0, std::move( status.modifiers ), status.flag, statusToSource, true );
      }
      else
      {
        // add function to ActionBuilder for No Effect effect
      }
      break;
    }
    case Common::StatusRefreshPolicy::Custom:
    {
      // script should handle it
      break;
    }
  }
}

void Action::Action::handleStatusEffects()
{
  auto pActionBuilder = getActionResultBuilder();

  if( !pActionBuilder )
    return;

  if( isComboAction() && !isCorrectCombo() )
    return;

  // handle caster statuses
  if( !m_lutEntry.statuses.caster.empty() )
  {
    for( auto& status : m_lutEntry.statuses.caster )
    {
      /*if( m_hitActors[ 0 ] ) // might need a firstValidVictim?
        applyStatusEffect( true, m_hitActors[ 0 ], m_pSource, status, true );
        // pActionBuilder->applyStatusEffectSelf( status.id, status.duration, 0, std::move( status.modifiers ), status.flag, true ); // statusToSource true
      else if( m_lutEntry.potency == 0 )*/
      applyStatusEffect( true, m_pSource, m_pSource, status, true );
        // pActionBuilder->applyStatusEffectSelf( status.id, status.duration, 0, std::move( status.modifiers ), status.flag, true );
    }
  }

  // handle hit actor statuses
  if( !m_lutEntry.statuses.target.empty() && !m_hitActors.empty() )
  {
    for( auto& actor : m_hitActors )
    {
      for( auto& status : m_lutEntry.statuses.target )
      {
        applyStatusEffect( false, actor, m_pSource, status );
        // pActionBuilder->applyStatusEffect( actor, status.id, status.duration, 0, std::move( status.modifiers ), status.flag, true );
      }
    }
  }
}

void Action::Action::handleJobAction()
{
  switch( m_pSource->getClass() )
  {
    case ClassJob::Warrior:
    {
      Warrior::onAction( *m_pSource->getAsPlayer(), *this );
      break;
    }
    case ClassJob::Archer:
    case ClassJob::Bard:
    {
      Bard::onAction( *m_pSource->getAsPlayer(), *this );
      break;
    }
  }
}

bool Action::Action::preCheck()
{
  if( auto player = m_pSource->getAsPlayer() )
  {
    if( !playerPreCheck( *player ) )
      return false;
  }

  return true;
}

bool Action::Action::playerPreCheck( Entity::Player& player )
{
  if( !player.isAlive() )
    return false;

  // npc actions/non player actions
  //if( m_actionData->data().UseClassJob == -1 /* dunno what this is in old data && !m_actionData->data().isRoleAction*/ )
  //  return false;

  //if( player.getLevel() < m_actionData->data().UseClassJob )
  //  return false;

  //auto currentClass = player.getClass();
  //auto actionClass = static_cast< Common::ClassJob >( m_actionData->data().UseClassJob );

  //if( actionClass != Common::ClassJob::Adventurer && currentClass != actionClass /* dunno what this is in old data && !m_actionData->data().isRoleAction*/ )
  //{
    // check if not a base class action
    //auto& exdData = Common::Service< Data::ExdData >::ref();

    //auto classJob = exdData.getRow< Excel::ClassJob >( static_cast< uint8_t >( currentClass ) );
    //if( !classJob )
    //  return false;

    //if( classJob->data().MainClass != m_actionData->data().UseClassJob )
    //  return false;
  //}

  //if( !m_actionData->data().SelectMyself && getTargetId() == m_pSource->getId() )
  //  return false;
  
  // todo: does this need to check for party/alliance stuff or it's just same type?
  // todo: m_pTarget doesn't exist at this stage because we only fill it when we snapshot targets
//  if( !m_actionData->canTargetFriendly && m_pSource->getObjKind() == m_pTarget->getObjKind() )
//    return false;
//
//  if( !m_actionData->canTargetHostile && m_pSource->getObjKind() != m_pTarget->getObjKind() )
//    return false;

  // todo: party/dead validation

  // validate range


  if( !hasResources() )
    return false;

  return true;
}

uint32_t Action::Action::getAdditionalData() const
{
  return m_additionalData;
}

void Action::Action::setAdditionalData( uint32_t data )
{
  m_additionalData = data;
}

// TODO: write something that can traverse comboparent in action parse
bool Action::Action::isCorrectCombo() const
{
  auto lastActionId = m_pSource->getLastComboActionId();

  if( lastActionId == 0 )
    return false;

  return m_actionData->data().ComboParent == lastActionId;
}

bool Action::Action::isComboAction() const
{
  return m_actionData->data().ComboParent != 0;
}

bool Action::Action::primaryCostCheck( bool subtractCosts )
{
  switch( m_primaryCostType )
  {
    case Common::ActionPrimaryCostType::TacticsPoints:
    case Common::ActionPrimaryCostType::TacticsPoints1:
    case Common::ActionPrimaryCostType::Sprint:
    {
      auto curTp = m_pSource->getTp();

      if( curTp < m_primaryCost )
        return false;

      if( subtractCosts )
        m_pSource->setTp( curTp - m_primaryCost );

      return true;
    }

    case Common::ActionPrimaryCostType::MagicPoints:
    {
      auto curMp = m_pSource->getMp();

      auto cost = Math::CalcStats::calculateMpCost( *m_pSource, m_primaryCost );

      if( curMp < static_cast< uint32_t >( cost ) )
        return false;

      if( subtractCosts )
        m_pSource->setMp( curMp - static_cast< uint32_t >( cost ) );

      return true;
    }

    case Common::ActionPrimaryCostType::StatusEffect:
    {
      if( !m_pSource->hasStatusEffect( m_primaryCost ) )
        return false;

      if( subtractCosts )
        m_pSource->removeSingleStatusEffectById( m_primaryCost );

      return true;
    }

    // free casts, likely just pure ogcds
    case Common::ActionPrimaryCostType::None:
    {
      return true;
    }

    default:
      Logger::debug( "Unknown action cost type: {}", static_cast< uint16_t >( m_primaryCostType ) );
      return false;
  }
}

bool Action::Action::secondaryCostCheck( bool subtractCosts )
{
  // todo: these need to be mapped
  return true;
}

bool Action::Action::hasResources()
{
  return primaryCostCheck( false ) && secondaryCostCheck( false );
}

bool Action::Action::consumeResources()
{
  return primaryCostCheck( true ) && secondaryCostCheck( true );
}

bool Action::Action::snapshotAffectedActors( std::vector< Entity::CharaPtr >& actors )
{
  for( const auto& actor : m_pSource->getInRangeActors( true ) )
  {
    // check for initial target validity based on flags in action exd (pc/enemy/etc.)
    if( !preFilterActor( *actor ) )
      continue;


    bool snapshotActor = true;
    for( const auto& filter : m_actorFilters )
    {
      if( !filter->conditionApplies( *actor ) )
      {
        snapshotActor = false;
        break;
      }
    }

    if( snapshotActor )
      actors.push_back( actor->getAsChara() );
  }

  if( auto player = m_pSource->getAsPlayer() )
  {
    Manager::PlayerMgr::sendDebug( *player, "Hit {} actors with {} filters", actors.size(), m_actorFilters.size() );
    for( const auto& actor : actors )
    {
      Manager::PlayerMgr::sendDebug( *player, "hit actor#{}", actor->getId() );
    }
  }

  return !actors.empty();
}

void Action::Action::addActorFilter( World::Util::ActorFilterPtr filter )
{
  m_actorFilters.push_back( std::move( filter ) );
}

void Action::Action::addDefaultActorFilters()
{
  switch( m_castType )
  {
    case Common::CastType::SingleTarget:
    {
      auto filter = std::make_shared< World::Util::ActorFilterSingleTarget >( static_cast< uint32_t >( m_targetId ) );
      addActorFilter( filter );
      break;
    }

    case Common::CastType::Circle:
    {
      auto filter = std::make_shared< World::Util::ActorFilterInRange >( m_pos, m_effectRange );
      addActorFilter( filter );
      break;
    }
    case Common::CastType::Box:
    {
        auto filter = std::make_shared< World::Util::ActorFilterBox >( m_pos, m_effectWidth, m_effectRange );
        addActorFilter( filter );
        break;
    }
    case Common::CastType::Cone:
    {
      ConeEntry shapeEntry = { 0, 0 };
      if( ActionShapeLut::validConeEntryExists( static_cast< uint16_t >( getId() ) ) )
      {
        shapeEntry = ActionShapeLut::getConeEntry( static_cast< uint16_t >( getId() ) );
      }

      auto rangeFilter = std::make_shared< World::Util::ActorFilterInRange >( m_pSource->getPos(), m_range );
      addActorFilter( rangeFilter );
      auto coneFilter = std::make_shared< World::Util::ActorFilterCone >( m_pSource->getPos(), m_pos, shapeEntry.startAngle, shapeEntry.endAngle );
      addActorFilter( coneFilter );
      break;
    }

    default:
    {
      Logger::error( "[{}] Action#{} has CastType#{} but that cast type is unhandled. Cancelling cast.",
                     m_pSource->getId(), getId(), static_cast< uint8_t >( m_castType ) );

      interrupt();
    }
  }
}

bool Action::Action::preFilterActor( Entity::GameObject& actor ) const
{
  if( m_castType == Common::CastType::SingleTarget ) // client filters any single target action by itself
    return true;

  auto kind = actor.getObjKind();
  auto chara = actor.getAsChara();

  // todo: are there any server side eobjs that players can hit?
  if( kind != ObjKind::BattleNpc && kind != ObjKind::Player )
    return false;

  bool actorApplicable = false;
  switch( m_lutEntry.targetFilter )
  {
    case Common::TargetFilter::All:
    {
      actorApplicable = true;
      break;
    }
    case Common::TargetFilter::Players:
    {
      actorApplicable = kind == ObjKind::Player;
      break;
    }
    case Common::TargetFilter::Allies:
    {
      // Todo: Make this work for allies properly
      actorApplicable = kind != ObjKind::BattleNpc;
      break;
    }
    case Common::TargetFilter::Party:
    {
      auto pPlayer = m_pSource->getAsPlayer();
      if( pPlayer && pPlayer->getPartyId() != 0 )
      {
        auto& partyMgr = Common::Service< World::Manager::PartyMgr >::ref();
        // Get party members
        auto pParty = partyMgr.getParty( pPlayer->getPartyId() );
        assert( pParty );

        for( const auto& id : pParty->MemberId )
        {
          if( id == actor.getId() )
          {
            actorApplicable = true;
            break;
          }
        }
      }
      break;
    }
    case Common::TargetFilter::Enemies:
    {
      actorApplicable = kind == ObjKind::BattleNpc;
      break;
    }
  }
  
  if( chara->isAlive() && ( m_lutEntry.curePotency > 0 || m_canTargetFriendly ) && m_pSource->isFriendly( *chara ) )
    return actorApplicable;

  if( chara->isAlive() && ( m_lutEntry.potency > 0 || m_canTargetHostile ) > 0 && m_pSource->isHostile( *chara ) )
    return actorApplicable;

  return false;
}

std::vector< Entity::CharaPtr >& Action::Action::getHitCharas()
{
  return m_hitActors;
}

Entity::CharaPtr Action::Action::getHitChara()
{
  if( !m_hitActors.empty() )
    return m_hitActors.at( 0 );
  return nullptr;
}

bool Action::Action::hasValidLutEntry() const
{
  return m_lutEntry.potency != 0 || m_lutEntry.comboPotency != 0 || m_lutEntry.flankPotency != 0 || m_lutEntry.frontPotency != 0 ||
    m_lutEntry.rearPotency != 0 || m_lutEntry.curePotency != 0 || m_lutEntry.restoreMPPercentage != 0 ||
    m_lutEntry.statuses.caster.size() > 0 || m_lutEntry.statuses.target.size() > 0;
}

Action::ActionResultBuilderPtr Action::Action::getActionResultBuilder()
{
  return m_actionResultBuilder;
}

uint8_t Action::Action::getActionKind() const
{
  return m_actionKind;
}

void Action::Action::setActionKind( uint8_t actionKind )
{
  m_actionKind = actionKind;
}

uint64_t Action::Action::getCastTimeRest() const
{
  return m_castTimeRestMs;
}

void Action::Action::enableGenericHandler()
{
  m_enableGenericHandler = true;
}