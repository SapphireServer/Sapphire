#ifndef _FRIENDLIST_H
#define _FRIENDLIST_H

#include <src/servers/Server_Common/Common.h>
#include <Server_Common/Network/PacketDef/Zone/ServerZoneDef.h>
#include <Server_Common/Forwards.h>
#include <Server_Zone/Actor/Group/Group.h>
#include <Server_Zone/Forwards.h>
#include <boost/enable_shared_from_this.hpp>
#include <set>
#include <cstdint>
#include <map>

using namespace Core::Network::Packets;
using namespace Core::Network::Packets::Server;

namespace Core {
namespace Entity {
namespace Group {

class FriendList;
using FriendListPtr = boost::shared_ptr< FriendList >;

class FriendList : public Group
{

public:
   FriendList( uint64_t id, uint64_t ownerId, uint32_t maxCapacity, time_point createTime ) :
      Group( id, ownerId, maxCapacity, createTime ),
      m_id( id ), m_ownerId( m_ownerId ), m_maxCapacity( maxCapacity ), m_createTime( createTime ) {};

   ~FriendList() {};

   virtual Core::Network::Packets::GamePacketPtr addMember( PlayerPtr pSender, PlayerPtr pRecipient, uint64_t senderId = 0, uint64_t recipientId = 0 );
   virtual Core::Network::Packets::GamePacketPtr inviteMember( PlayerPtr pSender, PlayerPtr pRecipient, uint64_t senderId = 0, uint64_t recipientId = 0 );
   virtual Core::Network::Packets::GamePacketPtr removeMember( PlayerPtr pSender, PlayerPtr pRecipient, uint64_t senderId = 0, uint64_t recipientId = 0 );
   virtual Core::Network::Packets::GamePacketPtr kickMember( PlayerPtr pSender, PlayerPtr pRecipient, uint64_t senderId = 0, uint64_t recipientId = 0 );
   virtual void sendPacketToMembers( Core::Network::Packets::GamePacketPtr pPacket, bool invitesToo = false );

   virtual void load();
   virtual void update();
   virtual void disband();

   bool isParty() const;
   bool isFriendList() const;
   bool isFreeCompany() const;
   bool isLinkshell() const;
   bool isFreeCompanyPetition() const;
   bool isBlacklist() const;
   bool isContentGroup() const;

   std::vector< Core::Network::Packets::Server::PlayerEntry > getFriendListEntries( uint16_t entryAmount );

   Core::Network::Packets::ZoneChannelPacket< FFXIVIpcSocialList > generateFriendsListPacket( PlayerPtr pPlayer );

private:
   GroupType m_type{ GroupType::FriendList };
   uint64_t m_id{ 0 };
   uint64_t m_ownerId{ 0 };
   uint32_t m_maxCapacity{ 200 };
   uint32_t m_maxRoles{ 8 };
   time_point m_createTime{ std::chrono::steady_clock::now() };
   std::map< uint64_t, GroupMember > m_members;
   std::map< uint64_t, uint64_t > m_invites; // <recipient, sender>


   

};

}
}
};
#endif // ! _FRIENDLIST_H