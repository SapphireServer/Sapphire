#ifndef _SOCIALMGR_H
#define _SOCIALMGR_H

#include <map>
#include <cstdint>

#include <boost/enable_shared_from_this.hpp>
#include <sapphire_zone/Forwards.h>
#include <Social/Group.h>

#include "Forwards.h"

namespace Core {
namespace Social {

template< class T >
class SocialMgr
{
public:

   SocialMgr();
   virtual ~SocialMgr();

   T findGroupByInviteIdForPlayer( uint64_t playerId ) const;
   T findGroupById( uint64_t groupId ) const;
   /*

   T findGroup( uint64_t groupId )
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
// those would be implemented in T, so you'd have T.m_type and T.m_maxEntries
//   GroupType m_type{ GroupType::None };
//   uint32_t m_maxEntries{ 0xFFFFFFFF };

   uint64_t m_groupCount{ 0 };   
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

   virtual uint64_t generateGroupId() const;

private:
   std::map< uint64_t, T > m_groups;

};

}
};
#endif /* ! _SOCIALMGR_H  */