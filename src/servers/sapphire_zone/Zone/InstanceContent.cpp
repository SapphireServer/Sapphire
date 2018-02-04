#include "InstanceContent.h"

#include <common/Logging/Logger.h>
#include <common/Util/Util.h>
#include <common/Util/UtilMath.h>

#include "Actor/Player.h"

extern Core::Logger g_log;

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

Core::Data::ExdDataGenerated::InstanceContentPtr Core::InstanceContent::getInstanceContentInfo() const
{
   return m_instanceContentInfo;
}

void Core::InstanceContent::onEnterTerritory( Entity::PlayerPtr pPlayer )
{
   g_log.debug( "InstanceContent::onEnterTerritory: Zone#" + std::to_string( getGuId() ) + "|"
                                                           + std::to_string( getInstanceContentId() ) +
                                                           + ", Entity#" + std::to_string( pPlayer->getId() ) );
}

void Core::InstanceContent::onLeaveTerritory( Entity::PlayerPtr pPlayer )
{
   g_log.debug( "InstanceContent::onLeaveTerritory: Zone#" + std::to_string( getGuId() ) + "|"
                                                           + std::to_string( getInstanceContentId() ) +
                                                           + ", Entity#" + std::to_string( pPlayer->getId() ) );
}

void Core::InstanceContent::onUpdate( uint32_t currTime )
{

}
