#ifndef _FRIENDLISTMGR_H
#define _FRIENDLISTMGR_H

#include <map>
#include <cstdint>

#include <boost/enable_shared_from_this.hpp>
#include <Server_Zone/Forwards.h>
#include <Server_Zone/Actor/Group/Group.h>

#include <Server_Zone/Actor/Group/Manager/GroupMgr.h>

namespace Core {
namespace Entity {
namespace Group {

class FriendListMgr : public GroupMgr
{
private:
   GroupType m_type{ GroupType::None };
   uint64_t m_groupCount{ 0 };
   uint32_t m_maxEntries{ 0xFFFFFFFF };
   std::map< uint64_t, GroupPtr > m_groups;  // < groupid, groupPtr >
   std::map< uint64_t, uint64_t > m_invites; // < recipient, groupid >
   virtual GroupPtr createGroup( PlayerPtr pOwner ) = 0;

public:
   FriendListMgr( GroupType type, uint32_t maxEntries ) :
      m_type( type ), m_maxEntries( maxEntries ){};
   ~FriendListMgr(){};

   GroupPtr findGroupByInviteIdForPlayer( uint64_t playerId ) const;
   GroupPtr findGroupById( uint64_t groupId ) const;
};

}
}
};
#endif /* ! _FRIENDLISTMGR_H */