#include "InstanceContent.h"

#include <common/Common.h>
#include <common/Logging/Logger.h>
#include <common/Util/Util.h>
#include <common/Util/UtilMath.h>
#include <servers/sapphire_zone/Event/Director.h>

#include "Actor/Player.h"

#include "Network/PacketWrappers/ActorControlPacket142.h"
#include "Network/PacketWrappers/ActorControlPacket143.h"

extern Core::Logger g_log;

using namespace Core::Common;
using namespace Core::Network::Packets;
using namespace Core::Network::Packets::Server;

Core::InstanceContent::InstanceContent( boost::shared_ptr< Core::Data::InstanceContent > pInstanceContent,
                                        uint32_t guId,
                                        const std::string& internalName,
                                        const std::string& contentName,
                                        uint32_t instanceContentId )
   : Zone( static_cast< uint16_t >( pInstanceContent->territoryType ), guId, internalName, contentName ),
     Director( Event::Director::InstanceContent, instanceContentId ),
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

   pPlayer->queuePacket(ActorControlPacket143( pPlayer->getId(), DirectorInit, getDirectorId(),
                                               getInstanceContentId() ) );
   pPlayer->setStateFlag( PlayerStateFlag::BoundByDuty );
}

void Core::InstanceContent::onLeaveTerritory( Entity::PlayerPtr pPlayer )
{
   g_log.debug( "InstanceContent::onLeaveTerritory: Zone#" + std::to_string( getGuId() ) + "|"
                                                           + std::to_string( getInstanceContentId() ) +
                                                           + ", Entity#" + std::to_string( pPlayer->getId() ) );
   pPlayer->queuePacket(ActorControlPacket143( pPlayer->getId(), DirectorClear, getDirectorId() ) );
   pPlayer->unsetStateFlag( PlayerStateFlag::BoundByDuty );
}

void Core::InstanceContent::onUpdate( uint32_t currTime )
{

}

void Core::InstanceContent::onFinishLoading( Entity::PlayerPtr pPlayer )
{

}

void Core::InstanceContent::onInitDirector( Entity::PlayerPtr pPlayer )
{

}
