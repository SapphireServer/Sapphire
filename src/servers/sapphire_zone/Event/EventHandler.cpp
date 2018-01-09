#include "EventHandler.h"

Core::Event::EventHandler::EventHandler( uint64_t actorId, uint32_t eventId, EventType eventType, uint32_t eventParam3 ) :
     m_actorId( actorId ),
     m_eventId( eventId ),
     m_eventType( eventType ),
     m_playedScene( false )
{
   m_entryId = static_cast< uint16_t >( eventId );
   m_type = static_cast< uint16_t >( eventId >> 16 );

   m_eventParam3 = eventParam3;

   m_callback = nullptr;
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

uint32_t Core::Event::EventHandler::getEventParam3() const
{
   return m_eventParam3;
}

Core::Event::EventHandler::SceneReturnCallback Core::Event::EventHandler::getEventReturnCallback() const
{
   return m_callback;
}

void Core::Event::EventHandler::setEventReturnCallback( SceneReturnCallback callback )
{
   m_callback = callback;
}

bool Core::Event::EventHandler::hasPlayedScene() const
{
   return m_playedScene;
}

void Core::Event::EventHandler::setPlayedScene( bool playedScene )
{
   m_playedScene = playedScene;
}
