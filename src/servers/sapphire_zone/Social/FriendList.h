#ifndef _FRIENDLIST_H
#define _FRIENDLIST_H

#include <common/Common.h>
#include <common/Network/PacketDef/Zone/ServerZoneDef.h>
#include <common/Network/GamePacketNew.h>
#include <common/Forwards.h>
#include <sapphire_zone/Social/Group.h>
#include <sapphire_zone/Forwards.h>
#include <boost/enable_shared_from_this.hpp>
#include <set>
#include <cstdint>
#include <map>

using namespace Core::Network::Packets;
using namespace Core::Network::Packets::Server;

namespace Core {
namespace Social {

class FriendList;
using FriendListPtr = boost::shared_ptr< FriendList >;

class FriendList : public Group
{

public:
   FriendList( uint64_t id, uint64_t ownerId ) :
      Group( id, ownerId ),
      m_id( id ), m_ownerId( ownerId ) {};

   /*virtual void load();
   virtual void update();
   virtual void disband();*/

   bool isParty() const;
   bool isFriendList() const;
   bool isFreeCompany() const;
   bool isLinkshell() const;
   bool isFreeCompanyPetition() const;
   /*bool isBlacklist() const;
   bool isContentGroup() const;*/

   std::vector< Core::Network::Packets::Server::PlayerEntry > getFriendListEntries( uint16_t entryAmount );

   

protected:
   uint64_t m_id{ 0 };
   uint64_t m_ownerId{ 0 };
   GroupType m_type{ GroupType::FriendList };
   uint32_t m_maxCapacity{ 200 };

   

};

}
};
#endif // ! _FRIENDLIST_H