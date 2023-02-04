#include <Network/PacketContainer.h>
#include <Exd/ExdData.h>

#include <utility>

#include "Actor/Player.h"

#include "Territory/Territory.h"
#include "WorldServer.h"

#include "Action/EventAction.h"

using namespace Sapphire::Common;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets::Server;
using namespace Sapphire::World::Manager;

void Sapphire::Entity::Player::addEvent( Event::EventHandlerPtr pEvent )
{
  m_eventHandlerMap[ pEvent->getId() ] = pEvent;
}

std::map< uint32_t, Sapphire::Event::EventHandlerPtr >& Sapphire::Entity::Player::getEventListRef()
{
  return m_eventHandlerMap;
}

Sapphire::Event::EventHandlerPtr Sapphire::Entity::Player::getEvent( uint32_t eventId ) const
{
  auto it = m_eventHandlerMap.find( eventId );
  if( it != m_eventHandlerMap.end() )
    return it->second;

  return nullptr;
}

size_t Sapphire::Entity::Player::getEventCount()
{
  return m_eventHandlerMap.size();
}

void Sapphire::Entity::Player::removeEvent( uint32_t eventId )
{
  auto it = m_eventHandlerMap.find( eventId );
  if( it != m_eventHandlerMap.end() )
  {
    m_eventHandlerMap.erase( it );
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Sapphire::Entity::Player::onDeath()
{

}

// TODO: slightly ugly here and way too static. Needs too be done properly
void Sapphire::Entity::Player::onTick()
{
  Chara::onTick();
  // add 3 seconds to total play time
  m_playTime += 3;

  bool sendUpdate = false;

  if( !isAlive() || !isLoadingComplete() )
    return;

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

  if( sendUpdate )
    sendStatusUpdate();
}
