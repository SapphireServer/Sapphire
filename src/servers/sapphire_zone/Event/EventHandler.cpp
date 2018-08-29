#include "EventHandler.h"

Core::Event::EventHandler::EventHandler( Entity::Player* pOwner, uint64_t actorId, uint32_t eventId,
                                         EventType eventType, uint32_t eventParam ) :
  m_pOwner( pOwner ),
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

uint64_t Core::Event::EventHandler::getActorId() const
{
  return m_actorId;
}

uint32_t Core::Event::EventHandler::getId() const
{
  return m_eventId;
}

uint8_t Core::Event::EventHandler::getEventType() const
{
  return m_eventType;
}

uint16_t Core::Event::EventHandler::getType() const
{
  return m_type;
}

uint16_t Core::Event::EventHandler::getEntryId() const
{
  return m_entryId;
}

uint32_t Core::Event::EventHandler::getEventParam() const
{
  return m_eventParam;
}

Core::Event::EventHandler::SceneReturnCallback Core::Event::EventHandler::getEventReturnCallback() const
{
  return m_returnCallback;
}

void Core::Event::EventHandler::setEventReturnCallback( SceneReturnCallback callback )
{
  m_returnCallback = callback;
}

Core::Event::EventHandler::SceneChainCallback Core::Event::EventHandler::getSceneChainCallback() const
{
  return m_chainCallback;
}

void Core::Event::EventHandler::setSceneChainCallback( Core::Event::EventHandler::SceneChainCallback callback )
{
  m_chainCallback = callback;
}

bool Core::Event::EventHandler::hasPlayedScene() const
{
  return m_playedScene;
}

void Core::Event::EventHandler::setPlayedScene( bool playedScene )
{
  m_playedScene = playedScene;
}

bool Core::Event::EventHandler::hasNestedEvent() const
{
  return m_pNestedEvent != nullptr;
}

void Core::Event::EventHandler::removeNestedEvent()
{
  m_pNestedEvent.reset();
}

