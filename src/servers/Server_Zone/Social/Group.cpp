#include <cassert>
#include <boost/shared_ptr.hpp>
#include <Server_Common/Logging/Logger.h>

#include <Server_Zone/Session.h>
#include <Server_Common/Network/PacketDef/Ipcs.h>
#include <Server_Common/Network/PacketDef/Zone/ServerZoneDef.h>
#include <Server_Zone/Actor/Actor.h>
#include <Server_Zone/Actor/Player.h>
#include <Server_Zone/ServerZone.h>
#include <Server_Zone/Zone/Zone.h>
#include <Server_Common/Network/GamePacketNew.h>
#include "Group.h"

extern Core::ServerZone g_serverZone;
extern Core::Logger g_log;

using namespace Core::Entity::Social;

// todo: i fuckin have no fuckin clue how to use group manager classes, why not just have a map of <id, group>?
// todo: invite map in g_serverZone.getGroupMgr(GroupType) and look up

Core::Network::Packets::GamePacketPtr Group::addMember( Core::Entity::PlayerPtr pSender, Core::Entity::PlayerPtr pRecipient, uint64_t senderId, uint64_t recipientId )
{
   constexpr uint32_t logMessages[] = {
      0, // 
      1
   };
   assert( pSender != nullptr || senderId != 0 );

   using namespace Core::Network::Packets;

   uint64_t recipientContentId = 0;

   if( pSender )
   {
      senderId = pSender->getId();
   }

   if( pRecipient )
   {
      recipientId = pRecipient->getId();
      recipientContentId = pRecipient->getContentId();
   }

   auto packet = GamePacketNew< Server::FFXIVIpcSocialRequestResponse, ServerZoneIpcType >( recipientId, senderId );
   packet.data().contentId = recipientContentId;
   packet.data().category = Common::SocialCategory::Friends;

   if( m_members.size() < m_maxCapacity )
   {
      // todo: broadcast join message

      m_invites.erase( m_invites.find( recipientId ), m_invites.end() );
      GroupMember member;
      member.inviterId = senderId;
      member.role = 0;
      member.contentId = recipientId;
      member.name = pSender->getName();
      m_members.emplace( recipientId, member );
   }
   else
   {
   }

   return packet;
}

Core::Network::Packets::GamePacketPtr Group::inviteMember( Core::Entity::PlayerPtr pSender, Core::Entity::PlayerPtr pRecipient, uint64_t senderId, uint64_t recipientId )
{
   assert( pSender != nullptr || senderId != 0 );

   auto packet = GamePacketNew< Server::FFXIVIpcSocialRequestResponse, ServerZoneIpcType >( recipientId, senderId );
   packet.data().contentId = recipientId;
   packet.data().category = Common::SocialCategory::Friends;

   if ( m_invites.size() < m_maxCapacity )
   {
      GroupMember member;
      member.inviterId = senderId;
      member.role = 0;
      member.contentId = recipientId;
      member.name = pSender->getName();

      m_invites.emplace( recipientId, member );
   }

   return packet;
}

// todo: fix
Core::Network::Packets::GamePacketPtr Group::removeMember( Core::Entity::PlayerPtr pSender, Core::Entity::PlayerPtr pRecipient, uint64_t senderId, uint64_t recipientId )
{
   assert( pSender != nullptr || senderId != 0 );

   auto packet = GamePacketNew< Server::FFXIVIpcSocialRequestResponse, ServerZoneIpcType >( recipientId, senderId );
   packet.data().contentId = recipientId;
   packet.data().category = Common::SocialCategory::Friends;

   return packet;
}

void Group::sendPacketToMembers( Core::Network::Packets::GamePacketPtr pPacket, bool invitesToo )
{
   assert( pPacket );
   for( const auto& member : m_members )
   {
      auto pSession = g_serverZone.getSession( member.second.name );
      if( pSession )
      {
         pSession->getPlayer()->queuePacket( pPacket );
      }
   }
}

Core::Network::Packets::Server::PlayerEntry Group::generatePlayerEntry( GroupMember groupMember )
{
   Core::Network::Packets::Server::PlayerEntry entry = {};

   memcpy( entry.name, groupMember.name.c_str(), strlen( groupMember.name.c_str() ) );
   entry.contentId = groupMember.contentId;

   // We check if player is online. If so, we can pull more data - otherwise just name
   // todo: set as offline in one of the unknown values, if session does not exist

   auto pSession = g_serverZone.getSession( groupMember.name ); // todo: aa i don't like this. maybe just store their ID instead of contentID???

   entry.timestamp = 1512799339;
   entry.status = 2;
   entry.unknown = 0;
   //entry.entryIcon = 0xf;  
   entry.unavailable = 0;    // unavailable (other world)
   entry.one = 0;

   if( pSession )
   {
      auto pPlayer = pSession->getPlayer();
      entry.contentId = pPlayer->getContentId();
      //entry.bytes[2] = pPlayer->getCurrentZone()->getId();
      
      entry.classJob = pPlayer->getClass();
      
      entry.level = pPlayer->getLevel();
      entry.zoneId = pPlayer->getCurrentZone()->getId();
      entry.grandCompany = pPlayer->getGc();
      memcpy( &entry.fcTag[0], "Meme", 4 );
      entry.clientLanguage = 2;
      entry.knownLanguages = 0x0F;
      entry.onlineStatusMask = pPlayer->getOnlineStatusMask();

      g_log.debug( std::to_string( pPlayer->getContentId() ) );
   }

   // TODO: no idea what this does - me neither
   //listPacket.data().entries[0].one = 1;

   g_log.debug( std::to_string(groupMember.contentId) );

   g_log.debug( std::to_string( entry.contentId ) );
   
   return entry;
}

std::map< uint64_t, GroupMember > Group::getMembers() const
{
   return m_members;
}

uint32_t Group::getCapacity() const
{
   return m_maxCapacity;
}

bool Group::isParty() const
{
   return m_type == GroupType::Party;
}

bool Group::isFriendList() const
{
   return m_type == GroupType::FriendList;
}

bool Group::isFreeCompany() const
{
   return m_type == GroupType::FreeCompany;
}

bool Group::isLinkshell() const
{
   return m_type == GroupType::Linkshell;
}

bool Group::isFreeCompanyPetition() const
{
   return m_type == GroupType::FreeCompanyPetition;
}

bool Group::isBlacklist() const
{
   return m_type == GroupType::Blacklist;
}

bool Group::isContentGroup() const
{
   return m_type == GroupType::ContentGroup;
}