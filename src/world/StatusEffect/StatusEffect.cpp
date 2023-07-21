#include <Exd/ExdData.h>
#include <Util/Util.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <Logging/Logger.h>

#include <algorithm>
#include <Service.h>

#include "Manager/PlayerMgr.h"

#include "Actor/Chara.h"
#include "Actor/Player.h"
#include "Actor/GameObject.h"

#include "Script/ScriptMgr.h"

#include "StatusEffect.h"

using namespace Sapphire;
using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
//using namespace Sapphire::Network::Packets::WorldPackets::Server;

Sapphire::StatusEffect::StatusEffect::StatusEffect( uint32_t id, Entity::CharaPtr sourceActor, Entity::CharaPtr targetActor,
                                                    uint32_t duration,std::vector< World::Action::StatusModifier >& modifiers,
                                                    uint32_t flag, uint32_t tickRate, bool canApplyMultipleTimes ) :
  StatusEffect( id, sourceActor, targetActor, duration, tickRate )
{
  m_statusModifiers = std::move( modifiers );
  m_flag = flag;
  m_canApplyMultipleTimes = canApplyMultipleTimes;
}

Sapphire::StatusEffect::StatusEffect::StatusEffect( uint32_t id, Entity::CharaPtr sourceActor, Entity::CharaPtr targetActor,
                                                    uint32_t duration, uint32_t tickRate ) :
  m_id( id ),
  m_sourceActor( sourceActor ),
  m_targetActor( targetActor ),
  m_duration( duration ),
  m_modifiers( 0 ),
  m_startTime( 0 ),
  m_tickRate( tickRate ),
  m_lastTick( 0 ),
  m_flag( 0 ),
  m_canApplyMultipleTimes( false )
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
  m_flag |= static_cast< uint32_t >( entry->data().Forever ) << static_cast< uint32_t >( Common::StatusEffectFlag::Permanent );
  m_flag |= static_cast< uint32_t >( entry->data().CanOff ) << static_cast< uint32_t >( Common::StatusEffectFlag::CanStatusOff );
  m_flag |= static_cast< uint32_t >( entry->data().NotAction ) << static_cast< uint32_t >( Common::StatusEffectFlag::LockActions );
  m_flag |= static_cast< uint32_t >( entry->data().NotControl ) << static_cast< uint32_t >( Common::StatusEffectFlag::LockControl );
  m_flag |= static_cast< uint32_t >( entry->data().NotMove ) << static_cast< uint32_t >( Common::StatusEffectFlag::LockMovement );
  m_flag |= static_cast< uint32_t >( entry->data().NotLookAt ) << static_cast< uint32_t >( Common::StatusEffectFlag::IsGaze );
  m_flag |= static_cast< uint32_t >( entry->data().FcAction ) << static_cast< uint32_t >( Common::StatusEffectFlag::FcBuff );
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
  scriptMgr.onStatusTick( m_targetActor, *this );
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

std::unordered_map< Common::ParamModifier, int32_t >& Sapphire::StatusEffect::StatusEffect::getModifiers()
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

  for( const auto& mod : m_statusModifiers )
  {
    if( mod.modifier != Common::ParamModifier::TickDamage && mod.modifier != Common::ParamModifier::TickHeal )
      setModifier( mod.modifier, mod.value );
    else if( mod.modifier == Common::ParamModifier::TickDamage )
      registerTickEffect( mod.modifier, mod.value );
    else if( mod.modifier == Common::ParamModifier::TickHeal )
      registerTickEffect( mod.modifier, mod.value );
  }

  m_targetActor->calculateStats();

  scriptMgr.onStatusReceive( m_targetActor, m_id );
}

void Sapphire::StatusEffect::StatusEffect::removeStatus()
{
  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();

  m_modifiers.clear();

  m_targetActor->calculateStats();

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

bool Sapphire::StatusEffect::StatusEffect::getCanApplyMultipleTimes() const
{
  return m_canApplyMultipleTimes;
}

std::vector< World::Action::StatusModifier > Sapphire::StatusEffect::StatusEffect::getStatusModifiers() const
{
  return m_statusModifiers;
}

void Sapphire::StatusEffect::StatusEffect::setFlag( uint32_t flag )
{
  m_flag = flag;
}

void Sapphire::StatusEffect::StatusEffect::setCanApplyMultipleTimes( bool canApplyMultipleTimes )
{
  m_canApplyMultipleTimes = canApplyMultipleTimes;
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
