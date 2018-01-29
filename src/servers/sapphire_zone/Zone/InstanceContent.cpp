#include "InstanceContent.h"

Core::InstanceContent::InstanceContent( uint16_t territoryId, uint32_t guId, const std::string& internalName, const std::string& placeName, bool bPrivate = false )
   : Zone( territoryId, guId, internalName, placeName, bPrivate )
{

}

Core::InstanceContent::~InstanceContent()
{

}