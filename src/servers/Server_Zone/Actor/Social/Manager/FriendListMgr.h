#ifndef _FRIENDLISTMGR_H
#define _FRIENDLISTMGR_H

#include <map>
#include <cstdint>

#include <boost/enable_shared_from_this.hpp>
#include <Server_Zone/Forwards.h>
#include <Server_Zone/Actor/Social/Group.h>
#include <Server_Zone/Actor/Social/FriendList.h>

#include <Server_Zone/Actor/Social/Manager/GroupMgr.h>

namespace Core {
namespace Entity {
namespace Social {

class FriendListMgr
{
public:
   FriendListMgr();

   FriendListPtr getPlayerFriendsList( uint32_t playerId );

private:
   GroupType m_type{ GroupType::FriendList };
   uint64_t m_groupCount{ 0 };
   uint32_t m_maxEntries{ 0xFFFFFFFF };
   std::map< uint64_t, GroupPtr > m_groups;  // < groupid, groupPtr >
   std::map< uint64_t, uint64_t > m_invites; // < recipient, groupid >

};

}
}
};
#endif /* ! _FRIENDLISTMGR_H */