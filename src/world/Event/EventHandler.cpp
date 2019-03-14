#include "EventHandler.h"

Sapphire::Event::EventHandler::EventHandler( uint64_t actorId, uint32_t eventId,
                                             EventType eventType, uint32_t eventParam ) :
  m_actorId( actorId ),
  m_eventId( eventId ),
  m_eventType( eventType ),
  m_playedScene( false )
{
  m_entryId = static_cast< uint16_t >( eventId );
  m_type = static_cast< uint16_t >( eventId >> 16 );
  m_eventParam = eventParam;
  m_returnCallback = nullptr;
}

uint64_t Sapphire::Event::EventHandler::getActorId() const
{
  return m_actorId;
}

uint32_t Sapphire::Event::EventHandler::getId() const
{
  return m_eventId;
}

uint8_t Sapphire::Event::EventHandler::getEventType() const
{
  return m_eventType;
}

uint16_t Sapphire::Event::EventHandler::getType() const
{
  return m_type;
}

uint16_t Sapphire::Event::EventHandler::getEntryId() const
{
  return m_entryId;
}

uint32_t Sapphire::Event::EventHandler::getEventParam() const
{
  return m_eventParam;
}

Sapphire::Event::EventHandler::SceneReturnCallback Sapphire::Event::EventHandler::getEventReturnCallback() const
{
  return m_returnCallback;
}

void Sapphire::Event::EventHandler::setEventReturnCallback( SceneReturnCallback callback )
{
  m_returnCallback = callback;
}

Sapphire::Event::EventHandler::SceneChainCallback Sapphire::Event::EventHandler::getSceneChainCallback() const
{
  return m_chainCallback;
}

void Sapphire::Event::EventHandler::setSceneChainCallback( Sapphire::Event::EventHandler::SceneChainCallback callback )
{
  m_chainCallback = callback;
}

Sapphire::Event::EventHandler::EventFinishCallback Sapphire::Event::EventHandler::getEventFinishCallback() const
{
  return m_finishCallback;
}

void Sapphire::Event::EventHandler::setEventFinishCallback( EventFinishCallback callback )
{
  m_finishCallback = callback;
}

bool Sapphire::Event::EventHandler::hasPlayedScene() const
{
  return m_playedScene;
}

void Sapphire::Event::EventHandler::setPlayedScene( bool playedScene )
{
  m_playedScene = playedScene;
}

bool Sapphire::Event::EventHandler::hasNestedEvent() const
{
  return m_pNestedEvent != nullptr;
}

void Sapphire::Event::EventHandler::removeNestedEvent()
{
  m_pNestedEvent.reset();
}

