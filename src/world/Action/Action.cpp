#include "Action.h"

#include <Exd/ExdDataGenerated.h>
#include <Util/Util.h>
#include "Framework.h"
#include "Script/ScriptMgr.h"

#include "Actor/Player.h"

#include <Network/CommonActorControl.h>
#include "Network/PacketWrappers/ActorControlPacket142.h"
#include "Network/PacketWrappers/ActorControlPacket143.h"
#include "Network/PacketWrappers/ActorControlPacket144.h"

using namespace Sapphire::Common;
using namespace Sapphire::Network;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;
using namespace Sapphire::Network::ActorControl;


Sapphire::Action::Action::Action() = default;
Sapphire::Action::Action::~Action() = default;

Sapphire::Action::Action::Action( Entity::CharaPtr caster, uint32_t actionId,
                                  Data::ActionPtr action, FrameworkPtr fw ) :
                                  m_pSource( std::move( caster ) ),
                                  m_pFw( std::move( fw ) ),
                                  m_id( actionId ),
                                  m_startTime( 0 ),
                                  m_bInterrupt( false )
{
  m_castTime = static_cast< uint32_t >( action->cast100ms ) * 100;

  m_actionCost.fill( { Common::ActionCostType::None, 0 } );

  m_actionCost[ 0 ] = {
    static_cast< Common::ActionCostType >( action->costType ),
    action->cost
  };

  calculateActionCost();
}

uint32_t Sapphire::Action::Action::getId() const
{
  return m_id;
}

void Sapphire::Action::Action::subtractCostFromCaster()
{
  if( !m_pSource->isPlayer() )
    return;

  auto player = m_pSource->getAsPlayer();

  switch( m_costType )
  {
    case Common::ActionCostType::MagicPoints:
    {

      break;
    }
    case Common::ActionCostType::TacticsPoints:
    {

      break;
    }
  }
}

void Sapphire::Action::Action::setPos( Sapphire::Common::FFXIVARR_POSITION3 pos )
{
  m_pos = pos;
}

Sapphire::Common::FFXIVARR_POSITION3 Sapphire::Action::Action::getPos() const
{
  return m_pos;
}

void Sapphire::Action::Action::setTargetChara( Sapphire::Entity::CharaPtr chara )
{
  assert( chara );

  m_pTarget = chara;
  m_targetId = chara->getId();
}

Sapphire::Entity::CharaPtr Sapphire::Action::Action::getTargetChara() const
{
  return m_pTarget;
}

bool Sapphire::Action::Action::isInterrupted() const
{
  return m_bInterrupt;
}

void Sapphire::Action::Action::setInterrupted()
{
  m_bInterrupt = true;
}

void Sapphire::Action::Action::start()
{
  m_startTime = Util::getTimeMs();

  onStart();
}

uint32_t Sapphire::Action::Action::getCastTime() const
{
  return m_castTime;
}

void Sapphire::Action::Action::setCastTime( uint32_t castTime )
{
  m_castTime = castTime;
}

bool Sapphire::Action::Action::isCastedAction() const
{
  return m_castTime > 0;
}

Sapphire::Entity::CharaPtr Sapphire::Action::Action::getActionSource() const
{
  return m_pSource;
}

bool Sapphire::Action::Action::update()
{
  // action has not been started yet
  if( m_startTime == 0 )
    return false;

  if( m_bInterrupt )
  {
    onInterrupt();
    return true;
  }

  uint64_t currTime = Util::getTimeMs();

  if( !isCastedAction() || ( currTime - m_startTime ) > m_castTime )
  {
    onFinish();
    return true;
  }
  return false;
}

void Sapphire::Action::Action::onStart()
{
  assert( m_pSource );

  if( isCastedAction() )
  {
    m_pSource->getAsPlayer()->sendDebug( "onStart()" );

    auto castPacket = makeZonePacket< Server::FFXIVIpcActorCast >( getId() );

    castPacket->data().action_id = m_id;
    castPacket->data().skillType = Common::SkillType::Normal;
    castPacket->data().unknown_1 = m_id;
    // This is used for the cast bar above the target bar of the caster.
    castPacket->data().cast_time = m_castTime / 1000.f;
    castPacket->data().target_id = m_targetId;

    m_pSource->sendToInRangeSet( castPacket, true );
    m_pSource->getAsPlayer()->setStateFlag( PlayerStateFlag::Casting );
  }
}

void Sapphire::Action::Action::onInterrupt()
{
  assert( m_pSource );

  if( isCastedAction() )
  {
    //m_pSource->getAsPlayer()->unsetStateFlag( PlayerStateFlag::Occupied1 );
    m_pSource->getAsPlayer()->unsetStateFlag( PlayerStateFlag::Casting );

    auto control = makeActorControl142( m_pSource->getId(), ActorControlType::CastInterrupt, 0x219, 1, m_id, 0 );

    // Note: When cast interrupt from taking too much damage, set the last value to 1. This enables the cast interrupt effect. Example:
    // auto control = ActorControlPacket142( m_pSource->getId(), ActorControlType::CastInterrupt, 0x219, 1, m_id, 0 );

    m_pSource->sendToInRangeSet( control, true );
  }
}

void Sapphire::Action::Action::onFinish()
{
  assert( m_pSource );

  auto pScriptMgr = m_pFw->get< Scripting::ScriptMgr >();

  auto pPlayer = m_pSource->getAsPlayer();
  pPlayer->sendDebug( "onFinish()" );

  if( isCastedAction() )
  {
    pPlayer->unsetStateFlag( PlayerStateFlag::Casting );

    /*auto control = ActorControlPacket143( m_pTarget->getId(), ActorControlType::Unk7,
                                            0x219, m_id, m_id, m_id, m_id );
    m_pSource->sendToInRangeSet( control, true );*/

    pScriptMgr->onCastFinish( *pPlayer, m_pTarget, m_id );
  }
}

void Sapphire::Action::Action::buildEffectPacket()
{
  for( int i = 0; i < EffectPacketIdentity::MAX_ACTION_EFFECT_PACKET_IDENT; ++i )
  {
    auto& packetData = m_effects[ static_cast< EffectPacketIdentity >( i ) ];

    // todo: this
  }
}

void Sapphire::Action::Action::damageTarget( uint32_t amount, Entity::Chara& chara,
                                             Common::ActionAspect aspect )
{
  Common::EffectEntry entry{};

  // todo: handle cases where the action misses/is blocked?
  entry.effectType = Common::ActionEffectType::Damage;

  // todo: handle crits
  entry.hitSeverity = Common::ActionHitSeverityType::NormalDamage;

  // todo: handle > 65535 damage values, not sure if this is right?
  if( amount > 65535 )
  {
    entry.value = static_cast< int16_t >( amount / 10 );
    // todo: rename this? need to confirm how it works again
    entry.bonusPercent = 1;
  }
  else
    entry.value = static_cast< int16_t >( amount );

  // todo: aspected damage?
  chara.takeDamage( amount );

  m_effects[ EffectPacketIdentity::DamageEffect ].m_entries.emplace_back( entry );

  // todo: make sure that we don't add the same actor more than once
  m_effects[ EffectPacketIdentity::DamageEffect ].m_hitActors.emplace_back( chara.getId() );
}

void Sapphire::Action::Action::healTarget( uint32_t amount, Entity::Chara& chara )
{
  Common::EffectEntry entry{};

  entry.effectType = Common::ActionEffectType::Heal;

  // todo: handle crits
  entry.hitSeverity = Common::ActionHitSeverityType::NormalHeal;

  // todo: handle > 65535 healing values, not sure if this is right?
  if( amount > 65535 )
  {
    entry.value = static_cast< int16_t >( amount / 10 );
    // todo: rename this? need to confirm how it works again
    entry.bonusPercent = 1;
  }
  else
    entry.value = static_cast< int16_t >( amount );

  chara.heal( amount );

  m_effects[ EffectPacketIdentity::HealingEffect ].m_entries.emplace_back( entry );

  // todo: make sure that we don't add the same actor more than once
  m_effects[ EffectPacketIdentity::HealingEffect ].m_hitActors.emplace_back( chara.getId() );
}

const Sapphire::Action::Action::ActionCostArray& Sapphire::Action::Action::getCostArray() const
{
  return m_actionCost;
}

void Sapphire::Action::Action::calculateActionCost()
{
  for( uint8_t i = 0; i < m_actionCost.size(); ++i )
  {
    auto& entry = m_actionCost[ i ];

    if( entry.m_costType == ActionCostType::MagicPoints )
      calculateMPCost( i );
  }
}

void Sapphire::Action::Action::calculateMPCost( uint8_t costArrayIndex )
{
  auto level = m_pSource->getLevel();

  // each level range is 1-10, 11-20, 21-30, ... therefore:
  // level 50 should be in the 4th group, not the 5th
  // dividing by 10 on the border will break this unless we subtract 1
  auto levelGroup = std::max< uint8_t >( level - 1, 1 ) / 10;

  auto& costEntry = m_actionCost[ costArrayIndex ];

  float cost = costEntry.m_cost;

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

  // m_cost is the base cost, cost is the multiplier for the current player level
  costEntry.m_cost = static_cast< uint16_t >( std::round( cost * costEntry.m_cost ) );
}