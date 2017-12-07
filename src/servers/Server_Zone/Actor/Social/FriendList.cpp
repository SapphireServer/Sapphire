#include <cassert>
#include <boost/shared_ptr.hpp>
#include <src/servers/Server_Common/Common.h>

#include <Server_Common/Network/PacketDef/Ipcs.h>
#include <Server_Common/Network/PacketDef/Zone/ServerZoneDef.h>
#include <src/servers/Server_Common/Logging/Logger.h>
#include <Server_Zone/Actor/Actor.h>
#include <Server_Zone/Actor/Player.h>
#include <Server_Zone/ServerZone.h>
#include <Server_Common/Network/GamePacketNew.h>
#include "FriendList.h"

extern Core::ServerZone g_serverZone;
extern Core::Logger g_log;

using namespace Core::Entity;
using namespace Core::Network::Packets;
using namespace Core::Network::Packets::Server;

std::vector< PlayerEntry > Core::Entity::Social::FriendList::getFriendListEntries( uint16_t entryAmount )
{
   std::vector< PlayerEntry > entryList = {};
   uint16_t limit = 0;

   for ( const auto& member : m_members )
   {
      if ( limit == entryAmount )
         break;

      entryList.push_back( generatePlayerEntry( member.second ) );
      limit++;
   }

   return entryList;
}