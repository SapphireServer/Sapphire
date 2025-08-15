#include <Exd/ExdData.h>
#include <Util/Util.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <Logging/Logger.h>

#include <algorithm>
#include <Service.h>

#include "Action/ActionLut.h"
#include "Actor/Chara.h"
#include "Actor/BNpc.h"
#include "Actor/Player.h"
#include "Actor/GameObject.h"
#include "Common.h"
#include "Manager/PlayerMgr.h"
#include "Manager/StatusEffectMgr.h"

#include <Math/CalcStats.h>
#include "Util/UtilMath.h"

#include "Script/ScriptMgr.h"

#include "StatusEffect.h"

using namespace Sapphire;
using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;

Sapphire::StatusEffect::StatusEffect::StatusEffect( uint32_t id, Entity::CharaPtr sourceActor, Entity::CharaPtr targetActor,
                                                    uint32_t duration, const std::vector< World::Action::StatusModifier >& modifiers, uint32_t flag, uint32_t tickRate ) :
  StatusEffect( id, sourceActor, targetActor, duration, tickRate )
{
  m_statusModifiers = modifiers;
  m_flag = flag;
}

Sapphire::StatusEffect::StatusEffect::StatusEffect( uint32_t id, Entity::CharaPtr sourceActor, Entity::CharaPtr targetActor,
                                                    uint32_t duration, const std::vector< World::Action::StatusModifier >& modifiers, const World::Action::GroundAOE& groundAOE,
                                                    uint32_t flag, uint32_t tickRate ) :
  StatusEffect( id, sourceActor, targetActor, duration, tickRate )
{
  m_statusModifiers = modifiers;
  m_groundAOE = groundAOE;
  m_flag = flag;
}

Sapphire::StatusEffect::StatusEffect::StatusEffect( uint32_t id, Entity::CharaPtr sourceActor, Entity::CharaPtr targetActor,
                                                    uint32_t duration, uint32_t tickRate ) :
  m_id( id ),
  m_sourceActor( sourceActor ),
  m_targetActor( targetActor ),
  m_duration( duration ),
  m_modifiers( {} ),
  m_startTime( 0 ),
  m_tickRate( tickRate ),
  m_lastTick( 0 ),
  m_flag( 0 )
{
  auto& exdData = Common::Service< Data::ExdData >::ref();
  auto entry = exdData.getRow< Excel::Status >( id );
  m_name = entry->getString( entry->data().Text.Name );

  std::replace( m_name.begin(), m_name.end(), ' ', '_' );
  std::replace( m_name.begin(), m_name.end(), ':', '_' );
  std::replace( m_name.begin(), m_name.end(), '&', '_' );
  std::replace( m_name.begin(), m_name.end(), '+', 'p' );
  Util::eraseAll( m_name, '\'' );
  Util::eraseAll( m_name, '&' );
  Util::eraseAll( m_name, '-' );
  Util::eraseAll( m_name, '(' );
  Util::eraseAll( m_name, ')' );

  m_flag |= entry->data().Category;
  if( entry->data().Forever )
    m_flag |= static_cast< uint32_t >( Common::StatusEffectFlag::Permanent );
  if( entry->data().CanOff )
    m_flag |= static_cast< uint32_t >( Common::StatusEffectFlag::CanStatusOff );
  if( entry->data().NotAction )
    m_flag |= static_cast< uint32_t >( Common::StatusEffectFlag::LockActions );
  if( entry->data().NotControl )
    m_flag |= static_cast< uint32_t >( Common::StatusEffectFlag::LockControl );
  if( entry->data().NotMove )
    m_flag |= static_cast< uint32_t >( Common::StatusEffectFlag::LockMovement );
  if( entry->data().NotLookAt )
    m_flag |= static_cast< uint32_t >( Common::StatusEffectFlag::IsGaze );
  if( entry->data().FcAction )
    m_flag |= static_cast< uint32_t >( Common::StatusEffectFlag::FcBuff );
}


Sapphire::StatusEffect::StatusEffect::~StatusEffect()
{
}

void Sapphire::StatusEffect::StatusEffect::registerTickEffect( ParamModifier type, uint32_t param )
{
  m_currTickEffect = std::make_pair( type, param );
}

std::pair< ParamModifier, uint32_t > Sapphire::StatusEffect::StatusEffect::getTickEffect()
{
  return m_currTickEffect;
}

void Sapphire::StatusEffect::StatusEffect::onTick()
{
  m_lastTick = Util::getTimeMs();

  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();
  bool hasScript = scriptMgr.onStatusTick( m_targetActor, *this );

  if( !hasScript && getFlag() & static_cast< uint32_t >( Common::StatusEffectFlag::GroundTarget ) && m_groundAOE.vfxId > 0 )
  {
    if( auto pAreaObject = m_targetActor->getAreaObject(); pAreaObject->getActionId() == m_groundAOE.actionId )
    {
      auto& statusEffectMgr = Common::Service< World::Manager::StatusEffectMgr >::ref();
      auto inRange = m_targetActor->getInRangeActors();

      // todo: probably use selectors
      for( auto& pActor : inRange )
      {
        // make sure we're only hitting enemies
        if( !pActor->isBattleNpc() || pActor->getAsBNpc()->getEnemyType() == Common::Friendly )
          continue;

        auto pChara = pActor->getAsChara();

        const auto& pos = pAreaObject->getPos();
        const auto& potency = pAreaObject->getActionPotency();
        if( Common::Util::distance( pos, pChara->getPos() ) < 5.f )
        {
          switch( m_groundAOE.aoeType )
          {
            case Common::GroundAOEType::Damage:
            {
              auto dmg = Math::CalcStats::calcActionDamage( *m_sourceActor, potency, 1.0f );
              float damageVal = dmg.first;
              Common::CalcResultType damageType = dmg.second;

              statusEffectMgr.damage( m_sourceActor, pChara, static_cast< int32_t >( damageVal ) );
              break;
            }
            case Common::GroundAOEType::Heal:
            {
              // todo: healing ground AOEs
              break;
            }
          }
        }
      }
    }
  }
}

uint32_t Sapphire::StatusEffect::StatusEffect::getSrcActorId() const
{
  return m_sourceActor->getId();
}

Sapphire::Entity::CharaPtr Sapphire::StatusEffect::StatusEffect::getSrcActor() const
{
  return m_sourceActor;
}

uint32_t Sapphire::StatusEffect::StatusEffect::getTargetActorId() const
{
  return m_targetActor->getId();
}

uint16_t Sapphire::StatusEffect::StatusEffect::getParam() const
{
  return m_param;
}

const std::unordered_map< Common::ParamModifier, int32_t >& Sapphire::StatusEffect::StatusEffect::getModifiers() const
{
  return m_modifiers;
}

void Sapphire::StatusEffect::StatusEffect::setModifier( Common::ParamModifier paramModifier, int32_t value )
{
  m_modifiers[ paramModifier ] = value;

  if( auto pPlayer = m_targetActor->getAsPlayer(); pPlayer )
    Common::Service< World::Manager::PlayerMgr >::ref().sendDebug( *pPlayer, "Modifier: {}, value: {}", static_cast< int32_t >( paramModifier ),
                                                                   pPlayer->getModifier( paramModifier ) );
}

void Sapphire::StatusEffect::StatusEffect::delModifier( Common::ParamModifier paramModifier )
{
  if( m_modifiers.find( paramModifier ) == m_modifiers.end() )
    return;

  m_modifiers.erase( paramModifier );

  if( auto pPlayer = m_targetActor->getAsPlayer(); pPlayer )
    Common::Service< World::Manager::PlayerMgr >::ref().sendDebug( *pPlayer, "Modifier: {}, value: {}", static_cast< int32_t >( paramModifier ),
                                                                   pPlayer->getModifier( paramModifier ) );
}

void Sapphire::StatusEffect::StatusEffect::applyStatus()
{
  m_startTime = Util::getTimeMs();
  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();

  if( m_modifiers.empty() )
  {  
    for( const auto& mod : m_statusModifiers )
    {
      if( mod.modifier != Common::ParamModifier::TickDamage && mod.modifier != Common::ParamModifier::TickHeal )
        setModifier( mod.modifier, mod.value );
      else if( mod.modifier == Common::ParamModifier::TickDamage )
        registerTickEffect( mod.modifier, mod.value );
      else if( mod.modifier == Common::ParamModifier::TickHeal )
        registerTickEffect( mod.modifier, mod.value );
    }
  }

  m_targetActor->calculateStats();

  scriptMgr.onStatusReceive( m_targetActor, m_id );
}

void Sapphire::StatusEffect::StatusEffect::removeStatus()
{
  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();

  m_modifiers.clear();

  m_targetActor->calculateStats();

  if( auto pAreaObject = m_targetActor->getAreaObject() )
  {
    if( pAreaObject->getActionId() == m_groundAOE.actionId )
      m_targetActor->despawnAreaObject();
  }

  scriptMgr.onStatusTimeOut( m_targetActor, m_id );
}

uint32_t Sapphire::StatusEffect::StatusEffect::getId() const
{
  return m_id;
}

uint32_t Sapphire::StatusEffect::StatusEffect::getDuration() const
{
  return m_duration;
}

uint32_t Sapphire::StatusEffect::StatusEffect::getTickRate() const
{
  return m_tickRate;
}

uint64_t Sapphire::StatusEffect::StatusEffect::getLastTickMs() const
{
  return m_lastTick;
}

uint64_t Sapphire::StatusEffect::StatusEffect::getStartTimeMs() const
{
  return m_startTime;
}

uint32_t Sapphire::StatusEffect::StatusEffect::getFlag() const
{
  return m_flag;
}

const std::vector< World::Action::StatusModifier >& Sapphire::StatusEffect::StatusEffect::getStatusModifiers() const
{
  return m_statusModifiers;
}

void Sapphire::StatusEffect::StatusEffect::setFlag( uint32_t flag )
{
  m_flag = flag;
}

void Sapphire::StatusEffect::StatusEffect::setLastTick( uint64_t lastTick )
{
  m_lastTick = lastTick;
}

void Sapphire::StatusEffect::StatusEffect::setParam( uint16_t param )
{
  m_param = param;
}

const std::string& Sapphire::StatusEffect::StatusEffect::getName() const
{
  return m_name;
}

uint8_t Sapphire::StatusEffect::StatusEffect::getSlot() const
{
  return m_slot;
}

void Sapphire::StatusEffect::StatusEffect::setSlot( uint8_t slot )
{
  m_slot = slot;
}

void Sapphire::StatusEffect::StatusEffect::refresh()
{
  applyStatus();
}

void Sapphire::StatusEffect::StatusEffect::refresh( uint32_t newDuration )
{
  m_duration = newDuration;
  refresh();
}