#include <Exd/ExdData.h>
#include <Util/Util.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <Logging/Logger.h>

#include <algorithm>
#include <Service.h>

#include "Actor/Chara.h"
#include "Actor/GameObject.h"

#include "Script/ScriptMgr.h"

#include "StatusEffect.h"

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
//using namespace Sapphire::Network::Packets::WorldPackets::Server;

Sapphire::StatusEffect::StatusEffect::StatusEffect( uint32_t id, Entity::CharaPtr sourceActor, Entity::CharaPtr targetActor,
                                                    uint32_t duration, std::vector< World::Action::StatusModifier >& modifiers, uint32_t tickRate ) :
  StatusEffect( id, sourceActor, targetActor, duration, tickRate )
{
  m_modifiers = std::move( modifiers );
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
  m_lastTick( 0 )
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

uint32_t Sapphire::StatusEffect::StatusEffect::getTargetActorId() const
{
  return m_targetActor->getId();
}

uint16_t Sapphire::StatusEffect::StatusEffect::getParam() const
{
  return m_param;
}

void Sapphire::StatusEffect::StatusEffect::applyStatus()
{
  m_startTime = Util::getTimeMs();
  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();

  for( const auto& mod : m_modifiers )
  {
    // TODO: ticks
    if( mod.modifier != Common::ParamModifier::TickDamage && mod.modifier != Common::ParamModifier::TickHeal )
      m_targetActor->addModifier( mod.modifier, mod.value );
    else if( mod.modifier == Common::ParamModifier::TickDamage )
      registerTickEffect( mod.modifier, mod.value );
    else if( mod.modifier == Common::ParamModifier::TickHeal )
      registerTickEffect( mod.modifier, mod.value );
  }

  m_targetActor->calculateStats();

  // this is only right when an action is being used by the player
  // else you probably need to use an actorcontrol

  //GamePacketNew< FFXIVIpcEffect > effectPacket( m_sourceActor->getId() );
  //effectPacket.data().targetId = m_sourceActor->getId();
  //effectPacket.data().actionAnimationId = 3;
  //effectPacket.data().unknown_3 = 1;
  //effectPacket.data().actionTextId = 3;
  //effectPacket.data().unknown_5 = 1;
  //effectPacket.data().unknown_6 = 321;
  //effectPacket.data().rotation = ( uint16_t ) ( 0x8000 * ( ( m_sourceActor->getPos().getR() + 3.1415926 ) ) / 3.1415926 );
  //effectPacket.data().effectTargetId = m_sourceActor->getId();
  //effectPacket.data().effects[4].unknown_1 = 17;
  //effectPacket.data().effects[4].bonusPercent = 30;
  //effectPacket.data().effects[4].param1 = m_id;
  //effectPacket.data().effects[4].unknown_5 = 0x80;
  //m_sourceActor->sendToInRangeSet( effectPacket, true );

  scriptMgr.onStatusReceive( m_targetActor, m_id );
}

void Sapphire::StatusEffect::StatusEffect::removeStatus()
{
  auto& scriptMgr = Common::Service< Scripting::ScriptMgr >::ref();

  for( const auto& mod : m_modifiers )
  {
    if( mod.modifier != Common::ParamModifier::TickDamage && mod.modifier != Common::ParamModifier::TickHeal )
      m_targetActor->delModifier( mod.modifier, mod.value );
  }

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
