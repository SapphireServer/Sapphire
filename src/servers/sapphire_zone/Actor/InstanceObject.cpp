#include "InstanceObject.h"
#include "Zone/InstanceContent.h"

Core::Entity::InstanceObject::InstanceObject( uint32_t objectId, uint32_t mapLinkId ) :
   Core::Entity::GameObject( ObjKind::EventObj ),
   m_mapLinkId( mapLinkId ),
   m_state( 0 )
{
   m_id = objectId;
}

Core::Entity::InstanceObject::InstanceObject( uint32_t objectId, uint32_t mapLinkId, Common::FFXIVARR_POSITION3 pos ) :
   InstanceObject( objectId, mapLinkId )
{

}

uint32_t Core::Entity::InstanceObject::getHierachyId() const
{
   return m_mapLinkId;
}

void Core::Entity::InstanceObject::setHierachyId( uint32_t hierachyId )
{
   m_mapLinkId = hierachyId;
}

uint8_t Core::Entity::InstanceObject::getState() const
{
   return m_state;
}

void Core::Entity::InstanceObject::setState( uint8_t state )
{
   m_state = state;

   //m_parentInstance->updateInstanceObj( InstanceObjectPtr( this ) );
}

void Core::Entity::InstanceObject::setParentInstance( Core::InstanceContentPtr instance )
{
   m_parentInstance = instance;
}

Core::InstanceContentPtr Core::Entity::InstanceObject::getParentInstance() const
{
   return m_parentInstance;
}