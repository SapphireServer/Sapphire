#include "Linkshell.h"


Core::Linkshell::Linkshell( uint64_t id,
                            const std::string &name,
                            uint64_t masterId,
                            const std::set<uint64_t> &members,
                            const std::set<uint64_t> &leaders,
                            const std::set<uint64_t> &invites ) :
  m_linkshellId( id ),
  m_name( name ),
  m_masterCharacterId( masterId ),
  m_memberIds( members ),
  m_leaderIds( leaders ),
  m_inviteIds( invites )
{

}

uint64_t Core::Linkshell::getId() const
{
   return m_linkshellId;
}

uint64_t Core::Linkshell::getMasterId() const
{
   return m_masterCharacterId;
}

const std::set< uint64_t >& Core::Linkshell::getMemberIdList() const
{
   return m_memberIds;
}

std::set< uint64_t >& Core::Linkshell::getMemberIdList()
{
   return m_memberIds;
}

const std::string& Core::Linkshell::getName() const
{
   return m_name;
}

const std::set< uint64_t >& Core::Linkshell::getLeaderIdList() const
{
   return m_leaderIds;
}

std::set< uint64_t >& Core::Linkshell::getLeaderIdList()
{
   return m_leaderIds;
}

const std::set< uint64_t >& Core::Linkshell::getInviteIdList() const
{
   return m_inviteIds;
}

std::set< uint64_t > &Core::Linkshell::getInviteIdList()
{
   return m_inviteIds;
}

void Core::Linkshell::addMember( uint64_t memberId )
{
   m_memberIds.insert( memberId );
}

void Core::Linkshell::removeMember( uint64_t memberId )
{
   m_memberIds.erase( memberId );
}

void Core::Linkshell::addLeader( uint64_t memberId )
{
   m_leaderIds.insert( memberId );
}

void Core::Linkshell::removeLeader( uint64_t memberId )
{
   m_leaderIds.erase( memberId );
}

void Core::Linkshell::addInvite( uint64_t memberId )
{
   m_inviteIds.insert( memberId );
}

void Core::Linkshell::removeInvite( uint64_t memberId )
{
   m_inviteIds.erase( memberId );
}



