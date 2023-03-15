#include <Network/PacketContainer.h>
#include <Exd/ExdData.h>

#include <utility>

#include "Actor/Player.h"

#include "Territory/Territory.h"

#include "Action/EventAction.h"
#include "Manager/PlayerMgr.h"
#include "Service.h"
#include <Network/Util/PacketUtil.h>

using namespace Sapphire;
using namespace Sapphire::Common;
using namespace Sapphire::Entity;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets::Server;
using namespace Sapphire::World::Manager;

void Player::addEvent( Event::EventHandlerPtr pEvent )
{
  m_eventHandlerMap[ pEvent->getId() ] = pEvent;
}

std::map< uint32_t, Event::EventHandlerPtr >& Player::getEventListRef()
{
  return m_eventHandlerMap;
}

Event::EventHandlerPtr Player::getEvent( uint32_t eventId ) const
{
  auto it = m_eventHandlerMap.find( eventId );
  if( it != m_eventHandlerMap.end() )
    return it->second;

  return nullptr;
}

size_t Player::getEventCount()
{
  return m_eventHandlerMap.size();
}

void Player::removeEvent( uint32_t eventId )
{
  auto it = m_eventHandlerMap.find( eventId );
  if( it != m_eventHandlerMap.end() )
  {
    m_eventHandlerMap.erase( it );
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Player::onDeath()
{
  Service< World::Manager::PlayerMgr >::ref().onDeath( *this );
}

// TODO: slightly ugly here and way too static. Needs too be done properly
void Player::onTick()
{
  Chara::onTick();
  // add 3 seconds to total play time
  m_playTime += 3;

  if( !isAlive() || !isLoadingComplete() )
    return;

  bool sendUpdate = performResting();

  if( sendUpdate )
    Network::Util::Packet::sendRestingUpdate( *this );
}

bool Player::performResting()
{
  bool sendUpdate = false;
  auto addHp = static_cast< uint32_t >( static_cast< float >( getMaxHp() ) * 0.1f + 1 );
  auto addMp = static_cast< uint32_t >( static_cast< float >( getMaxMp() ) * 0.06f + 1 );
  uint32_t addTp = 100;

  if( !m_actorIdTohateSlotMap.empty() )
  {
    addHp = static_cast< uint32_t >( static_cast< float >( getMaxHp() ) * 0.01f + 1 );
    addMp = static_cast< uint32_t >( static_cast< float >( getMaxMp() ) * 0.02f + 1 );
    addTp = 60;
  }

  if( m_hp < getMaxHp() )
  {

    if( m_hp + addHp < getMaxHp() )
      m_hp += addHp;
    else
      m_hp = getMaxHp();

    sendUpdate = true;
  }

  if( m_mp < getMaxMp() )
  {

    if( m_mp + addMp < getMaxMp() )
      m_mp += addMp;
    else
      m_mp = getMaxMp();

    sendUpdate = true;
  }

  if( m_tp < 1000 )
  {
    if( m_tp + addTp < 1000 )
      m_tp += addTp;
    else
      m_tp = 1000;

    sendUpdate = true;
  }
  return sendUpdate;
}
