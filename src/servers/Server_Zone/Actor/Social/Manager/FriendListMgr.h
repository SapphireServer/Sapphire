#ifndef _FRIENDLISTMGR_H
#define _FRIENDLISTMGR_H

#include <map>
#include <cstdint>

#include <boost/enable_shared_from_this.hpp>
#include <Server_Zone/Forwards.h>
#include <Server_Zone/Actor/Social/Group.h>
#include <Server_Zone/Actor/Social/FriendList.h>

#include <Server_Zone/Actor/Social/Manager/GroupMgr.h>
#include <Server_Zone/Forwards.h>

namespace Core {
namespace Entity {
namespace Social {

class FriendListMgr : public GroupMgr
{
public:
   FriendListMgr();

   bool init();

   uint64_t fetchPlayerFriendsList( uint32_t playerId );
   /*
   FriendListPtr findGroupByInviteIdForPlayer( uint64_t playerId ) const;
   FriendListPtr findGroupById( uint64_t groupId ) const;
   */
   std::map< uint64_t, FriendListPtr > m_groups;
private:
   // todo: can we handle this m_groups grouptype better..?
   
   GroupType m_type{ GroupType::FriendList };

};

}
}
};
#endif /* ! _FRIENDLISTMGR_H */