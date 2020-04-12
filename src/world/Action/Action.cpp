#include "Action.h"

#include <Inventory/Item.h>

#include <Exd/ExdDataGenerated.h>
#include <Util/Util.h>
#include "Script/ScriptMgr.h"

#include <Math/CalcStats.h>

#include "Actor/Player.h"
#include "Actor/BNpc.h"

#include "Action/ActionLut.h"

#include "Territory/Territory.h"

#include <Network/CommonActorControl.h>
#include "Network/PacketWrappers/ActorControlPacket.h"
#include "Network/PacketWrappers/ActorControlSelfPacket.h"
#include "Network/PacketWrappers/ActorControlTargetPacket.h"

#include <Logging/Logger.h>

#include <Util/ActorFilter.h>
#include <Util/UtilMath.h>
#include <Service.h>

using namespace Sapphire;
using namespace Sapphire::Common;
using namespace Sapphire::Network;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::Server;
using namespace Sapphire::Network::ActorControl;
using namespace Sapphire::World;


Action::Action::Action() = default;
Action::Action::~Action() = default;

Action::Action::Action( Entity::CharaPtr caster, uint32_t actionId, uint16_t sequence) :
  Action( std::move( caster ), actionId, sequence, nullptr )
{
}

Action::Action::Action( Entity::CharaPtr caster, uint32_t actionId, uint16_t sequence,
                        Data::ActionPtr actionData ) :
  m_pSource( std::move( caster ) ),
  m_actionData( std::move( actionData ) ),
  m_id( actionId ),
  m_targetId( 0 ),
  m_startTime( 0 ),
  m_interruptType( Common::ActionInterruptType::None ),
  m_sequence( sequence ),
  m_isAutoAttack( false ),
  m_disableGenericHandler( false ),
  m_started( false ),
  m_shouldAlwaysCombo( false )
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
    auto& exdData = Common::Service< Data::ExdDataGenerated >::ref();

    auto actionData = exdData.get< Data::Action >( m_id );
    assert( actionData );

    m_actionData = actionData;
  }

  m_effectBuilder = make_EffectBuilder( m_pSource, getId(), m_sequence );

  m_castTimeMs = static_cast< uint32_t >( m_actionData->cast100ms * 100 );
  m_recastTimeMs = static_cast< uint32_t >( m_actionData->recast100ms * 100 );
  auto actionCategory = static_cast< Common::ActionCategory >( m_actionData->actionCategory );
  if( actionCategory == Common::ActionCategory::Spell || actionCategory == Common::ActionCategory::Weaponskill )
  {
    m_castTimeMs = static_cast< uint32_t >( m_castTimeMs * ( m_pSource->getStatValue( Common::BaseParam::Haste ) / 100.0f ) );
    m_recastTimeMs = static_cast< uint32_t >( m_recastTimeMs * ( m_pSource->getStatValue( Common::BaseParam::Haste ) / 100.0f ) );
  }

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

  if( m_primaryCostType != Common::ActionPrimaryCostType::None )
  {
    for( auto const& entry : m_pSource->getStatusEffectMap() )
    {
      if( entry.second->getParam() == 65436 ) // todo: decode this shit and figure out exact percentage to apply to primary cost, this magic number is 0%
      {
        /*
        Since the client is displaying correctly without additional data, there should be a "primary primary cost type" defined for each class.
        In the case of 65436, on whm, mp cost is removed, on drk, blood cost is removed but mp cost remains.
        */
        auto affectedPrimaryCost = Common::ActionPrimaryCostType::MagicPoints;
        switch( m_pSource->getClass() )
        {
          case Common::ClassJob::Marauder:
          case Common::ClassJob::Warrior:
          {
            affectedPrimaryCost = Common::ActionPrimaryCostType::WARGauge;
            break;
          }
          case Common::ClassJob::Darkknight:
          {
            affectedPrimaryCost = Common::ActionPrimaryCostType::DRKGauge;
            break;
          }
        }
        if( m_primaryCostType == affectedPrimaryCost )
        {
          setPrimaryCost( Common::ActionPrimaryCostType::None, 0 );
        }
        
        break;
      }
    }
  }

  if( auto player = m_pSource->getAsPlayer() )
  {
    switch( player->getClass() )
    {
      case Common::ClassJob::Darkknight:
      {
        if( m_primaryCostType == Common::ActionPrimaryCostType::MagicPoints && player->gaugeDrkGetDarkArts() )
        {
          setPrimaryCost( Common::ActionPrimaryCostType::None, 0 );
          player->gaugeDrkSetDarkArts( false );
        }
        break;
      }
    }
  }

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

  m_effectBuilder->setAnimationLock( getAnimationLock() );

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

  if( !hasCastTime() || std::difftime( static_cast< time_t >( tickCount ), static_cast< time_t >( m_startTime ) ) > m_castTimeMs )
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
      interrupt();
      return true;
    }
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
    data.rotation = Common::Util::floatToUInt16Rot( m_pSource->getRot() );

    m_pSource->sendToInRangeSet( castPacket, true );

    if( player )
    {
      player->setStateFlag( PlayerStateFlag::Casting );
    }
  }

  if( player )
  {
    // todo: m_recastTimeMs needs to be adjusted for player sks/sps
    auto actionStartPkt = makeActorControlSelf( m_pSource->getId(), ActorControlType::ActionStart, 1, getId(),
      m_recastTimeMs / 10 );
    player->queuePacket( actionStartPkt );
  }

  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();
  scriptMgr.onStart( *this );

  // instantly finish cast if there's no cast time
  if( !hasCastTime() )
    execute();

  m_started = true;
}

void Action::Action::interrupt( ActionInterruptType type )
{
  if( isInterrupted() )
    return;

  assert( m_pSource );

  m_interruptType = type;

  // things that aren't players don't care about cooldowns and state flags
  if( m_pSource->isPlayer() )
  {
    auto player = m_pSource->getAsPlayer();

    // todo: reset cooldown for actual player

    // reset state flag
    //player->unsetStateFlag( PlayerStateFlag::Occupied1 );
    player->unsetStateFlag( PlayerStateFlag::Casting );
  }

  if( m_started && hasCastTime() )
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
      player->unsetStateFlag( PlayerStateFlag::Casting );
    }
  }

  if( isCorrectCombo() )
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
    scriptMgr.onEObjHit( *player, m_targetId, getId() );
  }

  m_started = false;

  // set currently casted action as the combo action if it interrupts a combo
  // ignore it otherwise (ogcds, etc.)
  if( !m_actionData->preservesCombo )
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
  if( m_isAutoAttack )
    return Math::CalcStats::calcAutoAttackDamage( *m_pSource, potency );
  else
    return Math::CalcStats::calcActionDamage( this, *m_pSource, potency, Math::CalcStats::getWeaponDamage( m_pSource ) );
}

std::pair< uint32_t, Common::ActionHitSeverityType > Action::Action::calcHealing( uint32_t potency )
{
  return Math::CalcStats::calcActionHealing( this, *m_pSource, potency, Math::CalcStats::getWeaponDamage( m_pSource ) );
}

void Action::Action::buildEffects()
{
  snapshotAffectedActors( m_hitActors );

  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();

  for( const auto& statusIt : m_pSource->getStatusEffectMap() )
  {
    statusIt.second->onActionExecute( this );
  }

  scriptMgr.onExecute( *this );

  if( isInterrupted() )
    return;

  if( m_disableGenericHandler || !hasValidLutEntry() )
  {
    // send any effect packet added by script or an empty one just to play animation for other players
    scriptMgr.onBeforeBuildEffect( *this, 0, 0 );
    m_effectBuilder->buildAndSendPackets();
    scriptMgr.onAfterBuildEffect( *this );
    return;
  }
  
  // we have a valid lut entry
  auto player = getSourceChara()->getAsPlayer();
  if( player )
  {
    player->sendDebug( "type: {}, dpot: {} (dcpot: {}, ddpot: {}), hpot: {}, ss: {}, ts: {}, bonus: {}, breq: {}, bdata: {}",
                       m_actionData->attackType,
                       m_lutEntry.damagePotency, m_lutEntry.damageComboPotency, m_lutEntry.damageDirectionalPotency,
                       m_lutEntry.healPotency, m_lutEntry.selfStatus, m_lutEntry.targetStatus,
                       m_lutEntry.bonusEffect, m_lutEntry.bonusRequirement, m_lutEntry.bonusDataUInt32 );
  }

  uint8_t victimCounter = 0, validVictimCounter = 0;

  for( auto& actor : m_hitActors )
  {
    victimCounter++;
    bool shouldHitThisTarget = true;
    for( const auto& statusIt : getSourceChara()->getStatusEffectMap() )
    {
      bool result = statusIt.second->onActionHitTarget( this, actor, victimCounter );
      if( !result )
        shouldHitThisTarget = false;
    }
    if( !shouldHitThisTarget )
      continue;
    if( m_lutEntry.damagePotency > 0 )
    {
      Common::AttackType attackType = static_cast< Common::AttackType >( m_actionData->attackType );
      actor->onActionHostile( m_pSource );
      
      auto dmg = calcDamage( isCorrectCombo() ? m_lutEntry.damageComboPotency : m_lutEntry.damagePotency );
      if( victimCounter > 1 )
      {
        if( m_lutEntry.bonusEffect & Common::ActionBonusEffect::DamageFallOff )
        {
          if( checkActionBonusRequirement() )
          {
            dmg.first = static_cast< uint32_t >( 1.0 * dmg.first * ( m_lutEntry.bonusDataByte1 / 100.0 ) );
          }
        }
      }
      dmg.first = Math::CalcStats::applyDamageReceiveMultiplier( *actor, dmg.first, attackType );

      float originalDamage = dmg.first;
      bool dodged = false;
      float blocked = 0;
      float parried = 0;

      if( dmg.first > 0 )
      {
        dodged = Math::CalcStats::calcDodge( *actor );

        if( !dodged && dmg.second == Common::ActionHitSeverityType::NormalDamage && actor->isPlayer() )
        {
          blocked = Math::CalcStats::calcBlock( *actor, dmg.first );
        }

        if( !dodged && blocked == 0 && dmg.second == Common::ActionHitSeverityType::NormalDamage && actor->isPlayer() )
        {
          if( isPhysical() )
          {
            parried = Math::CalcStats::calcParry( *actor, dmg.first );
          }
        }
      }

      if( dodged )
        dmg.first = 0;
      else
      {
        dmg.first -= blocked;
        dmg.first -= parried;
      }

      if( dmg.first > 0 )
      {
        dmg.first = actor->applyShieldProtection( dmg.first );
        if( blocked > 0 )
          m_effectBuilder->blockedDamage( actor, actor, dmg.first, static_cast< uint16_t >( blocked / originalDamage * 100 ) , dmg.first == 0 ? Common::ActionEffectResultFlag::Absorbed : Common::ActionEffectResultFlag::None );
        else if (parried > 0 )
          m_effectBuilder->parriedDamage( actor, actor, dmg.first, static_cast< uint16_t >( parried / originalDamage * 100 ), dmg.first == 0 ? Common::ActionEffectResultFlag::Absorbed : Common::ActionEffectResultFlag::None );
        else
          m_effectBuilder->damage( actor, actor, dmg.first, dmg.second, dmg.first == 0 ? Common::ActionEffectResultFlag::Absorbed : Common::ActionEffectResultFlag::None );

        auto reflectDmg = Math::CalcStats::calcDamageReflect( m_pSource, actor, dmg.first,
          attackType == Common::AttackType::Physical ? Common::ActionTypeFilter::Physical :
          ( attackType == Common::AttackType::Magical ? Common::ActionTypeFilter::Magical : Common::ActionTypeFilter::Unknown ) );
        if( reflectDmg.first > 0 )
        {
          m_effectBuilder->damage( actor, m_pSource, reflectDmg.first, reflectDmg.second, Common::ActionEffectResultFlag::Reflected );
        }

        auto absorb = Math::CalcStats::calcAbsorbHP( m_pSource, dmg.first );
        if( absorb > 0 )
        {
          if( absorb > actor->getHp() )
            absorb = actor->getHp();
          m_effectBuilder->heal( actor, m_pSource, absorb, Common::ActionHitSeverityType::NormalHeal, Common::ActionEffectResultFlag::EffectOnSource );
        }
      }
      else
      {
        if( dodged )
        {
          m_effectBuilder->dodge( actor, actor );
        }
        else
        {
          // todo: no effect or invulnerable
        }
      }

      if( !dodged )
      {
        if( ( !isComboAction() || isCorrectCombo() ) )
        {
          if ( !m_actionData->preservesCombo ) // this matches retail packet, on all standalone actions even casts.
          {
            m_effectBuilder->startCombo( actor, getId() ); // this is on all targets hit
          }
        }

        if( m_lutEntry.bonusEffect & Common::ActionBonusEffect::SelfHeal )
        {
          if( checkActionBonusRequirement() )
          {
            auto heal = calcHealing( m_lutEntry.bonusDataUInt16L );
            heal.first = Math::CalcStats::applyHealingReceiveMultiplier( *m_pSource, heal.first );
            m_effectBuilder->heal( actor, m_pSource, heal.first, heal.second, Common::ActionEffectResultFlag::EffectOnSource );
          }
        }

        if( validVictimCounter == 0 )
        {
          if( isCorrectCombo() )
            m_effectBuilder->comboSucceed( actor );

          if( m_isAutoAttack && m_pSource->isPlayer() )
          {
            if( auto player = m_pSource->getAsPlayer() )
            {
              if( player->getClass() == Common::ClassJob::Paladin )
              {
                player->gaugePldSetOath( std::min( 100, player->gaugePldGetOath() + 5 ) );
              }
            }
          }

          if( m_lutEntry.bonusEffect & Common::ActionBonusEffect::GainMPPercentage )
          {
            if( checkActionBonusRequirement() )
              m_effectBuilder->restoreMP( actor, m_pSource, m_pSource->getMaxMp() * m_lutEntry.bonusDataUInt16L / 100, Common::ActionEffectResultFlag::EffectOnSource );
          }

          if( m_lutEntry.bonusEffect & Common::ActionBonusEffect::GainJobResource )
          {
            if( checkActionBonusRequirement() )
            {
              switch( static_cast< Common::ClassJob >( m_lutEntry.bonusDataByte3 ) )
              {
                case Common::ClassJob::Marauder:
                case Common::ClassJob::Warrior:
                {
                  player->gaugeWarSetIb( std::min( 100, player->gaugeWarGetIb() + m_lutEntry.bonusDataByte4 ) );
                  break;
                }
                case Common::ClassJob::Darkknight:
                {
                  player->gaugeDrkSetBlood( std::min( 100, player->gaugeDrkGetBlood() + m_lutEntry.bonusDataByte4 ) );
                  break;
                }
                case Common::ClassJob::Gunbreaker:
                {
                  player->gaugeGnbSetAmmo( std::min( 2, player->gaugeGnbGetAmmo() + m_lutEntry.bonusDataByte4 ) );
                  break;
                }
                case Common::ClassJob::Samurai:
                {
                  player->gaugeSamSetKenki( std::min( 100, player->gaugeSamGetKenki() + m_lutEntry.bonusDataByte4 ) );
                  break;
                }
              }
            }
          }

          if( m_lutEntry.bonusEffect & Common::ActionBonusEffect::GainJobTimer )
          {
            if( checkActionBonusRequirement() )
            {
              switch( static_cast< Common::ClassJob >( m_lutEntry.bonusDataByte3 ) )
              {
                case Common::ClassJob::Darkknight:
                {
                  player->gaugeDrkSetDarkSideTimer( std::min( 60000, player->gaugeDrkGetDarkSideTimer() + m_lutEntry.bonusDataUInt16L ), true );
                  break;
                }
              }
            }
          }
        }
        validVictimCounter++;
      }
    }

    if( m_lutEntry.healPotency > 0 )
    {
      auto heal = calcHealing( m_lutEntry.healPotency );
      heal.first = Math::CalcStats::applyHealingReceiveMultiplier( *actor, heal.first );
      m_effectBuilder->heal( actor, actor, heal.first, heal.second );
    }

    if( m_lutEntry.targetStatus != 0 )
    {
      if( !isComboAction() || isCorrectCombo() )
        m_effectBuilder->applyStatusEffect( actor, m_pSource, m_lutEntry.targetStatus, m_lutEntry.targetStatusDuration, m_lutEntry.targetStatusParam );
    }
  }

  if( m_lutEntry.selfStatus != 0 )
  {
    if( !isComboAction() || isCorrectCombo() )
      m_effectBuilder->applyStatusEffect( m_pSource, m_pSource, m_lutEntry.selfStatus, m_lutEntry.selfStatusDuration, m_lutEntry.selfStatusParam );
  }

  scriptMgr.onBeforeBuildEffect( *this, victimCounter, validVictimCounter );
  m_effectBuilder->buildAndSendPackets();
  scriptMgr.onAfterBuildEffect( *this );

  // at this point we're done with it and no longer need it
  m_effectBuilder.reset();
}

bool Action::Action::preCheck()
{
  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();
  scriptMgr.onBeforePreCheck( *this );

  if( isInterrupted() )
    return false;

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
  if( m_actionData->classJob == -1 && !m_actionData->isRoleAction )
    return false;

  if( player.getLevel() < m_actionData->classJobLevel )
    return false;

  auto currentClass = player.getClass();
  auto actionClass = static_cast< Common::ClassJob >( m_actionData->classJob );

  if( actionClass != Common::ClassJob::Adventurer && currentClass != actionClass && !m_actionData->isRoleAction )
  {
    // check if not a base class action
    auto& exdData = Common::Service< Data::ExdDataGenerated >::ref();

    auto classJob = exdData.get< Data::ClassJob >( static_cast< uint8_t >( currentClass ) );
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

bool Action::Action::isCorrectCombo() const
{
  if( m_shouldAlwaysCombo )
    return true;

  auto lastActionId = m_pSource->getLastComboActionId();

  if( lastActionId == 0 )
  {
    return false;
  }

  return m_actionData->actionCombo == lastActionId;
}

bool Action::Action::isComboAction() const
{
  return m_actionData->actionCombo != 0;
}

void Sapphire::World::Action::Action::setAlwaysCombo()
{
  m_shouldAlwaysCombo = true;
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

      if( curMp < static_cast< uint32_t >( cost ) )
        return false;

      if( subtractCosts )
        m_pSource->setMp( curMp - static_cast< uint32_t >( cost ) );

      return true;
    }

    case Common::ActionPrimaryCostType::StatusEffect:
    {
      auto statusEntry = m_pSource->getStatusEffectById( m_primaryCost );

      if( !statusEntry.second )
        return false;

      if( subtractCosts )
        m_pSource->removeStatusEffect( statusEntry.first );

      return true;
    }

    case Common::ActionPrimaryCostType::WARGauge:
    {
      auto pPlayer = m_pSource->getAsPlayer();
      if( pPlayer )
      {
        auto ib = pPlayer->gaugeWarGetIb();
        if( ib >= m_primaryCost )
        {
          if( subtractCosts )
            pPlayer->gaugeWarSetIb( ib - m_primaryCost );

          return true;
        }
      }
      return false;
    }

    case Common::ActionPrimaryCostType::PLDGauge:
    {
      auto pPlayer = m_pSource->getAsPlayer();
      if( pPlayer )
      {
        auto oath = pPlayer->gaugePldGetOath();
        if( oath >= m_primaryCost )
        {
          if( subtractCosts )
            pPlayer->gaugePldSetOath( oath - m_primaryCost );

          return true;
        }
      }
      return false;
    }

    case Common::ActionPrimaryCostType::WHMBloodLily:
    {
      auto pPlayer = m_pSource->getAsPlayer();
      if( pPlayer )
      {
        auto bloodLily = pPlayer->gaugeWhmGetBloodLily();
        if( bloodLily >= m_primaryCost )
        {
          if( subtractCosts )
            pPlayer->gaugeWhmSetLilies( pPlayer->gaugeWhmGetLily(), bloodLily - m_primaryCost );

          return true;
        }
      }
      return false;
    }

    case Common::ActionPrimaryCostType::WHMLily:
    {
      auto pPlayer = m_pSource->getAsPlayer();
      if( pPlayer )
      {
        auto lily = pPlayer->gaugeWhmGetLily();
        if( lily >= m_primaryCost )
        {
          if( subtractCosts )
          {
            lily -= m_primaryCost;
            auto bloodLily = pPlayer->gaugeWhmGetBloodLily();
            if( pPlayer->getLevel() >= 74 )
            {
              bloodLily = std::min( 3, bloodLily + m_primaryCost );
            }
            pPlayer->gaugeWhmSetLilies( lily, bloodLily );
          }

          return true;
        }
      }
      return false;
    }

    case Common::ActionPrimaryCostType::DRKGauge:
    {
      auto pPlayer = m_pSource->getAsPlayer();
      if( pPlayer )
      {
        auto blood = pPlayer->gaugeDrkGetBlood();
        if( blood >= m_primaryCost )
        {
          if( subtractCosts )
            pPlayer->gaugeDrkSetBlood( blood - m_primaryCost );

          return true;
        }
      }
      return false;
    }

    case Common::ActionPrimaryCostType::GNBAmmo:
    {
      auto pPlayer = m_pSource->getAsPlayer();
      if( pPlayer )
      {
        auto ammo = pPlayer->gaugeGnbGetAmmo();
        if( ammo >= m_primaryCost )
        {
          if( subtractCosts )
            pPlayer->gaugeGnbSetAmmo( ammo - m_primaryCost );

          return true;
        }
      }
      return false;
    }

    case Common::ActionPrimaryCostType::SAMKenki:
    {
      auto pPlayer = m_pSource->getAsPlayer();
      if( pPlayer )
      {
        auto kenki = pPlayer->gaugeSamGetKenki();
        if( kenki >= m_primaryCost )
        {
          if( subtractCosts )
            pPlayer->gaugeSamSetKenki( kenki - m_primaryCost );

          return true;
        }
      }
      return false;
    }

    case Common::ActionPrimaryCostType::SAMSen:
    {
      auto pPlayer = m_pSource->getAsPlayer();
      if( pPlayer )
      {
        // trust the client and assume the action is correct, you can cheat this by performing one sen midare :)
        if( pPlayer->gaugeSamHasAnySen() )
        {
          if( subtractCosts )
            pPlayer->gaugeSamSetSen( Common::SamSen::None );

          return true;
        }
      }
      return false;
    }

    case Common::ActionPrimaryCostType::SAMMeditation:
    {
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

bool Action::Action::preFilterActor( Sapphire::Entity::Actor& actor ) const
{
  auto kind = actor.getObjKind();
  auto chara = actor.getAsChara();

  // todo: are there any server side eobjs that players can hit?
  if( kind != ObjKind::BattleNpc && kind != ObjKind::Player )
    return false;
  
  if( m_lutEntry.damagePotency > 0 && chara->getId() == m_pSource->getId() ) // !m_canTargetSelf
    return false;
  
  if( ( m_lutEntry.damagePotency > 0 || m_lutEntry.healPotency > 0 ) && !chara->isAlive() ) // !m_canTargetDead not working for aoe
    return false;

  if( m_lutEntry.damagePotency > 0 && m_pSource->getObjKind() == chara->getObjKind() ) // !m_canTargetFriendly not working for aoe
    return false;

  if( ( m_lutEntry.damagePotency == 0 && m_lutEntry.healPotency > 0 ) && m_pSource->getObjKind() != chara->getObjKind() ) // !m_canTargetHostile not working for aoe
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
  return m_lutEntry.damagePotency != 0 || m_lutEntry.healPotency != 0 || m_lutEntry.selfStatus != 0 ||
    m_lutEntry.targetStatus != 0 || m_lutEntry.bonusEffect != 0;
}

float Action::Action::getAnimationLock()
{
  switch( static_cast< Common::ActionCategory >( m_actionData->actionCategory ) )
  {
    case Common::ActionCategory::Item:
    {
      return 1.1f;
    }
    case Common::ActionCategory::Mount:
    {
      return 0.1f;
    }
  }
  return hasCastTime() ? 0.1f : 0.6f;
}

Action::EffectBuilderPtr Action::Action::getEffectbuilder()
{
  return m_effectBuilder;
}

Data::ActionPtr Action::Action::getActionData()
{
  return m_actionData;
}

Action::ActionEntry& Action::Action::getActionEntry()
{
  return m_lutEntry;
}

void Action::Action::setAutoAttack()
{
  m_isAutoAttack = true;
}

void Action::Action::disableGenericHandler()
{
  m_disableGenericHandler = true;
}

bool Action::Action::isPhysical() const
{
  return isAttackTypePhysical( static_cast< Common::AttackType >( m_actionData->attackType ) );
}

bool Action::Action::isMagical() const
{
  return isAttackTypeMagical( static_cast< Common::AttackType >( m_actionData->attackType ) );
}

bool Action::Action::isGCD() const
{
  auto actionCategory = static_cast< Common::ActionCategory >( m_actionData->actionCategory );
  return actionCategory == Common::ActionCategory::Weaponskill || actionCategory == Common::ActionCategory::Spell;
}

bool Action::Action::isWeaponSkill() const
{
  auto actionCategory = static_cast< Common::ActionCategory >( m_actionData->actionCategory );
  return actionCategory == Common::ActionCategory::Weaponskill;
}

bool Action::Action::isAttackTypePhysical( Common::AttackType attackType )
{
  return attackType == Common::AttackType::Physical;
}

bool Action::Action::isAttackTypeMagical( Common::AttackType attackType )
{
  return attackType == Common::AttackType::Magical;
}

void Action::Action::setPrimaryCost( Common::ActionPrimaryCostType type, uint16_t cost )
{
  m_primaryCostType = type;
  m_primaryCost = cost;
}

bool Action::Action::checkActionBonusRequirement()
{
  if( !m_pSource->isPlayer() )
    return false;

  if( m_lutEntry.bonusRequirement & Common::ActionBonusEffectRequirement::RequireCorrectCombo )
  {
    if( !isCorrectCombo() )
      return false;
  }
  if( m_lutEntry.bonusRequirement & Common::ActionBonusEffectRequirement::RequireCorrectPositional )
  {
    // todo
  }

  return true;
}