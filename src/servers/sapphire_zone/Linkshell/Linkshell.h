#ifndef CORE_LINKSHELL_H
#define CORE_LINKSHELL_H

#include <Common.h>
#include <set>

namespace Core
{

class Linkshell
{
private:
   /*! unique ID of the linkshell */
   uint64_t m_linkshellId;
   /*! ID of the master character */
   uint64_t m_masterCharacterId;
   /*! ID list of all linkshell members */
   std::set< uint64_t > m_memberIds;
   /*! Name of the linkshell */
   std::string m_name;
   /*! List of member IDs with leader rank */
   std::set< uint64_t > m_leaderIds;
   /*! list of IDs of pending character invites */
   std::set< uint64_t > m_inviteIds;

public:
   Linkshell( uint64_t id,
              const std::string& name,
              uint64_t masterId,
              const std::set< uint64_t >& members,
              const std::set< uint64_t >& leaders,
              const std::set< uint64_t >& invites );

   uint64_t getId() const;

   const std::string& getName() const;

   uint64_t getMasterId() const;

   const std::set< uint64_t >& getMemberIdList() const;
   std::set< uint64_t >& getMemberIdList();

   const std::set< uint64_t >& getLeaderIdList() const;
   std::set< uint64_t >& getLeaderIdList();

   const std::set< uint64_t >& getInviteIdList() const;
   std::set< uint64_t >& getInviteIdList();

   void addMember( uint64_t memberId );
   void removeMember( uint64_t memberId );

   void addLeader( uint64_t memberId );
   void removeLeader( uint64_t memberId );

   void addInvite( uint64_t memberId );
   void removeInvite( uint64_t memberId );


};

}
#endif //SAPPHIRE_LINKSHELL_H
