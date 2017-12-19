#ifndef _GROUPMGR_H
#define _GROUPMGR_H

#include <map>
#include <cstdint>

#include <boost/enable_shared_from_this.hpp>
#include <Server_Zone/Forwards.h>
#include <Server_Zone/Actor/Social/Group.h>

namespace Core {
namespace Entity {
namespace Social {

class GroupMgr
{
public:
   GroupMgr();
   virtual ~GroupMgr();

   virtual GroupPtr findGroupByInviteIdForPlayer( uint64_t playerId ) const;
   virtual GroupPtr findGroupById( uint64_t groupId ) const;
   /*
   template <typename GroupPtr>
   GroupPtr findGroup( uint64_t arg )
   {
      auto it = m_groups.find( groupId );
      if ( it != m_groups.end() )
      {
         return it->second;
      }
      return nullptr;
   }*/

   bool hasInvite( uint64_t playerId ) const;

protected:
   GroupType m_type{ GroupType::None };
   uint64_t m_groupCount{ 0 };
   uint32_t m_maxEntries{ 0xFFFFFFFF };
   
   std::map< uint64_t, uint64_t > m_invites;

   uint64_t m_lastGroupId{ 0 };

   // < recipient, groupid >
   //virtual GroupPtr createGroup( PlayerPtr pOwner ) = 0;

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

   virtual uint64_t generateGroupId();

private:
   std::map< uint64_t, GroupPtr > m_groups;

};

}
}
};
#endif /* ! _GROUPMGR_H */