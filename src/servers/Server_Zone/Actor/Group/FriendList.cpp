#include <cassert>
#include <boost/shared_ptr.hpp>
#include <src/servers/Server_Common/Common.h>

#include <Server_Common/Network/PacketDef/Ipcs.h>
#include <Server_Common/Network/PacketDef/Zone/ServerZoneDef.h>
#include <Server_Zone/Actor/Actor.h>
#include <Server_Zone/Actor/Player.h>
#include <Server_Zone/ServerZone.h>
#include <Server_Common/Network/GamePacketNew.h>
#include "FriendList.h"

extern Core::ServerZone g_serverZone;

using namespace Core::Network::Packets;
using namespace Core::Network::Packets::Server;

std::vector< PlayerEntry > Core::Entity::Group::FriendList::getFriendListEntries( uint16_t entryAmount )
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

//todo: make this function generic for all groups, and override if needed?
Core::Network::Packets::ZoneChannelPacket< FFXIVIpcSocialList > Core::Entity::Group::FriendList::generateFriendsListPacket( PlayerPtr pPlayer )
{
   ZoneChannelPacket< FFXIVIpcSocialList > listPacket( pPlayer->getId() );
   listPacket.data().type = 0x0B;
   listPacket.data().sequence = 10;
   memset( listPacket.data().entries, 0, sizeof( listPacket.data().entries ) );

   uint16_t i = 0;

   for ( const auto& member : m_members )
   {
      if ( i == 10 )
         break;

      listPacket.data().entries[i] = generatePlayerEntry( member.second );
      i++;
   }

   return listPacket;
}
