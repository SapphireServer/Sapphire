#include "Action.h"

#include <Exd/ExdDataGenerated.h>
#include <Util/Util.h>
#include "Framework.h"
#include "Script/ScriptMgr.h"

#include "Actor/Player.h"
#include "Actor/BNpc.h"

#include "Territory/Zone.h"

#include <Network/CommonActorControl.h>
#include "Network/PacketWrappers/ActorControlPacket142.h"
#include "Network/PacketWrappers/ActorControlPacket143.h"
#include "Network/PacketWrappers/ActorControlPacket144.h"
#include <Network/PacketWrappers/EffectPacket.h>

using namespace Sapphire::Common;
using namespace Sapphire::Network;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;
using namespace Sapphire::Network::ActorControl;


Sapphire::Action::Action::Action() = default;
Sapphire::Action::Action::~Action() = default;

Sapphire::Action::Action::Action( Entity::CharaPtr caster, uint32_t actionId, FrameworkPtr fw ) :
                                  Action( std::move( caster ), actionId, nullptr, std::move( fw ) )
{
}

Sapphire::Action::Action::Action( Entity::CharaPtr caster, uint32_t actionId,
                                  Data::ActionPtr actionData, FrameworkPtr fw ) :
                                  m_pSource( std::move( caster ) ),
                                  m_pFw( std::move( fw ) ),
                                  m_actionData( std::move( actionData ) ),
                                  m_id( actionId ),
                                  m_targetId( 0 ),
                                  m_startTime( 0 ),
                                  m_interruptType( Common::ActionInterruptType::None )
{
}

uint32_t Sapphire::Action::Action::getId() const
{
  return m_id;
}

bool Sapphire::Action::Action::init()
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

  m_castTimeMs = static_cast< uint32_t >( m_actionData->cast100ms * 100 );
  m_recastTimeMs = static_cast< uint32_t >( m_actionData->recast100ms * 100 );
  m_cooldownGroup = m_actionData->cooldownGroup;
  m_range = m_actionData->range;
  m_effectRange = m_actionData->effectRange;
  m_aspect = static_cast< Common::ActionAspect >( m_actionData->aspect );

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

  m_primaryCostType = static_cast< Common::ActionPrimaryCostType >( m_actionData->costType );
  m_primaryCost = m_actionData->cost;

  // todo: add missing rows for secondaryCostType/secondaryCostType and rename the current rows to primaryCostX

  return true;
}

void Sapphire::Action::Action::setPos( Sapphire::Common::FFXIVARR_POSITION3 pos )
{
  m_pos = pos;
}

Sapphire::Common::FFXIVARR_POSITION3 Sapphire::Action::Action::getPos() const
{
  return m_pos;
}

void Sapphire::Action::Action::setTargetId( uint64_t targetId )
{
  m_targetId = targetId;
}

uint64_t Sapphire::Action::Action::getTargetId() const
{
  return m_targetId;
}

bool Sapphire::Action::Action::hasClientsideTarget() const
{
  return m_targetId > 0xFFFFFFFF;
}

bool Sapphire::Action::Action::isInterrupted() const
{
  return m_interruptType != Common::ActionInterruptType::None;
}

void Sapphire::Action::Action::setInterrupted( Common::ActionInterruptType type )
{
  m_interruptType = type;
}

uint32_t Sapphire::Action::Action::getCastTime() const
{
  return m_castTimeMs;
}

void Sapphire::Action::Action::setCastTime( uint32_t castTime )
{
  m_castTimeMs = castTime;
}

bool Sapphire::Action::Action::hasCastTime() const
{
  return m_castTimeMs > 0;
}

Sapphire::Entity::CharaPtr Sapphire::Action::Action::getSourceChara() const
{
  return m_pSource;
}

bool Sapphire::Action::Action::update()
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

  uint64_t currTime = Util::getTimeMs();

  if( !hasCastTime() || std::difftime( currTime, m_startTime ) > m_castTimeMs )
  {
    execute();
    return true;
  }

  return false;
}

void Sapphire::Action::Action::start()
{
  assert( m_pSource );

  m_startTime = Util::getTimeMs();

  auto player = m_pSource->getAsPlayer();

  if( hasCastTime() )
  {
    auto castPacket = makeZonePacket< Server::FFXIVIpcActorCast >( getId() );

    castPacket->data().action_id = static_cast< uint16_t >( m_id );
    castPacket->data().skillType = Common::SkillType::Normal;
    castPacket->data().unknown_1 = m_id;
    // This is used for the cast bar above the target bar of the caster.
    castPacket->data().cast_time = m_castTimeMs / 1000.f;
    castPacket->data().target_id = static_cast< uint32_t >( m_targetId );

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
  if( !pScriptMgr->onStart( *this ) )
  {
    // script not implemented
    interrupt();

    if( player )
    {
      player->sendUrgent( "Action not implemented, missing script for action#{0}", getId() );
      player->setCurrentAction( nullptr );
    }

    return;
  }

  // instantly finish cast if there's no cast time
  if( !hasCastTime() )
    execute();
}

void Sapphire::Action::Action::interrupt()
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

void Sapphire::Action::Action::execute()
{
  assert( m_pSource );

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

  if( !hasClientsideTarget() )
  {
    pScriptMgr->onExecute( *this );
  }
  else if( auto player = m_pSource->getAsPlayer() )
  {
    pScriptMgr->onEObjHit( *player, m_targetId );
    return;
  }
}

void Sapphire::Action::Action::calculateActionCost()
{
  // todo: just a test handler for now to get MP output for each cast, not sure where we should put this
  // check primary cost
  switch( m_primaryCostType )
  {
    case ActionPrimaryCostType::None:
    {
      break;
    }
    case ActionPrimaryCostType::MagicPoints:
    {
      calculateMPCost( m_primaryCost );
      break;
    }
    case ActionPrimaryCostType::TacticsPoints:
    {
      break;
    }

    default:
    {
      if( auto player = m_pSource->getAsPlayer() )
      {
        player->sendDebug( "action#{0} is missing a handler for cost type: {1}",
                           m_id, static_cast< uint8_t >( m_primaryCostType ) );
      }

      break;
    }
  }

  // todo: secondary cost type needs to be handled
}

// todo: this shouldn't be in action and instead be in some general stat calc util
void Sapphire::Action::Action::calculateMPCost( uint16_t baseCost )
{
  auto level = m_pSource->getLevel();

  // each level range is 1-10, 11-20, 21-30, ... therefore:
  // level 50 should be in the 4th group, not the 5th
  // dividing by 10 on the border will break this unless we subtract 1
  auto levelGroup = std::max< uint8_t >( level - 1, 1 ) / 10;

  float cost = baseCost;

  // thanks to andrew for helping me figure this shit out, should be pretty accurate
  switch( levelGroup )
  {
    // level 1-10
    case 0:
    {
      // r^2 = 0.9999
      cost = 0.0952f * level + 0.9467f;
      break;
    }

    // level 11-20
    case 1:
    {
      // r^2 = 1
      cost = 0.19f * level;
      break;
    }

    // level 21-30
    case 2:
    {
      // r^2 = 1
      cost = 0.38f * level - 3.8f;
      break;
    }

    // level 31-40
    case 3:
    {
      // r^2 = 1
      cost = 0.6652f * level - 12.358f;
      break;
    }

      // level 41-50
    case 4:
    {
      // r^2 = 1
      cost = 1.2352f * level - 35.159f;
      break;
    }

    // level 51-60
    case 5:
    {
      // r^2 = 1
      cost = 0.0654f * std::exp( 0.1201f * level );
      break;
    }

    // level 61-70
    case 6:
    {
      // r^2 = 0.9998
      cost = 0.2313f * ( level * level ) - 26.98f * level + 875.21f;
      break;
    }

    default:
      return;
  }

  // m_primaryCost is the base cost, cost is the multiplier for the current player level
  m_primaryCost = static_cast< uint16_t >( std::round( cost * baseCost ) );

  if( auto player = m_pSource->getAsPlayer() )
    player->sendDebug( "calculated mp cost: {0}", m_primaryCost );
}

bool Sapphire::Action::Action::precheck()
{
  if( auto player = m_pSource->getAsPlayer() )
  {
    if( !playerPrecheck( *player ) )
      return false;
  }

  return true;
}

bool Sapphire::Action::Action::playerPrecheck( Entity::Player& player )
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

  // reset target on actions that can only be casted on yourself while having a target set
  // todo: check what actions send when targeting an enemy
//  if( m_actionData->canTargetSelf &&
//      !m_actionData->canTargetFriendly &&
//      !m_actionData->canTargetHostile &&
//      !m_actionData->canTargetParty )
//  {
//    setTargetId( getSourceChara() );
//  }

  // todo: party/enemy validation

  // validate range


  // todo: validate costs/conditionals here

  calculateActionCost();

  return true;
}

uint32_t Sapphire::Action::Action::getAdditionalData() const
{
  return m_additionalData;
}

void Sapphire::Action::Action::setAdditionalData( uint32_t data )
{
  m_additionalData = data;
}