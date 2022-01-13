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

#include "Session.h"
#include "Network/GameConnection.h"
#include <Network/CommonActorControl.h>
#include "Network/PacketWrappers/ActorControlPacket.h"
#include "Network/PacketWrappers/ActorControlSelfPacket.h"
#include "Network/PacketWrappers/ActorControlTargetPacket.h"

#include <Logging/Logger.h>

#include <Util/ActorFilter.h>
#include <Util/UtilMath.h>
#include <Service.h>
#include "WorldServer.h"

using namespace Sapphire;
using namespace Sapphire::Common;
using namespace Sapphire::Network;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets;
using namespace Sapphire::Network::Packets::WorldPackets::Server;
using namespace Sapphire::Network::ActorControl;
using namespace Sapphire::World;


Action::Action::Action() = default;
Action::Action::~Action() = default;

Action::Action::Action( Entity::CharaPtr caster, uint32_t actionId, uint16_t sequence) :
  Action( std::move( caster ), actionId, sequence, nullptr )
{
}

Action::Action::Action( Entity::CharaPtr caster, uint32_t actionId, uint16_t sequence,
                        std::shared_ptr< Component::Excel::ExcelStruct< Component::Excel::Action > > actionData ) :
  m_pSource( std::move( caster ) ),
  m_actionData( std::move( actionData ) ),
  m_id( actionId ),
  m_targetId( 0 ),
  m_startTime( 0 ),
  m_interruptType( Common::ActionInterruptType::None ),
  m_sequence( sequence ),
  m_actionKind( Common::SkillType::Normal )
{
}

uint32_t Action::Action::getId() const
{
  return m_id;
}

bool Action::Action::init()
{
  if( !m_actionData )
  {
    // need to get actionData
    auto& exdData = Common::Service< Data::ExdData >::ref();

    auto actionData = exdData.getRow< Component::Excel::Action >( m_id );
    if( !actionData )
      throw std::runtime_error( "No actiondata found!" );

    m_actionData = actionData;
  }

  m_effectBuilder = make_EffectBuilder( m_pSource, getId(), m_sequence );

  m_castTimeMs = static_cast< uint32_t >( m_actionData->data().CastTime * 100 );
  m_recastTimeMs = static_cast< uint32_t >( m_actionData->data().RecastTime * 100 );
  m_cooldownGroup = m_actionData->data().RecastGroup;
  m_range = m_actionData->data().SelectRange;
  m_effectRange = m_actionData->data().EffectRange;
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
        m_range = 25;
        break;
        // anything that isnt ranged
      default:
        m_range = 3;
        break;
    }
  }

  m_primaryCostType = static_cast< Common::ActionPrimaryCostType >( m_actionData->data().CostType );
  m_primaryCost = m_actionData->data().CostValue;

  /*if( !m_actionData->targetArea )
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
  }*/

  // todo: add missing rows for secondaryCostType/secondaryCostType and rename the current rows to primaryCostX

  if( ActionLut::validEntryExists( static_cast< uint16_t >( getId() ) ) )
  {
    m_lutEntry = ActionLut::getEntry( static_cast< uint16_t >( getId() ) );
  }
  else
  {
    std::memset( &m_lutEntry, 0, sizeof( ActionEntry ) );
  }

  addDefaultActorFilters();

  return true;
}

void Action::Action::setPos( Sapphire::Common::FFXIVARR_POSITION3 pos )
{
  m_pos = pos;
}

Sapphire::Common::FFXIVARR_POSITION3 Action::Action::getPos() const
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

Sapphire::Entity::CharaPtr Action::Action::getSourceChara() const
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

  uint64_t tickCount = Common::Util::getTimeMs();
  uint32_t castTime = m_castTimeMs;

  if( auto player = m_pSource->getAsPlayer() )
  {
    uint64_t lastActionTick = player->getLastActionTick();
    uint32_t lastTickMs = 0;
    if( lastActionTick > 0 )
    {
      lastTickMs = static_cast< uint32_t >( std::difftime( static_cast< time_t >( tickCount ), static_cast< time_t >( lastActionTick ) ) );
      if( lastTickMs > 100 ) //max 100ms
        lastTickMs = 100;
    }

    player->setLastActionTick( tickCount );
    uint32_t delayMs = 100 - lastTickMs;
    castTime = ( m_castTimeMs + delayMs ) - 500; //subtract 500ms before the client begin to request actions while casting
  }

  if( !hasCastTime() || std::difftime( static_cast< time_t >( tickCount ), static_cast< time_t >( m_startTime ) ) > castTime )
  {
    execute();
    return true;
  }

  if( m_pTarget == nullptr && m_targetId != 0 )
  {
    // try to search for the target actor
    for( auto actor : m_pSource->getInRangeActors( true ) )
    {
      if( actor->getId() == m_targetId )
      {
        m_pTarget = actor->getAsChara();
        break;
      }
    }
  }

  if( m_pTarget != nullptr )
  {
    if( !m_pTarget->isAlive() )
    {
      // interrupt the cast if target died
      setInterrupted( Common::ActionInterruptType::RegularInterrupt );
      interrupt();
      return true;
    }
  }

  return false;
}

void Action::Action::start()
{
  assert( m_pSource );
  auto& server = Common::Service< World::WorldServer >::ref();
  m_startTime = Common::Util::getTimeMs();

  auto player = m_pSource->getAsPlayer();

  if( hasCastTime() )
  {
    auto castPacket = makeZonePacket< Server::FFXIVIpcActorCast >( m_pSource->getId() );
    auto& data = castPacket->data();

    data.Action = static_cast< uint16_t >( m_id );
    data.ActionKey = m_id;
    data.ActionKind = m_actionKind;
    data.CastTime = m_castTimeMs / 1000.f;
    data.Target = static_cast< uint32_t >( m_targetId );

    data.TargetPos[ 0 ] = Common::Util::floatToUInt16( m_pSource->getPos().x );
    data.TargetPos[ 1 ] = Common::Util::floatToUInt16( m_pSource->getPos().y );
    data.TargetPos[ 2 ] = Common::Util::floatToUInt16( m_pSource->getPos().z );
    data.Dir = m_pSource->getRot();

    m_pSource->sendToInRangeSet( castPacket, true );

    if( player )
    {
      player->setStateFlag( PlayerStateFlag::Casting );
    }
  }
  
  // todo: m_recastTimeMs needs to be adjusted for player sks/sps
  auto actionStartPkt = makeActorControlSelf( m_pSource->getId(), ActorControlType::ActionStart, m_cooldownGroup, getId(),
                                              m_recastTimeMs / 10 );

  player->setRecastGroup( m_cooldownGroup, m_castTimeMs / 1000.f );

  server.queueForPlayer( player->getCharacterId(), actionStartPkt );

  onStart();

  // instantly finish cast if there's no cast time
  if( !hasCastTime() )
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

  // things that aren't players don't care about cooldowns and state flags
  if( m_pSource->isPlayer() )
  {
    auto player = m_pSource->getAsPlayer();

    // todo: reset cooldown for actual player

    // reset state flag
    //player->unsetStateFlag( PlayerStateFlag::Occupied1 );
    player->setLastActionTick( 0 );
    player->unsetStateFlag( PlayerStateFlag::Casting );
  }

  if( hasCastTime() )
  {
    uint8_t interruptEffect = 0;
    if( m_interruptType == ActionInterruptType::DamageInterrupt )
      interruptEffect = 1;

    // Note: When cast interrupt from taking too much damage, set the last value to 1.
    // This enables the cast interrupt effect.
    auto control = makeActorControl( m_pSource->getId(), ActorControlType::CastInterrupt,
                                     0x219, 1, m_id, interruptEffect );

    m_pSource->sendToInRangeSet( control, true );
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

  if( hasCastTime() )
  {
    // todo: what's this?
    /*auto control = ActorControlSelfPacket( m_pTarget->getId(), ActorControlType::Unk7,
                                            0x219, m_id, m_id, m_id, m_id );
    m_pSource->sendToInRangeSet( control, true );*/

    if( auto player = m_pSource->getAsPlayer() )
    {
      player->setLastActionTick( 0 );
      player->unsetStateFlag( PlayerStateFlag::Casting );
    }
  }

  if( isCorrectCombo() )
  {
    auto player = m_pSource->getAsPlayer();
    Manager::PlayerMgr::sendDebug( *player,"action combo success from action#{0}", player->getLastComboActionId() );
  }

  if( !hasClientsideTarget()  )
  {
    buildEffects();
  }
  else if( auto player = m_pSource->getAsPlayer() )
  {
    scriptMgr.onEObjHit( *player, m_targetId, getId() );
  }

  // set currently casted action as the combo action if it interrupts a combo
  // ignore it otherwise (ogcds, etc.)
  if( !m_actionData->data().ComboContinue )
  {
    // potential combo starter or correct combo from last action, must hit something to progress combo
    if( !m_hitActors.empty() && ( !isComboAction() || isCorrectCombo() ) )
    {
      m_pSource->setLastComboActionId( getId() );
    }
    else // clear last combo action if the combo breaks
    {
      m_pSource->setLastComboActionId( 0 );
    }
  }
}

std::pair< uint32_t, Common::ActionHitSeverityType > Action::Action::calcDamage( uint32_t potency )
{
  // todo: what do for npcs?
  auto wepDmg = 1.f;

  if( auto player = m_pSource->getAsPlayer() )
  {
    auto item = player->getEquippedWeapon();
    assert( item );

    auto role = player->getRole();
    if( role == Common::Role::RangedMagical || role == Common::Role::Healer )
    {
      wepDmg = item->getMagicalDmg();
    }
    else
    {
      wepDmg = item->getPhysicalDmg();
    }
  }

  return Math::CalcStats::calcActionDamage( *m_pSource, potency, wepDmg );
}

std::pair< uint32_t, Common::ActionHitSeverityType > Action::Action::calcHealing( uint32_t potency )
{
  auto wepDmg = 1.f;

  if( auto player = m_pSource->getAsPlayer() )
  {
    auto item = player->getEquippedWeapon();
    assert( item );

    auto role = player->getRole();
    if( role == Common::Role::RangedMagical || role == Common::Role::Healer )
    {
      wepDmg = item->getMagicalDmg();
    }
    else
    {
      wepDmg = item->getPhysicalDmg();
    }
  }

  return Math::CalcStats::calcActionHealing( *m_pSource, potency, wepDmg );
}

void Action::Action::buildEffects()
{
  snapshotAffectedActors( m_hitActors );

  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();
  auto hasLutEntry = hasValidLutEntry();

  if( !scriptMgr.onExecute( *this ) && !hasLutEntry )
  {
    if( auto player = m_pSource->getAsPlayer() )
    {
      Manager::PlayerMgr::sendUrgent( *player, "missing lut entry for action#{}", getId() );
    }

    return;
  }

  if( !hasLutEntry || m_hitActors.empty() )
  {
    // send any effect packet added by script or an empty one just to play animation for other players
    m_effectBuilder->buildAndSendPackets( m_hitActors );
    return;
  }

  // no script exists but we have a valid lut entry
  if( auto player = getSourceChara()->getAsPlayer() )
  {
    Manager::PlayerMgr::sendDebug( *player, "Hit target: pot: {} (c: {}, f: {}, r: {}), heal pot: {}, mpp: {}",
                                   m_lutEntry.potency, m_lutEntry.comboPotency, m_lutEntry.flankPotency, m_lutEntry.rearPotency,
                                   m_lutEntry.curePotency, m_lutEntry.restoreMPPercentage );
  }

  // when aoe, these effects are in the target whatever is hit first
  bool shouldRestoreMP = true;
  bool shouldApplyComboSucceedEffect = true;

  for( auto& actor : m_hitActors )
  {
    if( m_lutEntry.potency > 0 )
    {
      auto dmg = calcDamage( isCorrectCombo() ? m_lutEntry.comboPotency : m_lutEntry.potency );
      m_effectBuilder->damage( m_pSource, actor, dmg.first, dmg.second );

      if( dmg.first > 0 )
        actor->onActionHostile( m_pSource );

      if( isCorrectCombo() && shouldApplyComboSucceedEffect )
      {
        m_effectBuilder->comboSucceed( m_pSource );
        shouldApplyComboSucceedEffect = false;
      }

      if( !isComboAction() || isCorrectCombo() )
      {
        if( m_lutEntry.curePotency > 0 ) // actions with self heal
        {
          auto heal = calcHealing( m_lutEntry.curePotency );
          m_effectBuilder->heal( actor, m_pSource, heal.first, heal.second, Common::ActionEffectResultFlag::EffectOnSource );
        }

        if( m_lutEntry.restoreMPPercentage > 0 && shouldRestoreMP )
        {
          m_effectBuilder->restoreMP( actor, m_pSource, m_pSource->getMaxMp() * m_lutEntry.restoreMPPercentage / 100, Common::ActionEffectResultFlag::EffectOnSource );
          shouldRestoreMP = false;
        }

        if( !m_actionData->data().ComboContinue ) // we need something like m_actionData->hasNextComboAction
        {
          m_effectBuilder->startCombo( m_pSource, getId() ); // this is on all targets hit
        }
      }
    }
    else if( m_lutEntry.curePotency > 0 )
    {
      auto heal = calcHealing( m_lutEntry.curePotency );
      m_effectBuilder->heal( actor, actor, heal.first, heal.second );

      if( m_lutEntry.restoreMPPercentage > 0 && shouldRestoreMP )
      {
        m_effectBuilder->restoreMP( actor, m_pSource, m_pSource->getMaxMp() * m_lutEntry.restoreMPPercentage / 100, Common::ActionEffectResultFlag::EffectOnSource );
        shouldRestoreMP = false;
      }
    }
    else if( m_lutEntry.restoreMPPercentage > 0 && shouldRestoreMP )
    {
      m_effectBuilder->restoreMP( actor, m_pSource, m_pSource->getMaxMp() * m_lutEntry.restoreMPPercentage / 100, Common::ActionEffectResultFlag::EffectOnSource );
      shouldRestoreMP = false;
    }
  }

  m_effectBuilder->buildAndSendPackets( m_hitActors );

  // TODO: disabled, reset kills our queued actions
  // at this point we're done with it and no longer need it
  // m_effectBuilder.reset();
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
  // lol
  if( !player.isAlive() )
    return false;

  // npc actions/non player actions
  if( m_actionData->data().UseClassJob == -1 /* dunno what this is in old data && !m_actionData->data().isRoleAction*/ )
    return false;

  if( player.getLevel() < m_actionData->data().UseClassJob )
    return false;

  auto currentClass = player.getClass();
  auto actionClass = static_cast< Common::ClassJob >( m_actionData->data().UseClassJob );

  if( actionClass != Common::ClassJob::Adventurer && currentClass != actionClass /* dunno what this is in old data && !m_actionData->data().isRoleAction*/ )
  {
    // check if not a base class action
    auto& exdData = Common::Service< Data::ExdData >::ref();

    auto classJob = exdData.getRow< Component::Excel::ClassJob >( static_cast< uint8_t >( currentClass ) );
    if( !classJob )
      return false;

    if( classJob->data().MainClass != m_actionData->data().UseClassJob )
      return false;
  }

  if( !m_actionData->data().SelectMyself && getTargetId() == m_pSource->getId() )
    return false;

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

bool Action::Action::isCorrectCombo() const
{
  auto lastActionId = m_pSource->getLastComboActionId();

  if( lastActionId == 0 )
  {
    return false;
  }

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

    for( const auto& filter : m_actorFilters )
    {
      if( filter->conditionApplies( *actor ) )
      {
        actors.push_back( actor->getAsChara() );
        break;
      }
    }
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
    case Common::CastType::Type3:
    {
      auto filter = std::make_shared< World::Util::ActorFilterSingleTarget >( static_cast< uint32_t >( m_targetId ) );

      addActorFilter( filter );

      break;
    }

    case Common::CastType::CircularAOE:
    {
      auto filter = std::make_shared< World::Util::ActorFilterInRange >( m_pos, m_effectRange );

      addActorFilter( filter );

      break;
    }

//    case Common::CastType::RectangularAOE:
//    {
//      break;
//    }

    default:
    {
      Logger::error( "[{}] Action#{} has CastType#{} but that cast type is unhandled. Cancelling cast.",
                     m_pSource->getId(), getId(), m_castType );

      interrupt();
    }
  }
}

bool Action::Action::preFilterActor( Sapphire::Entity::GameObject& actor ) const
{
  auto kind = actor.getObjKind();
  auto chara = actor.getAsChara();

  // todo: are there any server side eobjs that players can hit?
  if( kind != ObjKind::BattleNpc && kind != ObjKind::Player )
    return false;
  
  if( !m_canTargetSelf && chara->getId() == m_pSource->getId() )
    return false;
  
  if( ( m_lutEntry.potency > 0 || m_lutEntry.curePotency > 0 ) && !chara->isAlive() ) // !m_canTargetDead not working for aoe
    return false;

  if( m_lutEntry.potency > 0 && m_pSource->getObjKind() == chara->getObjKind() ) // !m_canTargetFriendly not working for aoe
    return false;

  if( ( m_lutEntry.potency == 0 && m_lutEntry.curePotency > 0 ) && m_pSource->getObjKind() != chara->getObjKind() ) // !m_canTargetHostile not working for aoe
    return false;

  return true;
}

std::vector< Sapphire::Entity::CharaPtr >& Action::Action::getHitCharas()
{
  return m_hitActors;
}

Sapphire::Entity::CharaPtr Action::Action::getHitChara()
{
  if( !m_hitActors.empty() )
  {
    return m_hitActors.at( 0 );
  }

  return nullptr;
}

bool Action::Action::hasValidLutEntry() const
{
  return m_lutEntry.potency != 0 || m_lutEntry.comboPotency != 0 || m_lutEntry.flankPotency != 0 || m_lutEntry.frontPotency != 0 ||
    m_lutEntry.rearPotency != 0 || m_lutEntry.curePotency != 0 || m_lutEntry.restoreMPPercentage != 0;
}

Action::EffectBuilderPtr Action::Action::getEffectbuilder()
{
  return m_effectBuilder;
}

uint8_t Action::Action::getActionKind() const
{
  return m_actionKind;
}

void Action::Action::setActionKind( uint8_t actionKind )
{
  m_actionKind = actionKind;
}
