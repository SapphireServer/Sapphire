#include "InstanceContent.h"

Core::InstanceContent::InstanceContent( boost::shared_ptr< Core::Data::InstanceContent > pInstanceContent,
                                        uint32_t guId,
                                        const std::string& internalName,
                                        const std::string& placeName,
                                        const uint32_t instanceContentId )
   : Zone( pInstanceContent->territoryType, guId, internalName, placeName ),
     m_instanceContentRow( pInstanceContent ),
     m_instanceContentId( instanceContentId )
{

}

Core::InstanceContent::~InstanceContent()
{

}