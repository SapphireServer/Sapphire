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

enum FriendEntryType : uint8_t
{
   Invalid = 0,
   Added = 0x10,
   SentRequest = 0x20,
   ReceivedRequest = 0x30
};

struct FriendEntry
{
   uint32_t timestamp;
   FriendEntryType entryStatus;
   uint8_t unknown;
   uint8_t friendGroup;
};

class FriendList : public Group
{

public:
   FriendList( uint64_t id, uint64_t ownerId ) :
      Group( id, ownerId ),
      m_id( id ), m_ownerId( ownerId ) {};

   std::vector< Network::Packets::Server::PlayerEntry > getFriendListEntries( uint16_t entryAmount );

   Core::Network::Packets::Server::PlayerEntry generatePlayerEntry( uint64_t contentId );

   uint32_t addMember( uint64_t contentId, FriendEntryType friendEntryType );

   uint32_t processInvite( uint64_t contentId, Common::SocialRequestAction );

   uint32_t removeMember( uint64_t contentId );

   uint32_t getFriendIndex( uint64_t contentId );

   /*! access entry vector */
   std::vector< FriendEntry >& getEntries();

protected:
   uint64_t m_id{ 0 };
   uint64_t m_ownerId{ 0 };
   GroupType m_type{ GroupType::FriendList };
   uint32_t m_maxCapacity{ 200 };
   
   // todo: profile and evaluate set vs vector approach
   std::vector< FriendEntry > m_entries;

};


using FriendListPtr = boost::shared_ptr< FriendList >;

}
};
#endif // ! _FRIENDLIST_H