#include <cassert>
#include <boost/shared_ptr.hpp>
#include <Logging/Logger.h>

#include <sapphire_zone/Session.h>
#include <Network/PacketDef/Ipcs.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <sapphire_zone/Actor/Actor.h>
#include <sapphire_zone/Actor/Player.h>
#include <sapphire_zone/ServerZone.h>
#include <sapphire_zone/Zone/Zone.h>

#include <Network/GamePacketNew.h>
#include "Group.h"
#include "FriendList.h"

extern Core::ServerZone g_serverZone;
extern Core::Logger g_log;

using namespace Core::Network::Packets;
using namespace Core::Network::Packets::Server;

std::vector< PlayerEntry > Core::Social::FriendList::getFriendListEntries( uint16_t entryAmount )
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