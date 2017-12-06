#ifndef _FRIENDLIST_H
#define _FRIENDLIST_H

#include <src/servers/Server_Common/Common.h>
#include <Server_Common/Forwards.h>
#include <Server_Zone/Actor/Group/Group.h>
#include <Server_Zone/Forwards.h>
#include <boost/enable_shared_from_this.hpp>
#include <set>
#include <cstdint>
#include <map>



namespace Core {
namespace Entity {
namespace Group {

class FriendList;
using FriendListPtr = boost::shared_ptr< FriendList >;

struct GroupMember
{
   uint64_t contentId;
   char name[32];
   uint32_t category;
   uint64_t inviterId;
};

enum class GroupType : uint8_t
{
   None,
   Party,
   FriendList,
   FreeCompany,
   Linkshell,
   FreeCompanyPetition,
   Blacklist,
   ContentGroup
};

class FriendList : public Group
{
private:
   GroupType m_type{ GroupType::FriendList };
   uint64_t m_id{ 0 };
   uint64_t m_ownerId{ 0 };
   uint32_t m_maxCapacity{ 200 };
   uint32_t m_maxRoles{ 8 };
   time_point m_createTime{ std::chrono::steady_clock::now() };
   std::map< uint64_t, GroupMember > m_members;
   std::map< uint64_t, uint64_t > m_invites; // <recipient, sender>


   virtual Core::Network::Packets::GamePacketPtr addMember( PlayerPtr pSender, PlayerPtr pRecipient, uint64_t senderId = 0, uint64_t recipientId = 0 );
   virtual Core::Network::Packets::GamePacketPtr inviteMember( PlayerPtr pSender, PlayerPtr pRecipient, uint64_t senderId = 0, uint64_t recipientId = 0 );
   virtual Core::Network::Packets::GamePacketPtr removeMember( PlayerPtr pSender, PlayerPtr pRecipient, uint64_t senderId = 0, uint64_t recipientId = 0 );
   virtual Core::Network::Packets::GamePacketPtr kickMember( PlayerPtr pSender, PlayerPtr pRecipient, uint64_t senderId = 0, uint64_t recipientId = 0 );
   virtual void sendPacketToMembers( Core::Network::Packets::GamePacketPtr pPacket, bool invitesToo = false );

   virtual void load();
   virtual void update();
   virtual void disband();
public:
   FriendList( uint64_t id, uint64_t ownerId, uint32_t maxCapacity, time_point createTime ) :
      m_id( id ), m_ownerId( m_ownerId ), m_maxCapacity( maxCapacity ),  m_createTime( createTime ){};
   ~FriendList(){};

   bool isParty() const;
   bool isFriendList() const;
   bool isFreeCompany() const;
   bool isLinkshell() const;
   bool isFreeCompanyPetition() const;
   bool isBlacklist() const;
   bool isContentGroup() const;
};

}
}
};
#endif // ! _FRIENDLIST_H