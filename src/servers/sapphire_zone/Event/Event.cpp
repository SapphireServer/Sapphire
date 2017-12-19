#include "Event.h"

Core::Event::Event::Event( uint64_t actorId, uint32_t eventId, uint8_t eventType, uint8_t eventParam2, uint32_t eventParam3 )
   : m_actorId( actorId ),
     m_eventId( eventId ),
     m_playedScene( false )
{
  
   m_param1 = static_cast< uint16_t >( eventId );
   m_param2 = static_cast< uint16_t >( eventId >> 16 );

   m_eventType = eventType;
   m_eventParam2 = eventParam2;
   m_eventParam3 = eventParam3;

   m_callback = nullptr;
}

uint64_t Core::Event::Event::getActorId() const
{
   return m_actorId;
}

uint32_t Core::Event::Event::getId() const
{
   return m_eventId;
}

uint32_t Core::Event::Event::getParam1() const
{
   return m_param1;
}

uint16_t Core::Event::Event::getParam2() const
{
   return m_param2;
}

uint8_t Core::Event::Event::getEventType() const
{
   return m_eventType;
}

uint32_t Core::Event::Event::getEventParam2() const
{
   return m_eventParam2;
}

uint32_t Core::Event::Event::getEventParam3() const
{
   return m_eventParam3;
}

Core::Scripting::EventReturnCallback Core::Event::Event::getEventReturnCallback() const
{
   return m_callback;
}

void Core::Event::Event::setEventReturnCallback( Scripting::EventReturnCallback callback )
{
   m_callback = callback;
}


bool Core::Event::Event::hasPlayedScene() const
{
   return m_playedScene;
}

void Core::Event::Event::setPlayedScene( bool playedScene )
{
   m_playedScene = playedScene;
}
