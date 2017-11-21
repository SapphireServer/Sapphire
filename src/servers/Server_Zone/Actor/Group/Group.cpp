#include <cassert>
#include <boost/shared_ptr.hpp>

#include <Server_Common/Network/PacketDef/Ipcs.h>
#include <Server_Common/Network/PacketDef/Zone/ServerZoneDef.h>
#include <Server_Zone/Actor/Actor.h>
#include <Server_Zone/Actor/Player.h>
#include <Server_Zone/ServerZone.h>
#include <Server_Common/Network/GamePacketNew.h>
#include "Group.h"

// todo: i fuckin have no fuckin clue how to use group manager classes, why not just have a map of <id, group>?
// todo: invite map in g_serverZone.getGroupMgr(GroupType) and look up

Core::Network::Packets::GamePacketPtr Core::Entity::Group::Group::addMember( PlayerPtr pSender, PlayerPtr pRecipient, uint64_t senderId, uint64_t recipientId )
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

   if( m_members.size() < m_maxCapacity )
   {
      // todo: broadcast join message

      m_invites.erase( m_invites.find( recipientId ), m_invites.end() );
      GroupMember member;
      member.inviterId = senderId;
      member.role = 0;
      member.pPlayer = pRecipient;
      m_members.emplace( recipientId, member );
   }
   else
   {
   }

   return packet;
}

void Core::Entity::Group::Group::sendPacketToMembers( Core::Network::Packets::GamePacketPtr pPacket, bool invitesToo )
{
   assert( pPacket );
   if( pPacket )
   {
      for( const auto& member : m_members )
      {
         if( member.second.pPlayer )
         {
            member.second.pPlayer->queuePacket( pPacket );
         }
      }
   }
}

bool Core::Entity::Group::Group::isParty() const
{
   return m_type == GroupType::Party;
}

bool Core::Entity::Group::Group::isFriendList() const
{
   return m_type == GroupType::FriendList;
}

bool Core::Entity::Group::Group::isFreeCompany() const
{
   return m_type == GroupType::FreeCompany;
}

bool Core::Entity::Group::Group::isLinkshell() const
{
   return m_type == GroupType::Linkshell;
}

bool Core::Entity::Group::Group::isFreeCompanyPetition() const
{
   return m_type == GroupType::FreeCompanyPetition;
}

bool Core::Entity::Group::Group::isBlacklist() const
{
   return m_type == GroupType::Blacklist;
}

bool Core::Entity::Group::Group::isContentGroup() const
{
   return m_type == GroupType::ContentGroup;
}