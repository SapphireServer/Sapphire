#include "InstanceContent.h"

Core::InstanceContent::InstanceContent( boost::shared_ptr< Core::Data::InstanceContent > pInstanceContent,
                                        uint32_t guId,
                                        const std::string& internalName,
                                        const std::string& placeName )
   : Zone( pInstanceContent->territoryType, guId, internalName, placeName ),
     m_instanceContentRow( pInstanceContent )
{

}

Core::InstanceContent::~InstanceContent()
{

}