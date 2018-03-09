#ifndef _FRIENDLIST_H
#define _FRIENDLIST_H

#include <Common.h>
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <Forwards.h>
#include <sapphire_zone/Forwards.h>
#include <boost/enable_shared_from_this.hpp>
#include <set>
#include <cstdint>
#include <map>
#include "Group.h"


namespace Core {
namespace Social {

class FriendList : public Group
{

public:
   FriendList( uint64_t id, uint64_t ownerId ) :
      Group( id, ownerId ),
      m_id( id ), m_ownerId( ownerId ) {};

   std::vector< Network::Packets::Server::PlayerEntry > getFriendListEntries( uint16_t entryAmount );

protected:
   uint64_t m_id{ 0 };
   uint64_t m_ownerId{ 0 };
   GroupType m_type{ GroupType::FriendList };
   uint32_t m_maxCapacity{ 200 };

   

};


using FriendListPtr = boost::shared_ptr< FriendList >;

}
};
#endif // ! _FRIENDLIST_H