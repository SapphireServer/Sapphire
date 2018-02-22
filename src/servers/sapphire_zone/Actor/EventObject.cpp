#include "EventObject.h"
#include "Zone/InstanceContent.h"

Core::Entity::EventObject::EventObject( uint32_t objectId, uint32_t mapLinkId ) :
   Core::Entity::Actor( ObjKind::EventObj ),
   m_mapLinkId( mapLinkId ),
   m_state( 0 )
{
   m_id = objectId;
}

Core::Entity::EventObject::EventObject( uint32_t objectId, uint32_t mapLinkId, Common::FFXIVARR_POSITION3 pos ) :
   EventObject( objectId, mapLinkId )
{

}

uint32_t Core::Entity::EventObject::getMapLinkId() const
{
   return m_mapLinkId;
}

void Core::Entity::EventObject::setMapLinkId( uint32_t mapLinkId )
{
   m_mapLinkId = mapLinkId;
}

uint8_t Core::Entity::EventObject::getState() const
{
   return m_state;
}

void Core::Entity::EventObject::setState( uint8_t state )
{
   m_state = state;

   //m_parentInstance->updateEObj( InstanceObjectPtr( this ) );
}

void Core::Entity::EventObject::setParentInstance( Core::InstanceContentPtr instance )
{
   m_parentInstance = instance;
}

Core::InstanceContentPtr Core::Entity::EventObject::getParentInstance() const
{
   return m_parentInstance;
}