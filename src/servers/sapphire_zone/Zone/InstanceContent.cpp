#include "InstanceContent.h"

Core::InstanceContent::InstanceContent( boost::shared_ptr< Core::Data::InstanceContent > pInstanceContent,
                                        uint32_t guId,
                                        const std::string& internalName,
                                        const std::string& contentName,
                                        uint32_t instanceContentId )
   : Zone( pInstanceContent->territoryType, guId, internalName, contentName ),
     m_instanceContentInfo( pInstanceContent ),
     m_instanceContentId( instanceContentId ),
     m_state( Created )
{

}

Core::InstanceContent::~InstanceContent()
{

}

uint32_t Core::InstanceContent::getInstanceContentId() const
{
   return m_instanceContentId;
}

boost::shared_ptr< Core::Data::InstanceContent > Core::InstanceContent::getInstanceContentInfo() const
{
   return m_instanceContentInfo;
}
