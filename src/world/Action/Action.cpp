#include "Action.h"
#include "ActionLut.h"
#include "EffectBuilder.h"

#include <Inventory/Item.h>

#include <Exd/ExdDataGenerated.h>
#include <Util/Util.h>
#include "Framework.h"
#include "Script/ScriptMgr.h"

#include <Math/CalcStats.h>

#include "Actor/Player.h"
#include "Actor/BNpc.h"

#include "Territory/Territory.h"

#include <Network/CommonActorControl.h>
#include "Network/PacketWrappers/ActorControlPacket142.h"
#include "Network/PacketWrappers/ActorControlPacket143.h"
#include "Network/PacketWrappers/ActorControlPacket144.h"

#include <Logging/Logger.h>

#include <Util/ActorFilter.h>
#include <Util/UtilMath.h>

using namespace Sapphire;
using namespace Sapphire::Common;
using namespace Sapphire::Network;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;
using namespace Sapphire::Network::ActorControl;
using namespace Sapphire::World;


Action::Action::Action() = default;
Action::Action::~Action() = default;

Action::Action::Action( Entity::CharaPtr caster, uint32_t actionId, uint16_t sequence, FrameworkPtr fw ) :
  Action( std::move( caster ), actionId, sequence, nullptr, std::move( fw ) )
{
}

Action::Action::Action( Entity::CharaPtr caster, uint32_t actionId, uint16_t sequence,
                        Data::ActionPtr actionData, FrameworkPtr fw ) :
  m_pSource( std::move( caster ) ),
  m_pFw( std::move( fw ) ),
  m_actionData( std::move( actionData ) ),
  m_id( actionId ),
  m_targetId( 0 ),
  m_startTime( 0 ),
  m_interruptType( Common::ActionInterruptType::None ),
  m_sequence( sequence )
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
    auto exdData = m_pFw->get< Data::ExdDataGenerated >();
    assert( exdData );

    auto actionData = exdData->get< Data::Action >( m_id );
    assert( actionData );

    m_actionData = actionData;
  }

  m_effectBuilder = make_EffectBuilder( m_pSource, getId(), m_sequence );

  m_castTimeMs = static_cast< uint32_t >( m_actionData->cast100ms * 100 );
  m_recastTimeMs = static_cast< uint32_t >( m_actionData->recast100ms * 100 );
  m_cooldownGroup = m_actionData->cooldownGroup;
  m_range = m_actionData->range;
  m_effectRange = m_actionData->effectRange;
  m_castType = static_cast< Common::CastType >( m_actionData->castType );
  m_aspect = static_cast< Common::ActionAspect >( m_actionData->aspect );

  // todo: move this to bitset
  m_canTargetSelf = m_actionData->canTargetSelf;
  m_canTargetParty = m_actionData->canTargetParty;
  m_canTargetFriendly = m_actionData->canTargetFriendly;
  m_canTargetHostile = m_actionData->canTargetHostile;
  // todo: this one doesn't look right based on whats in that col, probably has shifted
  m_canTargetDead = m_actionData->canTargetDead;

  // a default range is set by the game for the class/job
  if( m_range == -1 )
  {
    switch( static_cast< Common::ClassJob >( m_actionData->classJob ) )
    {
      case Common::ClassJob::Bard:
      case Common::ClassJob::Archer:
        m_range = 25;

        // anything that isnt ranged
      default:
        m_range = 3;
    }
  }

  m_primaryCostType = static_cast< Common::ActionPrimaryCostType >( m_actionData->primaryCostType );
  m_primaryCost = m_actionData->primaryCostValue;

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

  if( !hasCastTime() || std::difftime( tickCount, m_startTime ) > m_castTimeMs )
  {
    execute();
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
    auto castPacket = makeZonePacket< Server::FFXIVIpcActorCast >( getId() );
    auto& data = castPacket->data();

    data.action_id = static_cast< uint16_t >( m_id );
    data.skillType = Common::SkillType::Normal;
    data.unknown_1 = m_id;
    // This is used for the cast bar above the target bar of the caster.
    data.cast_time = m_castTimeMs / 1000.f;
    data.target_id = static_cast< uint32_t >( m_targetId );

    auto pos = m_pSource->getPos();
    data.posX = Common::Util::floatToUInt16( pos.x );
    data.posY = Common::Util::floatToUInt16( pos.y );
    data.posZ = Common::Util::floatToUInt16( pos.z );
    data.rotation = m_pSource->getRot();

    m_pSource->sendToInRangeSet( castPacket, true );

    if( player )
    {
      player->setStateFlag( PlayerStateFlag::Casting );
    }
  }

  // todo: m_recastTimeMs needs to be adjusted for player sks/sps
  auto actionStartPkt = makeActorControl143( m_pSource->getId(), ActorControlType::ActionStart, 1, getId(), m_recastTimeMs / 10 );
  player->queuePacket( actionStartPkt );

  auto pScriptMgr = m_pFw->get< Scripting::ScriptMgr >();

  // check the lut too and see if we have something usable, otherwise cancel the cast
  if( !pScriptMgr->onStart( *this ) && !ActionLut::validEntryExists( getId() ) )
  {
    // script not implemented and insufficient lut data (no potencies)
    interrupt();

    if( player )
    {
      player->sendUrgent( "Action not implemented, missing script/lut entry for action#{0}", getId() );
      player->setCurrentAction( nullptr );
    }

    return;
  }

  // instantly finish cast if there's no cast time
  if( !hasCastTime() )
    execute();
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
    player->unsetStateFlag( PlayerStateFlag::Casting );
  }

  if( hasCastTime() )
  {
    uint8_t interruptEffect = 0;
    if( m_interruptType == ActionInterruptType::DamageInterrupt )
      interruptEffect = 1;

    // Note: When cast interrupt from taking too much damage, set the last value to 1.
    // This enables the cast interrupt effect.
    auto control = makeActorControl142( m_pSource->getId(), ActorControlType::CastInterrupt,
                                        0x219, 1, m_id, interruptEffect );

    m_pSource->sendToInRangeSet( control, true );
  }

  auto pScriptMgr = m_pFw->get< Scripting::ScriptMgr >();
  pScriptMgr->onInterrupt( *this );
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

  auto pScriptMgr = m_pFw->get< Scripting::ScriptMgr >();

  if( hasCastTime() )
  {
    // todo: what's this?
    /*auto control = ActorControlPacket143( m_pTarget->getId(), ActorControlType::Unk7,
                                            0x219, m_id, m_id, m_id, m_id );
    m_pSource->sendToInRangeSet( control, true );*/

    if( auto player = m_pSource->getAsPlayer() )
    {
      player->unsetStateFlag( PlayerStateFlag::Casting );
    }
  }

  if( isComboAction() )
  {
    auto player = m_pSource->getAsPlayer();

    player->sendDebug( "action combo success from action#{0}", player->getLastComboActionId() );
  }

  if( !hasClientsideTarget()  )
  {
    buildEffects();
  }
  else if( auto player = m_pSource->getAsPlayer() )
  {
    pScriptMgr->onEObjHit( *player, m_targetId, getId() );
  }

  // set currently casted action as the combo action if it interrupts a combo
  // ignore it otherwise (ogcds, etc.)
  if( !m_actionData->preservesCombo )
  {
    m_pSource->setLastComboActionId( getId() );
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

  auto dmg = Math::CalcStats::calcActionDamage( *m_pSource, potency, wepDmg );

  return std::make_pair( dmg, Common::ActionHitSeverityType::NormalDamage );
}

void Action::Action::buildEffects()
{
  snapshotAffectedActors( m_hitActors );

  auto pScriptMgr = m_pFw->get< Scripting::ScriptMgr >();

  if( !pScriptMgr->onExecute( *this ) && !ActionLut::validEntryExists( getId() ) )
  {
    if( auto player = m_pSource->getAsPlayer() )
    {
      player->sendUrgent( "missing lut entry for action#{}", getId() );
    }

    return;
  }

  if( m_hitActors.empty() )
    return;

  auto lutEntry = ActionLut::getEntry( getId() );

  // no script exists but we have a valid lut entry
  if( auto player = getSourceChara()->getAsPlayer() )
  {
    player->sendDebug( "Hit target: pot: {} (c: {}, f: {}, r: {}), heal pot: {}",
                       lutEntry.potency, lutEntry.comboPotency, lutEntry.flankPotency, lutEntry.rearPotency,
                       lutEntry.curePotency );
  }

  for( auto& actor : m_hitActors )
  {
    // todo: this is shit
    if( lutEntry.curePotency > 0 )
    {

      m_effectBuilder->healTarget( actor, lutEntry.curePotency );
    }

    else if( lutEntry.potency > 0 )
    {
      auto dmg = calcDamage( lutEntry.potency );
      m_effectBuilder->damageTarget( actor, dmg.first, dmg.second );
    }
  }

  m_effectBuilder->buildAndSendPackets();

  // at this point we're done with it and no longer need it
  m_effectBuilder.reset();
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
  if( m_actionData->classJob == -1 )
    return false;

  if( player.getLevel() < m_actionData->classJobLevel )
    return false;

  auto currentClass = player.getClass();
  auto actionClass = static_cast< Common::ClassJob >( m_actionData->classJob );

  if( actionClass != Common::ClassJob::Adventurer && currentClass != actionClass )
  {
    // check if not a base class action
    auto exdData = m_pFw->get< Data::ExdDataGenerated >();
    assert( exdData );

    auto classJob = exdData->get< Data::ClassJob >( static_cast< uint8_t >( currentClass ) );
    if( !classJob )
      return false;

    if( classJob->classJobParent != m_actionData->classJob )
      return false;
  }

  if( !m_actionData->canTargetSelf && getTargetId() == m_pSource->getId() )
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

bool Action::Action::isComboAction() const
{
  auto lastActionId = m_pSource->getLastComboActionId();

  if( lastActionId == 0 )
  {
    return false;
  }

  return m_actionData->actionCombo == lastActionId;
}

bool Action::Action::primaryCostCheck( bool subtractCosts )
{
  switch( m_primaryCostType )
  {
    case Common::ActionPrimaryCostType::TacticsPoints:
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

      auto cost = m_primaryCost * 100;

      if( curMp < cost )
        return false;

      if( subtractCosts )
        m_pSource->setMp( curMp - cost );

      return true;
    }

    // free casts, likely just pure ogcds
    case Common::ActionPrimaryCostType::None:
    {
      return true;
    }

    default:
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
    player->sendDebug( "Hit {} actors with {} filters", actors.size(), m_actorFilters.size() );
    for( const auto& actor : actors )
    {
      player->sendDebug( "hit actor#{}", actor->getId() );
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

bool Action::Action::preFilterActor( Sapphire::Entity::Actor& actor ) const
{
  auto kind = actor.getObjKind();

  // todo: are there any server side eobjs that players can hit?
  if( kind != ObjKind::BattleNpc && kind != ObjKind::Player )
    return false;

  // todo: handle things such based on canTargetX

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