#ifndef CORE_LINKSHELL_H
#define CORE_LINKSHELL_H

#include <Server_Common/Common.h>
#include <set>

namespace Core
{

class Linkshell
{
private:
   /*! unique ID of the linkshell */
   uint32_t m_linkshellId;
   /*! ID of the master character */
   uint32_t m_masterCharacterId;
   /*! ID list of all linkshell members */
   std::set< uint32_t > m_memberIds;
   /*! Name of the linkshell */
   std::string m_name;
   /*! List of member IDs with leader rank */
   std::set< uint32_t > m_leaderIds;
   /*! list of IDs of pending character invites */
   std::set< uint32_t > m_inviteIds;

public:
   Linkshell( uint32_t id,
              const std::string& name,
              uint32_t masterId,
              const std::set< uint32_t >& members,
              const std::set< uint32_t >& leaders,
              const std::set< uint32_t >& invites );

   uint32_t getId() const;

   const std::string& getName() const;

   uint32_t getMasterId() const;

   const std::set< uint32_t >& getMemberIdList() const;
   std::set< uint32_t >& getMemberIdList();

   const std::set< uint32_t >& getLeaderIdList() const;
   std::set< uint32_t >& getLeaderIdList();

   const std::set< uint32_t >& getInviteIdList() const;
   std::set< uint32_t >& getInviteIdList();

   void addMember( uint32_t memberId );
   void removeMember( uint32_t memberId );

   void addLeader( uint32_t memberId );
   void removeLeader( uint32_t memberId );

   void addInvite( uint32_t memberId );
   void removeInvite( uint32_t memberId );


};

}
#endif //SAPPHIRE_LINKSHELL_H
