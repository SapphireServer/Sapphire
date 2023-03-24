#include "EventHandler.h"

#include <utility>

using namespace Sapphire;

Event::EventHandler::EventHandler( uint64_t actorId, uint32_t eventId, EventType eventType, uint32_t eventParam ) :
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

uint64_t Event::EventHandler::getActorId() const
{
  return m_actorId;
}

uint32_t Event::EventHandler::getId() const
{
  return m_eventId;
}

uint8_t Event::EventHandler::getEventType() const
{
  return m_eventType;
}

uint16_t Event::EventHandler::getType() const
{
  return m_type;
}

uint16_t Event::EventHandler::getEntryId() const
{
  return m_entryId;
}

uint32_t Event::EventHandler::getEventParam() const
{
  return m_eventParam;
}

Event::EventHandler::SceneReturnCallback Event::EventHandler::getEventReturnCallback() const
{
  return m_returnCallback;
}

void Event::EventHandler::setEventReturnCallback( SceneReturnCallback callback )
{
  m_returnCallback = std::move( callback );
}

Event::EventHandler::QuestSceneReturnCallback Event::EventHandler::getQuestEventReturnCallback() const
{
  return m_questReturnCallback;
}

void Event::EventHandler::setQuestEventReturnCallback( QuestSceneReturnCallback callback )
{
  m_questReturnCallback = std::move( callback );
}

Event::EventHandler::SceneChainCallback Event::EventHandler::getSceneChainCallback() const
{
  return m_chainCallback;
}

void Event::EventHandler::setSceneChainCallback( Event::EventHandler::SceneChainCallback callback )
{
  m_chainCallback = std::move( callback );
}

Event::EventHandler::QuestSceneChainCallback Event::EventHandler::getQuestSceneChainCallback() const
{
  return m_questChainCallback;
}

void Event::EventHandler::setQuestSceneChainCallback( Event::EventHandler::QuestSceneChainCallback callback )
{
  m_questChainCallback = std::move( callback );
}

Event::EventHandler::EventFinishCallback Event::EventHandler::getEventFinishCallback() const
{
  return m_finishCallback;
}

void Event::EventHandler::setEventFinishCallback( EventFinishCallback callback )
{
  m_finishCallback = std::move( callback );
}

bool Event::EventHandler::hasPlayedScene() const
{
  return m_playedScene;
}

void Event::EventHandler::setPlayedScene( bool playedScene )
{
  m_playedScene = playedScene;
}

bool Event::EventHandler::hasNestedEvent() const
{
  return m_pNestedEvent != nullptr;
}

void Event::EventHandler::removeNestedEvent()
{
  m_pNestedEvent.reset();
}

Event::ScenePlayParam* Event::EventHandler::getScenePlayParams()
{
  return &m_scenePlayParams;
}