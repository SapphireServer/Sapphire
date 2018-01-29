#include "InstanceContent.h"

Core::InstanceContent::InstanceContent( uint16_t territoryId, uint32_t guId, const std::string& internalName, const std::string& placeName )
   : Zone( territoryId, guId, internalName, placeName )
{

}

Core::InstanceContent::~InstanceContent()
{

}