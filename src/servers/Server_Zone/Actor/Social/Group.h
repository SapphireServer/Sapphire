#ifndef _GROUP_H
#define _GROUP_H

#include <Server_Common/Common.h>
#include <Server_Common/Network/PacketDef/Zone/ServerZoneDef.h>
#include <Server_Common/Forwards.h>
#include <Server_Zone/Forwards.h>
#include <boost/enable_shared_from_this.hpp>
#include <set>
#include <cstdint>
#include <map>

namespace Core {
namespace Entity {
namespace Social {

class Group;
using GroupPtr = boost::shared_ptr< Group >;

struct GroupMember
{
   uint64_t inviterId;
   uint64_t contentId; // todo: maybe just use id..
   std::string name;
   uint32_t role;
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

class Group : public boost::enable_shared_from_this< Group >
{
public:
   Group( uint64_t id, uint64_t ownerId ) :
      m_id( id ), m_ownerId( m_ownerId ) {};

   bool isParty() const;
   bool isFriendList() const;
   bool isFreeCompany() const;
   bool isLinkshell() const;
   bool isFreeCompanyPetition() const;
   bool isBlacklist() const;
   bool isContentGroup() const;

   virtual Core::Network::Packets::GamePacketPtr addMember( PlayerPtr pSender, PlayerPtr pRecipient, uint64_t senderId = 0, uint64_t recipientId = 0 );
   
   virtual Core::Network::Packets::GamePacketPtr inviteMember( PlayerPtr pSender, PlayerPtr pRecipient, uint64_t senderId = 0, uint64_t recipientId = 0 );
   virtual Core::Network::Packets::GamePacketPtr removeMember( PlayerPtr pSender, PlayerPtr pRecipient, uint64_t senderId = 0, uint64_t recipientId = 0 );
   //virtual Core::Network::Packets::GamePacketPtr kickMember( PlayerPtr pSender, PlayerPtr pRecipient, uint64_t senderId = 0, uint64_t recipientId = 0 );
   virtual void sendPacketToMembers( Core::Network::Packets::GamePacketPtr pPacket, bool invitesToo = false );

   /*! generates a player entry used for lists (social, etc) */
   static Core::Network::Packets::Server::PlayerEntry generatePlayerEntry( GroupMember groupMember );

   /*! access GroupMember vector */

   std::map< uint64_t, GroupMember > getMembers() const;

   /*! get container limit */
   uint32_t getCapacity() const;

protected:
   GroupType m_type{ GroupType::None };
   uint64_t m_id{ 0 };
   uint64_t m_ownerId{ 0 };
   uint32_t m_maxCapacity{ 250 };
   uint32_t m_maxRoles{ 50 };
   time_point m_createTime{ std::chrono::steady_clock::now() };
   std::map< uint64_t, GroupMember > m_members;
   std::map< uint64_t, GroupMember > m_invites; // <recipient, groupmember (which contains senderId)>

private:
   

   /*virtual void load();
   virtual void update();
   virtual void disband();*/

};

}
}
};
#endif // ! _GROUP_H