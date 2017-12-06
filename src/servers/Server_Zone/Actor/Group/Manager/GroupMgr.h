#ifndef _GROUPMGR_H
#define _GROUPMGR_H

#include <map>
#include <cstdint>

#include <boost/enable_shared_from_this.hpp>
#include <Server_Zone/Forwards.h>
#include <Server_Zone/Actor/Group/Group.h>

namespace Core {
namespace Entity {
namespace Group {

class GroupMgr : public boost::enable_shared_from_this< GroupMgr >
{
private:
   GroupType m_type{ GroupType::None };
   uint64_t m_groupCount{ 0 };
   uint32_t m_maxEntries{ 0xFFFFFFFF };
   std::map< uint64_t, GroupPtr > m_groups;
   std::map< uint64_t, uint64_t > m_invites; // < recipient, groupid >
   virtual GroupPtr createGroup( PlayerPtr pOwner ) = 0;

   /*
   friend virtual Core::Network::Packets::GamePacketPtr Core::Entity::Group::Group::addMember( PlayerPtr pSender, PlayerPtr pRecipient, uint64_t senderId = 0, uint64_t recipientId = 0 );
   friend virtual Core::Network::Packets::GamePacketPtr Core::Entity::Group::Group::inviteMember( PlayerPtr pSender, PlayerPtr pRecipient, uint64_t senderId = 0, uint64_t recipientId = 0 );
   friend virtual Core::Network::Packets::GamePacketPtr Core::Entity::Group::Group::removeMember( PlayerPtr pSender, PlayerPtr pRecipient, uint64_t senderId = 0, uint64_t recipientId = 0 );
   friend virtual Core::Network::Packets::GamePacketPtr Core::Entity::Group::Group::kickMember( PlayerPtr pSender, PlayerPtr pRecipient, uint64_t senderId = 0, uint64_t recipientId = 0 );
   friend virtual void sendPacketToMembers( Core::Network::Packets::GamePacketPtr pPacket, bool invitesToo = false );

   friend virtual void load();
   friend virtual void update();
   friend virtual void disband();
   */
public:
   GroupMgr( GroupType type, uint32_t maxEntries ) :
      m_type( type ), m_maxEntries( maxEntries ){};
   ~GroupMgr(){};

   GroupPtr findGroupByInviteIdForPlayer( uint64_t playerId ) const;
   GroupPtr findGroupById( uint64_t groupId ) const;
};

}
}
};
#endif /* ! _GROUPMGR_H */